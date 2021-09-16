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

#ifndef CYISRNEXTION_H
    #define CYISRNEXTION_H
   
    #include <project.h>
    
    #include <GlobalVariables.h>
    
    static int counter = 0;
    
    
    CY_ISR(Nextion_Interrupt_Function)
    {
        char last_byte;
        last_byte = UART_TFT_GetByte();
        
        if (last_byte != 0xFF)                      // 0xFF indicates end of communication from/to Nextion
        {             
            if (g_SliderValueReceiving == 1)
            {
                g_SliderValueBuffer[counter] = last_byte;
                counter++;
                if (counter == 4){
                    g_SliderValueReceiving = 2;     // indicates that all slider values got received
                    counter = 0;                    // counter reset for finished transmission
                }
            }
            else if (last_byte == '&')                   // Slider value will be sent
            {
                g_SliderValueReceiving = 1;              
                counter = 0;                            // Counter reset, if transmission gets interrupted
                
            }else if (last_byte == 'H')             // Stop everything and return to home!
            {
                g_ActivePage = 'H';
            }
            else 
            {
                g_NextionInterrupt = last_byte;   
            }
        }
    }

#endif

/* [] END OF FILE */
