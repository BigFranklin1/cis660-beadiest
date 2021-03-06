#pragma once
#include <maya/MPxNode.h>

#include "cylinder.h"
#include "LSystem.h"
#include <string.h>

#include <maya/MPxCommand.h>
#include <maya/MTime.h>
#include <maya/MFnMesh.h>
#include <maya/MPoint.h>
#include <maya/MFloatPoint.h>
#include <maya/MFloatPointArray.h>
#include <maya/MIntArray.h>
#include <maya/MDoubleArray.h>
#include "cylinder.h"
#include "LSystem.h"
#include "Mesh.h"
#include <maya/MItMeshPolygon.h>
#include <maya/MSelectionList.h>
#include <maya/MDagPath.h>
#include <maya/MItMeshVertex.h>
#include <maya/MItMeshEdge.h>
#include <maya/MGlobal.h>

#include <maya/MTime.h>
#include <maya/MFnMesh.h>
#include <maya/MPoint.h>
#include <maya/MFloatPoint.h>
#include <maya/MFloatPointArray.h>
#include <maya/MIntArray.h>
#include <maya/MDoubleArray.h>

#include <maya/MFnUnitAttribute.h>
#include <maya/MFnTypedAttribute.h>
#include <maya/MFnNumericAttribute.h>

#include <maya/MObject.h>
#include <maya/MPlug.h>
#include <maya/MDataBlock.h>
#include <maya/MFnMeshData.h>
#include <maya/MIOStream.h>

#include <maya/MFnUnitAttribute.h>
#include <maya/MFnTypedAttribute.h>
#include <maya/MFnNumericAttribute.h>

#include <maya/MObject.h>
#include <maya/MPlug.h>
#include <maya/MDataBlock.h>
#include <maya/MFnMeshData.h>
#include <maya/MIOStream.h>

#define McheckErr(stat,msg)             \
        if ( MS::kSuccess != stat ) {   \
                cerr << msg;            \
                return MS::kFailure;    \
        }

class ToHexNode :
	public MPxNode
{
public:
	ToHexNode() {};
	virtual ~ToHexNode() {};
	virtual MStatus compute(const MPlug& plug, MDataBlock& data);
	static void* creator();
	static MStatus initialize();

	static MTypeId id;
	static MObject time;
	static MObject angle;
	static MObject step_size;
	static MObject grammarFile;
	static MObject outputMesh;
	static MObject inputMesh;

protected:
	MObject createMesh(MObject& inMesh, const MTime& time, const float& angle, const float &step, const MString& grammar, MObject& outData, MStatus& stat);


};

