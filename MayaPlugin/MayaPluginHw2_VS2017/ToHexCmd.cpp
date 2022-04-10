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

	//MStatus status = createLSystem(20, 2, 3, "F\nF->F[+F]F[-F]F");
	
	MStatus status = convertToHex();
	MGlobal::displayInfo("ToHexCmd\n");
	setResult("ToHexCmd was executed\n");




	return status;
}

MStatus ToHexCmd::convertToHex() {

	MSelectionList sList;
	MGlobal::getActiveSelectionList(sList);
	if (sList.length() == 0)
	{
		displayError("No mesh or mesh transform specified!");
		return MS::kFailure;
	}

	// RETRIEVE THE FIRST ITEM FROM THE SELECTION LIST:
	MDagPath meshDagPath;
	sList.getDagPath(0, meshDagPath);

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