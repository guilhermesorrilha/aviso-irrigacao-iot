#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>
#include <ArduinoJson.h>

#define DHTPIN 15
DHT dht(DHTPIN, DHT22);

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

void setup() {
  Serial.begin(115200);
  dht.begin();

  WiFi.begin("Wokwi-GUEST", "");
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }
  Serial.println("\nWiFi conectado!");

  mqttClient.setServer("test.mosquitto.org", 1883);

  while (!mqttClient.connect("esp32-cliente")) {
    Serial.println("Tentando conectar ao MQTT...");
    delay(1000);
  }

  Serial.println("MQTT conectado!");
}

void loop() {
  if (!mqttClient.connected()) {
    mqttClient.connect("esp32-cliente");
  }
  
  mqttClient.loop();

  float t = dht.readTemperature();
  float h = dht.readHumidity();

  if (isnan(t) || isnan(h)) {
    Serial.println("Erro ao ler do sensor DHT!");
    return;
  }

  StaticJsonDocument<200> json;
  json["Temperatura"] = t;
  json["Umidade"] = h;

  if (t >= 28 || h <= 40) {
    json["Campo/Irrigação"] = "LIGAR";
  } else {
    json["Campo/Irrigação"] = "DESLIGAR";
  }

  char jsonBuffer[200];
  serializeJson(json, jsonBuffer);
  
  mqttClient.publish("sensor/dht/passaabola", jsonBuffer);

  Serial.println("JSON publicado no MQTT!");
  
  
}