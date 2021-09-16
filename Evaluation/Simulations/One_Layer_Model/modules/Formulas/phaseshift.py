import numpy as np
import modules.Formulas.Winkel as Wi


def phaseshift(
    Dicke,
    Wellenlange_Laser,
    Refraction_Index_Lamella,
    Refraction_Index_Air,
    Einfallswinkel_in_Radians
):
    Propagationswinkel_in_Radians = (
        Wi.get_Snellius_Winkel2_in_Radians(
            Brechungsindex_1=Refraction_Index_Air,
            Winkel1_in_Radians=Einfallswinkel_in_Radians,
            Brechungsindex_2=Refraction_Index_Lamella
        )
    )
  
    return (
        (
            Refraction_Index_Lamella
            * 2
            * Dicke
            * np.cos(
                Propagationswinkel_in_Radians
            )
            - Wellenlange_Laser
            / 2
        )
        * 2
        * np.pi
        / Wellenlange_Laser
    )
