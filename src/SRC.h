/* 
 * File:   SRC.h
 * Author: Benjamin
 *
 * Created on 26 July 2025, 19:37
 */

#ifndef SRC_H
#define	SRC_H

typedef struct sPllCfg
{
    /* 0: 2
     * 1: 3
     * ...
     * 31: 33 */
    uint16 N1 :5;
    
    /* 0: 2
     * 1: 4
     * 2: reserved
     * 3: 8 */
    uint16 N2 :2;
    
    /* 0: 2
     * 1: 3
     * ...
     * 511: 513 */
    uint16 M :9;
    uint16 OscSel :3;
} dtPllCfg;

extern void SRC_PllConfig(dtPllCfg cfg);

#endif	/* SRC_H */

