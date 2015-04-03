/********************************************************************************
** Form generated from reading UI file 'qt1.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QT1_H
#define UI_QT1_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_qt1Class
{
public:
    QWidget *centralWidget;
    QPushButton *pushButton;
    QLineEdit *lineEdit;
    QLineEdit *lineEdit_2;
    QLabel *label;
    QLineEdit *lineEdit_3;
    QLabel *label_2;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *qt1Class)
    {
        if (qt1Class->objectName().isEmpty())
            qt1Class->setObjectName(QStringLiteral("qt1Class"));
        qt1Class->resize(600, 400);
        centralWidget = new QWidget(qt1Class);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(410, 220, 75, 23));
        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(50, 110, 113, 20));
        lineEdit_2 = new QLineEdit(centralWidget);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(200, 110, 113, 20));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(180, 110, 21, 30));
        lineEdit_3 = new QLineEdit(centralWidget);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));
        lineEdit_3->setGeometry(QRect(360, 110, 113, 20));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(330, 110, 21, 30));
        qt1Class->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(qt1Class);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 23));
        qt1Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(qt1Class);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        qt1Class->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(qt1Class);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        qt1Class->setStatusBar(statusBar);
#ifndef QT_NO_SHORTCUT
        label->setBuddy(label);
#endif // QT_NO_SHORTCUT
        QWidget::setTabOrder(lineEdit, lineEdit_2);
        QWidget::setTabOrder(lineEdit_2, lineEdit_3);
        QWidget::setTabOrder(lineEdit_3, pushButton);

        retranslateUi(qt1Class);
        QObject::connect(pushButton, SIGNAL(clicked()), qt1Class, SLOT(close()));

        QMetaObject::connectSlotsByName(qt1Class);
    } // setupUi

    void retranslateUi(QMainWindow *qt1Class)
    {
        qt1Class->setWindowTitle(QApplication::translate("qt1Class", "WindowTitle", 0));
        pushButton->setText(QApplication::translate("qt1Class", "PushButton", 0));
        label->setText(QApplication::translate("qt1Class", "+", 0));
        label_2->setText(QApplication::translate("qt1Class", "=", 0));
    } // retranslateUi

};

namespace Ui {
    class qt1Class: public Ui_qt1Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QT1_H
