#define MNoVersionString
#define MNoPluginEntry
#include "ToHexNode.h"

MObject ToHexNode::time;
MTypeId ToHexNode::id(0x80000);
MObject ToHexNode::angle;
MObject ToHexNode::step_size;
MObject ToHexNode::grammarFile;
MObject ToHexNode::outputMesh;
MObject ToHexNode::inputMesh;

void* ToHexNode::creator()
{
	return new ToHexNode;
}

MStatus ToHexNode::initialize()
{
	MFnUnitAttribute unitAttr;
	MFnTypedAttribute typedAttr;
	MFnNumericAttribute numAttr;

	MStatus returnStatus;
	// input mesh
	ToHexNode:: inputMesh = typedAttr.create("inputMesh", "in",
		MFnData::kMesh,
		&returnStatus);
	McheckErr(returnStatus, "ERROR creating ToHexNode input attribute\n");

	// time
	ToHexNode::time = unitAttr.create("time", "tm",
		MFnUnitAttribute::kTime,
		0.0, &returnStatus);
	McheckErr(returnStatus, "ERROR creating ToHexNode time attribute\n");

	// angle
	ToHexNode::angle = numAttr.MFnNumericAttribute::create("angle",
		"a",
		MFnNumericData::kDouble,
		0.0,
		&returnStatus
	);
	McheckErr(returnStatus, "ERROR creating ToHexNode angle attribute\n");

	// step size
	ToHexNode::step_size = numAttr.MFnNumericAttribute::create("step",
		"ss",
		MFnNumericData::kDouble,
		0.0,
		&returnStatus
	);
	McheckErr(returnStatus, "ERROR creating ToHexNode step attribute\n");

	// grammar
	ToHexNode::grammarFile = typedAttr.MFnTypedAttribute::create("grammar",
		"g",
		MFnData::kString,
		&returnStatus
	);
	McheckErr(returnStatus, "ERROR creating ToHexNode grammar attribute\n");

	
	// output
	ToHexNode::outputMesh = typedAttr.create("outputMesh", "out",
		MFnData::kMesh,
		&returnStatus);
	McheckErr(returnStatus, "ERROR creating ToHexNode output attribute\n");
	//CHECK_MSTATUS(typedAttr.setKeyable(false));
	CHECK_MSTATUS(typedAttr.setStorable(false));



	returnStatus = addAttribute(ToHexNode::inputMesh);
	McheckErr(returnStatus, "ERROR add input\n");
	returnStatus = addAttribute(ToHexNode::time);
	McheckErr(returnStatus, "ERROR add time\n");
	returnStatus = addAttribute(ToHexNode::angle);
	McheckErr(returnStatus, "ERROR add angle\n");
	returnStatus = addAttribute(ToHexNode::step_size);
	McheckErr(returnStatus, "ERROR add step\n");
	returnStatus = addAttribute(ToHexNode::grammarFile);
	McheckErr(returnStatus, "ERROR add grammar\n");
	returnStatus = addAttribute(ToHexNode::outputMesh);
	McheckErr(returnStatus, "ERROR add output\n");

	returnStatus = attributeAffects(ToHexNode::inputMesh, ToHexNode::outputMesh);
	McheckErr(returnStatus, "ERROR in attributeAffects input mesh\n");
	returnStatus = attributeAffects(ToHexNode::grammarFile, ToHexNode::outputMesh);
	McheckErr(returnStatus, "ERROR in attributeAffects grammar\n");
	returnStatus = attributeAffects(ToHexNode::angle, ToHexNode::outputMesh);
	McheckErr(returnStatus, "ERROR in attributeAffects angle\n");
	returnStatus = attributeAffects(ToHexNode::step_size, ToHexNode::outputMesh);
	McheckErr(returnStatus, "ERROR in attributeAffects step size\n");
	returnStatus = attributeAffects(ToHexNode::time, ToHexNode::outputMesh);
	McheckErr(returnStatus, "ERROR in attributeAffects time\n");

	return MS::kSuccess;

}

// This function should i) get called whenever an attribute, such as time, changes,
// and ii) then recompute the output mesh. We have included a utility class for creating 
// cylinders which you may use to help create the mesh geometry.
// Don't forget to connect all the input attributes to the geometry! Test that changing every attribute from the attribute panel works correctly!

MStatus ToHexNode::compute(const MPlug& plug, MDataBlock& data)
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
		MDataHandle angleData = data.inputValue(angle, &returnStatus);
		McheckErr(returnStatus, "Error getting angle data handle\n");
		double angleVal = angleData.asDouble();

		// get step size
		MDataHandle stepData = data.inputValue(step_size, &returnStatus);
		McheckErr(returnStatus, "Error getting step data handle\n");
		double stepVal = stepData.asDouble();

		// get grammar
		MDataHandle grammarData = data.inputValue(grammarFile, &returnStatus);
		McheckErr(returnStatus, "Error getting gramnar data handle\n");
		MString gramVal = grammarData.asString();

		// get output object
		MDataHandle outputHandle = data.outputValue(outputMesh, &returnStatus);
		McheckErr(returnStatus, "ERROR getting geometry data handle\n");

		MFnMeshData dataCreator;

		MObject newOutputData = dataCreator.create(&returnStatus);

		McheckErr(returnStatus, "ERROR creating outputData");

		MObject input = inputHandle.asMesh();
		createMesh(input, timeVal, angleVal, stepVal, gramVal, newOutputData, returnStatus);
		McheckErr(returnStatus, "ERROR creating mesh");

		outputHandle.set(newOutputData);
		data.setClean(plug);

	}

	return MS::kSuccess;
}

MObject ToHexNode::createMesh(MObject& inMesh, const MTime& time, const float& angle, const float &step, const MString& grammar, MObject& outData, MStatus& stat)
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
	MPxCommand::displayInfo("convert to hex");

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

	// new points 
	MFloatPointArray centroidArray;

	// create faces
	MItMeshPolygon faceIter(inMesh);
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



		MGlobal::displayInfo(str);
		faces.push_back(f);
		id++;
	}

	//// ------------------ create new hex ------------------
	MIntArray faceConnects;
	MIntArray faceCounts;


	int numOfNewV = faces.size();
	int numOfNewF = vertices.size();

	MFloatPointArray newPoints;

	//int* face_counts = new int[numOfNewV];

	//std::vector<int> face_counts;
	//std::vector<int> face_connects;

	int numOfFaceConnects = 0;

	for (Face f : faces) {
		newPoints.append(f.centroid);
	}
	int oldVertexIndex = 0;
	for (Vertex v : vertices) {
		// the face count is dependent on  
		//face_counts[oldVertexIndex] = v.adjacentVertices.size();
		//face_counts.push_back((int)v.adjacentVertices.size());
		faceCounts.append((int)v.adjacentVertices.size());
		
		//numOfFaceConnects += face_counts[oldVertexIndex];
		//numOfFaceConnects += face_counts.at(oldVertexIndex);
		numOfFaceConnects += (int)v.adjacentVertices.size();

		oldVertexIndex++;

		for (auto adjF : v.adjacentFaces) {
			//face_connects.push_back(adjV);
			faceConnects.append(adjF);
		}
	}

	//int* face_connects = new int[numOfFaceConnects];
	//int x = 0;
	//for (Vertex v : vertices) {
	//	for (auto adjV : v.adjacentVertices) {
	//		face_connects[x] = adjV;
	//		x++;
	//	}
	//}
	//int* a = face_connects.data();
	//int* b = face_counts.data();

	// Set up and array to assign vertices from points to each face
	//MIntArray faceConnects(a, numOfFaceConnects);
	//MIntArray faceCounts(b, numOfNewF);

	MObject newMesh = meshFS.create(numOfNewV, numOfNewF, newPoints, faceCounts, faceConnects, outData, &stat);


	//----------------------Debug code -----------------------------

	// 
	MString faceCountsDebug;
	for (auto fc : faceCounts) {
		faceCountsDebug += double(fc);
		faceCountsDebug += " ";
	}
	MString faceCountsDebugArray;
	faceCountsDebugArray += faceCounts.length();
	MGlobal::displayInfo("face counts: " + faceCountsDebug + " Array Size: " + faceCountsDebugArray + " expected: " + vertices.size());
	//
	MString faceConnectsDebug;
	for (auto fc : faceConnects) {
		faceConnectsDebug += double(fc);
		faceConnectsDebug += " ";
	}
	MString faceConnectsDebugArray;
	faceConnectsDebugArray += faceConnects.length();
	MGlobal::displayInfo("face connects: " + faceConnectsDebug   + " Array Size: " + faceConnectsDebugArray + " expected: " + numOfFaceConnects);
	//
	MString noNewFacesDebug;
	noNewFacesDebug += double(numOfNewF);
	MGlobal::displayInfo("new faces: " + noNewFacesDebug);
	//
	MString noNewVerticesDebug;
	noNewVerticesDebug += double(numOfNewV);
	MGlobal::displayInfo("new vertices: " + noNewVerticesDebug);


	//delete [] face_counts;
	//delete [] face_connects;

	return newMesh;


	// --------------A cube for testing-----------------//
	//const int numFaces = 6;
	//int face_counts[numFaces] = { 4, 4, 4, 4, 4, 4 };
	//MIntArray faceCounts(face_counts, numFaces);
	//// Set up and array to assign vertices from points to each face 
	////
	//const int numFaceConnects = 24;
	//int face_connects[numFaceConnects] = { 0, 1, 2, 3,
	//										4, 5, 6, 7,
	//										3, 2, 6, 5,
	//										0, 3, 5, 4,
	//										0, 4, 7, 1,
	//										1, 7, 6, 2 };
	//MIntArray faceConnects(face_connects, numFaceConnects);



	//MFloatPointArray points;
	//float cubeSize = 1;
	//points.append(-cubeSize, -cubeSize, -cubeSize);
	//points.append(cubeSize, -cubeSize, -cubeSize);
	//points.append(cubeSize, -cubeSize, cubeSize);
	//points.append(-cubeSize, -cubeSize, cubeSize);
	//points.append(-cubeSize, cubeSize, -cubeSize);
	//points.append(-cubeSize, cubeSize, cubeSize);
	//points.append(cubeSize, cubeSize, cubeSize);
	//points.append(cubeSize, cubeSize, -cubeSize);

	////MFnMesh meshFS;
	//return meshFS.create(points.length(), faceCounts.length(),
	//	points, faceCounts, faceConnects, outData, &stat);
}
