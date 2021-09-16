import numpy as np
import SuppModules.Winkel as Wi


def Dicke_Maxima(
    Brechungsindex_Luft,
    Brechungsindex_Lamelle,
    Einfallswinkel_in_Radians,
    Order,
    Wellenlange
):
    Propagationswinkel = (
        Wi.get_Snellius_Winkel2_in_Radians(
            Brechungsindex_1=Brechungsindex_Luft,
            Winkel1_in_Radians=Einfallswinkel_in_Radians,
            Brechungsindex_2=Brechungsindex_Lamelle
        )
    )
    return (
        (
            (
                2
                * Order
                + 1
            )
            * Wellenlange
            / 2
            + Wellenlange
            / 2
        )
        / (
            Brechungsindex_Lamelle
            * 2
            * np.cos(
                Propagationswinkel
            )
        )
    )
    
    
def Dicke_Minima(
    Brechungsindex_Luft,
    Brechungsindex_Lamelle,
    Einfallswinkel_in_Radians,
    Order,
    Wellenlange
):
    Propagationswinkel = (
        Wi.get_Snellius_Winkel2_in_Radians(
            Brechungsindex_1=Brechungsindex_Luft,
            Winkel1_in_Radians=Einfallswinkel_in_Radians,
            Brechungsindex_2=Brechungsindex_Lamelle
        )
    )
    return (
        (
            (
                Order
                + 1
            )
            * Wellenlange
            + Wellenlange
            / 2
        )
        / (
            Brechungsindex_Lamelle
            * 2
            * np.cos(
                Propagationswinkel
            )
        )
    )


if __name__ == "__main__":
    print(
        Dicke_Minima(
            1.00,
            1.33,
            np.pi / 4,
            0.00,
            532
        )
    )
    print(
        Dicke_Maxima(
            1.00,
            1.33,
            np.pi / 4,
            0.00,
            532
        )
    )
