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
#ifndef ERROR_H
    #define ERROR_H
    
    #include <Nextion.h>
    #include <GlobalVariables.h>
    
    void setError(int code)
    {
        g_Error_Code = code;
    }
    
    void Error()
    {
        // INIT
        
        // MAIN
        
        Nextion_SendString("page Error");
        CyDelay(100);
       
        Nextion_SendValueToValueBox("n_ErrorCode", g_Error_Code);
        CyDelay(100);
        g_Error_Code = 0;
        
        while (g_NextionInterrupt != BUTTON_HOME)
        {
            CyDelay(5);
        }
        g_NextionInterrupt = '0';
    }
#endif
/* [] END OF FILE */
