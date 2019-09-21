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

#ifndef RELAIS_H
    #define RELAIS_H
    
        #include <Includes.h>
        int Toggle_RELAIS1()
        {
            Pin_Relais1_Write(!Pin_Relais1_Read());
            return !Pin_Relais1_Read();
        }
        
        int Toggle_RELAIS2()
        {
            Pin_Relais2_Write(!Pin_Relais2_Read());
            return !Pin_Relais2_Read();
        }
         
        int RELAIS1(int Status)
        {
            Pin_Relais1_Write(!Status);   
            #ifdef DEBUG_Relais
                UART_PC_PutString("Relais 1 toggled\n");
            #endif
            return 0;
        }
        
        int RELAIS2(int Status)
        {
            Pin_Relais2_Write(!Status);
            #ifdef DEBUG_Relais
                UART_PC_PutString("Relais 2 toggled\n");
            #endif
            return 0;
        }
        
        int GET_RELAIS1()
        {
            return !Pin_Relais1_Read();
        }
        
        int GET_RELAIS2()
        {
            return !Pin_Relais2_Read();
        }
        

#endif
/* [] END OF FILE */
