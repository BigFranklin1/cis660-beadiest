#pragma once
#include <maya/MItMeshVertex.h>
#include <vector>

class Mesh
{
};

class Vertex {
public:
	Vertex():id(-1){};
	~Vertex() {};
	MPoint position;
	MVector normal;
	int id;
	std::vector<int> adjacentEdges;
};

class Edge {
public:
	Edge():id(-1) {};
	~Edge() {};
	int id;
	int v1Id;
	int v2Id;
};

