#include <SoftwareSerial.h>

SoftwareSerial ble_device(11,12);

#include <CapacitiveSensor.h>

#define speaker 13
int latchPin = A1;
int clockPin = A5;
int dataPin = A2;
int dt = 150;
int dt2 = 10; 
int dt_out = 500;
int dur = 500; 

// pitch

// notes in the melody:
int melody[] = {

  // start
  659, 659, 0, 659, 0, 262, 659,
  784, 0, 392, 0,

};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {

  // start
  8, 8, 8, 8, 8, 8, 4,
  4, 4, 4, 4,

};

byte LED1s = 0b10000000;
byte LED2s = 0b01000000;
byte LED3s = 0b00100000;
byte LED4s = 0b00010000;
byte LED5s = 0b00001000;
byte LED6s = 0b00000100;
byte LED7s = 0b00000010;
byte LED8s = 0b00000001;
byte LEDs = 0b0000000;
byte LED9s = 0b10101010;
byte LED10s = 0b00001111;


// Set the Send Pin & Receive Pin.
CapacitiveSensor   cs_2_3 = CapacitiveSensor(2,3);        
CapacitiveSensor   cs_2_4 = CapacitiveSensor(2,4);         
CapacitiveSensor   cs_2_5 = CapacitiveSensor(2,5);     
CapacitiveSensor   cs_2_6 = CapacitiveSensor(2,6);     
CapacitiveSensor   cs_2_7 = CapacitiveSensor(2,7);      
CapacitiveSensor   cs_2_8 = CapacitiveSensor(2,8);    
CapacitiveSensor   cs_2_9 = CapacitiveSensor(2,9);  
CapacitiveSensor   cs_2_10 = CapacitiveSensor(2,10); 


// Set the sensitivity of the sensors.
long total1 =  cs_2_3.capacitiveSensor(3000);
long total2 =  cs_2_4.capacitiveSensor(3000);
long total3 =  cs_2_5.capacitiveSensor(3000);
long total4 =  cs_2_6.capacitiveSensor(3000);
long total5 =  cs_2_7.capacitiveSensor(3000);
long total6 =  cs_2_8.capacitiveSensor(3000);
long total7 =  cs_2_9.capacitiveSensor(3000);
long total8 =  cs_2_10.capacitiveSensor(3000);



// duration of each note
unsigned long timeBegin; unsigned long timeEnd; unsigned long duration;
float dur_float; float start_float; float end_float = timeEnd;






//-----------------------------------------------------------------------------------------------------------------------------



void setup() {
  // put your setup code here, to run once:
  cs_2_6.set_CS_AutocaL_Millis(0xFFFFFFFF);  
  // Arduino start communicate with computer.
  Serial.begin(115200);
//  Serial.println("Start");
  pinMode(latchPin,OUTPUT);
  pinMode(dataPin,OUTPUT);
  pinMode(clockPin,OUTPUT);
  ble_device.begin(9600);
//  ble_device.println("Start");
  
}

//-----------------------------------------------------------------------------------------------------------------------------





void loop() {
  // put your main code here, to run repeatedly:

  // Set the sensitivity of the sensors.
  long total1 =  cs_2_3.capacitiveSensor(3000);
  long total2 =  cs_2_4.capacitiveSensor(3000);
  long total3 =  cs_2_5.capacitiveSensor(3000);
  long total4 =  cs_2_6.capacitiveSensor(3000);
  long total5 =  cs_2_7.capacitiveSensor(3000);
  long total6 =  cs_2_8.capacitiveSensor(3000);
  long total7 =  cs_2_9.capacitiveSensor(3000);
  long total8 =  cs_2_10.capacitiveSensor(3000);

  // piano mode
  if (total1 > 1500) {
    tone(speaker,262);   // frequency C4 262
    Serial.println("C4");
    ble_device.print("C");
    digitalWrite(latchPin,LOW);
    shiftOut(dataPin,clockPin,LSBFIRST,LED1s);
    digitalWrite(latchPin,HIGH);
    delay(dt2);
  }
  if (total2 > 1500) {
    tone(speaker,294); 
    Serial.println("D4");
    ble_device.print("D");
    digitalWrite(latchPin,LOW);
    shiftOut(dataPin,clockPin,LSBFIRST,LED2s);
    digitalWrite(latchPin,HIGH);
    delay(dt2);
  }
  if (total3 > 1500) {
    tone(speaker,330);
    Serial.println("E4");
    ble_device.print("E");
    digitalWrite(latchPin,LOW);
    shiftOut(dataPin,clockPin,LSBFIRST,LED3s);
    digitalWrite(latchPin,HIGH);
    delay(dt2);
  }
  if (total4 > 1500) {
    tone(speaker,349);
    Serial.println("F4");
    ble_device.print("F");
    digitalWrite(latchPin,LOW);
    shiftOut(dataPin,clockPin,LSBFIRST,LED4s);
    digitalWrite(latchPin,HIGH);
    delay(dt2);
  }
  if (total5 > 1500) {
    tone(speaker,392);
    Serial.println("G4");
    ble_device.print("G");
    digitalWrite(latchPin,LOW);
    shiftOut(dataPin,clockPin,LSBFIRST,LED5s);
    digitalWrite(latchPin,HIGH);
    delay(dt2);
  }
  if (total6 > 1500) {
    tone(speaker,440);
    Serial.println("A4");
    ble_device.print("A");
    digitalWrite(latchPin,LOW);
    shiftOut(dataPin,clockPin,LSBFIRST,LED6s);
    digitalWrite(latchPin,HIGH);
    delay(dt2);
  }
  if (total7 > 1500) {
    tone(speaker,494);
    Serial.println("B4");
    ble_device.print("B");
    digitalWrite(latchPin,LOW);
    shiftOut(dataPin,clockPin,LSBFIRST,LED7s);
    digitalWrite(latchPin,HIGH);
    delay(dt2);
  }
  if (total8 > 1500) {
    tone(speaker,523);
    Serial.println("C5");
    ble_device.print("c");
    digitalWrite(latchPin,LOW);
    shiftOut(dataPin,clockPin,LSBFIRST,LED8s);
    digitalWrite(latchPin,HIGH);
    delay(dt2);
  }
  
  while (ble_device.available()){

    int serial_command = Serial.read();
    char ble_command = ble_device.read();
    
    // Get input keynote from Arduino board - Web control: press start recording
    if (ble_command == 'i') { 
      delay(100);
//      ble_device.print("Keynotes Input");  
      Serial.println("Keynotes Input");

      for (int thisNote = 0; thisNote < 10; thisNote++) {

          digitalWrite(latchPin,LOW);
          shiftOut(dataPin,clockPin,LSBFIRST,LED9s);
          digitalWrite(latchPin,HIGH);
          delay(10);
          digitalWrite(latchPin,LOW);
          shiftOut(dataPin,clockPin,LSBFIRST,LEDs);
          digitalWrite(latchPin,HIGH);
          delay(10);

            // to calculate the note duration, take one second divided by the note type.
          int noteDuration = 1000 / noteDurations[thisNote];
          
          tone(speaker, melody[thisNote], noteDuration);
          
          // to distinguish the notes, set a minimum time between them.
          int pauseBetweenNotes = noteDuration * 1.30;
          
          delay(pauseBetweenNotes);
    
          // stop the tone playing:
    
          noTone(speaker);
        }
      
      keynote_input(); 
    }

    // Output keynote to Arduino board - Web control: after machine learning process, press start playing
    else if (ble_command == 'o') {
      delay(100);
//      ble_device.println("Keynotes Output"); 
      Serial.println("Keynotes Output");
     
      toArray();
 

    }
  }
  
    
  if (total1<=1500  &  total2<=1500  &  total3<=1500 & total4<=1500  &  total5<=1500  &  total6<=1500 &   total7<=1500 &  total8<=1500)
    {
      noTone(speaker);
      digitalWrite(latchPin,LOW);
      shiftOut(dataPin,clockPin,LSBFIRST,LEDs);
      digitalWrite(latchPin,HIGH);
      delay(dt2);
     }
  
}



//-----------------------------------------------------------------------------------------------------------------------------

// keynote input from Arduino board
void keynote_input() {
  // put your code here, to run repeatedly:
  
  // Set the sensitivity of the sensors.
  long total1 =  cs_2_3.capacitiveSensor(3000);
  long total2 =  cs_2_4.capacitiveSensor(3000);
  long total3 =  cs_2_5.capacitiveSensor(3000);
  long total4 =  cs_2_6.capacitiveSensor(3000);
  long total5 =  cs_2_7.capacitiveSensor(3000);
  long total6 =  cs_2_8.capacitiveSensor(3000);
  long total7 =  cs_2_9.capacitiveSensor(3000);
  long total8 =  cs_2_10.capacitiveSensor(3000);

  // return if receive BLE command'
  char ble_command = ble_device.read();
  if (ble_command == 'o') {
      delay(100);
      ble_device.println("Keynotes Output"); 
      Serial.println("Keynotes Output");
      return keynote_output();
  }


  // back to piano mode
  if (ble_command == 'b') {
      delay(100);
      ble_device.println("Back to Piano Mode"); 
      Serial.println("Back to Piano Mode");
      return loop();
  }

  // stop command
  if (ble_command == 's') {
      delay(100);
      Serial.println("Stop");
      return loop;
  }

//  Serial.println("get input");
  noTone(speaker);

  // no input
  if (total1<=1500  &  total2<=1500  &  total3<=1500 & total4<=1500  &  total5<=1500  &  total6<=1500 &   total7<=1500 &  total8<=1500)
    {
      noTone(speaker);
      digitalWrite(latchPin,LOW);
      shiftOut(dataPin,clockPin,LSBFIRST,LEDs);
      digitalWrite(latchPin,HIGH);
      delay(dt2);
      return keynote_input();
     }

  // input C4
  if (total1 > 1500) {   
    delay(100);

    timeBegin = millis();

    keynote_input_C();
    delay(100);

    timeEnd = millis();
    duration = timeEnd - timeBegin;
    dur_float = duration;
    start_float = timeBegin;
    end_float = timeEnd;

    Serial.println("C4_in, 60"); // 60 - MIDI number in string
    Serial.print("Start: ");
    Serial.println(start_float/1000, 1);
    Serial.print("End: ");
    Serial.println(end_float/1000, 1);

    ble_device.println(60); 
    ble_device.println(start_float/1000, 1);
    ble_device.println(end_float/1000, 1);

    delay(100);
    return keynote_input();
  }

  // input D4
  if (total2 > 1500) {   
    delay(100);

    timeBegin = millis();

    keynote_input_D();
    delay(100);

    timeEnd = millis();
    duration = timeEnd - timeBegin;
    dur_float = duration;
    start_float = timeBegin;
    end_float = timeEnd;

    Serial.println("D4_in, 62"); 
    Serial.print("Start: ");
    Serial.println(start_float/1000, 1);
    Serial.print("End: ");
    Serial.println(end_float/1000, 1);

    ble_device.println(62); 
    ble_device.println(start_float/1000, 1);
    ble_device.println(end_float/1000, 1);

    delay(100);
    return keynote_input();
  }

  // input E4
  if (total3 > 1500) {   
    delay(100);

    timeBegin = millis();

    keynote_input_E();
    delay(100);

    timeEnd = millis();
    duration = timeEnd - timeBegin;
    dur_float = duration;
    start_float = timeBegin;
    end_float = timeEnd;

    Serial.println("E4_in, 64"); 
    Serial.print("Start: ");
    Serial.println(start_float/1000, 1);
    Serial.print("End: ");
    Serial.println(end_float/1000, 1);

    ble_device.println(64); 
    ble_device.println(start_float/1000, 1);
    ble_device.println(end_float/1000, 1);

    delay(100);
    return keynote_input();
  }

  // input F4
  if (total4 > 1500) {   
    delay(100);

    timeBegin = millis();

    keynote_input_F();
    delay(100);

    timeEnd = millis();
    duration = timeEnd - timeBegin;
    dur_float = duration;
    start_float = timeBegin;
    end_float = timeEnd;

    Serial.println("F4_in, 65"); 
    Serial.print("Start: ");
    Serial.println(start_float/1000, 1);
    Serial.print("End: ");
    Serial.println(end_float/1000, 1);

    ble_device.println(65); 
    ble_device.println(start_float/1000, 1);
    ble_device.println(end_float/1000, 1);

    delay(100);
    return keynote_input();
  }

  // input G4
    if (total5 > 1500) {   
      delay(100);
  
      timeBegin = millis();
  
      keynote_input_G();
      delay(100);
  
      timeEnd = millis();
      duration = timeEnd - timeBegin;
      dur_float = duration;
      start_float = timeBegin;
      end_float = timeEnd;
  
      Serial.println("G4_in, 67"); 
      Serial.print("Start: ");
      Serial.println(start_float/1000, 1);
      Serial.print("End: ");
      Serial.println(end_float/1000, 1);
  
      ble_device.println(67); 
      ble_device.println(start_float/1000, 1);
      ble_device.println(end_float/1000, 1);
  
      delay(100);
      return keynote_input();
    }

  // input A4
    if (total6 > 1500) {   
      delay(100);
  
      timeBegin = millis();
  
      keynote_input_A();
      delay(100);
  
      timeEnd = millis();
      duration = timeEnd - timeBegin;
      dur_float = duration;
      start_float = timeBegin;
      end_float = timeEnd;
  
      Serial.println("A4_in, 69"); 
      Serial.print("Start: ");
      Serial.println(start_float/1000, 1);
      Serial.print("End: ");
      Serial.println(end_float/1000, 1);
  
      ble_device.println(69); 
      ble_device.println(start_float/1000, 1);
      ble_device.println(end_float/1000, 1);
  
      delay(100);
      return keynote_input();
    }

   // input B4
    if (total7 > 1500) {   
      delay(100);
  
      timeBegin = millis();
  
      keynote_input_B();
      delay(100);
  
      timeEnd = millis();
      duration = timeEnd - timeBegin;
      dur_float = duration;
      start_float = timeBegin;
      end_float = timeEnd;
  
      Serial.println("B4_in, 71"); 
      Serial.print("Start: ");
      Serial.println(start_float/1000, 1);
      Serial.print("End: ");
      Serial.println(end_float/1000, 1);
  
      ble_device.println(71); 
      ble_device.println(start_float/1000, 1);
      ble_device.println(end_float/1000, 1);
  
      delay(100);
      return keynote_input();
    }

   // input C5
    if (total8 > 1500) {   
      delay(100);
  
      timeBegin = millis();
  
      keynote_input_C_H();
      delay(100);
  
      timeEnd = millis();
      duration = timeEnd - timeBegin;
      dur_float = duration;
      start_float = timeBegin;
      end_float = timeEnd;
  
      Serial.println("C5_in, 72"); 
      Serial.print("Start: ");
      Serial.println(start_float/1000, 1);
      Serial.print("End: ");
      Serial.println(end_float/1000, 1);
  
      ble_device.println(72); 
      ble_device.println(start_float/1000, 1);
      ble_device.println(end_float/1000, 1);
  
      delay(100);
      return keynote_input();
    }
    
  
}



//-----------------------------------------------------------------------------------------------------------------------------
void keynote_input_C() { 
  tone(speaker, 262);
  digitalWrite(latchPin,LOW);
  shiftOut(dataPin,clockPin,LSBFIRST,LED1s);
  digitalWrite(latchPin,HIGH);

  long total1 =  cs_2_3.capacitiveSensor(3000);
  
  if (total1 <= 1500) {
    delay(100);
    digitalWrite(latchPin,LOW);
    shiftOut(dataPin,clockPin,LSBFIRST,LEDs);
    digitalWrite(latchPin,HIGH);
    return;
  }
  else {
    return keynote_input_C();
  }
}

void keynote_input_D() { 
  tone(speaker, 294);
  digitalWrite(latchPin,LOW);
  shiftOut(dataPin,clockPin,LSBFIRST,LED2s);
  digitalWrite(latchPin,HIGH);

  long total2 =  cs_2_4.capacitiveSensor(3000);
  
  if (total2 <= 1500) {
    delay(100);
    digitalWrite(latchPin,LOW);
    shiftOut(dataPin,clockPin,LSBFIRST,LEDs);
    digitalWrite(latchPin,HIGH);
    return;
  }
  else {
    return keynote_input_D();
  }
}


void keynote_input_E() { 
  tone(speaker, 330);
  digitalWrite(latchPin,LOW);
  shiftOut(dataPin,clockPin,LSBFIRST,LED3s);
  digitalWrite(latchPin,HIGH);

  long total3 =  cs_2_5.capacitiveSensor(3000);
  
  if (total3 <= 1500) {
    delay(100);
    digitalWrite(latchPin,LOW);
    shiftOut(dataPin,clockPin,LSBFIRST,LEDs);
    digitalWrite(latchPin,HIGH);
    return;
  }
  else {
    return keynote_input_E();
  }
}


void keynote_input_F() { 
  tone(speaker, 349);
  digitalWrite(latchPin,LOW);
  shiftOut(dataPin,clockPin,LSBFIRST,LED4s);
  digitalWrite(latchPin,HIGH);

  long total4 =  cs_2_6.capacitiveSensor(3000);
  
  if (total4 <= 1500) {
    delay(100);
    digitalWrite(latchPin,LOW);
    shiftOut(dataPin,clockPin,LSBFIRST,LEDs);
    digitalWrite(latchPin,HIGH);
    return;
  }
  else {
    return keynote_input_F();
  }
}


void keynote_input_G() { 
  tone(speaker, 392);
  digitalWrite(latchPin,LOW);
  shiftOut(dataPin,clockPin,LSBFIRST,LED5s);
  digitalWrite(latchPin,HIGH);

  long total5 =  cs_2_7.capacitiveSensor(3000);
  
  if (total5 <= 1500) {
    delay(100);
    digitalWrite(latchPin,LOW);
    shiftOut(dataPin,clockPin,LSBFIRST,LEDs);
    digitalWrite(latchPin,HIGH);
    return;
  }
  else {
    return keynote_input_G();
  }
}

void keynote_input_A() { 
  tone(speaker, 440);
  digitalWrite(latchPin,LOW);
  shiftOut(dataPin,clockPin,LSBFIRST,LED6s);
  digitalWrite(latchPin,HIGH);

  long total6 =  cs_2_8.capacitiveSensor(3000);
  
  if (total6 <= 1500) {
    delay(100);
    digitalWrite(latchPin,LOW);
    shiftOut(dataPin,clockPin,LSBFIRST,LEDs);
    digitalWrite(latchPin,HIGH);
    return;
  }
  else {
    return keynote_input_A();
  }
}

void keynote_input_B() { 
  tone(speaker, 494);
  digitalWrite(latchPin,LOW);
  shiftOut(dataPin,clockPin,LSBFIRST,LED7s);
  digitalWrite(latchPin,HIGH);

  long total7 =  cs_2_9.capacitiveSensor(3000);
  
  if (total7 <= 1500) {
    delay(100);
    digitalWrite(latchPin,LOW);
    shiftOut(dataPin,clockPin,LSBFIRST,LEDs);
    digitalWrite(latchPin,HIGH);
    return;
  }
  else {
    return keynote_input_B();
  }
}

void keynote_input_C_H() { 
  tone(speaker, 523);
  digitalWrite(latchPin,LOW);
  shiftOut(dataPin,clockPin,LSBFIRST,LED8s);
  digitalWrite(latchPin,HIGH);

  long total8 =  cs_2_10.capacitiveSensor(3000);
  
  if (total8 <= 1500) {
    delay(100);
    digitalWrite(latchPin,LOW);
    shiftOut(dataPin,clockPin,LSBFIRST,LEDs);
    digitalWrite(latchPin,HIGH);
    return;
  }
  else {
    return keynote_input_C_H();
  }
}


//-----------------------------------------------------------------------------------------------------------------------------

//  array 

int index = 0 ;
char magenta_output[100];
byte note;

int index_m = 0;
int index_t = 0;
char melody_lst[50] ;
int time_lst[50] ;
String temp_dur = "";

//

void toArray() {

  note = (char)ble_device.read();
  
  delay(100);

  // keep receiving from ble_device  (empty=255)
  if (note == 255){
    return toArray();
    }

  // "z" means end of the output array (z=122)
  else if (note == 122) {
      // add the z into the array as an indicator
      magenta_output[index] = note;
      index++;
      return keynote_output();
      }


  // ( i = 105 )
  else if (note == 105) {
      delay(50);
//      ble_device.print("Keynotes Input"); 
      Serial.println("Keynotes Input");
      return keynote_input();
      }

  // back to Piano Mode( b = 98 )
  else if (note == 98) {
      delay(100);
//      ble_device.println("Back to Piano Mode"); 
      Serial.println("Back to Piano Mode");
      return loop();
      }

  // store the received data into array
  else {
    
    Serial.println(note);
    magenta_output[index] = note;
    index++;

    return toArray();
    }
  
   
  }





//-----------------------------------------------------------------------------------------------------------------------------

void play(){


  for (int i = 0; i < index_m ; i++) {

          // to calculate the note duration, take one second divided by the note type.
          unsigned long noteDuration = time_lst[i] * 1.50 ;

          // B2
          if (melody_lst[i] == 'A') {
            delay(50);
            Serial.println("B2 out");
            
            tone(speaker, 123, noteDuration);
            digitalWrite(latchPin,LOW);
            shiftOut(dataPin,clockPin,LSBFIRST,LED7s);
            digitalWrite(latchPin,HIGH);
            delay(dt_out);
          }

          // C3
          if (melody_lst[i] == 'B') {
            delay(50);
            Serial.println("C3 out");
            
            tone(speaker, 131, noteDuration);
            digitalWrite(latchPin,LOW);
            shiftOut(dataPin,clockPin,LSBFIRST,LED1s);
            digitalWrite(latchPin,HIGH);
            delay(dt_out);
          }
        
          // C#3
          if (melody_lst[i] == 'C') {
            delay(50);
            Serial.println("C#3 out");
            
            tone(speaker, 139, noteDuration);
            delay(dt_out);
          }
        
          // D3
          if (melody_lst[i] == 'D') {
            delay(50);
            Serial.println("F out");
            
            tone(speaker, 147, noteDuration);
            digitalWrite(latchPin,LOW);
            shiftOut(dataPin,clockPin,LSBFIRST,LED2s);
            digitalWrite(latchPin,HIGH);
            delay(dt_out);
          }
        
          // D#3
          if (melody_lst[i] == 'E') {
            delay(50);
            Serial.println("D#3 out");
            
            tone(speaker, 156, noteDuration);
            delay(dt_out);
          }

        
          // E3
          if (melody_lst[i] == 'F') {
            delay(50);
            Serial.println("E3 out");
            
            tone(speaker, 165, noteDuration);
            digitalWrite(latchPin,LOW);
            shiftOut(dataPin,clockPin,LSBFIRST,LED3s);
            digitalWrite(latchPin,HIGH);
            delay(dt_out);
          }
        
          // F3
          if (melody_lst[i] == 'G') {
            delay(50);
            Serial.println("F3 out");
            
            tone(speaker, 175, noteDuration);
            digitalWrite(latchPin,LOW);
            shiftOut(dataPin,clockPin,LSBFIRST,LED7s);
            digitalWrite(latchPin,HIGH);
            delay(dt_out);
          }

       
           // F#3
          if (melody_lst[i] == 'H') {
            delay(50);
            Serial.println("F#3 out");
            
            tone(speaker, 185, noteDuration);
            delay(dt_out);
          }
  
           // G3
          if (melody_lst[i] == 'I') {
            delay(50);
            Serial.println("G3 out");
            
            tone(speaker, 196, noteDuration);
            digitalWrite(latchPin,LOW);
            shiftOut(dataPin,clockPin,LSBFIRST,LED5s);
            digitalWrite(latchPin,HIGH);
            delay(dt_out);
          }


          // G#3
          if (melody_lst[i] == 'J') {
            delay(50);
            Serial.println("G#3 out");
            
            tone(speaker, 208, noteDuration);
            delay(dt_out);
          }


          // A3
          if (melody_lst[i] == 'K') {
            delay(50);
            Serial.println("A3 out");
            
            tone(speaker, 220, noteDuration);
            digitalWrite(latchPin,LOW);
            shiftOut(dataPin,clockPin,LSBFIRST,LED6s);
            digitalWrite(latchPin,HIGH);
            delay(dt_out);
          }


          // A#3
          if (melody_lst[i] == 'L') {
            delay(50);
            Serial.println("G#3 out");
            
            tone(speaker, 233, noteDuration);
            delay(dt_out);
          }


          // B3
          if (melody_lst[i] == 'M') {
            delay(50);
            Serial.println("B3 out");
            
            tone(speaker, 247, noteDuration);
            digitalWrite(latchPin,LOW);
            shiftOut(dataPin,clockPin,LSBFIRST,LED7s);
            digitalWrite(latchPin,HIGH);
            delay(dt_out);
          }


          // C4
          if (melody_lst[i] == 'N') {
            delay(50);
            Serial.println("C4 out");
            
            tone(speaker, 262, noteDuration);
            digitalWrite(latchPin,LOW);
            shiftOut(dataPin,clockPin,LSBFIRST,LED8s);
            digitalWrite(latchPin,HIGH);
            delay(dt_out);
          }

          // C#4
          if (melody_lst[i] == 'O') {
            delay(50);
            Serial.println("C#4 out");
            
            tone(speaker, 277, noteDuration);
            delay(dt_out);
          }


          // D4
          if (melody_lst[i] == 'P') {
            delay(50);
            Serial.println("D4 out");
            
            tone(speaker, 294, noteDuration);
            digitalWrite(latchPin,LOW);
            shiftOut(dataPin,clockPin,LSBFIRST,LED2s);
            digitalWrite(latchPin,HIGH);
            delay(dt_out);
          }


          // D#4
          if (melody_lst[i] == 'Q') {
            delay(50);
            Serial.println("D#4 out");
            
            tone(speaker, 311, noteDuration);
            delay(dt_out);
          }


          // E4
          if (melody_lst[i] == 'R') {
            delay(50);
            Serial.println("E4 out");
            
            tone(speaker, 330, noteDuration);
            digitalWrite(latchPin,LOW);
            shiftOut(dataPin,clockPin,LSBFIRST,LED3s);
            digitalWrite(latchPin,HIGH);
            delay(dt_out);
          }


          // F4
          if (melody_lst[i] == 'S') {
            delay(50);
            Serial.println("F4 out");
            
            tone(speaker, 349, noteDuration);
            digitalWrite(latchPin,LOW);
            shiftOut(dataPin,clockPin,LSBFIRST,LED4s);
            digitalWrite(latchPin,HIGH);
            delay(dt_out);
          }



          // F#4
          if (melody_lst[i] == 'T') {
            delay(50);
            Serial.println("F#4 out");
            
            tone(speaker, 370, noteDuration);
            delay(dt_out);
          }


          // G4
          if (melody_lst[i] == 'U') {
            delay(50);
            Serial.println("G4 out");
            
            tone(speaker, 392, noteDuration);
            digitalWrite(latchPin,LOW);
            shiftOut(dataPin,clockPin,LSBFIRST,LED5s);
            digitalWrite(latchPin,HIGH);
            delay(dt_out);
          }


          // G#4
          if (melody_lst[i] == 'V') {
            delay(50);
            Serial.println("G#4 out");
            
            tone(speaker, 415, noteDuration);
            delay(dt_out);
          }


          // A4
          if (melody_lst[i] == 'W') {
            delay(50);
            Serial.println("A4 out");
            
            tone(speaker, 440, noteDuration);
            digitalWrite(latchPin,LOW);
            shiftOut(dataPin,clockPin,LSBFIRST,LED6s);
            digitalWrite(latchPin,HIGH);
            delay(dt_out);
          }


          // A#4
          if (melody_lst[i] == 'X') {
            delay(50);
            Serial.println("A#4 out");
            
            tone(speaker, 466, noteDuration);
            delay(dt_out);
          }


          // B4
          if (melody_lst[i] == 'Y') {
            delay(50);
            Serial.println("B4 out");
            
            tone(speaker, 494, noteDuration);
            digitalWrite(latchPin,LOW);
            shiftOut(dataPin,clockPin,LSBFIRST,LED7s);
            digitalWrite(latchPin,HIGH);
            delay(dt_out);
          }


          // C5
          if (melody_lst[i] == 'Z') {
            delay(50);
            Serial.println("C5 out");
            
            tone(speaker, 523, noteDuration);
            digitalWrite(latchPin,LOW);
            shiftOut(dataPin,clockPin,LSBFIRST,LED1s);
            digitalWrite(latchPin,HIGH);
            delay(dt_out);
          }


          // C#5
          if (melody_lst[i] == 'a') {
            delay(50);
            Serial.println("C#5 out");
            
            tone(speaker, 554, noteDuration);
            delay(dt_out);
          }

          
    
          // stop the tone playing:
    
          noTone(speaker);
    }

   // reset the var
    index = 0 ;
//    magenta_output[100];
    memset(magenta_output,0,sizeof(magenta_output));
    index_m = 0;
    index_t = 0;
//    melody_lst[50] ;
    memset(melody_lst,0,sizeof(melody_lst));
//    time_lst[50] ;
    memset(melody_lst,0,sizeof(melody_lst));
      
//    return command();
  }




//-----------------------------------------------------------------------------------------------------------------------------

  

// output keynote to Arduino board
void keynote_output() {

  Serial.print("Output Array:");
  Serial.println(magenta_output);
  
    
  for ( int i = 0 ; i < sizeof(magenta_output); i++){

    Serial.print("Magenta Output: ");
    Serial.println(magenta_output[i]);
    
    if (isAlpha(magenta_output[i])){

        
        if (i == 0){
          
          // reset the number 
          temp_dur = "";

          if (magenta_output[i] != 'z'){
          
          melody_lst[index_m] = magenta_output[i] ; 
          index_m++;
          }
          
         }
          
          
        else if (magenta_output[i] == 'z'){
           
           // affter put the number together and then append to the array
           time_lst[index_t] = temp_dur.toInt();
           index_t++;
           //
           Serial.println("Melody List:");
           for (int i=0; i< index_t ;i++){
              Serial.println(melody_lst[i]);
                    };
          Serial.println("Time List:");
          for (int i=0; i< index_t ;i++){
             Serial.println(time_lst[i]);
                    };
           //
           return play();

          }
     
        else {
          
           
           // affter put the number together and then append to the array
           time_lst[index_t] = temp_dur.toInt();
           index_t++;

           
           // reset the number
           temp_dur = "";

             // append the keynote into melody array
           
            melody_lst[index_m] = magenta_output[i] ; 
            index_m++;
        
         }
          
        }
    else {
        // add the number into a string as temp storage
        temp_dur += String(magenta_output[i]);
        
      }
   }   
    
}
