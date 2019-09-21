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
#ifndef NEXTION_H
    #define NEXTION_H
    
    #include <Includes.h>
    
    void Nextion_EndOfCommunication(){
        UART_TFT_PutChar(0xFF);
        UART_TFT_PutChar(0xFF);
        UART_TFT_PutChar(0xFF);
    }
    
    void Nextion_SendString(char *string){   
        #ifdef DEBUG_NEXTION
            UART_PC_PutString("#Nextion: ");
            UART_PC_PutString(string);
            UART_PC_PutString("\n");
        #endif
        UART_TFT_PutString(string);
        Nextion_EndOfCommunication();
    }
    
    void InitNextion(){                     
        UART_TFT_Start();
        CyDelay(1000);
        Nextion_SendString("page Home");
        CyDelay(100);
    }
#endif
/* [] END OF FILE */
