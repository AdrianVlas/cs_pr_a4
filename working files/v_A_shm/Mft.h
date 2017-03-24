#pragma once
#include "lubase.h"
const short shCLUMFT_x_y_AmtOut = 1;
const short shCLUMFT_x_y_AmtIn  = 2;
#include "prtTmr.hpp"

typedef struct MftSuit_tag{
char chTypeMft;
long lTpause;
long lTdelay;
long lTWork;
}MftSuit;







class CMft :
public CLUBase {
public:
    CMft(void);
    ~CMft(void);
    CMft(char chM,char chI);
    char* arrPchIn[shCLUMFT_x_y_AmtIn ];//
    char  arrOut  [shCLUMFT_x_y_AmtOut];//
    long TpauseMft(long lActivKey);
    long TdelayMft(long lResetKey,long lInKey);
    long TWorkMft (long lResetKey,long lInKey);
    
    char m_chLinkedTimers; //Field bit
    char m_chStateTpause;
    char m_chStateTdelay;
    char m_chStateTWork ;
    MftSuit m_MftSuit;
    TmrNode m_NodeTpause;
    TmrNode m_NodeTdelay;
    TmrNode m_NodeTWork;

    long LinkMftTimers(void);
    void UpdateCMft(void);
    friend long SetMftSuit(void* pv);
    friend void Mft_Op(void *pObj);
};

