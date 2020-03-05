





#ifndef __STORETOFLASH
#define __STORETOFLASH

#include <Arduino.h>


extern void initSaveToFlash(void);
extern void restoreDatasfromFlash(void);
extern void saveDatasToFlash(void);
extern boolean savetoFlashNeeded(void);
extern void displayStoredDatasStructure(void);



#endif