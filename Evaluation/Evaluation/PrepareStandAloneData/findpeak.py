import csv
import scipy.signal as sp
import GetFileList as GFL
import numpy as np
import threading
import time


def findpeaks(dataname):
    crimefile = open(dataname, 'r')
    reader = csv.reader(crimefile)
    allRows = [row for row in reader]
    time = [float(elem[0].split("\t")[0]) for elem in allRows[1:]]
    smoothed = np.array(
        [float(elem[0].split("\t")[1]) for elem in allRows[1:]]
    )
    a, b = sp.find_peaks(
        smoothed,
        distance=10,
        prominence=10,
        width=1
    )
    c, d = sp.find_peaks(
        -smoothed,
        distance=10,
        prominence=10,
        width=1
    )
    maxima = a[0:(np.argmax(b["prominences"] + 1))]
    minima = c[0:(np.argmax(d["prominences"] + 1))]
    minima_peaktimes = [time[elem] for elem in minima]
    maxima_peaktimes = [time[elem] for elem in maxima]
    
    return minima_peaktimes, maxima_peaktimes


def create_report(tmp_file):
    Min, Max = findpeaks(tmp_file)
    
    # This is for compatibility with the evaluation software.
    # Needs to be adjusted to the new situation.
        
    max_filename = tmp_file.replace(tmp_file.split(".")[-1], "max")
    min_filename = tmp_file.replace(tmp_file.split(".")[-1], "min")
    mwrt_filename = tmp_file.replace(tmp_file.split(".")[-1], "mwrt")
        
    tmp_file = open("%s" % mwrt_filename, "w")
    tmp_file.write(" ")
    tmp_file.close()
        
    tmp_file = open("%s" % max_filename, "w")
    tmp_file.write("time / s \t Intensity / mV\n")
    for item in Max:
        tmp_file.write("%s \t ---\n" % item)
    tmp_file.close()
        
    tmp_file = open("%s" % min_filename, "w")
    tmp_file.write("time / s \t Intensity / mV \n")
    for item in Min:
        tmp_file.write("%s \t ---\n" % item)
    tmp_file.close()


def main():
    for RawDataFile in GFL.askFileList(
        title="Choose Smoothed Data",
        filetypes=(
            ("SM_MWRT files", "*.sm_mwrt"),
            ("all files", "*.*")
        )
    ):
        t = threading.Thread(target=create_report, args=(RawDataFile, ))
        t.start()
        
    while threading.active_count() != 1:
        print(threading.active_count())
        time.sleep(0.1)
    print("Finished")
        
        
if __name__ == "__main__":
    main()
