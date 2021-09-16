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
    
    #include <project.h>
    #include <GlobalVariables.h>
    
    CY_ISR(Timer_Interrupt_Function)
    {
        v_timer_100ms++;
        if (v_timer_100ms >= 100)
        {
            v_timerflag_100ms = 1;   
            v_timer_100ms = 0;
        }
        
        v_timer_waiting++;
        
        v_timer_Lifetime_ms++;
        
        v_timer_Measurement++;
        
        if (v_timer_Measurement >= (g_SwitchPeriodOfLaser_ms/2))
        {
            v_timerflag_Measurement = 1;
            // Reset is done, after the laser gets switched -> easier for obtaining the time in the middle.
        }
        
        v_timer_LaserSwitch++;
        if (v_timer_LaserSwitch >= g_SwitchPeriodOfLaser_ms)
        {
            v_timer_LaserSwitch = 0;
            v_timerflag_LaserSwitch = 1;
        }
        
        v_timer_500ms++;
        if (v_timer_500ms >= 500)
        {
            v_timer_500ms = 0;
            v_timerflag_500ms = 1;
        }
    }

#endif


/* [] END OF FILE */
