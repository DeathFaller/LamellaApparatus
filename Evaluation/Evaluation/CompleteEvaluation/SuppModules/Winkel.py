import numpy as np


def Degree_To_Radians(Angle):
    return (
        Angle
        / 180
        * np.pi
    )


def get_Snellius_Winkel2_in_Radians(
    Brechungsindex_1,
    Winkel1_in_Radians,
    Brechungsindex_2
):
    return (
        np.arcsin(
            Brechungsindex_1
            / Brechungsindex_2
            * np.sin(
                Winkel1_in_Radians
            )
        )
    )
