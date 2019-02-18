#ifndef __LIBRARY_H
#define __LIBRARY_H

#ifdef BUILDINGDLL 
//#define DECLSPEC __declspec(dllexport)
#else
//#define DECLSPEC __declspec(dllimport)
#endif 

float usefulFunction(float a,float b);

#endif
