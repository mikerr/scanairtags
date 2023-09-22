
#include <BLEDevice.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>

BLEScan* pBLEScan;

void setup() {
  Serial.begin(115200);
  Serial.println("Scanning for airtags...");
  pinMode(LED_BUILTIN, OUTPUT);

  BLEDevice::init("");
  pBLEScan = BLEDevice::getScan();
  pBLEScan->setActiveScan(true); 
  pBLEScan->setInterval(100);
  pBLEScan->setWindow(99);  
}

void loop() {
  BLEScanResults foundDevices;
  BLEAdvertisedDevice device;
  const char *payload;

  digitalWrite(LED_BUILTIN, LOW);
  foundDevices = pBLEScan->start(2, false);
  for (int i=0; i < foundDevices.getCount(); i++) {
    device = foundDevices.getDevice(i);
    payload = device.getManufacturerData().data();
    if (payload[2] == 0x12) {
      Serial.print("Found an airtag: \n");
      Serial.printf("%s ",device.getAddress().toString().c_str());
      Serial.printf("%d\n",device.getRSSI());
      digitalWrite(LED_BUILTIN, HIGH);
    }
  }
  pBLEScan->clearResults();   
  delay(1000);
}
