/* 
 * File:   AsmFunctions.h
 * Author: Benjamin
 *
 * Created on 17 August 2025, 14:26
 */

#ifndef ASMFUNCTIONS_H
#define	ASMFUNCTIONS_H

extern void memcpy(uint8 *src, uint8 *dest, uint16 len);
extern void memcpy_inverse(uint8 *src, uint8 *dest, uint16 len);
extern void memset(uint8 *dest, uint8 value, uint16 length);
extern uint16 strlen(uint8 *string);

#endif	/* ASMFUNCTIONS_H */

