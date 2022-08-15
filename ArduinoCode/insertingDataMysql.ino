#include <LCD_I2C.h>
#include <DHT.h>

#define DHTPIN 4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

LCD_I2C lcd(0x27);
String datos = "";
byte humi_act = 0;
byte humi_ant = 0;
byte temp_act = 0;
byte temp_ant = 0;
unsigned long tiempo_act = 0;
unsigned long tiempo_ant = 0;
unsigned int periodo = 1000;

void setup() {
    Serial.begin(9600);
    dht.begin();
    lcd.begin();
    lcd.backlight();
}

void loop() {
    tiempo_act = millis(); 
    humi_act = dht.readHumidity();
    temp_act = dht.readTemperature();

    if (isnan(humi_act) || isnan(temp_act)) {
        Serial.println(F("Failed to read from DHT sensor!"));
        return;
    }
    if ((humi_act != humi_ant || temp_act != temp_ant) && (tiempo_act - tiempo_ant > periodo)) {
        datos = String(humi_act) + "!" + String(temp_act);
        lcd.setCursor(0,0);
        lcd.print("Humi: "+String(humi_act)+ "%");
        lcd.setCursor(0,1);
        lcd.print("Temp: "+String(temp_act)+ "C");
        Serial.println(datos);
        humi_ant = humi_act;
        temp_ant = temp_act;
        tiempo_ant = tiempo_act;
        datos = "";
    }
}
