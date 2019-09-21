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
    
    #include <Includes.h>
    
    void InitADC(){                 // confliting types error message can be ignored
        TIA_1_Start();
        PGA_Photo_Start();
        
        Analog_Digital_Converter_Start();
        Analog_Digital_Converter_StartConvert();
    }
    
    #ifndef TEST_ADC
        int getADCValue(){
            Analog_Digital_Converter_IsEndConversion(Analog_Digital_Converter_WAIT_FOR_RESULT);
            int tmp = Analog_Digital_Converter_GetResult16();
            #ifdef DEBUG_ADC
                char Meldung[10];
                UART_PC_PutString("#ADC Value: ");
                itoa(tmp, Meldung, 10);
                UART_PC_PutString(Meldung);
                UART_PC_PutString("\n");
            #endif
            return tmp;
        }
    #else
       int v_ADC_Debug_Counter = 0;
        int getADCValue(){
            v_ADC_Debug_Counter++
            return v_ADC_Debug_Counter;
        }
    #endif
    
    
#endif
/* [] END OF FILE */
