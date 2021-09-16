import Simulation_For_Bericht as SFB


def main(Start_Winkel, End_Winkel, Abstand_Winkel):
    a = 1000
    b = 5800
    c = 0.032
    Starttime = 0
    Stoptime = 200
    Intervall = 0.05
    Wellenlange = 532
    for i in range(Start_Winkel, End_Winkel, Abstand_Winkel):
        SFB.main(
            a=a,
            b=b,
            c=c,
            Starttime=Starttime,
            Stoptime=Stoptime,
            Intervall=Intervall,
            Wellenlaenge=Wellenlange,
            Winkel=i,
            save=True,
            filename="Winkel_Test"
        )
        print("%s von %s" % (i, End_Winkel))
    
    
if __name__ == "__main__":
    Start_Winkel = int(input(
        "Bei welchem Winkel soll begonnen werden? "
    ))
    End_Winkel = int(input(
        "Bis zu welchem Winkel soll simuliert werden? "
    ))
    Abstand_Winkel = int(input(
        "In welchem Abstand sollen die Simulationen durchgefuehrt werden? "
    ))
    
    main(Start_Winkel, End_Winkel, Abstand_Winkel)
    print("finished")
