from matplotlib.figure import Figure
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
import tkinter as tk
import tkinter.filedialog as fdiag
import numpy as np
import serial
import time
import datetime
import threading



def millisec():
    dt_obj = datetime.datetime.now()
    return dt_obj.timestamp() * 1000

def WaittimeUpdateMeasurementPlot(timer):
    if timer > 1000:
        return 1
    elif timer > 100:
        return 0.5
    else:
        return 0.25

class LamellaControl(tk.Tk):
    def __init__(self):
        tk.Tk.__init__(self)
        self.Port = "COM6"
        self.v_RuptureDetectionValue = 200                                  # Testweise
        
        
        self.Baudrate = 115200
        self.SerialPort = None
        self.Connected = False
        
        self.v_LaserSwitch = True
        
        self.LiveFig = None
        self.LiveAxis = None
        self.LiveADCValue = None
        self.MeasurementFig = None
        self.MeasurementAxis = None
        self.MeasurementPlotL0 = None
        self.MeasurementPlotL1 = None
        self.MeasurementPlotL2 = None
        
        self.Open_ControlWindow = False
        self.Open_AdditionalSettings = False
        self.Open_BigCounter = False
        self.PlotOfLiveData = False
        self.PlotOfMeasurementData = False
        self.LastMeasurementPlotUpdate = 0
        
        self.Waiting = False
        
        self.Grabbing = False
        self.Measuring = False
        self.MeasurementStarted = False
        self.MeasurementFinished = False
        
        self.LastMeasuringRequest = 0
        self.LastSwitchRequest = 0
        
        self.Messages = []
        
        
        self.Status_UV = False
        self.Status_Blue = False
        self.Time_UVOn = 0
        self.Time_UVOff = 0
        
        
        # Standard values for Measurement
        self.v_NumberMeasurements = 50
        self.v_ThresholdValue = 55                  # mV (Wert ohne Lamelle liegt bei etwa 40mV)
        self.v_FormationTime = 5000                 # ms
        self.v_RelaxationTime = 2500                # ms
        self.v_ConfirmationTime = 10000             # ms
        self.v_SwitchPeriod = 300                   # ms
        self.v_MaximumTime = 3600                   # s
        self.v_MeasurementCounter = -1              # Nummerierung beginnt bei 0
        self.v_NameOfSubstance = "Sample"
        
        self.WaitForCompletion = False
        self.SavingData = False
        self.SaveFolder = None
        self.ToDoList = []
        self.v_MeasurementDataCounter = 0
        self.v_MeasurementDataTimer_L0 = []
        self.v_MeasurementDataIntensity_L0 = []
        self.v_MeasurementDataTimer_L1 = []
        self.v_MeasurementDataIntensity_L1 = []
        self.v_MeasurementDataTimer_L2 = []
        self.v_MeasurementDataIntensity_L2 = []
        self.v_HandleMeasurementData = []
        self.v_LiveData = []
        
        
        self.v_StateLaser1 = False
        self.v_StateLaser2 = False
        self.v_StateLaser3 = False
        
        self.RuptureStart = 0
        self.RuptureConfirmed = False
        
        
        
       # self.handles = 0
        
        
        
        for i in range(0, 120):
            self.v_LiveData.append(2000)
            
        self.b_OpenPort = tk.Button(self, text="Open Port", width = 20, command = self.f_OpenPort)
        self.b_OpenPort.grid(row = 3, column = 0, sticky = tk.W)
        self.b_ClosePort = tk.Button(self, text="...", width = 20, command = self.f_ClosePort)
        self.b_ClosePort.grid(row = 4, column = 0, sticky = tk.W)

        self.b_ToggleGrabLiveData = tk.Button(self, text="Start Live Data Grabbing", bg = "red", width = 30, command = self.f_ToggleLiveDataGrabbing)
        self.b_ToggleGrabLiveData.grid(row = 7, column = 2, sticky = tk.W)
        
        self.b_Test = tk.Button(self, text="Test", width = 20, command = self.Test)
        self.b_Test.grid(row = 9, column = 0, sticky = tk.W)
        
        self.b_ShowLiveData = tk.Button(self, text="Show Live Data", width = 30, command = self.f_ShowLiveData)
        self.b_ShowLiveData.grid(row = 8, column = 2, sticky = tk.W)

        self.b_CloseProgram = tk.Button(self, text="Close Programm", width = 20, command = self.f_CloseProgram)
        self.b_CloseProgram.grid(row = 10, column = 0, sticky = tk.W)
        
        self.b_OpenControlWindow = tk.Button(self, text="Controls", width = 20, command=self.f_OpenControlWindow)
        self.b_OpenControlWindow.grid(row = 7, column = 0, sticky = tk.W)
        
        self.l_NameOfSubstance = tk.Label(self, text="Name der Probe")
        self.l_NameOfSubstance.grid(row = 0, column = 2, sticky = tk.W)
        self.e_NameOfSubstance = tk.Entry(self)
        self.e_NameOfSubstance.grid(row = 0, column = 3, sticky = tk.W)
        
        self.b_FolderSelect = tk.Button(self, text="Ordnerwahl", command=self.f_SelectFolder, width = 20)
        self.b_FolderSelect.grid(row = 0, column = 0, sticky = tk.W)
        self.e_FolderSelect = tk.Entry(self)
        self.e_FolderSelect.grid(row = 1, column = 0, sticky = tk.W)
        
        self.l_NumberMeasurements = tk.Label(self, text="Anzahl Messungen")
        self.l_NumberMeasurements.grid(row = 1, column = 2, sticky = tk.W)
        self.e_NumberMeasurements = tk.Entry(self)
        self.e_NumberMeasurements.grid(row = 1, column = 3, sticky = tk.W)

        self.l_SwitchPeriod = tk.Label(self, text="Periode Laser (ms)")
        self.l_SwitchPeriod.grid(row = 2, column = 2, sticky = tk.W)
        self.e_SwitchPeriod = tk.Entry(self)
        self.e_SwitchPeriod.grid(row = 2, column = 3, sticky = tk.W)

        self.l_MaximumTime = tk.Label(self, text = "Maximum time (s)")
        self.l_MaximumTime.grid(row = 3, column = 2, sticky = tk.W)
        self.e_MaximumTime = tk.Entry(self)
        self.e_MaximumTime.grid(row = 3, column = 3, sticky = tk.W)

        self.l_MeasurementCounter = tk.Label(self, text="Measurement counter")
        self.l_MeasurementCounter.grid(row = 0, column = 4, sticky = tk.W)
        self.e_MeasurementCounter = tk.Entry(self)
        self.e_MeasurementCounter.grid(row = 0, column = 5, sticky = tk.W)

        self.l_ConfirmationTime = tk.Label(self, text="Confirmation time (ms)")
        self.l_ConfirmationTime.grid(row = 1, column = 4, sticky = tk.W)
        self.e_ConfirmationTime = tk.Entry(self)
        self.e_ConfirmationTime.grid(row = 1, column = 5, sticky = tk.W)
        
        self.l_RelaxationTime = tk.Label(self, text="Relaxation time (ms)")
        self.l_RelaxationTime.grid(row = 2, column = 4, sticky = tk.W)
        self.e_RelaxationTime = tk.Entry(self)
        self.e_RelaxationTime.grid(row = 2, column = 5, sticky = tk.W)

        self.l_FormationTime = tk.Label(self, text = "Formation time (ms)")
        self.l_FormationTime.grid(row = 3, column = 4, sticky = tk.W)
        self.e_FormationTime = tk.Entry(self)
        self.e_FormationTime.grid(row = 3, column = 5, sticky = tk.W)

        self.l_TresholdValue = tk.Label(self, text="Treshold (mV)")
        self.l_TresholdValue.grid(row = 4, column = 4, sticky = tk.W)
        self.e_TresholdValue = tk.Entry(self)
        self.e_TresholdValue.grid(row = 4, column = 5, sticky = tk.W)
        
        self.l_UVOn = tk.Label(self, text="UV An nach x s")
        self.l_UVOn.grid(row = 4, column = 2, sticky = tk.W)
        self.e_UVOn = tk.Entry(self)
        self.e_UVOn.grid(row = 4, column = 3, sticky = tk.W)
        
        self.l_UVOff = tk.Label(self, text = "UV Aus nach x s")
        self.l_UVOff.grid(row = 5, column = 2, sticky = tk.W)
        self.e_UVOff = tk.Entry(self)
        self.e_UVOff.grid(row = 5, column = 3, sticky = tk.W)

        self.b_ResetValues = tk.Button(self, text="Reset", width = 30, command=self.f_ResetValues)
        self.b_ResetValues.grid(row = 5, column = 4, sticky = tk.W)
        
        self.b_RefreshParameters = tk.Button(self, text="Set Parameters", width = 30, command = self.f_SetParameters)
        self.b_RefreshParameters.grid(row = 5, column = 5, sticky = tk.W)
        
        self.b_ToggleMeasurement = tk.Button(self, text="Start Measurement", width = 30, bg= "red", command=self.f_ToggleMeasurement)
        self.b_ToggleMeasurement.grid(row = 7, column = 3, sticky = tk.W)
        
        self.b_ShowMeasurementData = tk.Button(self, text="Show Measurement Data", width = 30, command = self.f_ShowMeasurementData)
        self.b_ShowMeasurementData.grid(row = 8, column=3, sticky = tk.W)
        
        self.b_AdditionalSettings = tk.Button(self, text="Settings", width = 20, command = self.f_AdditionalSettings)
        self.b_AdditionalSettings.grid(row = 6, column = 0, sticky = tk.W)
        
        self.b_SaveParameters = tk.Button(self, text="Save Params", width = 30, command = self.f_SaveParameters)
        self.b_SaveParameters.grid(row = 6, column = 4, sticky = tk.W)
        
        self.b_LoadParameters = tk.Button(self, text="Load Params", width = 30, command = self.f_LoadParameters)
        self.b_LoadParameters.grid(row = 6, column = 5, sticky = tk.W)
        
        
        self.b_BigCounter = tk.Button(self, text="Counter", width = 30, command = self.f_BigCounter)
        self.b_BigCounter.grid(row = 9, column = 5, sticky = tk.W)
        
        
        self.l_ActualState = tk.Label(self, text="Status:", width=30)
        self.l_ActualState.grid(row = 8, column = 4, sticky = tk.W)
        self.e_ActualState = tk.Entry(self, width = 30)
        self.e_ActualState.grid(row = 8, column = 5, sticky = tk.W)
        
        # Added two loops for Requesting and Handling Measurement Data
        self.f_StartMeasurement()
        self.f_ResetValues()
        self.Watchdog_ToDoList()
        self.update()
        
    def f_BigCounter(self):
        if self.Open_BigCounter == False:
            BigCounter = tk.Toplevel()   
            self.Open_BigCounter = True
            
            def on_closing():
                self.Open_BigCounter = False
                time.sleep(0.5)
                BigCounter.destroy()
                
            BigCounter.protocol("WM_DELETE_WINDOW", on_closing)
        
            self.e_BigCounter = tk.Entry(BigCounter, font="Arial 60", width = 20)
            self.e_BigCounter.grid(row = 0, column = 0)
        
        
        
    def f_LoadParameters(self):
        with fdiag.askopenfile("r", defaultextension=".param") as f:
            for line in f.readlines():
                exec("self.%s"%line)
        self.f_ResetValues()
        self.e_ActualState.delete(0,'end')
        self.e_ActualState.insert(0, "Parameters loaded")
        pass
    
    def f_SaveParameters(self):
        with fdiag.asksaveasfile("w", defaultextension = ".param") as f:
            f.write(self.f_ReturnParameters())
        self.e_ActualState.delete(0,'end')
        self.e_ActualState.insert(0, "Parameters saved")
        pass
    
    def f_ToggleLaserSwitch(self):
        self.v_LaserSwitch = not self.v_LaserSwitch
        if self.v_LaserSwitch == True:
            self.b_LaserSwitch.config(bg="green")
        else:
            self.b_LaserSwitch.config(bg="red")
    
    def f_AdditionalSettings(self):
        if self.Open_AdditionalSettings == False:
            self.Open_AdditionalSettings = True
            AdditionalSettings = tk.Toplevel()
            
            def on_closing():
                self.Open_AdditionalSettings = False
                AdditionalSettings.destroy()
                
            AdditionalSettings.protocol("WM_DELETE_WINDOW", on_closing)
            
            self.b_LaserSwitch = tk.Button(AdditionalSettings, width = 20, text = "Toggle LaserSwitch",  command = self.f_ToggleLaserSwitch)
            self.b_LaserSwitch.grid(row = 0, column = 0, sticky=tk.W)
            
            b_Close = tk.Button(AdditionalSettings, width = 20, text="Close", command=on_closing)
            b_Close.grid(row = 100, column = 0, sticky=tk.W)
            
            # Add Settings
            # Welche Laser verwendet werden -> Haken
            # Lebenszeit-Bestimmung (Abschalten der MaxZeit)
        pass
        
        
    def f_SetLaser1(self, state):
        print("State: %s"%state)
        print("Laser: %s"%self.v_StateLaser1)
        if state != self.v_StateLaser1:
            self.f_SendSerial("1")
            #time.sleep(0.5)
            while self.WaitForCompletion:
                time.sleep(0.001)
                
        pass
    
    def f_SetLaser2(self, state):
        print("State: %s"%state)
        print("Laser: %s"%self.v_StateLaser2)
        if state != self.v_StateLaser2:
            self.f_SendSerial("2")
            self.WaitForCompletion == True
            while self.WaitForCompletion:
                time.sleep(0.001)
                
    def f_SetLaser3(self, state):
        print("State: %s"%state)
        print("Laser: %s"%self.v_StateLaser3)
        if state != self.v_StateLaser3:
            self.f_SendSerial("3")
            self.WaitForCompletion == True
            while self.WaitForCompletion:
                time.sleep(0.001)
        pass
        
    def f_SelectFolder(self):
        self.SaveFolder = fdiag.askdirectory()  
        self.e_FolderSelect.delete(0,'end')
        self.e_FolderSelect.insert(0, self.SaveFolder)
        
    def f_StartMeasurement(self):                       # Startet notwendige Funktionen fur Messungen, Steuerung der Aktivitat uber globale Variablen!
        t = threading.Thread(target = self.f_RequestMeasurementData)        # Anforderung Messdaten und Wechsel des Lasers, nur aktiv, wenn Messung gestartet wurde
        t.start()
        u = threading.Thread(target = self.f_HandleMeasurementData)         # Auswertung, lauft dauerhaft
        u.start()
        v = threading.Thread(target = self.HandleSerialRead)                # Empfang der seriellen Daten, dauerhaft aktiv
        v.start()
            
    
    def f_ToggleMeasurement(self):         
        self.f_GetParameters()
        self.MeasurementStarted = not self.MeasurementStarted
        #print("Measurement: %s"%self.MeasurementStarted)
        if self.MeasurementStarted == True:
            self.b_ToggleMeasurement.config(bg="green", text="Stop Measurement")
        else:
            self.f_SaveData()
            while self.SavingData == True:
                time.sleep(0.1)
            self.Measuring = False
            self.Waiting = False
            self.MeasurementFinished = True
            self.v_MeasurementCounter = 0
            self.b_ToggleMeasurement.config(bg="red", text="Start Measurement")
            self.f_SendSerial("S")
            pass
        pass
    
    
    
    def f_RequestMeasurementData(self):
        while True:
            if self.MeasurementFinished == True:
                self.MeasurementFinished = False
                self.b_ToggleMeasurement.config(bg ="cyan", text="New Measurement")
                self.e_ActualState.delete(0, 'end')
                self.e_ActualState.insert(0, "Finished")
                continue
            if self.MeasurementStarted == True:
                if self.Measuring == False:
                    while self.Waiting == True:                                                 # Warte auf etwaige andere Threads
                        time.sleep(0.1)                                                         #
                        #print("Sleep")                                                         #
                    while self.SavingData == True:                                              # Warte auf Beendigung der Speicherung
                        time.sleep(0.1)                                                         #
                    
                                                                                                # Reset der ErgebnisArrays vor Messstart!
                    self.v_MeasurementDataIntensity_L0 = []
                    self.v_MeasurementDataTimer_L0 = []
                    self.v_MeasurementDataIntensity_L1 = []
                    self.v_MeasurementDataTimer_L1 = []
                    
                    
                    
                    
                    while self.Status_Blue == False:
                        self.f_SendSerial("0")
                        time.sleep(0.2)
                    while self.Status_UV == True:
                        self.f_SendSerial("9")
                        time.sleep(0.2)
                        
                        
                    self.v_MeasurementCounter = self.v_MeasurementCounter + 1
                    self.e_MeasurementCounter.delete(0, 'end')
                    self.e_MeasurementCounter.insert(0, "%s"%self.v_MeasurementCounter)
                    if self.v_MeasurementCounter > self.v_NumberMeasurements:                   # Stoppe Messungen, wenn gewunschte Anzahl erreicht
                        self.MeasurementStarted = False                                         # Resette Variablen
                        self.MeasurementFinished = True                                         #
                        self.v_MeasurementCounter = 0                                           #
                    #print("Stepper 90 CW")
                    self.WaitForCompletion = True
                    self.Stepper_Deg90CW()                                                      # Fahre Stepper auf Homeposition
                    while self.WaitForCompletion == True:                                       # Warte auf Beendigung der Fahrt
                        time.sleep(0.1)                                                         #
                    help_Formationtime = millisec()                                             # Setze Start der Lamellenformation
                    #print("Formtime: %s"%help_Formationtime)                                   #
                    #print("v-Formtime: %s"%self.v_FormationTime)                               #
                    while ((millisec() - help_Formationtime) < self.v_FormationTime):           # Warte fur eingestellte Zeit auf Bildung der Lamelle
                        time.sleep(0.1)                                                         #
                    #print("Stepper 90 CCW")                                                    #
                    self.WaitForCompletion = True                                               #
                    self.Stepper_Deg90CCW()                                                     # Fahre Stepper auf Messposition
                    while self.WaitForCompletion == True:                                       # Warte auf Beendigung der Fahr
                        time.sleep(0.1)                                                         #
                    self.Measuring = True                                                       #
                    self.WaitForCompletion = True                                               #
                    self.f_SendSerial("M")                                                      # Starte Timer am PSoC, fur Messergebnisse
                    while (self.WaitForCompletion == True):                                     # Warte auf Bestatigung des Befehls
                        time.sleep(1/1000/1000)                                                 #
                    self.LastMeasuringRequest = millisec() - self.v_SwitchPeriod/2              # Setze letzte Datenanforderung auf Start, sorge fur Abstand zwischen Wechsel und Anforderung
                    #self.LastMeasuringRequest = millisec() + 5                                                                           # Abstand notig um Laser die Chance zu geben sich einzupendeln 
                    self.LastSwitchRequest = millisec()                                         # Setze letzten Laserwechsel auf Start
                
                
                
                
                else:                                                                           # Messung laufend
                    timenow = millisec()
                    if ((timenow - self.LastMeasuringRequest) > self.v_SwitchPeriod):
                        self.f_SendSerial("D")                                                  # Fordere Daten an
                        #print("D: %s"%millisec())
                        #print("Waiting: %s"%int(self.SerialPort.inWaiting()))
                        self.LastMeasuringRequest = timenow
                        #print("Measure: %s"%millisec())
                        pass
                    if self.v_LaserSwitch == True:
                        if ((timenow - self.LastSwitchRequest) > self.v_SwitchPeriod):
                            self.f_SendSerial("X")                                              # Sende Switch Befehl fur Laser
                            #print("X: %s"%millisec())
                            self.LastSwitchRequest = timenow
                            #print("Switch: %s"%millisec())
                            pass
                        else:
                            pass
                pass
            else:
                time.sleep(0.5)
        pass

    def f_HandleMeasurementData(self):                                  # Laeuft in eigenem Thread
        RuptureStart = 0
        RuptureConfirmed = False
        timer = 0
        timer_vorher = 0                                                # dient der Aktualisierung des Timers in 0.2 Sekunden Abstanden
        
        Rupture_0_Confirmed = False
        Rupture_1_Confirmed = False
        Rupture_2_Confirmed = False
        while True:
            if self.SerialPort != None and self.SerialPort.isOpen():
                if RuptureConfirmed:
                    #Verarbeitung der Messdaten
                    self.Waiting = True
                    self.Measuring = False


                if len(self.v_HandleMeasurementData) != 0:
                    #print(len(self.v_HandleMeasurementData))
                    data = self.v_HandleMeasurementData[0]              # Auswertung der erhaltenen Daten "L-0-1000-100"
                    self.v_HandleMeasurementData.pop(0)
                    data = data.split("-")
                    laser = int(data[1])
                    timer = int(data[2]) / 1000.0
                    inten = int(data[3]) / 2
                    
                    if timer == 0.0:                                    # Abfangen des Neustarts des Systems
                        RuptureConfirmed = True
                        tmp_StateLaser1 = self.v_StateLaser1
                        tmp_StateLaser2 = self.v_StateLaser2
                        
                        self.f_SendSerial("1")
                        self.f_SendSerial("2")
                        
                        time.sleep(200)
                        if self.v_StateLaser1 != tmp_StateLaser1:
                            self.f_SendSerial("1")
                        if self.v_StateLaser2 != tmp_StateLaser2:
                            self.f_SendSerial("2")
                        
                        
                        self.f_SetLaser1(state)
#                    print("Timer: %s"%timer)
#                    print("Inten: %s"%inten)
#                    print("Schwellwert: %s"%self.v_ThresholdValue)
                    
                    # Umschalten Relais
                    
                    if timer >= self.Time_UVOff:
                        if self.Status_UV == True:
                            self.f_SendSerial("9")
                        if self.Status_Blue == False:
                            self.f_SendSerial("0")
                    elif timer >= self.Time_UVOn:
                        if self.Status_UV == False:
                            self.f_SendSerial("9")
                        if self.Status_Blue == True:
                            self.f_SendSerial("0")
                    
                    if timer >= self.v_MaximumTime:
                        RuptureConfirmed = True
                    elif timer < (self.v_RelaxationTime/1000.0):
                        RuptureConfirmed = False
                        RuptureStart = 0
                    elif inten <= self.v_ThresholdValue:                # Wert unter Schwellwert -> Lamelle gerissen
                        if RuptureStart == 0:   
                            RuptureStart = millisec()
                        else:                                           # Uberprufen ob Wert fur Bestatigungszeit unterhalb bleibt!
                            if ((millisec() - RuptureStart) >= self.v_ConfirmationTime):
                                RuptureConfirmed = True
                    else:
                        RuptureStart = 0
                        RuptureConfirmed = False
                            
                    if (laser == 0):
                        self.v_MeasurementDataIntensity_L0.append(inten)
                        self.v_MeasurementDataTimer_L0.append(timer)
                        
                        if len(self.v_MeasurementDataIntensity_L0) > 100:
                            Vorher = np.mean(self.v_MeasurementDataIntensity_L0[-100:-51])
                            Nachher = np.mean(self.v_MeasurementDataIntensity_L0[-50:-1])
                            
                            if Nachher <= self.v_ThresholdValue:
                                if ((Vorher - Nachher) > self.v_RuptureDetectionValue):
                                    Rupture_0_Confirmed = True
                    elif (laser == 1):
                        self.v_MeasurementDataIntensity_L1.append(inten)
                        self.v_MeasurementDataTimer_L1.append(timer)
                          
                        if len(self.v_MeasurementDataIntensity_L1) > 100:
                            Vorher = np.mean(self.v_MeasurementDataIntensity_L1[-100:-51])
                            Nachher = np.mean(self.v_MeasurementDataIntensity_L1[-50:-1])
                            
                            if Nachher <= self.v_ThresholdValue:
                                if ((Vorher - Nachher) > self.v_RuptureDetectionValue):
                                    Rupture_1_Confirmed = True
                        
                    elif (laser == 2):
                        self.v_MeasurementDataIntensity_L2.append(inten)
                        self.v_MeasurementDataTimer_L2.append(timer)  

                        if len(self.v_MeasurementDataIntensity_L2) > 100:
                            Vorher = np.mean(self.v_MeasurementDataIntensity_L2[-100:-51])
                            Nachher = np.mean(self.v_MeasurementDataIntensity_L2[-50:-1])
                            
                            if Nachher <= self.v_ThresholdValue:
                                if ((Vorher - Nachher) > self.v_RuptureDetectionValue):
                                    Rupture_2_Confirmed = True

                    if timer >= (self.v_RelaxationTime/1000.0):
                        if Rupture_0_Confirmed == True:
                            if Rupture_1_Confirmed == True:
                                pass
                                #RuptureConfirmed = True
                elif int(self.SerialPort.inWaiting()) == 0:
                    if RuptureConfirmed == True:
                        self.f_SendSerial("S")
                        self.WaitForCompletion = True
                        t = threading.Thread(target = self.f_SaveData)
                        t.start()
                        while self.WaitForCompletion == True:
                            time.sleep(0.1)
                        while self.SavingData == True:
                            time.sleep(0.1)
                        RuptureConfirmed = False
                        RuptureStart = 0
                        self.Waiting = False  
                        timer_vorher = 0
                time.sleep(0.001)
                if self.Measuring == True:
                    #if ((millisec() - self.LastMeasurementPlotUpdate) > WaittimeUpdateMeasurementPlot(timer)):
                    if ((millisec() - self.LastMeasurementPlotUpdate) > 0.5):
                        self.ToDoList.append("M")
                        self.LastMeasurementPlotUpdate = millisec()
                    #if (timer - 0.2) > timer_vorher:
                        #timer_vorher = timer
                        self.e_ActualState.delete(0,'end')
                        self.e_ActualState.insert(0, "%s"%timer)
                        if self.Open_BigCounter == True:
                            self.e_BigCounter.delete(0, 'end')
                            self.e_BigCounter.insert(0, "%s"%timer)
#                
    def f_SaveData(self):
        self.SavingData = True
        print("Saving")
        if self.SaveFolder == None:
            name = "%s-%s"%(self.v_NameOfSubstance,self.v_MeasurementCounter)
        else:
            name = "%s/%s-%s"%(self.SaveFolder, self.v_NameOfSubstance, self.v_MeasurementCounter)
            
        with open("%s_0.rawlam"%name, "w") as f:
            f.write("time / s \t Intensity / mV\n")
            for i in range(0, len(self.v_MeasurementDataIntensity_L0)):
                f.write("%s\t%s\n"%(self.v_MeasurementDataTimer_L0[i],self.v_MeasurementDataIntensity_L0[i]))
        with open("%s_1.rawlam"%name, "w") as f:
            f.write("time / s \t Intensity / mV\n")
            for i in range(0, len(self.v_MeasurementDataIntensity_L1)):
                f.write("%s\t%s\n"%(self.v_MeasurementDataTimer_L1[i],self.v_MeasurementDataIntensity_L1[i]))
        with open("%s_2.rawlam"%name, "w") as f:
            f.write("time / s \t Intensity / mV\n")
            for i in range(0, len(self.v_MeasurementDataIntensity_L2)):
                f.write("%s\t%s\n"%(self.v_MeasurementDataTimer_L2[i],self.v_MeasurementDataIntensity_L2[i]))
        
        self.v_MeasurementDataIntensity_L0 = []
        self.v_MeasurementDataTimer_L0 = []
        self.v_MeasurementDataIntensity_L1 = []
        self.v_MeasurementDataTimer_L1 = []
        self.v_MeasurementDataIntensity_L2 = []
        self.v_MeasurementDataTimer_L2 = []
        print("Saving Finished")
        self.SavingData = False
        
    def f_ShowMeasurementData(self):
        if self.PlotOfMeasurementData == False:
            MeasurementData = tk.Toplevel()
            self.PlotOfMeasurementData = True

            def on_closing():
                self.PlotOfMeasurementData = False
                MeasurementData.destroy()

            MeasurementData.protocol("WM_DELETE_WINDOW", on_closing)
        
            self.MeasurementFig = Figure(figsize = (9,6), facecolor="white")
            self.MeasurementAxis = self.MeasurementFig.add_subplot(111)
            
            self.MeasurementPlotL0, = self.MeasurementAxis.plot([0, 0], [0, 0], "-r", label="red")
        
            self.MeasurementPlotL1, = self.MeasurementAxis.plot([0, 0], [0, 0], "-g", label="green")
            
            self.MeasurementPlotL2, = self.MeasurementAxis.plot([0, 0], [0, 0], "-b", label="IR")
        
            self.MeasurementAxis.set_ylabel("Intensity (mV)")

            self.MeasurementAxis.set_xlabel("t / s")
            self.MeasurementAxis.legend()
            self.MeasurementAxis.grid()
        
            canvas = FigureCanvasTkAgg(self.MeasurementFig, master = MeasurementData)
            canvas._tkcanvas.pack(side=tk.TOP, fill=tk.BOTH, expand=1)
        

    def Test(self):
        pass
        # Finished (vorlaeufig)
        
    def f_ResetValues(self):
        self.e_TresholdValue.delete(0, 'end')
        self.e_FormationTime.delete(0, 'end')       
        self.e_NumberMeasurements.delete(0, 'end')
        self.e_SwitchPeriod.delete(0, 'end')
        self.e_MaximumTime.delete(0, 'end')
        self.e_MeasurementCounter.delete(0, 'end')
        self.e_ConfirmationTime.delete(0, 'end')
        self.e_RelaxationTime.delete(0, 'end')
        self.e_NameOfSubstance.delete(0,'end')
        self.e_UVOff.delete(0,'end')
        self.e_UVOn.delete(0,'end')
        
        self.e_TresholdValue.insert(0, "%s"%self.v_ThresholdValue)
        self.e_FormationTime.insert(0, "%s"%self.v_FormationTime)        
        self.e_NumberMeasurements.insert(0, "%s"%self.v_NumberMeasurements)
        self.e_SwitchPeriod.insert(0, "%s"%self.v_SwitchPeriod)
        self.e_MaximumTime.insert(0, "%s"%self.v_MaximumTime)
        self.v_MeasurementCounter = 0
        self.e_MeasurementCounter.insert(0, "%s"%self.v_MeasurementCounter)
        self.e_ConfirmationTime.insert(0, "%s"%self.v_ConfirmationTime)
        self.e_RelaxationTime.insert(0, "%s"%self.v_RelaxationTime)
        self.e_NameOfSubstance.insert(0, "%s"%self.v_NameOfSubstance)
        self.e_UVOff.insert(0, "%s"%self.Time_UVOff)
        self.e_UVOn.insert(0, "%s"%self.Time_UVOn)
    
    
    def f_ReturnParameters(self):
        string = ""
        
        string = string + "v_NumberMeasurements = int(%s)\n"%self.v_NumberMeasurements
        string = string + "v_Confirmation = int(%s)\n"%self.v_ConfirmationTime
        string = string + "v_FormationTime = %s\n"%self.v_FormationTime
        string = string + "v_RelaxationTime = %s\n"%self.v_RelaxationTime
        string = string + "v_SwitchPeriod = %s\n"%self.v_SwitchPeriod
        string = string + "v_ThresholdValue = %s\n"%self.v_ThresholdValue
        string = string + "v_NameOfSubstance = \"%s\"\n"%self.v_NameOfSubstance
        string = string + "v_MaximumTime = %s\n"%self.v_MaximumTime
        #print(string)      
        return string
    
    def f_SetParameters(self):
        self.f_GetParameters()
        Bestatigung = tk.Toplevel()
        
        def Close():
            Bestatigung.destroy()
        l_Bestatigung = tk.Label(Bestatigung, text="Parameters got set")
        l_Bestatigung.grid(row = 0, column = 0)
        
        b_Bestatigung = tk.Button(Bestatigung, text="Close", command=Close)
        b_Bestatigung.grid(row = 0, column = 1)
        
    def f_GetParameters(self):
        self.v_NumberMeasurements = int(self.e_NumberMeasurements.get())
        self.v_ConfirmationTime = int(self.e_ConfirmationTime.get())
        self.v_FormationTime = int(self.e_FormationTime.get())
        self.v_RelaxationTime = int(self.e_RelaxationTime.get())
        self.v_SwitchPeriod = int(self.e_SwitchPeriod.get())
        self.v_ThresholdValue = int(self.e_TresholdValue.get())
        self.v_NameOfSubstance = str(self.e_NameOfSubstance.get())
        self.v_MaximumTime = int(self.e_MaximumTime.get())
        self.Time_UVOff = int(self.e_UVOff.get())
        self.Time_UVOn = int(self.e_UVOn.get())

        #self.f_ReturnParameters()
    
        
        
    def Watchdog_ToDoList(self):                    # dient der Aktualisierung der Plots
        LastToDo = ""
        while len(self.ToDoList) > 0:
            if self.ToDoList == LastToDo:
                continue
            if self.ToDoList[0] == "L":
                #Update Live Plot mit Setup Daten
                LastToDo = "L"
                self.f_UpdateLivePlot()
            elif self.ToDoList[0] == "M":
                # Update Measurement Plot mit Daten
                LastToDo = "M"
                self.f_UpdateMeasurementPlot()
            self.ToDoList.pop(0)
            pass
        self.after(100, self.Watchdog_ToDoList)
        
    def f_UpdateMeasurementPlot(self):
        if self.PlotOfMeasurementData == True:
            if len(self.v_MeasurementDataTimer_L0) > 0:
                self.MeasurementAxis.set_xlim(0, int(self.v_MeasurementDataTimer_L0[-1]+5))
            else:
                self.MeasurementAxis.set_xlim(0, 1)
            self.MeasurementPlotL0.set_data(self.v_MeasurementDataTimer_L0, self.v_MeasurementDataIntensity_L0)
            self.MeasurementPlotL1.set_data(self.v_MeasurementDataTimer_L1, self.v_MeasurementDataIntensity_L1)
            self.MeasurementPlotL2.set_data(self.v_MeasurementDataTimer_L2, self.v_MeasurementDataIntensity_L2)
            self.MeasurementAxis.set_ylim(0,2048)
            self.MeasurementFig.canvas.draw()
            self.MeasurementFig.canvas.flush_events()
        
    def f_UpdateLivePlot(self):
        if self.PlotOfLiveData == True:
            self.LiveADCValue.set_ydata(self.v_LiveData)
            self.LiveFig.canvas.draw()
            self.LiveFig.canvas.flush_events()
        
    def f_ToggleLiveDataGrabbing(self):
        if self.SerialPort.isOpen() == True:
            self.Grabbing = not self.Grabbing
            if self.Grabbing == True:
                if self.PlotOfLiveData == False:
                    self.f_ShowLiveData()
                self.b_ToggleGrabLiveData.config(bg="green", text="Stop Live Data Grabbing")
                t = threading.Thread(target = self.RequestLiveData)
                t.start()
            else:
                self.b_ToggleGrabLiveData.config(bg="red", text="Start Live Data Grabbing")
        
    def RequestLiveData(self):
        while self.Grabbing == True:
            self.f_SendSerial("L")
            time.sleep(100.0/1000.0)
    
    
    def f_OpenControlWindow(self):
        if self.Open_ControlWindow == False:
            Control = tk.Toplevel()
            self.Open_ControlWindow = True
            
            
            def on_closing():
                self.Open_ControlWindow = False
                Control.destroy()
                
            Control.protocol("WM_DELETE_WINDOW", on_closing)
            
            def f_Laser1():
                self.f_SendSerial("1")
            
            def f_Laser2():
                self.f_SendSerial("2")

            def f_Laser3():
                self.f_SendSerial("3")

            def f_Relais1():
                self.f_SendSerial("9")
                
            def f_Relais2():
                self.f_SendSerial("0")


            def GetLamella():
                OldState = self.Grabbing
                self.Grabbing = False
                self.Stepper_Deg90CW()
                self.f_GetParameters()
                time.sleep(self.v_FormationTime/1000)
                self.Stepper_Deg90CCW()
                self.Grabbing = OldState

            # 200 Steps entsprechen 90 Grad
            def MoveCW():
                OldStateLaser1 = self.v_StateLaser1             # Laser vorubergehend ausschalten, um etwaige Reflexionen am Glas zu verhindern
                OldStateLaser2 = self.v_StateLaser2
                self.f_SetLaser1(False)
                self.f_SetLaser2(False)
                OldState = self.Grabbing
                self.Grabbing = False
                Count = int(int(e_CountStepCW.get())/90*200)
                for i in range(0, Count):
                    self.Stepper_StepCW()
                    e_CountStepCW.delete(0, 'end')
                    e_CountStepCW.insert(0, "%s von %s"%(i, Count))
                self.Grabbing = OldState
                self.f_SetLaser1(OldStateLaser1)
                self.f_SetLaser2(OldStateLaser2)

            def MoveCCW():
                OldStateLaser1 = self.v_StateLaser1             # Laser vorubergehend ausschalten, um etwaige Reflexionen am Glas zu verhindern
                OldStateLaser2 = self.v_StateLaser2
                self.f_SetLaser1(False)
                self.f_SetLaser2(False)
                OldState = self.Grabbing
                self.Grabbing = False
                Count = int(int(e_CountStepCCW.get())/90*200)
                for i in range(0, Count):
                    self.Stepper_StepCCW()
                    e_CountStepCCW.delete(0, 'end')
                    e_CountStepCCW.insert(0, "%s von %s"%(i+1, Count))
                self.Grabbing = OldState
                self.f_SetLaser1(OldStateLaser1)
                self.f_SetLaser2(OldStateLaser2)
            
            b_StepCW = tk.Button(Control, text="1 CW", width = 5, height = 2, command = self.Stepper_StepCW)
            b_StepCW.grid(row = 0, column = 2)
            b_StepCCW = tk.Button(Control, text="1 CCW", width = 5, height = 2, command = self.Stepper_StepCCW)
            b_StepCCW.grid(row = 1, column = 2)
            
            e_CountStepCW = tk.Entry(Control)
            e_CountStepCW.grid(row = 0, column = 3)
            e_CountStepCCW = tk.Entry(Control)
            e_CountStepCCW.grid(row = 1, column = 3)
            
            b_GetLamella = tk.Button(Control, text="Get Lamella", width = 20, height = 2, command=GetLamella)
            b_GetLamella.grid(row=2, column = 3)
            
            b_CountStepCW = tk.Button(Control, text="x deg CW", width = 8, height = 2, command = MoveCW)
            b_CountStepCW.grid(row = 0, column = 4)
            
            b_CountStepCCW = tk.Button(Control, text="x deg CCW", width = 8, height = 2, command = MoveCCW)
            b_CountStepCCW.grid(row = 1, column = 4)
            
            
            b_Deg90CW = tk.Button(Control, text="90 CW", width = 8, height = 2, command = self.Stepper_Deg90CW)
            b_Deg90CW.grid(row = 0, column = 5)
            b_Deg90CCW = tk.Button(Control, text="90 CCW", width = 8, height = 2, command = self.Stepper_Deg90CCW)
            b_Deg90CCW.grid(row = 1, column = 5)
            
            self.b_Laser1 = tk.Button(Control, text="L1", width = 8, height = 2, command = f_Laser1)
            self.b_Laser1.grid(row = 0, column = 6)
            self.b_Laser2 = tk.Button(Control, text="L2", width = 8, height = 2, command = f_Laser2)
            self.b_Laser2.grid(row = 1, column = 6)
            self.b_Laser3 = tk.Button(Control, text="L3 (IR)", width = 8, height = 2, command = f_Laser3)
            self.b_Laser3.grid(row = 2, column = 6)
            
            
            self.b_Relais1 = tk.Button(Control, text="R1 - UV", width = 8, height = 2, command = f_Relais1)
            self.b_Relais1.grid(row = 0, column = 7)
            self.b_Relais2 = tk.Button(Control, text="R2 - Blue", width = 8, height = 2, command = f_Relais2)
            self.b_Relais2.grid(row = 1, column = 7)
            
            
            
        else:
            pass

    def Stepper_StepCW(self):
        self.f_SendSerial("+")
        self.WaitForCompletion = True
        while self.WaitForCompletion == True:
            time.sleep(0.001)
    
    def Stepper_StepCCW(self):
        self.f_SendSerial("-")
        self.WaitForCompletion = True
        while self.WaitForCompletion == True:
            time.sleep(0.001)
    
    def Stepper_Deg90CW(self):
#        OldStateLaser1 = self.v_StateLaser1             # Laser vorubergehend ausschalten, um etwaige Reflexionen am Glas zu verhindern
 #       OldStateLaser2 = self.v_StateLaser2
  #      self.f_SetLaser1(False)
   #     self.f_SetLaser2(False)
        self.f_SendSerial("!")
        self.WaitForCompletion = True
        while self.WaitForCompletion == True:
            time.sleep(0.001)
      #  self.f_SetLaser1(OldStateLaser1)
       # self.f_SetLaser2(OldStateLaser2)
    
    def Stepper_Deg90CCW(self):
        
     #   OldStateLaser1 = self.v_StateLaser1             # Laser vorubergehend ausschalten, um etwaige Reflexionen am Glas zu verhindern
      #  OldStateLaser2 = self.v_StateLaser2
       # self.f_SetLaser1(False)
        #self.f_SetLaser2(False)
        #print("OldState: %s"%OldStateLaser1)
        self.f_SendSerial("?")
        self.WaitForCompletion = True
        while self.WaitForCompletion == True:
            time.sleep(0.001)
      #  self.f_SetLaser1(OldStateLaser1)
       # self.f_SetLaser2(OldStateLaser2)
        
    def f_ShowLiveData(self):
        if self.PlotOfLiveData == False:
            self.f_OpenControlWindow()
            LiveData = tk.Toplevel()
            self.PlotOfLiveData = True
                    
            def on_closing():
                self.f_SetLaser1(False)                 # Laser abschalten, da nicht notwendig, wenn keine Livedaten angezeigt werden (Nur fuer einstellen!)
                self.f_SetLaser2(False)
                self.PlotOfLiveData = False
                LiveData.destroy()
                
            LiveData.protocol("WM_DELETE_WINDOW", on_closing)
            self.LiveFig = Figure(figsize = (9,6), facecolor="white")
            self.LiveAxis = self.LiveFig.add_subplot(111)
            
            x = []
            for i in range(-120,0):
                x.append(int(i/2))
    
            
            self.LiveADCValue, = self.LiveAxis.plot(x, self.v_LiveData, "-r", label="")
            
            self.LiveAxis.set_xticks([0,10,20,30,40,50,60])
            self.LiveAxis.set_yticks([0,500,1000,1500,2000])
            self.LiveAxis.set_ylabel("Intensity (mV)")
            self.LiveAxis.set_xlim(-60,0)
            self.LiveAxis.set_ylim(0,2048)
            self.LiveAxis.set_xlabel("x")
            
            self.LiveAxis.legend()
            self.LiveAxis.grid()
            
            canvas = FigureCanvasTkAgg(self.LiveFig, master = LiveData)
            canvas._tkcanvas.pack(side=tk.TOP, fill=tk.BOTH, expand=1)
        
    def StartSerialReads(self):
        t = threading.Thread(target = self.GetSerialReads)
        t.start()
        pass
 
    def GetSerialReads(self):
        while self.SerialPort.isOpen() == True:
            try:
                while int(self.SerialPort.inWaiting()) > 0:
                    Message = self.SerialPort.readline().decode("UTF-8")
                    #self.HandleSerialRead(Message)
                    self.Messages.append(Message)
                    #print(Message)
            finally:
                pass
            
            
            
    def HandleSerialRead(self):
        while True:
            if len(self.Messages)>0:
                data = self.Messages[0]
                self.Messages.pop(0)
                if data[0] == "C":
                    if self.WaitForCompletion == True:
                        if (int(self.SerialPort.inWaiting()) > 0):
                            print("Wait for empty RX Buffer")
                        else:
                            self.WaitForCompletion = False
                elif data[0] == "f":
                    self.v_LiveData.pop(0)
                    self.v_LiveData.append(float(data.split("-")[1])/2)
                    self.ToDoList.append("L")
            
                elif data[0] == "#":
                    print("DEBUG: %s"%data)
                elif data[0] == "d":
                    self.v_HandleMeasurementData.append(data)
                    
                elif data[0] == "0":
                    tmp = int(data.split("-")[1])
                    if tmp == 0:
                        self.Status_Blue = False
                    else:
                        self.Status_Blue = True
                elif data[0] == "9":
                    tmp = int(data.split("-")[1])
                    if tmp == 0:
                        self.Status_UV = False
                    else:
                        self.Status_UV = True
                    pass
                if self.Open_ControlWindow == True:
                    if data[0] == "1":
                        tmp = int(data.split("-")[1])
                        if tmp == 0:
                            self.b_Laser1.config(bg="red")
                            self.v_StateLaser1 = False
                        else:
                            self.b_Laser1.config(bg="green")
                            self.v_StateLaser1 = True

                    if data[0] == "2":
                        tmp = int(data.split("-")[1])
                        if tmp == 0:
                            self.b_Laser2.config(bg="red")
                            self.v_StateLaser2 = False

                        else:
                            self.b_Laser2.config(bg="green")
                            self.v_StateLaser2 = True
                    
                    if data[0] == "3":
                        tmp = int(data.split("-")[1])
                        if tmp == 0:
                            self.b_Laser3.config(bg="red")
                            self.v_StateLaser3 = False

                        else:
                            self.b_Laser3.config(bg="green")
                            self.v_StateLaser3 = True
                    
                    if data[0] == "9":
                        tmp = int(data.split("-")[1])
                        if tmp == 0:
                            self.b_Relais1.config(bg="red")
                        else:
                            self.b_Relais1.config(bg="green")

                    if data[0] == "0":
                        tmp = int(data.split("-")[1])
                        if tmp == 0:
                            self.b_Relais2.config(bg="red")
                        else:
                            self.b_Relais2.config(bg="green")
                            
                        
                
                            
                    pass
            else:
                time.sleep(1/1000/1000)
                
                
    def f_IsConnected(self):
        self.Connected = self.SerialPort.isOpen()
        if self.Connected == True:
            self.b_OpenPort.config(text="Connected", bg = "green")
            self.b_ClosePort.config(text = "Disconnect")
        else:
            self.b_OpenPort.config(text="Open Port", bg = "red")
            self.b_ClosePort.config(text="Not connected")
        
    def f_SendSerial(self, command):
        self.SerialPortBlocked = True
        self.SerialPort.write(command.encode())
        self.SerialPortBlocked = False
 
    def f_CloseProgram(self):
        try:
            self.SerialPort.close()
        finally:
            self.destroy()
 
    def f_ClosePort(self):
        try:
            self.SerialPort.close()
        finally:
            self.f_IsConnected()
            

    def f_OpenPort(self):
        SelectPortWindow = tk.Toplevel()
        def Connect():
            self.Port = e_Port.get()
            self.SerialPort = serial.Serial()
            self.SerialPort.baudrate = int(self.Baudrate)
            self.SerialPort.port = self.Port
            self.SerialPort.timeout = 1
            self.SerialPort.open()
            self.f_SendSerial("Y")
            self.f_IsConnected()
            self.StartSerialReads()
            self.f_SetLaser1(False)
            self.f_SetLaser2(False)
            SelectPortWindow.destroy()
            
            
        def Close():
            SelectPortWindow.destroy()

        SelectPortWindow.title("Select Port to open")
        
        l_Port = tk.Label(SelectPortWindow, text="Port")
        l_Port.grid(row=0, column=0)
        e_Port = tk.Entry(SelectPortWindow)
        e_Port.grid(row=0, column=1)
        e_Port.insert(0, self.Port)
        
        l_Baudrate = tk.Label(SelectPortWindow, text="Baudrate")
        l_Baudrate.grid(row=1, column=0)
        e_Baudrate = tk.Entry(SelectPortWindow)
        e_Baudrate.grid(row=1, column=1)
        e_Baudrate.insert(0, "%s"%self.Baudrate)
        
        b_Connect = tk.Button(SelectPortWindow, text="Connect", command=Connect)
        b_Connect.grid(row=5, column=0)
        b_Close = tk.Button(SelectPortWindow, text="Close", command=Close)
        b_Close.grid(row=5, column=1)         
    
    
def main():
    App = LamellaControl()
    App.mainloop()    
        
if __name__ == "__main__":
    main()
    