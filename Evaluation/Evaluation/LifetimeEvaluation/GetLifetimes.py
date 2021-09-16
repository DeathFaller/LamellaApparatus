import Files.GetFileList as GFL
import Files.SaveFile as SF

import os


def main(filelist, savefile, Treshold=55):
    Lifetimes = []
    for RawDataFile in filelist:
        try:
            tmp_datei = open(RawDataFile, "r")
            lines = tmp_datei.readlines()
            tmp_datei.close()
            lines.pop(0)
            lines.reverse()
            Lifetime_0 = 0

            for line in lines:
                data = line.split("\t")
                time = float(data[0])
                intensity = float(data[1])
                if intensity >= Treshold:
                    Lifetime_0 = time
                    break

            directory = os.path.dirname(RawDataFile)
            filename = os.path.basename(RawDataFile)
            filename = filename.replace("_0", "_1")
            tmp_datei = open("%s/%s" % (directory, filename))
            lines = tmp_datei.readlines()
            lines.pop(0)
            lines.reverse()
            Lifetime_1 = 0
            for line in lines:

                data = line.split("\t")
                time = float(data[0])
                intensity = float(data[1])
                if intensity >= Treshold:
                    Lifetime_1 = time
                    break

            if Lifetime_1 > Lifetime_0:
                Lifetimes.append(Lifetime_1)
            else:
                Lifetimes.append(Lifetime_0)
        except:
            pass
    
    savefile.write("Number\tTime [s]\n")
    
    cnt = 1
    for time in Lifetimes:
        savefile.write("%s\t%s\n" % (cnt, time))
        cnt = cnt + 1
        
    savefile.close()


if __name__ == "__main__":
    print(
        "Use .rawlam files for evaluation,\
         only use the laser data *_0*, the other ones \
         will be found by the script"
    )
    main(
        GFL.askFileList(),
        SF.SaveFile(),
        Treshold=float(
            input(
                "Threshold for Confirmation of Rupture [mV] Recommended: 50?"
            )
        )
    )
    print("Finished")
