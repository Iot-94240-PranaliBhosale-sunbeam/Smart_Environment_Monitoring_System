CREATE DATABASE env_track_monitor;

USE env_track_monitor;

CREATE TABLE sensor_data (
    id INT AUTO_INCREMENT PRIMARY KEY,
    temperature FLOAT,
    humidity FLOAT,
    gas INT,
    timestamp DATETIME DEFAULT CURRENT_TIMESTAMP
);

