# flake8: noqa

import Files.GetFileList as GFL
import Files.SaveFile as SF
import numpy as np


# Time in which x % of lamellas are ruptured
def char_time(x, t_rupt):
    t_rupt.sort()
    return t_rupt[
        int(len(t_rupt))
        / 100
        * x
    ]


def mean_time(t_rupt):
    t_mean = np.mean(t_rupt)
    t_mean_std = np.std(t_rupt)
    return t_mean, t_mean_std


def main(filelist, savefile):
    for tmpFile in filelist:
        datei = open(tmpFile, "r")
        lines = datei.readlines()
        lines.pop(0)    # remove Headline
        datei.close()
        
        Lifetimes = []
        
        t_start_list = []
        t_start = 0
        for line in lines:
            data = line.split("\t")
            Lifetimes.append(float(data[1]))
            t_start_list.append(t_start + float(data[1]))
            t_start = float(data[1])
            
        data_distribution = dict()

        for i in t_rupt:
            data_distribution[int(np.log(i)+0.5)] = list()
        for i in t_rupt:
            data_distribution[int(np.log(i)+0.5)].append(i)
        for i in data_distribution:
            data_distribution[i] = (
                int(
                    len(
                        data_distribution[i]
                    )
                )
                / len(t_rupt)
            )
            
    savefile.write("percentage\tt_char[s]\n")
    savefile.write("")
    
    savefile.close()
    

if __name__ == "__main__":
    main(GFL.askFileList(), SF.SaveFile())
