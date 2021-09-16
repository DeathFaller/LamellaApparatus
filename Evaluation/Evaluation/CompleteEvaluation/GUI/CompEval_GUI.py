import tkinter


class EvaluationGUI(tkinter.Tk):
    def __init__(self):
        tkinter.Tk.__init__(self)
        self.b_ProcessRawData = tkinter.Button(
            self,
            text="Process Raw Data measured via a computer",
            width=60,
            command=self.f_ProcessRawData,
            bg="yellow"
        )

        self.b_ProcessRawData_StandAlone = tkinter.Button(
            self,
            text="Process Raw Data measured via the standalone device",
            width=60,
            command=self.f_ProcessRawData_StandAlone,
            bg="yellow"
        )

        self.b_GetThicknesses = tkinter.Button(
            self,
            text="Get Thicknesses",
            width=30,
            command=self.f_GetThicknesses,
            bg="yellow"
        )

        self.b_StartThicknessEvaluation = tkinter.Button(
            self,
            text="Start Evaluation",
            width=30,
            command=self.f_StartThicknessEvaluation,
            bg="yellow"
        )

        self.b_Close = tkinter.Button(
            self,
            text="Close",
            width=30,
            command=self.destroy,
            bg="red"
        )
        self.config()

    def config(self):
        self.b_ProcessRawData.grid(
            column=2,
            row=2
        )
        self.b_ProcessRawData_StandAlone.grid(
            column=4,
            row=2,
        )
        self.b_GetThicknesses.grid(
            column=3,
            row=3
        )
        self.b_StartThicknessEvaluation.grid(
            column=3,
            row=4
        )
        self.b_Close.grid(
            column=3,
            row=100
        )
