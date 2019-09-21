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
#ifndef CY_ISR_PCUART_H
    #define CY_ISR_PCUART_H
    
    #include <Includes.h>
    
    CY_ISR(PCUART_Interrupt){
        char last_byte = UART_PC_GetByte();
        #ifdef DEBUG_PCControl_INTERRUPT
            UART_PC_PutString("#Interrupt (PC): ");
            UART_PC_PutChar(last_byte);
            UART_PC_PutString("\n");
        #endif
       
        Switch_PCInterrupt(last_byte);
        
    }
    
#endif
/* [] END OF FILE */