from tkinter import filedialog, Tk


def askFileList():
    """Importieren der Ursprungsdateien"""
    root = Tk()
    root.dateiname = filedialog.askopenfilenames(
        title="choose your raw data from SINTERFACE PAT1M",
        filetypes=(
            ("all files", "*.*"),
            ("LAM files", "*.lam"),
            ("RAWLAM Files", "*.rawlam"),
            ("MWRT-Files", "*.mwrt"),
            ("text files", "*.txt"),
            ("Result Files", "*_results"),
        )
    )   # Tupel der Dateinamen

    liste_dateien = list(root.dateiname)     # macht Liste aus Tupel
    root.withdraw()
    
    return liste_dateien
