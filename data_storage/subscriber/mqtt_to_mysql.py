import json
import mysql.connector
import requests
from paho.mqtt import client as mqtt

# ---------- MySQL connection ----------
db = mysql.connector.connect(
    host="localhost",
    user="root",
    password="root",
    database="env_track_monitor"
)
cursor = db.cursor()

# ---------- ThingSpeak config ----------
THINGSPEAK_API_KEY = "LMDBP9G29OE5LJNX"
THINGSPEAK_URL = "https://api.thingspeak.com/update"

# ---------- MQTT callbacks ----------
def on_connect(client, userdata, flags, rc, properties=None):
    if rc == 0:
        print("Connected to MQTT broker ✔")
        client.subscribe("env/esp32/data")
    else:
        print("Failed to connect, return code:", rc)

def on_message(client, userdata, msg):
    try:
        payload = msg.payload.decode()
        print("Raw message:", payload)

        # Parse JSON
        data = json.loads(payload)
        temperature = data.get("temperature")
        humidity = data.get("humidity")
        gas = data.get("gas")

        # ---------- Insert into MySQL ----------
        sql = "INSERT INTO sensor_data (temperature, humidity, gas) VALUES (%s, %s, %s)"
        cursor.execute(sql, (temperature, humidity, gas))
        db.commit()
        print("Inserted into MySQL ✔")

        # ---------- Update ThingSpeak ----------
        params = {
            "api_key": THINGSPEAK_API_KEY,
            "field1": temperature,
            "field2": humidity,
            "field3": gas
        }
        response = requests.get(THINGSPEAK_URL, params=params)
        if response.status_code == 200:
            print("Updated ThingSpeak ✔")
        else:
            print("ThingSpeak update failed:", response.status_code, response.text)

    except json.JSONDecodeError:
        print("Invalid JSON received, skipping")
    except KeyError as e:
        print("Missing field:", e)
    except Exception as e:
        print("Error:", e)

# ---------- MQTT client ----------
client = mqtt.Client(mqtt.CallbackAPIVersion.VERSION2)
client.on_connect = on_connect
client.on_message = on_message

client.connect("test.mosquitto.org", 1883, 60)

print("Subscriber running...")
client.loop_forever()
