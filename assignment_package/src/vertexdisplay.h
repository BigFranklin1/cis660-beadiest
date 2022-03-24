#ifndef VERTEXDISPLAY_H
#define VERTEXDISPLAY_H
#include <vertex.h>
#include <drawable.h>

class VertexDisplay : public Drawable {
protected:
    Vertex *representedVertex;

public:
    // Creates VBO data to make a visual
    // representation of the currently selected Vertex
    void create() override;
    // Change which Vertex representedVertex points to
    void updateVertex(Vertex*);

    GLenum drawMode() override;

    VertexDisplay(OpenGLContext* context);

};


#endif
