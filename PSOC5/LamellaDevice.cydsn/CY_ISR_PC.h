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

#ifndef CY_ISR_PC_H
    #define CY_ISR_PC_H
    
    #include <project.h>
    #include <GlobalVariables.h>
    
    CY_ISR(PC_Interrupt_Function)
    {
        if (g_ActivePage == 'P')
        {
            char last_byte;
            last_byte = UART_PC_GetByte();
            // Provisorisch
            if (last_byte == 'H')             // Stop everything and return to home!
            {
                g_ActivePage = 'H';
            }
            else
            {
                g_PCInterrupt = last_byte;
            } 
        }
        
    }
    

#endif


/* [] END OF FILE */
