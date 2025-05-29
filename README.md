# Este projeto foi realizado para a matéria de Arquitetura e Organização de Computadores 2 da UNITINS

## Projeto

A ideia inicial do projeto foi desenvolver uma trava de porta que destravasse via leitura de digital, que guardasse log e que verificasse a pessoa em um sistema externo, no entanto, logo vimos que não seria possivel dado as limitações do simulador. Portando, para abstrair a ideia do projeto, estaremos fazendo uma trava de porta que destrave via sensor de movimento e que guarde o log dos dois ultimos horarios de abertura.

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
