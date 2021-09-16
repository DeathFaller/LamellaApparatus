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

#ifndef NEXTION_PLOTLIFETIMEDATA_H
    #define NEXTION_PLOTLIFETIMEDATA_H
    
    #include <project.h>
    #include <GlobalVariables.h>
    #include <Nextion.h>
    
    #define Nextion_LifetimePlot_Settings_x 110
    #define Nextion_LifetimePlot_Settings_y 72
    #define Nextion_LifetimePlot_Settings_w 300
    #define Nextion_LifetimePlot_Settings_h 200
    
    #define Nextion_LifetimePlot_Settings_Fill_Width 3 
    #define Nextion_LifetimePlot_Settings_Fill_Height 3
    
    
    void Nextion_SendFillCommand(int pos_x, int pos_y, int height, int width)
    {
        char num_str[20];
        itoa(pos_x, num_str, 10);
        UART_TFT_PutString("fill ");
        UART_TFT_PutString((char*)num_str);
        UART_TFT_PutString(",");
        itoa(pos_y, num_str, 10);
        UART_TFT_PutString((char*)num_str);
        UART_TFT_PutString(",");
        itoa(width, num_str, 10);
        UART_TFT_PutString((char*)num_str);
        UART_TFT_PutString(",");
        itoa(height, num_str, 10);
        UART_TFT_PutString((char*)num_str);
        UART_TFT_PutString(",");
        itoa(NextionColor_Red, num_str, 10);
        UART_TFT_PutString((char*)num_str);
        Nextion_SendEndOfCommunication();
    }
    
    void Nextion_PlotLifetime(int Number, int Lifetime_ms)
    {
        
        int tmp_x = Nextion_LifetimePlot_Settings_w * Number/g_NumberOfMeasurements  + Nextion_LifetimePlot_Settings_x;
        int tmp_y = Nextion_LifetimePlot_Settings_h - Nextion_LifetimePlot_Settings_h * Lifetime_ms/1000/60/g_MaxMeasurementTime_min  + Nextion_LifetimePlot_Settings_y - Nextion_LifetimePlot_Settings_Fill_Height;
        
        Nextion_SendFillCommand(tmp_x, tmp_y, Nextion_LifetimePlot_Settings_Fill_Width, Nextion_LifetimePlot_Settings_Fill_Height);
        
        
    }


    
#endif

/* [] END OF FILE */
