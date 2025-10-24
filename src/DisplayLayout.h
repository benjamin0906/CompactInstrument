/* 
 * File:   DisplayLayout.h
 * Author: Benjamin
 *
 * Created on 23 October 2025, 18:44
 */

#ifndef DISPLAYLAYOUT_H
#define	DISPLAYLAYOUT_H

extern void DisplayLayout_Measurement(uint8 range, int32 currResVolt, int32 avgResVolt, uint32 CurrSrcVolt, uint32 avgSrcVolt);
extern void DisplayLayout_Init(int32 res_offset);

#endif	/* DISPLAYLAYOUT_H */

