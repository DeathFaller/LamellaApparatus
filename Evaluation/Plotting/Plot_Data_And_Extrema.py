import matplotlib.pyplot as plt
import GetFileList.GetFileList as GFL


def main(filelist, save):
    for MeasurementFile in filelist:
        filename = MeasurementFile
        d_messwerte = open("%s" % MeasurementFile, "r")
        try:
            d_minima = open("%s.min" % filename, "r")
            d_maxima = open("%s.max" % filename, "r")
            Fileopen = True
        except IOError as e:
            print(e)
            Fileopen = False
        
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
        
        w_minima_time = []
        w_minima_intensity = []
        
        w_maxima_time = []
        w_maxima_intensity = []
        
        for line in w_messwerte_lines:
            tmp = line.split("\t")
            w_mess_time.append(float(tmp[0]))
            w_mess_smoothed.append(float(tmp[1]))
            
        if Fileopen:
            for line in w_minima_lines:
                tmp = line.split("\t")
                w_minima_intensity.append(float(tmp[1]))
                w_minima_time.append(float(tmp[0]))
            
            for line in w_maxima_lines:
                tmp = line.split("\t")
                w_maxima_intensity.append(float(tmp[1]))
                w_maxima_time.append(float(tmp[0]))
            
        plt.plot(
            w_mess_time,
            w_mess_smoothed,
            label="%s" % filename)
        if Fileopen:
            plt.plot(
                w_maxima_time,
                w_maxima_intensity,
                marker="x",
                linestyle="none"
            )
            plt.plot(
                w_minima_time,
                w_minima_intensity,
                marker="x",
                linestyle="none"
            )
            
        if save is True:
            plt.xlabel("time")
            plt.ylabel("intensity")
            plt.grid(True)
            plt.savefig(MeasurementFile.replace(".mwrt", ".pdf"), Format="pdf")
            plt.close()
            
    if save is False:
        plt.show()
        
        
if __name__ == "__main__":
    try:
        main(GFL.askFileList(), False)
    except Exception as e:
        print(e)
