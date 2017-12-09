// This example shows how to connect to Cayenne using an ESP8266 and send/receive sample data.
// Make sure you install the ESP8266 Board Package via the Arduino IDE Board Manager and select the correct ESP8266 board before compiling. 
// small changes by Nicu FLORICA aka niq_ro, 27.11.2017, Craiova - Romania
// see http://nicuflorica.blogspot.ro/search?q=nodemcu

// note GPIO5 is D1 at NodeMCU - http://www.14core.com/wp-content/uploads/2015/06/Node-MCU-Pin-Out-Diagram1.png


#define ledexterior 15 // external led is as D3

//#define CAYENNE_DEBUG
#define CAYENNE_PRINT Serial
#include <CayenneMQTTESP8266.h>

// WiFi network info.
char ssid[] = "your-ssid";
char wifiPassword[] = "your-password";

// Cayenne authentication info. This should be obtained from the Cayenne Dashboard.
char username[] = "username";
char password[] = "password";
char clientID[] = "clientID";

unsigned long lastMillis = 0;


void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println("NodeMCU 0.9 - Cayenne IoT");
 

  delay(300);
  
  pinMode(ledexterior, OUTPUT);
  digitalWrite(ledexterior, LOW);   // Turn the LED off 
  
  
  Cayenne.begin(username, password, clientID, ssid, wifiPassword);
}

void loop() {
  Cayenne.loop();


 
  }



//Default function for processing actuator commands from the Cayenne Dashboard.
//You can also use functions for specific channels, e.g CAYENNE_IN(1) for channel 1 commands.
CAYENNE_IN_DEFAULT()
{
  CAYENNE_LOG("CAYENNE_IN_DEFAULT(%u) - %s, %s", request.channel, getValue.getId(), getValue.asString());
  //Process message here. If there is an error set an error message using getValue.setError(), e.g getValue.setError("Error message");
}

CAYENNE_IN(0)  // button
  {   
    int currentValue=getValue.asInt();
     if(currentValue==1)
     {
      digitalWrite(ledexterior,HIGH);
      }
      else
      {
      digitalWrite(ledexterior,LOW); 
      }
  }
/*   CAYENNE_IN(1)  // button 2
  {   
    int currentValue=getValue.asInt();
     if(currentValue==1)
     {
      digitalWrite(ledexterior,HIGH);
      }
      else
      {
      digitalWrite(ledexterior,LOW); 
      }
  }
  */
