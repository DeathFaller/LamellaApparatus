from tkinter import filedialog, Tk


def askFileList(title, filetypes):
    root = Tk()
    root.dateiname = filedialog.askopenfilenames(
        title=title,
        filetypes=filetypes)

    liste_dateien = list(root.dateiname)
    root.withdraw()
    
    return liste_dateien
