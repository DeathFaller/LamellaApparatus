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

#ifndef NEXTION_PLOTSETUPDATA_H
    #define NEXTION_PLOTSETUPDATA_H

    #include <project.h>
    #include <stdlib.h>
    #include <math.h>
    
    #include <Nextion.h>
    
    
    // NextionPlotSettings:
    // Settings of Nextion software
    #define Nextion_SetupPlot_Settings_x 180
    #define Nextion_SetupPlot_Settings_y 40
    #define Nextion_SetupPlot_Settings_w 325
    #define Nextion_SetupPlot_Settings_h 200
                
    #define Nextion_SetupPlot_Settings_xmax 100          // Immer 100 Messwerte auf x-Achse
    #define Nextion_SetupPlot_Settings_ymax 4095         // Maximalwerts des 12bit ADC, also 2^12
    
    
    
    void NextionPlot_PointsToSetupAxes(float presence_ths, float ref_ths, float intensity)
    {
        // Hilfsvariable mit 20 Zeichen
        char num_str[20];

        // bescheuerte Skalierung!!!! Höhe im Nextion Editor is massgeblich
        presence_ths = 1.0*Nextion_SetupPlot_Settings_h*(1.0*presence_ths/Nextion_SetupPlot_Settings_ymax);
        ref_ths = 1.0*Nextion_SetupPlot_Settings_h*(1.0*ref_ths/Nextion_SetupPlot_Settings_ymax);
        intensity = 1.0*Nextion_SetupPlot_Settings_h*(1.0*intensity/Nextion_SetupPlot_Settings_ymax);
        
        // -> setze jeweiligen Wert in Kanäle 0, 1 und 2 der Zeichenfläche mit ID 2
        
        // Wert für Detektionsgrenze -> darunter wird die Zeitmessung gestoppt
        UART_TFT_PutString("add 1,0,"); // Nextion Befehl: add ID, Channel, Value
        // Umwandlung Integer -> Array of char ("String") x_str im Decimalsystem
        itoa((int)presence_ths, num_str, 10);
        UART_TFT_PutString(num_str);
        // Ende der Eingabe markieren
        Nextion_SendEndOfCommunication(); 
        
        // Wert für Autokalibrierung -> wenn überschritten, ist das die Sampling Position
        UART_TFT_PutString("add 1,1,");
        // Umwandlung Integer -> Array of char ("String") x_str im Decimalsystem
        itoa((int)ref_ths, num_str, 10);
        UART_TFT_PutString(num_str);
        // Ende der Eingabe markieren
        Nextion_SendEndOfCommunication(); 
        
        // Momentaner Wert vom ADC
        UART_TFT_PutString("add 1,2,");
        // Umwandlung Integer -> Array of char ("String") x_str im Decimalsystem
        itoa((int)intensity, num_str, 10);
        UART_TFT_PutString(num_str);
        // Ende der Eingabe markieren
        Nextion_SendEndOfCommunication();
    }

#endif
/* [] END OF FILE */
