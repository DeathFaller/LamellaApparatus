from tkinter import filedialog, Tk


def askFileList():
    """Importieren der Ursprungsdateien"""
    root = Tk()
    root.dateiname = filedialog.askopenfilenames(
        title="choose your raw data from SINTERFACE PAT1M",
        filetypes=(
            ("all files", "*.*"),
            ("RAWLAM Files", "*_0.rawlam"),
            ("LAM files", "*.lam"),
            ("MWRT-Files", "*.mwrt"),
            ("text files", "*.txt"),
            ("Stand Alone Lamella Device files", "*_0.sm_mwrt")
        )
    )  # Tupel der Dateinamen

    liste_dateien = list(root.dateiname)   # macht Liste aus Tupel
    root.withdraw()
    
    return liste_dateien
