#include "skeleton.h"

Skeleton::Skeleton(OpenGLContext *context)
    : Drawable(context), representedJoint(-1) {}

Skeleton::~Skeleton() {}

void Skeleton::create() {
    std::vector<glm::vec4> pos;
    std::vector<glm::vec4> col;
    std::vector<GLuint> idx;

    int start = 0;
    int currentIdx = 0;
    for (uPtr<Joint> &joint: joints) {

        // rotate around x
        glm::vec4 offsetYZ = glm::vec4(0, 0.5, 0, 1);
        glm::vec3 axisX = glm::vec3(1, 0, 0);
        start = currentIdx;

        for (int i = 0; i < 18; i++) {
            pos.push_back(joint->getOverallTransformation() * offsetYZ);

            if (joint->id == representedJoint) {
                col.push_back(glm::vec4(1, 1, 1, 1));
            } else {
                // red
                col.push_back(glm::vec4(1, 0, 0, 1));
            }

            idx.push_back(currentIdx);
            if (i == 17) {
                idx.push_back(start);
            } else {
                idx.push_back(currentIdx + 1);
            }
            offsetYZ = glm::rotate(offsetYZ, glm::radians(20.f), axisX);
            currentIdx++;
        }

        // rotate around y
        glm::vec4 offsetZX = glm::vec4(0, 0, 0.5, 1);
        glm::vec3 axisY = glm::vec3(0, 1, 0);
        start = currentIdx;

        for (int i = 0; i < 18; i++) {
            pos.push_back(joint->getOverallTransformation() * offsetZX);

            if (joint->id == representedJoint) {
                 col.push_back(glm::vec4(1, 1, 1, 1));
            } else {
                col.push_back(glm::vec4(0, 1, 0, 1));
            }

            idx.push_back(currentIdx);
            if (i == 17) {
                idx.push_back(start);
            } else {
                idx.push_back(currentIdx + 1);
            }

            offsetZX = glm::rotate(offsetZX, glm::radians(20.f), axisY);
            currentIdx++;
        }

        // rotate around z
        glm::vec4 offsetXY = glm::vec4(0.5, 0, 0, 1);
        glm::vec3 axisZ = glm::vec3(0, 0, 1);
        start = currentIdx;

        for (int i = 0; i < 18; i++) {
            pos.push_back(joint->getOverallTransformation() * offsetXY);

            if (joint->id == representedJoint) {
                 col.push_back(glm::vec4(1, 1, 1, 1));
            } else {
                // blue
                col.push_back(glm::vec4(0, 0, 1, 1));
            }

            idx.push_back(currentIdx);
            if (i == 17) {
                idx.push_back(start);
            } else {
                idx.push_back(currentIdx + 1);
            }
            offsetXY = glm::rotate(offsetXY, glm::radians(20.f), axisZ);
            currentIdx++;
        }

        // the bones
        if (joint->jParent) {
            pos.push_back(joint->getOverallTransformation() * glm::vec4(0, 0, 0, 1));
            pos.push_back(joint->jParent->getOverallTransformation() * glm::vec4(0, 0, 0, 1));
            col.push_back(glm::vec4(1, 1, 0, 1));
            col.push_back(glm::vec4(1, 0, 1, 1));
            idx.push_back(currentIdx);
            idx.push_back(++currentIdx);
            currentIdx++;
        }
    }

    count = idx.size();

    generateIdx();
    bindIdx();
    mp_context->glBufferData(GL_ELEMENT_ARRAY_BUFFER, idx.size() * sizeof(GLuint), idx.data(), GL_STATIC_DRAW);

    generatePos();
    bindPos();
    mp_context->glBufferData(GL_ARRAY_BUFFER, pos.size() * sizeof(glm::vec4), pos.data(), GL_STATIC_DRAW);

    generateCol();
    bindCol();
    mp_context->glBufferData(GL_ARRAY_BUFFER, col.size() * sizeof(glm::vec4), col.data(), GL_STATIC_DRAW);


}


GLenum Skeleton::drawMode() {
    return GL_LINES;
}

void Skeleton::updateJoint(Joint* joint) {
    representedJoint = joint->id;
}

std::vector<glm::mat4> Skeleton::setTranslateMatrix() {
    std::vector<glm::mat4> translate;
    for (uPtr<Joint> &j : joints) {
        translate.push_back(j->getOverallTransformation());
    }
    return translate;

}
void Skeleton::setBindMatrix() {
    for (uPtr<Joint> &j : joints) {
        j->bindMatrix = glm::inverse(j->getOverallTransformation());
    }
}
