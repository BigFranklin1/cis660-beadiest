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
	static MObject time;
	static MObject angle;
	static MObject step_size;
	static MObject grammarFile;
	static MObject outputMesh;
	static MObject inputMesh;

protected:
	MObject createMesh(MObject& inMesh, const MTime& time, const float& angle, const float& step, const MString& grammar, MObject& outData, MStatus& stat);


};

