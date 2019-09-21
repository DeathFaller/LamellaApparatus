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
#ifndef DEBUG_H
    #define DEBUG_H
    
    #include <Includes.h>
    #ifdef DEBUGGING
        #ifdef UART_PC
            #define DEBUG_INIT
            #define DEBUG_ADC
            #define DEBUG_Timer_Interrupt
            #define DEBUG_PCControl_INTERRUPT    
            #define DEBUG_STEPPER
            #define DEBUG_NEXTION
//            #define DEBUG_LASER
//            #define DEBUG_PCCONTROL
        #endif
    #endif
#endif
/* [] END OF FILE */
