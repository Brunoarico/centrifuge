#include <Servo.h>
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>
#include <Wire.h>
#include "config.h"
#include "game.h"


static unsigned long Interupt_Last_Call = 0; 
bool ativate = false, is_Ative = false;

//Estados do programa
enum states {ABORT, SET_TIME_STATE, SET_ROTATE_STATE, SET_ACEL_STATE, EXECUTION, FAILURE};

char *std_texts[]{"Set Time:",
              "Set RPM:",  
              "Set Accel:", 
              "Do maintenance!",
              "Mischief Managed!", 
              "Running...",
              "Set!"}; 

int Acel = 100;
double pulse = 0;

static long settime = 0;
static int setrpm = Vmin;

static double rpm;

int state = SET_TIME_STATE;
int velocity = 0;
Servo motor;
LiquidCrystal_I2C lcd(LCD_ADRESS,2,1,0,4,5,6,7,3, POSITIVE);

void calibrate_ESC () {
  motor.writeMicroseconds(MAXSIGNAL);
  delay(2000);
  motor.writeMicroseconds(MINSIGNAL);
  delay(1000);
}

void setup() {
  motor.attach (motor_pin);
  lcd.begin(16, 2);
  lcd.print(" HARDWARE LIVRE");
  lcd.setCursor(6, 1);
  lcd.print("USP");
  calibrate_ESC ();
  lcd.clear();
  pinMode(botao_pin, INPUT_PULLUP);
  pinMode(ENC_PIN, INPUT_PULLUP);
  attachInterrupt(0, magnet_detect, RISING);
  randomSeed(analogRead(2));
  ChapeuSeletor();
  maintenance();
  Serial.begin(9600);
}
/*-------------Funçoes de manutenção--------------*/

/* Se a flag da EEPROM estiver ativada
   solicita o reset fisico na placa.*/
void maintenance (){
  bool stats = EEPROM.read(maintenance_time);
  if(stats)
    while(1) {
      lcd.home();
      lcd.print(std_texts[3]);
      if(!digitalRead(maintenance_reset)) {
        EEPROM.write(maintenance_time, 0);
        asm volatile ("  jmp 0");
      }
    }   
}

/* Atualiza o tempo de uso na EEPROM, se ultrapassar 254 minutos
   solicita a manutenção.                                     */
void maintenance_atualize(long milliseconds) {
  byte t = milliseconds/60000;
  int now = EEPROM.read(eeprom_maintenance); //tempo de uso
  bool stats = EEPROM.read(maintenance_time); //É hora da manutenção?
  int variation = now + t; 
  Serial.println(variation);
  if(variation > 254 && !stats) {
    EEPROM.write(maintenance_time, 1);
    variation = 254;
  }
  if(now != variation) 
    EEPROM.write(eeprom_maintenance, variation);
  maintenance ();
}

/*-------------Função de interface do Motor--------------*/

/* Gera o PWM para controlar o motor proporcional 
   a variavel power.                           */
void motor_control (int power){
  Serial.println(power);
  int value = map(power, 0, 254, MINSIGNAL, MAXSIGNAL);
  motor.writeMicroseconds(value);
}

/*-------------Funçoes de Medidas--------------*/

/* Calcula a RPM do motor baseado na quantidade de 
   pulsos no sensor, o tempo de amostragem é o trigger  
   para o update.                                   */
double update_rpm (double trigger) {
  static double update_rpm_timeold = 0;
  double delta = millis() - update_rpm_timeold;
  double RPM;
  if(delta >= trigger){
      RPM = (10000 * pulse) / delta;
      update_rpm_timeold = millis();
      pulse = 0;
   }
   return RPM;
}

/* Calcula a força g baseado na RPM */
unsigned int gforce (double rpm) {
  return pow (rpm * pi / 30 , 2) * raio_rotor / g;
}

/*-------------Fução de interface com o Encoder--------------*/

/* Faz a interpretação do sinal do Encoder */
int8_t read_encoder() {
  static int8_t enc_states[] = {0,-1,1,0,1,0,0,-1,-1,0,0,1,0,1,-1,0};
  static uint8_t old_AB = 0;      //armazena o estado anterior
  old_AB <<= 2;                   //grava estado anterior
  old_AB |= ( (ENC_PORT) & 0x03 );  //adiciona estado atual
  return enc_states[( old_AB & 0x0f )];
}

/*-------------Funçoes de Estados--------------*/

/* Ao ser ativada faz um spin rapido do motor enquanto a variavel 
   button for verdadeira.                                      */
void spin(bool button) {
  
  if(!button){
    lcd.clear();
    lcd.home();
    lcd.print("Do a Barrel Roll");
    while(!digitalRead(ENC_PIN)){
      if(velocity < SPIN_SPEED)
        motor_control(++velocity);
        update_rpm(20);
        delay(20);
        //Serial.println(velocity);
    }
    while (velocity > 0) {
      motor_control(--velocity);
      delay(20);
    }
    ativate = false;
    lcd.clear();
    lcd.print(std_texts[0]);
  }
}

/* Função que obtem o tempo de operação da centrifuga
   introduzido pelo usuario                        */
long time_state() {
  long tmp = 0; 
  long encoder = settime/1000;
  
  while(!digitalRead(botao_pin)){} //Verifica se o botão esta pressionado
  lcd.print(std_texts[0]);
    while(state == SET_TIME_STATE){
      while(!digitalRead(botao_pin)){}
      
      spin(digitalRead(ENC_PIN));
      
      tmp = read_encoder();
      
      if( tmp ) {
        encoder += StepTIME * tmp;
        if(encoder < 0) encoder = 0;
        lcd.setCursor(0, 1);
        strtime(encoder);
      }
      
      if(!digitalRead(botao_pin)) {
        lcd.clear();
        lcd.print(std_texts[6]);      
        delay(1000);
        lcd.clear();
        state = SET_ROTATE_STATE;
        return encoder * 1000;
      }
    }
}

/* Função que obtem o RPM de operação da centrifuga 
   informado pelo usuario                        */
int rotate_state() {
  int encoder = setrpm, tmp = 0, ti, tf;
   Serial.println("OK");
  ti= millis ();
  while(!digitalRead(botao_pin)){} //Verifica se o botão esta pressionado
  tf= millis ();

  if (tf-ti > 3000) {
    lcd.print("ARCADE MODE ON!");
    delay(1000);
    game_setup();
    game();
  }
  
  lcd.print(std_texts[1]);
  while(state == SET_ROTATE_STATE){

    set_acel(digitalRead(ENC_PIN));
    
    tmp = read_encoder();
    if(tmp){
      encoder += StepROTATE * tmp;
      if(encoder < Vmin) encoder = Vmin;
      if(encoder > Vmax) encoder = Vmax;
      lcd.setCursor(0, 1);
      lcd.print(encoder);
      lcd.print("     ");
    }
    if(!digitalRead(botao_pin)) {
      state = EXECUTION;
      lcd.clear();
      lcd.print(std_texts[6]);
      delay(1000);
      lcd.clear();
      return encoder;
    }
  }
}

/* Função que obtem do usuario o parametro de aceleração 
   de partida e parada da centrifugação, recebe como 
   parametro o boleano para a ativação dessa opção     */

void set_acel (bool button){
  int encoder = Acel, tmp = 0;
  if(!button){
    lcd.clear();
    lcd.print(std_texts[2]);
    while (!digitalRead(botao_pin)){}
    state = SET_ACEL_STATE;
    while (state == SET_ACEL_STATE) {
      tmp = read_encoder();
      if(tmp){
        encoder += 50 * tmp;
        if(encoder < 100) encoder = 100;
        if(encoder > 500) encoder = 500;
        lcd.setCursor(0, 1);
        lcd.print(encoder);
        lcd.print("    ");
      }
      if(!digitalRead(botao_pin)) {
        lcd.clear();
        lcd.print(std_texts[6]);
        delay(1000);
        lcd.clear();
        Acel = encoder;
        lcd.home();
        lcd.print(std_texts[1]);
        state = SET_ROTATE_STATE;
      }
    }
  }
}

/* Executa a rotação do motor em s_rpm durante s_time segundos,
   faz verificação de estado do motor para uma operação segura. */
void execution_state(int s_rpm, long s_time){
  unsigned long beginContdown;
  int cont_flag = 1, show_flag = 1, error = 400;
  double rpm;
    
  while(!digitalRead(botao_pin)){} //Verifica se o botão esta pressionado
        
        lcd.print(std_texts[5]);
        delay(800);
        lcd.clear();
        while(state == EXECUTION){
          
          rpm = update_rpm(Acel);                         //Verifica a rotação

          is_Ative = ativate;                             //ativa a flag de funcionamento
          
          if(!digitalRead(ENC_PIN)) 
            show_flag = !show_flag;

          ItsShowTime(rpm, show_flag);                    //alterna o mostrador rpm/gforce
          
          if(Rotate_verification ()) state = FAILURE;     //verifica falhas
          
          if(rpm >= s_rpm-error && cont_flag) {           //inicia contagem regressiva
            beginContdown = millis();
            cont_flag = 0;
          }

          if(!cont_flag) {
            lcd.setCursor(0, 0);
            strtime((s_time - millis() + beginContdown) / 1000);
          }
          else { 
            lcd.setCursor(0, 0);
            strtime(s_time/1000);
          }
          
          if (rpm < s_rpm - error && velocity < 254) motor_control(velocity++);
          else if(rpm > s_rpm+error) motor_control(velocity--);
          //Serial.println(velocity);
          delay(Acel);
          
          if(!digitalRead(botao_pin) || ((millis()-beginContdown) > s_time) && cont_flag == 0 ){
            abortar();
          }
    }
    maintenance_atualize(s_time);
}

/* Verifica se a atividade do sensor, em caso de ultrapassar 
   1000 ms de inatividade retorna true.                   */

bool Rotate_verification () {
    if (is_Ative && ativate) {
      //Serial.println(millis() - Interupt_Last_Call);
      if(millis() - Interupt_Last_Call > 1000){
        return true;
      }
    }
    else return false;
}

/* Aborta a operação atual e reduz a velocidade do motor até
   sua completa parada.                                    */
void abortar(){
  lcd.clear();
  lcd.print(std_texts[4]);
  while (velocity > 0){
    motor_control(--velocity);
    delay(Acel);
  } 
  update_rpm(2000);
  state = SET_TIME_STATE;
  ativate = false;
  delay(1000);
  lcd.clear();
}
/* Em caso de falha do motor todas as atividades são suspensas
   o motor é desligado e um aviso é mostrado.               */
void failure(){
  lcd.clear();
  lcd.print("Houston, we have");
  lcd.setCursor(0,1);
  lcd.print("   a problem!");
  while(1){motor.writeMicroseconds(0);};
}

/*-------------Funçoes de Print--------------*/

/* Escreve na tela uma string que converte a variavel 
   tempo para o formato time stamp HH:MM:SS        */
void strtime (unsigned long tempo){
  long sec, minut, hour;
  sec = tempo % 60;
  minut = (tempo/60);
  hour = minut /60;
  lcd.print(leftPad(hour,2,'0')); 
  lcd.print(":");
  lcd.print(leftPad(minut % 60,2,'0'));
  lcd.print(":");
  lcd.print(leftPad(sec,2,'0'));

}

/* Formata o o valor value, com uma certa quantidade 
   de digitos numDigits, sendo esses digitos do tipo
   escolhido pelo padrão pattern.                  */
String leftPad(float value, int numDigits, char pattern) {
  String retVal = String((int)value);
  int lenPad = numDigits - retVal.length(); 
  for (int x = 1; x <= lenPad; x++){
    retVal = pattern + retVal;   
  }
  return retVal;
}

/* Recebe o valor de rpm e um boleano, se 1 mostra RPM,
   senão mostra a Gforce.                            */
void ItsShowTime(double rpm, bool set) {
  lcd.clear();
  lcd.setCursor(0, 1);
  set ? lcd.print(rpm) : lcd.print(gforce(rpm));
  lcd.setCursor(13, 1);
  set ? lcd.print("RPM") : lcd.print("G");
}

/*-------------Função da Interrupção--------------*/

/* Função chamada na interrupção, lê os pulsos no sensor,
   e se chamada define o estado ativado na função ativate. */
void magnet_detect() {
  
  if (!ativate && state == EXECUTION ) {
    ativate = true; 
  }
  
  Interupt_Last_Call = millis();
  pulse++;
}


/*Brincadeira do inicio: Escolhe uma escola  
  aleatoria do Harry Potter.             */ 
void ChapeuSeletor() {
  int escola;
  lcd.clear();
  lcd.home();
  lcd.print("Today your house");
  delay(500);
  lcd.setCursor(0, 1);
  escola = random(0,4);
  if(escola == 0) lcd.print("is Gryffindor!");
  else if(escola == 1) lcd.print("is Hufflepuff!");
  else if(escola == 2) lcd.print("is Ravenclaw!");
  else lcd.print("is Slytherin!");
  delay(2000);
  lcd.clear();
}


void loop() {
  pulse = 0;
  switch(state){
    
    case(SET_TIME_STATE):
        settime = time_state();
        delay(500);
        break;
        
    case(SET_ROTATE_STATE):
        setrpm = rotate_state();   
        delay(500);
        break;
        
    case (EXECUTION):
        execution_state(setrpm, settime);
        ativate = false;
        break;
        
    case (FAILURE):
      failure();
      break;
  }
}

void game_setup() {
  lcd.clear();
  crash = crashtime = road_index = 0;
  step_duration = MAXSTEPDURATION;
  line_buff[1+ROADLEN] = '\0'; // null terminate it
  for (int i=0; i<NGLYPHS; i++) {
    lcd.createChar(i+1,glyphs[i]);
  }
  for (int i=0; i<ROADLEN; i++) {
    road[i]=-1;
  }
  car_pos = 2;
  drawRoad();
  lcd.setCursor(1,0);
  lcd.print("Trucks ahead,");
  lcd.setCursor(1,1);
  lcd.print("Drive carefully");
  delay(2000);
}


void drawRoad() {
  for (int i=0; i<2; i++) {
    if (crash) {
      line_buff[0]=crash2glyphs[car_pos/factor][i];
    } 
    else {
      line_buff[0]=car2glyphs[car_pos/factor][i];
    }
    for (int j=0; j<ROADLEN; j++) {
      int pos = road[(j+road_index)%ROADLEN];
      line_buff[j+1] = pos>=0 && pos<NCARPOSITIONS ? truck2glyphs[pos][i] : BLANK;
    }
    lcd.setCursor(0,i);
    lcd.print(line_buff);
  }
}
void game() { 
  unsigned long int antes = 0, depois = 0;
  
  begintime = millis();
  
  while(1) {
  unsigned long int now = millis();
  if (!crash) {
      car_pos += read_encoder();
      if(car_pos <= 0) car_pos = 0;
      if(car_pos > factor*NCARPOSITIONS) car_pos = factor*NCARPOSITIONS;
  
      crash = (car_pos/factor==road[road_index]);
  }
  if (crash) {
    if (!crashtime) {
      crashtime=now;
      drawRoad();
      // Game over text
      // (keep first 2 "crash" columns intact)
      lcd.setCursor(2,0);
      lcd.print("Crashed after");
      lcd.setCursor(2,1);
      lcd.print((now-begintime)/1000);
      lcd.print(" seconds.");
    }
    delay(3000); // Wait a bit between writes
    state = SET_TIME_STATE;
    lcd.clear();
    time_state();
    break;
  } 
  else {
    if(millis() - antes > step_duration){
      antes = millis();
      int prev_pos = road[(road_index-1)%ROADLEN];
      int this_pos = random(MAXROADPOS);
      while (abs(this_pos-prev_pos)<2) { // don't jam the road
        this_pos = random(MAXROADPOS);
      }
      road[road_index] = this_pos;
      road_index = (road_index+1)%ROADLEN;
      drawRoad();
      antes = millis();
      if (step_duration>MINSTEPDURATION) {
        step_duration--; // go faster
    }
   }
  }
 }
}



