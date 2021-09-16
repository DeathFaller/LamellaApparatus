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

#ifndef HOME_H
    #define HOME_H
    
    #include <Laser.h>
    #include <Nextion.h>
    
    void home()
    {
        turnAllLasersOff();
        CyDelay(10);
        Nextion_SendString("page Home");
    }
    
    #endif

/* [] END OF FILE */
