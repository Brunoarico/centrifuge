#ifndef CONFIG_H
#define CONFIG_H
//Define endereço I2C do LCD
#define LCD_ADRESS 0x3F
//Pinagem do LCD:
//SDA: A4
//SCL: A5
//Define pino do motor
#define motor_pin 3
//Define pinos do encoder
#define ENC_A 14
#define ENC_B 15
#define ENC_PORT PINC
//Define botão do encoder
#define ENC_PIN 9
//Define pino do botão
#define botao_pin 4
//Define pino "reset"
#define maintenance_reset 8
//define constantes naturais
#define pi 3.14159265
#define g 9.80665
#define raio_rotor 0.37
//sensor hall é conectado no pino de interrupção pin 2
//constantes de execução
#define Vmin 2500            //Velocidade minima de rotação
#define Vmax 15000           //Velocidade maxima de rotação
#define StepROTATE 200       //passo do seletor de rpm
#define StepTIME 5           //passo do seletor de tempo
#define eeprom_maintenance 0 //memoria da eeprom flag de manutenção
#define maintenance_time 1   //memoria da EEPROM de tempo de uso
#define SPIN_SPEED 200       //parametro da velocidade do spin
#define MINSIGNAL 1000
#define MAXSIGNAL 2000

#endif CONFIG_H

