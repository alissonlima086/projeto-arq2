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

![Projeto Arq 2 (2)](https://github.com/user-attachments/assets/3b2584a7-b45a-4ed8-a2a3-288e82990e76)




