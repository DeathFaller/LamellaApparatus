import SuppModules.GetFileList as GFL
import scipy.signal as sp
import threading
import time


def split(dataname):
    """
    Teilt Rohdaten in 3 Datensets (1 pro Laser) auf
    """

    with open(dataname, "r") as myfile:
        data = myfile.readlines()
        
    Lasers = [[], [], []]
    
    for elem in data:
        elem = elem.split("\t")
        if elem[0] == "1":
            Lasers[0].append(elem[3:5])
        elif elem[1] == "1":
            Lasers[1].append(elem[3:5])
        else:
            Lasers[2].append(elem[3:5])
    
    # glaetten
    for elem in Lasers:
        if len(elem) <= 5:
            continue
        intensities = []
        for elem1 in elem:
            intensities.append(float(elem1[1][0:-1]))
        smoothed = sp.savgol_filter(
            intensities,
            window_length=5,
            polyorder=1
        )
        for elem1 in elem:
            elem1.append(
                str(
                    smoothed[elem.index(elem1)]
                )
            )
            
    # speichern
    for elem in Lasers:
        f = open(
            dataname[0:-4]
            + "_{}.sm_mwrt".format(Lasers.index(elem)),
            "w"
        )
        f.write("time [s] \t smoothed intensity \t raw intensity \n")
        for elem1 in elem:
            f.write(
                str(
                    float(
                        elem1[0]
                    )
                    * 0.001)
                + "\t"
                + str(elem1[2])
                + "\t"
                + str(elem1[1])
            )
        f.close()


def main(filelist):
    for RawFile in filelist:
        t = threading.Thread(
            target=split,
            args=(RawFile, )
        )
        t.start()

    while threading.active_count() != 1:
        pass

        
if __name__ == "__main__":
    main(
        GFL.askFileList(
            title="Choose Raw Data",
            filetypes=(
                ("RAW files", "*.RAW"),
                ("all files", "*.*")
            )
        )
    )
