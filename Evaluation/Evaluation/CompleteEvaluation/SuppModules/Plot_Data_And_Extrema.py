import matplotlib.pyplot as plt


def main(
    filelist,
    save=False
):
    for MeasurementFile in filelist:
        d_messwerte = open("%s" % MeasurementFile, "r")
        try:
            d_minima = open("%s.min" % MeasurementFile, "r")
            d_maxima = open("%s.max" % MeasurementFile, "r")
            Fileopen = True
        except IOError:
            Fileopen = False
            pass
        
        w_messwerte_lines = d_messwerte.readlines()
        w_messwerte_lines.pop(0)
        
        if Fileopen:
            w_minima_lines = d_minima.readlines()
            w_minima_lines.pop(0)
        
            w_maxima_lines = d_maxima.readlines()
            w_maxima_lines.pop(0)
                
        d_messwerte.close()
        
        if Fileopen:
            d_maxima.close()
            d_minima.close()
        
        w_mess_time = []
        w_mess_smoothed = []
        
        w_maxima_time = []
        w_maxima_int = []
        
        w_minima_time = []
        w_minima_int = []
        
        for line in w_messwerte_lines:
            tmp = line.split("\t")
            w_mess_time.append(float(tmp[0]))
            w_mess_smoothed.append(float(tmp[1]))
            
        """
        Beschleunigung des Ablaufes notwendig
        Merken des Index, von w_mess_time, damit nicht immer
        von 0 gesucht wird.
        Sind ja Zeitlich geordnet
        """
            
        tmp_count = 0
        for line in w_maxima_lines:
            tmp = line.split("\t")
            for i in range(tmp_count, len(w_mess_time)):
                if w_mess_time[i] == float(tmp[0]):
                    w_maxima_time.append(float(tmp[0]))
                    w_maxima_int.append(w_mess_smoothed[i])
                    tmp_count = i
                elif w_mess_time[i] < float(tmp[0]):
                    continue
                else:
                    break
                
        tmp_count = 0
        for line in w_minima_lines:
            tmp = line.split("\t")

            for i in range(tmp_count, len(w_mess_time)):
                if w_mess_time[i] == float(tmp[0]):
                    w_minima_time.append(float(tmp[0]))
                    w_minima_int.append(w_mess_smoothed[i])
                    tmp_count = i
                elif w_mess_time[i] < float(tmp[0]):
                    continue
                else:
                    break
                
        plt.plot(w_mess_time, w_mess_smoothed)
        plt.plot(w_maxima_time, w_maxima_int, linestyle="none", marker="x")
        plt.plot(w_minima_time, w_minima_int, linestyle="none", marker=".")
            
    if save is False:
        plt.show()
