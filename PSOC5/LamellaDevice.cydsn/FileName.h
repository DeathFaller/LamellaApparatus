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

#ifndef FILENAME_H
    #define FILENAME_H
    
    #include <project.h>
    #include <GlobalVariables.h>
    #include <Nextion.h>
    
    
    void SendFileNameToNextion()
    {
        UART_TFT_PutString("t_FileName.txt=\"");
        for (int i = 0; i<LengthOfFileName; i++)
        {
            UART_TFT_PutChar(FileName[i]);   
        }
        UART_TFT_PutString("\"");
        Nextion_SendEndOfCommunication();   
    }
    
    void Filename()
    {
        g_NextionInterrupt = 40;
        g_ActivePage = 'A'; // TODO
        Nextion_SendString("page Filename");
        
        int counter = 0;
            
        for (int i=0; i < LengthOfFileName; i++)
        {
            FileName[i] = '-';   
        }
        
        while (g_ActivePage == 'A')
        {
            if (g_NextionInterrupt != 40)
            {
                if (g_NextionInterrupt >= 48 && g_NextionInterrupt <= 57)           // Numbers from "0" to "9"
                {
                    FileName[counter] = g_NextionInterrupt;
                    counter++;
                }
                if (g_NextionInterrupt >= 97 && g_NextionInterrupt <= 122)          // Letters from "a" to "z"
                {
                    FileName[counter] = g_NextionInterrupt;
                    counter++;
                }
                if (counter >= LengthOfFileName)                                                   // Reset of counter as easily implemented solution for deleting chars
                {
                    counter = 0;   
                }
                
                SendFileNameToNextion();
                
                if (g_NextionInterrupt == '!')
                {
                    g_ActivePage = 'C';
                }
                
                g_NextionInterrupt = 40;
            }
            
        }
    }

#endif

/* [] END OF FILE */
