import matplotlib.pyplot as plt
import GetFileList.GetFileList as GFL


def main(
    filelist,
    save=False
):
    fig, ax = plt.subplots(figsize=(11, 5))
    
    ax.set_title('Legend to toggle line')
    plt.ylabel("Y")
    plt.xlabel("X")
    plt.grid(True, which='both')
    
    list_lines = []
    
    for MeasurementFile in filelist:
        datei = open(MeasurementFile, "r")
        lines = datei.readlines()
        lines.pop(0)
        counter = 0
        for line in lines:
            if line[0] == "#":
                counter = counter + 1
                
        for i in range(0, counter):
            print("Cut: %s" % lines[0])
            lines.pop(0)
            
        datei.close()

        tmp_x = []
        tmp_y = []

        for line in lines:
            data = line.split("\t")
            tmp_x.append(float(data[0]))
            tmp_y.append(float(data[1]))
            
        tmp_var_filename = MeasurementFile.split("/")[-1]
        tmp_var_filename = tmp_var_filename.split("-")[-1]
        tmp_var_filename = tmp_var_filename.split(".")[0:-1]
        filename = tmp_var_filename
        list_lines.append(
            ax.plot(
                tmp_x,
                tmp_y,
                label="%s" % (filename)
            )[0]
        )

    box = ax.get_position()
    ax.set_position(
        [
            box.x0,
            box.y0,
            box.width * 0.7,
            box.height
        ]
    )
    leg = ax.legend(
        loc='center left',
        bbox_to_anchor=(1, 0.5),
        ncol=3,
        fancybox=True,
        shadow=True
    )
    leg.get_frame().set_alpha(0.6)

    lined = dict()
    lined_vis = dict()
    for legline, origline in zip(leg.get_lines(), list_lines):
        legline.set_picker(5)
        lined[legline] = origline
        lined_vis[legline] = True
        
    def onpick(event):
        legline = event.artist
        origline = lined[legline]
        vis = not origline.get_visible()
        origline.set_visible(vis)
        
        if vis:
            legline.set_alpha(1.0)
        else:
            legline.set_alpha(0.1)
        fig.canvas.draw()
        
    fig.canvas.mpl_connect('pick_event', onpick)
    plt.show()
    plt.close()


if __name__ == "__main__":
    filelist = GFL.askFileList()
    main(filelist)
