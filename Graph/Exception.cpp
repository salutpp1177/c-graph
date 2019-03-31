#include "Exception.h"

/** The dafault constructor
 */
Exception::Exception()
{
	iEXCType = -1;
}

/** The self-defining constructor
 * @param iType a int value as a label to an exception 
 */
Exception::Exception(int iType)
{
	iEXCType = iType;
}

/** The destructor
 */
Exception::~Exception()
{
}

/** Print stack trace for these exceptions
 */
void Exception::EXCPrintStackTrace()
{
	switch (iEXCType)
	{
	case AllocationFail : cerr<<"We can't succeed in allocating the memory. "<<endl; break;
	case PointerNull : cerr<<"This pointer is NULL."<<endl; break;
	case SommetExist : cerr<<"This sommet already exists in the graph, you can't add it again. "<<endl; break; 
	case SommetNotFound : cerr<<"We can't find this sommet. "<<endl;break;
	case FailOpenFile : cerr<<"We can't open the file. "<<endl; break;
	case FileVide : cerr<<"This file is vide. "<<endl; break;
	case FileContentError : cerr<<"There are some errors in the file's content. "<<endl; break;
	default:
		break;
	}
}
