# Controle de Irrigação baseado em Temperatura e Umidade

## 👥 Integrantes
- Guilherme de Melo Sorrilha
- Guilherme Rodrigues de Andrade
- Victor Antonio Teixeira da Silva
- Gusthavo Costa de Melo
- Lucas Oliveira de Mendonça Almeida

## 📌 Descrição do Projeto
Este projeto utiliza um **ESP32** conectado a um sensor **DHT22** para monitorar **temperatura e umidade** em tempo real.
Os dados são enviados via **MQTT** para o **Node-RED**, onde podem ser processados, visualizados em dashboards e utilizados para **entender se a irrigação do campo deve ser ligada ou desligada**.

A lógica implementada:
- Se **temperatura ≥ 28°C** ou **umidade ≤ 40%** é emitido um aviso para que a irrigação seja ligada (LIGAR).
- Caso contrário, o aviso é para que a irrigação seja desligada (DESLIGAR).

---

## 🏗️ Arquitetura Proposta

🔹 Diagrama da Arquitetura

<img src="https://github.com/user-attachments/assets/c4abbf86-1a12-4733-9769-9eaa7c0972ac" alt="Arquitetura do Projeto" width="700px">

🔹 Explicação
1. **Sensor DHT22**: Coleta os valores de **temperatura e umidade**.  
2. **ESP32**: Faz a leitura dos dados e publica via **MQTT** no broker.  
3. **Mosquitto Broker**: Recebe e distribui as mensagens publicadas no tópico `sensor/dht/passaabola`.  
4. **Node-RED**:  
   - Interpreta os dados JSON recebidos.  
   - Exibe em **debug** ou dashboards (gauge, gráficos, etc).  
   - Pode acionar atuadores para controle da irrigação.

---

## 🛠️ Recursos Necessários

### 🔹 Hardware
- ESP32
- Sensor DHT22
- Jumpers e protoboard (ou conexão direta)
- Fonte USB

<img src="https://github.com/user-attachments/assets/fdea828e-952d-48db-8276-5c11ddedf611" alt="Foto do circuito físico" width="250px">

### 🔹 Software

- [Arduino IDE](https://www.arduino.cc/en/software)
    - Bibliotecas: `WiFi.h`, `PubSubClient.h`, `DHT.h`, `ArduinoJson.h`
- Broker MQTT público (ex.: test.mosquitto.org) ou local
- [Node-RED](https://nodered.org/)
    - Nó `mqtt` in configurado no mesmo tópico
    - Nó `json` para converter em objeto
    - Nó `debug` para visualização

---

## 🚀 Instruções de Uso

### 🔹 1. Montagem do Circuito
- **DHT22 → ESP32**  
  - VCC → 3V3  
  - GND → GND  
  - DATA → GPIO 15  

### 🔹 2. Configuração no Arduino IDE
1. Instale as bibliotecas necessárias:  
   - `DHT sensor library`  
   - `PubSubClient`  
   - `ArduinoJson`  
2. Copie o código fornecido no projeto.  
3. Altere o **SSID** e **senha do Wi-Fi**, se necessário.  
4. Carregue o código no ESP32.  

### 🔹 3. Configuração do Node-RED
1. Adicione um nó **mqtt in** e configure:  
   - Servidor: `test.mosquitto.org`  
   - Porta: `1883`  
   - Tópico: `sensor/dht/passaabola`  
2. Conecte ao nó **json**.  
3. Ligue em um nó **debug** ou em elementos de dashboard. 

### 🔹 4. Teste do Sistema
- Abra o **debug** do Node-RED.  
- Verifique os valores de temperatura, umidade e status da irrigação.  
- Os dados aparecerão no formato JSON:  

```json
{
  "Temperatura": 29.5,
  "Umidade": 38.2,
  "Campo/Irrigação": "LIGAR"
}
