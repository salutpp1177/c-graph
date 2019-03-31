#include "OperationForGraph.h"


COperationForGraph::COperationForGraph()
{
}


COperationForGraph::~COperationForGraph()
{
}

void COperationForGraph::OPRReverseGraph(CGraph & paramGraph)
{
	unsigned int iGRAnbrSommets = paramGraph.GRAGetnbrSommets();
	unsigned int iGRAnbrArcs = paramGraph.GRAGetnbrArcs();
	CSommet ** paramSom = paramGraph.GRAGetSommets();
	unsigned int ** paramArc = (unsigned int **)malloc((size_t)iGRAnbrArcs * sizeof(unsigned int*));
	if (paramArc == nullptr)
	{
		throw Exception(AllocationFail);
	}
	for (unsigned int i = 0; i < iGRAnbrArcs; i++)
	{
		paramArc[i] = (unsigned int *)malloc(2 * sizeof(unsigned int *));
	}
	unsigned int iLoop1, iLoop2, iLoop3 = 0;
	//cout<< iGRAnbrArcs << endl;
	for (iLoop1 = 0; iLoop1 < iGRAnbrSommets; iLoop1++)
	{
		iLoop2 = 0;
		while (paramSom[iLoop1]->SOMGetArrive()[iLoop2] != nullptr)
		{
			paramArc[iLoop3][0] = paramSom[iLoop1]->SOMGetArrive()[iLoop2]->ARCGetDestination();
			paramArc[iLoop3][1] = paramSom[iLoop1]->SOMGetNumber();
			iLoop2++;
			iLoop3++;
		}
	}

	for (iLoop1 = 0; iLoop1 < iLoop3; iLoop1++)
	{
		paramGraph.GRADeleteArc(paramArc[iLoop1][0], paramArc[iLoop1][1]);
		paramGraph.GRAAddArc(paramArc[iLoop1][1], paramArc[iLoop1][0]);
	}
}
