#include <rpcWiFi.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>
#include <TFT_eSPI.h>

#include "./setting.h"


WiFiClientSecure client;
TFT_eSPI tft;

void setup() {
  // 光センサのセットアップ
  pinMode(WIO_LIGHT, INPUT);  

  // シリアル出力の設定
  Serial.begin(115200);

  /*
   * WiFiのセットアップ
   */
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting..");
  }
  Serial.print("Connected to the WiFi network with IP: ");
  Serial.println(WiFi.localIP());
  client.setCACert(rootCa);

  /*
   * LCDディスプレイの固定表示部分のセットアップ
   */
  tft.begin();
  tft.setRotation(3);
 
  tft.fillScreen(TFT_DARKCYAN);

  tft.setTextColor(TFT_WHITE);
  tft.setTextSize(2);
  tft.drawString("Light value:", 70, 115);
  tft.drawRoundRect(15, 75, 320 - (15 * 2), 240 - (75 * 2), 15, TFT_WHITE);
}
 
void loop() {
  // 光センサの値の読み込み
  String lightValue = String(analogRead(WIO_LIGHT));

  // 光センサの値をLDCに表示
  tft.fillRect(220, 115, 50, 18, TFT_DARKCYAN);
  tft.drawString(lightValue, 220, 115);

  if(&client) {
    /*
     * サーバへ値を送信
     */
    HTTPClient http;
 
    http.begin(client, postUrl);
    http.addHeader("Content-type", "application/json");
 
    int httpResponseCode = http.POST(lightValue);
    if (httpResponseCode > 0){
      Serial.print("HTTP Response Code: ");
    } else {
      Serial.print("Error on sending request: ");
    }
    Serial.println(httpResponseCode);
 
    http.end();  //Free resources
  } else {
    Serial.println("Unable to create client");
  }
  
  Serial.println();
  Serial.println("Waiting 1s before the next round...");
  delay(1000);
}
