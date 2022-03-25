#ifndef VERTEX_H
#define VERTEX_H

#include <halfedge.h>
#include <face.h>
#include <la.h>
#include <QListWidgetItem>

static int lastIdVertex;
class HalfEdge;
class Vertex: public QListWidgetItem
{
public:
    // A vec3 for storing its position
    glm::vec3 pos;

    // A pointer to one of the HalfEdges that points to this Vertex
    HalfEdge* halfEdge;

    // A unique integer to identify the Vertex in menus and while debugging
    int id;

    QString name;

    // influences <id, strength>
    std::vector<std::pair<int, float>> weights;

    // each vertex stores pointers to its adjacent edges
    std::unordered_set<HalfEdge*> adjacentEdges;

    Vertex();
    Vertex(const Vertex &vertex);

};

#endif // VERTEX_H
