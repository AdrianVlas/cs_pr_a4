#ifndef LU_GENERAL_OP_h
#define LU_GENERAL_OP_h

enum ID_LU_GEN_OP { 

LU_GEN_OP_AND  = 1,  
LU_GEN_OP_OR    ,  
LU_GEN_OP_XOR   ,
LU_GEN_OP_NOT,
LU_GEN_OP_RS_TRIGGER,
LU_GEN_OP_D_TRIGGER_TYPE3,
LU_GEN_OP_D_TRIGGER,
LU_GEN_OP_EV_FIX_IBUS
};


typedef struct LU_InputDataDsc_tag{
short shOrderNumLU;
short shIndexOut;
}LUShcemasInDataDsc;
typedef struct LU_SCHEMAS_DSC_Info_tag{
char chAmtIn;
char chAmtOut;
char chTypeOperation;
LUShcemasInDataDsc const *pInputDscData; 
}LedShcemasDscRecord;
typedef struct LU_SCHEMAS_DSC_Info_tagg{
char chAmtIn;
char chAmtOut;
char chTypeOperation;
LUShcemasInDataDsc const *pInputDscData; 
}LUShcemasDscRecord;


#endif
