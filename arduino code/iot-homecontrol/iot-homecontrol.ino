#include <SoftwareSerial.h>
  
  #define DEBUG true
  
  SoftwareSerial esp8266(2,3);
  
  boolean alreadyConnected = false;
  
  
  void setup()
  {
  
    Serial.begin(9600);
    esp8266.begin(115200); // your esp's baud rate might be different
    
    pinMode(6,OUTPUT);
    digitalWrite(6,LOW);
    
    pinMode(12,OUTPUT);
    digitalWrite(12,HIGH);
   
    sendData("AT+RST\r\n",2000,DEBUG); // reset module
    sendData("AT+CWMODE=2\r\n",1000,DEBUG); // configure as access point
    sendData("AT+CIFSR\r\n",1000,DEBUG); // get ip address
    sendData("AT+CIPMUX=1\r\n",1000,DEBUG); // configure for multiple connections
    sendData("AT+CIPSERVER=1,80\r\n",1000,DEBUG); // turn on server on port 80
  
  }
  
  void loop()
  {
  
  
    String inString = "";  
    if(esp8266.available()) // check if the esp is sending a message 
    {
     if (!alreadyConnected) {
        // clear out the input buffer:
      esp8266.flush();
      Serial.println("We have a new client");
      esp8266.println("Hello, client!");
      alreadyConnected = true;
    }
  //Serial.println("IPD :"+IPD);//
    if(esp8266.find("+IPD,"))
    {
       delay(1); // wait for the serial buffer to fill up (read all the serial data)
      
      int pinNumber = 0;
      String tempS = "";
      esp8266.find("pin="); // advance cursor to "pin="
      char temp = esp8266.read();
      //Serial.println("temp value: " +temp);
      tempS = temp;
       
      pinNumber = tempS.toInt();
      Serial.println(pinNumber);
      digitalWrite(6, !digitalRead(6));
   
      digitalWrite(12,LOW);
   delay(100);
   digitalWrite(12,HIGH);
    delay(100);
     
  
     }
   }
   
  }
  
  
  /*
 
  */

  String sendData(String command, const int timeout, boolean debug)
  {
    String response = "";
  
      esp8266.print(command); // send the read character to the esp8266
      
      long int time = millis();
      
      while( (time+timeout) > millis())
      {
        while(esp8266.available())
        {
  
          // The esp has data so display its output to the serial window 
          char c = esp8266.read(); // read the next character.
          response+=c;
        }  
      }
      
      if(debug)
      {
        Serial.print(response);
      }
      
      return response;
    }
