===============================================================
// ======================================================================
// --- Inclusão de bibliotecas ---
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <UrlEncode.h> /

//variaveis globais 

#define DHTPIN 5
#define DHTTYPE DHT11
#define PIN_MQ5 17 // Pino analógico  o MQ-5 está conectado
#define PIN_MQ135 16 // Pino analógico  o MQ-135 está conectado
#define LIMITE_MQ5 500 // Limite para acionar o alerta do MQ-5
#define LIMITE_MQ135 600 // Limite para acionar o alerta do MQ-135

const char* ssid = ""; // nome da rede do seu wifi
const char* password = "" // Aqui você colocará a senha do seu wifi;
String numeroTelefone = ""; // seus numeros de telefone
String apiKey = ""; // aqui você deverá adicionar a ApiKey do chatbot 

WiFiClientSecure client;
DHT dht(DHTPIN, DHTTYPE);

int lerMQ5() {
  int valor = analogRead(PIN_MQ5);
  return valor;
}

int lerMQ135() {
  int valor = analogRead(PIN_MQ135);
  return valor;
}

void sendMessage(String message) {
  String url = "http://api.callmebot.com/whatsapp.php?phone=" + numeroTelefone + "&apikey=" + apiKey + "&text=" + urlEncode(message);
  WiFiClient client;    
  HTTPClient http;
  http.begin(client, url);
  // Especificação do cabeçalho
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  
  int httpResponseCode = http.POST("");
  if (httpResponseCode == 200) {
    Serial.println("Mensagem enviada com sucesso");
  } else {
    Serial.println("Erro no envio da resposta");
    Serial.print("HTTP código de resposta: ");
    Serial.println(httpResponseCode);
  }
  http.end();
}

// ======================================================================
void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println(WiFi.macAddress());

  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("Conectando a rede WiFi");
    delay(1000);
  }
  Serial.println("Conectado a rede, ");
  Serial.println(ssid);
  Serial.println(WiFi.status());
  dht.begin();
  
  sendMessage("Sistema iniciado e conectado à rede WiFi.");
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("Conectado à Internet");

    float temperatura = 40 ; 
    float umidade = dht.readHumidity();
    int valorMQ5 = lerMQ5();
    int valorMQ135 = lerMQ135();

    if (temperatura > 30) {
      sendMessage("Atenção moradora Cristiane do APARTAMENTO - 104B - Atenção! A temperatura está acima de 30°C no seu apartamento.");
    }

    if (valorMQ5 > LIMITE_MQ5) {
      sendMessage("Atenção moradora Cristiane do APARTAMENTO - 104B Atenção! Possível vazamento de gás MQ-5 detectado.");
    }

    if (valorMQ135 > LIMITE_MQ135) {
      sendMessage("Atenção moradora Cristiane do APARTAMENTO - 104B Atenção! Possível vazamento de gás MQ-135 detectado.");
    }

    delay(16000);
  } else {
    Serial.println("Não conectado à internet. Tentando novamente em 5 segundos.");
    delay(5000);
  }
}
