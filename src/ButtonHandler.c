#include "types.h"
#include "Ports.h"
#include "main.h"

uint8 button_one_flag;

void ButtonHandler_Runnable(void)
{
    static uint32 btn_one_timestamp = 0;
    
    if(TimePassed(btn_one_timestamp, 50) != 0)
    {
        if(Ports_GetPin(Port_A_1) == 0)
        {
            if(button_one_flag != 255)
            {
                button_one_flag ++;
            }
            btn_one_timestamp = SysTime();
        }
        else
        {
            button_one_flag = 0;
        }
    }
}

uint8 ButtonHandler_GetButton()
{
    return button_one_flag;
}
