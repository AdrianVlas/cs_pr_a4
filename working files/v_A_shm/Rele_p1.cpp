#ifndef LU_RELE_SCHEMATIC_DSC_CONST_C
#define LU_RELE_SCHEMATIC_DSC_CONST_C


const short arReleShOffsets[TOTAL_RELE_LU_CALC_POINT ] = {
OFFSET_OUT_RELE_Not01__1_1, 
OFFSET_OUT_RELE_And02__2_1, 
OFFSET_OUT_RELE_And03__2_1, 
OFFSET_OUT_RELE_And04__2_1, 
OFFSET_OUT_RELE_Or_05__2_1, 
OFFSET_OUT_RELE_RS_06__2_2, 
OFFSET_OUT_RELE_And07__2_1, 
OFFSET_OUT_RELE_Or_08__2_1, 
OFFSET_OUT_RELE_And09__2_1, 
OFFSET_OUT_RELE_And10__2_1, 
OFFSET_OUT_RELE_And11__2_1,
OFFSET_OUT_RELE_Or_12__2_1,
OFFSET_OUT_RELE_Or_13__2_1,
OFFSET_OUT_RELE_Not14__1_1,
OFFSET_OUT_RELE_And15__3_1,
OFFSET_OUT_RELE_And16__3_1,
OFFSET_OUT_RELE_Or_17__3_1,
OFFSET_OUT_IN_RELE_NORMAL_SELECTOR,
OFFSET_OUT_IN_RELE_TRIGGER_SELECTOR,
OFFSET_OUT_IN_RELE_STABLE_SELECTOR,
OFFSET_OUT_IN_RELE_PULSE_SELECTOR,
OFFSET_OUT_IN_RELE_PULSE_SIMPLE_SELECTOR,
OFFSET_OUT_IN_RELE_PULSE_EXTANDED_SELECTOR,
OFFSET_OUT_IN_RELE__RIN ,
OFFSET_OUT_IN_RELE__RESET,
OFFSET_OUT_IN_RELE__BL_IMP,
OFFSET_OUT_IN_RELE__C1_C2,
OFFSET_OUT_IN_RELE_C1   ,
OFFSET_OUT_IN_RELE_C2   ,
TOTAL_RELE_LU_CALC_POINT 
};

//RELE_Not01__1_1, 
const LUShcemasInDataDsc arNot01__1_1InDataDsc[1] = {
IN_RELE__RIN, 0
};
const LedShcemasDscRecord Not01__1_1DscRec = {
1,1,LU_GEN_OP_NOT,
&arNot01__1_1InDataDsc[0]
};
//RELE_And02__2_1, 
const LUShcemasInDataDsc arAnd02__2_1InDataDsc[2] = {
{IN_RELE__RIN, 0},{IN_RELE_NORMAL_SELECTOR,0}
};

const LedShcemasDscRecord And02__2_1DscRec = {
2,1,LU_GEN_OP_AND,
&arAnd02__2_1InDataDsc[0]
};

//RELE_And03__2_1, 
const LUShcemasInDataDsc arAnd03__2_1InDataDsc[2] = {
{IN_RELE__RIN, 0},{IN_RELE_TRIGGER_SELECTOR,0}
};

const LedShcemasDscRecord And03__2_1DscRec = {
2,1,LU_GEN_OP_AND,
&arAnd03__2_1InDataDsc[0]
};

//RELE_And04__2_1, 
const LUShcemasInDataDsc arAnd04__2_1InDataDsc[2] = {
{IN_RELE__RESET, 0},{RELE_Not01__1_1,0}
};

const LedShcemasDscRecord And04__2_1DscRec = {
2,1,LU_GEN_OP_AND,
&arAnd04__2_1InDataDsc[0]
};

//RELE_Or_05__2_1, 
const LUShcemasInDataDsc arOr_05__2_1InDataDsc[2] = {
{IN_RELE_PULSE_SIMPLE_SELECTOR, 0},{IN_RELE_PULSE_EXTANDED_SELECTOR,0}//not Led In
};
const LedShcemasDscRecord Or_05__2_1DscRec = {
2,1,LU_GEN_OP_OR,
&arOr_05__2_1InDataDsc[0]
}; 
//RELE_RS_06__2_2, 
const LUShcemasInDataDsc arRS_06__2_2InDataDsc[2] = {
{RELE_And03__2_1, 0},{RELE_And04__2_1,0}//not Led In
};
const LedShcemasDscRecord RS_06__2_2DscRec = {
2,2,LU_GEN_OP_RS_TRIGGER,
&arRS_06__2_2InDataDsc[0]
}; 
//RELE_And07__2_1, 
const LUShcemasInDataDsc arAnd07__2_1InDataDsc[2] = {
{IN_RELE__BL_IMP, 0},{IN_RELE_PULSE_SELECTOR,0}
};

const LedShcemasDscRecord And07__2_1DscRec = {
2,1,LU_GEN_OP_AND,
&arAnd07__2_1InDataDsc[0]
};
//RELE_Or_08__2_1, 
const LUShcemasInDataDsc arOr_08__2_1InDataDsc[2] = {
{RELE_And02__2_1, 0},{RELE_RS_06__2_2,0}//not Led In
};
const LedShcemasDscRecord Or_08__2_1DscRec = {
2,1,LU_GEN_OP_OR,
&arOr_08__2_1InDataDsc[0]
}; 
//RELE_And09__2_1, 
const LUShcemasInDataDsc arAnd09__2_1InDataDsc[2] = {
{IN_RELE__C1_C2, 0},{IN_RELE_PULSE_EXTANDED_SELECTOR,0}//not Led In
};
const LedShcemasDscRecord And09__2_1DscRec = {
2,1,LU_GEN_OP_AND,
&arAnd09__2_1InDataDsc[0]
};
//RELE_And10__2_1, 
const LUShcemasInDataDsc arAnd10__2_1InDataDsc[2] = {
{IN_RELE_STABLE_SELECTOR, 0},{RELE_Or_08__2_1,0}//not Led In
};
const LedShcemasDscRecord And10__2_1DscRec = {
2,1,LU_GEN_OP_AND,
&arAnd10__2_1InDataDsc[0]
};
//RELE_And11__2_1,
const LUShcemasInDataDsc arAnd11__2_1InDataDsc[2] = {
{IN_RELE_PULSE_SELECTOR, 0},{RELE_Or_08__2_1,0}//not Led In
};
const LedShcemasDscRecord And11__2_1DscRec = {
2,1,LU_GEN_OP_AND,
&arAnd11__2_1InDataDsc[0]
};
//RELE_Or_12__2_1,
const LUShcemasInDataDsc arOr_12__2_1InDataDsc[2] = {
{IN_RELE_C1, 0},{RELE_And07__2_1,0}//not Led In
};
const LedShcemasDscRecord Or_12__2_1DscRec = {
2,1,LU_GEN_OP_OR,
&arOr_12__2_1InDataDsc[0]
};
//RELE_Or_13__2_1,
const LUShcemasInDataDsc arOr_13__2_1InDataDsc[2] = {
{IN_RELE_C2, 0},{RELE_And07__2_1,0}//not Led In
};
const LedShcemasDscRecord Or_13__2_1DscRec = {
2,1,LU_GEN_OP_OR,
&arOr_13__2_1InDataDsc[0]
};
//RELE_Not14__1_1,
const LUShcemasInDataDsc arNot14__1_1InDataDsc[1] = {
RELE_And09__2_1, 0
};
const LedShcemasDscRecord Not14__1_1DscRec = {
1,1,LU_GEN_OP_NOT,
&arNot14__1_1InDataDsc[0]
};
//RELE_And15__3_1,
const LUShcemasInDataDsc arAnd15__3_1InDataDsc[3] = {
{RELE_And11__2_1, 0},{RELE_Or_12__2_1,0},{RELE_Not14__1_1,0}//not Led In
};
const LedShcemasDscRecord And15__3_1DscRec = {
3,1,LU_GEN_OP_AND,
&arAnd15__3_1InDataDsc[0]
};
//RELE_And16__3_1,
const LUShcemasInDataDsc arAnd16__3_1InDataDsc[3] = {
{RELE_And11__2_1, 0},{RELE_Or_13__2_1,0},{RELE_And09__2_1,0}//not Led In
};
const LedShcemasDscRecord And16__3_1DscRec = {
3,1,LU_GEN_OP_AND,
&arAnd16__3_1InDataDsc[0]
};
//RELE_Or_17__3_1,
const LUShcemasInDataDsc arOr17__3_1InDataDsc[3] = {
{RELE_And10__2_1, 0},{RELE_And15__3_1,0},{RELE_And16__3_1,0}//not Led In
};
const LedShcemasDscRecord Or17__3_1DscRec = {
3,1,LU_GEN_OP_OR,
&arOr17__3_1InDataDsc[0]
};
//IN_RELE_NORMAL_SELECTOR,

//IN_RELE_TRIGGER_SELECTOR,

//IN_RELE_STABLE_SELECTOR,

//IN_RELE_PULSE_SELECTOR,

//IN_RELE_PULSE_SIMPLE_SELECTOR,

//IN_RELE_PULSE_EXTANDED_SELECTOR,

//IN_RELE__RIN ,

//IN_RELE__RESET,

//IN_RELE__BL_IMP,

//IN_RELE__C1_C2,
const LedShcemasDscRecord* const arPReleShcemasDscRecords[] = {
&Not01__1_1DscRec,
&And02__2_1DscRec,
&And03__2_1DscRec,
&And04__2_1DscRec,
&Or_05__2_1DscRec,
&RS_06__2_2DscRec,
&And07__2_1DscRec,
&Or_08__2_1DscRec,
&And09__2_1DscRec,
&And10__2_1DscRec,
&And11__2_1DscRec,
&Or_12__2_1DscRec,
&Or_13__2_1DscRec,
&Not14__1_1DscRec,
&And15__3_1DscRec,
&And16__3_1DscRec,
&Or17__3_1DscRec 
};
 
 
#endif
