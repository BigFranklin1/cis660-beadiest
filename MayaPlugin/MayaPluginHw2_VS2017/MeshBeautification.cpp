#include "MeshBeautification.h"
#pragma once
#include "ToHexCmd.h"


MeshBeautification::MeshBeautification() : MPxCommand()
{
}

MeshBeautification::~MeshBeautification()
{
}

MStatus MeshBeautification::doIt(const MArgList& args)
{
	MStatus status = beautification();
	MGlobal::displayInfo("Start beautification\n");
	setResult("Mesh beautification was executed\n");

	return status;
}

MStatus MeshBeautification::beautification() {
	MStatus status;
	MObject multiVertexComponent, singleVertexComponent;
	MSelectionList sList;
	MDagPath meshDagPath;

	// 
	MGlobal::getActiveSelectionList(sList);
	if (sList.length() == 0)
	{
		displayError("No mesh or mesh transform specified!");
		return MS::kFailure;
	}

	// RETRIEVE THE FIRST ITEM FROM THE SELECTION LIST:
	sList.getDagPath(0, meshDagPath);

	// STORE THE MESH NAME
	MString meshName = meshDagPath.fullPathName();
	MGlobal::displayInfo("Selected Mesh Name: " + meshName);
	MGlobal::displayInfo("convert to hex");

	// create vertices list
	MItMeshVertex vertexIter(meshDagPath, multiVertexComponent);
	int id = 0;
	std::vector<Vertex> vertices;//(vertexIter.count(&status));
	for (; !vertexIter.isDone(); vertexIter.next())
	{
		Vertex v;
		v.id = id;//vertexIter.index(&status);
		v.position = vertexIter.position(MSpace::kWorld, &status);
		vertexIter.getNormal(v.normal, MSpace::kWorld);
		MString str;
		str += (double)v.normal.x;
		str += ",";
		str += (double)v.normal.y;
		str += ",";
		str += (double)v.normal.z;



		MGlobal::displayInfo(str);
		MIntArray adjEdges;
		vertexIter.getConnectedEdges(adjEdges);
		MPoint centroid;
		for (int i = 0; i < adjEdges.length(); i++) {
			v.adjacentEdges.push_back(adjEdges[i]);
		}
		vertices.push_back(v);
		id++;
	}

	// create edges
	MItMeshEdge edgeIter(meshDagPath, multiVertexComponent);
	std::vector<Edge> edges;// (edgeIter.count(&status));
	id = 0;
	for (; !edgeIter.isDone(); edgeIter.next())
	{
		Edge e;
		e.id = id;// vertexIter.index(&status);
		e.v1Id = edgeIter.index(0, &status);
		e.v2Id = edgeIter.index(1, &status);
		edges.push_back(e);
		id++;
	}

	// modify vertices
	vertexIter.reset();
	id = 0;
	for (; !vertexIter.isDone(); vertexIter.next())
	{
		//int id = vertexIter.index(&status);
		MPoint ori = vertices[id].position;
		MPoint centroid;
		double distance = INT_MAX;
		for (int id : vertices[id].adjacentEdges) {
			int neighborId = id == edges[id].v1Id ? edges[id].v2Id : edges[id].v1Id;
			MPoint neighborPos = vertices[neighborId].position;
			centroid += neighborPos;
			double dist = ori.distanceTo(neighborPos);
			if (distance > dist) {
				distance = dist;
			}
		}
		centroid = centroid / (unsigned int)vertices[id].adjacentEdges.size();
		double alpha = 0.6;
		double beta = 0.4;
		double gamma = 1 - alpha - beta;
		distance = distance > 1 ? 1 : distance;
		MPoint newPos = alpha * ori + beta * centroid + (ori + gamma * vertices[id].normal * distance);
		vertexIter.setPosition(newPos, MSpace::kWorld);
		id++;
	}

	return MS::kSuccess;

}


MSyntax MeshBeautification::newSyntax() {
	MSyntax syntax;
	syntax.addFlag(STEPSIZE, STEPSIZELONG, MSyntax::kDouble);
	syntax.addFlag(ANGLE, ANGLELONG, MSyntax::kDouble);
	syntax.addFlag(GRAMMAR, GRAMMARLONG, MSyntax::kString);
	syntax.addFlag(ITER, ITERLONG, MSyntax::kLong);
	return syntax;
}