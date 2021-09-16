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

    #include <project.h>
    #include <stdlib.h>
    #include <ProgramParts.h>
    #include <GlobalVariables.h>
    
    void Nextion_SendEndOfCommunication()
    {
        CyDelay(10);
        UART_TFT_PutChar(0xFF);
        UART_TFT_PutChar(0xFF);
        UART_TFT_PutChar(0xFF);
    }
    
    void Nextion_SendString(const char *string)
    {
        UART_TFT_PutString(string);
        Nextion_SendEndOfCommunication();
    }
    
    void Nextion_SendValueToValueBox(const char *string, const int value)
    {
        // Hilfsvariable mit 20 Zeichen, in der new_value als char gespeichert wird
        char num_str[20];
    
        // neuen Wert setzen
        UART_TFT_PutString((char*)string);
        UART_TFT_PutString((char*)".val=");
        // Umwandlung Integer -> Array of char ("String") x_str im Decimalsystem
        itoa(value, num_str, 10);
        UART_TFT_PutString((char*)num_str);
        // Anfrage absenden
        Nextion_SendEndOfCommunication();
    }
    
    void Nextion_SendTextToTextBox(char *string, char *value)
    {
        UART_TFT_PutString((char*)string);
        UART_TFT_PutString((char*)".txt=\"");
        UART_TFT_PutString((char*)value);
        UART_TFT_PutString("\"");
        // Anfrage absenden
        Nextion_SendEndOfCommunication();
    }
    
    int Nextion_GetSliderValue(){
        int slider_value = (g_SliderValueBuffer[0]+g_SliderValueBuffer[1]*256);
        return slider_value;
    }
    
    void Nextion_SendBackgroundColorToButton(char *string, int color)
    {
        char num_str[20];
        itoa(color, num_str, 10);
        UART_TFT_PutString((char*)string);
        UART_TFT_PutString((char*)".bco=");
        UART_TFT_PutString((char*)num_str);
        Nextion_SendEndOfCommunication();
    }
    
    void Init_Nextion()
    {
        UART_TFT_Start();
        CyDelay(2000);
        Nextion_SendString("page Home");
        
    }
    
#endif

/* [] END OF FILE */
