#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <windows.h>
#include <psapi.h>
#include <QInputDialog>
#include <QMessageBox>
#include <QTreeWidgetItem>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QListWidgetItem>
#include <QStyledItemDelegate>

// 自定义列表项委托用于支持编辑
class EditableDelegate : public QStyledItemDelegate {
public:
    explicit EditableDelegate(QObject* parent = nullptr) : QStyledItemDelegate(parent) {}
    QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem&, const QModelIndex&) const override {
        return new QLineEdit(parent);
    }
};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 初始化控件
    ui->comboBoxType->addItems({"整数（4字节）", "浮点数", "字符串"});
    ui->treeWidgetRecords->setHeaderLabel("修改记录");
    ui->listOffsets->setItemDelegate(new EditableDelegate(this)); // 允许编辑

    // 连接信号槽
    connect(ui->btnRefresh, &QPushButton::clicked, this, &MainWindow::refreshProcessList);
    connect(ui->btnAddOffset, &QPushButton::clicked, [=](){
        bool ok;
        QString offset = QInputDialog::getText(this, "添加偏移量", "输入十六进制偏移量：",
                                               QLineEdit::Normal, "0", &ok,
                                               Qt::MSWindowsFixedSizeDialogHint);
        if(ok && !offset.isEmpty())
            ui->listOffsets->addItem(offset);
    });
    connect(ui->btnRemoveOffset, &QPushButton::clicked, [=](){
        delete ui->listOffsets->currentItem();
    });
    connect(ui->btnCalculate, &QPushButton::clicked, this, &MainWindow::calculateAddress);
    connect(ui->btnModify, &QPushButton::clicked, this, &MainWindow::modifyMemory);
    connect(ui->btnAddGroup, &QPushButton::clicked, this, &MainWindow::addGroup);
    connect(ui->btnAddRecord, &QPushButton::clicked, this, &MainWindow::addRecord);
    connect(ui->btnDelete, &QPushButton::clicked, this, &MainWindow::deleteItem);
    connect(ui->treeWidgetRecords, &QTreeWidget::itemClicked, this, &MainWindow::onRecordClicked);
    connect(ui->listOffsets, &QListWidget::itemDoubleClicked, this, [=](QListWidgetItem* item){
        bool ok;
        QString newVal = QInputDialog::getText(this, "修改偏移量", "新值：",
                                               QLineEdit::Normal, item->text(), &ok);
        if(ok) item->setText(newVal);
    });
    connect(ui->btnTheme, &QPushButton::toggled, this, [=](bool checked){
        QString style = checked ?
                            "QWidget { background: #333; color: #EEE; }"
                            "QLineEdit, QComboBox { background: #444; border: 1px solid #555; }"
                            "QPushButton { background: #666; border: 1px solid #555; }"
                            "QTreeWidget, QListWidget { background: #2A2A2A; }"
                                : "";
        qApp->setStyleSheet(style);
    });

    // 初始状态
    refreshProcessList();
    loadRecords();
    ui->comboProcess->setCurrentIndex(-1); // 取消默认选择
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::refreshProcessList()
{
    ui->comboProcess->clear();
    DWORD processes[1024], cbNeeded;

    if(EnumProcesses(processes, sizeof(processes), &cbNeeded)) {
        DWORD count = cbNeeded / sizeof(DWORD);
        QString filter = ui->editFilter->text().toLower();

        for(DWORD i = 0; i < count; i++) {
            DWORD pid = processes[i];
            if(pid == 0) continue;

            HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pid);
            if(hProcess) {
                WCHAR name[MAX_PATH] = {0};
                if(GetModuleBaseNameW(hProcess, NULL, name, MAX_PATH)) {
                    QString processName = QString::fromWCharArray(name);
                    if(filter.isEmpty() || processName.toLower().contains(filter)) {
                        ui->comboProcess->addItem(QString("%1 (PID: %2)").arg(processName).arg(pid),
                                                  QVariant::fromValue(static_cast<quint32>(pid)));
                    }
                }
                CloseHandle(hProcess);
            }
        }
    }
}

void MainWindow::calculateAddress()
{
    if(!ui->comboProcess->currentData().isValid()) {
        QMessageBox::warning(this, "错误", "请先选择进程");
        return;
    }

    DWORD pid = ui->comboProcess->currentData().toUInt();
    bool ok;
    QString baseStr = ui->editBase->text().trimmed().remove("0x");
    DWORD baseAddr = baseStr.toULong(&ok, 16);

    if(!ok || ui->listOffsets->count() != 2) {
        QMessageBox::warning(this, "错误", "需要：\n1. 正确基址\n2. 两个偏移量");
        return;
    }

    HANDLE hProcess = OpenProcess(PROCESS_VM_READ | PROCESS_VM_WRITE, FALSE, pid);
    if(!hProcess) {
        QMessageBox::critical(this, "错误", QString("打开进程失败 (错误码: %1)").arg(GetLastError()));
        return;
    }

    DWORD addrValue = 0;
    DWORD offset1 = ui->listOffsets->item(0)->text().toUInt(&ok, 16);
    DWORD offset2 = ui->listOffsets->item(1)->text().toUInt(&ok, 16);
    DWORD finalAddr = 0;

    if(!ReadProcessMemory(hProcess, (LPCVOID)baseAddr, &addrValue, sizeof(DWORD), NULL)) {
        QMessageBox::critical(this, "错误", QString("读取基址失败\n0x%1").arg(baseAddr, 8, 16, QLatin1Char('0')));
        goto cleanup;
    }

    if(!ReadProcessMemory(hProcess, (LPCVOID)(addrValue + offset1), &addrValue, sizeof(DWORD), NULL)) {
        QMessageBox::critical(this, "错误", QString("读取一级偏移失败\n0x%1").arg(addrValue + offset1, 8, 16, QLatin1Char('0')));
        goto cleanup;
    }

    finalAddr = addrValue + offset2;
    ui->labelAddress->setText(QString("计算结果：0x%1").arg(finalAddr, 8, 16, QLatin1Char('0')));

cleanup:
    CloseHandle(hProcess);
}

void MainWindow::modifyMemory()
{
    if(!ui->comboProcess->currentData().isValid()) {
        QMessageBox::warning(this, "错误", "请先选择进程");
        return;
    }

    DWORD pid = ui->comboProcess->currentData().toUInt();
    QString addrStr = ui->labelAddress->text().split("0x").last();
    bool ok;
    DWORD_PTR addr = addrStr.toULongLong(&ok, 16);
    QString type = ui->comboBoxType->currentText();
    QString value = ui->editValue->text();

    if(!ok || value.isEmpty()) {
        QMessageBox::warning(this, "错误", "参数不完整");
        return;
    }

    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
    if(!hProcess) {
        QMessageBox::critical(this, "错误", "无法打开进程");
        return;
    }

    QByteArray data;
    if(type == "整数（4字节）") {
        int num = value.toInt(&ok);
        data = QByteArray::fromRawData((char*)&num, sizeof(num));
    }
    else if(type == "浮点数") {
        float num = value.toFloat(&ok);
        data = QByteArray::fromRawData((char*)&num, sizeof(num));
    }
    else {
        data = value.toUtf8();
    }

    SIZE_T written;
    if(WriteProcessMemory(hProcess, (LPVOID)addr, data.constData(), data.size(), &written)) {
        // 自动更新记录（如果当前在记录编辑状态）
        if(auto currentItem = ui->treeWidgetRecords->currentItem()) {
            if(currentItem->data(0, Qt::UserRole) == "record") {
                QJsonObject recordData = currentItem->data(0, Qt::UserRole+1).toJsonObject();
                recordData["value"] = value;
                currentItem->setData(0, Qt::UserRole+1, recordData);
                autoSave();
            }
        }
    }
    else {
        QMessageBox::critical(this, "错误", "写入失败");
    }
    CloseHandle(hProcess);
}

void MainWindow::addGroup()
{
    bool ok;
    QString name = QInputDialog::getText(this, "新建分组", "输入组名：",
                                         QLineEdit::Normal, "", &ok,
                                         Qt::MSWindowsFixedSizeDialogHint);
    if(ok && !name.isEmpty()) {
        QTreeWidgetItem *item = new QTreeWidgetItem(ui->treeWidgetRecords);
        item->setText(0, name);
        item->setData(0, Qt::UserRole, "group");
    }
}

void MainWindow::addRecord()
{
    QTreeWidgetItem *parent = findOrCreateDefaultGroup();

    bool ok;
    QString name = QInputDialog::getText(this, "新建记录", "记录名称：",
                                         QLineEdit::Normal, "未命名", &ok,
                                         Qt::MSWindowsFixedSizeDialogHint);
    if(ok && !name.isEmpty()) {
        QJsonObject recordData{
            {"name", name},
            {"base", ui->editBase->text()},
            {"offsets", QJsonArray::fromStringList(getOffsetStrings())},
            {"type", ui->comboBoxType->currentIndex()},
            {"value", ui->editValue->text()}
        };

        QTreeWidgetItem *item = new QTreeWidgetItem();
        item->setText(0, name);
        item->setData(0, Qt::UserRole, "record");
        item->setData(0, Qt::UserRole+1, recordData);
        item->setSizeHint(0, QSize(0, 28));

        parent->addChild(item);
        autoSave();
    }
}

void MainWindow::onRecordClicked(QTreeWidgetItem *item, int column)
{
    if(!ui->comboProcess->currentData().isValid()) {
        QMessageBox::warning(this, "提示", "请先选择目标进程");
        return;
    }

    if(item && item->data(0, Qt::UserRole) == "record") {
        QJsonObject data = item->data(0, Qt::UserRole+1).toJsonObject();
        ui->editBase->setText(data["base"].toString());
        ui->listOffsets->clear();
        foreach(const QJsonValue &v, data["offsets"].toArray())
            ui->listOffsets->addItem(v.toString());
        ui->comboBoxType->setCurrentIndex(data["type"].toInt());
        ui->editValue->setText(data["value"].toString());
        calculateAddress();
    }
}

void MainWindow::deleteItem()
{
    if(auto item = ui->treeWidgetRecords->currentItem()) {
        if(item->data(0, Qt::UserRole) == "group" && item->childCount() > 0) {
            QMessageBox::warning(this, "警告", "请先删除组内所有记录");
            return;
        }
        delete item;
        autoSave();
    }
}


// 自动保存
void MainWindow::autoSave()
{
    saveRecords(); // 复用原有保存逻辑
}

// 查找或创建默认分组
QTreeWidgetItem* MainWindow::findOrCreateDefaultGroup()
{
    // 查找现有默认分组
    for(int i=0; i<ui->treeWidgetRecords->topLevelItemCount(); i++){
        QTreeWidgetItem *item = ui->treeWidgetRecords->topLevelItem(i);
        if(item->text(0) == "默认分组"){
            return item;
        }
    }

    // 创建新分组
    QTreeWidgetItem *group = new QTreeWidgetItem();
    group->setText(0, "默认分组");
    group->setData(0, Qt::UserRole, "group");
    group->setSizeHint(0, QSize(0, 40)); // 分组项高度
    ui->treeWidgetRecords->addTopLevelItem(group);
    return group;
}

QStringList MainWindow::getOffsetStrings()
{
    QStringList offsets;
    for(int i = 0; i < ui->listOffsets->count(); i++)
        offsets << ui->listOffsets->item(i)->text();
    return offsets;
}


void MainWindow::saveRecords()
{
    QJsonArray groups;
    for(int i = 0; i < ui->treeWidgetRecords->topLevelItemCount(); i++) {
        QTreeWidgetItem *group = ui->treeWidgetRecords->topLevelItem(i);
        QJsonObject groupObj;
        groupObj["name"] = group->text(0);

        QJsonArray records;
        for(int j = 0; j < group->childCount(); j++) {
            QTreeWidgetItem *record = group->child(j);
            records << record->data(0, Qt::UserRole+1).toJsonObject();
        }
        groupObj["records"] = records;
        groups << groupObj;
    }

    QFile file("records.json");
    if(file.open(QIODevice::WriteOnly)) {
        file.write(QJsonDocument(groups).toJson());
        file.close();
    }
}

void MainWindow::loadRecords()
{
    QFile file("records.json");
    if(file.open(QIODevice::ReadOnly)) {
        QJsonArray groups = QJsonDocument::fromJson(file.readAll()).array();
        foreach(const QJsonValue &groupVal, groups) {
            QJsonObject groupObj = groupVal.toObject();
            QTreeWidgetItem *groupItem = new QTreeWidgetItem();
            groupItem->setText(0, groupObj["name"].toString());
            groupItem->setData(0, Qt::UserRole, "group");

            QJsonArray records = groupObj["records"].toArray();
            foreach(const QJsonValue &recordVal, records) {
                QJsonObject recordObj = recordVal.toObject();
                QTreeWidgetItem *recordItem = new QTreeWidgetItem();
                recordItem->setText(0, recordObj["name"].toString());
                recordItem->setData(0, Qt::UserRole, "record");
                recordItem->setData(0, Qt::UserRole+1, recordObj);
                groupItem->addChild(recordItem);
            }
            ui->treeWidgetRecords->addTopLevelItem(groupItem);
        }
    }
}
