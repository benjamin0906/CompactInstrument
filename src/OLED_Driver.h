/* 
 * File:   OLED_Driver.h
 * Author: Benjamin
 *
 * Created on 03 August 2025, 16:02
 */

#ifndef OLED_DRIVER_H
#define	OLED_DRIVER_H

#include "types.h"

typedef enum eOledMode
{
    OledMode_Off,
    OledMode_On
} dtOledMode;

extern void OLED_Driver_Runnable(void);
extern void OLED_Driver_Set(dtOledMode mode);

#endif	/* OLED_DRIVER_H */

