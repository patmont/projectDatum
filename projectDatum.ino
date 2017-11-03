
#include <XBee.h>
#include <LiquidCrystal.h>
#include <LCDKeypad.h>

XBee xbee = XBee();
LCDKeypad lcd;
unsigned long lf_last = 0; //Initialize a timer variable
unsigned long rf_last = 0; //Initialize a timer variable
unsigned long lr_last = 0; //Initialize a timer variable
unsigned long rr_last = 0; //Initialize a timer variable


Rx16IoSampleResponse ioSample = Rx16IoSampleResponse();
Rx64Response rx64 = Rx64Response();

void setup() { 
//initialize Serial
  Serial.begin(9600);
  Serial.println("--- Start Serial Monitor SEND_RCVE ---");
  xbee.setSerial(Serial);
//Initialize LCD
  lcd.begin(16, 2);
  lcd.clear();
  lcd.print("Project Datum");
  lcd.setCursor(0,1);
  lcd.print("ver. 8232015v1_6");
  delay(3000);
  lcd.clear();
    
}

void loop() {
  //attempt to read a packet    
  xbee.readPacket();

  if (xbee.getResponse().isAvailable()) {
    //Location Character Set
      lcd.setCursor(0,0);
      lcd.print("LF:");
      lcd.setCursor(9,0);
      lcd.print("RF:");
      lcd.setCursor(0,1);
      lcd.print("LR:");
      lcd.setCursor(9,1);
      lcd.print("RR:");
  }
    
    if (xbee.getResponse().getApiId() == RX_16_IO_RESPONSE) {
      xbee.getResponse().getRx16IoSampleResponse(ioSample);
      
      Serial.println(ioSample.getRemoteAddress16(), HEX);
      
      for (int k = 0; k < ioSample.getSampleSize(); k++) {
                    
               if ((millis()-lf_last) > 5000) {
                  lcd.setCursor(3,0);
                  lcd.print("    ");
                  lcd.setCursor(3,0);
                  lcd.print("SNA");
                  Serial.print(millis()-lf_last);
                  Serial.println("   difference");
               }

               if ((millis()-rf_last) > 5000) {
                  lcd.setCursor(12,0);
                  lcd.print("    ");
                  lcd.setCursor(12,0);
                  lcd.print("SNA");
               }

               if ((millis()-lr_last) > 5000) {
                  lcd.setCursor(3,1);
                  lcd.print("    ");
                  lcd.setCursor(3,1);
                  lcd.print("SNA");
               }

               if ((millis()-rr_last) > 5000) {
                  lcd.setCursor(12,1);
                  lcd.print("    ");
                  lcd.setCursor(12,1);
                  lcd.print("SNA");
               }
       
             //Left Front
              if (ioSample.getRemoteAddress16() == 0x64){
                lf_last = millis();
                //Debug
                Serial.print(lf_last);
                Serial.println("  lf_lastseen");
                lcd.setCursor(3,0);
                lcd.print("    ");
                lcd.setCursor(3,0);
                lcd.print(ioSample.getAnalog(4, k));              
               }

             //Right Front
              if (ioSample.getRemoteAddress16() == 0x65){
                rf_last = millis();
                lcd.setCursor(12,0);
                lcd.print("    ");
                lcd.setCursor(12,0);
                lcd.print(ioSample.getAnalog(4, k));
              }

             //Left Rear
              if (ioSample.getRemoteAddress16() == 0x66){
                lr_last = millis();
                lcd.setCursor(3,1);
                lcd.print("    ");
                lcd.setCursor(3,1);
                lcd.print(ioSample.getAnalog(4, k));
             }

             //Right Rear
              if (ioSample.getRemoteAddress16() == 0x67){
                rr_last = millis();
                lcd.setCursor(12,1);
                lcd.print("    ");
                lcd.setCursor(12,1);
                lcd.print(ioSample.getAnalog(4, k));

             }

        }
        
      }
    
    }
