#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Definições
LiquidCrystal_I2C lcd(0x20, 16, 2);

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

  // Display
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);

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

  delay(200);
}

void liberarAcesso() {
  portaAberta = true;

  // Atualizar logs
  penultimoAcesso = ultimoAcesso;
  ultimoAcesso = horaAtual();

  Serial.println("Log:"); 
  Serial.println("Penultimo acesso- " + penultimoAcesso);
  Serial.println("Ultimo acesso - " + ultimoAcesso);

  atualizarDisplay();

  abrirPorta();

  delay(5000);

  fecharPorta();
  portaAberta = false;

  delay(1000);
  digitalWrite(ledVermelho, LOW);
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
}

void atualizarDisplay() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Ult:" + ultimoAcesso);
  lcd.setCursor(0, 1);
  lcd.print("Pen:" + penultimoAcesso);
}

String horaAtual() {
  // Simulação de hora com millis()
  unsigned long segundos = millis() / 1000;
  unsigned long minutos = segundos / 60;
  segundos = segundos % 60;
  
  char buffer[10];
  sprintf(buffer, "%02lu:%02lu", minutos, segundos);
  
  return String(buffer);
}
