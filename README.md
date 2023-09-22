# scanAirtags
Use pi pico W to find nearby airtags

Apple airtags transmit a BLE advert every 2 seconds:

| Byte #	| Value	| Description
| ------- | ----- | ----------
|0	|0x1E	|Advertising data length: 31 (the maximum allowed)
|1	|0xFF	|Advertising data type: Manufacturer Specific Data
|2-3	|0x004C	|Apple’s company identifier
|4	|0x12	|Apple payload type to indicate a FindMy network broadcast



picoscan.py - picoW script sample output

```
found 4 airtags
{'fbbfbfc692ba': -92, 'f72e497db30c': -101, 'cb216b92d158': -99, 'd9184057f394': -23}
```
