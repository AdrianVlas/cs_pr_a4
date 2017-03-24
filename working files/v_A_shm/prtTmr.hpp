#ifndef I_PRT_TIMER_HPP
#define I_PRT_TIMER_HPP

typedef struct TmrNode_t{
    long lTmrVal;
    void *next;
}TmrNode;



extern char chGlSem ;
//fix max amount available in system timers
extern const unsigned char uCh_MAX_Amt_1_MS_TMR ;
//counter for 1ms Timers <-now Reserved as is the functionaliyi should move to locals Vars
//extern short  sh1MsCtrServicedTimers;
extern short  sh1MsRegisteredTimers;//Max amount fix timers
extern TmrNode *pHeadTmrNode; //Pointer on Firsst
extern TmrNode *pTailTmrNode;
extern TmrNode *PCurrNode;

#ifdef __cplusplus
extern "C" {
#endif

//Semafor for Stop Processing
extern long RegisterTimer(TmrNode *pNode);

//Iterating over a list void print_list(node_t * head)
//All Insert Functions Return Registered Number 0-False
//All Dell Functions Return old Registered Number If Ok 0-False
//Adding an item to the end of the list
extern long TallingList(TmrNode *pNode);
//Adding an item to the beginning of the list (pushing to the list)
extern long PushTmrNode(TmrNode *pNode);
//Adding an item to the special position of the list (cutting to the list)
extern long IncreaseTmrList(TmrNode *pNode,long lPos);
//Removing the first item (popping from the list)
extern long PopTmrNode(TmrNode *pNode);
//Removing the last item of the list
extern long CuttingList(TmrNode *pNode);
//Removing a specific item
extern long DecreaseTmrList(TmrNode *pNode,long lPos);

#ifdef __cplusplus
}
#endif



//counter for 2ms Timers
//Pointer on Firsst

//counter for 5ms Timers
//Pointer on Firsst

//counter for 10 ms Timers
//Pointer on Firsst

//counter for 50 ms Timers
//Pointer on Firsst

//counter for 100 ms Timers
//Pointer on Firsst




#endif

