import GetFileList.GetFileList as GFL


def main(filelist, Stoptime):
    for tmp_File in filelist:
        Endung = tmp_File.split(".")[-1]
        datei = open(tmp_File, "r")
        lines = datei.readlines()
        datei.close()
        
        datei2 = open(tmp_File.replace(Endung, "mwrt_w"), "w")
        headline = False
        for line in lines:
            data = line.split("\t")
            if headline:
                if (float(data[0]) > Stoptime):
                    continue
            datei2.write("%s\t%s\n" % (data[0], data[1]))
            headline = True
        datei2.close()
        print("Finished")


if __name__ == "__main__":
    main(
        GFL.askFileList(),
        float(
            input(
                "Bis zu welcher Zeit sollen die Daten behalten werden?"
            )
        )
    )
