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
#ifndef CY_ISR_NEXTION_H
    #define CY_ISR_NEXTION_H
    
    #include <Includes.h>
    
    CY_ISR(Nextion_Interrupt){
        char last_byte = UART_TFT_GetByte();
        #ifdef DEBUG_Nextion_INTERRUPT
            UART_PC_PutString("#Interrupt (Nextion): ");
            UART_PC_PutChar(last_byte);
            UART_PC_PutString("\n");
        #endif
        if (last_byte == 0xFF){
            // Ignore, because only signal for End of Communication
        }
        else
        {
            if (last_byte == 'H')
            {
                g_ActivePage = 'H';
            }
            else if (last_byte == 'Z')
            {
               Switch_PCInterrupt('Z');
            }
            else
            {
                Switch_NextionInterrupt(last_byte);
            }
        }
    }
    
    
#endif
/* [] END OF FILE */
