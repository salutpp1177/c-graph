#ifndef _EXCEPTION_H
#define _EXCEPTION_H


#include <iostream>
#include <cstring>

using namespace std;

#pragma once

/** List all the exceptions
 */
static enum AlltheExceptions
{
	AllocationFail, /**< Allocating memory failed. */
	PointerNull, /**< Pointer is null */
	SommetExist, /**< This sommet already exists in the graph */
	SommetNotFound, /**< Can't find this sommet */
	FailOpenFile, /**< Can not open the file */
	FileVide, /**< The file is vide */
	FileContentError, /**< There are some errors in the content of this file */
};


class Exception
{
private:
	int iEXCType; /** < A label as an exception */
public:
	Exception();
	Exception(int iType);
	~Exception();
	void EXCPrintStackTrace();
};


#endif
