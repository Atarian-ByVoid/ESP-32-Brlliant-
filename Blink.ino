#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "Rede_carlos";
const char* password = "1205032383";
const char* mqtt_server = "192.168.0.107";
const char* mqtt_topic = "/brilliant/listen";

bool mensagemEnviada = false;
long lastMsg = 0;

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando ao WiFi...");
  }
  Serial.println("Conectado ao WiFi");

  client.setServer(mqtt_server, 1883);
}

void loop() {
  digitalWrite(LED_BUILTIN, LOW);
  delay(500);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);

  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  long now = millis();
  if (!mensagemEnviada && now - lastMsg > 5000) {
    lastMsg = now;
    client.publish(mqtt_topic, "       ________________\n"
                               "     |'-.--._ _________:");
    delay(10);
    client.publish(mqtt_topic, "     |  /    |  __    __\\\n"
                               "     | |  _  | [\\_\\= [\\_\\");
    delay(15);
    client.publish(mqtt_topic, "     | |.' '. \\.........|\n"
                               "     | ( <)  ||:       :|_\n"
                               "      \\ '._.' | :.....: |_(o");
    delay(20);
    client.publish(mqtt_topic, "       '-\\_   \\ .------./\n"
                               "       _   \\   ||.---.||  _\n"
                               "      / \\  '-._|/\\n~~\\n' | \\");
    delay(25);
    client.publish(mqtt_topic, "     (| []=.--[===[()]===[) |\n"
                               "     <\\_/  \\_______/ _.' /_/\n"
                               "     ///            (_/_/");
    delay(30);
    client.publish(mqtt_topic, "     |\\\\            [\\ \n"
                               "     ||:|           | I|\n"
                               "     |::|           | I|");
    delay(35);
    client.publish(mqtt_topic, "     ||:|           | I|\n"
                               "     ||:|           : \\:\n"
                               "     |\\:|            \\I|");
    delay(40);
    client.publish(mqtt_topic, "     :/\\:            ([]) \n"
                               "     ([])             [|\n"
                               "      ||              |\\_");
    delay(45);
    client.publish(mqtt_topic, "     _/_\\_            [ -'-.__\n"
                               "snd <]   \\>            \\_____.>\n"
                               "      \\__/");
    mensagemEnviada = true;
  }

  // Lógica para obter dados dos sensores ou outras fontes
  String field1Value = "valor_do_campo_1";
  int field2Value = 42;

  // Monta a mensagem
  String message = "{\"field1\":\"" + field1Value + "\",\"field2\":" + String(field2Value) + "}";

  // Publica a mensagem no tópico MQTT
  client.publish(mqtt_topic, message.c_str());

  delay(5000);  // Aguarda 5 segundos antes de enviar a próxima mensagem
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Conectando ao servidor MQTT...");
    if (client.connect("ESP8266Client")) {
      Serial.println("Conectado ao servidor MQTT");
    } else {
      Serial.print("Falha na conexão, rc=");
      Serial.print(client.state());
      Serial.println(" Tentando novamente em 5 segundos...");
      delay(5000);
    }
  }
}
