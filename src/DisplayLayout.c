#include "types.h"
#include "OLED_Driver.h"
#include "AsmFunctions.h"

#define AVG_VALUES_POSITION 12

uint8 ExtendString(uint8 *string, uint8 extChar, uint8 toLength)
{
    uint8 len = strlen(string);
    if(len < toLength)
    {
        memcpy_inverse(&string[0], &string[toLength - len], len);
        memset(&string[0], extChar, toLength - len);
        len = toLength;
        string[len] = 0;
    }
    return len;
}

void InsertChar(uint8 *string, uint8 character, uint8 position)
{
    uint8 len = strlen(string) + 1;
    if(len > position)
    memcpy_inverse(&string[position], &string[position + 1], len - position);
    string[position] = character;
}

void DisplayLayout_Measurement(uint8 range, int32 currResVolt, int32 avgResVolt, uint32 CurrSrcVolt, uint32 avgSrcVolt)
{
    uint8 line[120];
    uint8 len = 0;
    uint8 last_lf_pos = 0;
    uint8 t = 0;
    int32 current           = divS32byS16toS32(currResVolt, 2000);
    int32 avg_current       = divS32byS16toS32(avgResVolt, 2000);
    uint16 src_voltage      = divU32byU16toU16(CurrSrcVolt, 10u);
    uint16 avg_src_voltage  = divU32byU16toU16(avgSrcVolt, 10u);
    int32 power             = divS32byS16toS32(current * src_voltage, 10000u);
    int32 avg_power         = divS32byS16toS32(avg_current * avg_src_voltage, 10000u);

    line[len++] = 'R';
    line[len++] = 'a';
    line[len++] = 'n';
    line[len++] = 'g';
    line[len++] = 'e';
    line[len++] = ':';
    len += Dabler16Bit(range, &line[len]);
    line[len++] = ' ';
    line[len++] = 'm';
    line[len++] = 'V';
    line[len++] = '\n';
    line[len++] = '\n';
    last_lf_pos = len-1;

    /* adding src voltage */
    Dabler16Bit(src_voltage, &line[len]);
    len += ExtendString(&line[len], '0', 5);
    InsertChar(line, ',', len-3);
    len++;
    line[len++] = ' ';
    line[len++] = 'V';
    while(len < (last_lf_pos + AVG_VALUES_POSITION))
    {
        line[len++] = ' ';
    }

    Dabler16Bit(avg_src_voltage, &line[len]);
    len += ExtendString(&line[len], '0', 5);
    InsertChar(line, ',', len-3);
    len++;
    line[len++] = ' ';
    line[len++] = 'V';

    line[len++] = '\n';
    line[len++] = '\n';
    last_lf_pos = len-1;

    /* adding current */
    if(current < 0)
    {
        line[len++] = '-';
        current *= -1;
    }
    t = Dabler16Bit(current, &line[len]);
    if(t == 1)
    {
        len += ExtendString(&line[len], '0', 2);
    }
    else
    {
        len += t;
    }

    InsertChar(&line[0], ',', len-1);
    len++;
    line[len++] = ' ';
    line[len++] = 'm';
    line[len++] = 'A';
    while(len < (last_lf_pos + AVG_VALUES_POSITION))
    {
        line[len++] = ' ';
    }
    if(avg_current < 0)
    {
        line[len++] = '-';
        avg_current *= -1;
    }
    t = Dabler16Bit(avg_current, &line[len]);
    if(t == 1)
    {
        len += ExtendString(&line[len], '0', 2);
    }
    else
    {
        len += t;
    }
    InsertChar(&line[0], ',', len-1);
    len++;
    line[len++] = ' ';
    line[len++] = 'm';
    line[len++] = 'A';
    line[len++] = '\n';
    line[len++] = '\n';
    last_lf_pos = len-1;

    /* adding power */
    if(power < 0)
    {
        line[len++] = '-';
        power *= -1;
    }
    t = Dabler16Bit(power, &line[len]);
    if(t < 4)
    {
        len += ExtendString(&line[len], '0', 4);
    }
    else
    {
        len += t;
    }
    InsertChar(&line[0], ',', len-3);
    len++;
    line[len++] = ' ';
    line[len++] = 'W';

    /* adding average power */
    while(len < (last_lf_pos + AVG_VALUES_POSITION))
    {
        line[len++] = ' ';
    }
    if(avg_power < 0)
    {
        line[len++] = '-';
        avg_power *= -1;
    }
    t = Dabler16Bit(avg_power, &line[len]);
    if(t < 4)
    {
        len += ExtendString(&line[len], '0', 4);
    }
    else
    {
        len += t;
    }
    InsertChar(&line[0], ',', len-3);
    len++;
    line[len++] = ' ';
    line[len++] = 'W';
    line[len++] = '\n';
    line[len++] = '\n';

    line[len++] = 0;
    OLED_Driver_PutString(line);
}

void DisplayLayout_Init(uint8 point_pos)
{
    uint8 line[32];
    uint8 len = 12;
    
    line[0] = 'I';
    line[1] = 'n';
    line[2] = 'i';
    line[3] = 't';
    line[4] = 'i';
    line[5] = 'a';
    line[6] = 'l';
    line[7] = 'i';
    line[8] = 'z';
    line[9] = 'i';
    line[10] = 'n';
    line[11] = 'g';
    point_pos &= 7;
    for(len = 12; len < (12 + point_pos); len++)
    {
        line[len] = '.';
    }
    
    line[len++] = 0;
    OLED_Driver_PutString(line);
}
