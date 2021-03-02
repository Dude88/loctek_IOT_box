#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include "fauxmoESP.h"

fauxmoESP fauxmo;

#define DESK_1 "desk one"
#define DESK_2 "desk two"
#define DESK_3 "desk three"
#define DESK_4 "desk four"

byte SendData[9];
//memclr(SendData);
//byte SendData = null;
//byte *SendData;
String bin_nb = "100110110000010000010001011111001100001110011101"; //request - HEX: 9B 04 11 7C C3 9D
byte no_button[] = {0x9B, 0x06, 0x02, 0x00, 0x00, 0x6C, 0xA1, 0x9D};
byte button1[] = {0x9B, 0x06, 0x02, 0x04, 0x00, 0xAC, 0xA3, 0x9D};
byte button2[] = {0x9B, 0x06, 0x02, 0x08, 0x00, 0xAC, 0xA6, 0x9D};
byte button3[] = {0x9B, 0x06, 0x02, 0x10, 0x00, 0xAC, 0xAC, 0x9D};
byte button4[] = {0x9B, 0x06, 0x02, 0x00, 0x01, 0xAC, 0x60, 0x9D};
byte i1;
int button_count;

// Replace the next variables with your SSID/Password combination
const char* ssid = "AAAAAAAA";
const char* password = "BBBBBBBB";

// Add your MQTT Broker IP address, example:
//const char* mqtt_server = "192.168.1.144";
const char* mqtt_server = "XXX.XXX.XXX.XXX";
const char* mqtt_user = "YYYYYYYY";
const char* mqtt_password = "ZZZZZZZZ";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

const int DisplHigh = 4;

#define RXD2 16
#define TXD2 17
char c;
String a;
String readString;

void setup() {




  // Note the format for setting a serial port is as follows: Serial2.begin(baud-rate, protocol, RX pin, TX pin);
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
									
															
														  
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  pinMode(DisplHigh, OUTPUT);

  fauxmo.createServer(true); // not needed, this is the default value
  fauxmo.setPort(80); // This is required for gen3 devices
  fauxmo.enable(true);
  fauxmo.addDevice(DESK_1);
  fauxmo.addDevice(DESK_2);
  fauxmo.addDevice(DESK_3);
  fauxmo.addDevice(DESK_4);
  fauxmo.onSetState([](unsigned char device_id, const char * device_name, bool state, unsigned char value) {
    Serial.printf("[MAIN] Device #%d (%s) state: %s value: %d\n", device_id, device_name, state ? "ON" : "OFF", value);
    //return false;
    if ( (strcmp(device_name, DESK_1) == 0) ) {
      // this just sets a variable that the main loop() does something about
      Serial.println("RELAY 1 switched by Alexa");
      //digitalWrite(RELAY_PIN_1, !digitalRead(RELAY_PIN_1));
      if (state) {
        client.publish("desk/button", "1");
      } else {
      }
    }
    if ( (strcmp(device_name, DESK_2) == 0) ) {
      // this just sets a variable that the main loop() does something about
      Serial.println("RELAY 2 switched by Alexa");
      if (state) {
        client.publish("desk/button", "2");
      } else {
      }
    }
    if ( (strcmp(device_name, DESK_3) == 0) ) {
      // this just sets a variable that the main loop() does something about
      Serial.println("RELAY 2 switched by Alexa");
      if (state) {
        client.publish("desk/button", "3");
      } else {
      }
    }
    if ( (strcmp(device_name, DESK_4) == 0) ) {
      // this just sets a variable that the main loop() does something about
      Serial.println("RELAY 2 switched by Alexa");
      if (state) {
        client.publish("desk/button", "4");
      } else {
      }
    }
  }
  );

//fauxmo.onGetState([](unsigned char device_id, const char * device_name) {


  
}

void setup_wifi() {
  delay(10);
											 
					 
								   
						 

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
						
  }

					   
									 
								   
								   
}

void callback(char* topic, byte* message, unsigned int length) {
											   
						
								
  String messageTemp;

  for (int i = 0; i < length; i++) {
									 
    messageTemp += (char)message[i];
  }
  //Serial.println();

  // Feel free to add more if statements to control more GPIOs with MQTT

  // If a message is received on the topic esp32/output, you check if the message is either "on" or "off".
  // Changes the output state according to the message
  if (String(topic) == "desk/button") {
    //Serial.print("Changing output to ");
    if (messageTemp == "1") {
							
      button_count = 5;
      digitalWrite(DisplHigh, HIGH);
									   
									 
      for (i1 = 0; i1 < 8; i1++)
      {
        SendData[i1] = button1[i1];
      }

    }
    else if (messageTemp == "2") {
							
      for (i1 = 0; i1 < 8; i1++)
      {
        SendData[i1] = button2[i1];
      }
      button_count = 5;
      digitalWrite(DisplHigh, HIGH);
    }
    else if (messageTemp == "3") {
							
      for (i1 = 0; i1 < 8; i1++)
      {
        SendData[i1] = button3[i1];
      }
      button_count = 5;
      digitalWrite(DisplHigh, HIGH);
    }
    else if (messageTemp == "4") {
							
      for (i1 = 0; i1 < 8; i1++)
      {
        SendData[i1] = button4[i1];
      }
      button_count = 5;
      digitalWrite(DisplHigh, HIGH);
    }
  }
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {

						 
    if (client.connect("ESP8266Client", mqtt_user, mqtt_password)) {

				  
      client.subscribe("desk/button");
    } else {

									 
												  
									   
      delay(5000);
    }
  }
}

void loop() {
  fauxmo.handle();
						   
  if (!client.connected()) {
    reconnect();
  }

  client.loop();

  while (Serial2.available()) {
    c = Serial2.read();
    readString += c;
  }

  for (int i = 0; i < readString.length(); i++) {
    char Char1 = readString.charAt(i);
    for (int i = 7; i >= 0; i--) {
      byte bytes = bitRead(Char1, i);
      //Serial.print(bytes, BIN);
      a += (bytes);
    }
  }

  if (readString.length() > 0) {
						 
					  
						   
						  
								 
												

    if (a == bin_nb) {
									  
																				 
					  
						   
	
      Serial2.write(SendData, sizeof(SendData));
      button_count = button_count - 1;
									   
									 
					   
																			 

      if (button_count == 0) {
        fauxmo.setState(DESK_1, false, 0);
        fauxmo.setState(DESK_2, false, 0);
        fauxmo.setState(DESK_3, false, 0);
        fauxmo.setState(DESK_4, false, 0);
        for (i1 = 0; i1 < 9; i1++)
        {
          SendData[i1] = no_button[i1];
        }
								
        digitalWrite(DisplHigh, LOW);

 


      }
      client.publish("desk/command", "ok");
    } else {
									   
	 

    }
								 
								  
    readString = "";
    a = "";
  }

}
