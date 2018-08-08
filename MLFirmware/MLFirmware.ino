String inString;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.print("<Arduino is ready>");
}

void loop() {
  if (Serial.available() > 0) {
    inString = Serial.readString();
    if (inString = "rst") {
      Serial.println("You reset your device");
    }
    if (inString = "hello") {
    Serial.println(inString);
  }else{
    Serial.println("Command Not Recognized");
    
  }
  inString = "";
}
}

  

     


        

  
  

