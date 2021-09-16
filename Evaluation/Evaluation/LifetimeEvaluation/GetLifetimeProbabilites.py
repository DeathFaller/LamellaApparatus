import Files.GetFileList as GFL


def main(files):
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
                
        with open(
            RawFile.replace(
                ".LAM",
                ".lifetimeprob"
            ),
            "w"
        ) as f:
            f.write(
                "lifetime /s \t "
                "Lifetime probability \t" 
                "Rupture probability\n"
            )
            for i in range(0, len(lifetime)):
                tmp = (
                    1
                    - (
                        i
                        + 1
                    )
                    / (
                        len(lifetime)
                    )
                )
                f.write("%s\t%s\t%s\n" % (lifetime[i], tmp, 1 - tmp))
            
            
if __name__ == "__main__":
    main(GFL.askFileList())
