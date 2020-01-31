


#ifndef __SIMULATION
#define __SIMULATION


#define SIMUL_TEMP_INTERIEURE         1
#define SIMUL_TEMP_EXTERIEURE         2
#define SIMUL_TEMP_SORTIE_CHAUDIERE   3
#define SIMUL_TEMP_RETOUR_CHAUDIERE   4

extern double getSimulatedValue(int type);
extern void initSimulation(void);

#endif
