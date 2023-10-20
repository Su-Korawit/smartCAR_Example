#include <Arduino.h>
#include <Servo.h>
#include <L298N.h>

Servo myServo1 ,  myServo2, myServo3, myServo4;

// Pin definition
const unsigned int IN1 = D0;
const unsigned int IN2 = D1;
const unsigned int IN3 = D7;
const unsigned int IN4 = D5;
const unsigned int EN1 = D8;
const unsigned int EN2 = D4;

// Create one motor instance
L298N motor1(EN1, IN1, IN2);
L298N motor2(EN2, IN3, IN4);

/*************************************************************

  This is a simple demo of sending and receiving some data.
  Be sure to check out other examples!
 *************************************************************/

/* Fill-in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID "TMPL6yU9L534S"
#define BLYNK_TEMPLATE_NAME "Quickstart Template"
#define BLYNK_AUTH_TOKEN "b0AKbYs8bEX8lQfHYEBKA7p95vNqSXA6"

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "AonSAI";
char pass[] = "Aon123456";

BlynkTimer timer;

// This function is called every time the Virtual Pin 0 state changes
BLYNK_WRITE(V0)
{
  // Set incoming value from pin V0 to a variable
  int value = param.asInt();

  Blynk.virtualWrite(V1, value);
}

// Smart Arm

BLYNK_WRITE(V4)
{
  int value = param.asInt();

  myServo1.write(value);  

  if (value == 90) {
    motor1.stop();
    motor2.stop();
    Serial.println("OFF");
  }
  else if (value == 180) {
    motor1.forward();
    motor2.forward();
    Serial.println("ON");
  }
  
}

BLYNK_WRITE(V5)
{
  int value = param.asInt();

  myServo2.write(value);

  if (value == 0) {
    motor2.stop();
    Serial.println("OFF");
  }
  else if (value == 120) {
    motor2.forward();
    Serial.println("ON");
  }
}
BLYNK_WRITE(V6)
{
  int value = param.asInt();

  myServo3.write(value);

  if (value == 0) {
    motor1.stop();
    motor2.stop();
    Serial.println("OFF");
  }
  else if (value == 180) {
    motor1.forward();
    motor2.forward();
    Serial.println("ON");
  }
}
BLYNK_WRITE(V7)
{
  int value = param.asInt();

  myServo4.write(value);

  if (value == 0) {
    motor1.stop();
    motor2.stop();
    Serial.println("OFF");
  }
  else if (value == 180) {
    motor1.backward();
    motor2.backward();
    Serial.println("ON");
  }
}

// This function is called every time the device is connected to the Blynk.Cloud
BLYNK_CONNECTED()
{
  // Change Web Link Button message to "Congratulations!"
  Blynk.setProperty(V3, "offImageUrl", "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations.png");
  Blynk.setProperty(V3, "onImageUrl",  "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations_pressed.png");
  Blynk.setProperty(V3, "url", "https://docs.blynk.io/en/getting-started/what-do-i-need-to-blynk/how-quickstart-device-was-made");
}

// This function sends Arduino's uptime every second to Virtual Pin 2.
void myTimerEvent()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V2, millis() / 1000);
}

void setup()
{
  // Debug console
  Serial.begin(115200);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  while (!Serial)
  {
    //do nothing
  }
  motor1.setSpeed(255);
  motor2.setSpeed(255);

  // You can also specify server:
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, IPAddress(192,168,1,100), 8080);

  //Attach myServo
  myServo1.attach(D2);
  myServo2.attach(D3);
  // myServo3.attach(D4);
  myServo4.attach(D6);
  // Setup a function to be called every second
  timer.setInterval(1000L, myTimerEvent);
}

void loop()
{
  Blynk.run();
  timer.run();
  // You can inject your own code or combine it with other sketches.
  // Check other examples on how to communicate with Blynk. Remember
  // to avoid delay() function!
}
