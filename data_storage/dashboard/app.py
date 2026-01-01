from flask import Flask, render_template
import mysql.connector

app = Flask(__name__)

# ---------- MySQL Connection ----------
db = mysql.connector.connect(
    host="localhost",
    user="root",
    password="root",
    database="env_track_monitor"
)
cursor = db.cursor(dictionary=True)

# ---------- Dashboard Route ----------
@app.route("/")
def index():
    # Fetch last 50 records
    cursor.execute("SELECT * FROM sensor_data ORDER BY id DESC LIMIT 50")
    rows = cursor.fetchall()

    # Latest row for cards
    latest = rows[0] if rows else {
        "temperature": "--",
        "humidity": "--",
        "gas": "--"
    }

    return render_template("index.html", rows=rows, latest=latest)

if __name__ == "__main__":
    app.run(debug=True)
