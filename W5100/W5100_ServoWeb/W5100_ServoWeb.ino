/*
  Title:Web Server for arduino data
  Designer:gongwenbo
  Time:2016.1.22
 */
#include <SPI.h>
#include <Ethernet.h>

#include <ros.h>                                     //--------------ros define-------------//
#include <geometry_msgs/Twist.h>
#include <logitech/logitech.h>     
int logitech_axis=3;

ros::NodeHandle  nh;                
logitech::logitech x,call_a_msg;
// ros::Publisher chatter("motor_encoder_msg", &call_a_msg);    //--------------ros define-------------//

void servo_cb ( const logitech::logitech& msg)
{
  x.a=(msg.a + 0.5)*100;
  x.a = map(x.a, 0, 100, 0, 255); 
  logitech_axis=int(x.a);
  
}

ros::Subscriber<logitech::logitech> sub("logitech_msg", servo_cb);


// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = { 
  0x0C, 0x82, 0x68, 0xCE, 0xDB, 0xAA };
IPAddress ip(192,168,1,200);

// Initialize the Ethernet server library
// with the IP address and port you want to use 
// (port 80 is default for HTTP):
EthernetServer server(80);

void setup() 
{
 // Open serial communications and wait for port to open:
 /*
  Serial.begin(9600);
   while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  */
  nh.initNode();              //--------------ros define-------------//
  nh.subscribe(sub);      //--------------ros define-------------//
  
  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip);
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());
  
}


void loop() 
 {
   // listen for incoming clients
   //nh.spinOnce();
   EthernetClient client = server.available();
   if (client) {
     Serial.println("new client");
    // an http request ends with a blank line
     boolean currentLineIsBlank = true;
     while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
	  client.println("Refresh: 5");  // refresh the page automatically every 5 sec
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          // output the value of each analog input pin
          for (int analogChannel = 0; analogChannel < 6; analogChannel++) {
            int sensorReading = analogRead(analogChannel);
            client.print("analog input ");
            client.print(analogChannel);
            client.print(" is ");
            nh.spinOnce();
            
            client.print(logitech_axis);
            client.println("<br />");       
          }
          client.println("</html>");
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } 
        else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
    Serial.println("client disonnected");
  }
}

