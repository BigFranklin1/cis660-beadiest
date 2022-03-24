#ifndef HALFEDGE_H
#define HALFEDGE_H

#include <QListWidget>
#include <vertex.h>
#include <face.h>
#include <la.h>

class Vertex;
class Face;

static int lastHalfEdge;

class HalfEdge : public QListWidgetItem
{
public:
    // A pointer to the next HalfEdge in the loop of HalfEdges that lie on this HalfEdge's Face
    HalfEdge* nextHE;

    // A pointer to the HalfEdge that lies parallel to this HalfEdge and which travels
    // in the opposite direction and is part of an adjacent Face, i.e. this HalfEdge's symmetrical HalfEdge
    HalfEdge* symmHE;

    // A pointer to the Face on which this HalfEdge lies
    Face* face;

    // A pointer to the Vertex between this HalfEdge and its next HalfEdge
    Vertex* vertex;

    // A unique integer to identify the HalfEdge in menus and while debugging
    int id;

    QString name;

    HalfEdge();
    HalfEdge(const HalfEdge &halfEdge);

};

#endif // HALFEDGE_H
