#define ANALOG_IN_PIN A0
#define TINY_GSM_MODEM_SIM800
#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL34kPFbsrX"
#define BLYNK_TEMPLATE_NAME "Quickstart Template"
#define BLYNK_AUTH_TOKEN "EAw6rfWE4rlifBDHpTp1vWsnzPLU2Fwk"
#include <TinyGsmClient.h>
#include <BlynkSimpleTinyGSM.h>//i included this library
#include <SoftwareSerial.h>

float adc_voltage = 0.0;
float in_voltage = 0.0;
float R1 = 30000.0;
float R2 = 7500.0; 

// Float for Reference Voltage
float ref_voltage = 5.0;
 
// Integer for ADC value
int adc_value = 0;
char auth[] = BLYNK_AUTH_TOKEN;
char apn[]  = "airtelgprs.com"; //APN of your service provider
char user[] = "";
char pass[] = "";
SoftwareSerial SerialAT(2, 3); // RX, TX
TinyGsm modem(SerialAT);
void setup()
 {
  Serial.begin(19200);
  delay(10);
  // Set GSM module baud rate
  SerialAT.begin(19200);
  delay(3000);
  modem.restart();
  //modem.init();
  //modem.simUnlock("1234");
  Blynk.begin(auth, modem, apn, user, pass);
}

void loop() {
   Blynk.run();
   // Read the Analog Input
   adc_value = analogRead(ANALOG_IN_PIN);
   Serial.print("Adc value:");
   Serial.println(adc_value);
   // Determine voltage at ADC input
   adc_voltage  = (adc_value * ref_voltage) / 1024.0; 
  // put your main code here, to run repeatedly:
  in_voltage = adc_voltage / (R2/(R1+R2)) ; 
   if(adc_value==5)
   {
      in_voltage=0;     
   }
   
  Serial.print("Input Voltage = ");
  Serial.println(in_voltage);
  Blynk.virtualWrite(V4, in_voltage); 
  if(in_voltage>13){
    //Blynk.Email("siddhantandure@gmail.com", "Alert", "Pipe rusting started");
    Blynk.logEvent("voltage_detection","Pipe rusting started");
  }

delay(1000);
}