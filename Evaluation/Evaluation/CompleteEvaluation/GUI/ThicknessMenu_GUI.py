import tkinter


class ThicknessMenu_GUI(tkinter.Toplevel):
    def __init__(self):
        tkinter.Toplevel.__init__(self)

        self.l_GreenWavelength = tkinter.Label(
            self,
            text="Wavelength of green laser [nm]:"
        )

        self.e_GreenWavelength = tkinter.Entry(
            self
        )

        self.l_RedWavelength = tkinter.Label(
            self,
            text="Wavelength of red laser [nm]:"
        )

        self.e_RedWavelength = tkinter.Entry(
            self
        )

        self.l_StartOrder = tkinter.Label(
            self,
            text="Order of interference at which the evaluation should begin: "
        )

        self.e_StartOrder = tkinter.Entry(
            self
        )

        self.l_EndOrder = tkinter.Label(
            self,
            text="Order of interference at which the evaluation should stop: "
        )

        self.e_EndOrder = tkinter.Entry(
            self
        )

        self.l_StartTime = tkinter.Label(
            self,
            text="At which time should the evaluation start [s]: "
        )

        self.e_StartTime = tkinter.Entry(
            self
        )

        self.l_EndTime = tkinter.Label(
            self,
            text="At which time should the evaluation stop [s]: "
        )

        self.e_EndTime = tkinter.Entry(
            self
        )

        self.l_Angle = tkinter.Label(
            self,
            text="At which angle were the measurements taken [0-90 Degree]: "
        )

        self.e_Angle = tkinter.Entry(
            self
        )

        self.b_Save = tkinter.Button(
            self,
            text="Start",
            command=self.on_saving
        )

        self.b_Close = tkinter.Button(
            self,
            text="Close",
            command=self.on_closing
        )

        self.clear()
        self.config()

    def config(self):
        self.l_GreenWavelength.grid(
            column=0,
            row=0
        )
        self.e_GreenWavelength.grid(
            column=1,
            row=0
        )
        self.l_RedWavelength.grid(
            column=0,
            row=1
        )
        self.e_RedWavelength.grid(
            column=1,
            row=1
        )
        self.l_StartOrder.grid(
            column=0,
            row=2
        )
        self.e_StartOrder.grid(
            column=1,
            row=2
        )
        self.l_EndOrder.grid(
            column=0,
            row=3
        )
        self.e_EndOrder.grid(
            column=1,
            row=3
        )
        self.l_StartTime.grid(
            column=0,
            row=4
        )
        self.e_StartTime.grid(
            column=1,
            row=4
        )
        self.l_EndTime.grid(
            column=0,
            row=5
        )
        self.e_EndTime.grid(
            column=1,
            row=5
        )

        self.e_Angle.grid(
            column=1,
            row=6
        )
        self.l_Angle.grid(
            column=0,
            row=6
        )
        self.b_Close.grid(
            column=1,
            row=7
        )
        self.b_Save.grid(
            column=0,
            row=7
        )

    def clear(self):
        self.e_GreenWavelength.delete(
            0,
            'end'
        )
        self.e_GreenWavelength.insert(
            0,
            "532"
        )
        self.e_RedWavelength.delete(
            0,
            'end'
        )
        self.e_RedWavelength.insert(
            0,
            "650"
        )
        self.e_StartOrder.delete(
            0,
            'end'
        )
        self.e_StartOrder.insert(
            0,
            "0"
        )
        self.e_EndOrder.delete(
            0,
            'end'
        )
        self.e_EndOrder.insert(
            0,
            "25"
        )
        self.e_StartTime.delete(
            0,
            'end'
        )
        self.e_StartTime.insert(
            0,
            "25"
        )
        self.e_EndTime.delete(
            0,
            'end'
        )
        self.e_EndTime.insert(
            0,
            "300"
        )

        self.e_Angle.delete(
            0,
            'end'
        )
        self.e_Angle.insert(
            0,
            "20"
        )

    def on_closing(self):
        self.destroy()

    def on_saving(self):
        pass
