// Board DOIT ESP32 DEVKIT V1
#include "BluetoothSerial.h"
#include <LiquidCrystal_I2C.h>

const int lcdColunas = 16; // Número de colunas do LCD
const int lcdLinhas = 2;   // Número de linhas do LCD

const int shield_rele = 26; // Saída padrão do Shield Rele

String senhaCorreta = "";          // Senha padrão
const int tentativasMaximas = 3;   // Número máximo de tentativas permitidas
const int bloqueioTempo = 3600000; // Tempo de bloqueio em milissegundos (1 hora)
const int tempo_desbloqueado = 10000;

LiquidCrystal_I2C lcd(0x27, lcdColunas, lcdLinhas); // Endereço do LCD, número de colunas e número de linhas
// Endereço padrão do LCD é 0x27

int tentativas = 0;            // Contador de tentativas
bool bloqueado = false;        // Flag para verificar se está bloqueado
unsigned long tempoDesbloqueio; // Tempo de desbloqueio

//---------------------CONFIGURAÇÃO BLUETOOTH--------------------------//
String device_name = "ESP32-BT-Samuel";

const char *pin = "1234";

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

#if !defined(CONFIG_BT_SPP_ENABLED)
#error Serial Bluetooth not available or not enabled. It is only available for the ESP32 chip.
#endif

BluetoothSerial SerialBT;
//---------------------------------------------------------------------//

void setup()
{
  Serial.begin(115200); // Serial do teclado

  SerialBT.begin(device_name); // Nome do device

  pinMode(shield_rele, OUTPUT); // Coloca a saída do Shield Rele como saída
  digitalWrite(shield_rele, HIGH); // Começa com a tranca fechada

  lcd.init();       // Inicializa o LCD
  lcd.backlight();  // Liga a luz de fundo do LCD

  lcd.setCursor(0, 0); // Coloca o cursor do display na primeira coluna e primeira linha
  lcd.print("Insira a senha"); // Imprime a mensagem para inserir a senha
}

void loop()
{
  if (bloqueado)
  {
    if (millis() - tempoDesbloqueio >= bloqueioTempo)
    {
      bloqueado = false;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Insira a senha");
      tentativas = 0; // Reinicia o contador de tentativas
    }
    return;
  }

  if (SerialBT.available())
  {
    String senha = SerialBT.readStringUntil('\n');
    senha.trim(); // Remove espaços em branco do início e fim da senha

    if (senhaCorreta == "")
    {
      // Pré-cadastro da senha
      senhaCorreta = senha;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Senha cadastrada");
      delay(2000);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Insira a senha");
    }
    else
    {
      if (senha.length() == senhaCorreta.length() && senha == senhaCorreta)
      {
        // Senha correta
        tentativas = 0; // Reinicia o contador de tentativas
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Senha correta");
        digitalWrite(shield_rele, LOW); // Abre a tranca
        delay(tempo_desbloqueado);
        digitalWrite(shield_rele, HIGH); // Fecha a tranca novamente
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Insira a senha");

        // Bloqueia por 1 hora após 3 tentativas incorretas consecutivas
      }
      else
      {
        // Senha incorreta
        tentativas++;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Senha incorreta");
        lcd.setCursor(0, 1);
        lcd.print("Tentativas: " + String(tentativas) + "/" + String(tentativasMaximas));

        if (tentativas >= tentativasMaximas)
        {
          bloqueado = true;
          tempoDesbloqueio = millis();
          lcd.setCursor(0, 1);
          lcd.print("Bloqueado por 1h");
        }
      }
    }
  }
}
