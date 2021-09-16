import Files.GetFileList as GFL
import Files.SaveFile as SFL
import statistics


def main(files):

    allData = []

    for RawFile in files:
        lifetime = []
        with open(RawFile, "r") as f:
            lines = f.readlines()
            lines.pop(0)
            lines.pop(0)
            
            for line in lines:
                data = line.split("\t")
                lifetime.append(float(data[1]))
                
        lifetime.sort()
        allData.append(
            [
                RawFile.split("/")[-1],
                sum(lifetime)/len(lifetime),
                statistics.stdev(lifetime)
            ]
        )

    f = SFL.SaveFile()
    f.write(
        "filename \t \
        Lifetime / s \
        \t std dev / s\n"
    )

    for filename, averageLifetime, standardDeviation in allData:
        f.write(f"{filename}\t{averageLifetime}\t{standardDeviation}\n")
    f.close()
            
            
if __name__ == "__main__":
    main(GFL.askFileList())
