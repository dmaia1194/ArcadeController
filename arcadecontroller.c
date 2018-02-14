#include <FastLED.h>

// Potenciometro Brilho LED
const int pot_p = A0;
int pot_v = 0;
int pot_b = 0;
int first = 1;
// FIM - Potenciometro Brilho LED

// Sensor presença LED
const int pir_p = 2;
int pir_v = 0;
const long pir_delay = 50000;
unsigned long pir_loop;
unsigned long pir_time;
// FIM - Sensor presença LED

// Botões extras
const int htk_p = 7;
int htk_v = 0;
int menu_press = 0;
int exit_press = 0;
const int pause_p = 8;
int pause_v = 0;
int pause_press = 0;
// FIM - Botões extras

// Ficheiro
const int coin1_p = A1;
const int coin2_p = A2;
const int coin3_p = A3;
const int coin4_p = A4;
int coin1_v = 0;
int coin2_v = 0;
int coin3_v = 0;
int coin4_v = 0;
int coin1_press = 0;
int coin2_press = 0;
int coin3_press = 0;
int coin4_press = 0;
// FIM - Ficheiro

// LEDs
const int ctrl1_pin = 3;
const int ctrl2_pin = 5;
const int strip1_pin = 6;
const int strip2_pin = 9;

const int ctrl_num = 2;

const int ctrl_leds = 11;
const int strip1_leds = 74;
const int strip2_leds = 346;

const int btn_leds = 2;
const int coin_leds = 4;
const int indoor_leds = 68;
const int left_leds = 90;
const int botton_leds = 97;
const int right_leds = 90;
const int marquee_leds = 69;

CRGB ctrl[ctrl_num][ctrl_leds];
CRGB strip1[strip1_leds];
CRGB strip2[strip2_leds];
// FIM - LEDs

// Serial Colors
int R[ctrl_leds], G[ctrl_leds], B[ctrl_leds];
// FIM - Serial Colors

int bright = 0;

// Functions
void clearColors(){
    for(int i = 0; i<ctrl_leds; i++){
        R[i] = 0;
        G[i] = 0;
        B[i] = 0;
      }
    }

void setColors(char rcv[]){
    if(rcv[0]=='0'){
        if(rcv[1]=='0'){
          	R[2] = 255;
          	B[2] = 215;
          	R[3] = 255;
          	B[3] = 215;
          	R[8] = 255;
          	B[8] = 215;
          	R[9] = 255;
          	B[9] = 215;
          	R[10] = 255;
          	B[10] = 215;
          }
        else if(rcv[1]=='m'){
            R[3] = 255;
            G[3] = 255;
            R[4] = 255;
            G[4] = 255;
            R[5] = 255;
            G[5] = 255;
            G[6] = 255;
            B[6] = 255;
            G[7] = 255;
            B[7] = 255;
            G[8] = 255;
            B[8] = 255;
            R[10] = 255;
          }
        else if(rcv[1]=='n'){
            R[2] = 255;
            B[2] = 255;
            R[3] = 255;
            G[3] = 255;
            R[4] = 255;
            G[4] = 255;
            R[5] = 255;
            G[5] = 255;
            R[6] = 255;
            G[6] = 255;
            G[7] = 255;
            B[7] = 255;
            G[8] = 255;
            B[9] = 255;
            R[10] = 255;
          }
        else if(rcv[1]=='s'){
            R[2] = 255;
            B[2] = 255;
            R[3] = 255;
            G[3] = 255;
            R[4] = 255;
            G[5] = 255;
            B[5] = 255;
            G[6] = 255;
            B[6] = 255;
            B[7] = 255;
            G[8] = 255;
            R[10] = 255;
          }
      }
    else {
      	R[10] = 255;
      	B[10] = 215;

        if(rcv[1]=='a'){
        		R[9] = 255;
        	}
      	else if(rcv[1]=='b'){
       		R[8] = 255;
        		G[8] = 255;
        		R[9] = 255;
        	}
      	else if(rcv[1]=='c'){
       		R[2] = 255;
        		G[8] = 255;
        		R[9] = 255;
        		G[9] = 255;
        	}
      	else if(rcv[1]=='d'){
       		R[2] = 255;
        		R[9] = 255;
        		G[9] = 255;
        		G[8] = 255;
        		B[7] = 255;
        	}
      	else if(rcv[1]=='e'){
       		R[2] = 255;
        		R[3] = 255;
        		G[3] = 255;
        		B[4] = 255;
        		R[9] = 255;
        		R[8] = 255;
        		G[8] = 255;
        		B[7] = 255;
        	}
      	else if(rcv[1]=='f'){
       		R[2] = 255;
        		G[2] = 255;
        		R[9] = 255;
        		G[8] = 255;
        	}
      	else if(rcv[1]=='g'){
       		R[2] = 255;
        		G[2] = 255;
        		R[9] = 255;
        		G[8] = 255;
        		B[7] = 255;
        	}
      	else if(rcv[1]=='f'){
       		G[2] = 255;
        		R[9] = 255;
        		R[8] = 255;
        		G[8] = 255;
        	}
      }
    }

void defineControllColors(CRGB target[], char rcv[]){
    clearColors();
    setColors(rcv);

    for(int i = 0; i<ctrl_leds; i++){
        target[i].setRGB(R[i],G[i],B[i]);
      }
    }

void fill_range_CRGB(CRGB target[], int start = 0, int end = 0, int R = 0, int G = 0, int B = 0) {
    for(int i = start; i<end; i++){
        target[i].setRGB(R,G,B);
      }
    }
// END - Functions

void setup() {
    Serial.begin(115200);

    pinMode(pir_p, INPUT);
    pir_loop = millis();

    pinMode(htk_p, INPUT);
    pinMode(pause_p, INPUT);

    pinMode(coin1_p, INPUT);
    pinMode(coin2_p, INPUT);
    pinMode(coin3_p, INPUT);
    pinMode(coin4_p, INPUT);

    FastLED.addLeds<NEOPIXEL, ctrl1_pin>(ctrl[0], ctrl_leds);
    FastLED.addLeds<NEOPIXEL, ctrl2_pin>(ctrl[1], ctrl_leds);

    FastLED.addLeds<NEOPIXEL, strip1_pin>(strip1, strip1_leds);
    FastLED.addLeds<NEOPIXEL, strip2_pin>(strip2, strip2_leds);
  }

void loop() {
    // Controla o brilho com o potenciometro e sensor de presença  
    pot_v = analogRead(pot_p);            // Lê os dados do potenciometro
    pot_b = map(pot_v, 0, 1023, 0, 250);  // Mapeia o valor entre 0-250

    pir_time = millis();

    if(first){
        bright = pot_b;
      }
    else{
        pir_v = digitalRead(pir_p);
        if(pir_v){
            bright = (bright < pot_b) ? bright + 5: pot_b; // Fade-in
            pir_loop = pir_time;
          }
        else{
            if((pir_time - pir_loop) >= pir_delay){
                bright = (bright > 5) ? bright - 5 : 0;       // Fade-out
              }
            else{
                bright = pot_b;
              }
          }
      }

    first = 0;
    // FIM - Controla o brilho com o potenciometro e sensor de presença

  // Botões extras, hotkey e pause
    htk_v = digitalRead(htk_p); // Lê o valor do botão
    pause_v = digitalRead(pause_p);

  if(htk_v && pause_v){
        menu_press = 1;
        exit_press = 0;
        pause_press = 0;
        Serial.println("menu");
      }
    else if((!htk_v || !pause_v) && menu_press){
        menu_press = 0;
        Serial.println("menuOFF");
      }
    else if(htk_v && !menu_press){
        exit_press = 1;
        Serial.println("exit");
      }
    else if(!htk_v && exit_press){
        exit_press = 0;
        Serial.println("exitOFF");
      }
    else if(pause_v && !menu_press){
        pause_press = 1;
        Serial.println("pause");
      }
    else if(!pause_v && pause_press){
        pause_press =  0;
        Serial.println("pauseOFF");
      }
    // FIM - Botões extras, exit e pause

    // Ficheiro e mecanismo da porta
    coin1_v = digitalRead(coin1_p); // Lê o valor do sensor
    coin2_v = digitalRead(coin2_p);
    coin3_v = digitalRead(coin3_p);
    coin4_v = digitalRead(coin4_p);

    if(coin1_v){
        coin1_press = 1;
        Serial.println("coin1");
      }
    else if(!coin1_v && coin1_press){
        coin1_press = 0;
        Serial.println("coin1OFF");
      }

    if(coin2_v){
        coin2_press = 1;
        Serial.println("coin2");
      }
    else if(!coin2_v && coin2_press){
        coin2_press = 0;
        Serial.println("coin2OFF");
      }

    if(coin3_v){
        coin3_press = 1;
        Serial.println("coin3");
      }
    else if(!coin3_v && coin3_press){
        coin3_press = 0;
        Serial.println("coin3OFF");
      }

    if(coin4_v){
        coin4_press = 1;
        Serial.println("coin4");
      }
    else if(!coin4_v && coin4_press){
        coin4_press = 0;
        Serial.println("coin4OFF");
      }
    // FIM - Ficheiro e mecanismo da porta

  // LEDs
    if(Serial.available()>0) {
        char inChar;
        int index = 0;
        char rcv[2];

        while(1) {
            if(index<2) {
                inChar = Serial.read();
                rcv[index] = inChar;
              }
            else {
                break;
              }

            index++;
          }

        defineControllColors(ctrl[0], rcv);
        defineControllColors(ctrl[1], rcv);

        if(rcv[0]=='0'){
            fill_range_CRGB(strip1, 0, btn_leds);
            fill_range_CRGB(strip1, btn_leds, (btn_leds + coin_leds), 255, 255, 255);

            if(rcv[1]!='0'){
                fill_range_CRGB(strip1, 0, btn_leds, 170, 0, 255);
              }
          }
        else{
            fill_range_CRGB(strip1, 0, btn_leds, 170, 0, 255);
            fill_range_CRGB(strip1, btn_leds, (btn_leds + coin_leds));

            if(rcv[0]=='1'){
                fill_range_CRGB(strip1, btn_leds, (btn_leds + 1), 255, 255, 255);
              }
            else if(rcv[0]=='2'){
                fill_range_CRGB(strip1, btn_leds, (btn_leds + 1), 255, 255, 255);
                fill_range_CRGB(strip1, (btn_leds + 3), (btn_leds + 4), 255, 255, 255);
              }
            else if(rcv[0]=='3'){
                fill_range_CRGB(strip1, btn_leds, (btn_leds + 2), 255, 255, 255);
                fill_range_CRGB(strip1, (btn_leds + 3), (btn_leds + 4), 255, 255, 255);
              }
            else{
                fill_range_CRGB(strip1, btn_leds, (btn_leds + coin_leds), 255, 255, 255);
              }
          }
      }

    fill_range_CRGB(strip1, (btn_leds + coin_leds), (btn_leds + coin_leds + indoor_leds), 170, 0, 255);

    fill_range_CRGB(strip2, 0, (strip2_leds - marquee_leds), 170, 0, 255);
    fill_range_CRGB(strip2, (strip2_leds - marquee_leds), strip2_leds, 21, 0, 31);

    FastLED.setBrightness(bright);
    FastLED.show();
    // FIM - LEDs
  }