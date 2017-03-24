#pragma once

enum TYPE_LU_OP {
LU_OP_NULL = 1,
LU_OP_AND,
LU_OP_OR ,
LU_OP_XOR,
LU_OP_NOT,
LU_OP_MEANDR,
LU_OP_READ_DI,
LU_OP_SET_OUT,
LU_OP_SET_LED,
LU_OP_MFT
};
 void AND_Op    (void *pObj);
 void OR__Op    (void *pObj);
 void XOR_Op    (void *pObj);
 void NOT_Op    (void *pObj);
 void Meandr_Op (void *pObj);
 void Null_OP   (void *pObj);
 void READ_DI_Op(void *pObj);
 void SET_OUT_Op(void *pObj);
 void SET_LED_Op(void *pObj);
 void Mft_Op    (void *pObj);








/*
#ifndef LU_OUT_DSC
#define LU_OUT_DSC
typedef struct tag_LUInputDsc{
	short shIdLUStng  ;//Type LU Described in settings
	short shOrdNumStng;//Order Num LU Described in settings
	char  chOrdNumOut ;// this LU Out Order Num
	//char *pStateOut;
}LUOutDsc;//In future compres in BitField
#endif
*/


typedef long(*logicfnptr1)(void*pIn,void *pOut);//-  pointer to a exec function
//class CLUBase;
typedef void(*logicfnptr)(void *pObj);//-  pointer to a exec function

class BaseInPoint;
class CLUBase
{
public:
	CLUBase(void);
	~CLUBase(void);
	CLUBase(CLUBase&);
	CLUBase(char chM,char chI,char chNumIn,char chNumOut);
	CLUBase& operator= (const CLUBase&);
	void* pIn;//List Addr//BaseInPoint* pIn;//List Addr
//	struct ch{
		char chMaxIteratoin;
		char chIteration;
		char chNumInput;
		char chNumOutput;
		char chTypeLogicFunction;//enum ID_LUOp
		char chLinkSetOn;
//	};
//	struct sh{
	short shShemasIdLUStng  ;//Type LU Described in settings
	short shShemasOrdNumStng;//Order Num LU Described in settings
	short shLUBieldOrdNum;//Order Num when bield LU
//	};
	//long lIn;
	//long lOut;
	logicfnptr LogicFunc;
		//In Reference
	
	//Out Reference
	void* pOut;//List Addr//BaseInPoint* pOut;//List Addr
	void SetOrderNumber(void);
	friend void AND_Op    (void *pObj);
	friend void OR__Op    (void *pObj);
	friend void XOR_Op    (void *pObj);
	friend void NOT_Op    (void *pObj);
	friend void Meandr_Op (void *pObj);
	friend void Null_OP   (void *pObj);
	friend void READ_DI_Op(void *pObj);
	friend void SET_OUT_Op(void *pObj);
	friend void SET_LED_Op(void *pObj);
	
	friend void SetupCircutLinks(void *pLULinksInfo, void*pObj);
	static short shOrderNumberCLUBase;
};



//extern inline void Null_OP   (void *pObj);//{}
//extern inline void NOT_Op    (void *pObj);//{}
