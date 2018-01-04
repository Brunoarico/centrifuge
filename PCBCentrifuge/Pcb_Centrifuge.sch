EESchema Schematic File Version 2
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L CONN_01X02 P2
U 1 1 57A399DD
P 3150 2700
F 0 "P2" H 3150 2850 50  0000 C CNN
F 1 "Botao" V 3250 2700 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02" H 3150 2700 50  0001 C CNN
F 3 "" H 3150 2700 50  0000 C CNN
	1    3150 2700
	-1   0    0    1   
$EndComp
$Comp
L CONN_01X02 P3
U 1 1 57A39B84
P 3150 3250
F 0 "P3" H 3150 3400 50  0000 C CNN
F 1 "Supply" V 3250 3250 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02" H 3150 3250 50  0001 C CNN
F 3 "" H 3150 3250 50  0000 C CNN
	1    3150 3250
	-1   0    0    1   
$EndComp
$Comp
L CONN_01X03 P4
U 1 1 57A39C92
P 3150 4000
F 0 "P4" H 3150 4200 50  0000 C CNN
F 1 "Motor" V 3250 4000 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x03" H 3150 4000 50  0001 C CNN
F 3 "" H 3150 4000 50  0000 C CNN
	1    3150 4000
	-1   0    0    1   
$EndComp
$Comp
L CONN_01X03 P5
U 1 1 57A39D0A
P 3150 4700
F 0 "P5" H 3150 4900 50  0000 C CNN
F 1 "Sensor_Hall" V 3250 4700 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x03" H 3150 4700 50  0001 C CNN
F 3 "" H 3150 4700 50  0000 C CNN
	1    3150 4700
	-1   0    0    1   
$EndComp
$Comp
L CONN_01X05 P6
U 1 1 57A39D34
P 3150 5600
F 0 "P6" H 3150 5900 50  0000 C CNN
F 1 "Encoder" V 3250 5600 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x05" H 3150 5600 50  0001 C CNN
F 3 "" H 3150 5600 50  0000 C CNN
	1    3150 5600
	-1   0    0    1   
$EndComp
$Comp
L CONN_01X04 P1
U 1 1 57A39D77
P 3150 1750
F 0 "P1" H 3150 2000 50  0000 C CNN
F 1 "LCD" V 3250 1750 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x04" H 3150 1750 50  0001 C CNN
F 3 "" H 3150 1750 50  0000 C CNN
	1    3150 1750
	-1   0    0    1   
$EndComp
$Comp
L CONN_01X12 P10
U 1 1 57A39E45
P 5650 2900
F 0 "P10" H 5650 3550 50  0000 C CNN
F 1 "Arduino_Baixo" V 5750 2900 50  0000 C CNN
F 2 "Socket_Strips:Socket_Strip_Straight_1x12" H 5650 2900 50  0001 C CNN
F 3 "" H 5650 2900 50  0000 C CNN
	1    5650 2900
	0    -1   -1   0   
$EndComp
$Comp
L CONN_01X12 P9
U 1 1 57A39ED4
P 5650 2400
F 0 "P9" H 5650 3050 50  0000 C CNN
F 1 "Arduino_Cima" V 5750 2400 50  0000 C CNN
F 2 "Socket_Strips:Socket_Strip_Straight_1x12" H 5650 2400 50  0001 C CNN
F 3 "" H 5650 2400 50  0000 C CNN
	1    5650 2400
	0    1    1    0   
$EndComp
Text GLabel 6200 3100 2    60   Input ~ 0
Raw
Text GLabel 6200 2200 2    60   Input ~ 0
TX0
Text GLabel 5100 2200 0    60   Input ~ 0
9
Text GLabel 5100 3100 0    60   Input ~ 0
10
Text GLabel 3350 1600 1    60   Input ~ 0
GND
Text GLabel 3350 1900 3    60   Input ~ 0
A5
$Comp
L CONN_01X02 P7
U 1 1 57A3A4D1
P 5050 2650
F 0 "P7" H 5050 2800 50  0000 C CNN
F 1 "Arduino_Central" V 5150 2650 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02" H 5050 2650 50  0001 C CNN
F 3 "" H 5050 2650 50  0000 C CNN
	1    5050 2650
	1    0    0    -1  
$EndComp
Text GLabel 4850 2600 0    60   Input ~ 0
A4
Text Label 4800 1600 0    60   ~ 0
GND
Text Label 4850 1900 0    60   ~ 0
A4
Text Label 7200 2150 0    60   ~ 0
Vcc
Text Label 5600 2000 0    60   ~ 0
pin4
Text Label 4550 3300 0    60   ~ 0
RAW
Text GLabel 3350 3200 1    60   Input ~ 0
GND
Text GLabel 3350 2750 3    60   Input ~ 0
GND
Text GLabel 3350 2650 1    60   Input ~ 0
pin4
Text GLabel 3350 3300 3    60   Input ~ 0
raw
Text GLabel 3350 3900 1    60   Input ~ 0
GND
Text GLabel 3350 4100 3    60   Input ~ 0
3
NoConn ~ 3350 4000
Text Label 7400 4100 0    60   ~ 0
pin3
Text GLabel 3350 4600 1    60   Input ~ 0
VCC
Text Label 6450 4800 0    60   ~ 0
pin2
$Comp
L R R1
U 1 1 57A3AE4A
P 6550 4450
F 0 "R1" V 6630 4450 50  0000 C CNN
F 1 "R" V 6550 4450 50  0000 C CNN
F 2 "Resistors_ThroughHole:Resistor_Horizontal_RM15mm" V 6480 4450 50  0001 C CNN
F 3 "" H 6550 4450 50  0000 C CNN
	1    6550 4450
	0    1    1    0   
$EndComp
Wire Notes Line
	3200 4800 3200 4750
Wire Wire Line
	3350 1600 5900 1600
Wire Wire Line
	5900 1050 5900 2200
Wire Wire Line
	5900 3100 5900 4600
Wire Wire Line
	5900 3500 7200 3500
Wire Wire Line
	7200 3500 7200 1700
Wire Wire Line
	7200 1700 3350 1700
Wire Wire Line
	3350 1800 4850 1800
Wire Wire Line
	4850 1800 4850 2600
Wire Wire Line
	3350 1900 4450 1900
Wire Wire Line
	4450 1900 4450 2700
Wire Wire Line
	4450 2700 4850 2700
Wire Wire Line
	3350 2650 4200 2650
Wire Wire Line
	4200 2650 4200 2000
Wire Wire Line
	4200 2000 5600 2000
Wire Wire Line
	5600 2000 5600 2200
Wire Wire Line
	3750 1600 3750 5800
Wire Wire Line
	3750 2750 3350 2750
Connection ~ 3750 1600
Wire Wire Line
	3750 3200 3350 3200
Connection ~ 3750 2750
Wire Wire Line
	3350 3300 6200 3300
Wire Wire Line
	6200 3300 6200 3100
Wire Wire Line
	5700 2200 5700 1850
Wire Wire Line
	5700 1850 7800 1850
Wire Wire Line
	7800 1850 7800 4100
Wire Wire Line
	7800 4100 3350 4100
Wire Wire Line
	3750 3900 3350 3900
Connection ~ 3750 3200
Wire Wire Line
	3750 4700 3350 4700
Connection ~ 3750 3900
Wire Wire Line
	5900 4600 3350 4600
Connection ~ 5900 3500
Wire Wire Line
	5800 2200 5800 2050
Wire Wire Line
	5800 2050 7000 2050
Wire Wire Line
	7000 2050 7000 4800
Wire Wire Line
	7000 4800 3350 4800
Wire Wire Line
	6400 4450 5900 4450
Connection ~ 5900 4450
Wire Wire Line
	6700 4450 7000 4450
Connection ~ 7000 4450
Text GLabel 3350 5400 1    60   Input ~ 0
CLK
Text GLabel 3350 5800 3    60   Input ~ 0
GND
Wire Wire Line
	3750 5800 3350 5800
Connection ~ 3750 4700
Wire Wire Line
	4350 4600 4350 5700
Wire Wire Line
	4350 5700 3350 5700
Connection ~ 4350 4600
Wire Wire Line
	5100 2200 4600 2200
Wire Wire Line
	4600 2200 4600 5600
Wire Wire Line
	4600 5600 3350 5600
Text Label 4600 5100 0    60   ~ 0
Pin9
Wire Wire Line
	5500 3100 5500 5500
Wire Wire Line
	5500 5500 3350 5500
Wire Wire Line
	3350 5400 5600 5400
Wire Wire Line
	5600 5400 5600 3100
Text Label 4900 5500 0    60   ~ 0
A0
Text Label 5250 5400 0    60   ~ 0
A1
NoConn ~ 6100 2200
NoConn ~ 6000 2200
NoConn ~ 5500 2200
NoConn ~ 5400 2200
NoConn ~ 5300 2200
NoConn ~ 5200 3100
NoConn ~ 5100 3100
NoConn ~ 5300 3100
NoConn ~ 5400 3100
NoConn ~ 5700 3100
NoConn ~ 5800 3100
NoConn ~ 6000 3100
NoConn ~ 6100 3100
$Comp
L CONN_01X02 P8
U 1 1 57A3BA54
P 5250 850
F 0 "P8" H 5250 1000 50  0000 C CNN
F 1 "RESET" V 5350 850 50  0000 C CNN
F 2 "Pin_Headers:Pin_Header_Straight_1x02" H 5250 850 50  0001 C CNN
F 3 "" H 5250 850 50  0000 C CNN
	1    5250 850 
	0    -1   -1   0   
$EndComp
Wire Wire Line
	5200 2200 5200 1050
Wire Wire Line
	5300 1050 5900 1050
Connection ~ 5900 1600
$EndSCHEMATC
