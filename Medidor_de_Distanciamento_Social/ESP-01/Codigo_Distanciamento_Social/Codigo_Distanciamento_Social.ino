//Projeto feito para detectar se as pessoas estao muito proximas umas das outras nesse momento de pandemia do COVID-19
//Feito para ESP-01
//Feito por: André Oliveira Cunha
//3° Periodo de Engenharia de Computacao - UFES

//Biblioteca do ESP8266
#include "ESP8266WiFi.h" 

// Pinos do ESP-01
#define apito 3 // GPIO2
#define led 2 // TXD

// Variáveis globais
int estado = 0;
int canal = 8;

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  // Define os pinos do ESP-01 como saída
  pinMode(led, OUTPUT);
  pinMode(apito, OUTPUT);

//Inicializa o esp8266 como access point em um canal específico
  boolean result = WiFi.softAP("PET-ENGCOMP", "12345678", canal);
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

  // WiFi.scanNetworks retorna o numero de redes wifi encontradas em um canal específico
  int n = WiFi.scanNetworks(false, true, canal);
  
  if (n == 0) {
    Serial.println("Nenhum wifi encontrado");
  } else {
    Serial.print(n);
    Serial.println(" redes encontradas");
    for (int i = 0; i < n; ++i) {
      //verifica se a rede tem o nome "PET-ENGCOMP"
      if(WiFi.SSID(i) == "PET-ENGCOMP"){
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
  // Chama a função para emitir um alerta ou não
  alertaDeProximidade(estado);
}

// Função para emitir um alerta sonoro e visual
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
