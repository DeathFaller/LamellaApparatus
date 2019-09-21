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
#ifndef INCLUDES_H
    #define INCLUDES_H
    
    #include <project.h>
    #include <float.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <math.h>
    #include <FS.h>
    #include <string.h>
    
    #include <ProgramParts.h>
    #include <Debug.h>
    #include <GlobalVariables.h>
    #include <SwitchInterruptVariables.h>
    #include <SwitchActivePage.h>
    
    #include <Nextion.h>
    #include <CY_ISR_Nextion.h>
    #include <CY_ISR_PCUART.h>
    #include <CY_ISR_Timer.h>
    #include <ADC.h>
    #include <Stepper.h>
    #include <SDCard.h>

    #include <Laser.h>
    #include <Home.h>
    #ifdef Relais
        #include <Relais.h>    
    #endif
    #ifdef PCControl
        #include <PCControl.h>
    #endif
    #include <Init.h>
    
#endif
/* [] END OF FILE */
