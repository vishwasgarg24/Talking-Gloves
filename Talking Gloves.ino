/*
Code is written by Sachin Verma (vsachin094@gmail.com) Transmitter data pin to Arduino pin 12
*/

#include<SoftwareSerial.h>
SoftwareSerial gsm(5,6);
int timesTosend=1;
int count=0;
int sense0 = A0;
int sense1 = A1;
int sense2 = A2;
int sense3 = A3;
// Pulse Monitor Test Script
int sensorPin = A4;
double alpha = 0.75;
int period = 100;
double change = 0.0;
double minval = 0.0;




int button;
int value;  //temperature
char temp[5]; // temperature
char heart[5];

void setup()
{
  

analogReference(DEFAULT);
vw_setup(2000); // Bits per sec
Serial.begin(9600);
gsm.begin(9600);
gsm.println("AT+CMGF=1"); //set GSM to text mode
delay(1000);
}
void loop()
{
 static double oldValue = 0;
    static double oldChange = 0;
 
    int rawValue = analogRead (sensorPin);
    int value1 = (alpha * oldValue + (1 - alpha) * rawValue)/3.75;
 
   // Serial.println (value1);
    oldValue = value1;
    if(value1 > 90)
    {
  
    
          while(count<timesTosend){
          delay(1500);
          gsm.print("AT+CMGS=\"");
          gsm.print("8010xxxxx");
          gsm.println("\"");
          while (gsm.read()!='>');
          {
            gsm.print("Heart rate greater than 90");  //SMS body
            delay(500);
            gsm.write(0x1A);  // sends ctrl+z end of message
            gsm.write(0x0D);  // Carriage Return in Hex
            gsm.write(0x0A);  // Line feed in Hex

            //The 0D0A pair of characters is the signal for the end of a line and beginning of another.
            delay(5000);
          }
          count++;
          }
    }
      itoa(value1, heart, 10);
    
  vw_setup(2000);
  delay(2000);
     send("he");
    send(heart);
    delay(500);
     Serial.println(heart);
  int flex0 = analogRead(sense0);
   int flex1 = analogRead(sense1);
    int flex2 = analogRead(sense2);
     int flex3 = analogRead(sense3);
flex0 = map(flex0, 0, 1023, 0, 255);
flex1 = map(flex1, 0, 1023, 0, 255);
flex2 = map(flex2, 0, 1023, 0, 255);
flex3 = map(flex3, 0, 1023, 0, 255);
     Serial.print(flex0);
Serial.print(" ");
     Serial.print(flex1);
Serial.print(" ");
     Serial.print(flex2);
     Serial.print(" ");
     Serial.print(flex3);
     Serial.println(" ");
    if(flex0 > 210 && flex1 > 62  && flex2 > 225 && flex3 < 200)
      { 
           Serial.println("water");
           send("waters");
         
    
          while(count<timesTosend){
          delay(1500);
          gsm.print("AT+CMGS=\"");
          gsm.print("8010559599");
          gsm.println("\"");
          while (gsm.read()!='>');
          {
            gsm.print("water Requirement by patient");  //SMS body
            delay(500);
            gsm.write(0x1A);  // sends ctrl+z end of message
            gsm.write(0x0D);  // Carriage Return in Hex
            gsm.write(0x0A);  // Line feed in Hex

            //The 0D0A pair of characters is the signal for the end of a line and beginning of another.
            delay(5000);
          }
          count++;
          }
      }
     if(flex0 >220 && flex1 >70  && flex2 <235 && flex3 > 240)
      { 
           Serial.println("food");
            send("foodie");
             
          while(count<timesTosend){
            Serial.print("Sending msg");
          delay(1500);
          gsm.print("AT+CMGS=\"");
          gsm.print("8010xxxx");
          gsm.println("\"");
          while (gsm.read()!='>');
          {
            gsm.print("Food Requirement by patient");  //SMS body
            delay(500);
            gsm.write(0x1A);  // sends ctrl+z end of message
            gsm.write(0x0D);  // Carriage Return in Hex
            gsm.write(0x0A);  // Line feed in Hex

            //The 0D0A pair of characters is the signal for the end of a line and beginning of another.
            delay(5000);
          }
          count++;
          }
      } 
      if(flex0 > 230 && flex1 < 70  && flex2 >230 && flex3 > 240)
      { 
           Serial.println("medicine");
            send("medici");
               
          while(count<timesTosend){
          delay(1500);
          gsm.print("AT+CMGS=\"");
          gsm.print("9069046104");
          gsm.println("\"");
          while (gsm.read()!='>');
          {
            gsm.print("Medicine Requirement by patient");  //SMS body
            delay(500);
            gsm.write(0x1A);  // sends ctrl+z end of message
            gsm.write(0x0D);  // Carriage Return in Hex
            gsm.write(0x0A);  // Line feed in Hex

            //The 0D0A pair of characters is the signal for the end of a line and beginning of another.
            delay(5000);
          }
          count++;
          }
    
      } 
      if(flex0 < 220 && flex1 >62  && flex2 > 230 && flex3 > 210)
      { 
           Serial.println("wheelchair");
            send("zchair");
            
          while(count<timesTosend){
          delay(1500);
          gsm.print("AT+CMGS=\"");
          gsm.print("90690xxxxx");
          gsm.println("\"");
          while (gsm.read()!='>');
          {
            gsm.print("wheelchair Requirement by patient");  //SMS body
            delay(500);
            gsm.write(0x1A);  // sends ctrl+z end of message
            
            gsm.write(0x0D);  // Carriage Return in Hex
            gsm.write(0x0A);  // Line feed in Hex

            //The 0D0A pair of characters is the signal for the end of a line and beginning of another.
            delay(5000);
          }
          count++;
          }
      } 
      if(flex0 < 230 && flex1 < 65  && flex2 < 230 && flex3 >240)
      { 
           Serial.println("critical");
            send("critic");
             gsm.print("ATD + +918010559599;");
          delay(100);
          gsm.println();
          delay(30000);            // wait for 30 seconds...
        gsm.println("ATH");   // hang up
        gsm.begin(9600);
          while(count<timesTosend){
          delay(1000);
          gsm.print("AT+CMGS=\"");
         gsm.print("9069046104");
         gsm.println("\"");
          while (gsm.read()!='>');
          {
           gsm.print("Emergency Call");  //SMS body
            delay(1000);
           gsm.write(0x1A);  // sends ctrl+z end of message
           gsm.write(0x0D);  // Carriage Return in Hex
           gsm.write(0x0A);  // Line feed in Hex

            //The 0D0A pair of characters is the signal for the end of a line and beginning of another.
            delay(5000);
          }
          count++;
          }
      } 
      if(flex0 >222  && flex1 < 65  && flex2 <230  && flex3 >210 )
      { 
           Serial.println("light on");
            send("lighto");
      } 
      
     /* if(flex0 <222  && flex1 < 62  && flex2 >230  && flex3 >195 )//fan
      { 
           Serial.println("zan on");
            send("fano");
      } */
      if(flex0 >218  && flex1 >62  && flex2 > 215 && flex3 < 210)
      { 
           Serial.println("headache");
            send("ache");
           
          while(count<timesTosend){
          delay(1000);
          gsm.print("AT+CMGS=\"");
          gsm.print("9069046104");
          gsm.println("\"");
          while (gsm.read()!='>');
          {
            gsm.print("Headache");  //SMS body
            delay(1000);
            gsm.write(0x1A);  // sends ctrl+z end of message
            gsm.write(0x0D);  // Carriage Return in Hex
            gsm.write(0x0A);  // Line feed in Hex

            //The 0D0A pair of characters is the signal for the end of a line and beginning of another.
            delay(5000);
          }
          count++;
          }
      } 
     if(flex0 <220  && flex1 < 62   && flex2 <230 && flex3 < 220)
      { 
           Serial.println("chest pain");
            send("pain");  
            
          while(count<timesTosend){
          delay(1000);
          gsm.print("AT+CMGS=\"");
          gsm.print("9069046104");
          gsm.println("\"");
          while (gsm.read()!='>');
          {
            gsm.print("Chest pain");  //SMS body
            delay(1000);
            gsm.write(0x1A);  // sends ctrl+z end of message
            gsm.write(0x0D);  // Carriage Return in Hex
            gsm.write(0x0A);  // Line feed in Hex

            //The 0D0A pair of characters is the signal for the end of a line and beginning of another.
            delay(5000);
          }
          count++;
          }
  }
  
   
  
}
void send (char *message)
{
vw_send((uint8_t *)message, strlen(message));
vw_wait_tx(); // Wait until the whole message is gone


} 

