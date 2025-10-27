/* 
 * File:   DisplayLayout.h
 * Author: Benjamin
 *
 * Created on 23 October 2025, 18:44
 */

#ifndef DISPLAYLAYOUT_H
#define	DISPLAYLAYOUT_H

extern void DisplayLayout_Measurement(uint8 range, int32 curr_current, int32 avg_current, uint32 CurrSrcVolt, uint32 avgSrcVolt, int32 curr_power, int32 avg_power);
extern void DisplayLayout_Init(int32 res_offset);

#endif	/* DISPLAYLAYOUT_H */

