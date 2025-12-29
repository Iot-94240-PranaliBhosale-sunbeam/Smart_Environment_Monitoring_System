# Day 4 – ESP32 HTTP Integration

## Work Done
- Debugged MQTT connection failures caused by mobile hotspot restrictions
- Identified port 1883 blocking issue
- Switched communication protocol from MQTT to HTTP
- Integrated ESP32 with ThingSpeak using HTTP REST API
- Successfully uploaded temperature, humidity, and gas data
- Verified real-time data visualization on ThingSpeak dashboard

## Screenshots
- Serial monitor output showing sensor readings and successful HTTP upload
- ThingSpeak dashboard displaying real-time temperature, humidity, and gas graphs

## Outcome
System is now stable and cloud-connected.
MQTT integration deferred to BeagleBone Black setup.
