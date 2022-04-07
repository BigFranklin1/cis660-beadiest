#ifndef FACE_H
#define FACE_H

#include <vertex.h>
#include <halfedge.h>
#include <QListWidget>
#include <la.h>
static int lastIdFace;
class HalfEdge;
class Vertex;
class Face: public QListWidgetItem
{
public:
    // A pointer to one of the HalfEdges that lies on this Face
    HalfEdge* halfEdge;

    // A vec3 to represent this Face's color as an RGB value
    glm::vec3 color;

    glm::vec3 normal;

    // A unique integer to identify the Face in menus and while debugging
    int id;

    // each face stores pointers to the three edges and vertices that define it.
    std::unordered_set<HalfEdge*> edges;
    std::unordered_set<Vertex*> vertices;

    QString name;

    void setColor();

    Face();
};

#endif // FACE_H
