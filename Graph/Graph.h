#ifndef _CGRAPH_H
#define _CGRAPH_H
#include "Arc.h"
#include <iostream>
#include "Exception.h"
#include "Sommet.h"

using namespace std;

#pragma once
class CGraph
{
private:
	CSommet ** pcGRASommets; /**< The lists of sommets */
	unsigned int uiGRAnbrSommets; /**< The number of sommets */
	unsigned int uiGRAnbrArcs; /**< The number of arcs */

public:
	CGraph();
	CGraph(CGraph & paramGraph);
	CGraph(unsigned int uiNbrSom, unsigned int uiNbrArc, CSommet ** paramSom);
	~CGraph();
	unsigned int GRAGetnbrSommets();
	unsigned int GRAGetnbrArcs();
	CSommet ** GRAGetSommets() const;
	void GRAAddSommet(CSommet * paramSom);
	void GRAAddSommet(unsigned int uiNum);
	void GRAAddArc(unsigned int uiDept, unsigned int uiDest);
	void GRADeleteSommet(unsigned int uiNum);
	void GRADeleteArc(unsigned int uiDept, unsigned int uiDest);
	void GRAModifySommet(unsigned int uiNum, CSommet *paramSom);
	void GRAModifySommet(unsigned int uiNumOld, unsigned int uiNumNew);
	void GRAModifyArc(unsigned int uiNumOldDept, unsigned int uiNumOldDest, unsigned int uiNumNewDept, unsigned int uiNumNewDest);
	void GRADispalyGraph();
	void GRACalnbrSommets();
	void GRACalnbrArcs();

	CGraph & operator=(CGraph & paramGraph);


};

#endif