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

#ifndef LASER_H
    #define LASER_H
    
        #include <Includes.h>
        int Toggle_LASER1()
        {
            Pin_LaserEN1_Write(!Pin_LaserEN1_Read());
            return Pin_LaserEN1_Read();
        }
        
         
        int LASER1(int Status)
        {
            Pin_LaserEN1_Write(Status);   
            #ifdef DEBUG_LASER
                UART_PC_PutString("Laser 1 toggled\n");
            #endif
            return 0;
        }
        
        int GET_LASER1()
        {
            return Pin_LaserEN1_Read();
        }
        
        int Toggle_LASER2()
        {
            Pin_LaserEN2_Write(!Pin_LaserEN2_Read());
            return Pin_LaserEN2_Read();
        }
        
        int LASER2(int Status)
        {
            Pin_LaserEN2_Write(Status);
            #ifdef DEBUG_LASER
                UART_PC_PutString("Laser 2 toggled\n");
            #endif
            return 0;
        }
        
        int GET_LASER2()
        {
            return Pin_LaserEN2_Read();
        }
        
        int Toggle_LASER3()
        {
            Pin_IRLaserEN_Write(!Pin_IRLaserEN_Read());
            return Pin_IRLaserEN_Read();
        }
        
        int LASER3(int Status)
        {
            Pin_IRLaserEN_Write(Status);
            #ifdef DEBUG_LASER
                UART_PC_PutString("Laser 3 toggled\n");
            #endif
            return 0;
        }
        
        int GET_LASER3()
        {
            return Pin_IRLaserEN_Read();
        }

#endif

/* [] END OF FILE */
