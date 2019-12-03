/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QWidget *widget;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox;
    QFormLayout *formLayout;
    QLabel *rowLabel;
    QSpinBox *rowBox;
    QLabel *colLabel;
    QSpinBox *colBox;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout_3;
    QWidget *widget_4;
    QHBoxLayout *horizontalLayout;
    QLabel *label_3;
    QSpinBox *spinBox_3;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *backBtn;
    QPushButton *resetBtn;
    QPushButton *nextBtn;
    QComboBox *comboBox;
    QPushButton *loadFileBtn;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QSpacerItem *horizontalSpacer;
    QLabel *infoLabel;
    QGraphicsView *graphicsView;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1007, 622);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        widget = new QWidget(centralWidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy);
        widget->setMaximumSize(QSize(200, 16777215));
        verticalLayout_2 = new QVBoxLayout(widget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        groupBox = new QGroupBox(widget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        formLayout = new QFormLayout(groupBox);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        rowLabel = new QLabel(groupBox);
        rowLabel->setObjectName(QString::fromUtf8("rowLabel"));

        formLayout->setWidget(0, QFormLayout::LabelRole, rowLabel);

        rowBox = new QSpinBox(groupBox);
        rowBox->setObjectName(QString::fromUtf8("rowBox"));
        rowBox->setMinimum(4);
        rowBox->setMaximum(10000);

        formLayout->setWidget(0, QFormLayout::FieldRole, rowBox);

        colLabel = new QLabel(groupBox);
        colLabel->setObjectName(QString::fromUtf8("colLabel"));

        formLayout->setWidget(1, QFormLayout::LabelRole, colLabel);

        colBox = new QSpinBox(groupBox);
        colBox->setObjectName(QString::fromUtf8("colBox"));
        colBox->setMinimum(4);
        colBox->setMaximum(10000);

        formLayout->setWidget(1, QFormLayout::FieldRole, colBox);


        verticalLayout_2->addWidget(groupBox);

        groupBox_2 = new QGroupBox(widget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        verticalLayout = new QVBoxLayout(groupBox_2);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        widget_2 = new QWidget(groupBox_2);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        verticalLayout_3 = new QVBoxLayout(widget_2);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        widget_4 = new QWidget(widget_2);
        widget_4->setObjectName(QString::fromUtf8("widget_4"));
        horizontalLayout = new QHBoxLayout(widget_4);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_3 = new QLabel(widget_4);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout->addWidget(label_3);

        spinBox_3 = new QSpinBox(widget_4);
        spinBox_3->setObjectName(QString::fromUtf8("spinBox_3"));
        spinBox_3->setMinimum(1);

        horizontalLayout->addWidget(spinBox_3);


        verticalLayout_3->addWidget(widget_4);

        widget_3 = new QWidget(widget_2);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        horizontalLayout_2 = new QHBoxLayout(widget_3);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        backBtn = new QPushButton(widget_3);
        backBtn->setObjectName(QString::fromUtf8("backBtn"));

        horizontalLayout_2->addWidget(backBtn);

        resetBtn = new QPushButton(widget_3);
        resetBtn->setObjectName(QString::fromUtf8("resetBtn"));

        horizontalLayout_2->addWidget(resetBtn);

        nextBtn = new QPushButton(widget_3);
        nextBtn->setObjectName(QString::fromUtf8("nextBtn"));

        horizontalLayout_2->addWidget(nextBtn);


        verticalLayout_3->addWidget(widget_3);


        verticalLayout->addWidget(widget_2);

        comboBox = new QComboBox(groupBox_2);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        verticalLayout->addWidget(comboBox);


        verticalLayout_2->addWidget(groupBox_2);

        loadFileBtn = new QPushButton(widget);
        loadFileBtn->setObjectName(QString::fromUtf8("loadFileBtn"));

        verticalLayout_2->addWidget(loadFileBtn);

        pushButton = new QPushButton(widget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        verticalLayout_2->addWidget(pushButton);

        pushButton_2 = new QPushButton(widget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        verticalLayout_2->addWidget(pushButton_2);


        gridLayout->addWidget(widget, 0, 2, 2, 1);

        horizontalSpacer = new QSpacerItem(20, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 1, 1, 1);

        infoLabel = new QLabel(centralWidget);
        infoLabel->setObjectName(QString::fromUtf8("infoLabel"));

        gridLayout->addWidget(infoLabel, 2, 0, 1, 1);

        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));

        gridLayout->addWidget(graphicsView, 1, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Size", nullptr));
        rowLabel->setText(QCoreApplication::translate("MainWindow", "Height", nullptr));
        colLabel->setText(QCoreApplication::translate("MainWindow", "Width", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "Solving settings", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Steps", nullptr));
        backBtn->setText(QCoreApplication::translate("MainWindow", "\342\206\220", nullptr));
        resetBtn->setText(QCoreApplication::translate("MainWindow", "\342\227\213", nullptr));
        nextBtn->setText(QCoreApplication::translate("MainWindow", "\342\206\222", nullptr));
        loadFileBtn->setText(QCoreApplication::translate("MainWindow", "Load From File", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "Generate", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "Solve", nullptr));
        infoLabel->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
