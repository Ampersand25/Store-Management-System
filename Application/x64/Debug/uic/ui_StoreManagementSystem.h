/********************************************************************************
** Form generated from reading UI file 'StoreManagementSystem.ui'
**
** Created by: Qt User Interface Compiler version 6.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STOREMANAGEMENTSYSTEM_H
#define UI_STOREMANAGEMENTSYSTEM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StoreManagementSystemClass
{
public:

    void setupUi(QWidget *StoreManagementSystemClass)
    {
        if (StoreManagementSystemClass->objectName().isEmpty())
            StoreManagementSystemClass->setObjectName("StoreManagementSystemClass");
        StoreManagementSystemClass->resize(600, 400);

        retranslateUi(StoreManagementSystemClass);

        QMetaObject::connectSlotsByName(StoreManagementSystemClass);
    } // setupUi

    void retranslateUi(QWidget *StoreManagementSystemClass)
    {
        StoreManagementSystemClass->setWindowTitle(QCoreApplication::translate("StoreManagementSystemClass", "StoreManagementSystem", nullptr));
    } // retranslateUi

};

namespace Ui {
    class StoreManagementSystemClass: public Ui_StoreManagementSystemClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STOREMANAGEMENTSYSTEM_H
