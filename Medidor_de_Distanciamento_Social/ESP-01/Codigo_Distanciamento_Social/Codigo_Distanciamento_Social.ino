//Projeto feito para detectar se as pessoas estao muito proximas umas das outras nesse momento de pandemia do COVID-19
//Feito para ESP-01
//Feito por: André Oliveira Cunha
//3° Periodo de Engenharia de Computacao - UFES


#include "ESP8266WiFi.h"
#define apito 3
#define led 2

int estado = 0;

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  pinMode(led, OUTPUT);
  pinMode(apito, OUTPUT);

//inicializa o esp8266 como access point no canal 8
  boolean result = WiFi.softAP("COVID19", "12345678", 8);
  if(result == true){
    Serial.println("Tudo pronto!");
  }
  else{
    Serial.println("Falhou!");
    while(1){
      digitalWrite(led, HIGH);
      delay(300);
      digitalWrite(led, LOW);
      delay(300);
    }
  }

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

  digitalWrite(led, HIGH);
  digitalWrite(apito, LOW);
  delay(2000);
  digitalWrite(led, LOW);
}

void loop() {
  estado = 0;
  delay(250);

  // WiFi.scanNetworks retorna o numero de redes wifi encontradas no canal 8
  int n = WiFi.scanNetworks(false, true, 8);
  
  if (n == 0) {
    Serial.println("Nenhum wifi encontrado");
  } else {
    Serial.print(n);
    Serial.println(" redes encontradas");
    for (int i = 0; i < n; ++i) {
      //verifica se a rede tem o nome "COVID19"
      if(WiFi.SSID(i) == "COVID19"){
        Serial.print(i + 1);
        Serial.print(") ");
        Serial.print(WiFi.SSID(i));// SSID
        Serial.print(WiFi.RSSI(i));//Potencia do sinal em dBm  
        Serial.println("dBm");

        if(WiFi.RSSI(i) >= -50){
          estado = 1;
        }
      }
    }
    Serial.println("");
  }
  alertaDeProximidade(estado);
}

void alertaDeProximidade(int estado){
  if(estado == 1){
      digitalWrite(led, HIGH);
      digitalWrite(apito, HIGH);
      delay(20);
    }
    else{
      digitalWrite(led, LOW);
      digitalWrite(apito, LOW);
    }
}
