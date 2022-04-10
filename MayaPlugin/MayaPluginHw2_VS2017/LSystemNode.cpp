#define MNoVersionString
#define MNoPluginEntry
#include "LSystemNode.h"

MObject LSystemNode::time;
MTypeId LSystemNode::id(0x80000);
MObject LSystemNode::angle;
MObject LSystemNode::step_size;
MObject LSystemNode::grammarFile;
MObject LSystemNode::outputMesh;

void* LSystemNode::creator()
{
	return new LSystemNode;
}

MStatus LSystemNode::initialize()
{
	MFnUnitAttribute unitAttr;
	MFnTypedAttribute typedAttr;
	MFnNumericAttribute numAttr;

	MStatus returnStatus;

	// time
	LSystemNode::time = unitAttr.create("time", "tm",
		MFnUnitAttribute::kTime,
		0.0, &returnStatus);
	McheckErr(returnStatus, "ERROR creating LSystemNode time attribute\n");


	// angle
	LSystemNode::angle = numAttr.MFnNumericAttribute::create("angle",
		"a",
		MFnNumericData::kDouble,
		0.0,
		&returnStatus
	);
	McheckErr(returnStatus, "ERROR creating LSystemNode angle attribute\n");

	// step size
	LSystemNode::step_size = numAttr.MFnNumericAttribute::create("step",
		"ss",
		MFnNumericData::kDouble,
		0.0,
		&returnStatus
	);
	McheckErr(returnStatus, "ERROR creating LSystemNode step attribute\n");

	// grammar
	LSystemNode::grammarFile = typedAttr.MFnTypedAttribute::create("grammar",
		"g",
		MFnData::kString,
		&returnStatus
	);
	McheckErr(returnStatus, "ERROR creating LSystemNode grammar attribute\n");

	// output
	LSystemNode::outputMesh = typedAttr.create("outputMesh", "out",
		MFnData::kMesh,
		&returnStatus);
	McheckErr(returnStatus, "ERROR creating LSystemNode output attribute\n");
	//CHECK_MSTATUS(typedAttr.setKeyable(false));
	CHECK_MSTATUS(typedAttr.setStorable(false));

	returnStatus = addAttribute(LSystemNode::time);
	McheckErr(returnStatus, "ERROR add time\n");
	returnStatus = addAttribute(LSystemNode::angle);
	McheckErr(returnStatus, "ERROR add angle\n");
	returnStatus = addAttribute(LSystemNode::step_size);
	McheckErr(returnStatus, "ERROR add step\n");
	returnStatus = addAttribute(LSystemNode::grammarFile);
	McheckErr(returnStatus, "ERROR add grammar\n");
	returnStatus = addAttribute(LSystemNode::outputMesh);
	McheckErr(returnStatus, "ERROR add output\n");

	returnStatus = attributeAffects(LSystemNode::grammarFile, LSystemNode::outputMesh);
	McheckErr(returnStatus, "ERROR in attributeAffects grammar\n");
	returnStatus = attributeAffects(LSystemNode::angle, LSystemNode::outputMesh);
	McheckErr(returnStatus, "ERROR in attributeAffects angle\n");
	returnStatus = attributeAffects(LSystemNode::step_size, LSystemNode::outputMesh);
	McheckErr(returnStatus, "ERROR in attributeAffects step size\n");
	returnStatus = attributeAffects(LSystemNode::time, LSystemNode::outputMesh);
	McheckErr(returnStatus, "ERROR in attributeAffects time\n");

	return MS::kSuccess;

}

// This function should i) get called whenever an attribute, such as time, changes,
// and ii) then recompute the output mesh. We have included a utility class for creating 
// cylinders which you may use to help create the mesh geometry.
// Don't forget to connect all the input attributes to the geometry! Test that changing every attribute from the attribute panel works correctly!

MStatus LSystemNode::compute(const MPlug& plug, MDataBlock& data)
{
	MStatus returnStatus;
	if (plug == outputMesh)
	{
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

		createMesh(timeVal, angleVal, stepVal, gramVal, newOutputData, returnStatus);
		McheckErr(returnStatus, "ERROR creating mesh");

		outputHandle.set(newOutputData);
		data.setClean(plug);

	}

	return MS::kSuccess;
}

MObject LSystemNode::createMesh(const MTime& time, const float& angle, const float &step, const MString& grammar, MObject& outData, MStatus& stat)
{
	MFnMesh meshFS;
	MPointArray points;
	MIntArray faceCounts;
	MIntArray faceConnects;
	MPoint start;
	MPoint end;

	MObject pluginObj = MFnPlugin::findPlugin("LSystem");
	MFnPlugin plugin(pluginObj);
	MString grammarFilePath = plugin.loadPath() + "/plants/" + grammar;
	//cout << grammarFilePath << endl;
	//MGlobal::displayInfo(grammarFilePath);

	LSystem lsystem;
	// pass parameters for the L system
	lsystem.loadProgram(grammarFilePath.asChar());
	lsystem.setDefaultAngle(angle);
	lsystem.setDefaultStep(step);

	// vector to store all branches processed at each iteration of lsystem
	std::vector<LSystem::Branch> br;

	lsystem.process((int)time.value(), br);

	// Create mesh after final iteration
	for (int i = 0; i < br.size(); i++)
	{
		vec3 s = br.at(i).first;
		vec3 e = br.at(i).second;
		start = MPoint(s[0], s[1], s[2]);
		end = MPoint(e[0], e[1], e[2]);
		CylinderMesh cMesh = CylinderMesh(start, end);
		cMesh.appendToMesh(points, faceCounts, faceConnects);
	}

	int numVertices = points.length();
	int numFaces = faceCounts.length();


	MObject newMesh = meshFS.create(numVertices, numFaces,
		points, faceCounts, faceConnects,
		outData, &stat);

	return newMesh;
}
