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

#ifndef SDCARD_H
    #define SDCARD_H
    
    #include <project.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <FS.h>
    #include <GlobalVariables.h>
    #include <Error.h>
    
    #define MaxRetriesForFileOpening 100
    
    void LogLifetime(char *name, int NumberOfMeasurement, double Lifetime, int ArbitrarilyRuptured)
    {
        FS_FILE *File;
        
        #ifdef ChangeFileName
            char tmp_FileName[13];
            sprintf(tmp_FileName, "%s.txt", FileName);
        #endif    
           
        char buffer_nextLine[40];

        
        int retryCount;
        retryCount = 0; 
        #ifdef ChangeFileName
        File = FS_FOpen((char*)tmp_FileName, "a");
        #else
            File = FS_FOpen(name, "a");    
        #endif
        CyDelay(10);
        
        while (File == 0)
        {
            retryCount++;
            #ifdef ChangeFileName
                File = FS_FOpen((char*)tmp_FileName, "a");
            #else
                File = FS_FOpen(name, "a");    
            #endif
            CyDelay(10);
            if (retryCount > MaxRetriesForFileOpening)
            {
                setError(700);
                return;                 // Stop logging, file is not open
            }
        }
        
        sprintf((char*)buffer_nextLine, "%d\t%f\t%i\n", NumberOfMeasurement, Lifetime/1000.0, ArbitrarilyRuptured);
        
        if (0 != FS_Write(File, buffer_nextLine, strlen(buffer_nextLine)))
        {
            // Write successfull, do nothing    
        }
        else
        {
            // Error, Write failed. 
            setError(701);
        }
        
        int retValFS_FClose = 1;
        retryCount = 0;
        while (retValFS_FClose)
        {
            retryCount++;
            retValFS_FClose = FS_FClose(File);
            
            if (retryCount > 100)
            {
                setError(702);
                return;
            }
        }
    }
    
    
    void WriteSpeedTest()
    {
        FS_FILE *File;
        char buffer_FileName[12];
        char buffer_nextLine[40];

        v_timer_Lifetime_ms = 0;
        for (int j = 100; j > 0; j = j-10)
        {
            for (int i = 0; i < 1000; i++)
            {
                sprintf((char*)buffer_FileName, "Sp%04i.txt", j);
                
                File = FS_FOpen(buffer_FileName, "a");
                CyDelay(j);
                
                int retryCount;
                retryCount = 0;
                
                while (File == 0)
                {
                    retryCount++;
                    File = FS_FOpen(buffer_FileName, "a");
                    CyDelay(j);
                    if (retryCount > MaxRetriesForFileOpening)
                    {
                        setError(710);
                        return;                 // Stop logging, file is not open
                    }
                }
                
                sprintf((char*)buffer_nextLine, "%0.3f\n", v_timer_Lifetime_ms);
                
                
                if (0 != FS_Write(File, buffer_nextLine, strlen(buffer_nextLine)))
                {
                    // Write successfull, do nothing    
                }
                else
                {
                    // Error, Write failed. 
                    setError(711);
                    return;
                }
                
                int retValFS_FClose = 1;
                retryCount = 0;
                while (retValFS_FClose)
                {
                    retryCount++;
                    retValFS_FClose = FS_FClose(File);
                    
                    if (retryCount > 100)
                    {
                        setError(712);
                        return;
                    }
                }
            }
        }
    }
    
    void LogIntensity(int MeasNo, char State1, char State2, char State3, double timer, int ADCValue)
    {
        FS_FILE *File;
        
        char tmp_FileName[12];
        char buffer_nextLine[40];
        #ifdef ChangeFileName
            sprintf((char*)tmp_FileName, "%s%04d.raw", FileName, MeasNo);
        #else
            sprintf((char*)tmp_FileName, "%08d.raw", MeasNo);
            
        #endif
        File = FS_FOpen(tmp_FileName, "a");
        CyDelay(10);
        
        int retryCount;

        
        retryCount = 0;
        
        while (File == 0)
        {
            retryCount++;
            File = FS_FOpen(tmp_FileName, "a");
            CyDelay(10);
            if (retryCount > MaxRetriesForFileOpening)
            {
                setError(720);
                return;                 // Stop logging, file is not open
            }
        }
        
        sprintf((char*)buffer_nextLine, "%i\t%i\t%i\t%0.0f\t%i\n", State1, State2, State3, timer, ADCValue);
        
        if (0 != FS_Write(File, buffer_nextLine, strlen(buffer_nextLine)))
        {
            // Write successfull, do nothing    
        }
        else
        {
            // Error, Write failed. 
            setError(721);
        }
        
        int retValFS_FClose = 1;
        retryCount = 0;
        while (retValFS_FClose)
        {
            retryCount++;
            retValFS_FClose = FS_FClose(File);
            
            if (retryCount > 100)
            {
                setError(722);
                return;
            }
        }
    }
    
    void Init_SDCard()
    {
        FS_Init();   
    }
    
    #endif

/* [] END OF FILE */
