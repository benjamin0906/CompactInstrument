/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H

#include "types.h"

typedef struct sPort
{
    uint16 TRIS;
    uint16 PORT;
    uint16 LAT;
    uint16 ODC;
    uint16 CNEN;
    uint16 CNPU;
    uint16 CNPD;
    uint16 ANSEL;
} dtPort;

typedef struct sPorts
{
    dtPort P[2];
} dtPorts;

typedef struct sRpors
{
    uint8 RPOR_L[16];
    uint16 :16;
    uint16 :16;
    uint16 :16;
    uint16 :16;
    uint16 :16;
    uint16 :16;
    uint16 :16;
    uint16 :16;
    uint8 RPOR_H[6];
} dtRpors;

typedef struct sRpinrs
{
    uint8 R[86];
} dtRpinrs;

#define PORTS ((dtPorts*)0x0E00)
#define RPORS ((dtRpors*)0x0670)
#define RPINRS ((dtRpinrs*)0x6A0)

#endif	/* XC_HEADER_TEMPLATE_H */

