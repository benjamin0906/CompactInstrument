#include "I2C_regdef.h"
#include "I2C.h"
#include "ISR.h"

typedef enum eTrState
{
    I2CState_TransmissionDone,
    I2CState_WaitingForStart,
            SendingStuff,
            Receiving_SendAck,
            Receiving_ReceivedData,
            I2CState_WaitingForStop,
            Error,
            
} dtTrState;

dtI2cTrDesc I2cTransmissionDescriptor;
uint8 I2CTransmissionOngoing;
dtTrState State;


void I2C_Init(const uint8 instance, const uint16 brg)
{
    I2Cx(instance).CONL.U = 0;
    I2Cx(instance).CONH.U = 0;
    I2Cx(instance).STAT.U = 0;
    
    I2Cx(instance).BRG = brg;
    I2Cx(instance).CONL.B.GCEN = 1;
    I2Cx(instance).CONL.B.I2CEN = 1;
}

void I2C_Transmission(const dtI2cTrDesc *const desc)
{
    if(State == I2CState_TransmissionDone)
    {
        I2cTransmissionDescriptor = *desc;
        I2CTransmissionOngoing = 1;
        
        State = I2CState_WaitingForStart;
        
        I2Cx(I2cTransmissionDescriptor.instance).CONL.B.SEN = 1;
    }
}

dtI2cStatus I2C_GetStatus(void)
{
    dtI2cStatus ret = I2cStatus_Done;
    if(State == Error)
    {
        ret = I2cStatus_Error;
    }
    else if(State != I2CState_TransmissionDone)
    {
        ret = I2cStatus_Ongoing;
    }
    return ret;
}

void __attribute__ ((interrupt, no_auto_psv)) _MI2C2Interrupt(void)
{
    switch(State)
    {
        case I2CState_WaitingForStart:
            if((I2Cx(I2cTransmissionDescriptor.instance).STAT.B.S != 0))
            {
                /* Start condition has arrived, slave address needs to be sent */
                uint8 address_byte = (I2cTransmissionDescriptor.slave_address << 1);
                State = SendingStuff;
                if(I2cTransmissionDescriptor.reg_addr_len == 0)
                {
                    address_byte |= 1;
                    State = Receiving_SendAck;
                }
                I2Cx(I2cTransmissionDescriptor.instance).STAT.B.S = 0;
                I2Cx(I2cTransmissionDescriptor.instance).TRN.B.TRN = address_byte;
            }
            break;
        case SendingStuff:
            if((I2Cx(I2cTransmissionDescriptor.instance).STAT.B.ACKSTAT != 0))
            {
                /* NACK was received */
                State = Error;
            }
            else
            {
                /* ACK was received */
                if(I2cTransmissionDescriptor.reg_addr_len > 0)
                {
                    I2Cx(I2cTransmissionDescriptor.instance).TRN.B.TRN = *I2cTransmissionDescriptor.reg_addr_ptr;
                    I2cTransmissionDescriptor.reg_addr_ptr++;
                    I2cTransmissionDescriptor.reg_addr_len--;
                }
                else
                {
                    if(I2cTransmissionDescriptor.read_transmission != 0)
                    {
                        I2Cx(I2cTransmissionDescriptor.instance).CONL.B.RSEN = 1;
                        State = I2CState_WaitingForStart;
                    }
                    else
                    {
                        if(I2cTransmissionDescriptor.data_len > 0)
                        {
                            I2Cx(I2cTransmissionDescriptor.instance).TRN.B.TRN = *I2cTransmissionDescriptor.data_ptr;
                            I2cTransmissionDescriptor.data_ptr++;
                            I2cTransmissionDescriptor.data_len--;
                        }
                        else
                        {
                            I2Cx(I2cTransmissionDescriptor.instance).CONL.B.PEN = 1;
                            State = I2CState_WaitingForStop;
                        }
                    }
                }
            }
            break;
        case Receiving_SendAck:
            if(I2cTransmissionDescriptor.data_len != 0)
            {
                I2Cx(I2cTransmissionDescriptor.instance).CONL.B.RCEN = 1;
                State = Receiving_ReceivedData;
            }
            else
            {
                I2Cx(I2cTransmissionDescriptor.instance).CONL.B.PEN = 1;
                State = I2CState_WaitingForStop;
            }
            break;
        case Receiving_ReceivedData:
            if(I2Cx(I2cTransmissionDescriptor.instance).STAT.B.RBF != 0)
            {
                *I2cTransmissionDescriptor.data_ptr = I2Cx(I2cTransmissionDescriptor.instance).RCV.B.RCV;
                I2cTransmissionDescriptor.data_ptr++;
                I2cTransmissionDescriptor.data_len--;
                if(I2cTransmissionDescriptor.data_len != 0)
                {
                    I2Cx(I2cTransmissionDescriptor.instance).CONL.B.ACKDT = 0;
                }
                else
                {
                    I2Cx(I2cTransmissionDescriptor.instance).CONL.B.ACKDT = 1;
                }
                I2Cx(I2cTransmissionDescriptor.instance).CONL.B.ACKEN = 1;
                State = Receiving_SendAck;
            }
            break;
        case I2CState_WaitingForStop:
            if(I2Cx(I2cTransmissionDescriptor.instance).STAT.B.P != 0)
            {
                /* Stop condition is arrived */
                State = I2CState_TransmissionDone;
            }
            break;
        case I2CState_TransmissionDone:
        case Error:
            break;
    }
    ISR_CLEAR_I2C2();
}
