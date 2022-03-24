#ifndef FACE_H
#define FACE_H

#include <vertex.h>
#include <halfedge.h>
#include <QListWidget>
#include <la.h>
static int lastIdFace;
class HalfEdge;

class Face: public QListWidgetItem
{
public:
    // A pointer to one of the HalfEdges that lies on this Face
    HalfEdge* halfEdge;

    // A vec3 to represent this Face's color as an RGB value
    glm::vec3 color;

    // A unique integer to identify the Face in menus and while debugging
    int id;

    QString name;

    void setColor();

    Face();
};

#endif // FACE_H
