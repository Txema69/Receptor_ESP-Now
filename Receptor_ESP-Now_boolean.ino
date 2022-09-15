#include <ESP8266WiFi.h>
#include <espnow.h>
bool activaRele1=false;


typedef struct struct_message { // Structure example to receive data
    bool Rele1;
    bool Rele2;
} struct_message;
struct_message myData;// Create a struct_message called myData

// ---------Callback function that will be executed when data is received------------
void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.print("Bytes received: ");
  Serial.println(len);
  Serial.print("Rele1: ");
  Serial.println(myData.Rele1);
  Serial.print("Rele2: ");
  Serial.println(myData.Rele2);
  Serial.println();
  if (myData.Rele1) activaRele1=true; else activaRele1=false;
}
void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);
  Serial.print("ESP8266 Board MAC Address:  ");
  Serial.println(WiFi.macAddress());
  pinMode(2, OUTPUT); // Led Integrado en placa.
  pinMode(12, OUTPUT); // D6.
  //pinMode(13, OUTPUT); // D7.
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);
  // Init ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;}
  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  esp_now_register_recv_cb(OnDataRecv);}

void loop() {
    if (activaRele1){
    Serial.println("TRUE RECIBIDO");
    digitalWrite(2, LOW); // Led Placa
    //digitalWrite(13,LOW); //D7
    digitalWrite(12,LOW); //D6
    delay(1000);
    digitalWrite(2, HIGH); // Led Placa
    //digitalWrite(13,HIGH); //D7
    digitalWrite(12,HIGH); //D6
    activaRele1=false;}
    
   else{
    Serial.println("FALSE RECIBIDO");
    digitalWrite(2, HIGH); // Led Placa
    //digitalWrite(13,HIGH); //D7
    digitalWrite(12,HIGH);} //D6  
}
