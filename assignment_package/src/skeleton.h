#ifndef SKELETON_H
#define SKELETON_H

#include <joint.h>
#include <drawable.h>
#include <smartpointerhelp.h>
#include <glm/gtx/rotate_vector.hpp>

class Skeleton: public Drawable
{
public:
    std::vector <uPtr<Joint>> joints;

    int representedJoint;

    void create() override;

    void updateJoint(Joint*);


    std::vector<glm::mat4> setTranslateMatrix();
    void setBindMatrix();


    GLenum drawMode() override;

    Skeleton(OpenGLContext* context);
    ~Skeleton();
};

#endif // SKELETON_H
