

#ifndef __REGULATION
#define __REGULATION


#include <Arduino.h>

extern boolean chauffageAllume;
extern boolean interrupteurPompe;
extern double variationChauffage;

extern void regulationInit(void);
extern void regulationLoop(void);


#endif
