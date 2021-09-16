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
#ifndef INIT_H
    #define INIT_H
    
    #include <project.h>
    
    #include <ProgramParts.h>
    #include <SDCard.h>
    #include <ADC.h>
    #include <LaserSelect.h>
    #include <Nextion.h>
    #include <CY_ISR_Nextion.h>
    #include <CY_ISR_PC.h>
    #include <CY_ISR_Timer.h>
    
    
    
    void Init_LED(char state)
    {
        Pin_LED_Write(state);
    }
    
    
    
    void Init(){
        Init_LED(1);
        
        Init_MeasurementLasers();
        
        UART_PC_Start();

        Init_ADC();    
        
        Timer1_Start();
        Timer1_Function_StartEx(Timer_Interrupt_Function);
        
        
        
        Init_Nextion();    
        
        Interr_TFT_StartEx(Nextion_Interrupt_Function);
        
        #ifdef PC_CONTROL
        Interr_PC_StartEx(PC_Interrupt_Function);
        #endif
        
        Init_SDCard();
        
        CyGlobalIntEnable;      // Enable Global Interrupts for Timer, Communication with Nextion and Communication with PC
        
        Init_LED(0);
    }
    
    
    
    #endif
/* [] END OF FILE */
