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

#ifndef OUTPUT_H
    #define OUTPUT_H
    
    #include <project.h>
    #include <GlobalVariables.h>
    
    void Output1(int State)
    {
        Pin_Output1_Write(State);
        OutputState1 = State;
    }

    void Output1_Toggle()
    {
        Pin_Output1_Write(!Pin_Output1_Read());
        OutputState1 = Pin_Output1_Read();
    }
    
    void Output2(int State)
    {
        Pin_Output2_Write(State);
        OutputState2 = State;
    }

    void Output2_Toggle()
    {
        Pin_Output2_Write(!Pin_Output2_Read());
        OutputState2 = Pin_Output2_Read();
    }
    
#endif



/* [] END OF FILE */
