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
#ifndef SWITCHACTIVEPAGE_H
    #define SWITCHACTIVEPAGE_H

    #include <Includes.h>
    
    char Protect_ActivePage = 0;
    
    void Switch_ActivePage(char New){
        if (Protect_ActivePage == 0){
            Protect_ActivePage = 1;
            g_ActivePage = New;
            Protect_ActivePage = 0;
        }
        
    }
   
#endif
/* [] END OF FILE */
