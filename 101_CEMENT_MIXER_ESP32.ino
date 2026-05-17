#include <WiFi.h>
#include <ESP32Servo.h>

const char* ssid = "ESP32_Servo";
const char* password = "12345678";

WiFiServer server(80);

Servo myservo;
int servoPin = 22;

// LED pins
int greenLED = 26;  // Moving
int redLED = 25;    // Stopped

bool sweeping = false;        // Start sweeping immediately
int stepSize = 3;            // Step size in degrees (+/- speed control)
int pos = 0;                 // Current position
int direction = 1;           // 1 = forward, -1 = backward
unsigned long lastMove = 0;
int moveInterval = 15;       // ms between steps (constant speed timing)

// HTML page template
String htmlPageTemplate = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
<title>Cement Mixer</title>
<style>
  body { font-family: Arial; text-align: center; margin-top: 50px; background-color: #ADD8E6; }
  h1 { font-size: 40px; color: #333; }
  button { font-size: 20px; padding: 10px 20px; margin: 5px; }
  p { font-size: 18px; }
</style>
<script>
function sendCommand(cmd) {
  fetch('/' + cmd).then(response => response.text()).then(data => {
    document.getElementById('speedValue').innerText = data;
  });
}
</script>
</head>
<body>
  <h1>Cement Mixer</h1>
  <button onclick="sendCommand('start')">Start Sweep</button>
  <button onclick="sendCommand('stop')">Stop Sweep</button>
  <br><br>
  <button onclick="sendCommand('faster')">Increase Speed</button>
  <button onclick="sendCommand('slower')">Decrease Speed</button>
  <p>Current Speed: <span id="speedValue">%SPEED%</span></p>
</body>
</html>
)rawliteral";

void setup() {
  Serial.begin(115200);
  
  myservo.attach(servoPin);
  
  pinMode(greenLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  
  updateLEDs(); // Set initial LED state
  
  WiFi.softAP(ssid, password);
  Serial.println("WiFi AP started");
  Serial.print("IP address: ");
  Serial.println(WiFi.softAPIP());

  server.begin();
}

void loop() {
  handleClient();

  if (sweeping) {
    unsigned long now = millis();
    if (now - lastMove >= moveInterval) {
      lastMove = now;
      pos += stepSize * direction;
      myservo.write(pos);

      if (pos >= 130) {
        pos = 130;
        direction = -1;
      } 
      else if (pos <= 50) {
        pos = 50;
        direction = 1;
      }
    }
  }
}

void handleClient() {
  WiFiClient client = server.available();
  if (!client) return;

  String request = client.readStringUntil('\r');
  client.flush();

  if (request.indexOf("GET / ") >= 0) {
    sendPage(client);
  }
  else if (request.indexOf("GET /start") >= 0) {
    sweeping = true;
    updateLEDs();
    sendText(client, formatSpeed(stepSize));
  }
  else if (request.indexOf("GET /stop") >= 0) {
    sweeping = false;
    updateLEDs();
    sendText(client, formatSpeed(stepSize));
  }
  else if (request.indexOf("GET /faster") >= 0) {
    stepSize = min(8, stepSize + 1);
    sendText(client, formatSpeed(stepSize));
  }
  else if (request.indexOf("GET /slower") >= 0) {
    stepSize = max(1, stepSize - 1);
    sendText(client, formatSpeed(stepSize));
  }
}

void sendPage(WiFiClient &client) {
  String page = htmlPageTemplate;
  page.replace("%SPEED%", formatSpeed(stepSize));
  client.println("HTTP/1.1 200 OK");
  client.println("Content-type:text/html");
  client.println();
  client.println(page);
}

void sendText(WiFiClient &client, String text) {
  client.println("HTTP/1.1 200 OK");
  client.println("Content-type:text/plain");
  client.println();
  client.println(text);
}

String formatSpeed(int speed) {
  return (speed > 0 ? "+" : "") + String(speed);
}

void updateLEDs() {
  if (sweeping) {
    digitalWrite(greenLED, HIGH);
    digitalWrite(redLED, LOW);
  } else {
    digitalWrite(greenLED, LOW);
    digitalWrite(redLED, HIGH);
  }
}

