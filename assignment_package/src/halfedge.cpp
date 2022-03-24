#include "halfedge.h"

HalfEdge::HalfEdge()
    :QListWidgetItem(),
      nextHE(nullptr), symmHE(nullptr),
      face(nullptr), vertex(nullptr),
      id(0), name("he ")

{
    id = lastHalfEdge++;
    name.append(QString::number(id));
    this->setText(name);
}

//Vertex::Vertex(const Vertex &vertex)
//    :QListWidgetItem(), pos(vertex.pos),
//      halfEdge(vertex.halfEdge),
//      id(vertex.id), name(vertex.name)

//{}
