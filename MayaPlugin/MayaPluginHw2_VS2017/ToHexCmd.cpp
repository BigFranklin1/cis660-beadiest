#pragma once
#include "ToHexCmd.h"


ToHexCmd::ToHexCmd() : MPxCommand()
{
}

ToHexCmd::~ToHexCmd()
{
}

//MStatus ToHexCmd::createLSystem(double angle, double step, double iter, MString grammar)
//{
//	LSystem lsystem;
//	lsystem.loadProgramFromString(grammar.asChar());
//	lsystem.setDefaultAngle(angle);
//	lsystem.setDefaultStep(step);
//	std::vector<LSystem::Branch> b;
//
//	for (int i = 0; i < iter; i++)
//	{
//		std::string currIter = lsystem.getIteration(i);
//		lsystem.process(i, b);
//	}
//
//	for (int i = 0; i < b.size(); i++)
//	{
//		vec3 start = b.at(i).first;
//		vec3 end = b.at(i).second;
//
//		std::string c;
//		std::stringstream stringStream;
//		stringStream << "$myCurve = `curve -d 1 -p " << start[0] << " " << start[2] << " " << start[1] << " -p " << end[0] << " " << end[2] << " " << end[1] << "-k 0 -k 1`";
//		c = stringStream.str();
//
//		MString cmd1 = "global string $myCurve";
//		MString cmd2 = c.c_str();
//		MString cmd3 = "circle -r 0.2 -name nurbsCircle1";
//		MString cmd4 = "select -r nurbsCircle1 curve1";
//		MString cmd5 = "extrude -ch true -rn false -po 1 -et 2 -ucp 1 -fpt 1 -upn 1 -rotation 0 -scale 1 -rsp 1 nurbsCircle1 $myCurve";
//
//		MGlobal::executeCommand(cmd1);
//		MGlobal::executeCommand(cmd2);
//		MGlobal::executeCommand(cmd3);
//		MGlobal::executeCommand(cmd4);
//		MGlobal::executeCommand(cmd5);
//	}
//
//	return MS::kSuccess;
//}

MStatus ToHexCmd::doIt(const MArgList& args)
{
	MStatus status = convertToHex();
	MGlobal::displayInfo("ToHexCmd\n");
	setResult("ToHexCmd was executed\n");




	return status;
}

MStatus ToHexCmd::convertToHex() {
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

	// new points 
	MFloatPointArray centroidArray;

	// create faces
	MItMeshPolygon faceIter(meshDagPath, multiVertexComponent);
	std::vector<Face> faces;// (faceIter.count(&status));
	id = 0;
	for (; !faceIter.isDone(); faceIter.next())
	{
		Face f;
		f.id = id;// vertexIter.index(&status);
		
		MIntArray adjEdges;
		faceIter.getConnectedEdges(adjEdges);
		for (int i = 0; i < adjEdges.length(); i++) {
			f.edges.push_back(adjEdges[i]);
		}

		MIntArray adjVertices;
		faceIter.getConnectedVertices(adjVertices);
		for (int i = 0; i < adjVertices.length(); i++) {
			f.vertices.push_back(adjVertices[i]);
			f.centroid += vertices[adjVertices[i]].position;
		}

		f.centroid.x /= adjVertices.length();
		f.centroid.y /= adjVertices.length();
		f.centroid.z /= adjVertices.length();
		f.centroid.w /= adjVertices.length();
		MString str;
		str += (double)f.centroid.x;
		str += ",";
		str += (double)f.centroid.y;
		str += ",";
		str += (double)f.centroid.z;



		displayInfo(str);
		faces.push_back(f);
		id++;
	}
	// reset new polygon
	//MFnMesh newMesh();

	int numOfNewV = faces.size();
	const int numOfNewF = vertices.size();

	MFloatPointArray newPoints;
	
	int* face_counts = new int[numOfNewV];

	//std::vector<int> face_counts;
	int numOfFaceConnects = 0;

	int i = 0;
	for (Face f : faces) {
		newPoints.append(f.centroid);
		face_counts[i] = f.edges.size();
		numOfFaceConnects += face_counts[i];
		i++;
	}
	int* face_connects = new int[numOfFaceConnects];
	
	// assign face connected vertices
	int index = 0;
	for (; !faceIter.isDone(); faceIter.next()){
		MIntArray adjVertices;
		faceIter.getConnectedVertices(adjVertices);
		for (int v: adjVertices) {
			face_connects[index] = v;
			//vIndex++;
			index++;
		}
	}



	
	//// new points generated
	//newPoints.append(1,1,1);

	//int face_connects[24] = { 0, 1, 2, 3,
	//						4, 5, 6, 7,
	//						3, 2, 6, 5,
	//						0, 3, 5, 4,
	//						0, 4, 7, 1,
	//						1, 7, 6, 2 };

	//newMesh.create(numOfNewV, numOfNewF, vertices, face_connects, );

	//newMesh.create(points.length(), faceCounts.length(),
	//	points, faceCounts, faceConnects, outData, &stat);



	// ----------TEST: create a single cube-------------
	//MDataHandle outputHandle = data.outputValue(outputMesh, &status);

	MFnMeshData dataCreator;
	MObject outData = dataCreator.create(&status);

	const int numFaces = 6;
	int fc[numFaces] = { 4, 4, 4, 4, 4, 4};
	MIntArray faceCounts(fc, numFaces);
	// Set up and array to assign vertices from points to each face
	//
	const int numFaceConnects = 36;
	//MObject outData ;

	MFloatPointArray points;
	float cubeSize = 1;
	points.append(-cubeSize, -cubeSize, -cubeSize);
	points.append(cubeSize, -cubeSize, -cubeSize);
	points.append(cubeSize, -cubeSize, cubeSize);
	points.append(-cubeSize, -cubeSize, cubeSize);
	points.append(-cubeSize, cubeSize, -cubeSize);
	points.append(-cubeSize, cubeSize, cubeSize);
	points.append(cubeSize, cubeSize, cubeSize);
	points.append(cubeSize, cubeSize, -cubeSize);

	int fconnects[numFaceConnects] = { 0, 1, 2, 3, 4, 5, 6, 7, 3, 2, 6, 5, 0, 3, 5, 4, 0, 4, 7, 1, 1, 7, 6, 2};
	MIntArray faceConnects(fconnects, numFaceConnects);
	MFnMesh meshFS;
	MObject newMesh;
	newMesh = meshFS.create(6, faceCounts.length(),
		points, faceCounts, faceConnects, outData, &status);

	displayInfo("new mesh created");

	// -------------FOR BEAUTIFICATION: modify vertices-------------
	//vertexIter.reset();
	//id = 0;
	//for (; !vertexIter.isDone(); vertexIter.next())
	//{
	//	//int id = vertexIter.index(&status);
	//	MPoint ori = vertices[id].position;
	//	MPoint centroid;
	//	double distance = INT_MAX;
	//	for (int id : vertices[id].adjacentEdges) {
	//		int neighborId = id == edges[id].v1Id ? edges[id].v2Id : edges[id].v1Id;
	//		MPoint neighborPos = vertices[neighborId].position;
	//		centroid += neighborPos;
	//		double dist = ori.distanceTo(neighborPos);
	//		if (distance > dist) {
	//			distance = dist;
	//		}
	//	}
	//	centroid = centroid / (unsigned int) vertices[id].adjacentEdges.size();
	//	double alpha = 0.4;
	//	double beta = 0.6;
	//	double gamma = 1 - alpha - beta;
	//	distance = distance > 1 ? 1 : distance;
	//	MPoint newPos = alpha * ori + beta * centroid + gamma * -vertices[id].normal * distance;
	//	vertexIter.setPosition(newPos, MSpace::kWorld);
	//	id++;
	//}

	return MS::kSuccess;

}


MSyntax ToHexCmd::newSyntax() {
	MSyntax syntax;
	syntax.addFlag(STEPSIZE, STEPSIZELONG, MSyntax::kDouble);
	syntax.addFlag(ANGLE, ANGLELONG, MSyntax::kDouble);
	syntax.addFlag(GRAMMAR, GRAMMARLONG, MSyntax::kString);
	syntax.addFlag(ITER, ITERLONG, MSyntax::kLong);
	return syntax;
}