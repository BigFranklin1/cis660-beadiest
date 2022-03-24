#ifndef JOINT_H
#define JOINT_H

#include <la.h>
#include <QTreeWidgetItem>

class Joint: public QTreeWidgetItem
{
public:
    static int lastIdJoint;

    QString name;
    Joint* jParent;
    std::vector<Joint*> jChildren;
    glm::vec3 position;
    glm::quat rotation;
    // The inverse of the joint's compound transformation matrix
    // at the time a mesh is bound to the joint's skeleton.
    glm::mat4 bindMatrix;
    int id;
    /* returns a mat4 that represents the concatenation
    of a joint's position and rotation */
    glm::mat4 getLocalTransformation();

    /* returns a mat4 that represents the concatentation
     * of this joint's local transformation with the
     * transformations of its chain of parent joints */
    glm::mat4 getOverallTransformation();

    void addChild(Joint* child);

    Joint();
    Joint(QString name);
};

#endif // JOINT_H
