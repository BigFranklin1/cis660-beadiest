#include "mygl.h"
#include <la.h>

#include <iostream>
#include <QApplication>
#include <QKeyEvent>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QFileDialog>

MyGL::MyGL(QWidget *parent)
    : OpenGLContext(parent),
      m_geomSquare(this),
      m_progLambert(this), m_progFlat(this), m_progSkeleton(this),
      m_glCamera(),
      m_mesh(this),
      m_vertDisplay(this),
      m_faceDisplay(this),
      m_halfEdgeDisplay(this),
      m_skeleton(this),
      m_selected(nullptr),
      m_selected_tree(nullptr)
{
    setFocusPolicy(Qt::StrongFocus);
}

MyGL::~MyGL()
{
    makeCurrent();
    glDeleteVertexArrays(1, &vao);
    m_geomSquare.destroy();
    m_skeleton.destroy();
    m_mesh.destroy();
}

void MyGL::initializeGL()
{
    // Create an OpenGL context using Qt's QOpenGLFunctions_3_2_Core class
    // If you were programming in a non-Qt context you might use GLEW (GL Extension Wrangler)instead
    initializeOpenGLFunctions();
    // Print out some information about the current OpenGL context
    debugContextVersion();

    // Set a few settings/modes in OpenGL rendering
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POLYGON_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
    // Set the size with which points should be rendered
    glPointSize(5);
    // Set the color with `which the screen is filled at the start of each render call.
    glClearColor(0.5, 0.5, 0.5, 1);

    printGLErrorLog();

    // Create a Vertex Attribute Object
    glGenVertexArrays(1, &vao);

    m_mesh.buildCubeMesh();
    m_mesh.create();

    // Create and set up the diffuse shader
    m_progLambert.create(":/glsl/lambert.vert.glsl", ":/glsl/lambert.frag.glsl");
    // Create and set up the flat lighting shader
    m_progFlat.create(":/glsl/flat.vert.glsl", ":/glsl/flat.frag.glsl");
    // Create and set up the skeleton shader
    m_progSkeleton.create(":/glsl/skeleton.vert.glsl", ":/glsl/skeleton.frag.glsl");

    // We have to have a VAO bound in OpenGL 3.2 Core. But if we're not
    // using multiple VAOs, we can just bind one once.
    glBindVertexArray(vao);

    // added: emit signals
    emit sig_sendVertexData(&m_mesh);
    emit sig_sendFaceData(&m_mesh);
    emit sig_sendHalfEdgeData(&m_mesh);
    emit sig_sendJointData(&m_skeleton);

}

void MyGL::resizeGL(int w, int h)
{
    //This code sets the concatenated view and perspective projection matrices used for
    //our scene's camera view.
    m_glCamera = Camera(w, h);
    glm::mat4 viewproj = m_glCamera.getViewProj();

    // Upload the view-projection matrix to our shaders (i.e. onto the graphics card)

    m_progLambert.setViewProjMatrix(viewproj);
    m_progFlat.setViewProjMatrix(viewproj);
    m_progSkeleton.setViewProjMatrix(viewproj);

    printGLErrorLog();
}

//This function is called by Qt any time your GL window is supposed to update
//For example, when the function update() is called, paintGL is called implicitly.
void MyGL::paintGL()
{
    // Clear the screen so that we only see newly drawn images
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_progFlat.setViewProjMatrix(m_glCamera.getViewProj());
    m_progLambert.setViewProjMatrix(m_glCamera.getViewProj());
    m_progLambert.setCamPos(m_glCamera.eye);
    m_progFlat.setModelMatrix(glm::mat4(1.f));
    //Create a model matrix. This one rotates the square by PI/4 radians then translates it by <-2,0,0>.
    //Note that we have to transpose the model matrix before passing it to the shader
    //This is because OpenGL expects column-major matrices, but you've
    //implemented row-major matrices.
    glm::mat4 model = glm::translate(glm::mat4(1.0f),
                                     glm::vec3(-2,0,0)) * glm::rotate(glm::mat4(),
                                     0.25f * 3.14159f,
                                     glm::vec3(0,1,0));
    //Send the geometry's transformation matrix to the shader
    m_progLambert.setModelMatrix(glm::mat4());
    //Draw the example sphere using our lambert shader
    m_progLambert.draw(m_mesh);

    m_progSkeleton.setViewProjMatrix(m_glCamera.getViewProj());
    m_progSkeleton.setModelMatrix(model);

    // visual debugging tool
    Vertex* vertex = dynamic_cast<Vertex*>(m_selected);
    Face* face = dynamic_cast<Face*>(m_selected);
    HalfEdge* halfEdge = dynamic_cast<HalfEdge*>(m_selected);
    Skeleton* skeleton = dynamic_cast<Skeleton*>(m_selected);

    // check whether a skeleton is bound
    if (!m_mesh.vertices[0]->weights.empty()) {
        m_progSkeleton.draw(m_mesh);
        m_progSkeleton.draw(m_skeleton);
    } else {
        m_progFlat.draw(m_mesh);
    }
    printGLErrorLog();

    glDisable(GL_DEPTH_TEST);
//    m_vertDisplay.create();
//    m_progFlat.draw(m_vertDisplay);
//    m_faceDisplay.create();
//    m_progFlat.draw(m_faceDisplay);
//    m_halfEdgeDisplay.create();
//    m_progFlat.draw(m_halfEdgeDisplay);
    m_skeleton.create();
    m_progFlat.draw(m_skeleton);
    if (vertex) {
        m_vertDisplay.create();
        m_progFlat.draw(m_vertDisplay);
    } else if (face) {
        m_faceDisplay.create();
        m_progFlat.draw(m_faceDisplay);
    } else if (halfEdge) {
        m_halfEdgeDisplay.create();
        m_progFlat.draw(m_halfEdgeDisplay);
    }
    glEnable(GL_DEPTH_TEST);
}
void MyGL::slot_highlightSelectedVertex(QListWidgetItem *v) {
    if (v) {
        m_selected = v;
        Vertex* vertex = dynamic_cast<Vertex*>(v);

        m_vertDisplay.destroy();

        if (vertex) {
            m_vertDisplay.updateVertex(vertex);
        }
        update();
    }
}

void MyGL::slot_highlightSelectedFace(QListWidgetItem *f) {
    if (f) {
        m_selected = f;
        Face* face = dynamic_cast<Face*>(f);

        m_faceDisplay.destroy();

        if (face) {
            m_faceDisplay.updateFace(face);
        }
        update();
    }
}

void MyGL::slot_highlightSelectedHalfEdge(QListWidgetItem *he) {
    if (he) {
        m_selected = he;
        HalfEdge* halfEdge = dynamic_cast<HalfEdge*>(he);

        m_halfEdgeDisplay.destroy();

        if (halfEdge) {
            m_halfEdgeDisplay.updateHalfEdge(halfEdge);
        }
        update();
    }
}
void MyGL::slot_highlightSelectedJoint(QTreeWidgetItem *j) {
    if (j) {
        Joint* joint = dynamic_cast<Joint*>(j);

        m_skeleton.destroy();

        if (joint) {
            m_skeleton.updateJoint(joint);
        }
        update();
    }
}

void MyGL::slot_vertX(double x){
    if(m_selected){
        Vertex* vertex = dynamic_cast<Vertex*>(m_selected);
        if (vertex) {
            vertex->pos.x = x;
            m_mesh.destroy();
            m_mesh.create();
            update();
        }
    }
};
void MyGL::slot_vertY(double y){
    if(m_selected){
        Vertex* vertex = dynamic_cast<Vertex*>(m_selected);
        if (vertex) {
            vertex->pos.y = y;
            m_mesh.destroy();
            m_mesh.create();
            update();
        }
    }
};
void MyGL::slot_vertZ(double z){
    if(m_selected){
        Vertex* vertex = dynamic_cast<Vertex*>(m_selected);
        if (vertex) {
            vertex->pos.z = z;
            m_mesh.destroy();
            m_mesh.create();
            update();
        }
    }
};
void MyGL::slot_faceR(double r){
    if(m_selected){
        Face* f = dynamic_cast<Face*>(m_selected);
        if (f) {
            f->color.r = r;
            m_mesh.destroy();
            m_mesh.create();
            update();
        }
    }
};
void MyGL::slot_faceG(double g){
    if(m_selected){
        Face* f = dynamic_cast<Face*>(m_selected);
        if (f) {
            f->color.g = g;
            m_mesh.destroy();
            m_mesh.create();
            update();
        }
    }
};
void MyGL::slot_faceB(double b){
    if(m_selected){
        Face* f = dynamic_cast<Face*>(m_selected);
        if (f) {
            f->color.b = b;
            m_mesh.destroy();
            m_mesh.create();
            update();
        }
    }
};
void MyGL::slot_splitEdge(){
    if(m_selected){
        HalfEdge* he = dynamic_cast<HalfEdge*>(m_selected);
        m_mesh.splitEdge(he);
        emit sig_sendHalfEdgeData(&m_mesh);
        emit sig_sendVertexData(&m_mesh);
    }

    m_mesh.destroy();
    m_mesh.create();
    update();
}
void MyGL::slot_triangulate(){
    if(m_selected){
        Face* f = dynamic_cast<Face*>(m_selected);
        m_mesh.triangulateFace(f);

        emit sig_sendHalfEdgeData(&m_mesh);
        emit sig_sendFaceData(&m_mesh);

    }

    m_mesh.destroy();
    m_mesh.create();
    update();
}
void MyGL::slot_subdivision(){

    //m_mesh.subdivision();
    m_mesh.postprocess();
//    emit sig_sendVertexData(&m_mesh);
//    emit sig_sendHalfEdgeData(&m_mesh);
//    emit sig_sendFaceData(&m_mesh);
    m_mesh.destroy();
    m_mesh.create();
    update();
}
void MyGL::slot_toHexa(){

    m_mesh.triToHexa();
    emit sig_sendVertexData(&m_mesh);
    emit sig_sendHalfEdgeData(&m_mesh);
    emit sig_sendFaceData(&m_mesh);
    m_mesh.destroy();
    m_mesh.create();
    update();
}

void MyGL::slot_loadOBJ(){
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open OBJ File"), QDir::currentPath().append(QString("../../obj_files")), tr("OBJ Files (*.obj)"));
    QFile file(fileName);

    std::map<std::pair<int, int>, HalfEdge*> mapSymm;

    if(file.exists()){
        m_mesh.vertices.clear();
        m_mesh.faces.clear();
        m_mesh.halfEdges.clear();
        if(!file.open(QIODevice::ReadOnly)) {
            QMessageBox::information(0, "error", file.errorString());
        }

        QTextStream in(&file);

        while (!in.atEnd()) {
           QString line = in.readLine();
           QStringList elementList = line.split(" ");

           // vertex
           if (elementList.at(0) == "v") {
               uPtr<Vertex> vertex = mkU<Vertex>();
               glm::vec3 position = glm::vec3(elementList[1].toFloat(),
                                              elementList[2].toFloat(),
                                              elementList[3].toFloat());
               vertex->pos = position;
               m_mesh.vertices.push_back(std::move(vertex));

           // face
           } else if (elementList.at(0) == "f") {
               // initialize faces and edges
               uPtr<Face> f = mkU<Face>();
               f->setColor();
               int idxLastItem = elementList.length() - 1;

               for (int i = 1; i <= idxLastItem; i++) {
                   QString element = elementList[i];
                   uPtr<HalfEdge> he = mkU<HalfEdge>();

                   // format: f pos/uv/norm
                   int vertexIdx = element.split("/")[0].toInt() - 1; // the file starts from 1

                   he->face = f.get();
                   f->halfEdge = he.get();
                   he->vertex = m_mesh.vertices[vertexIdx].get();
                   m_mesh.vertices[vertexIdx]->halfEdge = he.get();

                   m_mesh.halfEdges.push_back(std::move(he));
               }

               m_mesh.faces.push_back(std::move(f));

               int heSize = m_mesh.halfEdges.size();

               for (int i = 1; i <= idxLastItem; i++) {
                   int elementListLength = elementList.size() - i;
                   int edgesSize = heSize - elementListLength;

                   if (i != idxLastItem) {
                       HalfEdge *theNextHE = m_mesh.halfEdges[edgesSize + 1].get();
                       m_mesh.halfEdges[edgesSize]->nextHE = theNextHE;
                   }

                   HalfEdge *lastHE = m_mesh.halfEdges[heSize - elementList.size() + 1].get();
                   m_mesh.halfEdges[heSize - 1]->nextHE = lastHE;

                   // set symm he
                   HalfEdge *he = m_mesh.halfEdges[edgesSize].get();

                   QStringList curr = elementList[i].split("/");
                   QStringList prev;

                   if (i == 1) {
                       prev = elementList[idxLastItem].split("/");
                   }
                   else{
                       prev = elementList[i - 1].split("/");
                   }

                   std::pair pair = {curr[0].toInt(), prev[0].toInt()};
                   std::pair pairSymm = {prev[0].toInt(), curr[0].toInt()};
                   // only implement following block when pairSymm is found
                   if (mapSymm.find(pairSymm) != mapSymm.end()) {
                       HalfEdge *he_symm = mapSymm.find(pairSymm)->second;
                       he->symmHE = he_symm;
                       he_symm->symmHE = he;
                   } else {
                       // if there is no pairSymm, insert "pair"
                       mapSymm.insert({pair, he});
                   }
               }
           }
        }

        file.close();
        m_mesh.destroy();
        m_mesh.create();


        emit sig_sendFaceData(&m_mesh);
        emit sig_sendVertexData(&m_mesh);
        emit sig_sendHalfEdgeData(&m_mesh);

        update();

    }

};
void MyGL::slot_loadJSON(){
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open JSON File"), QDir::currentPath().append(QString("../../json_files")), tr("JSON Files (*.json)"));
    QFile file(fileName);


    if (file.exists()) {
        Joint::lastIdJoint = 0;
        m_skeleton.representedJoint = -1;
        m_skeleton.joints.clear();

        for (uPtr<Vertex> &v : m_mesh.vertices) {
            v->weights.clear();
        }

        if(!file.open(QIODevice::ReadOnly)) {
            QMessageBox::information(0, "error", file.errorString());
        }

        QString val = file.readAll();
        file.close();
        QJsonDocument doc = QJsonDocument::fromJson(val.toUtf8());
        QJsonObject root = doc.object()["root"].toObject();

        loadJSONHelper(root);

    }
    file.close();

    m_skeleton.destroy();
    m_skeleton.create();

    emit sig_sendJointData(&m_skeleton);

    update();

};

Joint* MyGL::loadJSONHelper(QJsonObject parent){
    glm::vec3 pos = glm::vec3(parent["pos"].toArray()[0].toDouble(),
            parent["pos"].toArray()[1].toDouble(),
            parent["pos"].toArray()[2].toDouble()
            );
    QJsonArray rotation = parent["rot"].toArray();
    QJsonArray children = parent["children"].toArray();

    double half = rotation[0].toDouble() / 2;
    glm::quat rot(cos(glm::radians(half)),
                  sin(glm::radians(half)) * rotation[1].toDouble(),
                  sin(glm::radians(half)) * rotation[2].toDouble(),
                  sin(glm::radians(half)) * rotation[3].toDouble());
    uPtr<Joint> j = mkU<Joint>(parent["name"].toString());
    j->position = pos;
    j->rotation = rot;

    Joint* joint = j.get();
    m_skeleton.joints.push_back(std::move(j));
    if(!children.isEmpty()){
        for(QJsonValueRef child: children){
            joint->addChild(loadJSONHelper(child.toObject()));
        }
    }
    return joint;

}

void MyGL::slot_meshSkinning(){
    m_skeleton.setBindMatrix();
    m_progSkeleton.setTransMatrix(m_skeleton.setTranslateMatrix());

    //    For all vertices connected to the original set
    //    of vertices, set their influence for this joint as a
    //    function of their distance from vertices with an
    //    influence weight > 0
    for (uPtr<Vertex> &v : m_mesh.vertices) {
        Joint* joint1 = nullptr;
        Joint* joint2 = nullptr;
        float j1Dist = 0;
        float j2Dist = 0;

        for (uPtr<Joint> &j : m_skeleton.joints) {
            glm::vec4 jointPos = j->getOverallTransformation() * glm::vec4(0, 0, 0, 1);
            float distJ2V = glm::distance(glm::vec4(v->pos, 1), jointPos);

            if (!joint1) {
                joint1 = j.get();
                j1Dist = distJ2V;
            } else if (j1Dist > distJ2V) {
                joint2 = joint1;
                j2Dist = j1Dist;
                joint1 = j.get();
                j1Dist = distJ2V;
            }
            joint2 = j.get();
            j2Dist = distJ2V;
        }

        float j1Weight = j1Dist / (j1Dist + j2Dist);
        float j2Weight = j2Dist / (j1Dist + j2Dist);

        v->weights.push_back({joint1->id, j1Weight});
        v->weights.push_back({joint2->id, j2Weight});
    }
    // update matrices to the shader
    std::vector<glm::mat4> bind;
    std::vector<glm::mat4> trans;

    for (uPtr<Joint> &j : m_skeleton.joints) {
        bind.push_back(j->bindMatrix);
        trans.push_back(j->getOverallTransformation());
    }
    m_progSkeleton.setBindMatrix(bind);
    m_progSkeleton.setTransMatrix(trans);

    m_mesh.destroy();
    m_mesh.create();

    m_skeleton.destroy();
    m_skeleton.create();

    update();
}
void MyGL::slot_jointRotX(){
    glm::vec3 axisX = glm::vec3(1, 0, 0);
    int selectedJoint = m_skeleton.representedJoint;
    if (selectedJoint != -1) {
        Joint* joint = dynamic_cast<Joint*>(m_skeleton.joints[selectedJoint].get());

        if (joint) {
            joint->rotation *= glm::rotate(glm::quat(), glm::radians(5.f), axisX);
            m_progSkeleton.setTransMatrix(m_skeleton.setTranslateMatrix());

            m_skeleton.destroy();
            m_skeleton.create();
            m_mesh.destroy();
            m_mesh.create();

            update();
        }
    }
}

void MyGL::slot_jointRotY(){
    glm::vec3 axisY = glm::vec3(0, 1, 0);
    int selectedJoint = m_skeleton.representedJoint;
    if (selectedJoint != -1) {
        Joint* joint = dynamic_cast<Joint*>(m_skeleton.joints[selectedJoint].get());

        if (joint) {
            joint->rotation *= glm::rotate(glm::quat(), glm::radians(5.f), axisY);
            m_progSkeleton.setTransMatrix(m_skeleton.setTranslateMatrix());

            m_skeleton.destroy();
            m_skeleton.create();
            m_mesh.destroy();
            m_mesh.create();

            update();
        }
    }
}
void MyGL::slot_jointRotZ(){
    glm::vec3 axisZ = glm::vec3(0, 0, 1);
    int selectedJoint = m_skeleton.representedJoint;
    if (selectedJoint != -1) {
        Joint* joint = dynamic_cast<Joint*>(m_skeleton.joints[selectedJoint].get());

        if (joint) {
            joint->rotation *= glm::rotate(glm::quat(), glm::radians(5.f), axisZ);
            m_progSkeleton.setTransMatrix(m_skeleton.setTranslateMatrix());

            m_skeleton.destroy();
            m_skeleton.create();
            m_mesh.destroy();
            m_mesh.create();

            update();
        }
    }
}
void MyGL::slot_jointRotNegX(){
    glm::vec3 axisX = glm::vec3(1, 0, 0);
    int selectedJoint = m_skeleton.representedJoint;
    if (selectedJoint != -1) {
        Joint* joint = dynamic_cast<Joint*>(m_skeleton.joints[selectedJoint].get());

        if (joint) {
            joint->rotation *= glm::rotate(glm::quat(), glm::radians(-5.f), axisX);
            m_progSkeleton.setTransMatrix(m_skeleton.setTranslateMatrix());

            m_skeleton.destroy();
            m_skeleton.create();
            m_mesh.destroy();
            m_mesh.create();

            update();
        }
    }
}

void MyGL::slot_jointRotNegY(){
    glm::vec3 axisY = glm::vec3(0, 1, 0);
    int selectedJoint = m_skeleton.representedJoint;
    if (selectedJoint != -1) {
        Joint* joint = dynamic_cast<Joint*>(m_skeleton.joints[selectedJoint].get());

        if (joint) {
            joint->rotation *= glm::rotate(glm::quat(), glm::radians(-5.f), axisY);
            m_progSkeleton.setTransMatrix(m_skeleton.setTranslateMatrix());

            m_skeleton.destroy();
            m_skeleton.create();
            m_mesh.destroy();
            m_mesh.create();

            update();
        }
    }
}
void MyGL::slot_jointRotNegZ(){
    glm::vec3 axisZ = glm::vec3(0, 0, 1);
    int selectedJoint = m_skeleton.representedJoint;
    if (selectedJoint != -1) {
        Joint* joint = dynamic_cast<Joint*>(m_skeleton.joints[selectedJoint].get());

        if (joint) {
            joint->rotation *= glm::rotate(glm::quat(), glm::radians(-5.f), axisZ);
            m_progSkeleton.setTransMatrix(m_skeleton.setTranslateMatrix());

            m_skeleton.destroy();
            m_skeleton.create();
            m_mesh.destroy();
            m_mesh.create();

            update();
        }
    }
}

void MyGL::slot_jointPosX(double value){
    int selectedJoint = m_skeleton.representedJoint;
    if (selectedJoint != -1) {
        Joint* joint = dynamic_cast<Joint*>(m_skeleton.joints[selectedJoint].get());

        if (joint) {
            joint->position.x = value;
            m_progSkeleton.setTransMatrix(m_skeleton.setTranslateMatrix());

            m_skeleton.destroy();
            m_skeleton.create();

            m_mesh.destroy();
            m_mesh.create();
            update();
        }
    }
}
void MyGL::slot_jointPosY(double value){
    int selectedJoint = m_skeleton.representedJoint;
    if (selectedJoint != -1) {
        Joint* joint = dynamic_cast<Joint*>(m_skeleton.joints[selectedJoint].get());

        if (joint) {
            joint->position.y = value;
            m_progSkeleton.setTransMatrix(m_skeleton.setTranslateMatrix());

            m_skeleton.destroy();
            m_skeleton.create();

            m_mesh.destroy();
            m_mesh.create();
            update();
        }
    }
}
void MyGL::slot_jointPosZ(double value){
    int selectedJoint = m_skeleton.representedJoint;
    if (selectedJoint != -1) {
        Joint* joint = dynamic_cast<Joint*>(m_skeleton.joints[selectedJoint].get());

        if (joint) {
            joint->position.z = value;
            m_progSkeleton.setTransMatrix(m_skeleton.setTranslateMatrix());

            m_skeleton.destroy();
            m_skeleton.create();

            m_mesh.destroy();
            m_mesh.create();
            update();
        }
    }
}



void MyGL::keyPressEvent(QKeyEvent *e)
{
    float amount = 2.0f;
    if(e->modifiers() & Qt::ShiftModifier){
        amount = 10.0f;
    }
    // http://doc.qt.io/qt-5/qt.html#Key-enum
    // This could all be much more efficient if a switch
    // statement were used
    if (e->key() == Qt::Key_Escape) {
        QApplication::quit();
    } else if (e->key() == Qt::Key_Right) {
        m_glCamera.RotateAboutUp(-amount);
    } else if (e->key() == Qt::Key_Left) {
        m_glCamera.RotateAboutUp(amount);
    } else if (e->key() == Qt::Key_Up) {
        m_glCamera.RotateAboutRight(-amount);
    } else if (e->key() == Qt::Key_Down) {
        m_glCamera.RotateAboutRight(amount);
    } else if (e->key() == Qt::Key_1) {
        m_glCamera.fovy += amount;
    } else if (e->key() == Qt::Key_2) {
        m_glCamera.fovy -= amount;
    } else if (e->key() == Qt::Key_W) {
        m_glCamera.TranslateAlongLook(amount);
    } else if (e->key() == Qt::Key_S) {
        m_glCamera.TranslateAlongLook(-amount);
    } else if (e->key() == Qt::Key_D) {
        m_glCamera.TranslateAlongRight(amount);
    } else if (e->key() == Qt::Key_A) {
        m_glCamera.TranslateAlongRight(-amount);
    } else if (e->key() == Qt::Key_Q) {
        m_glCamera.TranslateAlongUp(-amount);
    } else if (e->key() == Qt::Key_E) {
        m_glCamera.TranslateAlongUp(amount);
    } else if (e->key() == Qt::Key_R) {
        m_glCamera = Camera(this->width(), this->height());
    } else if (e->key() == Qt::Key_N) {
        HalfEdge* he = dynamic_cast<HalfEdge*>(m_selected);
        if (he) {
            slot_highlightSelectedHalfEdge(he-> nextHE);
        }
    } else if (e->key() == Qt::Key_M) {
        HalfEdge* he = dynamic_cast<HalfEdge*>(m_selected);
        if (he) {
            slot_highlightSelectedHalfEdge(he-> symmHE);
        }
    } else if (e->key() == Qt::Key_F) {
        HalfEdge* he = dynamic_cast<HalfEdge*>(m_selected);
        if (he) {
            slot_highlightSelectedFace(he-> face);
        }
    } else if (e->key() == Qt::Key_V) {
        HalfEdge* he = dynamic_cast<HalfEdge*>(m_selected);
        if (he) {
            slot_highlightSelectedVertex(he->vertex);
        }
    } else if (e->key() == Qt::Key_H) {
        Vertex* v = dynamic_cast<Vertex*>(m_selected);
        if (v) {
            slot_highlightSelectedHalfEdge(v-> halfEdge);
        }
    } else if (e->key() == (Qt::Key_H & Qt::Key_Shift)) {
        HalfEdge* he = dynamic_cast<HalfEdge*>(m_selected);
        if (he) {
            slot_highlightSelectedFace(he-> face);
        }
    }
    m_glCamera.RecomputeAttributes();
    update();  // Calls paintGL, among other things
}
