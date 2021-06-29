#include <SCD30.h>
#include <rpcWiFi.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>
#include <TFT_eSPI.h>

#include "./setting.h"


WiFiClientSecure client;
TFT_eSPI tft;

void setup() {
  // SDC30の初期化
  Wire.begin();
  scd30.initialize();

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
  tft.drawString("CO2:",      40,  90);
  tft.drawString("Temp.:",    40, 115);
  tft.drawString("Humidity:", 40, 140);
  tft.drawRoundRect(15, 55, 320 - (15 * 2), 240 - (55 * 2), 15, TFT_WHITE);
}
 
void loop() {
  float result[3] = {0};

  if (scd30.isAvailable()) {
    // SDC30の値を読み込み、LCDの表示
    scd30.getCarbonDioxideConcentration(result);
    tft.fillRect(160, 90, 140, 80, TFT_DARKCYAN);
    tft.drawString(String(result[0], 0) + " ppm",   160,  90);
    tft.drawString(String(result[1], 1) + " deg C", 160, 115);
    tft.drawString(String(result[2], 1) + " %",     160, 140);
  }

  if(&client) {
    /*
     * サーバへ値を送信
     */
    HTTPClient http;
 
    http.begin(client, postUrl);
    http.addHeader("Content-type", "application/json");

    String body = String("{\"co2\": " + String(result[0]) + ", \"temperature\":  " + String(result[1], 1) +", \"humidity\": " + String(result[2], 1) + "}");
 
    int httpResponseCode = http.POST(body);
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
