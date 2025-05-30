#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_LiquidCrystal.h>

// Definições
Adafruit_LiquidCrystal lcd(0);

const int pirPin = 2;
const int ledVerde = 3;
const int ledVermelho = 4;
const int servoPin = 6;

Servo servoMotor;

String ultimoAcesso = "------";
String penultimoAcesso = "------";

bool portaAberta = false;

// Inicio
void setup() {
  // Serial
  Serial.begin(9600);
  Wire.begin();

  lcd.begin(16, 2);

  // Pinos (entrada de movimento saida de leds)
  pinMode(pirPin, INPUT);
  pinMode(ledVerde, OUTPUT);
  pinMode(ledVermelho, OUTPUT);

  // Servo Motor
  servoMotor.attach(servoPin);
  fecharPorta();

  delay(2000);
  lcd.clear();
  atualizarDisplay();
}

void loop() {
  int movimento = digitalRead(pirPin);

  if (movimento == HIGH && !portaAberta) {
    liberarAcesso();
  }
  
  if (portaAberta) {
    movimento = digitalRead(pirPin);

    if (movimento == LOW) {
      // Conta 5 segundos
      unsigned long tempoInicio = millis();
      
      while (millis() - tempoInicio < 5000) {
        movimento = digitalRead(pirPin);
        // Reseta o tempo se houver movimento
        if (movimento == HIGH) {
          tempoInicio = millis();
        }
      }

      // Fecha a porta depois de 5 seg sem movimentos
      fecharPorta();
      portaAberta = false;
    }
  }

  delay(200);
}

void liberarAcesso() {
  portaAberta = true;

  // Atualiza logs
  penultimoAcesso = ultimoAcesso;
  ultimoAcesso = horaAtual();

  Serial.println("Log:"); 
  Serial.println("Penultimo acesso - " + penultimoAcesso);
  Serial.println("Ultimo acesso - " + ultimoAcesso);

  atualizarDisplay();
  abrirPorta();
}

void abrirPorta() {
  servoMotor.write(90);
  
  // Ativar led verde
  digitalWrite(ledVerde, HIGH);
  digitalWrite(ledVermelho, LOW);
}

void fecharPorta() {
  servoMotor.write(0);
  
  // Ativar led vermelho
  digitalWrite(ledVerde, LOW);
  digitalWrite(ledVermelho, HIGH);
  delay(2000);
  digitalWrite(ledVermelho, LOW);
}

void atualizarDisplay() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Ult:" + ultimoAcesso);
  lcd.setCursor(0, 1);
  lcd.print("Pen:" + penultimoAcesso);
}

String horaAtual() {
  unsigned long segundos = millis() / 1000;
  unsigned long minutos = segundos / 60;
  segundos = segundos % 60;
  
  char buffer[10];
  sprintf(buffer, "%02lu:%02lu", minutos, segundos);
  
  return String(buffer);
}
