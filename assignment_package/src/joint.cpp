#include "joint.h"

int Joint::lastIdJoint = 0;

Joint::Joint():
    QTreeWidgetItem(),
    name(),
    jParent(nullptr),
    jChildren(),
    position(glm::vec4()),
    rotation(glm::quat()),
    bindMatrix(glm::mat4()),
    id(lastIdJoint++)
{
    this->QTreeWidgetItem::setText(0, this->name);
}
Joint::Joint(QString n):
    QTreeWidgetItem(),
    name(n),
    jParent(nullptr),
    jChildren(),
    position(glm::vec4()),
    rotation(glm::quat()),
    bindMatrix(glm::mat4()),
    id(lastIdJoint++)
{
    this->QTreeWidgetItem::setText(0, this->name);
}
glm::mat4 Joint::getLocalTransformation() {
    glm::mat4 t = glm::mat4(glm::vec4(1, 0, 0, 0),
                            glm::vec4(0, 1, 0, 0),
                            glm::vec4(0, 0, 1, 0),
                            glm::vec4(position, 1));

    glm::mat4 r = glm::mat4_cast(rotation);

    return t * r;
}

glm::mat4 Joint::getOverallTransformation() {
    glm::mat4 overall;
    if (jParent) {
        overall = jParent->getOverallTransformation() * getLocalTransformation();
    }
    overall = getLocalTransformation();
    return overall;
}

void Joint::addChild(Joint *child){
    QTreeWidgetItem::addChild(child);
    jChildren.push_back(child);
    child->jParent = this;
}

