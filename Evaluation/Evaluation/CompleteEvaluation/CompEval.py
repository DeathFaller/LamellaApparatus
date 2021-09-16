import tkinter as tk
import GUI.CompEval_GUI
import Functions.ThicknessMenu_Function
import SuppModules.GetFileList as GFL
import SuppModules.Computer_Smooth_and_Find_Extrema as Smooth_Find
import SuppModules.Rueckrechnung_CompEval as Ruck
import SuppModules.FindThicknesses_Automatically as Thickness
import SuppModules.Plot_Data_And_Extrema as PlDaEx
import SuppModules.StandAlone_Split as SA_Split
import SuppModules.StandAlone_FindExtrema as SA_Find


# TODO: Umbau GUI, so dass nicht hängt, wenn Daten abgearbeitet werden.
# TODO: Fortschrittsanzeige oder ähnliches einbauen.


class Evaluation(GUI.CompEval_GUI.EvaluationGUI):
    def __init__(self):
        GUI.CompEval_GUI.EvaluationGUI.__init__(self)
        self.Angle = 0
        self.End_Time = 0
        self.Start_Time = 0
        self.End_Order = 0
        self.Start_Order = 0
        self.Red_Wavelength = 0
        self.Green_Wavelength = 0

    def f_ProcessRawData(self):
        self.b_ProcessRawData.config(
            bg="red"
        )
        List = GFL.askFileList(
            title="Choose raw data",
            filetypes=(
                ("Raw files", "*.rawlam"),
                ("All files", "*.*")
            )
        )
        Smooth_Find.main(
            List
        )
        self.b_ProcessRawData.config(
            bg="green"
        )

    def f_ProcessRawData_StandAlone(self):
        self.b_ProcessRawData_StandAlone.config(
            bg="red"
        )

        List = GFL.askFileList(
            title="Choose Raw Data",
            filetypes=(
                ("RAW files", "*.RAW"),
                ("all files", "*.*")
            )
        )
        SA_Split.main(
            List
        )
        Splitted_List = GFL.askFileList(
            title="Choose Smoothed Data",
            filetypes=(
                ("Smoothed Measurement files", "*.sm_mwrt"),
                ("all files", "*.*")
            )
        )
        SA_Find.main(
            Splitted_List
        )

        self.b_ProcessRawData_StandAlone.config(
            bg="green"
        )

    def f_GetThicknesses(self):
        self.b_GetThicknesses.config(bg="red")
        
        # Unm
        Green_Data = GFL.askFileList(
            title="Choose mwrt data of green laser",
            filetypes=(
                ("green data - Standalone", "*_0.sm_mwrt"),
                ("green data - PC Version", "*_0.mwrt"),
                ("all files", "*.*")
            )
        )
        Red_Data = GFL.askFileList(
            title="Choose mwrt data of red laser",
            filetypes=(
                ("red data - Standalone", "*_1.sm_mwrt"),
                ("red data - PC Version", "*_1.mwrt"),
                ("all files", "*.*")
            )
        )

        ThicknessMenu = Functions.ThicknessMenu_Function.ThicknessMenu_Func(self)
        self.wait_window(ThicknessMenu)
        # Evaluation of Green Data
        try:
            for tmp_file in Green_Data:
                Ruck.main(
                    MeasurementFile=tmp_file,
                    Wellenlange_Laser=self.Green_Wavelength,
                    Winkel=self.Angle,
                    Start_Order=self.Start_Order,
                    End_Order=self.End_Order,
                    Starttime=self.Start_Time,
                    Endtime=self.End_Time
                )

        # Evaluation of Red Data

            for tmp_file in Red_Data:
                Ruck.main(
                    MeasurementFile=tmp_file,
                    Wellenlange_Laser=self.Red_Wavelength,
                    Winkel=self.Angle,
                    Start_Order=self.Start_Order,
                    End_Order=self.End_Order,
                    Starttime=self.Start_Time,
                    Endtime=self.End_Time
                )
            self.b_GetThicknesses.config(
                bg="green"
            )

        except Exception as E:
            print(E)
            self.b_GetThicknesses.config(
                bg="blue"
            )

        PlDaEx.main(Green_Data + Red_Data)

    def f_StartThicknessEvaluation(self):
        Thickness.main()


def main():
    App = Evaluation()
    App.mainloop()


if __name__ == "__main__":
    main()
