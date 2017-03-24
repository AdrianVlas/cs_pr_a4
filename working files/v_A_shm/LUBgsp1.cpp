#ifndef LU_BGS_SCHEMATIC_DSC_CONST_C
#define LU_BGS_SCHEMATIC_DSC_CONST_C

const short arShOffsets[TOTAL_BGS_LU_CALC_POINT] = {
OFFSET_OUT_EvalDeltaIbus_1,
OFFSET_OUT_StoreIfixTimeFix_1,
OFFSET_OUT_D_TRG_03__3_2,
OFFSET_OUT_TIMER_04_1_1,  
OFFSET_OUT_OR_05__2_1,
OFFSET_OUT_And06__2_1,
OFFSET_OUT_Not07__1_1,
OFFSET_OUT_EvalDeltaIbusFix_3_1,
OFFSET_OUT_TDELAY_1_1,
OFFSET_OUT_Not10__1_1,
OFFSET_OUT_And11__2_1,
OFFSET_OUT_And12__2_1,
OFFSET_OUT_And13__2_1,
OFFSET_OUT_And14__2_1,
OFFSET_OUT_EvalNNC_NCH_1,
OFFSET_OUT_EvalNNP_NCH_1,
OFFSET_OUT_EvalNNC_CH_1 ,
OFFSET_OUT_EvalNNP_CH_1 ,
OFFSET_OUT_EvalCE_1,
OFFSET_OUT_EvalOC_1,
OFFSET_OUT_EvalIptp_1, 
OFFSET_OUT_EvalIctc_1,
OFFSET_OUT_MUX21_3_1,
OFFSET_OUT_MUX22_3_1,
OFFSET_OUT_EvalNNP_1,
OFFSET_OUT_EvalNNM_1,
OFFSET_OUT_EvalNCC_1,
TOTAL_BGS_LU_CALC_POINT
};


//RS_12__2_2 ,
const LUShcemasInDataDsc arDTrg_03__3_2InDataDsc[3] = {
{BGS_VCC, 0},{EvalDeltaIbus_1, 0},{TIMER_04_1_1,0}//not Led In
};
const LUShcemasDscRecord DTrg_03__3_2DscRec = {
3,2,LU_GEN_OP_D_TRIGGER_TYPE3,
&arDTrg_03__3_2InDataDsc[0]
}; 

//OR_05__2_1 ,
const LUShcemasInDataDsc arOr_05__2_1InDataDsc[2] = {
{And06__2_1, 0},{TDELAY_1_1,0}//not Led In
};
const LUShcemasDscRecord Or_05__2_1DscRec = {
2,1,LU_GEN_OP_OR,
&arOr_05__2_1InDataDsc[0]
}; 
//And06__2_1 ,
const LUShcemasInDataDsc arAnd06__2_1InDataDsc[2] = {
{Not07__1_1, 0},{D_TRG_03__3_2,0}
};
const LUShcemasDscRecord And06__2_1DscRec = {
2,1,LU_GEN_OP_AND,
&arAnd06__2_1InDataDsc[0]
};

const LUShcemasInDataDsc arNot07__1_1InDataDsc[1] = {
EvalDeltaIbusFix_3_1, 0
};
const LUShcemasDscRecord Not07__1_1DscRec = {
1,1,LU_GEN_OP_NOT,
&arNot07__1_1InDataDsc[0]
};

const LUShcemasInDataDsc EvDeltaIbusFix_3_1InDataDsc[1] = {
D_TRG_03__3_2, 0
};
const LUShcemasDscRecord EvDeltaIbusFix_3_1DscRec = {
1,1,LU_GEN_OP_EV_FIX_IBUS,
&arNot07__1_1InDataDsc[0]
};

//Not10__1_1,
const LUShcemasInDataDsc arNot10__1_1InDataDsc[1] = {
IN_BGS_MNU_STATE_CHECK_BGS_SELECTOR, 0
};
const LUShcemasDscRecord Not10__1_1DscRec = {
1,1,LU_GEN_OP_NOT,
&arNot10__1_1InDataDsc[0]
};


//And11__2_1 ,
const LUShcemasInDataDsc arAnd11__2_1InDataDsc[2] = {
{Not10__1_1, 0},{TDELAY_1_1,0}//not Led In
};
const LUShcemasDscRecord And11__2_1DscRec = {
2,1,LU_GEN_OP_AND,
&arAnd11__2_1InDataDsc[0]
};
//And12__2_1 ,
const LUShcemasInDataDsc arAnd12__2_1InDataDsc[2] = {
{TDELAY_1_1, 0},{Not10__1_1,0}//not Led In
};
const LUShcemasDscRecord And12__2_1DscRec = {
2,1,LU_GEN_OP_AND,
&arAnd12__2_1InDataDsc[0]
};  

//And13__2_1 ,
const LUShcemasInDataDsc arAnd13__2_1InDataDsc[2] = {
{TDELAY_1_1, 0},{Not10__1_1,0}//not Led In
};
const LUShcemasDscRecord And13__2_1DscRec = {
2,1,LU_GEN_OP_AND,
&arAnd13__2_1InDataDsc[0]
};
//And14__2_1 ,
const LUShcemasInDataDsc arAnd14__2_1InDataDsc[2] = {
{TDELAY_1_1, 0},{Not10__1_1,0}//not Led In
};
const LUShcemasDscRecord And14__2_1DscRec = {
2,1,LU_GEN_OP_AND,
&arAnd14__2_1InDataDsc[0]
};  


#endif

