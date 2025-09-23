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

/**
 * @brief Dividing an unsigned 32bit number by an unsigned 16 bit number
 * @details The function uses the divisor instruction. The result is an uint32.
 *          The function also rounds the remainder.
 * @param dividend, 32 bit unsigned value
 * @param divisor, 16 bit unsigned value
 * @return 32 bit unsigned value
 */
extern uint32 divU32byU16toU32(uint32 dividend, uint16 divisor);

/**
 * @brief Dividing an unsigned 32bit number by an unsigned 16 bit number
 * @details The function uses the divisor instruction. The result is an uint16 so the result must be small enough to fit in.
 *          The function also rounds the remainder.
 * @param dividend, 32 bit unsigned value
 * @param divisor, 16 bit unsigned value
 * @return 16 bit unsigned value
 */
extern uint16 divU32byU16toU16(uint32 dividend, uint16 divisor);

extern int32 divS32byS16toS32(int32 dividend, int16 divisor);

extern uint8 Dabler16Bit(uint16 value, uint8 *Digits);

extern uint8 Dabler16Bit(uint16 value, uint8 *digits);

#endif	/* ASMFUNCTIONS_H */

