#pragma once
#ifndef _CARC_H_
#define _CARC_H_

#include <cstring>
#include <iostream>
#include "Exception.h"
using namespace std;
class CArc
{
private:
	unsigned int uiARCDestination; /**< The number of sommet which is the destination pointed by the arc*/
public:
	CArc();
	CArc(CArc & paramArc); 
	CArc(unsigned int paramDest);
	~CArc();
	unsigned int ARCGetDestination();
	void ARCSetDestination(unsigned int paramDest);
};

#endif

