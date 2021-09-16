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
    
    #include <Includes.h>
    
    
    void home(){
        
        // Turn laser off, for safety reasons
        
        LASER1(0); 
        LASER2(0);
        LASER3(0);
        CyDelay(100);
        
        // Waiting for input
        
    }
    
#endif
/* [] END OF FILE */
