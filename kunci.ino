#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address
#include <Wire.h>
#include <EEPROM.h>
#include <Keypad.h>

#include <avr/sleep.h>
#include <avr/power.h>
#define hapus 10 //jumper ke VCC
int solenoid = 11;
boolean ngawur = false;

int analogPin = 3;
int readValue = 0;
boolean somplak = false;
//int z = 11;
//float temperature = 0;
const byte ROWS = 4; // Four rows
const byte COLS = 4; // Three columns
// Define the Keymap
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
// Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins.
byte rowPins[ROWS] = { 9, 8, 7, 6 };
// Connect keypad COL0, COL1 and COL2 to these Arduino pins.
byte colPins[COLS] = { 5, 4, 3, 2 };

// Create the Keypad
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
int countsalah = 0;
/*
const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
	{'1','2','3'},
	{'0','5','6'},
	{'7','8','9'},
	{'*','0','#'}
	};
byte rowPins[ROWS] = {10, 9, 8, 7};
byte colPins[COLS] = {6, 5, 4};
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
*/
//RTC_DS1307 RTC;

//LiquidCrystal lcd(19, 18, 17, 16, 15, 14);
int kosong = 30;

boolean ada, k, l, m, n, o, p = false;
byte isikosong;
byte nilai, nilai2, nilai3, nilai0, nilai5, nilai6;

// number of items in an array
#define NUMITEMS(arg) ((unsigned int) (sizeof (arg) / sizeof (arg [0])))
// turn off interrupts until we are ready
ISR (PCINT0_vect)
  {
  PCICR = 0;  // cancel pin change interrupts
  } // end of ISR (PCINT0_vect)

ISR (PCINT1_vect)
  {
  PCICR = 0;  // cancel pin change interrupts
  } // end of ISR (PCINT1_vect)

ISR (PCINT2_vect)
  {
  PCICR = 0;  // cancel pin change interrupts
  } // end of ISR (PCINT2_vect)
void setup()
{
  lcd.begin(16, 2);
  /*finger.begin(57600);


  if (finger.verifyPassword()) {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("OK!");
    delay(1000);
  } else {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("BAD!");
    delay(1000);
    while (1);
  }*/

  pinMode(solenoid, OUTPUT);
  lcd.clear();
  pinMode(hapus, INPUT);
  delay(1000);
  ngawur = digitalRead(hapus);

  //analogWrite(A7,1023);

  Serial.begin(9600);
  // Wire.begin();
  // RTC.begin();


  Serial.print(ngawur);

  if ( ngawur == HIGH )
  {
    digitalWrite(13, HIGH);

    EEPROM.write(kosong, 100);
    lcd.print("Hapus data...");

    delay(1000);
    lcd.clear();
  }

  digitalWrite(13, LOW);
  isikosong = EEPROM.read(kosong);
  lcd.setCursor(0, 0);
  lcd.print(" Kunci  Elekrik ");
  lcd.setCursor(0, 1);
  lcd.print("- Ruang Server -");
  tone(0, 1500, 100);
  delay(100);
  tone(0, 1800, 100);
  delay(100);

  tone(0, 2000, 100);
  delay(100);
  tone(0, 3000, 500);
  delay(500);
  tone(0, 1800, 100);
  delay(100);
  tone(0, 1500, 100);
  delay(100);

  delay(2000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("First Setup...");
  lcd.setCursor(0, 1);
  lcd.print("Psw : ");
  int a = 0;
  while (isikosong != 2)
  {
    char key = keypad.getKey();
    if (a < 6)
    {
      if (key)
      {
        digitalWrite(13, HIGH);
        delay(50);
        digitalWrite(13, LOW);
        lcd.print("*");
        EEPROM.write(a, key);
        //Serial.println(key);
        a++;
      }
    }
    if (key == '*')
    {

      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("First Setup...");
      lcd.setCursor(0, 1);
      lcd.print("Psw : ");
      a = 0;
    }
    if (key == '#')
    {
      a = 0;
      EEPROM.write(kosong, 2);
      lcd.setCursor(0, 0);
      lcd.clear();
      lcd.print("Pass. Tersimpan!");
      delay(2000);

      int id = 0;
      /*while ( somplak==false)
        {
          getFingerprintEnroll(id);
          delay(50);
        }*/
      digitalWrite(13, HIGH);
      delay(200);
      digitalWrite(13, LOW);
      delay(200);
      digitalWrite(13, HIGH);
      delay(200);
      digitalWrite(13, LOW);
      delay(200);
      digitalWrite(13, HIGH);
      delay(200);
      digitalWrite(13, LOW);
      break;

    }

  }

  lcd.clear();
  somplak = false;

  // Sleeeppppp
 for (byte i = 0; i <= A5; i++)
    {
    pinMode (i, OUTPUT);    // changed as per below
    digitalWrite (i, LOW);  //     ditto
    }
    
  // disable ADC
  ADCSRA = 0;  
  
   // pin change interrupt masks (see above list)
  PCMSK2 |= bit (PCINT22);   // pin 6
  PCMSK2 |= bit (PCINT23);   // pin 7
  PCMSK0 |= bit (PCINT0);    // pin 8
  PCMSK0 |= bit (PCINT1);    // pin 9

  }  // end of setup

// set pins as keypad library expects them
// or call: kpd.initializePins ();
//    however in the library I have that is a private method


void reconfigurePins ()
  {
  byte i;
  
  // go back to all pins as per the keypad library
  
  for (i = 0; i < NUMITEMS (colPins); i++)
    {
    pinMode (colPins [i], OUTPUT);
    digitalWrite (colPins [i], HIGH); 
    }  // end of for each column 

  for (i = 0; i < NUMITEMS (rowPins); i++)
    {
    pinMode (rowPins [i], INPUT);
    digitalWrite (rowPins [i], HIGH); 
    }   // end of for each row

  }  // end of reconfigurePins

void goToSleep ()
  {
  byte i;
   lcd.noBacklight();
  // set up to detect a keypress
  for (i = 0; i < NUMITEMS (colPins); i++)
    {
    pinMode (colPins [i], OUTPUT);
    digitalWrite (colPins [i], LOW);   // columns low
    }  // end of for each column

  for (i = 0; i < NUMITEMS (rowPins); i++)
    {
    pinMode (rowPins [i], INPUT);
    digitalWrite (rowPins [i], HIGH);  // rows high (pull-up)
    }  // end of for each row
    
   // now check no pins pressed (otherwise we wake on a key release)
   for (i = 0; i < NUMITEMS (rowPins); i++)
    {
    if (digitalRead (rowPins [i]) == LOW)
       {
       reconfigurePins ();
       return; 
       } // end of a pin pressed
    }  // end of for each row
  
  // overcome any debounce delays built into the keypad library
  delay (50);
  
  // at this point, pressing a key should connect the high in the row to the 
  // to the low in the column and trigger a pin change
  
  set_sleep_mode (SLEEP_MODE_PWR_DOWN);  
  sleep_enable();

  byte old_ADCSRA = ADCSRA;
  // disable ADC to save power
  ADCSRA = 0;  

  power_all_disable ();  // turn off various modules
   
  PCIFR  |= bit (PCIF0) | bit (PCIF1) | bit (PCIF2);   // clear any outstanding interrupts
  PCICR  |= bit (PCIE0) | bit (PCIE1) | bit (PCIE2);   // enable pin change interrupts
   
  // turn off brown-out enable in software
  MCUCR = bit (BODS) | bit (BODSE);
  MCUCR = bit (BODS); 
  sleep_cpu ();  
 
  // cancel sleep as a precaution
  sleep_disable();
  power_all_enable ();   // enable modules again
  ADCSRA = old_ADCSRA;   // re-enable ADC conversion
  
  // put keypad pins back how they are expected to be
  reconfigurePins ();
    
  }  // end of goToSleep


void loop()

{
  if (countsalah > 3)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("  Terblokir!!!  ");
    lcd.setCursor(0, 1);
    lcd.print("  Remaining :  ");
    int rem = 0;
    for (int aha = 9; aha >= 0; aha--)
    {
      lcd.setCursor(12, 1);
      lcd.print(aha);
      delay(1000);


    }
    countsalah = 0;
    lcd.clear();
    digitalWrite(13, HIGH);
    delay(50);
    digitalWrite(13, LOW);
  }
awal:
  ada = false;
  // DateTime now = RTC.now();
  lcd.setCursor(0, 0);
  lcd.print(" Kunci  Elekrik ");
  lcd.setCursor(0, 1);
  lcd.print("- Ruang Server -");
  int a;

  char key = keypad.getKey();
   if (!key)
     {
     // no key pressed? go to sleep
     goToSleep ();
     return;
     }

  
  a = 0;
  if (key == '*')
  {
    lcd.backlight();
    lcd.clear();
    digitalWrite(13, HIGH);
    delay(50);
    digitalWrite(13, LOW);
    lcd.setCursor(0, 0);
    lcd.print("Input Password");
    lcd.setCursor(0, 1);
    lcd.print("Psw : ");
    while (ada == false)
    {
      char key = keypad.getKey();
      if (key == '#')

      {
        digitalWrite(13, HIGH);
        delay(50);
        digitalWrite(13, LOW);
        delay(500);
        if (k == true)
        {
          if (l = true)
          {
            if (m = true)
            {
              if (n == true)
              {
                if (o == true)
                {
                  if (p == true)
                  {
                    /*delay(100);
                    lcd.clear();
                    lcd.setCursor(0, 0);
                    lcd.print(" Password Benar ");
                    delay(200);
                    lcd.setCursor(0, 0);
                    lcd.print("Tempelkan Jari..");
                    digitalWrite(0, HIGH);
                    delay(200);
                    digitalWrite(0, LOW);
                    delay(2000); int g = 0;
                    while (somplak == false)
                    {
                      g++;
                      getFingerprintIDez();
                      delay(50);
                      if (g > 1000)
                      {
                        goto awal;
                      }
                    }*/
                    somplak = false;
                    lcd.setCursor(0, 1);

                    digitalWrite(13, HIGH);
                    delay(500);
                    digitalWrite(13, LOW);
                    for (int y = 5; y >= 0; y--)
                    {
                      lcd.clear();
                      lcd.setCursor(0, 0);
                      lcd.print("Password Benar..");
                      lcd.setCursor(8, 1);
                      lcd.print(y);
                      digitalWrite(solenoid, HIGH);
                      delay(1000);

                    }
                    digitalWrite(solenoid, LOW);
                    lcd.clear();
                    k, l, m, n = false;
                    ada = true;
                  }
                  else {
                    keluar();
                    goto awal;
                  }
                }
                else {
                  keluar();
                  goto awal;
                }
              }
              else {
                keluar();
                goto awal;
              }
            }
            else {
              keluar();
              goto awal;
            }
          }
          else {
            keluar();
            goto awal;
          }
        }
        else {
          keluar();
          goto awal;
        }
      }
      if (a < 6)
      {
        if (key)
        {
          digitalWrite(13, HIGH);
          delay(50);
          digitalWrite(13, LOW);


          {
            lcd.print("*");
            nilai = EEPROM.read(0);
            nilai2 = EEPROM.read(1);
            nilai3 = EEPROM.read(2);
            nilai0 = EEPROM.read(3);
            nilai5 = EEPROM.read(0);
            nilai6 = EEPROM.read(5);
            if (a == 0)
            {
              if (key == nilai)
              {
                k = true;
              }
            }
            if (a == 1)
            {
              if (key == nilai2)
              {
                l = true;
              }
            }
            if (a == 2)
            {
              if (key == nilai3)
              {
                m = true;
              }
            }
            if (a == 3)
            {
              if (key == nilai0)
              {
                n = true;
              }
            }
            if (a == 0)
            {
              if (key == nilai5)
              {
                o = true;
              }
            }
            if (a == 5)
            {
              if (key == nilai6)
              {
                p = true;
              }
            }

            //Serial.println(key);
            a++;

          }
        }

      }
    }

    // delay(500);
  }

}

void keluar()
{
  delay(500);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(" Password Salah ");
  digitalWrite(13, HIGH);
  delay(200);
  digitalWrite(13, LOW);
  delay(200);
  digitalWrite(13, HIGH);
  delay(200);
  digitalWrite(13, LOW);
  delay(200);
  digitalWrite(13, HIGH);
  delay(200);
  digitalWrite(13, LOW);
  delay(200);
  digitalWrite(13, HIGH);
  delay(200);
  digitalWrite(13, LOW);
  delay(200);
  delay(2000);
  lcd.clear();
  countsalah++;

}
