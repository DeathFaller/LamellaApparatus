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
#ifndef STEPPER_H
    #define STEPPER_H
        
    #include <Includes.h>
    
    #define RIGHT 1
    #define LEFT -1
    
    #define c_StepsDifferenceHomeSampling 800
    #define c_StepsOneStepSettings 4
    
    
    #define c_MaxStepperFrequenz 700        // Maximale Frequenz
    #define c_SigShiftStepper -100          // Verschiebung des Sigmoids
    #define c_SigRaiseStepper 10            // Anstieg des Sigmoids
    
    
    void InitStepper(){                         // conflicting types error message can be ignored
        
        // Betriesart des Steppers festlegen
        Pin_StepperMS1_Write(0);
        Pin_StepperMS2_Write(0);
        Pin_StepperMS3_Write(1);
        //   MODE0 	MODE1 	MODE2 	Microstepping
        //   0 	    0 	    0 	    Vollschritt
        //   1 	    0 	    0 	    Halbschritt
        //   0 	    1 	    1 	    1/4 Schritt
        //   1 	    1 	    0 	    1/8 Schritt
        //   0 	    0 	    1 	    1/16 Schritt        x => momentan ausgewählt 
        //   1 	    0 	    1 	    1/32 Schritt
        //   0 	    1 	    1 	    1/32 Schritt
        //   1 	    1 	    1 	    1/32 Schritt  
        
        
        Pin_StepperEN_Write(0);
        Pin_StepperSLEEP_Write(1);  // Let Stepper activated, otherwise it won't hold the position!
        Pin_StepperRES_Write(1);
    }    
    
    void SetDirection(double dir)
    {
        if (dir == RIGHT)
        {
            Pin_StepperDIR_Write(0);
        }   
        else
        {
            Pin_StepperDIR_Write(1);
        }   
    }
    
    int MoveTo (double steps, double dir)
    {
        #ifdef DEBUG_STEPPER
            UART_PC_PutString("#Move To\n");
        #endif
        double f_rel;
        double t_StepperCLK;
        steps = steps * 2;
                                   
        SetDirection(dir);
        
        for (int i = 0; i < steps; i++)
        {
            #ifdef DEBUG_STEPPER
                if (i%10 == 0)
                {
                    char Meldung[10];
                    UART_PC_PutString("Step: ");
                    itoa(i, Meldung, 10);
                    UART_PC_PutString(Meldung);
                    UART_PC_PutString("\n");
                }
            #endif
            // Beschleunigung
            if (i < steps/2)
            {
                f_rel = (1/(1+exp(-1/(steps/c_SigRaiseStepper)*(i-steps/c_SigShiftStepper)))); 
                Pin_StepperCLK_Write(!Pin_StepperCLK_Read());
                t_StepperCLK = 1000000.0/(c_MaxStepperFrequenz*f_rel);            
                CyDelayUs((uint16)(t_StepperCLK));     
            }
            // Bremsung
            else
            {
                f_rel = (1.0 - 1/(1+exp(-1/(steps/c_SigRaiseStepper)*(i-steps+steps/c_SigShiftStepper)))); 
                Pin_StepperCLK_Write(!Pin_StepperCLK_Read());
                t_StepperCLK = 1000000.0/(c_MaxStepperFrequenz*f_rel);            
                CyDelayUs((uint16)(t_StepperCLK));        
            }
            
        }
        return 0;   
    }
    
    
    int MoveToWithConstantSpeed (double steps, double dir)
    {
        Pin_StepperSLEEP_Write(1);
        #ifdef DEBUG_STEPPER
            UART_PC_PutString("#Move To With Constant Speed\n");
        #endif
        steps = steps*2;
        double t_StepperCLK = 27500; // Microseconds
 
        
        SetDirection(dir);
        
        for (int i = 0; i < steps; i++)
        {
            Pin_StepperCLK_Write(!Pin_StepperCLK_Read());
            CyDelayUs((uint16)(t_StepperCLK));
            
        }
        
       
        return 0;
    }
    
    int MoveOneStep_CW()
    {
        #ifdef DEBUG_STEPPER
            UART_PC_PutString("#Move CW\n");
        #endif
        MoveToWithConstantSpeed(c_StepsOneStepSettings, RIGHT);
        return 0;
    }
    
    int MoveOneStep_CCW()
    {
        #ifdef DEBUG_STEPPER
            UART_PC_PutString("#Move CCW\n");
        #endif
        MoveToWithConstantSpeed(c_StepsOneStepSettings, LEFT);
        return 0;
    }
    
    int Move90Degree_CW()
    {
        #ifdef DEBUG_STEPPER
            UART_PC_PutString("#Move 90 CW\n");
        #endif
        MoveTo(c_StepsDifferenceHomeSampling, RIGHT);
        return 0;
    }
    
    int Move90Degree_CCW()
    {
        #ifdef DEBUG_STEPPER
            UART_PC_PutString("#Move 90 CCW\n");
        #endif
        MoveTo(c_StepsDifferenceHomeSampling, LEFT);
        return 0;
    }
    
#endif
/* [] END OF FILE */
