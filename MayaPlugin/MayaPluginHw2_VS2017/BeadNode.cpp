#include "BeadNode.h"
#define MNoVersionString
#define MNoPluginEntry

MObject BeadNode::time;
MTypeId BeadNode::id(0x80001);
MObject BeadNode::beadDiv;
MObject BeadNode::outputMesh;
MObject BeadNode::inputMesh;

void* BeadNode::creator()
{
	return new BeadNode;
}

MStatus BeadNode::initialize()
{
	MFnUnitAttribute unitAttr;
	MFnTypedAttribute typedAttr;
	MFnNumericAttribute numAttr;

	MStatus returnStatus;
	// input mesh
	BeadNode::inputMesh = typedAttr.create("inputMesh", "in",
		MFnData::kMesh,
		&returnStatus);
	McheckErr(returnStatus, "ERROR creating ToHexNode input attribute\n");

	// time
	BeadNode::time = unitAttr.create("time", "tm",
		MFnUnitAttribute::kTime,
		0.0, &returnStatus);
	McheckErr(returnStatus, "ERROR creating ToHexNode time attribute\n");

	// angle
	BeadNode::beadDiv = numAttr.MFnNumericAttribute::create("beadDiv",
		"bd",
		MFnNumericData::kInt,
		4,
		&returnStatus
	);
	
	McheckErr(returnStatus, "ERROR creating ToHexNode angle attribute\n");


	// output
	BeadNode::outputMesh = typedAttr.create("outputMesh", "out",
		MFnData::kMesh,
		&returnStatus);
	McheckErr(returnStatus, "ERROR creating ToHexNode output attribute\n");
	//CHECK_MSTATUS(typedAttr.setKeyable(false));
	CHECK_MSTATUS(typedAttr.setStorable(false));



	returnStatus = addAttribute(BeadNode::inputMesh);
	McheckErr(returnStatus, "ERROR add input\n");
	returnStatus = addAttribute(BeadNode::time);
	McheckErr(returnStatus, "ERROR add time\n");
	returnStatus = addAttribute(BeadNode::beadDiv);
	McheckErr(returnStatus, "ERROR add angle\n");
	returnStatus = addAttribute(BeadNode::outputMesh);
	McheckErr(returnStatus, "ERROR add output\n");
	returnStatus = attributeAffects(BeadNode::inputMesh, BeadNode::outputMesh);
	McheckErr(returnStatus, "ERROR in attributeAffects input mesh\n");
	returnStatus = attributeAffects(BeadNode::beadDiv, BeadNode::outputMesh);
	McheckErr(returnStatus, "ERROR in attributeAffects angle\n");
	returnStatus = attributeAffects(BeadNode::time, BeadNode::outputMesh);
	McheckErr(returnStatus, "ERROR in attributeAffects time\n");

	return MS::kSuccess;

}

// This function should i) get called whenever an attribute, such as time, changes,
// and ii) then recompute the output mesh. We have included a utility class for creating 
// cylinders which you may use to help create the mesh geometry.
// Don't forget to connect all the input attributes to the geometry! Test that changing every attribute from the attribute panel works correctly!

MStatus BeadNode::compute(const MPlug& plug, MDataBlock& data)
{
	MStatus returnStatus;
	if (plug == outputMesh)
	{
		// input mesh
		MDataHandle inputHandle = data.inputValue(inputMesh, &returnStatus);
		McheckErr(returnStatus, "ERROR getting geometry data handle\n");

		// get time
		MDataHandle timeData = data.inputValue(time, &returnStatus);
		McheckErr(returnStatus, "Error getting time data handle\n");
		MTime timeVal = timeData.asTime();

		// get angle
		MDataHandle angleData = data.inputValue(beadDiv, &returnStatus);
		McheckErr(returnStatus, "Error getting angle data handle\n");
		int divVal = angleData.asInt();
		MString str = "div: ";
		str += divVal;



		MGlobal::displayInfo(str);
		// get output object
		MDataHandle outputHandle = data.outputValue(outputMesh, &returnStatus);
		McheckErr(returnStatus, "ERROR getting geometry data handle\n");

		MFnMeshData dataCreator;

		MObject newOutputData = dataCreator.create(&returnStatus);

		McheckErr(returnStatus, "ERROR creating outputData");

		MObject input = inputHandle.asMesh();
		createMesh(input, timeVal, divVal, newOutputData, returnStatus);
		McheckErr(returnStatus, "ERROR creating mesh");

		outputHandle.set(newOutputData);
		data.setClean(plug);

	}

	return MS::kSuccess;
}

void buildSphere(
	double                          rad,
	int                                     div,
	MPoint center,
	MPointArray& vertices,
	MIntArray& counts,
	MIntArray& connects,
	MVectorArray& normals)
	//
	// Description
	//
	//    Create circles of vertices starting with 
	//    the top pole ending with the botton pole
	//
{
	int start = vertices.length();

	double u = -M_PI_2;
	double v = -M_PI;
	double u_delta = M_PI / ((double)div);
	double v_delta = 2 * M_PI / ((double)div);

	MPoint topPole(0.0, rad, 0.0);
	MPoint botPole(0.0, -rad, 0.0);
	topPole += center;
	botPole += center;

	// Build the vertex and normal table
	//
	vertices.append(botPole);
	normals.append(botPole - MPoint::origin);
	int i;
	for (i = 0; i < (div - 1); i++)
	{
		u += u_delta;
		v = -M_PI;

		for (int j = 0; j < div; j++)
		{
			double x = rad * cos(u) * cos(v) + center[0];
			double y = rad * sin(u) + center[1];
			double z = rad * cos(u) * sin(v) + center[2];
			MPoint pnt(x, y, z);
			vertices.append(pnt);
			normals.append(pnt - MPoint::origin);
			v += v_delta;
		}
	}
	vertices.append(topPole);
	normals.append(topPole - MPoint::origin);

	// Create the connectivity lists
	//
	int vid = 1;
	int numV = 0;
	for (i = 0; i < div; i++)
	{
		for (int j = 0; j < div; j++)
		{
			if (i == 0) {
				counts.append(3);
				connects.append(start + 0);
				connects.append(start + j + vid);
				connects.append((j == (div - 1)) ? vid + start : j + vid + 1 + start);
			}
			else if (i == (div - 1)) {
				counts.append(3);
				connects.append(start + j + vid + 1 - div);
				connects.append(start + vid + 1);
				connects.append(j == (div - 1) ? start + vid + 1 - div : start + j + vid + 2 - div);
			}
			else {
				counts.append(4);
				connects.append(start + j + vid + 1 - div);
				connects.append(start + j + vid + 1);
				connects.append(j == (div - 1) ? start + vid + 1 : start + j + vid + 2);
				connects.append(j == (div - 1) ? start + vid + 1 - div : start + j + vid + 2 - div);
			}
			numV++;
		}
		vid = numV;
	}

}

void buildSphere(MPoint p1, MPoint p2, int divVal, MPointArray& vertices,
	MIntArray& counts,
	MIntArray& connects,
	MVectorArray& normals) {
	double rad = p1.distanceTo(p2) / 2;
	if (rad < 1) {
	//	return;
	}
	MPoint center = (p1 + p2) / 2;
	buildSphere(rad,
		divVal,
		center,
		vertices,
		counts,
		connects,
		normals
	);
}

MObject BeadNode::createMesh(MObject& inMesh, const MTime& time, const int& divVal,  MObject& outData, MStatus& stat)
{
	//MStatus status;
	MObject multiVertexComponent, singleVertexComponent;
	MSelectionList sList;
	MDagPath meshDagPath;
	MFnMesh meshFS;

	// 
	//MGlobal::displayInfo(str);

	MGlobal::getActiveSelectionList(sList);
	if (sList.length() == 0)
	{
		MPxCommand::displayError("No mesh or mesh transform specified!");
		stat = MS::kFailure;
	}

	// RETRIEVE THE FIRST ITEM FROM THE SELECTION LIST:
	sList.getDagPath(0, meshDagPath);

	// STORE THE MESH NAME
	MString meshName = meshDagPath.fullPathName();

	MPxCommand::displayInfo("Selected Mesh Name: " + meshName);
	MPxCommand::displayInfo("convert to bead");

	// create vertices list

	MItMeshVertex vertexIter(inMesh);
	int id = 0;
	std::vector<Vertex> vertices;//(vertexIter.count(&status));
	for (; !vertexIter.isDone(); vertexIter.next())
	{
		Vertex v;
		v.id = id;//vertexIter.index(&status);
		v.position = vertexIter.position(MSpace::kWorld, &stat);
		vertexIter.getNormal(v.normal, MSpace::kWorld);
		MIntArray adjEdges;
		vertexIter.getConnectedEdges(adjEdges);
		MIntArray adjVertices;
		vertexIter.getConnectedVertices(adjVertices);
		MIntArray adjFaces;
		vertexIter.getConnectedFaces(adjFaces);

		MPoint centroid;
		for (int i = 0; i < adjEdges.length(); i++) {
			v.adjacentEdges.push_back(adjEdges[i]);
		}
		for (int i = 0; i < adjVertices.length(); i++) {
			v.adjacentVertices.push_back(adjVertices[i]);
		}
		for (int i = 0; i < adjFaces.length(); i++) {
			v.adjacentFaces.push_back(adjFaces[i]);
		}
		vertices.push_back(v);
		id++;
	}

	// create edges
	MItMeshEdge edgeIter(inMesh);
	std::vector<Edge> edges;// (edgeIter.count(&status));
	id = 0;
	for (; !edgeIter.isDone(); edgeIter.next())
	{
		Edge e;
		e.id = id;// vertexIter.index(&status);
		e.v1Id = edgeIter.index(0, &stat);
		e.v2Id = edgeIter.index(1, &stat);
		edges.push_back(e);
		id++;
	}
	MPointArray points1;
	MIntArray faceCounts1, faceConnects1;
	MVectorArray normals1;
	for (Edge e : edges) {
		buildSphere(vertices[e.v1Id].position, vertices[e.v2Id].position, divVal,
			points1,
			faceCounts1,
			faceConnects1,
			normals1);
	}

	MObject newMesh = meshFS.create(points1.length(), faceCounts1.length(), points1, faceCounts1, faceConnects1, outData, &stat);

	return newMesh;


	
}
