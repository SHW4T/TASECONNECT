# TaseConnect: Smart Taser with Live Location Alerts

## Overview

TaseConnect is a safety-focused taser prototype that sends the live GPS location to emergency contacts via a Telegram bot whenever the taser is used or when emergency contacts request the location. This project combines IoT hardware (ESP32, GPS module, High volt generator and a switch) with cloud-based messaging for real-time emergency response.

---

## Features

- **Live Location Alerts:** Instantly sends the taser’s GPS coordinates to emergency contacts through Telegram when activated.
- **On-Demand Location:** Emergency contacts can request the current location at any time by sending `/Location` to the bot.
- **Secure Communication:** Only authorized users can interact with the bot and receive location updates.
- **Reliable Connectivity:** Uses WiFi and the UniversalTelegramBot library for seamless communication.

---

## How It Works

- When the taser’s switch is pressed, the ESP32 reads GPS data and sends a Google Maps link with the current location to the pre-set Telegram chat.
- Emergency contacts can also request the current location by sending `/Location` to the Telegram bot.
- The bot responds only to authorized users, ensuring privacy and security.

---

## Hardware Used

- ESP32 Development Board
- GPS Module (TinyGPS++)
- High Volt Generator
- Switch/Button
- WiFi Connectivity

---

## Software & Libraries

- [UniversalTelegramBot](https://github.com/witnessmenow/Universal-Arduino-Telegram-Bot)
- TinyGPS++
- ArduinoJson
- WiFiClientSecure

---

## Getting Started

1. **Clone this repository.**
2. **Update your WiFi credentials, Telegram Bot Token, and Chat ID in the code.**
3. **Upload the code to your ESP32 board.**
4. **Connect the GPS module and switch as specified in the code.**
5. **Start interacting with your Telegram bot!**

---

## Demo

Check out our [project demonstration video](https://www.linkedin.com/posts/shashwat-thakur-2b2618354_iot-safety-telegrambot-activity-7319761802865573888-FAFX?utm_source=share&utm_medium=member_desktop&rcm=ACoAAFheUKYBKwZZDEvvdUkR3gMmMJ6eP8me_zg) to see TaseConnect in action!

---

## Team Members

- SHASHWAT THAKUR (ME)
- NEIL SHIRKE
- VAISHNAVI VERMA
- VATSAL PARATE
- JAS SHROFF

---

## License

This project is for educational and demonstration purposes.

