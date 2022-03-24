#ifndef FACEDISPLAY_H
#define FACEDISPLAY_H

#include <face.h>
#include <drawable.h>

class FaceDisplay: public Drawable
{
protected:
    Face *representedFace;

public:
    // Creates VBO data to make a visual
    // representation of the currently selected Vertex
    void create() override;
    // Change which Vertex representedVertex points to
    void updateFace(Face*);

    GLenum drawMode() override;

    FaceDisplay(OpenGLContext* context);

    ~FaceDisplay();

};

#endif // FACEDISPLAY_H
