import numpy as np


def Intensity_of_Amplitude_After_Reflection(
    Refraction_Index_Before,
    Refraction_Index_After,
    Intensity
):
    # aus Quelle A-0025
    
    # LaTex
    # $ r = (\frac{n_e - n_i}{n_f + n_0})^2 $
    # $n_e$: refraction index of end medium
    # $n_i$: refraction index of initial medium
    
    return (
        Intensity
        * np.power(
            (
                (
                    Refraction_Index_After
                    - Refraction_Index_Before
                )
                / (
                    Refraction_Index_After
                    + Refraction_Index_Before
                )
            ),
            2
        )
    )
   
        
def Interference_Intensity_of_Amplitude(
    Intensity_1,
    Intensity_2,
    Phaseshift,
    Wellenlange_Laser,
    Zeit=0
):
    Lichtgeschwindigkeit = 299792468
    Kreis_Frequenz = (
        2
        * np.pi
        * Lichtgeschwindigkeit
        / (Wellenlange_Laser)
        * np.power(
            10,
            9
        )
    )
    Int = (
        Intensity_1
        * np.cos(
            Kreis_Frequenz
            * Zeit
        )
        + Intensity_2
        * np.cos(
            Kreis_Frequenz
            * Zeit
            + Phaseshift
        )
    )
    return Int
