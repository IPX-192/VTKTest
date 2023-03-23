/********************************************************************************
** Form generated from reading UI file 'PlaneSlice.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLANESLICE_H
#define UI_PLANESLICE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "QVTKWidget.h"

QT_BEGIN_NAMESPACE

class Ui_PlaneSliceClass
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QVTKWidget *qvtkWidget;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;

    void setupUi(QMainWindow *PlaneSliceClass)
    {
        if (PlaneSliceClass->objectName().isEmpty())
            PlaneSliceClass->setObjectName(QString::fromUtf8("PlaneSliceClass"));
        PlaneSliceClass->resize(600, 400);
        centralWidget = new QWidget(PlaneSliceClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        qvtkWidget = new QVTKWidget(centralWidget);
        qvtkWidget->setObjectName(QString::fromUtf8("qvtkWidget"));

        gridLayout->addWidget(qvtkWidget, 0, 0, 1, 1);

        PlaneSliceClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(PlaneSliceClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 23));
        PlaneSliceClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(PlaneSliceClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        PlaneSliceClass->addToolBar(Qt::TopToolBarArea, mainToolBar);

        retranslateUi(PlaneSliceClass);

        QMetaObject::connectSlotsByName(PlaneSliceClass);
    } // setupUi

    void retranslateUi(QMainWindow *PlaneSliceClass)
    {
        PlaneSliceClass->setWindowTitle(QCoreApplication::translate("PlaneSliceClass", "PlaneSlice", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PlaneSliceClass: public Ui_PlaneSliceClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLANESLICE_H
