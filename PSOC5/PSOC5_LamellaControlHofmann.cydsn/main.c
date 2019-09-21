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
#ifndef MAIN_C
    #define MAIN_C
    
    #include <Includes.h>
    
    int main(){
        Init();
        
        while (1){                  // Main-Schleife, Dauerhaft wiederholen
            if (g_Nextion_InterruptSignal != 0){    
                switch(g_Nextion_InterruptSignal){
                    case 'H':
                        home();
                        break;
                    #ifdef PCControl
                    case 'P':
                        pc_control();
                        break;
                    #endif
                }
                
            }
        }
    }
    
    
#endif 
/* [] END OF FILE */
