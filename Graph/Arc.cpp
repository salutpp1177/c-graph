#include "Arc.h"

/** The default constructor
 */
CArc::CArc()
{
	uiARCDestination = 0;
}


/** The copy constructor
 * @param paramArc An object of CArc
 */
CArc::CArc(CArc & paramArc)
{
	uiARCDestination = paramArc.ARCGetDestination();
}

/** The self-defining constructor 
 * @param paramDest An unsigned-int number which is the destination pointed by the arc
 */
CArc::CArc(unsigned int paramDest)
{
	uiARCDestination = paramDest;
}

/** The destructor
 */
CArc::~CArc(void)
{
}

/** Get the private attribute @uiARCDestination of a class CArc
 * @return an unisgined-int value of destination to CArc 
 */
unsigned int CArc::ARCGetDestination()
{
	return uiARCDestination;
}

/** Set the destination for a class of CArc
 * @param paramDest a unsigned-int value that we want to modify for a destination
 */

void CArc::ARCSetDestination(unsigned int paramDest)
{
	uiARCDestination = paramDest;
}







