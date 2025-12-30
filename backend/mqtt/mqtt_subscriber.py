import json
import paho.mqtt.client as mqtt

BROKER = "test.mosquitto.org"
TOPIC = "env/esp32/data"

def on_connect(client, userdata, flags, rc):
    if rc == 0:
        print("Connected to MQTT Broker")
        client.subscribe(TOPIC)
        print(f"Subscribed to topic: {TOPIC}")
    else:
        print("Connection failed with code", rc)

def on_message(client, userdata, msg):
    try:
        payload = msg.payload.decode()
        data = json.loads(payload)
        print("Received Data:")
        print(data)
    except json.JSONDecodeError:
        print("Received NON-JSON payload:", msg.payload.decode())

client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message

client.connect(BROKER, 1883, 60)
print("MQTT Subscriber running...")
client.loop_forever()
