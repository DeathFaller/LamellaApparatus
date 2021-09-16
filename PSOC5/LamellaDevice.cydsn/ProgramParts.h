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



#ifndef PROGRAMPARTS_H
    #define PROGRAMPARTS_H
    
    // This file is used for adding new parts, while testing them. 
    // If the new module is working correctly, the changes should be implemented completely without the possibility to deactivate them here. 
    
    // #define ChangeFileName       // Excluded, because it is not working right now. 
    
    // #define PC_CONTROL
    
   // #define DEACTIVATE        // Used for deactivating unnecessary program parts during debugging
                                // The corresponding frame should be deleted after completion
                                // This is reserved as a safety function, so that everything runs, if one deactivation is forgotten
    
    #define ARDUINOCONTROL      // For usage with the arduino controlled pressure sensor and pressure control
    
    #define CHANGES09032020
    
#endif
    

/* [] END OF FILE */
