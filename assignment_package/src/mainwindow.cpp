#include "mainwindow.h"
#include <ui_mainwindow.h>
#include "cameracontrolshelp.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->mygl->setFocus();

    connect(ui->mygl, SIGNAL(sig_sendVertexData(Mesh*)),
            this, SLOT(slot_receiveVertexData(Mesh*)));
    connect(ui->mygl, SIGNAL(sig_sendFaceData(Mesh*)),
            this, SLOT(slot_receiveFaceData(Mesh*)));
    connect(ui->mygl, SIGNAL(sig_sendHalfEdgeData(Mesh*)),
            this, SLOT(slot_receiveHalfEdgeData(Mesh*)));
    connect(ui->mygl, SIGNAL(sig_sendJointData(Skeleton*)),
            this, SLOT(slot_receiveJointData(Skeleton*)));

    connect(ui->vertsListWidget, SIGNAL(itemClicked(QListWidgetItem*)),
            ui->mygl, SLOT(slot_highlightSelectedVertex(QListWidgetItem*)));
    connect(ui->facesListWidget, SIGNAL(itemClicked(QListWidgetItem*)),
            ui->mygl, SLOT(slot_highlightSelectedFace(QListWidgetItem*)));
    connect(ui->halfEdgesListWidget, SIGNAL(itemClicked(QListWidgetItem*)),
            ui->mygl, SLOT(slot_highlightSelectedHalfEdge(QListWidgetItem*)));
    connect(ui->jointTreeWidget, SIGNAL(itemClicked(QTreeWidgetItem*, int)),
            ui->mygl, SLOT(slot_highlightSelectedJoint(QTreeWidgetItem*)));

    // position boxes
    connect(ui->vertPosXSpinBox, SIGNAL(valueChanged(double)),
            ui->mygl, SLOT(slot_vertX(double)));
    connect(ui->vertPosYSpinBox, SIGNAL(valueChanged(double)),
            ui->mygl, SLOT(slot_vertY(double)));
    connect(ui->vertPosZSpinBox, SIGNAL(valueChanged(double)),
            ui->mygl, SLOT(slot_vertZ(double)));

    // color boxes
    connect(ui->faceRedSpinBox, SIGNAL(valueChanged(double)),
            ui->mygl, SLOT(slot_faceR(double)));
    connect(ui->faceGreenSpinBox, SIGNAL(valueChanged(double)),
            ui->mygl, SLOT(slot_faceG(double)));
    connect(ui->faceBlueSpinBox, SIGNAL(valueChanged(double)),
            ui->mygl, SLOT(slot_faceB(double)));

    // topology editing functions
    connect(ui->addVertexButton, SIGNAL(clicked(bool)),
            ui->mygl, SLOT(slot_splitEdge()));
    connect(ui->triangulateButton, SIGNAL(clicked(bool)),
            ui->mygl, SLOT(slot_triangulate()));
    connect(ui->subDivButton, SIGNAL(clicked(bool)),
            ui->mygl, SLOT(slot_subdivision()));

    // load obj file
    connect(ui->loadOBJButton, SIGNAL(clicked(bool)),
            ui->mygl, SLOT(slot_loadOBJ()));
    // load json file
    connect(ui->loadJSONButton, SIGNAL(clicked(bool)),
            ui->mygl, SLOT(slot_loadJSON()));
    // mesh skinning
    connect(ui->meshSkinningButton, SIGNAL(clicked(bool)),
            ui->mygl, SLOT(slot_meshSkinning()));

    // rotate joint
    connect(ui->jointRotateXButton, SIGNAL(clicked(bool)),
            ui->mygl, SLOT(slot_jointRotX()));
    connect(ui->jointRotateNegXButton, SIGNAL(clicked(bool)),
            ui->mygl, SLOT(slot_jointRotNegX()));
    connect(ui->jointRotateYButton, SIGNAL(clicked(bool)),
            ui->mygl, SLOT(slot_jointRotY()));
    connect(ui->jointRotateNegYButton, SIGNAL(clicked(bool)),
            ui->mygl, SLOT(slot_jointRotNegY()));
    connect(ui->jointRotateZButton, SIGNAL(clicked(bool)),
            ui->mygl, SLOT(slot_jointRotZ()));
    connect(ui->jointRotateNegZButton, SIGNAL(clicked(bool)),
            ui->mygl, SLOT(slot_jointRotNegZ()));

    // translate joint
    connect(ui->jointPosXSpinBox, SIGNAL(valueChanged(double)),
            ui->mygl, SLOT(slot_jointPosX(double)));
    connect(ui->jointPosYSpinBox, SIGNAL(valueChanged(double)),
            ui->mygl, SLOT(slot_jointPosY(double)));
    connect(ui->jointPosZSpinBox, SIGNAL(valueChanged(double)),
            ui->mygl, SLOT(slot_jointPosZ(double)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionQuit_triggered()
{
    QApplication::exit();
}

void MainWindow::on_actionCamera_Controls_triggered()
{
    CameraControlsHelp* c = new CameraControlsHelp();
    c->show();
}
void MainWindow::slot_receiveVertexData(Mesh *mesh) {
    for (const uPtr<Vertex> &v : mesh->vertices) {
        ui->vertsListWidget->addItem(v.get());
    }
}

void MainWindow::slot_receiveFaceData(Mesh *mesh) {
    for (const uPtr<Face> &f : mesh->faces) {
        ui->facesListWidget->addItem(f.get());
    }
}

void MainWindow::slot_receiveHalfEdgeData(Mesh *mesh) {
    for (const uPtr<HalfEdge> &h : mesh->halfEdges) {
        ui->halfEdgesListWidget->addItem(h.get());
    }
}

void MainWindow::slot_receiveJointData(Skeleton *sk){
//    ui->jointTreeWidget->clear();
    for (const uPtr<Joint> &j : sk->joints) {
        ui->jointTreeWidget->addTopLevelItem(j.get());
    }
}
