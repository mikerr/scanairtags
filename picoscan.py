import bluetooth
import binascii
import time

# scan bluetooth devices nearby and only show airtags

_ADV_TYPE_NAME = const(0x08)
_IRQ_SCAN_RESULT = const(5)

devices = {}

def bt_irq(event, data):
    if event == _IRQ_SCAN_RESULT:        
        addr_type, addr, connectable, rssi, adv_data = data
        address = binascii.hexlify(addr).decode()

        i = 0
        result = []
        while i + 1 < len(adv_data):
                result.append(adv_data[i + 2 : i + adv_data[i] + 1])
                i += 1 + adv_data[i]
        if (i > 0) :
            payload = binascii.hexlify(result[0]).decode()
            if (payload[4:6] == "12"):
                    devices[address] = rssi
    

ble = bluetooth.BLE() 
ble.active('active')
ble.irq(bt_irq)

print ("scanning for airtags...")
while True:
    ble.gap_scan(5000,1000,1000)
    time.sleep(1)
    if (devices):
        print ("found %d airtags" % len(devices))
        print (devices)
