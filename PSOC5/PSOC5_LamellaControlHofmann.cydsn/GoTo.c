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

void GoToPosition (double steps, double dir)
{
    // Maximale Frequenz
    double f_max = 25;
    // Relative Frequenz [0, 1]
    double f_rel;
    // Inkrement der Anzufahrenden Schritte
    int i;
    // gerundete Dauer des Stepper-Zustands
    int t_StepperCLK;
    
    // Verschiebung des Sigmoids
    int sig_shift = 12;                 // höherere Wert -> höherere Frequenz zu Beginn
    // Anstieg des Sigmoids
    int sig_raise = 20;                 // höherer Wert -> schnellerer Anstieg
    
    // Enable Stepper-Motor an 
    Pin_StepperEN_Write(1); 
    
    // Richtung setzen
    //
    // Rechtsdrehung
    if (dir == 1)
    {
        Pin_StepperDIR_Write(1);
    }
    // Linksdrehung
    else
    {
        Pin_StepperDIR_Write(0);
    }    
    
    // Für jeden der Schritte
    for (i = 0; i < steps; i = i + 1)
    {
        // Frequenz für Beschleunigungsteil
        if (i < steps/2)
        {       
            // Berechnung der Frequenz
            f_rel = 1/(1+exp(-1/(steps/sig_raise)*(i-steps/sig_shift))); 
            // Momentane Ausgabe der LED invertieren
            Pin_StepperCLK_Write(!Pin_StepperCLK_Read());
            // Wartezeit berechnen
            t_StepperCLK = round(1000/(f_max*f_rel));
            // Warten
            CyDelay(t_StepperCLK);
        }        
        // Frequenz für Abbremsungsgungsteil
        else 
        {
            // Berechnung der Frequenz
            f_rel = (1 - 1/(1+exp(-1/(steps/sig_raise)*(i-steps+steps/sig_shift)))); 
            // Momentane Ausgabe der LED invertieren
            Pin_StepperCLK_Write(!Pin_StepperCLK_Read());
            // Wartezeit berechnen
            t_StepperCLK = round(1000/(f_max*f_rel));
            // Warten
            CyDelay(t_StepperCLK);
        }  
    }
    // Enable Stepper-Motor aus
    Pin_StepperEN_Write(0); 
}

/* [] END OF FILE */
