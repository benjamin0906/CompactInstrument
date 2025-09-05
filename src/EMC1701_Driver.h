/* 
 * File:   EMC1701_Driver.h
 * Author: Benjamin
 *
 * Created on 15 August 2025, 18:13
 */

#ifndef EMC1701_DRIVER_H
#define	EMC1701_DRIVER_H

extern int32 EMC1701_Driver_GetResVolt(void);
extern uint32 EMC1701_Driver_GetSrcVolt(void);
extern uint8 EMC1701_Driver_GetRange(void);
extern void EMC1701_Driver_Turn(uint8 on);
extern void EMC1701_Driver_Runnable(void);

#endif	/* EMC1701_DRIVER_H */

