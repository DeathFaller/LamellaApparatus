# THIS FILE IS AUTOMATICALLY GENERATED
# Project: D:\Masterarbeit - Chemie\Lamella\Firmware\KompletteSteuerung\PSOC5_LamellaControlHofmann.cydsn\PSOC5_LamellaControlHofmann.cyprj
# Date: Fri, 05 Jul 2019 07:56:22 GMT
#set_units -time ns
create_clock -name {CyILO} -period 10000 -waveform {0 5000} [list [get_pins {ClockBlock/ilo}] [get_pins {ClockBlock/clk_100k}] [get_pins {ClockBlock/clk_1k}] [get_pins {ClockBlock/clk_32k}]]
create_clock -name {CyIMO} -period 41.666666666666664 -waveform {0 20.8333333333333} [list [get_pins {ClockBlock/imo}]]
create_clock -name {CyPLL_OUT} -period 15.625 -waveform {0 7.8125} [list [get_pins {ClockBlock/pllout}]]
create_clock -name {CyMASTER_CLK} -period 15.625 -waveform {0 7.8125} [list [get_pins {ClockBlock/clk_sync}]]
create_generated_clock -name {CyBUS_CLK} -source [get_pins {ClockBlock/clk_sync}] -edges {1 2 3} [list [get_pins {ClockBlock/clk_bus_glb}]]
create_generated_clock -name {emFile_Clock_1} -source [get_pins {ClockBlock/clk_sync}] -edges {1 2 3} [list [get_pins {ClockBlock/dclk_glb_0}]]
create_generated_clock -name {Analog_Digital_Converter_theACLK} -source [get_pins {ClockBlock/clk_sync}] -edges {1 7 13} [list [get_pins {ClockBlock/aclk_glb_0}]]
create_generated_clock -name {UART_PC_IntClock} -source [get_pins {ClockBlock/clk_sync}] -edges {1 69 139} [list [get_pins {ClockBlock/dclk_glb_2}]]
create_generated_clock -name {UART_TFT_IntClock} -source [get_pins {ClockBlock/clk_sync}] -edges {1 833 1667} [list [get_pins {ClockBlock/dclk_glb_3}]]
create_generated_clock -name {timer_clock} -source [get_pins {ClockBlock/clk_sync}] -edges {1 3 5} -nominal_period 41.666666666666664 [list [get_pins {ClockBlock/dclk_glb_1}]]

set_false_path -from [get_pins {__ONE__/q}]

# Component constraints for D:\Masterarbeit - Chemie\Lamella\Firmware\KompletteSteuerung\PSOC5_LamellaControlHofmann.cydsn\TopDesign\TopDesign.cysch
# Project: D:\Masterarbeit - Chemie\Lamella\Firmware\KompletteSteuerung\PSOC5_LamellaControlHofmann.cydsn\PSOC5_LamellaControlHofmann.cyprj
# Date: Fri, 05 Jul 2019 07:56:14 GMT
