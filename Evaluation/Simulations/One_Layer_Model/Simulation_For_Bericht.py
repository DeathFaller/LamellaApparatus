import numpy as np

import modules.Formulas.Amplitude as Ap
import modules.Formulas.phaseshift as Ph
import modules.Formulas.Winkel as Wi


def Zerfallsfunkion_Lamelle(
    a,
    b,
    c,
    time
):
    return a - b * time


def Error_Zerfallsfunktion_Lamella(
    a,
    b,
    c,
    time,
    d_a=0,
    d_b=0,
    d_c=0
):
    return (
        np.abs(d_a)
        + np.abs(
            np.exp(
                -c
                * time
            )
            * d_b
        )
        + np.abs(
            b
            * np.exp(
                -c
                * time
            )
            * time
            * d_c
        )
    )


def main(
    Starttime,
    Stoptime,
    Intervall,
    Wellenlaenge,
    Winkel,
    a,
    b,
    c,
    d_a,
    d_b,
    d_c,
    save=None,
    filename=None
):
    
    # Konstanten
    Brechungsindex_Medium_Luft = 1.00
    Brechungsindex_Medium_Wasser = 1.33

    # Umrechnung in Radians
    Einfallswinkel = Wi.Degree_To_Radians(Winkel)       # Winkel zum Lot hin!
    
    # Willkuerliche Festlegung der Amplitude
    Amplitude_Start = 10000
    # Berechnung der Intensitaet der reflektierten Welle ohne Transmission
    Amplitude_1 = Ap.Intensity_of_Amplitude_After_Reflection(
        Brechungsindex_Medium_Luft,
        Brechungsindex_Medium_Wasser,
        Amplitude_Start
    )
    Amplitude_2 = Ap.Intensity_of_Amplitude_After_Reflection(
        Brechungsindex_Medium_Wasser,
        Brechungsindex_Medium_Luft,
        Amplitude_Start - Amplitude_1
    )
    
    # Startzeitpunkt festlegen:
    time = Starttime
    
    # Intervall fuer Berechnung festlegen (0.1 bis 1.0 sind gute Werte):
    time_intervall = Intervall
    
    # Array fuer Ergebniswerte
    res_time = []
    res_thickness = []
    res_intensity = []
    err_p_Intensity = []
    err_n_Intensity = []
    
    # Aenderung 09.07.19 tmp
    Zusatz = 0
    #
    
    while(time < Stoptime):

        Dicke = (
            Zerfallsfunkion_Lamelle(
                a,
                b,
                c,
                time
            )
            + Zusatz
        )
        DiffDicke = (
            Error_Zerfallsfunktion_Lamella(
                a,
                b,
                c,
                time,
                d_a,
                d_b,
                d_c
            )
        )
        
        Phasenunterschied = Ph.phaseshift(
            Dicke=Dicke,
            Wellenlange_Laser=Wellenlaenge,
            Refraction_Index_Lamella=Brechungsindex_Medium_Wasser,
            Refraction_Index_Air=Brechungsindex_Medium_Luft,
            Einfallswinkel_in_Radians=Einfallswinkel
        )
        Error_p_Phasenunterschied = Ph.phaseshift(
            Dicke=Dicke + DiffDicke,
            Wellenlange_Laser=Wellenlaenge,
            Refraction_Index_Lamella=Brechungsindex_Medium_Wasser,
            Refraction_Index_Air=Brechungsindex_Medium_Luft,
            Einfallswinkel_in_Radians=Einfallswinkel
        )
        Error_n_Phasenunterschied = Ph.phaseshift(
            Dicke=Dicke - DiffDicke,
            Wellenlange_Laser=Wellenlaenge,
            Refraction_Index_Lamella=Brechungsindex_Medium_Wasser,
            Refraction_Index_Air=Brechungsindex_Medium_Luft,
            Einfallswinkel_in_Radians=Einfallswinkel
        )
        
        Intensitaet = Ap.Interference_Intensity_of_Amplitude(
            Intensity_1=Amplitude_1,
            Intensity_2=Amplitude_2,
            Phaseshift=Phasenunterschied,
            Wellenlange_Laser=Wellenlaenge,
            Zeit=0
        )
        Error_p_Intensitaet = Ap.Interference_Intensity_of_Amplitude(
            Intensity_1=Amplitude_1,
            Intensity_2=Amplitude_2,
            Phaseshift=Error_p_Phasenunterschied,
            Wellenlange_Laser=Wellenlaenge,
            Zeit=0
        )
        Error_n_Intensitaet = Ap.Interference_Intensity_of_Amplitude(
            Intensity_1=Amplitude_1,
            Intensity_2=Amplitude_2,
            Phaseshift=Error_n_Phasenunterschied,
            Wellenlange_Laser=Wellenlaenge,
            Zeit=0
        )
    
        res_time.append(time)
        res_thickness.append(Dicke)
        res_intensity.append(Intensitaet)
        err_p_Intensity.append(Error_p_Intensitaet)
        err_n_Intensity.append(Error_n_Intensitaet)
        
        time = time + time_intervall
   
        # Aenderung 09.07.19 tmp
        # if time >= 1800 and time <= 1805:
        #    Zusatz = +50
        #
        # if time >= 3600 and time <= 3605:
        #    Zusatz = -50
        #
   
    if save is True:
        SaveFile = open(
            "%s_%snm_%smGrad_%sto%s.result" % (
                filename,
                int(Wellenlaenge),
                int(Winkel * 1000),
                int(Starttime),
                int(Stoptime)
            ),
            "w"
        )
        SaveFile.write("time \t intensity \t thickness \t p_Int \t n_Int \n")
        for i in range(0, len(res_time)):
            SaveFile.write(
                "%s \t %s \t %s \t %s \t %s \n" % (
                    res_time[i],
                    res_intensity[i],
                    res_thickness[i],
                    err_p_Intensity[i],
                    err_n_Intensity[i]
                )
            )
        SaveFile.close()


def loop():
    Wellenlaenge = float(
        input(
            "Bei welcher Wellenlaenge soll simuliert werden? "
        )
    )
    Winkel = float(
        input(
            "Bei welchem Winkel (zum Lot hin) soll simuliert werden? "
        )
    )
    
    # Abfrage Parameter
    print("y = a + b*exp(-c*t)")
    a = float(input("a: "))
    b = float(input("b: "))
    c = float(input("c: "))
    d_a = float(input("d_a: "))
    d_b = float(input("d_b: "))
    d_c = float(input("d_c: "))
    
    # Abfrage: Welcher Zeitraum soll simuliert werden?
    Starttime = float(input("Startzeit: "))
    Stoptime = float(input("Stopzeit: "))
    Intervall = float(input("Intervall: "))
    
    if (input("Soll gespeichert werden? (y/N)? ") == "y"):
        save = True
        filename = input(
            "Name der Ergebnisdatei: \
            *_Wellenlaengenm_WinkelGrad_StartToEndTime.result: "
        )
    else:
        save = False
        filename = None
        
    main(
        Starttime=Starttime,
        Stoptime=Stoptime,
        Intervall=Intervall,
        Wellenlaenge=Wellenlaenge,
        Winkel=Winkel,
        a=a,
        b=b,
        c=c,
        d_a=d_a,
        d_b=d_b,
        d_c=d_c,
        save=save,
        filename=filename
    )


if __name__ == "__main__":
    while (input("Neue Simulation? [y/N]") == "y"):
        loop()
