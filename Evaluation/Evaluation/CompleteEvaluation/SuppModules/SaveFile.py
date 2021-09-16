from tkinter import filedialog


def SaveFile():
    return filedialog.asksaveasfile(
        mode="w",
        defaultextension=".txt"
    )
