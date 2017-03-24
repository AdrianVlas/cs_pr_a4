
#include "Mft.h"









CMft::CMft(void):CLUBase() {
m_NodeTpause.lTmrVal = 0;
m_NodeTpause.next    = 0;
m_NodeTdelay.lTmrVal = 0;
m_NodeTdelay.next    = 0;
m_NodeTWork .lTmrVal = 0;
m_NodeTWork .next    = 0;
m_MftSuit.chTypeMft = 0;
m_MftSuit.lTpause   = 0;
m_MftSuit.lTdelay   = 0;
m_MftSuit.lTWork    = 0;
m_chLinkedTimers    = 0;
m_chStateTpause     = 0;
m_chStateTdelay     = 0;
m_chStateTWork      = 0;


}
CMft::CMft(char chM,char chI){
	chMaxIteratoin = chM;
	chIteration = chI;
	
chNumInput  = static_cast<char>(shCLUMFT_x_y_AmtIn);//
chNumOutput = static_cast<char>(shCLUMFT_x_y_AmtOut);
	
	

m_NodeTpause.lTmrVal = 0;
m_NodeTpause.next    = 0;
m_NodeTdelay.lTmrVal = 0;
m_NodeTdelay.next    = 0;
m_NodeTWork .lTmrVal = 0;
m_NodeTWork .next    = 0;
m_MftSuit.chTypeMft = 0;
m_MftSuit.lTpause   = 0;
m_MftSuit.lTdelay   = 0;
m_MftSuit.lTWork    = 0;
m_chLinkedTimers    = 0;
m_chStateTpause     = 0;
m_chStateTdelay     = 0;
m_chStateTWork      = 0;

}
CMft::~CMft(void) {
}
void CMft::UpdateCMft(void) {
//Set Input parameters
pIn = static_cast<void*>(arrPchIn);
//Set OutPut parameters
pOut = static_cast<void*>(arrOut);
//LinkMftTimers();
//pInit2LcVarArea->pCLUBase->shShemasIdLUStng =  STNG_LU_NOT;

//Set Operation
//Set Type Operation
}


long CMft::TpauseMft(long lActivKey) {
    
    register long *plTmrVal = &m_NodeTpause.lTmrVal;
    if (lActivKey) {
        if (m_chStateTpause == 0) {
            lActivKey = m_MftSuit.lTpause; //Load Timer
            *plTmrVal = lActivKey;
            if (*plTmrVal != lActivKey)
                *plTmrVal = lActivKey; //Possible Clear in Int
            m_chStateTpause = 1;
        } else {
            lActivKey = *plTmrVal;
            if (lActivKey == 0) {
                return 1; //End of Interval
            }
        }
        
    } else {
        ;
        m_chStateTpause = 0;
        *plTmrVal = 0; //m_NodeTpause.lTmrVal = 0;
    }
    return 0;
}

long CMft::TdelayMft(long lResetKey, long lInKey) {
    register long *plTmrVal = &m_NodeTdelay.lTmrVal;
	
    if (lResetKey == 0) {
        if (lInKey) {
            lInKey = m_MftSuit.lTdelay;
            *plTmrVal = lInKey;
            if (*plTmrVal != lInKey)
                *plTmrVal = lInKey; //lResetKey == 0!
			m_chStateTdelay = 1;//Activated
            return 1;
       	
        } else {
            if (m_chStateTdelay == 1) {//Activated
                lInKey = *plTmrVal;
                if (lInKey != 0)
                    return 1; //
                else {
                    lResetKey = 1;
                }
            }

        }
    }
    if (lResetKey) {
        m_chStateTdelay = 0;
        *plTmrVal = 0;
    }
    return 0;
}

long CMft::TWorkMft(long lResetKey, long lInKey) {
    register long *plTmrVal = &m_NodeTWork .lTmrVal;
	
    if (lResetKey == 0) {
        if (lInKey) {
            if (m_chStateTWork == 0) {
                lInKey = m_MftSuit.lTWork;
                *plTmrVal = lInKey;
                if (*plTmrVal != lInKey)
                    *plTmrVal = lInKey;
                m_chStateTWork = 1;
                return 1;
            } else {
                lInKey = *plTmrVal;
                if (lInKey != 0)
                    return 1; //
            }
        } else {
            if (m_chStateTWork == 1) {//Activated
                lInKey = *plTmrVal;
                if (lInKey != 0)
                    return 1; //
                else
                    lResetKey = 1;
            }
        }
    }
    if (lResetKey) {
        m_chStateTWork = 0;
        *plTmrVal = 0;
    }    
    return 0;
}

long CMft::LinkMftTimers(void) {
    register long i = 0;
    //Insert TpauseMft
    chGlSem++;
    
    if (PushTmrNode(&m_NodeTpause)) {//static_cast<void*>(
        i++;
        m_chLinkedTimers |= 2;
    }
    //Insert TdelayMft
    if (PushTmrNode(&m_NodeTdelay)) {//static_cast<void*>(
        i++;
        m_chLinkedTimers |= 4;
    }
    //Insert TWorkMft 
    if (PushTmrNode(&m_NodeTWork)) {//static_cast<void*>(
        i++;
        m_chLinkedTimers |= 8;
    }
    chGlSem--;
    return i;
}

void Mft_Op(void *pObj){

    register long i, j;
    //register char* pCh;
	CMft& rCMft = *(static_cast<CMft*>(pObj));
	i = static_cast<long>(*(rCMft.arrPchIn[0]));
	j = rCMft.TpauseMft(i);
	i = static_cast<long>(*(rCMft.arrPchIn[1]));//Reset
	if(rCMft.m_MftSuit.chTypeMft == 1){
		
		i = rCMft.TWorkMft(i,j);
	}
	else{
		i = rCMft.TdelayMft(i,j);
	}
rCMft.arrOut[0] = static_cast<char>(i);
}



