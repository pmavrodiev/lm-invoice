/********************************************************************************
** Form generated from reading UI file 'locationsTabWidget.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOCATIONSTABWIDGET_H
#define UI_LOCATIONSTABWIDGET_H

#include "../../libs/utils/pathchooser.h"
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QSpacerItem>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LocationsTabWidget
{
public:
    QGridLayout *gridLayout;
    QSpacerItem *verticalSpacer;
    QGroupBox *commonFileSelectors;
    QGridLayout *gridLayout_2;
    QLabel *latexTamplateLabel;
    Utils::PathChooser *latextemplateChooser;
    QLabel *smcDetectionLabel;
    Utils::PathChooser *membersFileChooser;

    void setupUi(QWidget *LocationsTabWidget)
    {
        if (LocationsTabWidget->objectName().isEmpty())
            LocationsTabWidget->setObjectName(QString::fromUtf8("LocationsTabWidget"));
        LocationsTabWidget->resize(785, 368);
        gridLayout = new QGridLayout(LocationsTabWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalSpacer = new QSpacerItem(1, 500, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 1, 0, 1, 1);

        commonFileSelectors = new QGroupBox(LocationsTabWidget);
        commonFileSelectors->setObjectName(QString::fromUtf8("commonFileSelectors"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(commonFileSelectors->sizePolicy().hasHeightForWidth());
        commonFileSelectors->setSizePolicy(sizePolicy);
        gridLayout_2 = new QGridLayout(commonFileSelectors);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        latexTamplateLabel = new QLabel(commonFileSelectors);
        latexTamplateLabel->setObjectName(QString::fromUtf8("latexTamplateLabel"));

        gridLayout_2->addWidget(latexTamplateLabel, 0, 0, 1, 1);

        latextemplateChooser = new Utils::PathChooser(commonFileSelectors);
        latextemplateChooser->setObjectName(QString::fromUtf8("latextemplateChooser"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(1);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(latextemplateChooser->sizePolicy().hasHeightForWidth());
        latextemplateChooser->setSizePolicy(sizePolicy1);

        gridLayout_2->addWidget(latextemplateChooser, 0, 1, 1, 1);

        smcDetectionLabel = new QLabel(commonFileSelectors);
        smcDetectionLabel->setObjectName(QString::fromUtf8("smcDetectionLabel"));

        gridLayout_2->addWidget(smcDetectionLabel, 1, 0, 1, 1);

        membersFileChooser = new Utils::PathChooser(commonFileSelectors);
        membersFileChooser->setObjectName(QString::fromUtf8("membersFileChooser"));
        sizePolicy1.setHeightForWidth(membersFileChooser->sizePolicy().hasHeightForWidth());
        membersFileChooser->setSizePolicy(sizePolicy1);

        gridLayout_2->addWidget(membersFileChooser, 1, 1, 1, 1);


        gridLayout->addWidget(commonFileSelectors, 0, 0, 1, 2);


        retranslateUi(LocationsTabWidget);

        QMetaObject::connectSlotsByName(LocationsTabWidget);
    } // setupUi

    void retranslateUi(QWidget *LocationsTabWidget)
    {
        commonFileSelectors->setTitle(QApplication::translate("LocationsTabWidget", "Generic Settings", 0, QApplication::UnicodeUTF8));
        latexTamplateLabel->setText(QApplication::translate("LocationsTabWidget", "Location of LaTeX template file:", 0, QApplication::UnicodeUTF8));
        smcDetectionLabel->setText(QApplication::translate("LocationsTabWidget", "Detect self-modifying code:", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(LocationsTabWidget);
    } // retranslateUi

};

namespace Ui {
    class LocationsTabWidget: public Ui_LocationsTabWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOCATIONSTABWIDGET_H
