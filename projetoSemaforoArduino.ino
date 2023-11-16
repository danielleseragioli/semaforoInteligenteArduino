#include <PubSubClient.h>
#include <Ethernet.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress mqtt_server(192, 168, 15, 11); // Endereço IP do servidor MQTT
EthernetClient ethClient;

const int mqtt_port = 1883;
PubSubClient client(ethClient);

void setup() {
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);

  Ethernet.begin(mac);
  delay(1500);

  client.setServer(mqtt_server, mqtt_port);
}

void loop() {
  if (!client.connected()) {
    if (client.connect("arduinoClient")) {
      Serial.println("Conectado ao servidor MQTT");
    } else {
      Serial.print("Falha na conexão com o servidor MQTT, rc=");
      Serial.print(client.state());
      Serial.println(" Tentando novamente em 5 segundos");
      delay(5000);
    }
  }

  if (digitalRead(8) == HIGH) {
    client.publish("seu_topico", "Luz Vermelha está acesa");
  } else if (digitalRead(9) == HIGH) {
    client.publish("seu_topico", "Luz Amarela está acesa");
  } else if (digitalRead(10) == HIGH) {
    client.publish("seu_topico", "Luz Verde está acesa");
  }

  digitalWrite(8, HIGH);
  delay(4000);
  digitalWrite(8, LOW);

  digitalWrite(9, HIGH);
  delay(2000);
  digitalWrite(9, LOW);

  digitalWrite(10, HIGH);
  delay(4000);
  digitalWrite(10, LOW);

  client.loop();
}