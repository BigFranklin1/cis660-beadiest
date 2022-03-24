#ifndef MYGL_H
#define MYGL_H

#include <openglcontext.h>
#include <utils.h>
#include <shaderprogram.h>
#include <scene/squareplane.h>
#include "camera.h"
#include <mesh.h>
#include <skeleton.h>
//#include <joint.h>

#include <vertexdisplay.h>
#include <facedisplay.h>
#include <halfedgedisplay.h>

#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>
#include <QFileDialog>
#include <QMessageBox>
#include <QJsonObject>

class MyGL
    : public OpenGLContext
{
    Q_OBJECT
private:
    SquarePlane m_geomSquare;// The instance of a unit cylinder we can use to render any cylinder
    ShaderProgram m_progLambert;// A shader program that uses lambertian reflection
    ShaderProgram m_progFlat;// A shader program that uses "flat" reflection (no shadowing at all)
    ShaderProgram m_progSkeleton;
    GLuint vao; // A handle for our vertex array object. This will store the VBOs created in our geometry classes.
                // Don't worry too much about this. Just know it is necessary in order to render geometry.


    Camera m_glCamera;


public:
    explicit MyGL(QWidget *parent = nullptr);
    ~MyGL();

    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    Mesh m_mesh;
    VertexDisplay m_vertDisplay;
    FaceDisplay m_faceDisplay;
    HalfEdgeDisplay m_halfEdgeDisplay;
    Skeleton m_skeleton;
    QListWidgetItem* m_selected;
    QTreeWidgetItem* m_selected_tree;


protected:
    void keyPressEvent(QKeyEvent* e);
public slots:
    void slot_highlightSelectedVertex(QListWidgetItem* v);
    void slot_highlightSelectedFace(QListWidgetItem* f);
    void slot_highlightSelectedHalfEdge(QListWidgetItem* he);
    void slot_highlightSelectedJoint(QTreeWidgetItem* joint);

    void slot_vertX(double x);
    void slot_vertY(double y);
    void slot_vertZ(double z);

    void slot_faceR(double r);
    void slot_faceG(double g);
    void slot_faceB(double b);

    void slot_splitEdge();
    void slot_triangulate();
    void slot_subdivision();

    void slot_loadOBJ();
    void slot_loadJSON();
    Joint* loadJSONHelper(QJsonObject parent);

    void slot_meshSkinning();

    void slot_jointRotX();
    void slot_jointRotY();
    void slot_jointRotZ();
    void slot_jointRotNegX();
    void slot_jointRotNegY();
    void slot_jointRotNegZ();
    void slot_jointPosX(double v);
    void slot_jointPosY(double v);
    void slot_jointPosZ(double v);

signals:
    void sig_sendVertexData(Mesh* mesh);
    void sig_sendFaceData(Mesh* mesh);
    void sig_sendHalfEdgeData(Mesh* mesh);
    void sig_sendJointData(Skeleton* skeleton);

};


#endif // MYGL_H
