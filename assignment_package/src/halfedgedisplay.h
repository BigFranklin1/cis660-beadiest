#ifndef HALFEDGEDISPLAY_H
#define HALFEDGEDISPLAY_H

#include <halfedge.h>
#include <drawable.h>

class HalfEdgeDisplay: public Drawable
{
protected:
    HalfEdge *representedHalfEdge;

public:
    // Creates VBO data to make a visual
    // representation of the currently selected Vertex
    void create() override;
    // Change which Vertex representedVertex points to
    void updateHalfEdge(HalfEdge*);

    GLenum drawMode() override;

    HalfEdgeDisplay(OpenGLContext* context);
    ~HalfEdgeDisplay();
};

#endif // HALFEDGEDISPLAY_H
