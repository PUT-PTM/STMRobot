# STMRobot

Projekt robota omijaj�cego przeszkody. Nap�dem s� przerobione serwa modelarskie TowerPro SG90 (1.8kg/cm, 100rpm) podpi�te do dwukana�owego mostka typu H (L293D). Do rozpoznawania przeszk�d u�ywany jest czujnik ultrad�wi�kowy HC-SR04, kt�ry umo�liwi mierzenie odleg�o�ci od przeszkody w zakresie 2-200cm.

## Sprz�t

 - STM32F4 Discovery
 - 2x Serwo SG90 + mostek L293DNE
 - Ultradzwi�kowy czujnik HC-SR04

Do zasilania silnik�w oraz p�ytki wykorzystano 8 baterii typu AA.

### Pod��czenie urz�dze�

#### HCSR-04
Pin czujnika -> Sygna� do pod��czenia

 - Vcc -> +5V
 - Trig -> PD14
 - Echo -> PD10
 - GND -> GND

#### Serwa SG90 + mostek L293DNE
Pin L293D -> Sygna� do pod��czenia

 - 1 -> Puste
 - 2 -> PA6
 - 3 -> Wej�cie 1. motoru 1.
 - 4 -> GND
 - 5 -> GND
 - 6 -> Wej�cie 2. motoru 1.
 - 7 -> PB0
 - 8 -> +5V - dla silnik�w
 - 9 -> Puste    
 - 10 -> PB8  
 - 11 -> Wej�cie 1. motoru 2.  
 - 12 -> GND  
 - 13 -> GND
 - 14 -> Wej�cie 2. motoru 2.   
 - 15 -> PE2  
 - 16 ->  +5V - dla uk�adu