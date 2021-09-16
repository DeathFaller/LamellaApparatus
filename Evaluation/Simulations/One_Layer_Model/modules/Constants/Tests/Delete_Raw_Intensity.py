import GetFileList.GetFileList as GFL


def main(filelist):
    for tmp_file in filelist:
        Endung = tmp_file.split(".")[-1]
        datei = open(tmp_file, "r")
        lines = datei.readlines()
        datei.close()
        
        datei2 = open(tmp_file.replace(Endung, "mwrt_w"), "w")
        for line in lines:
            data = line.split("\t")
            datei2.write("%s\t%s\n" % (data[0], data[1]))
            
        datei2.close()
        print("Finished")


if __name__ == "__main__":
    main(GFL.askFileList())
