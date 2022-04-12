#pragma once

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


class MeshBeautification : public MPxCommand
{
public:
	MeshBeautification();
	virtual ~MeshBeautification();
	static void* creator() { return new MeshBeautification(); }
	MStatus doIt(const MArgList& args);
	MStatus beautification();
	MSyntax newSyntax();
};

