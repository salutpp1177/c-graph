#ifndef _CPARSE_H_
#define _CPARSE_H_ 
#include "Arc.h"
#include "Sommet.h"
#include "Graph.h"
#include "Exception.h"
#include <iostream>
#include <fstream>
#include <istream>
#include <string>
#include <algorithm>

#pragma once
using namespace std;
class CParse
{
private:
	unsigned int uiPARnbrSommets; /**< record the number of sommets */
	unsigned int uiPARnbrArcs; /**< record the number of arcs */
	CGraph * pcGraph;
	char * cPARFilename; /**< file path */
public:
	CParse();
	// CParse(CParse & paramParse);
	CParse(const char * Filename);
	~CParse();
	unsigned int PARGetnbrSommets();
	unsigned int PARGetnbrArcs();
	CGraph * PARGetGraph() const { return pcGraph; }
	void PARReadFile();
	void PARRemoveBlanks(string & str);
};

#endif

