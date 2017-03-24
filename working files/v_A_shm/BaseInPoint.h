#pragma once

typedef struct tag_FUOutInfoListElem{
	char chTypeFUnit;  // Type functional Unit Point Overcurrent Protection
	char chOrderNumFUnit;//Order number FUnit
	short shOrderNumOutFUnit;//
	
}FUOutInfo;//This is ID Link

extern short shOrdNumBaseInPoint;
class BaseInPoint//Dobavit' 'C'
{
public:
	BaseInPoint(void);
	~BaseInPoint(void);
	BaseInPoint(BaseInPoint&);
	BaseInPoint(char chM,char chI,char chS,char chR);
	BaseInPoint& operator= (const BaseInPoint&);
	char chMaxIteratoin;
	char chIteration;
	char chState;
	char chReqCalc;
	short shOrderNumber;
	//static short shOrdNumBaseInPoint;
};
#define SIZE_BASE_IN_POINT sizeof(BaseInPoint)
typedef union 
{

			char   chArRamPrgEvt [SIZE_BASE_IN_POINT];
	    	long    lArRamPrgEvt [SIZE_BASE_IN_POINT>>2];

			//struct
			//{
			//	
			//}BaseInPointData;
			BaseInPoint mBaseInPoint();
       
}UNN_BaseInPointArea;

