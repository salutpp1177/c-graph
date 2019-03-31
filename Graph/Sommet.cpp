#include "Sommet.h"

/** The default constructor
 */
CSommet::CSommet()
{
	uiSOMNumber = 0;
	pcSOMArrive = (CArc **)malloc((size_t)(sizeof(CArc *)));
	if (pcSOMArrive == nullptr)
	{
		throw Exception(AllocationFail);
	}
	pcSOMDepart = (CArc **)malloc((size_t)(sizeof(CArc *)));
	if (pcSOMDepart == nullptr)
	{
		throw Exception(AllocationFail);
	}
	pcSOMArrive[0] = pcSOMDepart[0] =nullptr;
	uiSOMnbrArcArrive = 0;
	uiSOMnbrArcDepart = 0;
}

/** The copy constructor
 * @param paramSommet An object of CSommet
 */
CSommet::CSommet(CSommet & paramSommet)
{
	uiSOMNumber = paramSommet.SOMGetNumber();
	uiSOMnbrArcArrive = paramSommet.SOMGetnbrArcArrive();
	uiSOMnbrArcDepart = paramSommet.SOMGetnbrArcDepart();

	//Allocate the memory for the list of Arc-Arrive
	pcSOMArrive = (CArc **)malloc((size_t)(uiSOMnbrArcArrive + 1) * sizeof(CArc *));
	if (pcSOMArrive == nullptr)
	{
		throw Exception(AllocationFail);
	}
	pcSOMArrive[uiSOMnbrArcArrive] = nullptr;
	for (unsigned int i = 0; i < uiSOMnbrArcArrive; i++)
	{
		pcSOMArrive[i] = new CArc(*paramSommet.SOMGetArrive()[i]);
	}
 
	//Allocate the memory for the list of Arc-Depart
	pcSOMDepart = (CArc **)malloc((size_t)(uiSOMnbrArcDepart + 1) * sizeof(CArc *));
	if (pcSOMDepart == nullptr)
	{
		throw Exception(AllocationFail);
	}
	pcSOMDepart[uiSOMnbrArcDepart] = nullptr;
	for (unsigned int j = 0; j < uiSOMnbrArcDepart; j++)
	{
		pcSOMDepart[j] = new CArc(*paramSommet.SOMGetDepart()[j]);
	}
}

/** The defined constructor
 * @param uiNum the number of this sommet
 */
CSommet::CSommet(unsigned int uiNum)
{
	uiSOMNumber = uiNum;
	pcSOMArrive = (CArc **)malloc((size_t)(sizeof(CArc *)));
	if (pcSOMArrive == nullptr)
	{
		throw Exception(AllocationFail);
	}
	pcSOMDepart = (CArc **)malloc((size_t)(sizeof(CArc *)));
	if (pcSOMDepart == nullptr)
	{
		throw Exception(AllocationFail);
	}
	pcSOMArrive[0] = pcSOMDepart[0] =nullptr;
	uiSOMnbrArcArrive = 0;
	uiSOMnbrArcDepart = 0;
}

/** The defined constructor
 * @param uiNum the number of this sommet
 * @param paramDept the list of the arcs which is the depart of this sommet
 * @param paramArrv the list of the arcs which is the arrive of this sommet
 */
CSommet::CSommet(unsigned int uiNum, CArc** paramDept, CArc** paramArrv)
{
	uiSOMNumber = uiNum;
	//depart
	size_t iDept = 0;
	pcSOMDepart = (CArc **)malloc(sizeof(CArc *));
	if (pcSOMDepart == nullptr)
	{
		throw Exception(AllocationFail);
	}
	while (paramDept && paramDept[iDept] != nullptr)
	{
		pcSOMDepart =(CArc **)realloc(pcSOMDepart, (iDept + 1)*sizeof(CArc *));
		pcSOMDepart[iDept] = new CArc(*paramDept[iDept]);
		iDept++;
	}
	uiSOMnbrArcDepart = iDept;
	pcSOMDepart[iDept] = nullptr;

	//arrive
	size_t iArrv = 0;
	pcSOMArrive = (CArc **)malloc(sizeof(CArc *));
	if (pcSOMArrive == nullptr)
	{
		throw Exception(AllocationFail);
	}
	while (paramArrv && paramArrv[iArrv] != nullptr)
	{
		pcSOMArrive = (CArc **)realloc(pcSOMArrive, (iArrv + 1)*sizeof(CArc *));
		pcSOMArrive[iArrv] = new CArc(*paramArrv[iArrv]);
		iArrv++;
	}
	uiSOMnbrArcArrive = iArrv;
	pcSOMArrive[iArrv] = nullptr;

}

/** The destructor
 */
CSommet::~CSommet(void)
{
	//arrive
	for (unsigned int i = 0; i < uiSOMnbrArcArrive; i++)
	{
		if (pcSOMArrive[i] != nullptr)
		{
			delete pcSOMArrive[i];
		}
	}
	free(pcSOMArrive);

	//depart
	for (unsigned int j= 0; j < uiSOMnbrArcDepart; j++)
	{
		if (pcSOMDepart[j] != nullptr)
		{
			delete pcSOMDepart[j];
		}
	}
	free(pcSOMDepart);
}


/** Get the private attribute @uiSOMNumber of a class CSommet
 * @return an unsigned-int value of the number of this sommet
 */
unsigned int CSommet::SOMGetNumber()
{
	return uiSOMNumber;
}

/** Get the private attribute @uiSOMnbrArcArrive of a class CSommet
 * @return an unsigned-int value of list of the arcs which is the arrive of this sommet
 */
unsigned int CSommet::SOMGetnbrArcArrive()
{
	return uiSOMnbrArcArrive;
}


/** Get the private attribute @uiSOMnbrArcDepart of a class CSommet
 * @return an unsigend-int value of list of the arcs which is the arrive of this sommet
 */
unsigned int CSommet::SOMGetnbrArcDepart()
{
	return uiSOMnbrArcDepart;
}

/** Get the private attribute @pcSOMArrive of a class CSommet
 * @return a pointer which points to a list of the arcs which is the depart of this sommet
 */
CArc** CSommet::SOMGetArrive() const
{
	return pcSOMArrive;
}

/** Get the private attribute @pcSOMDepart of a class CSommet
 * @return a pointer which points to a list of the arcs which is the arrive of this sommet 
 */
CArc** CSommet::SOMGetDepart() const
{
	return pcSOMDepart;
}


/** Add an Arrive-Arc to this sommet
 * @param uiNum the number of sommet which is the destination pointed by the arc
 */
void CSommet::SOMAddArrive(unsigned int uiNum)
{
	unsigned int uiNbrArrv = SOMGetnbrArcArrive();

	pcSOMArrive = (CArc **)realloc(pcSOMArrive, (size_t)(uiNbrArrv + 2) * sizeof(CArc *));
	pcSOMArrive[uiNbrArrv] = new CArc(uiNum);
	pcSOMArrive[uiNbrArrv + 1] =nullptr;

	uiSOMnbrArcArrive = uiSOMnbrArcArrive + 1;
}

/** Add a Depart-Arc to this sommet
 * @param uiNum the number of sommet which is the destination pointed by the arc
 */
void CSommet::SOMAddDepart(unsigned int uiNum)
{
	unsigned int uiNbrDept = SOMGetnbrArcDepart();
	
	pcSOMDepart = (CArc **)realloc(pcSOMDepart, (size_t)(uiNbrDept + 2) * sizeof(CArc *));
	pcSOMDepart[uiNbrDept] = new  CArc(uiNum);
	pcSOMDepart[uiNbrDept + 1] = nullptr;
	
	uiSOMnbrArcDepart = uiSOMnbrArcDepart + 1;
} 
 
/** Modify the number of this sommet
 * @param uiNum the new set number
 */
void CSommet::SOMModifySOMNumber(unsigned int uiNum)
{
	uiSOMNumber = uiNum;
}


/** Modify an Arrive-Arc on this sommet
 * @param uiNum the number of sommet which is the destination pointed by the arc
 * @param paramArc the arc to replace
 */
void CSommet::SOMModifyArrive(unsigned int uiNum, CArc* paramArc)
{
	int i = 0;
	if (paramArc == nullptr)
	{
		throw Exception(PointerNull);
	}
	else
	{
		while (pcSOMArrive[i] != nullptr)
		{
			if (pcSOMArrive[i]->ARCGetDestination() == uiNum)
			{ 
				delete pcSOMArrive[i];
				pcSOMArrive[i] = new CArc(*paramArc);
			}
			i++;
		}
		
	}
}


/** Modify a Depart-Arc on this sommet
 * @param uiNum the number of sommet which is the destination pointed by the arc
 * @param paramArc the arc to replace
 */
void CSommet::SOMModifyDepart(unsigned int uiNum, CArc* paramArc)
{
	unsigned int i = 0;
	if (paramArc == nullptr)
	{
		throw Exception(PointerNull);
	}
	else
	{
		while (pcSOMDepart[i] != nullptr)
		{
			if (pcSOMDepart[i]->ARCGetDestination() == uiNum)
			{ 
				delete pcSOMDepart[i];
				pcSOMDepart[i] = new CArc(*paramArc);
			}
			i++;
		}
	}
}

/** Delete an Arrive-Arc according to its destination number
 * @param uiNum the number of sommet which is the destination pointed by the arc
 */
void CSommet::SOMDeleteArrive(unsigned int uiNum)
{
	unsigned int uiNbrArrv = SOMGetnbrArcArrive();
	unsigned int i = 0;
	while (pcSOMArrive[i] != nullptr)
	{
		if (pcSOMArrive[i]->ARCGetDestination() == uiNum)
		{
			delete pcSOMArrive[i];
			break;
		}
		i++;
	}

	unsigned int j = i;
	while (pcSOMArrive[j] != nullptr)
	{
		pcSOMArrive[j] = pcSOMArrive[j + 1];
		j++;
	}
	pcSOMArrive = (CArc **)realloc(pcSOMArrive, (size_t)uiNbrArrv * sizeof(CArc *));
	uiSOMnbrArcArrive = uiSOMnbrArcArrive - 1;

}

/** Delete all the Arrive-arcs in this sommet
 */
void CSommet::SOMDeleteArrive()
{
	unsigned int uiNbrArrv = SOMGetnbrArcDepart();

	for (unsigned int i = 0; i < uiNbrArrv; i++)
	{
		delete pcSOMArrive[i];
	}
	delete pcSOMArrive[uiNbrArrv];
	
	pcSOMArrive = (CArc **)malloc((size_t)(sizeof(CArc *)));
	if (pcSOMArrive == nullptr)
	{
		throw Exception(AllocationFail);
	}

	uiSOMnbrArcArrive = 0;
}

/** Delete a Depart-Arc according to its destination number
 * @param uiNum the number of sommet which is the destination pointed by the arc
 */
void CSommet::SOMDeleteDepart(unsigned int uiNum)
{
	unsigned int uiNbrDept = SOMGetnbrArcDepart();
	int i = 0;
	while (pcSOMDepart[i] != nullptr)
	{
		if (pcSOMDepart[i]->ARCGetDestination() == uiNum)
		{
			delete pcSOMDepart[i];
			break;
		}
		i++;
	}

	int j = i;
	while (pcSOMDepart[j] != nullptr)
	{
		pcSOMDepart[j] = pcSOMDepart[j + 1];
		j++;
	}
	pcSOMDepart = (CArc **)realloc(pcSOMDepart, (size_t)uiNbrDept * sizeof(CArc *));
	
	uiSOMnbrArcDepart = uiSOMnbrArcDepart - 1;
}

/** Delete all the Depart-arcs in this sommet
 */
void CSommet::SOMDeleteDepart()
{
	unsigned int uiNbrDept = SOMGetnbrArcDepart();

	for (unsigned int i = 0; i < uiNbrDept; i++)
	{
		delete pcSOMArrive[i];
	}
	delete pcSOMArrive[uiNbrDept];
	
	pcSOMDepart = (CArc **)malloc((size_t)(sizeof(CArc *)));
	uiSOMnbrArcDepart = 0;
}

/** overload the operator =
 * @return a new defined object of CSommet
 */
CSommet & CSommet::operator=(CSommet & paramSommet)
{
	uiSOMNumber = paramSommet.SOMGetNumber();
	//Arrive
	for (unsigned int i = 0; i < SOMGetnbrArcArrive(); i++)
	{
		if (pcSOMArrive[i] != nullptr)
		{
			delete pcSOMArrive[i];
		}
	}
	free(pcSOMArrive);
	
	pcSOMArrive = (CArc **)malloc((size_t)(paramSommet.SOMGetnbrArcArrive() + 1) * sizeof(CArc *));
	if (pcSOMArrive == nullptr)
	{
		throw Exception(AllocationFail);
	}
	for (unsigned int i = 0; i < paramSommet.SOMGetnbrArcArrive(); i++)
	{
		pcSOMArrive[i] = new CArc(*paramSommet.SOMGetArrive()[i]);
	}

	//Depart
	for (unsigned int j = 0; j < SOMGetnbrArcDepart(); j++)
	{
		if (pcSOMDepart[j] != nullptr)
		{
			delete pcSOMDepart[j];
		}
	}
	free(pcSOMDepart);
	
	pcSOMDepart = (CArc **)malloc((size_t)(paramSommet.SOMGetnbrArcDepart() + 1) * sizeof(CArc *));
	if (pcSOMDepart == nullptr)
	{
		throw Exception(AllocationFail);
	}
	for (unsigned int j = 0; j < paramSommet.SOMGetnbrArcDepart(); j++)
	{
		pcSOMDepart[j] = new CArc(*paramSommet.SOMGetDepart()[j]);
	}

	return *this;
}