
#include <SoftwareSerial.h>

SoftwareSerial mySerial(10,11);

#define LEDPIN 13
#include <LiquidCrystal.h>
LiquidCrystal lcd(8,9,10,11,12,13);


char tag[] ="0900717D9693"; // Replace with your own Tag ID
char input[12];        // A variable to store the Tag ID being presented
int count = 0;        // A counter variable to navigate through the input[] character array
int taps=0;
boolean flag = 0;  // A variable to store the Tag match status

void setup()
{ mySerial.begin(9600);   // Setting the baud rate of GSM Module  
  Serial.begin(9600);    // Setting the baud rate of Serial Monitor (Arduino)
  delay(1000);
  lcd.begin(16, 2);
   Serial.begin(9600);   // Initialise Serial Communication with the Serial Monitor
  pinMode(LEDPIN,OUTPUT);
}
void loop()
{  
 
  if(Serial.available())// Check if there is incoming data in the RFID Reader Serial Buffer.
  {
    count = 0; // Reset the counter to zero
    /* Keep reading Byte by Byte from the Buffer till the RFID Reader Buffer is empty 
       or till 12 Bytes (the ID size of our Tag) is read */
    while(Serial.available() && count < 12) 
    {
      input[count] = Serial.read(); // Read 1 Byte of data and store it in the input[] variable
      count++; // increment counter
      delay(5);
    }
    /* When the counter reaches 12 (the size of the ID) we stop and compare each value 
        of the input[] to the corresponding stored value */
    if(count == 12) // 
    {
      count =0; // reset counter varibale to 0
      flag = 1;
      /* Iterate through each value and compare till either the 12 values are 
         all matching or till the first mistmatch occurs */
      while(count<12 && flag !=0)  
      {
        if(input[count]==tag[count])
        flag = 1; // everytime the values match, we set the flag variable to 1
        else
        flag= 0; 
                               /* if the ID values don't match, set flag variable to 0 and 
                                  stop comparing by exiting the while loop */
        count++; // increment i
      }
    }
    if(flag == 1) // If flag variable is 1, then it means the tags match
    { 
      
     taps++;
      digitalWrite(LEDPIN,HIGH);
     
 

       switch(taps)
 {case 1:  if (Serial.available()>0)
  
      mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+919718004545\"\r"); // Replace x with mobile number
  delay(1000);
 mySerial.println("Passed security check");// The SMS text you want to send
  delay(100);
          Serial.println("Passed security check");
          mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
  
 if (mySerial.available()>0)
   Serial.write(mySerial.read());

          break;
          
 case 2: if (Serial.available()>0)
  
      mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+919718004545\"\r"); // Replace x with mobile number
  delay(1000);  
 mySerial.println("Loaded on plane");// The SMS text you want to send
  delay(100);
        Serial.println("Loaded on plane");
        mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
  
 if (mySerial.available()>0)
   Serial.write(mySerial.read());

          break;
           
 case 3:  if (Serial.available()>0)
  
      mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+919718004545\"\r"); // Replace x with mobile number
  delay(1000); 
 mySerial.println("Deloaded");// The SMS text you want to send
  delay(100);
        Serial.println("Deloaded");
        mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
  
 if (mySerial.available()>0)
   Serial.write(mySerial.read());

          break;
          
 case 4: if (Serial.available()>0)
  
      mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+919718004545\"\r"); // Replace x with mobile number
  delay(1000); 
 mySerial.println("On the belt. Switch on your bluetooth.");// The SMS text you want to send
  delay(100);
        Serial.println("On the belt. Switch on your bluetooth.");
        mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
          break;
          
 if (mySerial.available()>0)
   Serial.write(mySerial.read());

 default: break; } 

      
      
    }
    else
    {
      Serial.println("Access Denied"); // Incorrect Tag Message
      digitalWrite(LEDPIN,LOW);
     
    }
 for(count=0;count<12;count++)
 { 
  input[count]='F';
 } 
 count =0;
 }


}


