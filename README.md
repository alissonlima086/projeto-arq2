# Este projeto foi realizado para a matéria de Arquitetura e Organização de Computadores 2 da UNITINS

Projeto desenvolvido pelos alunos: Alisson de Oliveira Lima; Thallyson Glória Alves.

## Projeto

A ideia inicial do projeto foi desenvolver uma trava de porta que destravasse via leitura de digital, que guardasse log e que verificasse a pessoa em um sistema externo, no entanto, logo vimos que não seria possivel dado as limitações do simulador. Portando, para abstrair a ideia do projeto, estaremos fazendo uma trava de porta que destrave via sensor de movimento e que guarde o log dos dois ultimos horarios de abertura.


O projeto foi desenvolvido utilizando a plataforma do Tinkercad.

---

## Componentes

Para o desenvolvimento deste projeto foram utilizados:

PIR1 - 1 - Sensor PIR

U1 - 1 - Arduino Uno R3

D1 - 1 - Verde LED

U2 - 1 - Baseado em MCP23008, 32 (0x20) LCD 16 x 2 (I2C)

SERVO1 - 1 - Posicional Micro servo

D2 - 1 - Vermelho LED

R1, R2 - 	2 -	1 kΩ Resistor

---

## Visão Esquemática

A seguir, a visão esquemática do projeto com os componentes:

![image](https://github.com/user-attachments/assets/dda70a51-02aa-417b-acac-1316896eefd3)
*Houve uma questão em que um dos leds ficou isolado na esquematização, mesmo que na arquitetura ele esteja conectado e esteja completamente funcional, não conseguimos encontrar a razão e deixamos como está, visto que afeta apenas a geração da visão esquematica.

---

## Arquitetura

A seguir, a arquitetura do arduino com seus componentes conectados:

![Projeto Arq 2 (3)](https://github.com/user-attachments/assets/89e773c3-0a31-4044-b0e4-c89647153ad6)

---

## Código

Iniciamos com os imports que serão utilizados para o controle do Servo Motor e com o Display.
```
#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
```

A seguir declaramos as variaveis de configuração do Display, configuração dos pino, controle do Servo Motor, status de log e controle da porta.
```
LiquidCrystal_I2C lcd(0x20, 16, 2);

const int pirPin = 2;
const int ledVerde = 3;
const int ledVermelho = 4;
const int servoPin = 6;

Servo servoMotor;

String ultimoAcesso = "------";
String penultimoAcesso = "------";

bool portaAberta = false;
```

A seguir o inicio das configurações, iniciando as configurações do serial para os logs, iniciando o Display, Input e Output para os sensores e iniciando o Servo motor, definindo um estado "default" para o sistema.
```
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
```

A seguir um loop que está fazendo a leitura do sensor de movimento, que chama o liberarAcesso() caso seja detectado algum movimento.
```
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
```

A seguir a função de liberarAcesso(), que define a porta aberta como true, imprime os logs no display e divide chama outras funções para executar a atualização do display, abertura e fechamento da porta.
```
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
```

A seguir a função de abrir e fechar a porta que também executam a atualização dos leds.
```
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
```

A seguir a atualização do display com as informações dos logs.
```
void atualizarDisplay() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Ult:" + ultimoAcesso);
  lcd.setCursor(0, 1);
  lcd.print("Pen:" + penultimoAcesso);
}
```

E por último uma função que retorna uma string de minutos e segundos sendo utilizado para registrar o log.
```
String horaAtual() {
  unsigned long segundos = millis() / 1000;
  unsigned long minutos = segundos / 60;
  segundos = segundos % 60;
  
  char buffer[10];
  sprintf(buffer, "%02lu:%02lu", minutos, segundos);
  
  return String(buffer);
}
```

---

## Limitações

Como anteriormente mencionado, houveram limitações no projeto devido falta de um ambiente fisico para desenvolvimento, aqui algumas das dificuldades pontuadas:

- Impossibilidade de conexão com aplicações externas, como servidores e dispositivos de armazenamento;
- Falta de alguns sensores nos simuladores, como o de digital e o de relogio;

## Melhorias

Algumas melhorias que poderiam ser realizadas no projeto incluem:

- Exportação de dados de log para um dispositivo ou servidor externo;
- Adicionar autenticação, juntamente a uma conexão a um banco de dados;

## Problemas

Houveram alguns problemas e dificuldades durante o projeto, desde a concepção até o desenvolvimento até a versão final, dentre eles:
- Limitação dos simuladores;
- Organização dos circuitos;
- Abstração de componentes;
- Algumas logicas específicas de algumas partes do codigo;
