#include "halfedgedisplay.h"

HalfEdgeDisplay::HalfEdgeDisplay(OpenGLContext* context)
    : Drawable(context), representedHalfEdge(nullptr)
{}

HalfEdgeDisplay::~HalfEdgeDisplay()
{}

void HalfEdgeDisplay::create(){
    std::vector<glm::vec4> pos;
        std::vector<glm::vec4> nor;
        std::vector<GLuint> idx;
        std::vector<glm::vec4> col;


        if (representedHalfEdge) {
            glm::vec4 vertexPos = glm::vec4(representedHalfEdge->vertex->pos, 1);
//            vertexPos.x *= 0.7;
//            vertexPos.y *= 0.7;

            glm::vec4 symVertexPos = glm::vec4(representedHalfEdge->symmHE->vertex->pos, 1);
//            symVertexPos.x *= 0.7f;
//            symVertexPos.y *= 0.7f;

//            // left and right sides
//            if(symVertexPos.x == vertexPos.x){
//                vertexPos.y *= 0.8;
//                vertexPos.z *= 0.8;
//                symVertexPos.y *= 0.8f;
//                symVertexPos.z *= 0.8f;
//            }
//            // top and buttom sides
//            if(symVertexPos.y == vertexPos.y){
//                vertexPos.x *= 0.8;
//                vertexPos.z *= 0.8;
//                symVertexPos.x *= 0.8f;
//                symVertexPos.z *= 0.8f;
//            }
//            // front and back sides
//            if(symVertexPos.z == vertexPos.z){
//                vertexPos.x *= 0.8;
//                vertexPos.y *= 0.8;
//                symVertexPos.x *= 0.8f;
//                symVertexPos.y *= 0.8f;
//            }

            pos.push_back(vertexPos);
            pos.push_back(symVertexPos);

            col.push_back(glm::vec4(1, 1, 1, 1));
            col.push_back(glm::vec4(1, 1, 1, 1));

            nor.push_back(glm::vec4(0, 0, 1, 1));
            nor.push_back(glm::vec4(0, 0, 1, 1));

            idx.push_back(0);
            idx.push_back(1);

        }

        count = idx.size();

        generateIdx();
        bindIdx();
        mp_context->glBufferData(GL_ELEMENT_ARRAY_BUFFER, idx.size() * sizeof(GLuint), idx.data(), GL_STATIC_DRAW);

        generateNor();
        bindNor();
        mp_context->glBufferData(GL_ARRAY_BUFFER, nor.size() * sizeof(glm::vec4), nor.data(), GL_STATIC_DRAW);

        generatePos();
        bindPos();
        mp_context->glBufferData(GL_ARRAY_BUFFER, pos.size() * sizeof(glm::vec4), pos.data(), GL_STATIC_DRAW);

        generateCol();
        bindCol();
        mp_context->glBufferData(GL_ARRAY_BUFFER, col.size() * sizeof(glm::vec4), col.data(), GL_STATIC_DRAW);
}


GLenum HalfEdgeDisplay::drawMode() {
    return GL_LINES;
}

void HalfEdgeDisplay::updateHalfEdge(HalfEdge * he) {
    representedHalfEdge = he;
}

