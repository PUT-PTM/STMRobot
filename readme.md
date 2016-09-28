# STMRobot

Projekt robota omijaj¹cego przeszkody. Napêdem s¹ przerobione serwa modelarskie TowerPro SG90 (1.8kg/cm, 100rpm) podpiête do dwukana³owego mostka typu H (L293D). Do rozpoznawania przeszkód u¿ywany jest czujnik ultradŸwiêkowy HC-SR04, który umo¿liwi mierzenie odleg³oœci od przeszkody w zakresie 2-200cm.

## Sprzêt

 - STM32F4 Discovery
 - 2x Serwo SG90 + mostek L293DNE
 - Ultradzwiêkowy czujnik HC-SR04

Do zasilania silników oraz p³ytki wykorzystano 8 baterii typu AA.

### Pod³¹czenie urz¹dzeñ

#### HCSR-04
Pin czujnika -> Sygna³ do pod³¹czenia

 - Vcc -> +5V
 - Trig -> PD14
 - Echo -> PD10
 - GND -> GND

#### Serwa SG90 + mostek L293DNE
Pin L293D -> Sygna³ do pod³¹czenia

 - 1 -> Puste
 - 2 -> PA6
 - 3 -> Wejœcie 1. motoru 1.
 - 4 -> GND
 - 5 -> GND
 - 6 -> Wejœcie 2. motoru 1.
 - 7 -> PB0
 - 8 -> +5V - dla silników
 - 9 -> Puste    
 - 10 -> PB8  
 - 11 -> Wejœcie 1. motoru 2.  
 - 12 -> GND  
 - 13 -> GND
 - 14 -> Wejœcie 2. motoru 2.   
 - 15 -> PE2  
 - 16 ->  +5V - dla uk³adu