
//Created by Matthew Agostinelli 5/24/2019 This is my first attempt at firmware on a smaller LED light source
#include <EEPROM.h>
String command;

void setup() {
  pinMode(3,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  Serial.begin(9600);
  
}
void loop() {
  if(Serial.available()){
  char c = Serial.read();
  if(c=='\n')
  {
    parseCommand(command);
    command = "";
  }
  else
  {
    command +=c;
  }
  }
}
//parsing the command coming in from the serial port, making up firmware commands for the arduino
void parseCommand(String com)
{
  //command
  String part1;
  //channel
  String part2;
  //power level
  String part3;

  part1 = com.substring(0,com.indexOf(" "));
  part2 = com.substring(com.indexOf(" ")+ 1,6);
  int part2int = part2.toInt();
  if(part2int<10)
  {
  part3 = com.substring(com.indexOf(" ")+ 2); 
  }
  else
  {
  part3 = com.substring(com.indexOf(" ")+ 3); 
  }
  
  if(part1.equalsIgnoreCase("scp"))
  {
    int pin = part2.toInt();
    double power = part3.toInt()*2.55;
    double per = part3.toInt();
    analogWrite(pin,power);
    if(per <=100)
    {
    //String perpow = String(per);
    //String output = "Channnel " + part2 + " at Power Level " + perpow + "%";
    //Serial.println(output);
    Serial.println("OK");
    
    if(pin==3)
    {
      EEPROM.update(12,pin);
      EEPROM.update(13,per);
    }
    else if(pin==5)
    {
      EEPROM.update(14,pin);
      EEPROM.update(15,per);
      
    }
    else if(pin==6)
    {
      EEPROM.update(16,pin);
      EEPROM.update(17,per);
    }
    else if(pin==9)
    {
      EEPROM.update(18,pin);
      EEPROM.update(19,per);
    }
    else if(pin==10)
    {
      EEPROM.update(20,pin);
      EEPROM.update(21,per);
    }
    //else if(pin==11)
    //{
      //EEPROM.update(22,pin);
     // EEPROM.update(23,per);
    //}
    //add other channels to this list if I need to hook up a mega board.
    else if (pin == 0)
    {

    analogWrite(3,power);
    analogWrite(5,power);
    analogWrite(6,power);
    analogWrite(9,power);
    analogWrite(10,power);
    EEPROM.update(13,per);
    EEPROM.update(15,per);
    EEPROM.update(17,per);
    EEPROM.update(19,per);
    EEPROM.update(21,per); 
    }
    }
      
  else
    {
      analogWrite(3,0);
      analogWrite(5,0);
      analogWrite(6,0);
      analogWrite(9,0);
      analogWrite(10,0);
      Serial.println("Exceeded Power Level!");
      EEPROM.update(13,0);
      EEPROM.update(15,0);
      EEPROM.update(17,0);
      EEPROM.update(19,0);
      EEPROM.update(21,0);
      //EEPROM.update(23,0);

    }  
  }
  else if(part1.equalsIgnoreCase("ver"))
  {
    Serial.println("0.02");
  }
  else if(part1.equalsIgnoreCase(""))
  {
    Serial.println("OK");
  }
  else if(part1.equalsIgnoreCase("typ"))
  {
    Serial.println("Visible");
  }
  else if(part1.equalsIgnoreCase("chg"))
  {
    int pin = part2.toInt();
    int wl = part3.toInt();
    byte wlHigh = highByte(wl);
    byte wlLow = lowByte(wl);

    if(pin == 3)
    {
      int pin3wl = pin;
      int wl3 = wl;
      String outwl = "Channnel " + part2 + " is now " + part3 + "nm";
      Serial.println(outwl);
      EEPROM.update(0,(wlHigh));
      EEPROM.write(1,(wlLow));    
    }
    else if(pin == 5)
    {
      int pin5wl = pin;
      int wl5 = wl;
      String outwl = "Channnel " + part2 + " is now " + part3 + "nm";
      Serial.println(outwl);
      EEPROM.update(2,(wlHigh));
      EEPROM.update(3,(wlLow)); 
    }
     else if(pin == 6)
    {
      int pin5wl = pin;
      int wl6 = wl;
      String outwl = "Channnel " + part2 + " is now " + part3 + "nm";
      Serial.println(outwl);
      EEPROM.update(4,(wlHigh));
      EEPROM.update(5,(wlLow)); 
    }
     else if(pin == 9)
    {
      int pin5wl = pin;
      int wl9 = wl;
      String outwl = "Channnel " + part2 + " is now " + part3 + "nm";
      Serial.println(outwl);
      EEPROM.update(6,(wlHigh));
      EEPROM.update(7,(wlLow)); 
    }
     else if(pin == 10)
    {
      int pin5wl = pin;
      int wl10 = wl;
      String outwl = "Channnel " + part2 + " is now " + part3 + "nm";
      Serial.println(outwl);
      EEPROM.update(8,(wlHigh));
      EEPROM.update(9,(wlLow)); 
    }
     //else if(pin == 11)
    //{
      //int pin11wl = pin;
      //int wl11 = wl;
      //String outwl = "Channnel " + part2 + " is now " + part3 + "nm";
      //Serial.println(outwl);
      //EEPROM.update(10,(wlHigh));
      //EEPROM.update(11,(wlLow)); 
    //}
    else
    {
      Serial.println("You have entered a Channel that does not exist");
    }

  }
  else if(part1.equalsIgnoreCase("chc"))
  {
    
    int pin = part2.toInt();

    if(pin == 3)
    {
      word wl = word(EEPROM.read(0),EEPROM.read(1));
      String wlp = String(wl);
      Serial.println(wlp);
    }
    else if(pin == 5)
    {
      word wl = word(EEPROM.read(2),EEPROM.read(3));
      String wlp = String(wl);
      Serial.println(wlp);
    }
    else if(pin == 6)
    {
      word wl = word(EEPROM.read(4),EEPROM.read(5));
      String wlp = String(wl);
      Serial.println(wlp);
    }
    else if(pin == 9)
    {
      word wl = word(EEPROM.read(6),EEPROM.read(7));
      String wlp = String(wl);
      Serial.println(wlp);
    }
    else if(pin == 10)
    {
      word wl = word(EEPROM.read(8),EEPROM.read(9));
      String wlp = String(wl);
      Serial.println(wlp);
    }
    //else if(pin == 11)
    //{
      //word wl = word(EEPROM.read(10),EEPROM.read(11));
      //String wlp = String(wl);
      //Serial.println(wlp);
    //}
    else
    {
     Serial.println("You have entered a Channel that does not exist");
    }
    }
    else if(part1.equalsIgnoreCase("ccl"))
    {
      
      String ch3 = String(EEPROM.read(12));
      word wl3 = word(EEPROM.read(0),EEPROM.read(1));
      String wlp3 = String(wl);
      Serial.println(ch3+" "+wlp3);    
      
      String ch5 = String(EEPROM.read(14));
      word wl5 = word(EEPROM.read(2),EEPROM.read(3));
      String wlp5 = String(wl5);
      Serial.println(ch5+" "+wlp5);
    
      String ch6 = String(EEPROM.read(16));
      word wl6 = word(EEPROM.read(4),EEPROM.read(5));
      String wlp6 = String(wl6);
      Serial.println(ch6+" "+wlp6);
      
      String ch9 = String(EEPROM.read(18));
      word wl9 = word(EEPROM.read(6),EEPROM.read(7));
      String wlp9 = String(wl9);
      Serial.println(ch9+" "+wlp9);
      
      String ch10 = String(EEPROM.read(20));
      word wl10 = word(EEPROM.read(8),EEPROM.read(9));
      String wlp10 = String(wl10);
      Serial.println(ch10+" "+wlp10);
      
    }
    else if(part1.equalsIgnoreCase("cpl"))
    {
      String ch3 = String(EEPROM.read(12));
      String ch3p = String(EEPROM.read(13));
      String ch3o = ch3 + " " + ch3p;
      Serial.println(ch3o);
      String ch5 = String(EEPROM.read(14));
      String ch5p = String(EEPROM.read(15));
      String ch5o = ch5 + " " + ch5p;
      Serial.println(ch5o); 
      String ch6 = String(EEPROM.read(16));
      String ch6p = String(EEPROM.read(17));
      String ch6o = ch6 + " " + ch6p;
      Serial.println(ch6o);
      String ch9 = String(EEPROM.read(18));
      String ch9p = String(EEPROM.read(19));
      String ch9o = ch9 + " " + ch9p;
      Serial.println(ch9o);
      String ch10 = String(EEPROM.read(20));
      String ch10p = String(EEPROM.read(21));
      String ch10o = ch10 + " " + ch10p;
      Serial.println(ch10o);

    }
    else if(part1.equalsIgnoreCase("usn"))
    {
     //I need to be able to save this into memory, maybe initialize in firmware..... or by command
     String usn = "MA001";
     Serial.println(usn);
    }
    //add more commands
  
  else
  {
    Serial.println("COMMAND NOT RECOGNIZED");
  }
}
