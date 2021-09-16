from tkinter import filedialog, Tk


def askFileList(title, filetypes):
    """Importieren der Ursprungsdateien"""
    root = Tk()
    root.dateiname = filedialog.askopenfilenames(
        title=title,
        filetypes=filetypes
    )
    liste_dateien = list(root.dateiname)    # macht Liste aus Tupel
    root.withdraw()
    
    return liste_dateien
