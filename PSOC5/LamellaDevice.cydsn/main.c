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


#include<project.h>

#include <Init.h>
#include <ProgramParts.h>
#include <GlobalVariables.h>
#include <home.h>
#include <ConfigurationOfMeasurement.h>
#include <SetupOfMeasurement.h>
#include <Measurement.h>
#include <Error.h>
#include <Test.h>
#include <LaserSelect.h>
#ifdef PC_CONTROL
#include <PCControl.h>
#endif


int breakScreen(char activeScreen)
{
    int retValue = 0;
    if (activeScreen == 'E')
    {
        retValue = 1;
    }
    else if (activeScreen == 'H')
    {
        retValue = 1;
    }
    return retValue;
}

int stepsToPrepareMeasurement(const char measurementMode)
{
    if (ConfigurationOfMeasurement(measurementMode))
    {
        return 1;
    }
    CyDelay(5);
    if (SetupOfMeasurement())
    {
        return 1;
    }
    CyDelay(5);
    if (Laserselect() != 0)
    {
        return 1;
    }
    CyDelay(5);
    Measurement(measurementMode);
    return 0;
}

void startMeasurementPreparation(const char measurementMode)
{
    if (stepsToPrepareMeasurement(measurementMode))
    {
        if (g_Error_Code != 0)
        {
            Error();
        }
        else
        {
            home();
        }
        g_NextionInterrupt = '0';
    }
    else
    {
        home();
    }
}

int main()
{
    Init();
   
    while (1)
    {
        if (g_ActivePage == 'H')
        {
            // Go to home page, stop everything. 
            // Force reset of all variables in different program parts -> Init in the subprograms
            home();
            g_NextionInterrupt = '0';               // Set to idling
            g_ActivePage = '0';
        }
        switch(g_NextionInterrupt)
        {
            case '0':
                CyDelay(1);
                // Do nothing! idling
                break;
            case 'L':
                // Lifetime measurement
                startMeasurementPreparation(MODE_LIFETIME);
                break;
                
            case 'T':
                // Thickness measurement
                startMeasurementPreparation(MODE_THICKNESS);
                break;
                
            case 'C':
                // Lifetime + Thickness Combi measurement
                startMeasurementPreparation(MODE_LIFETIMEANDTHICKNESS);
                break;
            #ifdef PC_CONTROL
            case 'P':
                // PCControl
                PCControl();
                break;
            #endif
            case 'Z':
                // Test - page
                Test();
                break;
            default:
                setError(1);
                break;
        }
    }
    return 1;   
}

/* [] END OF FILE */
