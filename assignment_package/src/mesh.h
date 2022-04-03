#ifndef MESH_H
#define MESH_H

#include <face.h>
#include <vertex.h>
#include <smartpointerhelp.h>
#include "drawable.h"
#include <halfedge.h>
#include <iostream>
//class Face;
//class Vertex;
//class HalfEdge;

class Mesh: public Drawable
{
public:

    std::vector<uPtr<Face>> faces;
    std::vector<uPtr<Vertex>> vertices;
    std::vector<uPtr<HalfEdge>> halfEdges;
    std::vector<uPtr<Vertex>> skinVertices;

    void buildCubeMesh();
    void initCubeData();
    void setHalfEdgeSymPairs(int he1, int he2);
    void setHalfEdgeVertices(int x, int y, int z, int vert);
    void triangulateFace(Face *face);
    void splitEdge(HalfEdge *he_1);
    void subdivision();
    void computeCentroids(std::map<Face*, Vertex*> *centroid_map,
                          std::vector<uPtr<Vertex>> *newVertices);
    void computeMidpoints(std::vector<HalfEdge*> *edge_split,
                          std::map<Face*, Vertex*> *centroid_map,
                          std::map<HalfEdge*, Vertex*> *midPoint_map,
                          std::vector<uPtr<Vertex>> *newVertices);
    void smooth(std::map<Face*, Vertex*> *centroid_map,
                std::map<HalfEdge*, Vertex*> *midPoint_map);

    // HELPERS
    void setSymm(std::vector<uPtr<HalfEdge>> *in_edges,
                       std::vector<uPtr<HalfEdge>> *out_edges);
    void setFaces(std::vector<HalfEdge*> *temp_he, Face *f, int n);

    std::vector<uPtr<Face>> quadFaces(std::vector<HalfEdge*> *temp_he, Face *f);

    void quadrangulate(std::vector<HalfEdge*> *edge_split,
                       std::map<Face*, Vertex*> *centroid_map,
                       std::map<HalfEdge*, Vertex*> *midpoint_map,
                       std::vector<uPtr<HalfEdge>> *newHalfEdges,
                       std::vector<uPtr<Face>> *newFaces);

    void postprocess();
    void skinAlgorithm();
    void create() override;
    GLenum drawMode() override;


    Mesh(OpenGLContext* context);

    ~Mesh();
};

#endif // MESH_H
