import SuppModules.GetFileList as GFL
import time
import threading


def find_extrema(
    file,
    Anzahl_Steps_Vorwarts_Ruckwarts=13,
    debug=False,
    BestMaxima=True,
    BestMinima=True,
):
    datei = open(file, "r")
    lines = datei.readlines()
    lines.pop(0)
    datei.close()

    time_s = []
    smoothed_intensity = []

    Minima_time_s = []
    Maxima_time_s = []
    Maxima_intensity = []
    Minima_intensity = []

    for line in lines:
        spalten = line.split("\t")
        time_s.append(float(spalten[0]))
        smoothed_intensity.append(float(spalten[1]))

    try:
        Maxima = False
        Minima = False

        for position in range(0, len(time_s)):

            x = time_s[position]
            y = smoothed_intensity[position]
            if debug:
                print("x: %s --- y: %s" % (x, y))
            if (Maxima is False):
                Annahme_Maximum = True
                for i in range(
                    position - Anzahl_Steps_Vorwarts_Ruckwarts,
                    position + Anzahl_Steps_Vorwarts_Ruckwarts
                ):
                    if (i == position):
                        continue
                    if (i < 0):
                        continue
                    if (i > len(time_s) - 1):
                        continue
                    if Annahme_Maximum is False:
                        break
                    else:
                        if (y < smoothed_intensity[i]):
                            Annahme_Maximum = False
                            if debug:
                                print("Annahme Maxima falsch")
                        if debug:
                            print("Max int: %s" % smoothed_intensity[i])

                if Annahme_Maximum:
                    if debug:
                        print("Maxima gefunden: %s" % x)

                    Maxima_time_s.append(x)
                    Maxima_intensity.append(y)

            if (Minima is False):
                Annahme_Minima = True
                for i in range(
                    position - Anzahl_Steps_Vorwarts_Ruckwarts,
                    position + Anzahl_Steps_Vorwarts_Ruckwarts
                ):
                    if (i == position):
                        continue
                    if (i < 0):
                        continue
                    if (i > len(time_s) - 1):
                        continue
                    if Annahme_Minima is False:
                        break
                    else:
                        if (y > smoothed_intensity[i]):
                            Annahme_Minima = False
                            if debug:
                                print("Annahme Minima Falsch!")
                        if debug:
                            print("Min int: %s" % smoothed_intensity[i])

                if Annahme_Minima:
                    if debug:
                        print("Minima gefunden: %s" % x)

                    Minima_time_s.append(x)
                    Minima_intensity.append(y)

        datei = open("%s.max" % (file), "w")
        datei.write("time / s \t Intensity \n")
        for pos in range(0, len(Maxima_time_s)):
            datei.write(
                "%s \t %s \n" % (
                    Maxima_time_s[pos],
                    Maxima_intensity[pos]
                )
            )
        datei.close()

        datei = open("%s.min" % (file), "w")
        datei.write("time / s \t Intensity \n")
        for pos in range(0, len(Minima_time_s)):
            datei.write(
                "%s \t %s \n" % (
                    Minima_time_s[pos],
                    Minima_intensity[pos]
                )
            )
        datei.close()

    except Exception as e:
        print(e)


def main(filelist):
    for file in filelist:
        t = threading.Thread(
            target=find_extrema,
            args=(file, ))
        t.start()
    while threading.active_count() != 1:
        pass


if __name__ == "__main__":
    main(
        GFL.askFileList(
            title="Choose Raw Data",
            filetypes=(
                ("SM_MWRT files", "*.sm_mwrt"),
                ("all files", "*.*")
            )
        ),
        debug=False
    )
