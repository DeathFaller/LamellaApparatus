import scipy
import scipy.signal
import numpy as np

import os
import SuppModules.GetFileList as GFL


def main(
    filelist,
    Anzahl_Steps_Vorwarts_Ruckwarts=13,
    debug=False,
    BestMaxima=True,
    BestMinima=True,
    ReturnList=False
):
    
    if ReturnList:
        List = []
        
    for tmp_file in filelist:
        filename = os.path.basename(tmp_file)
        NewFile_Name = tmp_file.replace(
            filename,
            "/Smoothed/%s" % filename
        )
        if os.path.isdir(tmp_file.replace(filename, "/Smoothed")):
            pass
        else:
            os.mkdir(tmp_file.replace(filename, "/Smoothed"))
        
        datei = open(tmp_file, "r")
        lines = datei.readlines()
        lines.pop(0)        # Entferne Kopfzeile
        
        time_s = []
        intensity = []
        
        Maxima_time_s = []
        Maxima_intensity = []
        
        Minima_time_s = []
        Minima_intensity = []
        
        for line in lines:
            spalten = line.split("\t")
            time_s.append(float(spalten[0]))
            intensity.append(float(spalten[1]))
    
        datei.close()
        try:
            smoothed_intensity = scipy.signal.savgol_filter(
                tmp_x=np.array(intensity),
                window_length=5,
                polyorder=1
            )

            Maxima = False
            Minima = False
            # Entscheide bei erstem Extremum, welches es ist
            
            for position in range(0, len(time_s)):
                tmp_x = time_s[position]
                tmp_y = smoothed_intensity[position]
                if debug:
                    print("tmp_x: %s" % tmp_x)
                    print("tmp_y: %s" % tmp_y)
                    print("Maxima: %s" % Maxima)
                    print("Minima: %s" % Minima)
                    
                Maxima = False
                Minima = False
                    
                if (Maxima is False):
                    Annahme_Maximum = True
                    for i in range(
                        position - Anzahl_Steps_Vorwarts_Ruckwarts,
                        position + Anzahl_Steps_Vorwarts_Ruckwarts
                    ):
                        if (i < 0):
                            continue
                        if (i > len(time_s) - 1):
                            continue
                        if Annahme_Maximum is False:
                            break
                        else:
                            if (tmp_y < smoothed_intensity[i]):
                                Annahme_Maximum = False
                    
                    if Annahme_Maximum:
                        if debug:
                            print("Maxima gefunden")
                            
                        Maxima_time_s.append(tmp_x)
                        Maxima_intensity.append(tmp_y)
                        
                if (Minima is False):
                    Annahme_Minima = True
                    for i in range(
                        position - Anzahl_Steps_Vorwarts_Ruckwarts,
                        position + Anzahl_Steps_Vorwarts_Ruckwarts
                    ):
                        if (i < 0):
                            continue
                        if (i > len(time_s) - 1):
                            continue
                        if Annahme_Minima is False:
                            break
                        else:
                            if (tmp_y > smoothed_intensity[i]):
                                Annahme_Minima = False
                                    
                    if Annahme_Minima:
                        Minima_time_s.append(tmp_x)
                        Minima_intensity.append(tmp_y)
            
            tmp_file = NewFile_Name.replace(
                ".%s" % tmp_file.split(".")[-1],
                ""
            )
            datei = open("%s.mwrt" % (tmp_file), "w")
            datei.write("time / s \t Smoothed \
            Intensitiy \t Raw Intensitiy\n")
            if ReturnList:
                List.append("%s.mwrt" % (tmp_file))
    
            for pos in range(0, len(time_s)):
                datei.write(
                    "%s \t %s \t %s\n" % (
                        time_s[pos],
                        smoothed_intensity[pos],
                        intensity[pos]
                    )
                )
            datei.close()
            
            datei = open("%s.max" % (tmp_file), "w")
            datei.write("time / s \t Intensity \n")
            for pos in range(0, len(Maxima_time_s)):
                datei.write(
                    "%s \t %s \n" % (
                        Maxima_time_s[pos],
                        Maxima_intensity[pos]
                    )
                )
            datei.close()
            
            datei = open("%s.min" % (tmp_file), "w")
            datei.write("time / s \t Intensity \n")
            for pos in range(0, len(Minima_time_s)):
                datei.write(
                    "%s \t %s \n" % (
                        Minima_time_s[pos],
                        Minima_intensity[pos]
                    )
                )
            datei.close()
                
            if ReturnList:
                return List
                
        except Exception as e:
            print(e)
            continue
        

if __name__ == "__main__":
    try:
        main(
            GFL.askFileList(
                title="Choose Data to Smooth",
                filetypes=(
                    ("Raw data files", "*.rawlam"),
                    ("all files", "*.*")
                )
            ),
            debug=False,
        )
        print("Finished")
    except Exception as e:
        print(e)
