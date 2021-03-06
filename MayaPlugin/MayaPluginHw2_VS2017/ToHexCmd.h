#pragma once
#ifndef CreateToHexCmd_H_
#define CreateToHexCmd_H_

#include <maya/MPxCommand.h>
#include <string>
#include <maya/MSyntax.h>
#include <maya/MArgDatabase.h>
#include <maya/MGlobal.h>
#include <maya/MItMeshPolygon.h>
#include <maya/MSelectionList.h>
#include <maya/MDagPath.h>
#include <maya/MItMeshVertex.h>
#include <maya/MItMeshEdge.h>
#include <Mesh.h>
#include <maya/MFloatPointArray.h>
#include <string.h>
#include <maya/MFnMesh.h>
#include <maya/MFnMeshData.h>
#include <maya/MDataHandle.h>


#include <list>
#include <sstream>
#include "LSystem.h"


#define STEPSIZE "-ss"
#define STEPSIZELONG "-step"
#define ANGLE "-a"
#define ANGLELONG "-angle"
#define GRAMMAR "-g"
#define GRAMMARLONG "-grammar"
#define ITER "-i"
#define ITERLONG "-iter"

class ToHexCmd : public MPxCommand
{
public:

	ToHexCmd();
	virtual ~ToHexCmd();
	static void* creator() { return new ToHexCmd(); }
	MStatus doIt(const MArgList& args);
	MStatus createLSystem(double angle, double stepSize, double iter, MString grammar);
	MStatus convertToHex();
	MSyntax newSyntax();

	static MObject  outputMesh;
	static MObject  inputMesh;

};


#endif