/********************************************************************************
** Form generated from reading UI file 'qt11.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QT11_H
#define UI_QT11_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_qt11Class
{
public:

    void setupUi(QDialog *qt11Class)
    {
        if (qt11Class->objectName().isEmpty())
            qt11Class->setObjectName(QStringLiteral("qt11Class"));
        qt11Class->resize(600, 400);

        retranslateUi(qt11Class);

        QMetaObject::connectSlotsByName(qt11Class);
    } // setupUi

    void retranslateUi(QDialog *qt11Class)
    {
        qt11Class->setWindowTitle(QApplication::translate("qt11Class", "qt11", 0));
    } // retranslateUi

};

namespace Ui {
    class qt11Class: public Ui_qt11Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QT11_H
