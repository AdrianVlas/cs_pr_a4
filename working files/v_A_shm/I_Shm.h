#ifndef I_SCHEMATIC_H
#define I_SCHEMATIC_H

#ifdef __cplusplus
extern "C" {
#endif



extern void  TmrCalls(void);
#ifdef __cplusplus
}
#endif
extern long CreateSchematic(void);
extern long InitSchematic(void);
extern long ReInitSchematic(void);

extern void DoCalcWrp(void);
extern void  TmrCalls(void);
#endif
