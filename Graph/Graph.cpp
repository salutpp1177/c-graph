#include "Graph.h"

/** The default constructor
 */
CGraph::CGraph()
{
	uiGRAnbrSommets = 0;
	uiGRAnbrArcs = 0;
	pcGRASommets = (CSommet **)malloc((size_t)(sizeof(CSommet *)));
	if (pcGRASommets == nullptr)
	{
		throw Exception(AllocationFail);
	}
	pcGRASommets[0] = nullptr;
}

/** The copy constructor
 * @param paramGraph An object of CGraph
 */
CGraph::CGraph(CGraph & paramGraph)
{
	uiGRAnbrSommets = paramGraph.GRAGetnbrSommets();
	pcGRASommets = (CSommet** )malloc((size_t)(paramGraph.GRAGetnbrSommets() + 1) * sizeof (CSommet* ));
	if (pcGRASommets == nullptr)
	{
		throw Exception(AllocationFail);
	}
	for (unsigned int i = 0; i < paramGraph.GRAGetnbrSommets(); i++)
	{
		pcGRASommets[i] = new CSommet(*(paramGraph.GRAGetSommets()[i]));
	}

	pcGRASommets[paramGraph.GRAGetnbrSommets()] = nullptr;
}

/** The defined constructor
 * @param uiNbrSom the number of sommets in this graph
 * @param uiNbrArc the number of arcs in this graph
 * @param paramSom the lists of sommets in this graph
 */
CGraph::CGraph(unsigned int uiNbrSom, unsigned int uiNbrArc, CSommet ** paramSom)
{
	uiGRAnbrSommets = uiNbrSom;
	uiGRAnbrArcs = uiNbrArc;

	pcGRASommets = (CSommet **)malloc((size_t)(uiGRAnbrSommets + 1) * sizeof (CSommet *));
	if (pcGRASommets == nullptr)
	{
		throw Exception(AllocationFail);
	}
	for (unsigned int i = 0; i < uiNbrSom; i++)
	{
		pcGRASommets[i] = new CSommet(*pcGRASommets[i]);
	}

	pcGRASommets[uiNbrSom] = nullptr;
}

/** The destructor
 */
CGraph::~CGraph()
{
	for (unsigned int i = 0; i < uiGRAnbrSommets; i++)
	{
		delete pcGRASommets[i];
	}
	free(pcGRASommets);

}

/** Get the private attribute @uiGRAnbrSommets in a class of CGraph
 * @return an unsigned-int value of the number of the sommets
 */
unsigned int CGraph::GRAGetnbrSommets()
{
	return uiGRAnbrSommets;
}

/** Get the private attribute @uiGRAnbrArcs in a class of Graph
 * @return an unsigned-int value of the number of the arcs
 */
unsigned int CGraph::GRAGetnbrArcs()
{
	return uiGRAnbrArcs;
}

/** Get the private attribute @pcGRASommets in a class of Graph
 * @return a pointor which points to the list of sommets in this graph
 */
CSommet** CGraph::GRAGetSommets() const
{
	return pcGRASommets;
}

/** Add a sommet into this graph
 * @param paramSom the sommet
 */
void CGraph::GRAAddSommet(CSommet * paramSom)
{
	//Check if the pointer is null
	if (paramSom == nullptr)
	{
		throw Exception(PointerNull);
	}
	else
	{		
		//Check if the sommet exists already
		for (unsigned int i = 0; i < GRAGetnbrSommets(); i++)
		{
			if (pcGRASommets[i]->SOMGetNumber() == paramSom->SOMGetNumber())
			{
				throw Exception(SommetExist);
			}
		}

		pcGRASommets = (CSommet **)realloc(pcGRASommets, (size_t)(uiGRAnbrSommets + 2) * sizeof(CSommet *));
		pcGRASommets[uiGRAnbrSommets] = new CSommet(*paramSom);
		pcGRASommets[uiGRAnbrSommets + 1] = nullptr;

		//Add the Arrive-Arcs of this sommet into other sommets as Depart-Arcs
		unsigned int m = 0;
		while (paramSom->SOMGetArrive()[m] != nullptr)
		{
			unsigned int uiADestNum;
			uiADestNum = paramSom->SOMGetArrive()[m]->ARCGetDestination();
			//Search the number @uiADestNum of sommet which is the destination for these Arrives-Arcs
			unsigned int iFindSom = 0;
			while (pcGRASommets[iFindSom] != nullptr && pcGRASommets[iFindSom]->SOMGetNumber() != uiADestNum)
			{
				iFindSom++;
			}
			if (pcGRASommets[iFindSom] != nullptr)
			{
				//Add these into other sommets as Depart-Arcs
				pcGRASommets[iFindSom]->SOMAddDepart(paramSom->SOMGetNumber());
			}
			else
			{
				throw Exception(SommetNotFound); 
			}
			m++; //
		}

		m = 0;
		while (paramSom->SOMGetDepart()[m] != nullptr)
		{
			unsigned int uiADeptNum;
			uiADeptNum = paramSom->SOMGetDepart()[m]->ARCGetDestination();
			//Search the number @uiADeptNum of sommet which is the departure for these Depart-Arcs
			unsigned int iFindSom = 0;
			while (pcGRASommets[iFindSom] != nullptr && pcGRASommets[iFindSom]->SOMGetNumber() != uiADeptNum)
			{
				iFindSom++;
			}
			if (pcGRASommets[iFindSom] != nullptr)
			{
				//Add these into other sommets as Arrive-Arcs
				pcGRASommets[iFindSom]->SOMAddArrive(paramSom->SOMGetNumber());
			}
			else
			{
				throw Exception(SommetNotFound); 
			}
			m++; 
		}

		uiGRAnbrArcs = uiGRAnbrArcs + paramSom->SOMGetnbrArcArrive() + paramSom->SOMGetnbrArcDepart();
		uiGRAnbrSommets = uiGRAnbrSommets + 1;
	}
}
/** Add a sommet into this graph
 * @param uiNum the number of the sommet
 */
void CGraph::GRAAddSommet(unsigned int uiNum)
{
	pcGRASommets = (CSommet **)realloc(pcGRASommets, (size_t)(GRAGetnbrSommets() + 2) * sizeof(CSommet *));
	pcGRASommets[uiGRAnbrSommets] = new CSommet(uiNum);
	pcGRASommets[uiGRAnbrSommets + 1] = nullptr;
	
	uiGRAnbrSommets = uiGRAnbrSommets + 1;

}

/** Add the arc into the graph
 * @param uiDept the departure of the arc
 * @param uiDest the destination of the arc
 */
void CGraph::GRAAddArc(unsigned int uiDept, unsigned int uiDest)
{
	unsigned int iFind = 0;
	while (pcGRASommets[iFind] != nullptr)
	{
		//Search the number of Sommet-Departure to add the arc in the destination 
		if (pcGRASommets[iFind]->SOMGetNumber() == uiDept)
		{
			pcGRASommets[iFind]->SOMAddDepart(uiDest);
			break;
		}
		iFind++;
	}

	iFind = 0;
	while (pcGRASommets[iFind] != nullptr)
	{
		//Search the number of Sommet-Destination to add the arc in the departure
		if (pcGRASommets[iFind]->SOMGetNumber() == uiDest)
		{
			pcGRASommets[iFind]->SOMAddArrive(uiDept);
			break;
		}
		iFind++;

	}

	uiGRAnbrArcs++;

}

/** Delete an arc
 * @param uiDept the departure of arc
 * @param uiDest the destination of arc
 */
void CGraph::GRADeleteArc(unsigned int uiDept, unsigned int uiDest)
{
	unsigned int iFind = 0 ;
	while (pcGRASommets[iFind] != nullptr)
	{
		//Search the number of Sommet-Departure to delete the arc in the destination
	
		if (pcGRASommets[iFind]->SOMGetNumber() == uiDept)
		{
			pcGRASommets[iFind]->SOMDeleteDepart(uiDest); 
			break; 
		}
		iFind++;
	}
		
	iFind = 0 ;
	while (pcGRASommets[iFind] != nullptr)
	{
		//Search the number of Sommet-Destination to delete the arc in the departure
		if (pcGRASommets[iFind]->SOMGetNumber() == uiDest)
		{
			pcGRASommets[iFind]->SOMDeleteArrive(uiDept);

			break; 
		}
		iFind++;
		
	}

	uiGRAnbrArcs--;
}

/** Delete a sommet 
 * param uiNum the number of sommet
 */
void CGraph::GRADeleteSommet(unsigned int uiNum)
{
	unsigned int iFind = 0;
	while (pcGRASommets[iFind] != nullptr && pcGRASommets[iFind]->SOMGetNumber() != uiNum) 
		iFind++;

	if (pcGRASommets[iFind] == nullptr) 
	{
		throw Exception(SommetNotFound); // Can't find this sommet
	}

	//Delete the Arrive-arcs
	while (pcGRASommets[iFind]->SOMGetArrive()[0] != nullptr)
	{
		unsigned int uiDept;
		uiDept = pcGRASommets[iFind]->SOMGetArrive()[0]->ARCGetDestination();
		GRADeleteArc(uiDept, pcGRASommets[iFind]->SOMGetNumber());
	}		

	//Delete the Depart-arcs
	while (pcGRASommets[iFind]->SOMGetDepart()[0] != nullptr)
	{
		unsigned int uiDest;
		uiDest = pcGRASommets[iFind]->SOMGetDepart()[0]->ARCGetDestination();
		GRADeleteArc(pcGRASommets[iFind]->SOMGetNumber(),uiDest);
	}

	/* Delete the Sommet*/
	delete pcGRASommets[iFind];
	for (unsigned int i = iFind; pcGRASommets[i] != nullptr; i++)
	{
		pcGRASommets[i] = pcGRASommets[i + 1];
	}
	uiGRAnbrSommets--;
	pcGRASommets = (CSommet **)realloc(pcGRASommets, (size_t)(uiGRAnbrSommets + 1) * sizeof(CSommet *));

}

/** Modify the sommet
 * @param uiNum
 * @param paramSom
 */
void CGraph::GRAModifySommet(unsigned int uiNum, CSommet *paramSom)
{
	GRADeleteSommet(uiNum);
	GRAAddSommet(paramSom);
}

/** Modify the sommet
 * @param uiNumOld the Old number of this sommet
 * @param unNumNew the New number of this sommet
 */
void CGraph::GRAModifySommet(unsigned int uiNumOld, unsigned int uiNumNew) {
	for (unsigned int i = 0; i < uiGRAnbrSommets; i++) 
	{
		if (pcGRASommets[i]->SOMGetNumber() == uiNumOld) 
		{
			CSommet tmp = *pcGRASommets[i];
			tmp.SOMModifySOMNumber(uiNumNew);
			GRAModifySommet(uiNumOld, &tmp);
			break;
		}
	}
}

/** Modify the arc
 * @param uiNumOldDept 
 * @param uiNumOldDest
 * @param uiNumNewDept
 * @param uiNumNewDest
 */
void CGraph::GRAModifyArc(unsigned int uiNumOldDept, unsigned int uiNumOldDest, unsigned int uiNumNewDept, unsigned int uiNumNewDest)
{
	GRADeleteArc(uiNumNewDept, uiNumOldDept);
	GRAAddArc(uiNumNewDept, uiNumNewDest);
}

/** Display the graph
 */
void CGraph::GRADispalyGraph()
{
	cout << "NBSommets = " << uiGRAnbrSommets <<endl;
	cout << "NBArcs = "<< uiGRAnbrArcs <<endl;
	cout << "Sommets = [ "<< endl ;
	for (unsigned int i = 0; i < uiGRAnbrSommets; i++)
	{
		cout << "Som["<<i<<"]Numero = "<<pcGRASommets[i]->SOMGetNumber() << endl;
	}
	cout << "]" <<endl;
	cout << "Arcs : " << endl;
	cout << "Depart -> Arrive" << endl;
	for (unsigned int j = 0; j < uiGRAnbrSommets; j++)
	{
		int m = 0 ;
		while (pcGRASommets[j]->SOMGetArrive()[m] != nullptr)
		{
			cout << pcGRASommets[j]->SOMGetArrive()[m]->ARCGetDestination() 
				<< "-------> " << pcGRASommets[j]->SOMGetNumber() << endl;
			m++;
		}
	}
}

/** Caculate the number of sommets
 */
void CGraph::GRACalnbrSommets()
{
	unsigned int iCal = 0;
	while (pcGRASommets[iCal] != nullptr)
	{
		iCal++;
	}
	uiGRAnbrSommets = iCal;
}

/** Calculate the number of the arcs
 */
void CGraph::GRACalnbrArcs()
{
	unsigned int iCal = 0;
	unsigned int i = 0;

	while (pcGRASommets[i] != nullptr)
	{
		iCal = iCal + pcGRASommets[i]->SOMGetnbrArcArrive();
		i++;
	}

	uiGRAnbrArcs = iCal;
}

CGraph & CGraph::operator=(CGraph & paramGraph)
{
	uiGRAnbrSommets = paramGraph.GRAGetnbrSommets();
	for (unsigned int i = 0; i < uiGRAnbrSommets; i++)
	{
		delete pcGRASommets[i];
	}

	free(pcGRASommets);

	pcGRASommets = (CSommet **)malloc((paramGraph.GRAGetnbrSommets() + 1) * sizeof(CSommet *));
	if (pcGRASommets == nullptr)
	{
		throw Exception(AllocationFail);
	}
	for (unsigned int j = 0; j < paramGraph.GRAGetnbrSommets(); j++)
	{
		pcGRASommets[j] = new CSommet(*paramGraph.GRAGetSommets()[j]);
	}
	pcGRASommets[uiGRAnbrSommets] = nullptr;

	return *this;
}