#include "par.h"
#include <cstddef>
Par::Par()
{
	par = NULL;
	parent = NULL;
	absolutePath = NULL;
	isLegal = false;
	canAccess = true;
}
Par::~Par()
{
	if(par == NULL)
		delete[] par;
	if(parent == NULL)
		delete[] parent;
	if(absolutePath == NULL)
		delete[] absolutePath;

}
