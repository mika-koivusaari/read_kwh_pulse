
volatile unsigned long kWhCounter1=0;
volatile unsigned long kWhCounter2=0;

unsigned long counter1Tmp=0;
unsigned long counter2Tmp=0;

// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
const int LED = 13;
const String GET = "GET";
const String HELP = "HELP";

int MAX_CMD_LENGTH = 10;
//char cmd[10]; //TODO use constant
//int cmdIndex=0;
//char incomingByte;

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

void setup(void)
{
  // start serial port
  Serial.begin(9600);
  Serial.println("");
  
  inputString.reserve(MAX_CMD_LENGTH);
  pinMode(LED, OUTPUT);     

  //alusta keskeytykset pulssien mittaamiseksi
  //pinneihin 2 ja 3
//  attachInterrupt(digitalPinToInterrupt(2), kWhInterrupt1, RISING);
  attachInterrupt(0, kWhInterrupt1, FALLING);
//  attachInterrupt(digitalPinToInterrupt(3), kWhInterrupt2, RISING);
  attachInterrupt(1, kWhInterrupt2, FALLING);
}

void loop(void) {
  // print the string when a newline arrives:
  if (stringComplete) {
    
    if (inputString==GET) {
      cli(); //disable interrupts
      counter1Tmp=kWhCounter1; //get interrupt counter to tmp variables
      kWhCounter1=0;
      counter2Tmp=kWhCounter2;
      kWhCounter2=0;
      sei(); //enable interrupts
      Serial.print("Counters: ");
      Serial.print(counter1Tmp);
      Serial.print(",");
      Serial.print(counter2Tmp);
      Serial.println("");        
    }
    else if (inputString==HELP) {
      Serial.println("Commands:");
      Serial.println("GET");
      
    } else {
      Serial.println("Syntax error:");
      Serial.println("Try HELP");
    }
    
    // clear the string:
    inputString = "";
    stringComplete = false;
  }

/*  if (kWhCounter1>0) {
    for (int i=0;i<10;i++) {
      digitalWrite(LED, HIGH);   // turn the LED on (HIGH is the voltage level)
      delay(1000);               // wait for a second
      digitalWrite(LED, LOW);    // turn the LED off by making the voltage LOW
      delay(1000);               // wait for a second
    }
  }*/

/*  delay(10000);
        cli(); //disable interrupts
        counter1Tmp=kWhCounter1; //get interrupt counter to tmp variables
        kWhCounter1=0;
        counter2Tmp=kWhCounter2;
        kWhCounter2=0;
        sei(); //enable interrupts
        Serial.print("Counters: ");
        Serial.print(counter1Tmp);
        Serial.print(",");
        Serial.print(counter2Tmp);
        Serial.println("");        */
  
}

/*
  SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
 */
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read(); 
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    } else {
      // add it to the inputString:
      inputString += inChar;
    }
  }
}

void kWhInterrupt1(void){
  kWhCounter1++;
  digitalWrite(LED, HIGH);   // turn the LED on (HIGH is the voltage level)
}

void kWhInterrupt2(void){
  kWhCounter2++;
  digitalWrite(LED, HIGH);   // turn the LED on (HIGH is the voltage level)
}
