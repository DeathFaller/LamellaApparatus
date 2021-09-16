import Simulation_For_Bericht as SFB


def main(Start_Dicke, End_Dicke, Abstand_Dicke):
    b = 5800
    c = 0.032
    Starttime = 0
    Stoptime = 2700
    Intervall = 0.1
    Wellenlange = 532
    Winkel = 50
    for i in range(Start_Dicke, End_Dicke, Abstand_Dicke):
        SFB.main(
            a=i,
            b=b,
            c=c,
            Starttime=Starttime,
            Stoptime=Stoptime,
            Intervall=Intervall,
            Wellenlaenge=Wellenlange,
            Winkel=Winkel,
            save=True,
            filename="%s" % i
        )
        print("%s von %s" % (i, End_Dicke))
    
    
if __name__ == "__main__":
    Start_Dicke = int(input(
        "Bei welcher Dicke soll begonnen werden? "
    ))
    End_Dicke = int(input(
        "Bis zu welcher Dicke soll simuliert werden? "
    ))
    Abstand_Dicke = int(input(
        "In welchem Abstand sollen die Simulationen durchgefuehrt werden? "
    ))
    
    main(Start_Dicke, End_Dicke, Abstand_Dicke)
    print("finished")
