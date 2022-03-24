/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.2.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "mygl.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionQuit;
    QAction *actionCamera_Controls;
    QWidget *centralWidget;
    MyGL *mygl;
    QListWidget *vertsListWidget;
    QListWidget *halfEdgesListWidget;
    QListWidget *facesListWidget;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QDoubleSpinBox *vertPosXSpinBox;
    QDoubleSpinBox *vertPosYSpinBox;
    QDoubleSpinBox *vertPosZSpinBox;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QDoubleSpinBox *faceBlueSpinBox;
    QLabel *label_10;
    QDoubleSpinBox *faceGreenSpinBox;
    QDoubleSpinBox *faceRedSpinBox;
    QLabel *label_11;
    QTreeWidget *jointTreeWidget;
    QLabel *label_12;
    QFrame *line;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *jointRotateXButton;
    QPushButton *jointRotateYButton;
    QPushButton *jointRotateZButton;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *loadJSONButton;
    QPushButton *meshSkinningButton;
    QWidget *horizontalLayoutWidget_3;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *loadOBJButton;
    QPushButton *subDivButton;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *addVertexButton;
    QPushButton *triangulateButton;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QDoubleSpinBox *jointPosXSpinBox;
    QDoubleSpinBox *jointPosYSpinBox;
    QDoubleSpinBox *jointPosZSpinBox;
    QLabel *label_13;
    QLabel *label_14;
    QLabel *label_15;
    QLabel *label_16;
    QWidget *verticalLayoutWidget_3;
    QVBoxLayout *verticalLayout_3;
    QPushButton *jointRotateNegXButton;
    QPushButton *jointRotateNegYButton;
    QPushButton *jointRotateNegZButton;
    QLabel *label_17;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuHelp;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1310, 526);
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
        actionCamera_Controls = new QAction(MainWindow);
        actionCamera_Controls->setObjectName(QString::fromUtf8("actionCamera_Controls"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        mygl = new MyGL(centralWidget);
        mygl->setObjectName(QString::fromUtf8("mygl"));
        mygl->setGeometry(QRect(11, 11, 618, 471));
        vertsListWidget = new QListWidget(centralWidget);
        vertsListWidget->setObjectName(QString::fromUtf8("vertsListWidget"));
        vertsListWidget->setGeometry(QRect(640, 10, 91, 261));
        halfEdgesListWidget = new QListWidget(centralWidget);
        halfEdgesListWidget->setObjectName(QString::fromUtf8("halfEdgesListWidget"));
        halfEdgesListWidget->setGeometry(QRect(740, 10, 101, 261));
        facesListWidget = new QListWidget(centralWidget);
        facesListWidget->setObjectName(QString::fromUtf8("facesListWidget"));
        facesListWidget->setGeometry(QRect(850, 10, 91, 261));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(640, 280, 111, 16));
        label->setAlignment(Qt::AlignCenter);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(750, 280, 81, 16));
        label_2->setAlignment(Qt::AlignCenter);
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(870, 280, 51, 16));
        label_3->setAlignment(Qt::AlignCenter);
        vertPosXSpinBox = new QDoubleSpinBox(centralWidget);
        vertPosXSpinBox->setObjectName(QString::fromUtf8("vertPosXSpinBox"));
        vertPosXSpinBox->setGeometry(QRect(720, 320, 62, 22));
        vertPosXSpinBox->setMinimum(-99.989999999999995);
        vertPosXSpinBox->setSingleStep(0.500000000000000);
        vertPosYSpinBox = new QDoubleSpinBox(centralWidget);
        vertPosYSpinBox->setObjectName(QString::fromUtf8("vertPosYSpinBox"));
        vertPosYSpinBox->setGeometry(QRect(800, 320, 62, 22));
        vertPosYSpinBox->setMinimum(-99.989999999999995);
        vertPosYSpinBox->setSingleStep(0.500000000000000);
        vertPosZSpinBox = new QDoubleSpinBox(centralWidget);
        vertPosZSpinBox->setObjectName(QString::fromUtf8("vertPosZSpinBox"));
        vertPosZSpinBox->setGeometry(QRect(880, 320, 62, 22));
        vertPosZSpinBox->setMinimum(-99.989999999999995);
        vertPosZSpinBox->setSingleStep(0.500000000000000);
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(640, 320, 71, 21));
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(720, 340, 61, 16));
        label_5->setAlignment(Qt::AlignCenter);
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(800, 340, 61, 16));
        label_6->setAlignment(Qt::AlignCenter);
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(880, 340, 61, 16));
        label_7->setAlignment(Qt::AlignCenter);
        label_8 = new QLabel(centralWidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(880, 390, 61, 16));
        label_8->setAlignment(Qt::AlignCenter);
        label_9 = new QLabel(centralWidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(720, 390, 61, 16));
        label_9->setAlignment(Qt::AlignCenter);
        faceBlueSpinBox = new QDoubleSpinBox(centralWidget);
        faceBlueSpinBox->setObjectName(QString::fromUtf8("faceBlueSpinBox"));
        faceBlueSpinBox->setGeometry(QRect(880, 370, 62, 22));
        faceBlueSpinBox->setMaximum(1.000000000000000);
        faceBlueSpinBox->setSingleStep(0.050000000000000);
        label_10 = new QLabel(centralWidget);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(640, 370, 71, 21));
        faceGreenSpinBox = new QDoubleSpinBox(centralWidget);
        faceGreenSpinBox->setObjectName(QString::fromUtf8("faceGreenSpinBox"));
        faceGreenSpinBox->setGeometry(QRect(800, 370, 62, 22));
        faceGreenSpinBox->setMaximum(1.000000000000000);
        faceGreenSpinBox->setSingleStep(0.050000000000000);
        faceRedSpinBox = new QDoubleSpinBox(centralWidget);
        faceRedSpinBox->setObjectName(QString::fromUtf8("faceRedSpinBox"));
        faceRedSpinBox->setGeometry(QRect(720, 370, 62, 22));
        faceRedSpinBox->setMaximum(1.000000000000000);
        faceRedSpinBox->setSingleStep(0.050000000000000);
        label_11 = new QLabel(centralWidget);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(800, 390, 61, 16));
        label_11->setAlignment(Qt::AlignCenter);
        jointTreeWidget = new QTreeWidget(centralWidget);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        jointTreeWidget->setHeaderItem(__qtreewidgetitem);
        jointTreeWidget->setObjectName(QString::fromUtf8("jointTreeWidget"));
        jointTreeWidget->setGeometry(QRect(980, 10, 301, 261));
        label_12 = new QLabel(centralWidget);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(1080, 280, 54, 12));
        line = new QFrame(centralWidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(950, 10, 20, 471));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);
        verticalLayoutWidget = new QWidget(centralWidget);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(980, 400, 82, 81));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        jointRotateXButton = new QPushButton(verticalLayoutWidget);
        jointRotateXButton->setObjectName(QString::fromUtf8("jointRotateXButton"));

        verticalLayout->addWidget(jointRotateXButton);

        jointRotateYButton = new QPushButton(verticalLayoutWidget);
        jointRotateYButton->setObjectName(QString::fromUtf8("jointRotateYButton"));

        verticalLayout->addWidget(jointRotateYButton);

        jointRotateZButton = new QPushButton(verticalLayoutWidget);
        jointRotateZButton->setObjectName(QString::fromUtf8("jointRotateZButton"));

        verticalLayout->addWidget(jointRotateZButton);

        horizontalLayoutWidget = new QWidget(centralWidget);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(980, 300, 301, 61));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        loadJSONButton = new QPushButton(horizontalLayoutWidget);
        loadJSONButton->setObjectName(QString::fromUtf8("loadJSONButton"));

        horizontalLayout->addWidget(loadJSONButton);

        meshSkinningButton = new QPushButton(horizontalLayoutWidget);
        meshSkinningButton->setObjectName(QString::fromUtf8("meshSkinningButton"));

        horizontalLayout->addWidget(meshSkinningButton);

        horizontalLayoutWidget_3 = new QWidget(centralWidget);
        horizontalLayoutWidget_3->setObjectName(QString::fromUtf8("horizontalLayoutWidget_3"));
        horizontalLayoutWidget_3->setGeometry(QRect(640, 450, 301, 31));
        horizontalLayout_3 = new QHBoxLayout(horizontalLayoutWidget_3);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        loadOBJButton = new QPushButton(horizontalLayoutWidget_3);
        loadOBJButton->setObjectName(QString::fromUtf8("loadOBJButton"));

        horizontalLayout_3->addWidget(loadOBJButton);

        subDivButton = new QPushButton(horizontalLayoutWidget_3);
        subDivButton->setObjectName(QString::fromUtf8("subDivButton"));

        horizontalLayout_3->addWidget(subDivButton);

        horizontalLayoutWidget_2 = new QWidget(centralWidget);
        horizontalLayoutWidget_2->setObjectName(QString::fromUtf8("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(640, 410, 301, 41));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        addVertexButton = new QPushButton(horizontalLayoutWidget_2);
        addVertexButton->setObjectName(QString::fromUtf8("addVertexButton"));

        horizontalLayout_2->addWidget(addVertexButton);

        triangulateButton = new QPushButton(horizontalLayoutWidget_2);
        triangulateButton->setObjectName(QString::fromUtf8("triangulateButton"));

        horizontalLayout_2->addWidget(triangulateButton);

        verticalLayoutWidget_2 = new QWidget(centralWidget);
        verticalLayoutWidget_2->setObjectName(QString::fromUtf8("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(1210, 390, 71, 91));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        jointPosXSpinBox = new QDoubleSpinBox(verticalLayoutWidget_2);
        jointPosXSpinBox->setObjectName(QString::fromUtf8("jointPosXSpinBox"));
        jointPosXSpinBox->setMinimum(-99.500000000000000);
        jointPosXSpinBox->setSingleStep(0.500000000000000);

        verticalLayout_2->addWidget(jointPosXSpinBox);

        jointPosYSpinBox = new QDoubleSpinBox(verticalLayoutWidget_2);
        jointPosYSpinBox->setObjectName(QString::fromUtf8("jointPosYSpinBox"));
        jointPosYSpinBox->setMinimum(-99.900000000000006);
        jointPosYSpinBox->setSingleStep(0.500000000000000);

        verticalLayout_2->addWidget(jointPosYSpinBox);

        jointPosZSpinBox = new QDoubleSpinBox(verticalLayoutWidget_2);
        jointPosZSpinBox->setObjectName(QString::fromUtf8("jointPosZSpinBox"));
        jointPosZSpinBox->setMinimum(-99.500000000000000);
        jointPosZSpinBox->setSingleStep(0.500000000000000);

        verticalLayout_2->addWidget(jointPosZSpinBox);

        label_13 = new QLabel(centralWidget);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(1170, 400, 31, 16));
        label_14 = new QLabel(centralWidget);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(1170, 370, 101, 16));
        label_15 = new QLabel(centralWidget);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(1170, 430, 31, 16));
        label_16 = new QLabel(centralWidget);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setGeometry(QRect(1170, 460, 31, 16));
        verticalLayoutWidget_3 = new QWidget(centralWidget);
        verticalLayoutWidget_3->setObjectName(QString::fromUtf8("verticalLayoutWidget_3"));
        verticalLayoutWidget_3->setGeometry(QRect(1060, 400, 82, 81));
        verticalLayout_3 = new QVBoxLayout(verticalLayoutWidget_3);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        jointRotateNegXButton = new QPushButton(verticalLayoutWidget_3);
        jointRotateNegXButton->setObjectName(QString::fromUtf8("jointRotateNegXButton"));

        verticalLayout_3->addWidget(jointRotateNegXButton);

        jointRotateNegYButton = new QPushButton(verticalLayoutWidget_3);
        jointRotateNegYButton->setObjectName(QString::fromUtf8("jointRotateNegYButton"));

        verticalLayout_3->addWidget(jointRotateNegYButton);

        jointRotateNegZButton = new QPushButton(verticalLayoutWidget_3);
        jointRotateNegZButton->setObjectName(QString::fromUtf8("jointRotateNegZButton"));

        verticalLayout_3->addWidget(jointRotateNegZButton);

        label_17 = new QLabel(centralWidget);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setGeometry(QRect(980, 370, 111, 16));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1310, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionQuit);
        menuHelp->addAction(actionCamera_Controls);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "OpenGLDemo", nullptr));
        actionQuit->setText(QCoreApplication::translate("MainWindow", "Quit", nullptr));
#if QT_CONFIG(shortcut)
        actionQuit->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+Q", nullptr));
#endif // QT_CONFIG(shortcut)
        actionCamera_Controls->setText(QCoreApplication::translate("MainWindow", "Camera Controls", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Vertices", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Half-Edges", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Faces", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Vertex Position", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "X", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Y", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "Z", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "Blue", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "Red", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "Face Color", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "Green", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "Skeleton", nullptr));
        jointRotateXButton->setText(QCoreApplication::translate("MainWindow", "Rotate X", nullptr));
        jointRotateYButton->setText(QCoreApplication::translate("MainWindow", "Rotate Y", nullptr));
        jointRotateZButton->setText(QCoreApplication::translate("MainWindow", "Rotate Z", nullptr));
        loadJSONButton->setText(QCoreApplication::translate("MainWindow", "Load JSON", nullptr));
        meshSkinningButton->setText(QCoreApplication::translate("MainWindow", "Mesh Skinning", nullptr));
        loadOBJButton->setText(QCoreApplication::translate("MainWindow", "Load OBJ", nullptr));
        subDivButton->setText(QCoreApplication::translate("MainWindow", "Subdivision", nullptr));
        addVertexButton->setText(QCoreApplication::translate("MainWindow", "Split Edge", nullptr));
        triangulateButton->setText(QCoreApplication::translate("MainWindow", "Triangulate Quad", nullptr));
        label_13->setText(QCoreApplication::translate("MainWindow", "Pos X", nullptr));
        label_14->setText(QCoreApplication::translate("MainWindow", "Joint Position", nullptr));
        label_15->setText(QCoreApplication::translate("MainWindow", "Pos Y", nullptr));
        label_16->setText(QCoreApplication::translate("MainWindow", "Pos Z", nullptr));
        jointRotateNegXButton->setText(QCoreApplication::translate("MainWindow", "Rotate -X", nullptr));
        jointRotateNegYButton->setText(QCoreApplication::translate("MainWindow", "Rotate -Y", nullptr));
        jointRotateNegZButton->setText(QCoreApplication::translate("MainWindow", "Rotate -Z", nullptr));
        label_17->setText(QCoreApplication::translate("MainWindow", "Joint Rotation", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
        menuHelp->setTitle(QCoreApplication::translate("MainWindow", "Help", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
