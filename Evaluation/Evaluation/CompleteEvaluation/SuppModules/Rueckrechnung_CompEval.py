import SuppModules.GetFileList as GFL
import SuppModules.Constants as Con
import SuppModules.ExtremeValues_Interference as Ext
import SuppModules.Winkel as Wi


def main(
    MeasurementFile,
    Wellenlange_Laser,
    Winkel,
    Start_Order,
    End_Order,
    Starttime,
    Endtime,
    DEBUG=False
):
    Dicke_Maxima = []
    Dicke_Minima = []
    Brechungsindex_Film = Con.getBrechungsindex("Wasser")
    Brechungsindex_Luft = Con.getBrechungsindex("Luft")
    
    # Erstelle Liste der moeglichen Dicken
    for i in range(Start_Order, End_Order):
        Dicke_Maxima.append(
            Ext.Dicke_Maxima(
                Brechungsindex_Luft=Brechungsindex_Luft,
                Brechungsindex_Lamelle=Brechungsindex_Film,
                Einfallswinkel_in_Radians=Wi.Degree_To_Radians(Winkel),
                Order=i,
                Wellenlange=Wellenlange_Laser
            )
        )
        Dicke_Minima.append(
            Ext.Dicke_Minima(
                Brechungsindex_Luft=Brechungsindex_Luft,
                Brechungsindex_Lamelle=Brechungsindex_Film,
                Einfallswinkel_in_Radians=Wi.Degree_To_Radians(Winkel),
                Order=i,
                Wellenlange=Wellenlange_Laser
            )
        )

    # Lese Extremwerte ein
    Endung = MeasurementFile.split(".")[-1]
#       if DEBUG:
#           print(Endung)
    File_Max = open(MeasurementFile.replace("%s" % Endung, "max"))
    File_Min = open(MeasurementFile.replace("%s" % Endung, "min"))
    Lines_Max = File_Max.readlines()
    Lines_Min = File_Min.readlines()
        
    Lines_Max.pop(0)        # Headlines entfernen
    Lines_Min.pop(0)        # Headlines entfernen
#        if DEBUG:
#            print(Lines_Max)
#            print(Lines_Min)
    File_Max.close()
    File_Min.close()
        
    Results_Max = open(
        MeasurementFile.replace(
            "%s" % Endung,
            "max_results"
        ),
        "w"
    )
    Results_Min = open(
        MeasurementFile.replace(
            "%s" % Endung,
            "min_results"
        ),
        "w"
    )
    Results_Max.write("Time [s] \t Thickness [nm]\n")
    Results_Min.write("Time [s] \t Thickness [nm]\n")
        
    for line in Lines_Max:
        data = line.split("\t")
                
        if float(data[0]) < Starttime:
            continue
        if float(data[0]) > Endtime:
            continue
            
        for i in Dicke_Maxima:
            Results_Max.write(
                "%s\t%s\n" % (
                    float(data[0]),
                    i
                )
            )

    for line in Lines_Min:
        data = line.split("\t")
        if float(data[0]) < Starttime:
            continue
        if float(data[0]) > Endtime:
            continue
        for i in Dicke_Minima:
            Results_Min.write(
                "%s\t%s\n" % (
                    float(data[0]),
                    i
                )
            )
                
    Results_Max.close()
    Results_Min.close()


def Preparations():
    filelist = GFL.askFileList(
        title="Data",
        filetypes=(
            ("all files", "*.*"),
            ("Must be", "*.x")
        )
    )
    Start_Order = int(
        input(
            "Bei welcher Ordnung soll gestartet werden?"
        )
    )
    End_Order = int(
        input(
            "Bei welcher Ordnung soll gestoppt werden? "
        )
    )
    
    Starttime = float(
        input(
            "Ab welchem Zeitpunkt soll ausgewertet werden [s]? "
        )
    )
    Endtime = float(
        input(
            "Bis zu welchem Zeitpunkt soll ausgewertet werden [s]? "
        )
    )
    
    Winkel = float(
        input(
            "Bei welchem Winkel wurden die Aufnahmen gemacht? (0-90 Degree)"
        )
    )
    for MeasurementFile in filelist:
        print(MeasurementFile)
        Wellenlange = float(
            input(
                "Bei welcher Wellenlaenge wurde gemessen [nm]?"
            )
        )
        main(
            MeasurementFile=MeasurementFile,
            Wellenlange_Laser=Wellenlange,
            Winkel=Winkel,
            Start_Order=Start_Order,
            End_Order=End_Order,
            Starttime=Starttime,
            Endtime=Endtime,
            DEBUG=False
        )


if __name__ == "__main__":
    Preparations()
    print("Finished")
