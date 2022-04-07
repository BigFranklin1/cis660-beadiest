/********************************************************************************
** Form generated from reading UI file 'cameracontrolshelp.ui'
**
** Created by: Qt User Interface Compiler version 6.1.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CAMERACONTROLSHELP_H
#define UI_CAMERACONTROLSHELP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CameraControlsHelp
{
public:
    QHBoxLayout *horizontalLayout;
    QLabel *label_14;
    QLabel *label_13;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label_9;
    QLabel *label_4;
    QLabel *label_7;
    QLabel *label_3;
    QLabel *label_8;
    QLabel *label_2;
    QLabel *label_5;
    QLabel *label;
    QLabel *label_6;
    QFrame *line;

    void setupUi(QWidget *CameraControlsHelp)
    {
        if (CameraControlsHelp->objectName().isEmpty())
            CameraControlsHelp->setObjectName(QString::fromUtf8("CameraControlsHelp"));
        CameraControlsHelp->resize(414, 184);
        horizontalLayout = new QHBoxLayout(CameraControlsHelp);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_14 = new QLabel(CameraControlsHelp);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout->addWidget(label_14);

        label_13 = new QLabel(CameraControlsHelp);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout->addWidget(label_13);

        label_10 = new QLabel(CameraControlsHelp);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout->addWidget(label_10);

        label_11 = new QLabel(CameraControlsHelp);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_11->setWordWrap(true);

        horizontalLayout->addWidget(label_11);

        label_9 = new QLabel(CameraControlsHelp);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout->addWidget(label_9);

        label_4 = new QLabel(CameraControlsHelp);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout->addWidget(label_4);

        label_7 = new QLabel(CameraControlsHelp);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout->addWidget(label_7);

        label_3 = new QLabel(CameraControlsHelp);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout->addWidget(label_3);

        label_8 = new QLabel(CameraControlsHelp);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout->addWidget(label_8);

        label_2 = new QLabel(CameraControlsHelp);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout->addWidget(label_2);

        label_5 = new QLabel(CameraControlsHelp);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout->addWidget(label_5);

        label = new QLabel(CameraControlsHelp);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout->addWidget(label);

        label_6 = new QLabel(CameraControlsHelp);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout->addWidget(label_6);

        line = new QFrame(CameraControlsHelp);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line);


        retranslateUi(CameraControlsHelp);

        QMetaObject::connectSlotsByName(CameraControlsHelp);
    } // setupUi

    void retranslateUi(QWidget *CameraControlsHelp)
    {
        CameraControlsHelp->setWindowTitle(QCoreApplication::translate("CameraControlsHelp", "Camera Controls", nullptr));
        label_14->setText(QCoreApplication::translate("CameraControlsHelp", "2: Decrease FOV", nullptr));
        label_13->setText(QCoreApplication::translate("CameraControlsHelp", "1: Increase FOV", nullptr));
        label_10->setText(QCoreApplication::translate("CameraControlsHelp", "E: Move up", nullptr));
        label_11->setText(QCoreApplication::translate("CameraControlsHelp", "R: Reset camera to default position and orientation", nullptr));
        label_9->setText(QCoreApplication::translate("CameraControlsHelp", "Q: Move down", nullptr));
        label_4->setText(QCoreApplication::translate("CameraControlsHelp", "D: Move right", nullptr));
        label_7->setText(QCoreApplication::translate("CameraControlsHelp", "Right arrow: Rotate right", nullptr));
        label_3->setText(QCoreApplication::translate("CameraControlsHelp", "A: Move left", nullptr));
        label_8->setText(QCoreApplication::translate("CameraControlsHelp", "Left arrow: Rotate left", nullptr));
        label_2->setText(QCoreApplication::translate("CameraControlsHelp", "S: Move backward", nullptr));
        label_5->setText(QCoreApplication::translate("CameraControlsHelp", "Down arrow: Rotate up", nullptr));
        label->setText(QCoreApplication::translate("CameraControlsHelp", "W: Move forward", nullptr));
        label_6->setText(QCoreApplication::translate("CameraControlsHelp", "Up arrow: Rotate down", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CameraControlsHelp: public Ui_CameraControlsHelp {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CAMERACONTROLSHELP_H
