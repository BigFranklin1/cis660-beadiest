#pragma once
#include <maya/MPxCommand.h>
#include <maya/MFnPlugin.h>
#include <maya/MIOStream.h>
#include <maya/MString.h>
#include <maya/MArgList.h>
#include <maya/MGlobal.h>
#include <maya/MSimple.h>
#include <maya/MDoubleArray.h>
#include <maya/MPoint.h>
#include <maya/MPointArray.h>
#include <maya/MFnNurbsCurve.h>
#include <maya/MDGModifier.h>
#include <maya/MPlugArray.h>
#include <maya/MVector.h>
#include <maya/MFnDependencyNode.h>
#include <maya/MStringArray.h>
#include <maya/MSyntax.h>
#include <list>

#include "MeshBeautification.h"
#include "ToHexCmd.h"
#include "LSystemNode.h"


MStatus initializePlugin(MObject obj)
{
	MStatus   status = MStatus::kSuccess;
	MFnPlugin plugin(obj, "MyPlugin", "1.0", "Any");

	// Register Command
	status = plugin.registerCommand("beautification", MeshBeautification::creator);
	if (!status) {
		status.perror("registerCommand ToHexCmd");
		return status;
	}

	plugin.setName("beadiest");

	/*status = plugin.registerNode("LSystemNode", LSystemNode::id, LSystemNode::creator, LSystemNode::initialize);
	if (!status) {
		CHECK_MSTATUS_AND_RETURN_IT(status);
	}*/

	char buffer[2048];
	std::string s = plugin.loadPath().asChar();
	sprintf_s(buffer, 2048, "source \"%s/Beadiest\";", plugin.loadPath().asChar());
	MGlobal::executeCommand(buffer, true);

	return status;
}

MStatus uninitializePlugin(MObject obj)
{
	MStatus   status = MStatus::kSuccess;
	MFnPlugin plugin(obj);

	status = plugin.deregisterCommand("beautification");
	if (!status) {
		status.perror("deregisterCommand beautification");
		return status;
	}

/*	status = plugin.deregisterNode(LSystemNode::id);
	if (!status) {
		CHECK_MSTATUS_AND_RETURN_IT(status);
	}*/

	return status;
}