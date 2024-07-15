#include <BLEDevice.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>
#include <TFT_eSPI.h>

TFT_eSPI tft;

BLEScan* pBLEScan;
BLEScanResults foundDevices;
BLEAdvertisedDevice device;
const int B_PIN = 17; // Blue LED pin
const int G_PIN = 16; // Green LED pin
const int R_PIN = 4;  // Red LED pin

void setup() {
    Serial.begin(115200);
    tft.init(); // Initialize TFT display
    tft.setRotation(1); // Adjust display rotation if needed

    tft.fillScreen(TFT_BLACK); // Clear screen
    tft.setTextColor(TFT_WHITE);
    tft.setTextSize(1);
    tft.setCursor(0, 0);
    tft.println("Scanning for airtags..."); // Display on TFT

    Serial.println("Scanning for airtags...");
    pinMode(B_PIN, OUTPUT);
    pinMode(G_PIN, OUTPUT);
    pinMode(R_PIN, OUTPUT);

    BLEDevice::init("");
    pBLEScan = BLEDevice::getScan();
    pBLEScan->setActiveScan(true); 
    pBLEScan->setInterval(100);
    pBLEScan->setWindow(99);  
}

void loop() {
    digitalWrite(B_PIN, HIGH);
    digitalWrite(G_PIN, HIGH); // Green LED on while scanning
    digitalWrite(R_PIN, LOW);

    foundDevices = pBLEScan->start(2, false);
    for (int i=0; i < foundDevices.getCount(); i++) {
        device = foundDevices.getDevice(i);
        const char* payload = device.getManufacturerData().data();
        if (payload[2] == 0x12) {
            Serial.print("Found an airtag: \n");
            Serial.printf("%s ", device.getAddress().toString().c_str());
            Serial.printf("%d\n", device.getRSSI());

            // Display on TFT
            tft.fillScreen(TFT_BLACK);
            tft.setCursor(0, 0);
            tft.setTextColor(TFT_WHITE);
            tft.setTextSize(1);
            tft.printf("Found an airtag:\n");
            tft.printf("%s\n", device.getAddress().toString().c_str());
            tft.printf("RSSI: %d\n", device.getRSSI());
            
            digitalWrite(R_PIN, HIGH);
            digitalWrite(G_PIN, LOW); 
            digitalWrite(B_PIN, HIGH); 
            delay(600);
            digitalWrite(R_PIN, HIGH);
            digitalWrite(B_PIN, HIGH); 
            digitalWrite(G_PIN, LOW); 
        }
    }
    pBLEScan->clearResults();   
    delay(2000);
}
