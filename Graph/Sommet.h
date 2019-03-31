#ifndef _CSOMMET_H_
#define _CSOMMET_H_

#include "Arc.h"
#include <iostream>
#include "Exception.h"

#pragma once

using namespace std;
class CSommet
{
private:
	unsigned int uiSOMNumber; /**< The number of this sommet */
	CArc **pcSOMDepart; /**< The list of the arcs which is the depart of this sommet */
	CArc **pcSOMArrive; /**< The list of the arcs which is the arrive of this sommet */
	unsigned int uiSOMnbrArcDepart; /**< accounting the number of arc-depart list from one sommet */
	unsigned int uiSOMnbrArcArrive; /**< accounting the number of arc-arrive list from one sommet */
	
public:
	CSommet();
	CSommet(CSommet & paramSommet);
	CSommet(unsigned int uiNum);
	CSommet(unsigned int uiNum, CArc** paramDept, CArc** paramArrv);
	~CSommet();

	unsigned int SOMGetNumber();
	unsigned int SOMGetnbrArcDepart();
	unsigned int SOMGetnbrArcArrive();
	CArc** SOMGetDepart() const;
	CArc** SOMGetArrive() const;
	void SOMAddDepart(unsigned int uiNum);
	void SOMAddArrive(unsigned int uiNum);
	void SOMModifySOMNumber(unsigned int uiNum);
	void SOMModifyDepart(unsigned int uiNum, CArc* paramArc);
	void SOMModifyArrive(unsigned int uiNum, CArc* paramArc);
	void SOMDeleteDepart(unsigned int uiNum);
	void SOMDeleteDepart();
	void SOMDeleteArrive(unsigned int uiNum);
	void SOMDeleteArrive();

	CSommet & operator = (CSommet & paramSommet);

};


#endif
