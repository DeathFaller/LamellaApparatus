/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#ifndef PCCONTROL_H
    #define PCCONTROL_H
    
    #include <project.h>
    #include <GlobalVariables.h>
    #include <ADC.h>
    #include <Laser.h>
    #include <StepMotor.h>
    #include <Nextion.h>
    #include <Error.h>
    #include <Output.h>
    
    void Init_PCControl()
    {
        
    }
    
    void SendADCValue()
    {
        char num_str[5];
        itoa(GetADCValue(), num_str, 10);
        UART_PC_PutString((char*)num_str);
    }
    
    void SendMeasurementData()
    {
        char num_str[20];
        
        itoa(LaserState1, num_str, 10);
        UART_PC_PutString((char*)num_str);
        itoa(LaserState2, num_str, 10);
        UART_PC_PutString((char*)num_str);
        itoa(LaserState3, num_str, 10);
        UART_PC_PutString((char*)num_str);
        UART_PC_PutString("-");
        
        itoa(v_timer_Lifetime_ms, num_str, 10);
        UART_PC_PutString((char*)num_str);
        UART_PC_PutString("-");
       
        itoa(GetADCValue(), num_str, 10);
        UART_PC_PutString((char*)num_str);
    }
    
    void ReturnIntCommand(int State){
        char num_str[10];
        
        itoa(State, num_str, 10);
        UART_PC_PutString((char*)num_str);
    }
    
    void ConfirmCommand(){
        UART_PC_PutChar('#');
    }
    
    void IgnoreCommand(){
        UART_PC_PutChar('.');   
    }
    
    void PCControl()
    {
        // Init
        g_ActivePage = 'P';
        Nextion_SendString("page PCControl");
        g_NextionInterrupt = '0';
        g_PCInterrupt = '0';
        
        
        // Main
        
        while (g_ActivePage == 'P')
        {
            if (g_PCInterrupt != '0')
            {
                switch(g_PCInterrupt)
                {
                    case '0':
                        // Do nothing
                        break;
                    case '+':
                        MoveOneStepCW();
                        ConfirmCommand();
                        break;
                    case '-':
                        MoveOneStepCCW();
                        ConfirmCommand();
                        break;
                    case '.':
                        Move10DegreeCW();
                        ConfirmCommand();
                        break;
                    case ',':
                        Move10DegreeCCW();
                        ConfirmCommand();
                        break;
                    case '!':
                        Move90DegreeCW();
                        ConfirmCommand();
                        break;
                    case '?':
                        Move90DegreeCCW();
                        ConfirmCommand();
                        break;
                    
                    
                    case '1':
                        Laser1_Toggle();
                        ReturnIntCommand(LaserState1);
                        ConfirmCommand();
                        break;
                    case '2':
                        Laser2_Toggle();
                        ReturnIntCommand(LaserState2);
                        ConfirmCommand();
                        break;
                    case '3':
                        Laser3_Toggle();
                        ReturnIntCommand(LaserState3);
                        ConfirmCommand();
                        break;
                        
                    case '8':
                        Output1_Toggle();
                        ReturnIntCommand(OutputState1);
                        ConfirmCommand();
                        break;
                    case '9':
                        Output2_Toggle();
                        ReturnIntCommand(OutputState2);
                        ConfirmCommand();
                        break;
                        
                        
                    case 'R':
                        v_timer_Lifetime_ms = 0;
                        ConfirmCommand();
                        break;
                    case 'M':
                        SendMeasurementData();
                        ConfirmCommand();
                        break;
                    case 'T':
                        SendADCValue();
                        ConfirmCommand();
                        break;
                    default:
                        IgnoreCommand();
                        
                }
                g_PCInterrupt = '0';
            }
        }
    }

#endif

/* [] END OF FILE */
