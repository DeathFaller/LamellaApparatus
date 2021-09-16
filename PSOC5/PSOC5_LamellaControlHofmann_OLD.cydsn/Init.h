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

    #include <Includes.h>
    
    void Init_LED(int Status){
        Pin_LED_Write(Status);
    }
    
    
    void Init(){
        Init_LED(1);
        
        #ifdef UART_PC                          // Init Serial Port for PC communication
            UART_PC_Start();
            #ifdef UART_PC_INTERRUPT
                Interr_PC_StartEx(PCUART_Interrupt);
            #endif
        #endif
        
        #ifdef DEBUG_INIT
            UART_PC_PutString("#Init started\n");
            UART_PC_PutString("#UART started´\n");
        #endif
        #ifdef TIMER
            Timer1_Start();
            #ifdef DEBUG_INIT
                UART_PC_PutString("#Started Timer\n");
            #endif
            Timer1_Function_StartEx(Timer_Interrupt);
            #ifdef DEBUG_INIT
                UART_PC_PutString("#Connected Timer Interrupt\n");
            #endif
        #endif
        
        #ifdef ADC
            InitADC();
            #ifdef DEBUG_INIT
                UART_PC_PutString("#Started ADC\n");    
            #endif
        #endif
        
        #ifdef STEPPER
            InitStepper();    
            #ifdef DEBUG_INIT
                UART_PC_PutString("#Started Stepper\n");
            #endif
        #endif
        
        #ifdef NEXTION // Last part of programm, since it shows the Initialising screen
            InitNextion();
            #ifdef DEBUG_INIT
                UART_PC_PutString("#Started Nextion\n");
            #endif
            Interr_TFT_StartEx(Nextion_Interrupt);
            #ifdef DEBUG_INIT
                UART_PC_PutString("#Connected Nextion Interrupt\n");
            #endif
        #endif
        
        #ifdef DEBUG_INIT
            UART_PC_PutString("#Finished Init\n");    
        #endif
        
        CyGlobalIntEnable;
        Init_LED(0);
    }
    
    
#endif
/* [] END OF FILE */
