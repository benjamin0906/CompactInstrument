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

void DisplayLayout_Measurement(uint8 range, int32 curr_current, int32 avg_current, uint32 curr_src_volt, uint32 avg_src_volt, int32 curr_power, int32 avg_power)
{
    uint8 line[120];
    uint8 len = 0;
    uint8 last_lf_pos = 0;
    uint8 t = 0;

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
    Dabler16Bit(curr_src_volt, &line[len]);
    len += ExtendString(&line[len], '0', 5);
    InsertChar(line, ',', len-3);
    len++;
    line[len++] = ' ';
    line[len++] = 'V';
    while(len < (last_lf_pos + AVG_VALUES_POSITION))
    {
        line[len++] = ' ';
    }

    Dabler16Bit(avg_src_volt, &line[len]);
    len += ExtendString(&line[len], '0', 5);
    InsertChar(line, ',', len-3);
    len++;
    line[len++] = ' ';
    line[len++] = 'V';

    line[len++] = '\n';
    line[len++] = '\n';
    last_lf_pos = len-1;

    /* adding current */
    if(curr_current < 0)
    {
        line[len++] = '-';
        curr_current *= -1;
    }
    t = Dabler16Bit(curr_current, &line[len]);
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
    if(curr_power < 0)
    {
        line[len++] = '-';
        curr_power *= -1;
    }
    t = Dabler16Bit(curr_power, &line[len]);
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

void DisplayLayout_Init(int32 res_offset)
{
    uint8 line[32];
    uint8 len = 7;
    uint8 t = 0;
    
    int32 current           = divS32byS16toS32(res_offset, 2000);
    
    line[0] = 'O';
    line[1] = 'f';
    line[2] = 'f';
    line[3] = 's';
    line[4] = 'e';
    line[5] = 't';
    line[6] = ':';
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
    line[len++] = '\n';
    
    line[len++] = 0;
    OLED_Driver_PutString(line);
}
