# aviso-irrigacao-iot

## 📌 Descrição do Projeto

Este projeto utiliza um ESP32 conectado a um sensor DHT22 para monitorar temperatura e umidade em tempo real.

Os dados são enviados via MQTT para o Node-RED, onde podem ser processados, visualizados em dashboards e utilizados para entender se a irrigação do campo deve ser ligada ou desligada.

A lógica implementada:

- Se temperatura ≥ 28°C ou umidade é emitido um aviso para que a irrigação seja ligada (LIGAR).
- Caso contrário, o aviso é para que a irrigação seja desligada (DESLIGAR).

---

## 🏗️ Arquitetura Proposta

🔹 Diagrama da Arquitetura

🔹 Explicação

---

## 🛠️ Recursos Necessários

🔹 Hardware

- ESP32

- Sensor DHT22

- Jumpers e protoboard (ou conexão direta)

- Fonte USB

🔹 Software