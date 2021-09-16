from matplotlib.figure import Figure
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg

import tkinter as tk
import numpy as np
import SuppModules.GetFileList as GFL
import SuppModules.SaveFile as SF
import scipy.optimize as spop


def SortAndDeleteItems(ItemList):
    ItemList.sort()
    delete = []
    for i in range(1, len(ItemList)):
        if ItemList[i - 1] == ItemList[i]:
            delete.append(i - 1)
        
    for i in range(0, len(delete)):
        ItemList.pop(
            delete[
                len(delete)
                - i
                - 1
            ]
        )
    return ItemList


def _ExponentialDecay(x, a, b, c):      # NOQA: VNE001
    return a + b * np.exp(-c * x)             # NOQA: VNE001


class FindThicknesses(tk.Tk):
    def key(self, event):
        if event.keycode == 87:        # w
            self.f_UP()
        if event.keycode == 68:        # d
            self.f_RIGHT()
        if event.keycode == 65:        # a
            self.f_LEFT()
        if event.keycode == 83:        # s
            self.f_DOWN()
        if event.keycode == 67:        # c
            self.f_CONFIRM()
    
    def __init__(
        self,
        filelist=None,
        DEBUG=False
    ):
        tk.Tk.__init__(self)
        self.DEBUG = DEBUG
        
        self.bind("<Key>", self.key)
        
        self.LiveFig = None
        self.LiveAxis = None
        self.LiveValues = []

        self.x_Values = []
        self.Selection = []
        self.HelpPoint = [0, 0]
        self.HelpPointValues = [0, 0]
        self.PlotOfHelpPoint = None
        self.PlotOfSelection = []
        self.PlotOfFit = None
        
        self.data = []
        
        self.b_Up = tk.Button(
            self,
            text="Up",
            width=20,
            command=self.f_UP
        )
        self.b_Up.grid(
            row=2,
            column=4
        )
        
        self.b_Down = tk.Button(
            self,
            text="Down",
            width=20,
            command=self.f_DOWN
        )
        self.b_Down.grid(
            row=4,
            column=4
        )
        
        self.b_Left = tk.Button(
            self,
            text="Left",
            width=20,
            command=self.f_LEFT
        )
        self.b_Left.grid(
            row=3,
            column=3
        )
        
        self.b_Right = tk.Button(
            self,
            text="Right",
            width=20,
            command=self.f_RIGHT
        )
        self.b_Right.grid(
            row=3,
            column=5
        )
        
        self.b_Confirm = tk.Button(
            self,
            text="Confirm",
            width=20,
            command=self.f_CONFIRM
        )
        self.b_Confirm.grid(
            row=3,
            column=4
        )
        
        self.b_StartSelection = tk.Button(
            self,
            text="Start automatic selection",
            width=20,
            command=self.f_StartSelection
        )
        self.b_StartSelection.grid(
            row=5,
            column=3
        )
        
        self.b_ListSelection = tk.Button(
            self,
            text="List Selection",
            width=20,
            command=self.ListSelection
        )
        self.b_ListSelection.grid(
            row=6,
            column=4
        )
        
        self.b_StartFitWithSelection = tk.Button(
            self,
            text="Start Fit with Selection",
            width=20,
            command=self.f_StartFitWithSelection
        )
        self.b_StartFitWithSelection.grid(
            row=6,
            column=3
        )
        
        self.b_NewData = tk.Button(
            self,
            text="Read new Data",
            width=20,
            command=self.f_NewData
        )
        self.b_NewData.grid(
            row=6,
            column=5
        )
        
        self.l_BotLim = tk.Label(
            self,
            text="Bottom Limit"
        )
        self.l_BotLim.grid(
            row=3,
            column=7
        )
        self.l_UpperLim = tk.Label(
            self,
            text="Upper Limit"
        )
        self.l_UpperLim.grid(
            row=3,
            column=8
        )
        
        self.l_x = tk.Label(
            self,
            text="x",
            width=20
        )
        self.l_x.grid(
            row=4,
            column=6
        )
        self.l_y = tk.Label(
            self,
            text="y"
        )
        self.l_y.grid(
            row=5,
            column=6
        )
        
        self.e_Empty = tk.Entry(self)
        self.e_Empty.grid(
            row=1,
            column=6
        )
        
        self.e_x_BotLim = tk.Entry(self)
        self.e_x_BotLim.grid(
            row=4,
            column=7
        )
        self.e_x_BotLim.insert(
            0,
            "0"
        )
        
        self.e_y_BotLim = tk.Entry(self)
        self.e_y_BotLim.grid(
            row=5,
            column=7
        )
        self.e_y_BotLim.insert(
            0,
            "0"
        )
        
        self.e_x_UpLim = tk.Entry(self)
        self.e_x_UpLim.grid(
            row=4,
            column=8
        )
        self.e_x_UpLim.insert(
            0,
            "300"
        )
                 
        self.e_y_UpLim = tk.Entry(self)
        self.e_y_UpLim.grid(
            row=5,
            column=8
        )
        self.e_y_UpLim.insert(
            0,
            "5000"
        )
        
        self.b_ZoomPlot = tk.Button(
            self,
            text="Zoom",
            width=20,
            command=self.f_ZoomPlot
        )
        self.b_ZoomPlot.grid(
            row=6,
            column=7
        )
        
        self.update()
        
        self.f_Plot(filelist)
        
    def f_StartSelection(self):
        if len(self.Selection) == 1:
            self.b_StartSelection.config(bg="red")
            LastPoint = [self.Selection[0][0], self.Selection[0][1]]
       
            # Hilfspunkt auf bekannte Position setzen
            self.HelpPoint = [0, 0]
            self.UpdateHelpPoint()
            
            # Punkte links des Startpunktes
            while self.HelpPointValues[0] <= LastPoint[0]:
                self.HelpPoint[0] = self.HelpPoint[0] + 1
                self.UpdateHelpPoint()
                pass
            
            # Startpunkt gefunden, hier Beginn
            # der Auswertung (derzeit nur nach rechts)
            while self.HelpPoint[0] <= len(self.x_Values):
                while True:
                    if self.HelpPointValues[1] > LastPoint[1]:
                        self.HelpPoint[1] = self.HelpPoint[1] - 1
                        self.UpdateHelpPoint()
                        break
                    else:
                        self.HelpPoint[1] = self.HelpPoint[1] + 1
                        self.UpdateHelpPoint()

                LastPoint = self.HelpPointValues
                self.f_CONFIRM()
                if self.HelpPoint[0] < len(self.x_Values) - 1:
                    self.HelpPoint[0] = self.HelpPoint[0] + 1
                    self.HelpPoint[1] = 0
                    self.UpdateHelpPoint()
                else:
                    break
                
            self.f_PlotSelectedPoints()
            self.b_StartSelection.config(bg="green")
            
        else:
            self.b_StartSelection.config(bg="red")
            
    def f_NewData(self):
        self.quit()
        main()
        
    def f_StartFitWithSelection(self):
        tmp_x = []
        tmp_y = []
        for i in range(0, len(self.Selection)):
            tmp_x.append(self.Selection[i][0])
            tmp_y.append(self.Selection[i][1])
            
        times = np.array(tmp_x)
        thickness = np.array(tmp_y)
            
        popt, pcov = spop.curve_fit(
            _ExponentialDecay,
            times,
            thickness,
            p0=[5000, 5000, 0.02],
            maxfev=1000000
        )
        
        FitResult = tk.Toplevel()
        
        l_values = []
        l_deviations = []
        
        l_Parameter = tk.Label(
            FitResult,
            text="Parameter",
            width=20
        )
        l_Parameter.grid(
            row=0,
            column=0
        )
        
        l_Value = tk.Label(
            FitResult,
            text="Value",
            width=20
        )
        l_Value.grid(
            row=0,
            column=1
        )
        
        l_StandardDeviation = tk.Label(
            FitResult,
            text="StandardDeviation",
            width=20
        )
        l_StandardDeviation.grid(
            row=0,
            column=2
        )
        
        l_a = tk.Label(
            FitResult,
            text="a",
            width=20
        )
        l_a.grid(
            row=1,
            column=0
        )
        l_b = tk.Label(
            FitResult,
            text="b",
            width=20
        )
        l_b.grid(
            row=2,
            column=0
        )
        l_c = tk.Label(
            FitResult,
            text="c",
            width=20
        )
        l_c.grid(
            row=3,
            column=0
        )
        
        for i in range(0, len(popt)):
            l_values.append(
                tk.Label(
                    FitResult,
                    text="%s" % popt[i],
                    width=20
                )
            )
            l_values[i].grid(
                row=i + 1,
                column=1
            )
        
            l_deviations.append(
                tk.Label(
                    FitResult,
                    text="%s" % np.sqrt(np.diagonal(pcov))[i],
                    width=20)
            )
            l_deviations[i].grid(
                row=i + 1,
                column=2
            )
        
        def Close():
            FitResult.destroy()
        
        def Save():
            FitSaveFile = SF.SaveFile()
            ParameterList = ["a", "b", "c"]
            FitSaveFile.write("#Parameters\t value \t standard-deviation\n")
            for i in range(0, len(popt)):
                FitSaveFile.write(
                    "#%s\t%s\t%s\n" % (
                        ParameterList[i],
                        popt[i],
                        np.sqrt(np.diagonal(pcov))[i]
                    )
                )
                
            FitSaveFile.write("# time / s \t thickness / nm\n")
            for i in range(0, len(self.Selection)):
                FitSaveFile.write(
                    "%s\t%s\n" % (
                        self.Selection[i][0],
                        self.Selection[i][1]
                    )
                )
            FitSaveFile.close()
                    
        b_Save = tk.Button(
            FitResult,
            text="Save Data",
            width=20,
            command=Save
        )
        b_Save.grid(
            row=100,
            column=1
        )
        
        b_Close = tk.Button(
            FitResult,
            text="Close",
            width=20,
            command=Close
        )
        b_Close.grid(
            row=100,
            column=2
        )
        
        times.sort()
        self.PlotOfFit, = self.LiveAxis.plot(
            times,
            _ExponentialDecay(
                times,
                *popt
            ),
            color="black"
        )
        self.UpdatePlot()
        
    def f_ZoomPlot(self):
        x_BotLim = float(self.e_x_BotLim.get())
        y_BotLim = float(self.e_y_BotLim.get())
        x_UppLim = float(self.e_x_UpLim.get())
        y_UppLim = float(self.e_y_UpLim.get())
        
        self.LiveAxis.set_xlim(x_BotLim, x_UppLim)
        self.LiveAxis.set_ylim(y_BotLim, y_UppLim)
        
        self.UpdatePlot()
        
    def ReadData(self, filelist):
        if filelist is None:
            filelist = GFL.askFileList(
                title="Choose thickness data",
                filetypes=(
                    ("all result files", "*_results"),
                    ("Con. Int. result files", "*.max_results"),
                    ("Des. Int. result files", "*.min_results"),
                    ("all files", "*.*")
                )
            )
        
        for ResultFiles in filelist:
            count = 0
            with open(ResultFiles, "r") as f:
                lines = f.readlines()
                lines.pop(0)
                tmp_x = []
                tmp_y = []
                for line in lines:
                    data = line.split("\t")
                    time = float(data[0])
                    thickness = float(data[1])
                    tmp_x.append(time)
                    tmp_y.append(thickness)
                    self.x_Values.append(time)
                    self.data.append([time, thickness])
                self.LiveValues.append(
                    self.LiveAxis.plot(
                        tmp_x,
                        tmp_y,
                        linestyle="none",
                        marker="x"
                    )[0]
                )
                count = count + 1
                
        self.UpdatePlot()
        self.x_Values = SortAndDeleteItems(self.x_Values)
        
    def f_Plot(self, filelist):
        Plot = tk.Toplevel()
        self.LiveFig = Figure(
            figsize=(9, 6),
            facecolor="white"
        )
        self.LiveAxis = self.LiveFig.add_subplot(111)
        
        self.LiveAxis.set_ylabel("d [nm]")
        self.LiveAxis.set_xlabel("t [s]")
        self.LiveAxis.grid()
        canvas = FigureCanvasTkAgg(self.LiveFig, master=Plot)
        canvas._tkcanvas.pack(side=tk.TOP, fill=tk.BOTH, expand=1)
        self.f_ZoomPlot()
        self.ReadData(filelist)
    
    def UpdatePlot(self):
        self.LiveFig.canvas.draw()
        self.LiveFig.canvas.flush_events()
        
    def UpdateHelpPoint(self):
        x = self.x_Values[self.HelpPoint[0]]
        
        def FindPossibleYValues(x, order):
            possibleYValues = []
            for i in self.data:
                if x == i[0]:
                    possibleYValues.append(i[1])
                    
            return possibleYValues[order]
                    
        y = FindPossibleYValues(x, self.HelpPoint[1])
        self.HelpPointValues = [x, y]
        
    def PlotHelpPoint(self):
        self.UpdateHelpPoint()
        if self.PlotOfHelpPoint is not None:
            self.PlotOfHelpPoint.set_visible(False)
        self.PlotOfHelpPoint, = self.LiveAxis.plot(
            self.HelpPointValues[0],
            self.HelpPointValues[1],
            color="black",
            linestyle="none",
            marker="o"
        )
        self.UpdatePlot()
        
    def f_UP(self):
        self.HelpPoint[1] = self.HelpPoint[1] + 1
        self.PlotHelpPoint()
        pass
    
    def f_DOWN(self):
        self.HelpPoint[1] = self.HelpPoint[1] - 1
        if self.HelpPoint[1] < 0:
            self.HelpPoint[1] == 0
        self.PlotHelpPoint()
        pass
    
    def f_LEFT(self):
        self.HelpPoint[0] = self.HelpPoint[0] - 1
        if self.HelpPoint[0] < 0:
            self.HelpPoint[0] = 0
        self.PlotHelpPoint()
    
    def f_RIGHT(self):
        self.HelpPoint[0] = self.HelpPoint[0] + 1
        if self.HelpPoint[0] == len(self.x_Values):
            self.HelpPoint[0] = len(self.x_Values) - 1
        self.PlotHelpPoint()
    
    def f_PlotSelectedPoints(self):
        for i in range(0, len(self.Selection)):
            self.PlotOfSelection.append(
                self.LiveAxis.plot(
                    self.Selection[i][0],
                    self.Selection[i][1],
                    color="red",
                    linestyle="none",
                    marker="d"
                )[0]
            )
        self.UpdatePlot()
    
    def ListSelection(self):
        SelectionWindow = tk.Toplevel()
     
        l_x_Label = tk.Label(
            SelectionWindow,
            text="x",
            width=20
        )
        l_x_Label.grid(
            row=0,
            column=0
        )
        l_y_Label = tk.Label(
            SelectionWindow,
            text="y",
            width=20
        )
        l_y_Label.grid(
            row=0,
            column=1
        )
        l_Del_Label = tk.Label(
            SelectionWindow,
            text="Delete",
            width=20
        )
        l_Del_Label.grid(
            row=0,
            column=2
        )
        
        l_x_Values = []
        l_y_Values = []
        b_Del = []
    
        def Close():
            SelectionWindow.destroy()
            
        def Refresh():
            Close()
            self.ListSelection()
        
        def Delete(order):
            self.Selection.pop(order)
            Refresh()
            for i in range(0, len(self.PlotOfSelection)):
                self.PlotOfSelection[i].set_visible(False)
        for i in range(0, len(self.Selection)):
            
            l_x_Values.append(
                tk.Label(
                    SelectionWindow,
                    text="%s" % self.Selection[i][0]
                )
            )
            l_x_Values[i].grid(
                row=i + 1,
                column=0
            )
            
            l_y_Values.append(
                tk.Label(
                    SelectionWindow,
                    text="%s" % self.Selection[i][1]
                )
            )
            l_y_Values[i].grid(
                row=i + 1,
                column=1
            )
            
            b_Del.append(
                tk.Button(
                    SelectionWindow,
                    text="X",
                    width=10,
                    command=lambda item=i: Delete(item)
                )
            )
            b_Del[i].grid(
                row=i + 1,
                column=2
            )
            
        b_Close = tk.Button(
            SelectionWindow,
            text="Close",
            width=20,
            command=Close
        )
        b_Close.grid(
            row=len(b_Del) + 1,
            column=2
        )
        
        b_Refresh = tk.Button(
            SelectionWindow,
            text="Refresh",
            width=20,
            command=Refresh
        )
        b_Refresh.grid(
            row=len(b_Del) + 1,
            column=1
        )
        
        b_ShowPoints = tk.Button(
            SelectionWindow,
            text="Show Selection",
            width=20,
            command=self.f_PlotSelectedPoints
        )
        b_ShowPoints.grid(
            row=len(b_Del) + 1,
            column=0
        )
    
    def f_CONFIRM(self):
        self.Selection.append(
            [
                self.HelpPointValues[0],
                self.HelpPointValues[1]
            ]
        )
        
        
def main():
    App = FindThicknesses()
    App.mainloop()
    
    
if __name__ == "__main__":
    main()
