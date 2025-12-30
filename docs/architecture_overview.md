## System Architecture Overview

The IoT-based Environmental Monitoring System follows a layered architecture:

Sensors (DHT11, MQ2) collect environmental data and send it to the ESP32.
The ESP32 processes sensor data and forwards it to the cloud platform.

In the current implementation, ThingSpeak is used for cloud-based data visualization.
The architecture is designed to support future integration of MQTT brokers and
gateway devices such as BeagleBone Black.

This modular design allows easy expansion with additional sensors and services.
