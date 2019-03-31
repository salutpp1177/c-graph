#ifndef _COPERATIONFORGRAPH_H_
#define _COPERATIONFORGRAPH_H_
#include "Arc.h"
#include <iostream>
#include "Exception.h"
#include "Sommet.h"
#include "Graph.h"
#pragma once

class COperationForGraph
{
public:
	COperationForGraph();
	~COperationForGraph();
	void OPRReverseGraph(CGraph & paramGraph);
};

#endif

