#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>
#include <TinyGPS++.h>
#include <HardwareSerial.h>

const char* ssid = ""; //wifi name
const char* password = ""; //wifi pass

// Initialize Bot Token
#define BOTtoken ""  // Replace with your Bot Token

// Chat ID from @myidbot
#define CHAT_ID ""  // Replace with your Chat ID

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

int botRequestDelay = 100;
unsigned long lastTimeBotRan;

// Initialize GPS
HardwareSerial GPSSerial(1);
TinyGPSPlus gps;

// Switch pin definition
const int switchPin = 27; // Change to your switch pin
bool lastSwitchState = HIGH; // Start with HIGH for pull-up resistor

void handleNewMessages(int numNewMessages) {
    Serial.println("handleNewMessages");
    for (int i = 0; i < numNewMessages; i++) {
        String chat_id = String(bot.messages[i].chat_id);
        if (chat_id != CHAT_ID) {
            bot.sendMessage(chat_id, "Unauthorized user", "");
            continue;
        }
        String text = bot.messages[i].text;
        Serial.println(text);

        while (GPSSerial.available()) {
            gps.encode(GPSSerial.read());
        }
        
        if (gps.charsProcessed() > 10) {
            float currentLat = gps.location.lat();
            float currentLng = gps.location.lng();

            if (text == "/start") {
                String control = "Heyy, " + bot.messages[i].from_name + ".\n";
                control += "Welcome To TASECONNECT BOT\n\n";
                control += "Use /Location To Get Real Time Location\n";
                bot.sendMessage(chat_id, control, "");
            }

            if (text == "/Location") {
                String lokasi = "Location : https://www.google.com/maps/@";
                lokasi += String(currentLat, 6);
                lokasi += ",";
                lokasi += String(currentLng, 6);
                lokasi += ",21z?entry=ttu";
                bot.sendMessage(chat_id, lokasi, "");
            }
        }
    }
}

void setup() {
    Serial.begin(115200);
    GPSSerial.begin(9600, SERIAL_8N1, 16, 17);
    
    // Setup switch pin
    pinMode(switchPin, INPUT_PULLUP); // Use internal pull-up resistor
    
    // Connect to WiFi
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    #ifdef ESP32
        client.setCACert(TELEGRAM_CERTIFICATE_ROOT);
    #endif
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi..");
    }
    
    // Print ESP32 Local IP Address
    Serial.println(WiFi.localIP());
}

void loop() {
    if (millis() > lastTimeBotRan + botRequestDelay) {
        int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

        while (numNewMessages) {
            Serial.println("got response");
            handleNewMessages(numNewMessages);
            numNewMessages = bot.getUpdates(bot.last_message_received + 1);
        }
        lastTimeBotRan = millis();
    }

    // Check switch state
    bool currentSwitchState = digitalRead(switchPin);
    
    // If switch is ON (LOW because of pull-up)
    if (currentSwitchState == LOW) {
        // Send GPS location on switch ON
        if (gps.charsProcessed() > 10) {
            float currentLat = gps.location.lat();
            float currentLng = gps.location.lng();
            String locationMessage = "Location : https://www.google.com/maps/@" + String(currentLat, 6) + "," + String(currentLng, 6) + ",21z?entry=ttu";
            bot.sendMessage(CHAT_ID, locationMessage, "");
            Serial.println("Location sent via Telegram.");
            
            // Wait for switch release before allowing another press
            while(digitalRead(switchPin) == LOW); // Wait until the switch is released
            delay(100); // Optional debounce delay
        } else {
            Serial.println("GPS data not available yet.");
        }
    }

    lastSwitchState = currentSwitchState; // Update switch state
}
