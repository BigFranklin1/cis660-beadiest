#include "face.h"

Face::Face()
    :QListWidgetItem(), halfEdge(nullptr),
      color(glm::vec3()),
      id(0), name("f ")

{
    id = lastIdFace++;
    name.append(QString::number(id));
    this->setText(name);
}

void Face::setColor(){
    this->color = glm::vec3(rand() / (float)RAND_MAX,
                            rand() / (float)RAND_MAX,
                            rand() / (float)RAND_MAX);
}

