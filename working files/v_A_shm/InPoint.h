#pragma once
#include "baseinpoint.h"
class InPoint :
	public BaseInPoint
{
public:
	InPoint(void);
	InPoint(char chM,char chI,char chS,char chR) :BaseInPoint( chM, chI, chS,chR){}

	~InPoint(void);
};
#define SIZE_IN_POINT sizeof(InPoint)
typedef union 
{

			char   chArRamPrgEvt [SIZE_IN_POINT];
	    	long    lArRamPrgEvt [SIZE_IN_POINT>>2];

			//struct
			//{
			//	
			//}BaseInPointData;
			InPoint mInPoint();
       
}UNN_InPointArea;

