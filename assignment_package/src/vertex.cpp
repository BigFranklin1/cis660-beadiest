#include "vertex.h"

Vertex::Vertex()
    :QListWidgetItem(), pos(glm::vec3()), halfEdge(nullptr),
      id(0), name("v "), weights()

{
    id = lastIdVertex++;
    name.append(QString::number(id));
    this->setText(name);
}

