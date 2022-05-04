#pragma once
#include <maya/MPxNode.h>
#include <ToHexNode.h>

#define McheckErr(stat,msg)             \
        if ( MS::kSuccess != stat ) {   \
                cerr << msg;            \
                return MS::kFailure;    \
        }

class BeadNode :
	public MPxNode
{
public:
	BeadNode() {};
	virtual ~BeadNode() {};
	virtual MStatus compute(const MPlug& plug, MDataBlock& data);
	static void* creator();
	static MStatus initialize();

	static MTypeId id;
	static MObject beadDiv;
	static MObject time;
	static MObject outputMesh;
	static MObject inputMesh;

protected:
	MObject createMesh(MObject& inMesh, const MTime& time, const int& div, MObject& outData, MStatus& stat);


};

