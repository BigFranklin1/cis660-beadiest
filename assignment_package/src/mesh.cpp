#include "mesh.h"

Mesh::Mesh(OpenGLContext* context)
    : Drawable(context), faces{}, vertices{}, halfEdges{}
{}

Mesh::~Mesh(){}
// helper
int getEdgeNum(Face* face) {
    int num = 0;
    HalfEdge* curr = face->halfEdge;
    do {
        num++;
        curr = curr->nextHE;
    } while (curr != face->halfEdge);

    return num;
}
void Mesh::create() {
    this->destroy();
    std::vector<glm::vec4> pos = std::vector<glm::vec4>();
    std::vector<glm::vec4> nor = std::vector<glm::vec4>();
    std::vector<glm::vec4> col = std::vector<glm::vec4>();
    std::vector<GLuint> idx = std::vector<GLuint>();

    int index = -1;
    for (const uPtr<Face> &face : faces) {
        // index for start of face
        index++;
        glm::vec4 normal;
        HalfEdge* curr = face->halfEdge;
        int i = 0;
        do {

            // update indices
            if (i >= 2) {
                idx.push_back(index);
                idx.push_back(index + i - 1);
                idx.push_back(index + i);
            }

            // pushing position, normal, color
            pos.push_back(glm::vec4(curr->vertex->pos, 1));
            col.push_back(glm::vec4(curr->face->color, 1));
            glm::vec3 pos1 = glm::vec3(curr->vertex->pos);
            glm::vec3 pos2 = glm::vec3(curr->nextHE->vertex->pos);
            nor.push_back(glm::vec4(glm::normalize(glm::cross(pos1, pos2)), 0));

            // incrementing vars
            i++;
            curr = curr->nextHE;
        } while (curr != face->halfEdge);
        index += i - 1;
    }

    count = idx.size();

    generateIdx();
    mp_context->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufIdx);
    mp_context->glBufferData(GL_ELEMENT_ARRAY_BUFFER, idx.size() * sizeof(GLuint), idx.data(), GL_STATIC_DRAW);

    generatePos();
    mp_context->glBindBuffer(GL_ARRAY_BUFFER, bufPos);
    mp_context->glBufferData(GL_ARRAY_BUFFER, pos.size() * sizeof(glm::vec4), pos.data(), GL_STATIC_DRAW);

    generateNor();
    mp_context->glBindBuffer(GL_ARRAY_BUFFER, bufNor);
    mp_context->glBufferData(GL_ARRAY_BUFFER, nor.size() * sizeof(glm::vec4), nor.data(), GL_STATIC_DRAW);

    generateCol();
    mp_context->glBindBuffer(GL_ARRAY_BUFFER, bufCol);
    mp_context->glBufferData(GL_ARRAY_BUFFER, col.size() * sizeof(glm::vec4), col.data(), GL_STATIC_DRAW);
}
//void Mesh::create(){
//    std::vector<glm::vec4> pos;
//    std::vector<glm::vec4> nor;
//    std::vector<glm::vec4> color;
//    std::vector<GLuint> idx;
//    std::vector<glm::ivec2> jointID;
//    std::vector<glm::vec2> jointWeight;


//    for (uPtr<Face> &f : faces) {
//        HalfEdge *currHE = f->halfEdge;
//        int firstCount = pos.size();

//        do {
//            HalfEdge* he = currHE;
//            glm::vec3 v1 = he->nextHE->vertex->pos - he->vertex->pos;
//            glm::vec3 v2 = he->nextHE->nextHE->vertex->pos - he->nextHE->vertex->pos;

//            // prevent overlap and false normal vector
//            while (glm::length(glm::cross(v1, v2)) < FLT_EPSILON) {
//               he = he->nextHE;
//               glm::vec3 nextVerPos = glm::vec3(he->nextHE->vertex->pos);
//               glm::vec3 currentVerPos = glm::vec3(he->vertex->pos);
//               glm::vec3 nextNextVerPos = glm::vec3(he->nextHE->nextHE->vertex->pos);

//               v1 = nextVerPos - currentVerPos;
//               v2 = nextNextVerPos - currentVerPos;
//           }

//            glm::vec4 normal = glm::vec4(glm::normalize(glm::cross(v1, v2)), 0);

//            pos.push_back(glm::vec4(currHE->vertex->pos, 1));
//            nor.push_back(normal);
//            color.push_back(glm::vec4(f->color, 1));

//            Vertex* vertex = currHE      ->vertex;
//            if (!vertex->weights.empty()) {
//                jointID.push_back(glm::ivec2(vertex->weights[0].first,
//                                             vertex->weights[1].first));
//                jointWeight.push_back(glm::vec2(vertex->weights[0].second,
//                                                vertex->weights[1].second));
//            }

//            currHE = currHE->nextHE;

//        } while (currHE != f->halfEdge);

//        // mesh
//        int i = 0;
//        // if it is a triangle, edgeNum = 3; condition is 1
//        //

//        std::cout<< "edge number of face: " << getEdgeNum(f.get()) << std::endl;

////        if(getEdgeNum(f.get()) <= 4){
//            while (i < getEdgeNum(f.get()) - 2) {
//                idx.push_back(firstCount);
//                idx.push_back(firstCount + i + 1);
//                idx.push_back(firstCount + i + 2);
//                i++;
//            }
////        }

////        if(getEdgeNum(f.get()) > 4){
//            std::cout<< "edge number of face: ";
//            std::cout << f->id << std::endl;

////        }
//    }

//    count = idx.size();

//    generateIdx();
//    bindIdx();
//    mp_context->glBufferData(GL_ELEMENT_ARRAY_BUFFER, idx.size() * sizeof(GLuint), idx.data(), GL_STATIC_DRAW);

//    generatePos();
//    bindPos();
//    mp_context->glBufferData(GL_ARRAY_BUFFER, pos.size() * sizeof(glm::vec4), pos.data(), GL_STATIC_DRAW);

//    generateNor();
//    bindNor();
//    mp_context->glBufferData(GL_ARRAY_BUFFER, nor.size() * sizeof(glm::vec4), nor.data(), GL_STATIC_DRAW);

//    generateCol();
//    bindCol();
//    mp_context->glBufferData(GL_ARRAY_BUFFER, color.size() * sizeof(glm::vec4), color.data(), GL_STATIC_DRAW);

//    generateJointID();
//    bindJointID();
//    mp_context->glBufferData(GL_ARRAY_BUFFER, jointID.size() * sizeof(glm::ivec2), jointID.data(), GL_STATIC_DRAW);

//    generateJointWeight();
//    bindJointWeight();

//}

GLenum Mesh::drawMode() {
    return GL_TRIANGLES;
}

void Mesh::buildCubeMesh(){

    // initialize faces, vertices, and halfedges in a cube
    for (int i = 0; i < 8; i++) {
        uPtr<Vertex> v = mkU<Vertex>();
        vertices.push_back(std::move(v));
    }

    for (int i = 0; i < 6; i++) {
        uPtr<Face> f = mkU<Face>();
        faces.push_back(std::move(f));
    }

    for (int i = 0; i < 24; i++) {
        uPtr<HalfEdge> he = mkU<HalfEdge>();
        halfEdges.push_back(std::move(he));
    }

    initCubeData();
}

// helpers set half edges that point to the same vertex
void Mesh::setHalfEdgeVertices(int vert, int first, int second, int third) {
    halfEdges.at(first)->vertex = vertices.at(vert).get();
    halfEdges.at(second)->vertex = vertices.at(vert).get();
    halfEdges.at(third)->vertex = vertices.at(vert).get();
}
void Mesh::setHalfEdgeSymPairs(int he1, int he2){
    halfEdges.at(he1)->symmHE = halfEdges.at(he2).get();
    halfEdges.at(he2)->symmHE = halfEdges.at(he1).get();
}
void Mesh::initCubeData() {

    // vertice positions and colors

   std::vector<glm::vec3> pos {glm::vec3 (-1.0, 1.0, 1.0),
                               glm::vec3 (-1.0, -1.0, 1.0),
                               glm::vec3 (1.0, -1.0, 1.0),
                               glm::vec3 (1.0, 1.0, 1.0),

                               glm::vec3 (1.0, 1.0, -1.0),
                               glm::vec3 (1.0, -1.0, -1.0),
                               glm::vec3 (-1.0, -1.0, -1.0),
                               glm::vec3 (-1.0, 1.0, -1.0)};

    std::vector<glm::vec3> col {glm::vec3 (1, 0, 0),
                                glm::vec3 (0, 1, 0),
                                glm::vec3 (0, 0, 1),

                                glm::vec3 (1, 0, 1),
                                glm::vec3 (0, 1, 1),
                                glm::vec3 (1, 0, 1)};

    // initialize pointers for faces
    for (int i = 0; i < 6; i++) {
        faces.at(i)->color = col[i];
        faces.at(i)->halfEdge = halfEdges.at(4 * i).get();
    }

    // initialize pointers for vertices
    for (int i = 0; i < 8; i++) {
        vertices.at(i)->pos = pos[i];
        vertices.at(i)->halfEdge = halfEdges.at(i).get();
    }

    // initialize pointers for halfedges
    for (int i = 0; i < 24 ; i++) {
        halfEdges.at(i)->face = faces.at(i / 4).get();

        if (i % 4 == 3) {
            halfEdges.at(i)->nextHE = halfEdges.at(i - 3).get();
        } else {
            halfEdges.at(i)->nextHE = halfEdges.at(i + 1).get();
        }
    }

    setHalfEdgeVertices(0, 15, 17, 0);
    setHalfEdgeVertices(1, 14, 22, 1);
    setHalfEdgeVertices(2, 9, 21, 2);
    setHalfEdgeVertices(3, 8, 18, 3);
    setHalfEdgeVertices(4, 11, 19, 4);
    setHalfEdgeVertices(5, 10, 20, 5);
    setHalfEdgeVertices(6, 13, 23, 6);
    setHalfEdgeVertices(7, 12, 16, 7);

    // 12 pairs of sym halfedges
    setHalfEdgeSymPairs(0, 18);
    setHalfEdgeSymPairs(1, 15);
    setHalfEdgeSymPairs(2, 22);
    setHalfEdgeSymPairs(3, 9);
    setHalfEdgeSymPairs(4, 16);
    setHalfEdgeSymPairs(5, 11);

    setHalfEdgeSymPairs(6, 20);
    setHalfEdgeSymPairs(7, 13);
    setHalfEdgeSymPairs(8, 19);
    setHalfEdgeSymPairs(10, 21);
    setHalfEdgeSymPairs(12, 17);
    setHalfEdgeSymPairs(14, 23);

}

void Mesh::splitEdge(HalfEdge* he){

    Vertex* v1 = he->vertex;
    Vertex* v2 = he->symmHE->vertex;
    uPtr<Vertex> v3 = mkU<Vertex>();

    v3 ->pos = glm::vec3((v1->pos.x + v2->pos.x) / 2,
                        (v1->pos.y + v2->pos.y) / 2,
                        (v1->pos.z + v2->pos.z) / 2);

    uPtr<HalfEdge> he1b = mkU<HalfEdge>();
    uPtr<HalfEdge> he2b = mkU<HalfEdge>();

    HalfEdge *he2 = he->symmHE;

    he1b->vertex = v1;
    he2b->vertex = v2;
    he->vertex = v3.get();
    he2->vertex = v3.get();
//    v3->col = v2-> col;

    he1b->face = he->face;
    he2b->face = he2->face;

    he1b->symmHE = he2;
    he2b->symmHE = he;
    he2->symmHE = he1b.get();
    he->symmHE = he2b.get();

    // the order is important here
    he1b->nextHE = he->nextHE;
    he->nextHE = he1b.get();
    he2b->nextHE = he2->nextHE;
    he2->nextHE = he2b.get();

    vertices.push_back(std::move(v3));
    halfEdges.push_back(std::move(he1b));
    halfEdges.push_back(std::move(he2b));

}

void Mesh::triangulateFace(Face* face){
    int num_edges = getEdgeNum(face);

    // if there is four edges, only one triangulation needed
    for(int i = 0; i < num_edges - 3; i++){
        HalfEdge* he0 = face->halfEdge;
        HalfEdge* he1 = he0->nextHE;
        HalfEdge* he2 = he1->nextHE;
        HalfEdge* he3 = he2->nextHE;


        uPtr<HalfEdge> he_A = mkU<HalfEdge>();
        uPtr<HalfEdge> he_B = mkU<HalfEdge>();

        he_A->vertex = he0->vertex;
        he_B->vertex = he2->vertex;

        he_A->symmHE = he_B.get();
        he_B->symmHE = he_A.get();

        uPtr<Face> face2 = mkU<Face>();
        he_A->face = face2.get();
        he0->nextHE->face = face2.get();
        he1->nextHE->face = face2.get();

        he_B->face = face;

        face2->halfEdge = he_A.get();

        he_B->nextHE = he3;
        he2->nextHE = he_A.get();
        he_A->nextHE = he1;
        he0->nextHE = he_B.get();

        halfEdges.push_back(std::move(he_A));
        halfEdges.push_back(std::move(he_B));
        faces.push_back(std::move(face2));
    }
};

void Mesh::subdivision(){
    //
    std::vector<uPtr<Vertex>> newVertices;
    std::vector<uPtr<HalfEdge>> newHalfEdges;
    std::vector<uPtr<Face>> newFaces;

    // storing these centroids in a way that you can access a centroid given its corresponding face
    std::map<Face*, Vertex*> centroidMap;
    std::map<HalfEdge*, Vertex*> midpointMap;

    std::vector<HalfEdge*> edge_split;

    // if he's symm is not in the list, add it to the list.
    for (auto &he: halfEdges) {
        if (std::find(edge_split.begin(), edge_split.end(),
                      he.get()->symmHE) == edge_split.end()) {
            edge_split.push_back(std::move(he.get()));
        }
    }
    for(auto h: edge_split){
        std::cout<<"edge_split: "<< h->id;
    }

    computeCentroids(&centroidMap, &newVertices);
    computeMidpoints(&edge_split, &centroidMap, &midpointMap, &newVertices);
    smooth(&centroidMap, &midpointMap);
    quadrangulate(&edge_split, &centroidMap, &midpointMap, &newHalfEdges, &newFaces);

    for (auto &v : newVertices) {
        vertices.push_back(std::move(v));
    }

    for (auto &he : newHalfEdges) {
        halfEdges.push_back(std::move(he));
    }

    for (auto &face: newFaces) {
        faces.push_back(std::move(face));
    }
}

void Mesh::triToHexa(){
    std::cout<< "converting triangle to hexagon"<< std::endl;

    std::vector<uPtr<Vertex>> newVertices;
    std::vector<uPtr<HalfEdge>> newHalfEdges;
    std::vector<uPtr<Face>> newFaces;

    // storing these centroids in a way that you can access a centroid given its corresponding face
    std::map<Face*, Vertex*> centroidMap;
    std::map<HalfEdge*, Vertex*> midpointMap;

    std::vector<HalfEdge*> edge_split;

    // if he's symm is not in the list, add it to the list.
    for (auto &he: halfEdges) {
        if (std::find(edge_split.begin(), edge_split.end(),
                      he.get()->symmHE) == edge_split.end()) {
            edge_split.push_back(std::move(he.get()));
        }
    }
//    for(auto h: edge_split){
//        std::cout<<"edge_split: "<< h->id;
//    }




    // compute all centroids of the triangle faces, and store them in new vertices
    computeCentroids(&centroidMap, &newVertices);
//    computeMidpoints(&edge_split, &centroidMap, &midpointMap, &newVertices);
//    smooth(&centroidMap, &midpointMap);
//    quadrangulate(&edge_split, &centroidMap, &midpointMap, &newHalfEdges, &newFaces);


//    hex(&centroidMap, &newHalfEdges, &newFaces,  &newVertices);
    hexTest(&centroidMap, &newHalfEdges, &newFaces);

    // clear the original mesh data
    vertices.clear();
    halfEdges.clear();
    faces.clear();

    for (auto &v : newVertices) {

        vertices.push_back(std::move(v));
    }

    for (auto &he : newHalfEdges) {
        halfEdges.push_back(std::move(he));
    }

    for (auto &face: newFaces) {
        faces.push_back(std::move(face));
    }

}
void Mesh::computeCentroids(std::map<Face*, Vertex*> *centroidMap,
                    std::vector<uPtr<Vertex>> *newVertices) {
    for (uPtr<Face> &f : faces) {
        uPtr<Vertex> centroid = mkU<Vertex>();
        glm::vec3 accumulated_pos = glm::vec3();
        glm::vec3 centroid_pos = glm::vec3();

        // the hf that this face points to
        HalfEdge *curr = f->halfEdge;

        // calculate the centroids
        do {
            accumulated_pos += curr->vertex->pos;
            curr = curr->nextHE;
            // loop through all he in a face
        } while (curr != f->halfEdge);

        centroid_pos = accumulated_pos /= getEdgeNum(f.get());
        centroid->pos = centroid_pos;

        centroidMap->insert({f.get(), centroid.get()});
        newVertices->push_back(std::move(centroid));
    }
}

void Mesh::computeMidpoints(std::vector<HalfEdge*> *edge_split,
                            std::map<Face*, Vertex*> *centroidMap,
                            std::map<HalfEdge*, Vertex*> *midpointMap,
                            std::vector<uPtr<Vertex>> *newVertices){
    // compute new hes for later assemble of new faces
    for (auto *he: *edge_split){
        uPtr<Vertex> midPoint = mkU<Vertex>();
        glm:: vec3 mp_pos = glm::vec3();
        HalfEdge *symHE = he->symmHE;

        glm::vec3 f1 = centroidMap->find(he->face)->second->pos;
        glm::vec3 f2 = centroidMap->find(symHE->face)->second->pos;

        glm::vec3 v1 = he->vertex->pos;
        glm::vec3 v2 = he->symmHE->vertex->pos;

        if (symHE) {
            mp_pos = (v1 + v2 + f1 + f2) / 4.0f;
        }else{
            // border edge
            mp_pos = (v1 + v2 + f1) / 3.0f;
        }
        midPoint->pos = mp_pos;

        midpointMap->insert({he, midPoint.get()});
        newVertices->push_back(std::move(midPoint));
    }
}

void Mesh::smooth(std::map<Face*, Vertex*> *centroidMap,
                  std::map<HalfEdge*, Vertex*> *midpointMap){
    // iterate through all old vertices
    for (auto &v : vertices) {
        HalfEdge *currHE = v->halfEdge;

       glm::vec3 sum_e = glm::vec3();
       glm::vec3 sum_f = glm::vec3();
       float n = 0;

       do {
          glm::vec3 midPointPos = midpointMap->find(currHE)->second->pos;
          glm::vec3 centroidPos = centroidMap->find(currHE->face)->second->pos;

          if (midpointMap->find(currHE->symmHE) != midpointMap->end()){
             midPointPos = midpointMap->find(currHE->symmHE)->second->pos;
          }

          sum_e += midPointPos;
          sum_f += centroidPos;

          n++;

          currHE = currHE->nextHE->symmHE;
      } while (currHE != v->halfEdge); // this makes sure that only two iterations are operated

      sum_e /= pow(n, 2);
      sum_f /= pow(n, 2);

      glm::vec3 v_pos = (n - 2.f) * v->pos / n + sum_e + sum_f;
      v->pos = v_pos;

    }

}

// helper function to assign symm he
void Mesh::setSymm(std::vector<uPtr<HalfEdge>> *edgesIn,
                      std::vector<uPtr<HalfEdge>> *edgesOut) {

    int IndexLast = edgesIn->size() - 1;
    edgesIn->at(IndexLast)->symmHE = edgesOut->at(0).get();
    edgesOut->at(0)->symmHE = edgesIn->at(IndexLast).get();

    for (int i = 0; i < IndexLast; i++) {
        edgesIn->at(i)->symmHE = edgesOut->at(i + 1).get();
        edgesOut->at(i + 1)->symmHE = edgesIn->at(i).get();
    }
}

void Mesh::setFaces(std::vector<HalfEdge*> *tempHeFromMP, Face *f, int n) {

    f->setColor();
    f->halfEdge = tempHeFromMP->at(n);

    tempHeFromMP->at(n)->face = f;
    tempHeFromMP->at(n)->nextHE->face = f;
    tempHeFromMP->at(n)->nextHE->nextHE->face = f;
    tempHeFromMP->at(n)->nextHE->nextHE->nextHE->face = f;
}

std::vector<uPtr<Face>> Mesh::quadFaces(std::vector<HalfEdge*> *tempHeFromMP, Face *f) {

    std::vector<uPtr<Face>> quad_faces;

    int n = (int)tempHeFromMP->size() - 1; // n = 3 in the cube case

    std::cout << "n: " << n;
    for (int i = 0; i < n; ++i) {
        uPtr<Face> newFace = mkU<Face>();
        setFaces(tempHeFromMP, newFace.get(), i);
        quad_faces.push_back(std::move(newFace));
    }

    setFaces(tempHeFromMP, f, n);

    return quad_faces;
}

void Mesh::quadrangulate(std::vector<HalfEdge*> *edge_split,
                         std::map<Face*, Vertex*> *centroidMap,
                         std::map<HalfEdge*, Vertex*> *midpointMap,
                         std::vector<uPtr<HalfEdge>> *newHalfEdges,
                         std::vector<uPtr<Face>> *newFaces)
{
    for (HalfEdge *he: *edge_split){

        HalfEdge* he1 = he;
        HalfEdge* he2 = he1->symmHE;
        Vertex *midPoint = midpointMap->find(he1)->second;
        Vertex* v1 = he1->vertex;
        Vertex* v2 = he2->vertex;

        uPtr<HalfEdge> he1B = mkU<HalfEdge>();
        uPtr<HalfEdge> he2B = mkU<HalfEdge>();

        he1B->vertex = v1;
        he2B->vertex = v2;

        he1B->face = he1->face;
        he2B->face = he2->face;

        // change the he that the face points to
        he1->face->halfEdge = he1B.get();
        he2->face->halfEdge = he2B.get();

        he1->symmHE = he2B.get();
        he2B->symmHE = he1;
        he2->symmHE = he1B.get();
        he1B->symmHE = he2;

        he1B->nextHE = he1->nextHE;
        he2B->nextHE = he2->nextHE;
        he1->nextHE = he1B.get();
        he2->nextHE = he2B.get();

        he1->vertex->halfEdge = he1B.get();
        he2->vertex->halfEdge = he2B.get();

        // the original HE's pointing vertex is cut to the midpoint
        he1->vertex = midPoint;
        he2->vertex = midPoint;

        newHalfEdges->push_back(std::move(he1B));
        newHalfEdges->push_back(std::move(he2B));
    }

    for (uPtr<Face> &f : faces) {
        HalfEdge *curr = f->halfEdge;

        // maintain a collection of halfedges
        std::vector<HalfEdge*> tempHeFromMP;
        std::vector<uPtr<HalfEdge>> edgesToCentroid;
        std::vector<uPtr<HalfEdge>> edgesFromCentroid;

        // access next half edge given id
        std::map<int, HalfEdge*> mapNextHE;
        // the quadrangulated faces
        std::vector<uPtr<Face>> quadedFaces;

        // store temporary halfedges
        // the original he that the face points to
        // starts from the midpoint after edge splitting.
        do {
            tempHeFromMP.push_back(curr);
            curr = curr->nextHE->nextHE;
        } while (curr != f->halfEdge);
        std::cout << "temp HE size: " << tempHeFromMP.size();
        HalfEdge *next = tempHeFromMP.at(tempHeFromMP.size() - 1)->nextHE;

        for (HalfEdge *he: tempHeFromMP) {
            mapNextHE.insert({he->id, next});
            next = he->nextHE;
        }

        for (HalfEdge *he : tempHeFromMP) {
            uPtr<HalfEdge> to_centroid = mkU<HalfEdge>();
            uPtr<HalfEdge> from_centroid = mkU<HalfEdge>();

            Vertex *cent_vert = centroidMap->find(he->face)->second;
            to_centroid->vertex = cent_vert;
            cent_vert->halfEdge = to_centroid.get();

            Vertex *next_vert = mapNextHE[he->id]->vertex;
            from_centroid->vertex = next_vert;
            next_vert->halfEdge = from_centroid.get();

            // half edge ring
            he->nextHE->nextHE = to_centroid.get();
            to_centroid->nextHE = from_centroid.get();
            from_centroid->nextHE = he;

            edgesToCentroid.push_back(std::move(to_centroid));
            edgesFromCentroid.push_back(std::move(from_centroid));
        }

        // set the symm HE
        setSymm(&edgesToCentroid, &edgesFromCentroid);

        for (auto &he : edgesToCentroid) {
            newHalfEdges->push_back(std::move(he));
        }

        for (auto &he : edgesFromCentroid) {
            newHalfEdges->push_back(std::move(he));
        }

        // quadrigulate faces
        quadedFaces = quadFaces(&tempHeFromMP, f.get());

        for (auto &face : quadedFaces) {
            newFaces->push_back(std::move(face));
        }
    }
}


void Mesh::hex(std::map<Face *, Vertex *> *centroid_map, std::vector<uPtr<HalfEdge>> *newHalfEdges, std::vector<uPtr<Face>> *newFaces, std::vector<uPtr<Vertex>> *newVertices){
    // centroid map stores face - vertex relationship

    for (auto &v: *newVertices){

        HalfEdge* he1 = v->halfEdge;
        Vertex* v1 = v.get();

        uPtr<HalfEdge> he1B = mkU<HalfEdge>();

        he1B->vertex = v1;

        he1B->face = he1->face;

        newHalfEdges->push_back(std::move(he1B));
    }
}

void Mesh::hexTest(std::map<Face *, Vertex *> *centroid_map, std::vector<uPtr<HalfEdge>> *newHalfEdges, std::vector<uPtr<Face>> *newFaces){

//    std::map<Vertex*, std::vector<Face*>> *v2fAroundMap = {};
    std::map<Vertex*, Face*> *v2fAroundMap = {};

    for (auto &v : vertices) {
        // old faces around
        std::vector<Face*> oldFaces;

        // initialize HEs
        HalfEdge *currHE = v->halfEdge;
        HalfEdge *NeighborHE;
        uPtr<Face> newFace = mkU<Face>();

        do{
            Face *f = currHE->face;
            NeighborHE = currHE->nextHE->symmHE;

            oldFaces.push_back(std::move(f));
            // jump into the next face's he
            currHE = currHE->nextHE->symmHE;
        }
        // while the next HE goes back to v->halfHE, the loop ends
        while(NeighborHE != v->halfEdge);

        switch(oldFaces.size()){
        case 3:{
            uPtr<HalfEdge> he1 = mkU<HalfEdge>();
            uPtr<HalfEdge> he1b = mkU<HalfEdge>();
            uPtr<HalfEdge> he2 = mkU<HalfEdge>();
            uPtr<HalfEdge> he2b = mkU<HalfEdge>();
            uPtr<HalfEdge> he3 = mkU<HalfEdge>();
            uPtr<HalfEdge> he3b = mkU<HalfEdge>();
            // currentHE is the one before inital one (which is the last one)
            Face *f = currHE->face;

            NeighborHE = currHE->nextHE->symmHE;
            Face *prevF = NeighborHE -> face;
            Face *nextF = currHE ->symmHE -> face;
//            Face *pprevF = NeighborHE ->nextHE ->symmHE->face;
//            Face *nnF = currHE ->symmHE -> nextHE ->symmHE -> face;

            Vertex *nV = centroid_map->at(f);
            Vertex *nextV = centroid_map->at(nextF);
            Vertex *prevV = centroid_map->at(prevF);

//            nV->halfEdge = he1.get();

            he1->vertex = nV;
            he1->face = newFace.get();

            he2->vertex = nextV;
            he2->face = newFace.get();

            he3->vertex = prevV;
            he3->face = newFace.get();

            // ----------------------------------------------------//
            he1b->vertex = prevV;
//            he1b->face = newFace.get();

            he2b->vertex = nV;
//            he2b->face = newFace.get();

            he3b->vertex = nextV;
//            he3b->face = newFace.get();

            // ----------------------------------------------------//

            he1->nextHE = he2.get();
            he1->symmHE = he1b.get();

            he1b->nextHE = he2.get();
            he1b->symmHE = he1.get();

            // ----------------------------------------------------//

            he2->nextHE = he3.get();
            he2->symmHE = he1b.get();

            he2b->nextHE = he2b.get();
            he2b->symmHE = he2.get();

            // ----------------------------------------------------//

            he3->nextHE = he1.get();
            he3->symmHE = he3b.get();

            he3b->nextHE = he2b.get();
            he3b->symmHE = he3.get();


            newFace->halfEdge = he1.get();
            newFace->setColor();

            newHalfEdges->push_back(std::move(he1));
            newHalfEdges->push_back(std::move(he2));
            newHalfEdges->push_back(std::move(he3));

            newHalfEdges->push_back(std::move(he1b));
            newHalfEdges->push_back(std::move(he2b));
            newHalfEdges->push_back(std::move(he3b));


            newFaces->push_back(std::move(newFace));
            break;

        }
        case 4:{
            uPtr<HalfEdge> he1 = mkU<HalfEdge>();
            uPtr<HalfEdge> he1b = mkU<HalfEdge>();
            uPtr<HalfEdge> he2 = mkU<HalfEdge>();
            uPtr<HalfEdge> he2b = mkU<HalfEdge>();
            uPtr<HalfEdge> he3 = mkU<HalfEdge>();
            uPtr<HalfEdge> he3b = mkU<HalfEdge>();
            uPtr<HalfEdge> he4 = mkU<HalfEdge>();
            uPtr<HalfEdge> he4b = mkU<HalfEdge>();
            // currentHE is the one before inital one (which is the last one)
            Face *f = currHE->face;

            NeighborHE = currHE->nextHE->symmHE;
            Face *prevF = NeighborHE -> face;
            Face *nextF = currHE ->symmHE -> face;
            Face *pprevF = NeighborHE ->nextHE ->symmHE->face;

            Vertex *nV = centroid_map->at(f);
            Vertex *nextV = centroid_map->at(nextF);
            Vertex *prevV = centroid_map->at(prevF);
            Vertex *pprevV = centroid_map->at(pprevF);

//            nV->halfEdge = he1.get();

            he1->vertex = nV;
            he1->face = newFace.get();

            he2->vertex = nextV;
            he2->face = newFace.get();

            he3->vertex = pprevV;
            he3->face = newFace.get();

            he4->vertex = prevV;
            he4->face = newFace.get();

            // ----------------------------------------------------//
            he1b->vertex = prevV;
//            he1b->face = newFace.get();

            he2b->vertex = nV;
//            he2b->face = newFace.get();

            he3b->vertex = nextV;
//            he3b->face = newFace.get();

            he4b->vertex = pprevV;

            // ----------------------------------------------------//

            he1->nextHE = he2.get();
            he1->symmHE = he1b.get();

            he1b->nextHE = he2.get();
            he1b->symmHE = he1.get();

            // ----------------------------------------------------//

            he2->nextHE = he3.get();
            he2->symmHE = he1b.get();

            he2b->nextHE = he2b.get();
            he2b->symmHE = he2.get();

            // ----------------------------------------------------//

            he3->nextHE = he4.get();
            he3->symmHE = he3b.get();

            he3b->nextHE = he2b.get();
            he3b->symmHE = he3.get();

            // ----------------------------------------------------//

            he4->nextHE = he1.get();
            he4->symmHE = he4b.get();

            he4b->nextHE = he3b.get();
            he4b->symmHE = he4.get();

            newFace->halfEdge = he1.get();
            newFace->setColor();

            newHalfEdges->push_back(std::move(he1));
            newHalfEdges->push_back(std::move(he2));
            newHalfEdges->push_back(std::move(he3));
            newHalfEdges->push_back(std::move(he4));

            newHalfEdges->push_back(std::move(he1b));
            newHalfEdges->push_back(std::move(he2b));
            newHalfEdges->push_back(std::move(he3b));
            newHalfEdges->push_back(std::move(he4b));


            newFaces->push_back(std::move(newFace));

            break;

        }
        case 5:{
            uPtr<HalfEdge> he1 = mkU<HalfEdge>();
            uPtr<HalfEdge> he1b = mkU<HalfEdge>();
            uPtr<HalfEdge> he2 = mkU<HalfEdge>();
            uPtr<HalfEdge> he2b = mkU<HalfEdge>();
            uPtr<HalfEdge> he3 = mkU<HalfEdge>();
            uPtr<HalfEdge> he3b = mkU<HalfEdge>();
            uPtr<HalfEdge> he4 = mkU<HalfEdge>();
            uPtr<HalfEdge> he4b = mkU<HalfEdge>();
            uPtr<HalfEdge> he5 = mkU<HalfEdge>();
            uPtr<HalfEdge> he5b = mkU<HalfEdge>();
            // currentHE is the one before inital one (which is the last one)
            Face *f = currHE->face;

            NeighborHE = currHE->nextHE->symmHE;
            Face *prevF = NeighborHE -> face;
            Face *nextF = currHE ->symmHE -> face;
            Face *pprevF = NeighborHE ->nextHE ->symmHE->face;
            Face *ppprevF = NeighborHE ->nextHE ->symmHE-> nextHE ->symmHE->face;

            Vertex *nV = centroid_map->at(f);
            Vertex *nextV = centroid_map->at(nextF);
            Vertex *prevV = centroid_map->at(prevF);
            Vertex *pprevV = centroid_map->at(pprevF);
            Vertex *ppprevV = centroid_map->at(ppprevF);

//            nV->halfEdge = he1.get();

            he1->vertex = nV;
            he1->face = newFace.get();

            he2->vertex = nextV;
            he2->face = newFace.get();

            he3->vertex = ppprevV;
            he3->face = newFace.get();

            he4->vertex = prevV;
            he4->face = newFace.get();

            he5->vertex = pprevV;
            he5->face = newFace.get();
            // ----------------------------------------------------//
            he1b->vertex = prevV;
//            he1b->face = newFace.get();

            he2b->vertex = nV;
//            he2b->face = newFace.get();

            he3b->vertex = nextV;
//            he3b->face = newFace.get();

            he4b->vertex = pprevV;

            he5b->vertex = ppprevV;

            // ----------------------------------------------------//

            he1->nextHE = he2.get();
            he1->symmHE = he1b.get();

            he1b->nextHE = he2.get();
            he1b->symmHE = he1.get();

            // ----------------------------------------------------//

            he2->nextHE = he3.get();
            he2->symmHE = he1b.get();

            he2b->nextHE = he2b.get();
            he2b->symmHE = he2.get();

            // ----------------------------------------------------//

            he3->nextHE = he5.get();
            he3->symmHE = he3b.get();

            he3b->nextHE = he2b.get();
            he3b->symmHE = he3.get();

            // ----------------------------------------------------//

            he4->nextHE = he1.get();
            he4->symmHE = he4b.get();

            he4b->nextHE = he3b.get();
            he4b->symmHE = he4.get();

            // ----------------------------------------------------//

            he5->nextHE = he4.get();
            he5->symmHE = he5b.get();

            he5b->nextHE = he4b.get();
            he5b->symmHE = he5.get();

            // ----------------------------------------------------//

            newFace->halfEdge = he1.get();
            newFace->setColor();

            newHalfEdges->push_back(std::move(he1));
            newHalfEdges->push_back(std::move(he2));
            newHalfEdges->push_back(std::move(he3));
            newHalfEdges->push_back(std::move(he4));
            newHalfEdges->push_back(std::move(he5));

            newHalfEdges->push_back(std::move(he1b));
            newHalfEdges->push_back(std::move(he2b));
            newHalfEdges->push_back(std::move(he3b));
            newHalfEdges->push_back(std::move(he4b));
            newHalfEdges->push_back(std::move(he5b));


            newFaces->push_back(std::move(newFace));

            break;
        }

        case 6:{
            uPtr<HalfEdge> he1 = mkU<HalfEdge>();
            uPtr<HalfEdge> he1b = mkU<HalfEdge>();
            uPtr<HalfEdge> he2 = mkU<HalfEdge>();
            uPtr<HalfEdge> he2b = mkU<HalfEdge>();
            uPtr<HalfEdge> he3 = mkU<HalfEdge>();
            uPtr<HalfEdge> he3b = mkU<HalfEdge>();
            uPtr<HalfEdge> he4 = mkU<HalfEdge>();
            uPtr<HalfEdge> he4b = mkU<HalfEdge>();
            uPtr<HalfEdge> he5 = mkU<HalfEdge>();
            uPtr<HalfEdge> he5b = mkU<HalfEdge>();
            uPtr<HalfEdge> he6 = mkU<HalfEdge>();
            uPtr<HalfEdge> he6b = mkU<HalfEdge>();
            // currentHE is the one before inital one (which is the last one)
            Face *f = currHE->face;

            NeighborHE = currHE->nextHE->symmHE;
            Face *prevF = NeighborHE -> face;
            Face *nextF = currHE ->symmHE -> face;
            Face *pprevF = NeighborHE ->nextHE ->symmHE->face;
            Face *ppprevF = NeighborHE ->nextHE ->symmHE-> nextHE ->symmHE->face;
            Face *pppprevF = NeighborHE ->nextHE ->symmHE-> nextHE ->symmHE -> nextHE ->symmHE->face;

            Vertex *nV = centroid_map->at(f);
            Vertex *nextV = centroid_map->at(nextF);
            Vertex *prevV = centroid_map->at(prevF);
            Vertex *pprevV = centroid_map->at(pprevF);
            Vertex *ppprevV = centroid_map->at(ppprevF);
            Vertex *pppprevV = centroid_map->at(pppprevF);

//            nV->halfEdge = he1.get();

            he1->vertex = nV;
            he1->face = newFace.get();

            he2->vertex = nextV;
            he2->face = newFace.get();

            he3->vertex = pppprevV;
            he3->face = newFace.get();

            he4->vertex = prevV;
            he4->face = newFace.get();

            he5->vertex = pprevV;
            he5->face = newFace.get();

            he6->vertex = ppprevV;
            he6->face = newFace.get();
            // ----------------------------------------------------//
            he1b->vertex = prevV;
//            he1b->face = newFace.get();

            he2b->vertex = nV;
//            he2b->face = newFace.get();

            he3b->vertex = nextV;
//            he3b->face = newFace.get();

            he4b->vertex = pprevV;

            he5b->vertex = ppprevV;

            he6b->vertex = pppprevV;


            // ----------------------------------------------------//

            he1->nextHE = he2.get();
            he1->symmHE = he1b.get();

            he1b->nextHE = he2.get();
            he1b->symmHE = he1.get();

            // ----------------------------------------------------//

            he2->nextHE = he3.get();
            he2->symmHE = he1b.get();

            he2b->nextHE = he2b.get();
            he2b->symmHE = he2.get();

            // ----------------------------------------------------//

            he3->nextHE = he6.get();
            he3->symmHE = he3b.get();

            he3b->nextHE = he2b.get();
            he3b->symmHE = he3.get();

            // ----------------------------------------------------//

            he4->nextHE = he1.get();
            he4->symmHE = he4b.get();

            he4b->nextHE = he3b.get();
            he4b->symmHE = he4.get();

            // ----------------------------------------------------//

            he5->nextHE = he4.get();
            he5->symmHE = he5b.get();

            he5b->nextHE = he4b.get();
            he5b->symmHE = he5.get();

            // ----------------------------------------------------//

            he6->nextHE = he5.get();
            he6->symmHE = he6b.get();

            he6b->nextHE = he5b.get();
            he6b->symmHE = he6.get();

            // ----------------------------------------------------//
            newFace->halfEdge = he1.get();
            newFace->setColor();

            newHalfEdges->push_back(std::move(he1));
            newHalfEdges->push_back(std::move(he2));
            newHalfEdges->push_back(std::move(he3));
            newHalfEdges->push_back(std::move(he4));
            newHalfEdges->push_back(std::move(he5));
            newHalfEdges->push_back(std::move(he6));

            newHalfEdges->push_back(std::move(he1b));
            newHalfEdges->push_back(std::move(he2b));
            newHalfEdges->push_back(std::move(he3b));
            newHalfEdges->push_back(std::move(he4b));
            newHalfEdges->push_back(std::move(he5b));
            newHalfEdges->push_back(std::move(he6b));


            newFaces->push_back(std::move(newFace));

            break;
        }

        case 7:{
            uPtr<HalfEdge> he1 = mkU<HalfEdge>();
            uPtr<HalfEdge> he1b = mkU<HalfEdge>();
            uPtr<HalfEdge> he2 = mkU<HalfEdge>();
            uPtr<HalfEdge> he2b = mkU<HalfEdge>();
            uPtr<HalfEdge> he3 = mkU<HalfEdge>();
            uPtr<HalfEdge> he3b = mkU<HalfEdge>();
            uPtr<HalfEdge> he4 = mkU<HalfEdge>();
            uPtr<HalfEdge> he4b = mkU<HalfEdge>();
            uPtr<HalfEdge> he5 = mkU<HalfEdge>();
            uPtr<HalfEdge> he5b = mkU<HalfEdge>();
            uPtr<HalfEdge> he6 = mkU<HalfEdge>();
            uPtr<HalfEdge> he6b = mkU<HalfEdge>();
            uPtr<HalfEdge> he7 = mkU<HalfEdge>();
            uPtr<HalfEdge> he7b = mkU<HalfEdge>();
            // currentHE is the one before inital one (which is the last one)
            Face *f = currHE->face;

            NeighborHE = currHE->nextHE->symmHE;
            Face *prevF = NeighborHE -> face;
            Face *nextF = currHE ->symmHE -> face;
            Face *pprevF = NeighborHE ->nextHE ->symmHE->face;
            Face *ppprevF = NeighborHE ->nextHE ->symmHE-> nextHE ->symmHE->face;
            Face *pppprevF = NeighborHE ->nextHE ->symmHE-> nextHE ->symmHE -> nextHE ->symmHE->face;
            Face *ppppprevF = NeighborHE ->nextHE ->symmHE-> nextHE ->symmHE -> nextHE ->symmHE-> nextHE ->symmHE->face;

            Vertex *nV = centroid_map->at(f);
            Vertex *nextV = centroid_map->at(nextF);
            Vertex *prevV = centroid_map->at(prevF);
            Vertex *pprevV = centroid_map->at(pprevF);
            Vertex *ppprevV = centroid_map->at(ppprevF);
            Vertex *pppprevV = centroid_map->at(pppprevF);
            Vertex *ppppprevV = centroid_map->at(ppppprevF);

//            nV->halfEdge = he1.get();

            he1->vertex = nV;
            he1->face = newFace.get();

            he2->vertex = nextV;
            he2->face = newFace.get();

            he3->vertex = ppppprevV;
            he3->face = newFace.get();

            he4->vertex = prevV;
            he4->face = newFace.get();

            he5->vertex = pprevV;
            he5->face = newFace.get();

            he6->vertex = ppprevV;
            he6->face = newFace.get();

            he7->vertex = pppprevV;
            he7->face = newFace.get();
            // ----------------------------------------------------//
            he1b->vertex = prevV;
//            he1b->face = newFace.get();

            he2b->vertex = nV;
//            he2b->face = newFace.get();

            he3b->vertex = nextV;
//            he3b->face = newFace.get();

            he4b->vertex = pprevV;

            he5b->vertex = ppprevV;

            he6b->vertex = pppprevV;

            he7b->vertex = ppppprevV;

            // ----------------------------------------------------//

            he1->nextHE = he2.get();
            he1->symmHE = he1b.get();

            he1b->nextHE = he2.get();
            he1b->symmHE = he1.get();

            // ----------------------------------------------------//

            he2->nextHE = he3.get();
            he2->symmHE = he1b.get();

            he2b->nextHE = he2b.get();
            he2b->symmHE = he2.get();

            // -----------------ENd-----------------------------------//

            he3->nextHE = he7.get();
            he3->symmHE = he3b.get();

            he3b->nextHE = he2b.get();
            he3b->symmHE = he3.get();

            // ----------------------------------------------------//

            he4->nextHE = he1.get();
            he4->symmHE = he4b.get();

            he4b->nextHE = he3b.get();
            he4b->symmHE = he4.get();

            // ----------------------------------------------------//

            he5->nextHE = he4.get();
            he5->symmHE = he5b.get();

            he5b->nextHE = he4b.get();
            he5b->symmHE = he5.get();

            // ----------------------------------------------------//

            he6->nextHE = he5.get();
            he6->symmHE = he6b.get();

            he6b->nextHE = he5b.get();
            he6b->symmHE = he6.get();

            // ----------------------------------------------------//
            he7->nextHE = he6.get();
            he7->symmHE = he7b.get();

            he7b->nextHE = he6b.get();
            he7b->symmHE = he7.get();

            // ----------------------------------------------------//
            newFace->halfEdge = he1.get();
            newFace->setColor();

            newHalfEdges->push_back(std::move(he1));
            newHalfEdges->push_back(std::move(he2));
            newHalfEdges->push_back(std::move(he3));
            newHalfEdges->push_back(std::move(he4));
            newHalfEdges->push_back(std::move(he5));
            newHalfEdges->push_back(std::move(he6));
            newHalfEdges->push_back(std::move(he7));

            newHalfEdges->push_back(std::move(he1b));
            newHalfEdges->push_back(std::move(he2b));
            newHalfEdges->push_back(std::move(he3b));
            newHalfEdges->push_back(std::move(he4b));
            newHalfEdges->push_back(std::move(he5b));
            newHalfEdges->push_back(std::move(he6b));
            newHalfEdges->push_back(std::move(he7b));


            newFaces->push_back(std::move(newFace));

            break;
        }

        case 8:{
            uPtr<HalfEdge> he1 = mkU<HalfEdge>();
            uPtr<HalfEdge> he1b = mkU<HalfEdge>();
            uPtr<HalfEdge> he2 = mkU<HalfEdge>();
            uPtr<HalfEdge> he2b = mkU<HalfEdge>();
            uPtr<HalfEdge> he3 = mkU<HalfEdge>();
            uPtr<HalfEdge> he3b = mkU<HalfEdge>();
            uPtr<HalfEdge> he4 = mkU<HalfEdge>();
            uPtr<HalfEdge> he4b = mkU<HalfEdge>();
            uPtr<HalfEdge> he5 = mkU<HalfEdge>();
            uPtr<HalfEdge> he5b = mkU<HalfEdge>();
            uPtr<HalfEdge> he6 = mkU<HalfEdge>();
            uPtr<HalfEdge> he6b = mkU<HalfEdge>();
            uPtr<HalfEdge> he7 = mkU<HalfEdge>();
            uPtr<HalfEdge> he7b = mkU<HalfEdge>();
            uPtr<HalfEdge> he8 = mkU<HalfEdge>();
            uPtr<HalfEdge> he8b = mkU<HalfEdge>();
            // currentHE is the one before inital one (which is the last one)
            Face *f = currHE->face;

            NeighborHE = currHE->nextHE->symmHE;
            Face *prevF = NeighborHE -> face;
            Face *nextF = currHE ->symmHE -> face;
            Face *pprevF = NeighborHE ->nextHE ->symmHE->face;
            Face *ppprevF = NeighborHE ->nextHE ->symmHE-> nextHE ->symmHE->face;
            Face *pppprevF = NeighborHE ->nextHE ->symmHE-> nextHE ->symmHE -> nextHE ->symmHE->face;
            Face *ppppprevF = NeighborHE ->nextHE ->symmHE-> nextHE ->symmHE -> nextHE ->symmHE-> nextHE ->symmHE->face;
            Face *pppppprevF = NeighborHE ->nextHE ->symmHE-> nextHE ->symmHE -> nextHE ->symmHE-> nextHE ->symmHE -> nextHE ->symmHE->face;

            Vertex *nV = centroid_map->at(f);
            Vertex *nextV = centroid_map->at(nextF);
            Vertex *prevV = centroid_map->at(prevF);
            Vertex *pprevV = centroid_map->at(pprevF);
            Vertex *ppprevV = centroid_map->at(ppprevF);
            Vertex *pppprevV = centroid_map->at(pppprevF);
            Vertex *ppppprevV = centroid_map->at(ppppprevF);
            Vertex *pppppprevV = centroid_map->at(pppppprevF);

//            nV->halfEdge = he1.get();

            he1->vertex = nV;
            he1->face = newFace.get();

            he2->vertex = nextV;
            he2->face = newFace.get();

            he3->vertex = pppppprevV;
            he3->face = newFace.get();

            he4->vertex = prevV;
            he4->face = newFace.get();

            he5->vertex = pprevV;
            he5->face = newFace.get();

            he6->vertex = ppprevV;
            he6->face = newFace.get();

            he7->vertex = pppprevV;
            he7->face = newFace.get();

            he8->vertex = ppppprevV;
            he8->face = newFace.get();
            // ----------------------------------------------------//
            he1b->vertex = prevV;
//            he1b->face = newFace.get();

            he2b->vertex = nV;
//            he2b->face = newFace.get();

            he3b->vertex = nextV;
//            he3b->face = newFace.get();

            he4b->vertex = pprevV;

            he5b->vertex = ppprevV;

            he6b->vertex = pppprevV;

            he7b->vertex = ppppprevV;

            he8b->vertex = pppppprevV;

            // ----------------------------------------------------//

            he1->nextHE = he2.get();
            he1->symmHE = he1b.get();

            he1b->nextHE = he2.get();
            he1b->symmHE = he1.get();

            // ----------------------------------------------------//

            he2->nextHE = he3.get();
            he2->symmHE = he1b.get();

            he2b->nextHE = he2b.get();
            he2b->symmHE = he2.get();

            // -----------------ENd-----------------------------------//

            he3->nextHE = he8.get();
            he3->symmHE = he3b.get();

            he3b->nextHE = he2b.get();
            he3b->symmHE = he3.get();

            // ----------------------------------------------------//

            he4->nextHE = he1.get();
            he4->symmHE = he4b.get();

            he4b->nextHE = he3b.get();
            he4b->symmHE = he4.get();

            // ----------------------------------------------------//

            he5->nextHE = he4.get();
            he5->symmHE = he5b.get();

            he5b->nextHE = he4b.get();
            he5b->symmHE = he5.get();

            // ----------------------------------------------------//

            he6->nextHE = he5.get();
            he6->symmHE = he6b.get();

            he6b->nextHE = he5b.get();
            he6b->symmHE = he6.get();

            // ----------------------------------------------------//
            he7->nextHE = he6.get();
            he7->symmHE = he7b.get();

            he7b->nextHE = he6b.get();
            he7b->symmHE = he7.get();

            // ----------------------------------------------------//
            he8->nextHE = he7.get();
            he8->symmHE = he8b.get();

            he8b->nextHE = he6b.get();
            he8b->symmHE = he8.get();
            // ----------------------------------------------------//
            newFace->halfEdge = he1.get();
            newFace->setColor();

            newHalfEdges->push_back(std::move(he1));
            newHalfEdges->push_back(std::move(he2));
            newHalfEdges->push_back(std::move(he3));
            newHalfEdges->push_back(std::move(he4));
            newHalfEdges->push_back(std::move(he5));
            newHalfEdges->push_back(std::move(he6));
            newHalfEdges->push_back(std::move(he7));
            newHalfEdges->push_back(std::move(he8));

            newHalfEdges->push_back(std::move(he1b));
            newHalfEdges->push_back(std::move(he2b));
            newHalfEdges->push_back(std::move(he3b));
            newHalfEdges->push_back(std::move(he4b));
            newHalfEdges->push_back(std::move(he5b));
            newHalfEdges->push_back(std::move(he6b));
            newHalfEdges->push_back(std::move(he7b));
            newHalfEdges->push_back(std::move(he8b));


            newFaces->push_back(std::move(newFace));

            break;
        }

        default:
                break;
        }


        std::cout << "old faces around v" << v->id << "is: " << oldFaces.size()<< std::endl;


        // helper debug
        std::cout << v.get()->id << "faces "<< std::endl;
        for (auto f: oldFaces){
            std::cout<< f->id << std::endl;
        }
    // for v ends
    }




}


void Mesh::hexTest2(std::map<Face *, Vertex *> *centroid_map, std::vector<uPtr<HalfEdge>> *newHalfEdges, std::vector<uPtr<Face>> *newFaces){

//    std::map<Vertex*, std::vector<Face*>> *v2fAroundMap = {};
    std::map<Vertex*, Face*> *v2fAroundMap = {};

    for (auto &v : vertices) {
        // old faces around
        std::vector<Face*> oldFaces;

        // initialize HEs
        HalfEdge *currHE = v->halfEdge;
        HalfEdge *NeighborHE;
        uPtr<Face> newFace = mkU<Face>();





        // loop until all faces are iterated (when the current he equals to the staring one)
        do{
            // initialize new half edges
            uPtr<HalfEdge> he1 = mkU<HalfEdge>();
            uPtr<HalfEdge> he1b = mkU<HalfEdge>();
            uPtr<HalfEdge> he2 = mkU<HalfEdge>();
            uPtr<HalfEdge> he2b = mkU<HalfEdge>();
            uPtr<HalfEdge> he3 = mkU<HalfEdge>();
            uPtr<HalfEdge> he3b = mkU<HalfEdge>();
            // currentHE is the one before inital one (which is the last one)
            Face *f = currHE->face;

            NeighborHE = currHE->nextHE->symmHE;
            Face *prevF = NeighborHE -> face;
            Face *nextF = currHE ->symmHE -> face;
//            Face *pprevF = NeighborHE ->nextHE ->symmHE->face;
//            Face *nnF = currHE ->symmHE -> nextHE ->symmHE -> face;

            Vertex *nV = centroid_map->at(f);
            Vertex *nextV = centroid_map->at(nextF);
            Vertex *prevV = centroid_map->at(prevF);

//            nV->halfEdge = he1.get();

            he1->vertex = nV;
            he1->face = newFace.get();

            he2->vertex = nextV;
            he2->face = newFace.get();

            he3->vertex = prevV;
            he3->face = newFace.get();

            // ----------------------------------------------------//
            he1b->vertex = prevV;
//            he1b->face = newFace.get();

            he2b->vertex = nV;
//            he2b->face = newFace.get();

            he3b->vertex = nextV;
//            he3b->face = newFace.get();

            // ----------------------------------------------------//

            he1->nextHE = he2.get();
            he1->symmHE = he1b.get();

            he1b->nextHE = he2.get();
            he1b->symmHE = he1.get();

            // ----------------------------------------------------//

            he2->nextHE = he3.get();
            he2->symmHE = he1b.get();

            he2b->nextHE = he2b.get();
            he2b->symmHE = he2.get();

            // ----------------------------------------------------//

            he3->nextHE = he1.get();
            he3->symmHE = he3b.get();

            he3b->nextHE = he2b.get();
            he3b->symmHE = he3.get();


            newFace->halfEdge = he1.get();
            newFace->setColor();

            newHalfEdges->push_back(std::move(he1));
            newHalfEdges->push_back(std::move(he2));
            newHalfEdges->push_back(std::move(he3));

            newHalfEdges->push_back(std::move(he1b));
            newHalfEdges->push_back(std::move(he2b));
            newHalfEdges->push_back(std::move(he3b));

            oldFaces.push_back(std::move(f));


            // jump into the next face's he
            currHE = currHE->nextHE->symmHE;
        }
        // while the next HE goes back to v->halfHE, the loop ends
        while(NeighborHE != v->halfEdge);

        newFaces->push_back(std::move(newFace));

        std::cout << "old faces around v" << v->id << "is: " << oldFaces.size()<< std::endl;


        // helper debug
        std::cout << v.get()->id << "faces "<< std::endl;
        for (auto f: oldFaces){
            std::cout<< f->id << std::endl;
        }
    // for v ends
    }




}





