#include "OLED_Driver.h"
#include "SPI.h"
#include "Ports.h"
#include "main.h"

#define PIN_RES Port_B_14
#define PIN_DC Port_A_4
#define PIN_CS Port_A_3

typedef enum eOledState
{
    OledState_Off,
            OledState_Init_Reset,
            OledState_Init_ResetWait,
            OledState_Init_Off,
            OledState_Init_ChargePumpEn,
            OledState_Init_AddressingMode,
            OledState_Init_On,
            OledState_Init_BufferClear,
            OledState_Running,
            OledState_WaitingForComm,
} dtOledState;

typedef struct sCharDef
{
    const uint8 code;
    const uint8 *const pixels;
} dtCharDef;

static dtOledState State;
static dtOledState AfterWaitState;
static dtOledMode Mode;
static uint16 Timestamp;
static uint8 dataBuffer[8][128];
static uint16 Timestamp;

static const uint8 digit_0[5] = {0x3E, 0x51, 0x49, 0x45, 0x3E};
static const uint8 digit_1[5] = {0x44, 0x42, 0x7F, 0x40, 0x40};
static const uint8 digit_2[5] = {0x42, 0x61, 0x51, 0x49, 0x46};
static const uint8 digit_3[5] = {0x22, 0x41, 0x49, 0x49, 0x36};
static const uint8 digit_4[5] = {0x18, 0x14, 0x12, 0x7F, 0x10};
static const uint8 digit_5[5] = {0x27, 0x45, 0x45, 0x45, 0x39};
static const uint8 digit_6[5] = {0x3E, 0x49, 0x49, 0x49, 0x32};
static const uint8 digit_7[5] = {0x01, 0x71, 0x09, 0x05, 0x03};
static const uint8 digit_8[5] = {0x36, 0x49, 0x49, 0x49, 0x36};
static const uint8 digit_9[5] = {0x26, 0x49, 0x49, 0x49, 0x3E};
static const uint8 digit_A[5] = {0x7E, 0x11, 0x11, 0x11, 0x7E};
static const uint8 digit_I[5] = {0x00, 0x00, 0x7F, 0x00, 0x00};
static const uint8 digit_O[5] = {0x3E, 0x41, 0x41, 0x41, 0x3E};
static const uint8 digit_P[5] = {0x7F, 0x09, 0x09, 0x09, 0x06};
static const uint8 digit_R[5] = {0x7F, 0x09, 0x09, 0x09, 0x76};
static const uint8 digit_S[5] = {0x46, 0x49, 0x49, 0x49, 0x31};
static const uint8 digit_U[5] = {0x3F, 0x40, 0x40, 0x40, 0x3F};
static const uint8 digit_V[5] = {0x1F, 0x20, 0x40, 0x20, 0x1F};
static const uint8 digit_W[5] = {0x7F, 0x20, 0x18, 0x20, 0x7F};
static const uint8 digit_a[5] = {0x20, 0x54, 0x54, 0x54, 0x78};
static const uint8 digit_e[5] = {0x38, 0x54, 0x54, 0x54, 0x18};
static const uint8 digit_f[5] = {0x08, 0x7E, 0x09, 0x01, 0x02};
static const uint8 digit_g[5] = {0x18, 0xA4, 0xA4, 0xA4, 0x7C};
static const uint8 digit_i[5] = {0x00, 0x44, 0x7D, 0x40, 0x00};
static const uint8 digit_l[5] = {0x00, 0x00, 0x7F, 0x00, 0x00};
static const uint8 digit_m[5] = {0x7C, 0x04, 0x78, 0x04, 0x7C};
static const uint8 digit_n[5] = {0x7C, 0x08, 0x04, 0x04, 0x78};
static const uint8 digit_s[5] = {0x48, 0x54, 0x54, 0x54, 0x20};
static const uint8 digit_t[5] = {0x04, 0x3F, 0x44, 0x40, 0x20};
static const uint8 digit_z[5] = {0x44, 0x64, 0x54, 0x4C, 0x44};
static const uint8 digit_Space[5] = {0x00, 0x00, 0x00, 0x00, 0x00};
static const uint8 digit_Comma[5] = {0x00, 0xA0, 0x60, 0x00, 0x00};
static const uint8 digit_Hyphen[5] = {0x00, 0x10, 0x10, 0x10, 0x00};
static const uint8 digit_Colon[5] = {0x00, 0x6C, 0x6C, 0x00, 0x00};
static const uint8 digit_Point[5] = {0x00, 0x60, 0x60, 0x00, 0x00};

static dtCharDef CharacterBuff[] = {  {.code = 48, .pixels = digit_0},
                                        {.code = 49, .pixels = digit_1},
                                        {.code = 50, .pixels = digit_2},
                                        {.code = 51, .pixels = digit_3},
                                        {.code = 52, .pixels = digit_4},
                                        {.code = 53, .pixels = digit_5},
                                        {.code = 54, .pixels = digit_6},
                                        {.code = 55, .pixels = digit_7},
                                        {.code = 56, .pixels = digit_8},
                                        {.code = 57, .pixels = digit_9},
                                        {.code = 65, .pixels = digit_A},
                                        {.code = 73, .pixels = digit_I},
                                        {.code = 'O', .pixels = digit_O},
                                        {.code = 'P', .pixels = digit_P},
                                        {.code = 'R', .pixels = digit_R},
                                        {.code = 'S', .pixels = digit_S},
                                        {.code = 'U', .pixels = digit_U},
                                        {.code = 'V', .pixels = digit_V},
                                        {.code = 'W', .pixels = digit_W},
                                        {.code = 'a', .pixels = digit_a},
                                        {.code = 'e', .pixels = digit_e},
                                        {.code = 'f', .pixels = digit_f},
                                        {.code = 'g', .pixels = digit_g},
                                        {.code = 'i', .pixels = digit_i},
                                        {.code = 'l', .pixels = digit_l},
                                        {.code = 'm', .pixels = digit_m},
                                        {.code = 'n', .pixels = digit_n},
                                        {.code = 's', .pixels = digit_s},
                                        {.code = 't', .pixels = digit_t},
                                        {.code = 'z', .pixels = digit_z},
                                        {.code = ' ', .pixels = digit_Space},
                                        {.code = ',', .pixels = digit_Comma},
                                        {.code = ':', .pixels = digit_Colon},
                                        {.code = '-', .pixels = digit_Hyphen},
                                        {.code = '.', .pixels = digit_Point},
};

void Send(uint8 *data, uint16 len, uint8 dc);
void OLED_Driver_PutString(uint8 *string);
void OLED_Driver_CopyArrayToBuf(uint8 row, uint8 column, const uint8 *const array, uint8 array_width, uint8 array_height);
void OLED_Driver_Runnable(void);
void OLED_Driver_Set(dtOledMode mode);
uint8 OLED_Driver_Running(void);

void Send(uint8 *data, uint16 len, uint8 dc)
{
    dtSpiTrDesc transfer = {.rx_buff = 0, .tx_buff = data, .length = len};
    Ports_SetPin(PIN_DC, dc);
    Ports_SetPin(PIN_CS, 0);
    SPI_Transmit(0, transfer);
    State = OledState_WaitingForComm;
}

void OLED_Driver_PutString(uint8 *string)
{
    uint8 row = 0;
    uint8 column = 0;
    uint16 len = sizeof(dataBuffer);
    do
    {
        len--;
        ((uint8*)(&dataBuffer[0][0]))[len] = 0;
    }while(len != 0);
    while(*string != 0)
    {
        if(*string == '\n')
        {
            row += 8;
            column = 0;
        }
        else
        {
            uint8 i = 0;
            while((i < (sizeof(CharacterBuff)/sizeof(CharacterBuff[0]))) && (CharacterBuff[i].code != *string))
            {
                i++;
            }
            if(i < (sizeof(CharacterBuff)/sizeof(CharacterBuff[0])))
            {
                OLED_Driver_CopyArrayToBuf(row, column, CharacterBuff[i].pixels, 5, 8);
            }
            column += 6;
        }
        string++;
    }
}

void OLED_Driver_CopyArrayToBuf(uint8 row, uint8 column, const uint8 *const array, uint8 array_width, uint8 array_height)
{
    uint8 x = 0;
    
    uint8 array_y = 0;
    while((array_y < array_height) && (row < 63))
    {
        uint8 char_v_index = array_y / 8;
        uint8 disp_v_index = row / 8;
        uint8 char_pix_pos = array_y - (char_v_index * 8);
        uint8 disp_pix_pos = row - (disp_v_index * 8);
        uint8 char_mask = 1 << char_pix_pos;
        uint8 disp_mask = 1 << disp_pix_pos;

        for(x = 0; (x < array_width) && ((x + column) < 127); x++)
        {
            dataBuffer[disp_v_index][x + column] &= ~disp_mask;
            if((array[char_v_index * array_width + x] & char_mask) != 0)
            {
                dataBuffer[disp_v_index][x + column] |= disp_mask;
            }
        }
        array_y++;
        row++;
    }
}

void OLED_Driver_Runnable(void)
{
    switch(State)
    {
        case OledState_Off:
            if(Mode == OledMode_On)
            {
                State = OledState_Init_Reset;
            }
            break;
        case OledState_Init_Reset:
            Ports_SetPin(PIN_RES, 0);
            Ports_SetPin(PIN_DC, 0);
            Ports_SetPin(PIN_CS, 1);
            Timestamp = SysTime();
            State = OledState_Init_ResetWait;
            break;
        case OledState_Init_ResetWait:
            if(TimePassed(Timestamp, 10) != 0)
            {
                State = OledState_Init_Off;
            }
            Ports_SetPin(PIN_RES, 1);
            break;
        case OledState_Init_Off:
            dataBuffer[0][0] = 0xAE;
            AfterWaitState = OledState_Init_ChargePumpEn;
            //AfterWaitState = OledState_Running;
            Send(&dataBuffer[0][0], 1, 0);
            break;
        case OledState_Init_ChargePumpEn:
            dataBuffer[0][0] = 0x8D;
            dataBuffer[0][1] = 0x14;
            AfterWaitState = OledState_Init_AddressingMode;
            Send(&dataBuffer[0][0], 2, 0);
            break;
        case OledState_Init_AddressingMode:
            dataBuffer[0][0] = 0x20;
            dataBuffer[0][1] = 0x00;
            AfterWaitState = OledState_Init_On;
            Send(&dataBuffer[0][0], 2, 0);
            break;
        case OledState_Init_On:
            dataBuffer[0][0] = 0xAF;
            AfterWaitState = OledState_Init_BufferClear;
            Send(&dataBuffer[0][0], 1, 0);
            break;
        case OledState_Init_BufferClear:
        {
            uint16 len = sizeof(dataBuffer);
            do
            {
                len--;
                ((uint8*)(&dataBuffer[0][0]))[len] = 0;
            }while(len != 0);
        }
                //OLED_Driver_CopyArrayToBuf(13, 24, digit_P, 5,8);
            Send(&dataBuffer[0][0], sizeof(dataBuffer), 1);
            AfterWaitState = OledState_Running;
            break;
        case OledState_Running:
            if(TimePassed(Timestamp, 10) != 0)
            {
                Timestamp = SysTime();
                Send(&dataBuffer[0][0], sizeof(dataBuffer), 1);
            }
            break;
        case OledState_WaitingForComm:
            if(SPI_SpiReady() != 0)
            {
                Ports_SetPin(PIN_CS, 1);
                State = AfterWaitState;
            }
    }
}

void OLED_Driver_Set(dtOledMode mode)
{
    Mode = mode;
}

uint8 OLED_Driver_Running(void)
{
    return (State == OledState_Running) || ((AfterWaitState == OledState_Running) && (State == OledState_WaitingForComm));
}
