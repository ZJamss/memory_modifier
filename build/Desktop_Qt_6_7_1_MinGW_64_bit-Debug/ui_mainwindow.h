/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout;
    QComboBox *comboProcess;
    QLineEdit *editFilter;
    QPushButton *btnRefresh;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLineEdit *editBase;
    QGroupBox *groupBox1;
    QVBoxLayout *vboxLayout;
    QListWidget *listOffsets;
    QHBoxLayout *hboxLayout;
    QPushButton *btnAddOffset;
    QPushButton *btnRemoveOffset;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *btnCalculate;
    QLabel *labelAddress;
    QGroupBox *groupBox_3;
    QHBoxLayout *horizontalLayout_5;
    QComboBox *comboBoxType;
    QLineEdit *editValue;
    QPushButton *btnModify;
    QGroupBox *groupBox_4;
    QVBoxLayout *verticalLayout;
    QTreeWidget *treeWidgetRecords;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *btnAddGroup;
    QPushButton *btnAddRecord;
    QPushButton *btnDelete;
    QPushButton *btnTheme;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 680);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout_2 = new QVBoxLayout(centralwidget);
        verticalLayout_2->setSpacing(8);
        verticalLayout_2->setContentsMargins(8, 8, 8, 8);
        verticalLayout_2->setObjectName("verticalLayout_2");
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        horizontalLayout = new QHBoxLayout(groupBox);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName("horizontalLayout");
        comboProcess = new QComboBox(groupBox);
        comboProcess->setObjectName("comboProcess");
        comboProcess->setMinimumHeight(28);
        comboProcess->setStyleSheet(QString::fromUtf8("QComboBox { \n"
"                      padding: 2px 8px;\n"
"                      background: palette(base);\n"
"                    }"));

        horizontalLayout->addWidget(comboProcess);

        editFilter = new QLineEdit(groupBox);
        editFilter->setObjectName("editFilter");
        editFilter->setMinimumHeight(28);

        horizontalLayout->addWidget(editFilter);

        btnRefresh = new QPushButton(groupBox);
        btnRefresh->setObjectName("btnRefresh");
        btnRefresh->setStyleSheet(QString::fromUtf8("QPushButton { \n"
"                      padding: 4px 8px;\n"
"                      min-width: 60px;\n"
"                      border-radius: 3px;\n"
"                    }"));

        horizontalLayout->addWidget(btnRefresh);


        verticalLayout_2->addWidget(groupBox);

        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName("groupBox_2");
        verticalLayout_3 = new QVBoxLayout(groupBox_2);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName("verticalLayout_3");
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label = new QLabel(groupBox_2);
        label->setObjectName("label");

        horizontalLayout_2->addWidget(label);

        editBase = new QLineEdit(groupBox_2);
        editBase->setObjectName("editBase");
        editBase->setMinimumHeight(28);

        horizontalLayout_2->addWidget(editBase);


        verticalLayout_3->addLayout(horizontalLayout_2);

        groupBox1 = new QGroupBox(groupBox_2);
        groupBox1->setObjectName("groupBox1");
        vboxLayout = new QVBoxLayout(groupBox1);
        vboxLayout->setSpacing(4);
        vboxLayout->setObjectName("vboxLayout");
        listOffsets = new QListWidget(groupBox1);
        listOffsets->setObjectName("listOffsets");
        listOffsets->setMaximumHeight(160);
        listOffsets->setStyleSheet(QString::fromUtf8("\n"
"                            QListWidget::item { \n"
"                              height: 24px;\n"
"                              padding: 2px 4px;\n"
"                              border-bottom: 1px solid palette(mid);\n"
"                            }\n"
"                            QListWidget::item:selected { \n"
"                              background: palette(highlight);\n"
"                              color: palette(highlighted-text);\n"
"                              border: 1px solid palette(highlight);\n"
"                            }\n"
"                          "));

        vboxLayout->addWidget(listOffsets);

        hboxLayout = new QHBoxLayout();
        hboxLayout->setObjectName("hboxLayout");
        btnAddOffset = new QPushButton(groupBox1);
        btnAddOffset->setObjectName("btnAddOffset");
        btnAddOffset->setStyleSheet(QString::fromUtf8("QPushButton { \n"
"                                padding: 0px;\n"
"                                min-width: 24px;\n"
"                                max-width: 24px;\n"
"                                border-radius: 12px;\n"
"                              }"));

        hboxLayout->addWidget(btnAddOffset);

        btnRemoveOffset = new QPushButton(groupBox1);
        btnRemoveOffset->setObjectName("btnRemoveOffset");
        btnRemoveOffset->setStyleSheet(QString::fromUtf8("QPushButton { \n"
"                                padding: 0px;\n"
"                                min-width: 24px;\n"
"                                max-width: 24px;\n"
"                                border-radius: 12px;\n"
"                              }"));

        hboxLayout->addWidget(btnRemoveOffset);


        vboxLayout->addLayout(hboxLayout);


        verticalLayout_3->addWidget(groupBox1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        btnCalculate = new QPushButton(groupBox_2);
        btnCalculate->setObjectName("btnCalculate");

        horizontalLayout_4->addWidget(btnCalculate);

        labelAddress = new QLabel(groupBox_2);
        labelAddress->setObjectName("labelAddress");

        horizontalLayout_4->addWidget(labelAddress);


        verticalLayout_3->addLayout(horizontalLayout_4);


        verticalLayout_2->addWidget(groupBox_2);

        groupBox_3 = new QGroupBox(centralwidget);
        groupBox_3->setObjectName("groupBox_3");
        horizontalLayout_5 = new QHBoxLayout(groupBox_3);
        horizontalLayout_5->setSpacing(8);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        comboBoxType = new QComboBox(groupBox_3);
        comboBoxType->setObjectName("comboBoxType");
        comboBoxType->setMinimumHeight(28);

        horizontalLayout_5->addWidget(comboBoxType);

        editValue = new QLineEdit(groupBox_3);
        editValue->setObjectName("editValue");
        editValue->setMinimumHeight(28);

        horizontalLayout_5->addWidget(editValue);

        btnModify = new QPushButton(groupBox_3);
        btnModify->setObjectName("btnModify");

        horizontalLayout_5->addWidget(btnModify);


        verticalLayout_2->addWidget(groupBox_3);

        groupBox_4 = new QGroupBox(centralwidget);
        groupBox_4->setObjectName("groupBox_4");
        verticalLayout = new QVBoxLayout(groupBox_4);
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName("verticalLayout");
        treeWidgetRecords = new QTreeWidget(groupBox_4);
        treeWidgetRecords->setObjectName("treeWidgetRecords");
        treeWidgetRecords->setMaximumHeight(240);
        treeWidgetRecords->setStyleSheet(QString::fromUtf8("\n"
"                      QTreeWidget::item { \n"
"                        height: 28px;\n"
"                        padding: 2px;\n"
"                      }\n"
"                      QTreeWidget::item:hover { \n"
"                        background: palette(alternate-base); \n"
"                      }\n"
"                      QTreeWidget::item:selected { \n"
"                        border: 1px solid palette(highlight);\n"
"                      }\n"
"                    "));

        verticalLayout->addWidget(treeWidgetRecords);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        btnAddGroup = new QPushButton(groupBox_4);
        btnAddGroup->setObjectName("btnAddGroup");

        horizontalLayout_6->addWidget(btnAddGroup);

        btnAddRecord = new QPushButton(groupBox_4);
        btnAddRecord->setObjectName("btnAddRecord");

        horizontalLayout_6->addWidget(btnAddRecord);

        btnDelete = new QPushButton(groupBox_4);
        btnDelete->setObjectName("btnDelete");

        horizontalLayout_6->addWidget(btnDelete);


        verticalLayout->addLayout(horizontalLayout_6);


        verticalLayout_2->addWidget(groupBox_4);

        btnTheme = new QPushButton(centralwidget);
        btnTheme->setObjectName("btnTheme");
        btnTheme->setCheckable(true);

        verticalLayout_2->addWidget(btnTheme);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 24));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\346\270\270\346\210\217\345\206\205\345\255\230\344\277\256\346\224\271\345\231\250", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "\350\277\233\347\250\213\351\200\211\346\213\251", nullptr));
        editFilter->setPlaceholderText(QCoreApplication::translate("MainWindow", "\350\277\207\346\273\244\350\277\233\347\250\213\345\220\215\347\247\260...", nullptr));
        btnRefresh->setText(QCoreApplication::translate("MainWindow", "\345\210\267\346\226\260", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "\345\234\260\345\235\200\350\256\241\347\256\227", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\345\237\272\345\235\200 (HEX):", nullptr));
        groupBox1->setTitle(QCoreApplication::translate("MainWindow", "\345\201\217\347\247\273\351\207\217\345\210\227\350\241\250", nullptr));
#if QT_CONFIG(tooltip)
        btnAddOffset->setToolTip(QCoreApplication::translate("MainWindow", "\346\267\273\345\212\240\345\201\217\347\247\273\351\207\217", nullptr));
#endif // QT_CONFIG(tooltip)
        btnAddOffset->setText(QCoreApplication::translate("MainWindow", "+", nullptr));
#if QT_CONFIG(tooltip)
        btnRemoveOffset->setToolTip(QCoreApplication::translate("MainWindow", "\345\210\240\351\231\244\351\200\211\344\270\255\345\201\217\347\247\273\351\207\217", nullptr));
#endif // QT_CONFIG(tooltip)
        btnRemoveOffset->setText(QCoreApplication::translate("MainWindow", "-", nullptr));
        btnCalculate->setText(QCoreApplication::translate("MainWindow", "\350\256\241\347\256\227\345\234\260\345\235\200", nullptr));
        labelAddress->setText(QCoreApplication::translate("MainWindow", "\350\256\241\347\256\227\347\273\223\346\236\234\357\274\232", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("MainWindow", "\346\225\260\345\200\274\344\277\256\346\224\271", nullptr));
        btnModify->setText(QCoreApplication::translate("MainWindow", "\344\277\256\346\224\271", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("MainWindow", "\344\277\256\346\224\271\350\256\260\345\275\225", nullptr));
        btnAddGroup->setText(QCoreApplication::translate("MainWindow", "\346\226\260\345\273\272\345\210\206\347\273\204", nullptr));
        btnAddRecord->setText(QCoreApplication::translate("MainWindow", "\346\226\260\345\273\272\350\256\260\345\275\225", nullptr));
        btnDelete->setText(QCoreApplication::translate("MainWindow", "\345\210\240\351\231\244", nullptr));
        btnTheme->setText(QCoreApplication::translate("MainWindow", "\345\244\234\351\227\264\346\250\241\345\274\217", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
