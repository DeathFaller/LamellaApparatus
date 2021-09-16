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

#ifndef STEPMOTOR_H
    #define STEPMOTOR_H
    
    #include <project.h>
    #include <math.h>
    #include <GlobalVariables.h>
    
    int g_Stepper_MaxFrequency = 700;
    int g_Stepper_SigmoidShift = -100;
    int g_Stepper_SigmoidRaise = 10;
    #define RIGHT 1
    #define LEFT -1
    #define Stepper_Diff_HomeSampling 400
    #define Stepper_StepsPerStep 4
    
     void MoveTo (double steps, double dir)
    {
    	// Übergebene Steps müssen mit 2 Mulipliziert werden, da jeder 
    	// Schritt 2 Flankenwechsel beeinhaltet
    	steps = steps*2;
    	
        // Maximale Frequenz
        double f_max;
        // Relative Frequenz [0, 1]
        double f_rel;
        // Inkrement der Anzufahrenden Schritte
        int i;
        // gerundete Dauer des Stepper-Zustands
        double t_StepperCLK;    
        // Verschiebung des Sigmoids
        double sig_shift;                   // höherere Wert -> höherere Frequenz zu Beginn
        // Anstieg des Sigmoids
        double sig_raise;                   // höherer Wert -> schnellerer Anstieg
        
        //
        // Parameterset für Motorkontrolle aus "MotorRamp.m"
        //   
        f_max = g_Stepper_MaxFrequency;
        sig_shift = g_Stepper_SigmoidShift;
        sig_raise = g_Stepper_SigmoidRaise;
        
        
        // SLEEP -> Motor "aufwecken" -> Leistungsaufnahme
        Pin_StepperSLEEP_Write(1);
        
        // Richtung setzen
        //
        // Rechtsdrehung
        if (dir == 1)
        {
            Pin_StepperDIR_Write(0);
        }
        // Linksdrehung
        else
        {
            Pin_StepperDIR_Write(1);
        }    
        
        // Für jeden der Schritte
        for (i = 0; i < steps; i = i + 1)
        {
            // Frequenz für Beschleunigungsteil
            if (i < steps/2)
            {       
                // Berechnung der Frequenz
                f_rel = 1.0/(1+exp(-1/(steps/sig_raise)*(i-steps/sig_shift))); 
                // Momentane Ausgabe der LED invertieren
                Pin_StepperCLK_Write(!Pin_StepperCLK_Read());
                // Wartezeit in us berechnen
                t_StepperCLK = 1000000.0/(f_max*f_rel);   
                CyDelayUs((uint16)(t_StepperCLK));           

            }        
            // Frequenz für Abbremsungsgungsteil
            else 
            {
                // Berechnung der Frequenz
                f_rel = (1.0 - 1/(1+exp(-1/(steps/sig_raise)*(i-steps+steps/sig_shift)))); 
                // Momentane Ausgabe der LED invertieren
                Pin_StepperCLK_Write(!Pin_StepperCLK_Read());

                // Wartezeit in us berechnen
                t_StepperCLK = 1000000.0/(f_max*f_rel);            
                CyDelayUs((uint16)(t_StepperCLK));           

            }  
        }
    }
    
    void MoveToWithConstSpeed (double steps, double dir)
    {
    	// Übergebene Steps müssen mit 2 Mulipliziert werden, da jeder 
    	// Schritt 2 Flankenwechsel beeinhaltet
    	steps = steps*2;
    	
        // Inkrement der Anzufahrenden Schritte
        int i;
        // gerundete Dauer des Stepper-Zustands
        double t_StepperCLK;       
        
        // SLEEP -> Motor "aufwecken" -> Leistungsaufnahme
        Pin_StepperSLEEP_Write(1);
        
        // Richtung setzen
        //
        // Rechtsdrehung
        if (dir == 1)
        {
            Pin_StepperDIR_Write(0);
        }
        // Linksdrehung
        else
        {
            Pin_StepperDIR_Write(1);
        }    
        
        // Für jeden der Schritte
        for (i = 0; i < steps; i = i + 1)
        {
            // Momentane Ausgabe der LED invertieren
            Pin_StepperCLK_Write(!Pin_StepperCLK_Read());
            t_StepperCLK = 27500; // [mus]
            CyDelayUs((uint16)(t_StepperCLK));     
        }
    }
    
    void MoveOneStepCW()
    {
        MoveToWithConstSpeed(1, RIGHT);
    }
    
    void MoveOneStepCCW()
    {
        MoveToWithConstSpeed(1, LEFT);
    }
    
    void Move10DegreeCW()
    {
        int StepsFor10Degree = Stepper_Diff_HomeSampling/90 * 10;
        MoveToWithConstSpeed(StepsFor10Degree, RIGHT);
    }
    
    void Move10DegreeCCW()
    {
        int StepsFor10Degree = Stepper_Diff_HomeSampling/90 * 10;
        MoveToWithConstSpeed(StepsFor10Degree, LEFT);  
    }
    
    void Move90DegreeCW()
    { 
        MoveTo(Stepper_Diff_HomeSampling, RIGHT);
    }
    
    void Move90DegreeCCW()
    {
        MoveTo(Stepper_Diff_HomeSampling, LEFT);
    }
    
    void Init_StepMotor()
    {
        // Betriebsart des Motors festlegen
        Pin_StepperMS1_Write(0); 	                // => 16tel-Schritt
        Pin_StepperMS2_Write(0);    
        Pin_StepperMS3_Write(1);   
        /*
        MODE0 	MODE1 	MODE2 	Microstepping
        0 	    0 	    0 	    Vollschritt
        1 	    0 	    0 	    Halbschritt
        0 	    1 	    1 	    1/4 Schritt
        1 	    1 	    0 	    1/8 Schritt
        0 	    0 	    1 	    1/16 Schritt        x => momentan ausgewählt 
        1 	    0 	    1 	    1/32 Schritt
        0 	    1 	    1 	    1/32 Schritt
        1 	    1 	    1 	    1/32 Schritt        
        */	
        
        // ENABLE -> Enable Stepper-Motor an
        Pin_StepperEN_Write(0); 
        // SLEEP -> Motor in Schlafzustand setzen -> keine Leistungsaufnahme
        Pin_StepperSLEEP_Write(0);
        // SLEEP -> Motor "aufwecken" -> Leistungsaufnahme
        Pin_StepperSLEEP_Write(1);
        // RESET -> nicht(!) resetten
        Pin_StepperRES_Write(1);
    }
  
    
    
    #endif

/* [] END OF FILE */
