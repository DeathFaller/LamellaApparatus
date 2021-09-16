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

    #include <project.h>
    #include <GlobalVariables.h>
    
    
    void Laser1(int Status)
    {
        Pin_LaserEN1_Write(Status);
        LaserState1 = Status;
    }
    
    void Laser1_Toggle()
    {
        Pin_LaserEN1_Write(!Pin_LaserEN1_Read());
        LaserState1 = Pin_LaserEN1_Read();
    }
    
    void Laser2(int Status)
    {
        Pin_LaserEN2_Write(Status);
        LaserState2 = Status;
    }
    
    void Laser2_Toggle()
    {
        Pin_LaserEN2_Write(!Pin_LaserEN2_Read());   
        LaserState2 = Pin_LaserEN2_Read();
    }
    
    void Laser3(int Status)
    {
        Pin_IRLaserEN_Write(Status);
        LaserState3 = Status;
    }
    
    void Laser3_Toggle()
    {
        Pin_IRLaserEN_Write(!Pin_IRLaserEN_Read());   
        LaserState3 = Pin_IRLaserEN_Read();
    }
    
    void turnAllLasersOff()
    {
        Laser1(0);
        Laser2(0);
        Laser3(0);
    }
    
    #endif


/* [] END OF FILE */
