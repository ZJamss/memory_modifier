#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidgetItem>
#include <QJsonObject>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void refreshProcessList();
    void calculateAddress();
    void modifyMemory();
    void addGroup();
    void addRecord();
    void deleteItem();
    void onRecordClicked(QTreeWidgetItem *item, int column);

private:
    Ui::MainWindow *ui;
    QStringList getOffsetStrings();
    QTreeWidgetItem* findOrCreateDefaultGroup();
    void saveRecords();
    void loadRecords();
    void autoSave();
};

#endif // MAINWINDOW_H
