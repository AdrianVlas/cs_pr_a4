#ifndef LU_LED_SCHEMATIC_DSC_CONST_C
#define LU_LED_SCHEMATIC_DSC_CONST_C

const short arShOffsets[TOTAL_LU_CALC_POINT] = {
OFFSET_OUT_IN_00_LEDIN ,
OFFSET_OUT_IN_01_RESET ,
OFFSET_OUT_IN_02_BL_IMP,
OFFSET_OUT_IN_03_C1_C2_SELECTOR ,
OFFSET_OUT_IN_04_C1  ,
OFFSET_OUT_IN_05_C2  ,

OFFSET_OUT_Not06__1_1 ,    
OFFSET_OUT_And07__2_1 ,
OFFSET_OUT_And08__2_1 ,
OFFSET_OUT_And09__2_1 ,
OFFSET_OUT_Or_10__2_1 ,
OFFSET_OUT_Or_11__2_1 ,
OFFSET_OUT_RS_12__2_2 ,
OFFSET_OUT_And13__2_1 ,
OFFSET_OUT_And14__2_1 ,
   
OFFSET_OUT_And15__2_1 ,
OFFSET_OUT_And16__2_1 ,
OFFSET_OUT_Or_17__2_1 ,
OFFSET_OUT_Or_18__2_1 ,
   
OFFSET_OUT_Not19__1_1 ,
OFFSET_OUT_And20__3_1 ,
OFFSET_OUT_And21__3_1 ,
OFFSET_OUT_Or_22__3_1 ,
OFFSET_OUT_And23__2_1 ,
OFFSET_OUT_And24__2_1 ,
OFFSET_OUT_Or_25__2_1 ,

OFFSET_OUT_IN_MNU_NORMAL_SELECTOR ,
OFFSET_OUT_IN_MNU_TRIGGER_SELECTOR,
OFFSET_OUT_IN_MNU_STABLE_SELECTOR,
OFFSET_OUT_IN_MNU_PULSE_SELECTOR,
OFFSET_OUT_IN_MNU_PULSE_SIMPLE_SELECTOR,
OFFSET_OUT_IN_MNU_PULSE_EXTANDED_SELECTOR,

TOTAL_LU_CALC_POINT
};



//IN_00_LEDIN  ,

//IN_01_RESET  ,

//IN_02_BL_IMP ,

//IN_03_C1_C2_SELECTOR,

//IN_04_C1   ,

//IN_05_C2   ,

//Not06__1_1 ,
const LUShcemasInDataDsc arNot06__1_1InDataDsc[1] = {
IN_00_LEDIN, 0
};
const LedShcemasDscRecord Not06__1_1DscRec = {
1,1,LU_GEN_OP_NOT,
&arNot06__1_1InDataDsc[0]
};
//And07__2_1 ,
const LUShcemasInDataDsc arAnd07__2_1InDataDsc[2] = {
{IN_00_LEDIN, 0},{IN_MNU_NORMAL_SELECTOR,0}
};

const LedShcemasDscRecord And07__2_1DscRec = {
2,1,LU_GEN_OP_AND,
&arAnd07__2_1InDataDsc[0]
};



//And08__2_1 ,
const LUShcemasInDataDsc arAnd08__2_1InDataDsc[2] = {
{IN_00_LEDIN, 0},{IN_MNU_TRIGGER_SELECTOR,0}
};
const LedShcemasDscRecord And08__2_1DscRec = {
2,1,LU_GEN_OP_AND,
&arAnd08__2_1InDataDsc[0]
};

//And09__2_1 ,
const LUShcemasInDataDsc arAnd09__2_1InDataDsc[2] = {
{IN_01_RESET, 0},{Not06__1_1,0}//not Led In
};
const LedShcemasDscRecord And09__2_1DscRec = {
2,1,LU_GEN_OP_AND,
&arAnd09__2_1InDataDsc[0]
};
//Or_10__2_1 ,

const LUShcemasInDataDsc arOr_10__2_1InDataDsc[2] = {
{IN_MNU_PULSE_SIMPLE_SELECTOR, 0},{IN_MNU_PULSE_EXTANDED_SELECTOR,0}//not Led In
};
const LedShcemasDscRecord Or_10__2_1DscRec = {
2,1,LU_GEN_OP_OR,
&arOr_10__2_1InDataDsc[0]
}; 

//Or_11__2_1 ,
const LUShcemasInDataDsc arOr_11__2_1InDataDsc[2] = {
{And07__2_1, 0},{RS_12__2_2,0}//not Led In
};
const LedShcemasDscRecord Or_11__2_1DscRec = {
2,1,LU_GEN_OP_OR,
&arOr_11__2_1InDataDsc[0]
}; 

//RS_12__2_2 ,
const LUShcemasInDataDsc arRS_12__2_2InDataDsc[2] = {
{And08__2_1, 0},{And09__2_1,0}//not Led In
};
const LedShcemasDscRecord RS_12__2_2DscRec = {
2,2,LU_GEN_OP_RS_TRIGGER,
&arRS_12__2_2InDataDsc[0]
}; 
//And13__2_1 ,
const LUShcemasInDataDsc arAnd13__2_1InDataDsc[2] = {
{IN_MNU_PULSE_SELECTOR, 0},{IN_02_BL_IMP,0}//not Led In
};
const LedShcemasDscRecord And13__2_1DscRec = {
2,1,LU_GEN_OP_AND,
&arAnd13__2_1InDataDsc[0]
};
//And14__2_1 ,
const LUShcemasInDataDsc arAnd14__2_1InDataDsc[2] = {
{IN_MNU_PULSE_EXTANDED_SELECTOR, 0},{IN_03_C1_C2_SELECTOR,0}//not Led In
};
const LedShcemasDscRecord And14__2_1DscRec = {
2,1,LU_GEN_OP_AND,
&arAnd14__2_1InDataDsc[0]
};   
//And15__2_1,
const LUShcemasInDataDsc arAnd15__2_1InDataDsc[2] = {
{IN_MNU_STABLE_SELECTOR, 0},{Or_11__2_1,0}//not Led In
};
const LedShcemasDscRecord And15__2_1DscRec = {
2,1,LU_GEN_OP_AND,
&arAnd15__2_1InDataDsc[0]
}; 
//And16__2_1,
const LUShcemasInDataDsc arAnd16__2_1InDataDsc[2] = {
{IN_MNU_PULSE_SELECTOR, 0},{Or_11__2_1,0}//not Led In
};
const LedShcemasDscRecord And16__2_1DscRec = {
2,1,LU_GEN_OP_AND,
&arAnd16__2_1InDataDsc[0]
}; 
//Or_17__2_1,
const LUShcemasInDataDsc arOr_17__2_1InDataDsc[2] = {
{And13__2_1, 0},{IN_04_C1,0}//not Led In
};
const LedShcemasDscRecord Or_17__2_1DscRec = {
2,1,LU_GEN_OP_OR,
&arOr_17__2_1InDataDsc[0]
}; 

//Or_18__2_1,
const LUShcemasInDataDsc arOr_18__2_1InDataDsc[2] = {
{And13__2_1, 0},{IN_05_C2 ,0}//not Led In
};
const LedShcemasDscRecord Or_18__2_1DscRec = {
2,1,LU_GEN_OP_OR,
&arOr_18__2_1InDataDsc[0]
}; 
  
//Not19__1_1,
const LUShcemasInDataDsc arNot19__1_1InDataDsc[1] = {
And14__2_1, 0
};
const LedShcemasDscRecord Not19__1_1DscRec = {
1,1,LU_GEN_OP_NOT,
&arNot19__1_1InDataDsc[0]
};
//And20__3_1,
const LUShcemasInDataDsc arAnd20__3_1InDataDsc[3] = {
{And16__2_1, 0},{Or_17__2_1,0},{Not19__1_1,0}//not Led In
};
const LedShcemasDscRecord And20__3_1DscRec = {
3,1,LU_GEN_OP_AND,
&arAnd20__3_1InDataDsc[0]
};
//And21__3_1,
const LUShcemasInDataDsc arAnd21__3_1InDataDsc[3] = {
{And16__2_1, 0},{Or_18__2_1,0},{And14__2_1,0}//not Led In
};
const LedShcemasDscRecord And21__3_1DscRec = {
3,1,LU_GEN_OP_AND,
&arAnd21__3_1InDataDsc[0]
};
//Or_22__3_1,
const LUShcemasInDataDsc arOr22__3_1InDataDsc[3] = {
{And15__2_1, 0},{And20__3_1,0},{And21__3_1,0}//not Led In
};
const LedShcemasDscRecord Or22__3_1DscRec = {
3,1,LU_GEN_OP_OR,
&arOr22__3_1InDataDsc[0]
};
//And23__2_1,

//And24__2_1,

//Or_25__2_1,

const LedShcemasDscRecord* const arPLedShcemasDscRecords[] = {
&Not06__1_1DscRec,
&And07__2_1DscRec,
&And08__2_1DscRec,
&And09__2_1DscRec ,
&Or_10__2_1DscRec ,
&Or_11__2_1DscRec ,
&RS_12__2_2DscRec ,
&And13__2_1DscRec ,
&And14__2_1DscRec ,
&And15__2_1DscRec ,
&And16__2_1DscRec ,
&Or_17__2_1DscRec ,
&Or_18__2_1DscRec ,
&Not19__1_1DscRec ,
&And20__3_1DscRec ,
&And21__3_1DscRec ,
&Or22__3_1DscRec
};

#endif
