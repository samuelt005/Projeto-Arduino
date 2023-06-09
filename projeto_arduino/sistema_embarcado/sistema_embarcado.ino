//Board DOIT ESP32 DEVKIT V1
#include "BluetoothSerial.h"
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

const int lcdColunas = 16; //Número de colunas do LCD
const int lcdLinhas = 2; //Número de linhas do LCD

const int shield_rele = 26; //Saída padrão do Shield Rele

LiquidCrystal_I2C lcd(0x27, lcdColunas, lcdLinhas);  //Endereço do LCD, numero de colunas e numero de linhas
//Endereço padrão do LCD é 0x27



/*const byte ROWS = 4; //Número de linhas do teclado
const byte COLS = 4; //Número de colunas do teclado

/*char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
}; //Matriz do teclado

byte rowPins[ROWS] = {16, 4, 2, 15}; //Saídas das linhas do teclado
byte colPins[COLS] = {17, 5, 18, 19}; //Saídas das colunas do teclado

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);*/ //Mapeamento do teclado



void setup(){
  Serial.begin(115200); //Serial do teclado

  pinMode(shield_rele, OUTPUT); //Coloca a saída do Shield Rele como saída

  lcd.init(); //inicializa o LCD

  lcd.backlight(); //liga a luz de fundo do LCD
}

void loop(){
  //digitalWrite(shield_rele, LOW); //Abre a tranca
  //delay(10000);
  //digitalWrite(shield_rele, LOW); //Fecha a tranca

  //char customKey = customKeypad.getKey(); //Captura a tecla pressionada do teclado

  /*if (customKey){
    Serial.println(customKey);
  }*/ //imprime a tecla capturada no terminal

  lcd.setCursor(0, 0); //Coloca o cursor do display na primeira coluna e primeira linha
  
  lcd.print("Hello, World!"); //Imprime a mensagem
  
  //lcd.clear(); //Limpa o LCD
}