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

#ifndef ADC_H
    #define ADC_H

    #include <project.h>
    
    short GetADCValue()
    {
        Analog_Digital_Converter_IsEndConversion(Analog_Digital_Converter_WAIT_FOR_RESULT);
        return Analog_Digital_Converter_GetResult16()/2;
    }
    
    void Init_ADC()
    {
        TIA_1_Start();
        PGA_Photo_Start();
        
        Analog_Digital_Converter_Start();
        Analog_Digital_Converter_StartConvert();
    }
    
#endif

/* [] END OF FILE */
