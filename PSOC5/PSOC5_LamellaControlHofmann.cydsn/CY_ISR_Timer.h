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
#ifndef CY_ISR_TIMER_H
    #define CY_ISR_TIMER_H
    #include <Includes.h>
    
    CY_ISR(Timer_Interrupt){
        #ifdef DEBUG_Timer_Interrupt
            UART_PC_PutString("#Interrupt (Timer): \n");    
        #endif

        t_timer_LaserSwitch++;
        if (t_timer_LaserSwitch >= p_LaserSwitchPeriod){
            f_timer_LaserSwitch = 1;
            t_timer_LaserSwitch = 0;
            #ifdef DEBUG_Timer_Interrupt
                UART_PC_PutString("#LaserSwitch\n");
            #endif
        }
        
        if (f_timer_LamellaLifetime_Measuring == 1){
            t_timer_LamellaLifetime++;
        }
    }

    
#endif
/* [] END OF FILE */
