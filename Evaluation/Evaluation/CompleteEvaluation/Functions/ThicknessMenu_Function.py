import GUI.ThicknessMenu_GUI


class ThicknessMenu_Func(GUI.ThicknessMenu_GUI.ThicknessMenu_GUI):
    def __init__(self, parent):
        GUI.ThicknessMenu_GUI.ThicknessMenu_GUI.__init__(self)
        self.parent = parent

    def on_saving(self):
        self.parent.Green_Wavelength = int(self.e_GreenWavelength.get())
        self.parent.Red_Wavelength = int(self.e_RedWavelength.get())

        self.parent.Start_Order = int(self.e_StartOrder.get())
        self.parent.End_Order = int(self.e_EndOrder.get())

        self.parent.Start_Time = float(self.e_StartTime.get())
        self.parent.End_Time = float(self.e_EndTime.get())

        self.parent.Angle = float(self.e_Angle.get())
        self.destroy()
