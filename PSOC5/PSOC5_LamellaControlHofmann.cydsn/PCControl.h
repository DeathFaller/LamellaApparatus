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

#ifndef PCControl_H
    #define PCControl_H
    
    #include <Includes.h>
    
    void requestConnection()
    {
        UART_PC_PutString("Request\n");
    }
    
    void sendLASERxReturn(int x,int tmp){
        char Meldung[10];
        itoa(x, Meldung, 10);
        UART_PC_PutString(Meldung);
        UART_PC_PutString("-");
        itoa(tmp, Meldung, 10);
        UART_PC_PutString(Meldung);
        UART_PC_PutString("\n");
    }    
    
    void sendRelaisxReturn(int x, int tmp){
        char Meldung[10];
        itoa(x, Meldung, 10);
        UART_PC_PutString(Meldung);
        UART_PC_PutString("-");
        itoa(tmp, Meldung, 10);
        UART_PC_PutString(Meldung);
        UART_PC_PutString("\n");
    }
// Change of 19062019   
//    void sendLASER1Return(int tmp){
//        char Meldung[10];
//        UART_PC_PutString("1-");
//        itoa(tmp, Meldung, 10);
//        UART_PC_PutString(Meldung);
//        UART_PC_PutString("\n");
//    }    
 
//    void sendLASER2Return(int tmp){
//        char Meldung[10];
//        UART_PC_PutString("2-");
//        itoa(tmp, Meldung, 10);
//        UART_PC_PutString(Meldung);
//        UART_PC_PutString("\n");
//    }
//    
//    void sendLASER3Return(int tmp){
//        char Meldung[10];
//        UART_PC_PutString("3-");
//        itoa(tmp, Meldung, 10);
//        UART_PC_PutString(Meldung);
//        UART_PC_PutString("\n");
//    }

    
//   void sendRelais1Return(int tmp){
//       char Meldung[10];
//       UART_PC_PutString("9-");
//       itoa(tmp, Meldung, 10);
//       UART_PC_PutString(Meldung);
//       UART_PC_PutString("\n");
//   }
//   
//   void sendRelais2Return(int tmp){
//       char Meldung[10];
//       UART_PC_PutString("0-");
//       itoa(tmp, Meldung, 10);
//       UART_PC_PutString(Meldung);
//       UART_PC_PutString("\n");
//   }
    
    void sendCompletion()
    {
        UART_PC_PutString("C\n");
    }
    
    void sendFailure()
    {
        UART_PC_PutString("F\n");   
    }
    
    void sendStatus()
    {
        char Meldung[10];
        UART_PC_PutString("!Measurement running: ");
        itoa(f_timer_LamellaLifetime_Measuring, Meldung, 10);
        UART_PC_PutString(Meldung);
        UART_PC_PutString("\n");
        
    }

//    void sendMeasurementData(short ADCValue, int timer, int laser1, int laser2){
//        char Meldung[30];
//        
//        UART_PC_PutString("d-");
//        itoa(laser1, Meldung, 10);
//        UART_PC_PutString(Meldung);
//        UART_PC_PutString("-");
//        itoa(laser2, Meldung, 10);
//        UART_PC_PutString(Meldung);
//        UART_PC_PutString("-");
//        itoa(timer, Meldung, 10);
//        UART_PC_PutString(Meldung);
//        UART_PC_PutString("-");
//        itoa(ADCValue, Meldung, 10);
//        UART_PC_PutString(Meldung);
//        UART_PC_PutString("\n");
//        
//    }
    void sendMeasurementData(short ADCValue, int timer, int laserstate){
        char Meldung[30];
        
        UART_PC_PutString("d-");
        itoa(laserstate, Meldung, 10);
        UART_PC_PutString(Meldung);
        UART_PC_PutString("-");
        itoa(timer, Meldung, 10);
        UART_PC_PutString(Meldung);
        UART_PC_PutString("-");
        itoa(ADCValue, Meldung, 10);
        UART_PC_PutString(Meldung);
        UART_PC_PutString("\n");
        
    }
    
    
//    void startPCControlMeasurement(){
//        f_timer_LamellaLifetime_Measuring = 0;
//        UART_PC_PutString("i-New Measurement\n");
//        #ifdef STEPPER
//            Move90Degree_CW();
//        #endif
//        for (int i = 0; i < g_LamellaFormationTime; i++){
//            CyDelay(1);   // Sleep 1 ms
//        }
//        t_timer_LamellaLifetime = 0;
//        #ifdef STEPPER
//            Move90Degree_CCW();
//        #endif
//        f_timer_LamellaLifetime_Measuring = 1;
//        //PCControl_Measurement();
//        
//    }
    
    void sendADCData(){
        char Meldung[30];
        UART_PC_PutString("f-");
        itoa(getADCValue(), Meldung, 10);
        UART_PC_PutString(Meldung);
        UART_PC_PutString("\n");
    }
    
    void pc_control(){
        // Init
        char Laserstate = 0;
        Nextion_SendString("page PC_Control");
        #ifdef DEBUG_PCControl
            UART_PC_PutString("#Started PC Control\n");
            char Test[10];
        #endif
        
        
        // Main
        
        while (g_ActivePage == 'P')
        {
            CyDelay(1);
            if (g_PC_InterruptSignal != 0){
                switch(g_PC_InterruptSignal)
                {
                    case 'Y':
                        #ifdef DEBUG_PCControl
                            UART_PC_PutString("#Connection Established\n");
                        #endif
                        sendCompletion();
                        break;
                    case 'Z':
                        requestConnection();
                        #ifdef DEBUG_PCControl
                            UART_PC_PutString("#Wait for Connection\n");
                        #endif 
                        break;
                    #ifdef STEPPER
                        case '+':           // Stepper clockwise
                            MoveOneStep_CW();
                            sendCompletion();
                            break;
                        case '-':           // Stepper counterclockwise
                            MoveOneStep_CCW();
                            sendCompletion();
                            break;
                        case '!':           // Stepper 90° clockwise
                            Move90Degree_CW();
                            sendCompletion();
                            break;
                        case '?':           // Stepper 90° counterclockwise
                            Move90Degree_CCW();
                            sendCompletion();
                            break;
                    #endif
                    case 'M':           // Starte Messung
                        f_timer_LamellaLifetime_Measuring = 1;
                        t_timer_LamellaLifetime = 0;
                        sendCompletion();
                        break;
                    case 'S':
                        f_timer_LamellaLifetime_Measuring = 0;
                        sendCompletion();
                        break;
                    case 'R':           // Request status
                        sendStatus();
                        sendCompletion();
                        break;
                    case 'L':           // Live Data
                        sendADCData();
                        sendCompletion();
                        break;
                    case 'D':           // MeasurementData
                        //sendMeasurementData(getADCValue(), t_timer_Measurement, GET_LASER1(), GET_LASER2());
                        sendMeasurementData(getADCValue(), t_timer_LamellaLifetime, Laserstate);
                        sendCompletion();
                        break;
                    case 'X':
                        
                        #ifdef DEBUG_PCControl
                            itoa(Laserstate, Test, 10);
                            UART_PC_PutString("#Laserstate: ");
                            UART_PC_PutString(Test);
                            UART_PC_PutString("\n");
                        #endif
                        if(Laserstate == 0)
                        {
                            LASER1(1);
                            LASER2(0);
                            #ifdef IRLASER
                                LASER3(0);  
                            #endif
                            Laserstate = 1;
                        }
                        else if(Laserstate == 1)
                        {
                            LASER1(0);
                            LASER2(0);
                            #ifdef IRLASER
                                LASER3(1);
                                Laserstate = 2;
                            #else
                                Laserstate = 0;
                            #endif

                        }else if(Laserstate == 2)
                        {
                            LASER1(0);
                            LASER2(1);
                            #ifdef IRLASER
                                LASER3(0);
                            #endif
                            Laserstate = 0;
                            
                        }
                        sendCompletion();
                        break;
                    case '1':
                        sendLASERxReturn(1, Toggle_LASER1());
                        sendCompletion();
                        break;
                    case '2':
                        sendLASERxReturn(2, Toggle_LASER2());
                        sendCompletion();
                        break;
                    case '3':
                        sendLASERxReturn(3, Toggle_LASER3());
                        sendCompletion();
                        break;
                    #ifdef Relais
                    case '9':
                        sendRelaisxReturn(9, Toggle_RELAIS1());
                        sendCompletion();
                        break;
                    case '0':
                        sendRelaisxReturn(0, Toggle_RELAIS2());
                        sendCompletion();
                        break;
                    #endif
                    default:
                        break;
                }
                
                
                Switch_PCInterrupt(0);
            }
        }
    }
    
    #endif

/* [] END OF FILE */
