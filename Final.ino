#include <SharpIR.h>
#include "HX711.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define calibration_factor -71026.00

#define LOADCELL_DOUT_PIN  3
#define LOADCELL_SCK_PIN  2
#define solenoidvalve 17
#define solenoidvalve1 19
#define IRPin1 A5
#define IRPin2 A6
#define model 1080//model no of ir sensor

//keypad
const byte ROWS = 4; 
const byte COLS = 4; 

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] =  {4, 5, 6, 7};//connected pins for rows and columns
byte colPins[COLS] =  {8, 9, 10,11}; 


Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 



int count=0;


HX711 scale;
//display i2c pins define
int SCL_pin = 20; //Pin D5
int SDA_pin = 21; //Pin D6

const int buzzer = 12; //buzzer to arduino pin 12



int distance_cm1,distance1,distance_cm2,distance2;
float w,oil_weight,Can_weight,Last_oil_weight,emergency_exit_oil;
int Can_count=0;
int Amount_of_oil=0;//variable of function wich has to define the oil amount and fill the relavent cans.
long Number,Num1,Num2;
char customKey,customKey1,customKey2,customKey3;
int oil_kg,amount_of_kg_for_price,amount_of_cane_for_price,remaining_kg;
int oil_price;
int real_oil_weight,oil_price_now;
int any_amount_of_kg,any_amount_of_can;
//int count_menu=0;
int emergency_exit_cane;

SharpIR mySensor1 = SharpIR(IRPin1, model);
SharpIR mySensor2 = SharpIR(IRPin2, model);

void setup() {
pinMode(buzzer, OUTPUT);  
  
 tone(buzzer, 1000); 
 delay(500);       
 noTone(buzzer);

  lcd.init();
  lcd.begin(16,4);
  lcd.backlight();

lcd.setCursor(16, 0);
lcd.print(">>  ZOE TECH  <<");
lcd.setCursor(8, 0);
lcd.print("   Oil Filling  ");
lcd.setCursor(24, 0);
lcd.print("    Machine ");
delay(3000);
lcd.clear();

      

  Serial.begin(9600);
  
  pinMode(solenoidvalve, OUTPUT);
  pinMode(solenoidvalve1, OUTPUT);  
  digitalWrite(solenoidvalve,HIGH); //set solenoid valve to close state  
  digitalWrite(solenoidvalve1,HIGH);  
    
  //Serial.print("In1");
//start the load cell  
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale(calibration_factor);
  scale.tare(); 
   
  function7();

}

void loop() {


 // Serial.println("loop"); 
  char customKey = customKeypad.getKey();
   
    if (customKey){
          tone(buzzer, 1000); 
              delay(50);       
          noTone(buzzer);     
              Serial.println(customKey);
      if(customKey=='1'){
          function1_1();
      }   
      if(customKey=='2'){
          function2();
      } 
      if(customKey=='3'){
          function3();
      }
      if(customKey=='4'){
          function4();
      }  
      if(customKey=='5'){
          function5();
      } 
      if(customKey=='6'){
          function6();
      }                              
      if(customKey=='B'){
           Display_menu2();
          
      } 
      if(customKey=='A'){
          Display_menu1();
      }                     
    }
}



void Display_menu2(){
lcd.clear();  
menu2();

return start1();  
  
} 
void Display_menu3(){
lcd.clear();  
menu3();

return start3();  
  
} 
void Display_menu1(){
lcd.clear();  
menu1();

return loop();  
  
} 
void start(){
menu1();
while(true){
char customKey2 = customKeypad.getKey();
   
    if (customKey2){
          tone(buzzer, 1000); 
              delay(50);       
          noTone(buzzer);     
              Serial.println(customKey);
      if(customKey2=='1'){
          function1_1();
      }   
      if(customKey2=='2'){
          function2();
      }
      if(customKey2=='3'){
          function3();
      }
      if(customKey2=='4'){
          function4();
      }   
       if(customKey2=='5'){
          function5();
      }                  
      if(customKey2=='6'){
          function6();
      } 
      if(customKey2=='B'){
          Display_menu2();
      } 
      if(customKey2=='A'){
          Display_menu1();
      }               
    }
} }

void start1(){

while(true){
char customKey3 = customKeypad.getKey();
   
    if (customKey3){
          tone(buzzer, 1000); 
              delay(50);       
          noTone(buzzer);     
              Serial.println(customKey3);
      if(customKey3=='1'){
          function1_1();
      }   
      if(customKey3=='2'){
          function2();
      }
      if(customKey3=='3'){
          function3();
      }
      if(customKey3=='4'){
          function4();
      }   
       if(customKey3=='5'){
          function5();
      }                  
      if(customKey3=='6'){
          function6();
      } 
      if(customKey3=='B'){
          Display_menu3();
      } 
      if(customKey3=='A'){
          Display_menu1();
      }               
    }
} }
  
    
void start3(){

while(true){
char customKey2 = customKeypad.getKey();
   
    if (customKey2){
          tone(buzzer, 1000); 
              delay(50);       
          noTone(buzzer);     
              Serial.println(customKey);
      if(customKey2=='1'){
          function1_1();
      }   
      if(customKey2=='2'){
          function2();
      }
      if(customKey2=='3'){
          function3();
      }
      if(customKey2=='4'){
          function4();
      }   
       if(customKey2=='5'){
          function5();
      }                  
      if(customKey2=='6'){
          function6();
      } 
      if(customKey2=='B'){
         return start();
      } 
      if(customKey2=='A'){
          Display_menu2();
      }               
    }
} }  
void function1_1(){

lcd.clear();
function_print1();
delay(5000);
scale.tare();
function1();

}
void function1(){
lcd.clear();  
while(true){

//delay(2000);
char customKey = customKeypad.getKey();
   
 if (customKey){
         
          Serial.println(customKey);
      if(customKey=='D'){
                lcd.clear();
                lcd.setCursor(0,0);
                lcd.print("Press OK to exit");
                                
                lcd.setCursor(16,0);
                lcd.print("No of Cans:");
                lcd.print(Can_count);

                lcd.setCursor(8,0);
                lcd.print("Oil Amount:");
                lcd.print(Amount_of_oil);
                //lcd.print("KG");

                        
                lcd.setCursor(24,0);
                lcd.print("Emg Oil:");
                lcd.print(emergency_exit_oil);
                lcd.print("KG");
        
            while(true){

              char customKey = customKeypad.getKey();

                if (customKey){
                        Serial.println(customKey);
                                                     
                    if(customKey=='#'){
                      Can_count=0;
                      Amount_of_oil=0; 
                      emergency_exit_oil=0;
                      emergency_exit_cane=0;
                      Num2=0;
                      oil_kg=0; 
                      Number=0;                                                                  
                            return start();
                    }  

                }              


            }          

      } 
      if(customKey=='C'){
        scale.tare(); 
      }         
  }

   
distance1=ir1();
distance2=ir2();
oil_weight=weight();

display_function1_value();

//can alignment and mouth alignment
if ( distance1 < 11  && distance1 > 9  && distance2 < 13 && distance2 >10 && oil_weight > 0.6 && oil_weight < 1.5 ){

  
      
    lcd.clear();
    lcd.setCursor(16,0);
    lcd.print(" Wait 5 Seconds"); 
    lcd.setCursor(8,0);
    lcd.print(" Identifying....");             

    Serial.print(" Can found");
    Serial.println();

    delay(5000);

    distance1=ir1();
    distance2=ir2();
   // oil_weight=weight();
     

     Serial.print(distance1);
     Serial.print(distance2);
      //delay(1000);

    if(distance1 < 11  && distance1 > 9  && distance2 < 13 && distance2 >10 && oil_weight > 0.6 && oil_weight < 1.5  ){
      
            lcd.clear();

      

            //oil_weight=weight();      
              
            Serial.print("Still Oil Can is there!!");
            Serial.println();
            Serial.print(oil_weight);

           /* lcd.setCursor(0,0);
            lcd.print("  function1 ");

            lcd.setCursor(16,0);
            lcd.print("Weight -");
                        
            lcd.print(oil_weight);
            lcd.print("KG");

            lcd.setCursor(8,0);
            lcd.print("Amount of Can-");
            lcd.print(Can_count);

            lcd.setCursor(24,0);
            lcd.print("Amount of Oil-");
            lcd.print(Amount_of_oil);
            lcd.print("KG");*/
            
            //delay(1000);
            Can_weight=oil_weight; 
            Serial.print(Can_weight);
            //delay(3000); 

          //compare the can weight to 19.1 or (can weight+18kg)                    
          while( oil_weight < (18+Can_weight) && oil_weight < 19.1  ){
    
                  distance1=ir1();
                  distance2=ir2();
                  oil_weight=weight();
                                    
                  Last_oil_weight=oil_weight;
                  display_function1_1value();

                  
              if(distance1 < 11  && distance1 > 9  && distance2 < 13 && distance2 >10 ){
                
                    
                    display_function1_1value();
                    Serial.print(" Oil is filling to Can");
                    Serial.println();
                    digitalWrite(solenoidvalve,LOW);


              } 

              else{
                digitalWrite(solenoidvalve,HIGH);
                emergency_exit_cane++;                
                emergency_exit_oil+=Last_oil_weight;
                lcd.clear();                

                    while(true){
                   
                    
                    Serial.print("Emergency Out");
                    Serial.println();
                    Serial.print(Last_oil_weight);
                    Serial.println(); 

                    lcd.setCursor(0,0);
                    lcd.print("Emergency Out!!");
                    
                      lcd.setCursor(16,0);
                      lcd.print("Filled Amount");

                      lcd.setCursor(8,0);
                      lcd.print(": ");
                      lcd.print(Last_oil_weight);
                      lcd.print("KG");                      

                        lcd.setCursor(24,0);
                        lcd.print("To continue-> E");
                                               
                    
                      tone(buzzer, 1000); 
                      delay(500);       
                      noTone(buzzer);     
                      delay(300);                      
                                          

 
                          char customKey = customKeypad.getKey();
   
 
  
                            if (customKey){
                             Serial.println(customKey);
                                                           
                               if(customKey=='C'){
                                      lcd.clear();                                  
                                      return function1();
                                  }   
                                  }
                               }                    
                                        
                                        
                    
                                                                                      
                    
                  }                            
            } 
              digitalWrite(solenoidvalve,HIGH);             
              lcd.clear();
              Serial.print("Oil Can successfully filled!!");
              Serial.println();
              
              Can_count++;
              Amount_of_oil+=18; 
                                                                     
                lcd.setCursor(0,0);
                lcd.print("Oil Can filled!!");
                                
                lcd.setCursor(8,0);
                lcd.print("No of Cans:");
                lcd.print(Can_count);

                lcd.setCursor(24,0);
                lcd.print("Oil Amount:");
                lcd.print(Amount_of_oil);
                lcd.print(" KG");    
                                           
              while(true){
                 Serial.print("Buzer!!");
                  Serial.println();
                      tone(buzzer, 1000); 
                      delay(1000);       
                      noTone(buzzer);     
                      delay(1000);                   
                  distance1=ir1();
                  distance2=ir2();                                        

                    if(distance1 > 9   && distance2 > 10  ){
                      lcd.clear();
                        return function1();                        
                    }                  




              }
                               
      }
    else{
              
        Serial.print(" Return");
        
        Serial.println();
        //delay(1000);
        return function1();
        
             }      
}
else{

Serial.print("Can not found!!");
Serial.println(); 

}

}}

int ir1(){

    distance_cm1 = mySensor1.distance();
    Serial.print("distance1: ");
    Serial.print(distance_cm1);
    Serial.println();   
    delay(100);
    return distance_cm1;

}
int ir2(){

    distance_cm2 = mySensor2.distance();
    Serial.print("distance2 - ");    
    Serial.print(distance_cm2);
    Serial.println();   
    delay(100);
    return distance_cm2;

}

  

float weight(){

  Serial.print("Weight -  ");   
  w=scale.get_units();
  Serial.print(w);
  Serial.println();  
  delay(10);
  return w;  
}
void display_function1_value(){
  
lcd.setCursor(0,0);
lcd.print(" 18KG oil Cans");

lcd.setCursor(16,0);
lcd.print("Weight : ");


lcd.print(oil_weight);
lcd.print("KG");

lcd.setCursor(8,0);
lcd.print("No of Cans:");
lcd.print(Can_count);

lcd.setCursor(24,0);
lcd.print("Oil Amount:");
lcd.print(Amount_of_oil);
lcd.print("KG");

}
//display the filling state
void display_function1_1value(){
  
lcd.setCursor(0,0);
lcd.print("  Filling.....");

lcd.setCursor(16,0);
lcd.print("Weight : ");


lcd.print(oil_weight);
lcd.print("KG");

lcd.setCursor(8,0);
lcd.print("No of Cans:");
lcd.print(Can_count);

lcd.setCursor(24,0);
lcd.print("Oil Amount:");
lcd.print(Amount_of_oil);
lcd.print("KG");

}

void menu1()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("   << MENU >> ");

  lcd.setCursor(16,0);
  lcd.print("1-18KG oil Cans");

  lcd.setCursor(8,0);
  lcd.print("2-Any Amount KG");
  
  lcd.setCursor(24,0);
  lcd.print("Press v to Down");

   
}

void menu2()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("   << MENU >> ");

  lcd.setCursor(16,0);
  lcd.print("3-Price filling");

  lcd.setCursor(8,0);
  lcd.print("4-fredom ");
  
  lcd.setCursor(24,0);
  lcd.print("Press v to Down");

   
}
void menu3()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("   << MENU >> ");

  lcd.setCursor(16,0);
  lcd.print("5-Any kg");

  lcd.setCursor(8,0);
  lcd.print("6-Price change ");
  
  lcd.setCursor(24,0);
  lcd.print("Press ^ to UP ");

   
}
void function_print1()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("   WELCOME TO ");

  lcd.setCursor(16,0);
  lcd.print("     18 KG");

  lcd.setCursor(8,0);
  lcd.print("  OIL  FILLING ");
  
  lcd.setCursor(24,0);
  lcd.print("    Function");

    
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//function 2



void function2(){
lcd.clear();  
  
  lcd.setCursor(0,0);
  lcd.print("   WELCOME TO ");

  lcd.setCursor(16,0);
  lcd.print(" KG Can ");
  delay(2000);
  function2_3();
  }
void function2_3()
{
  
  lcd.clear();  
  display_function2();  
  function2_4();

  }

  
void return_amount_kg_for_can()
{

  lcd.clear();  
  lcd.setCursor(0,0);
  display_function2(); 
  function2_4();
  
}


void function2_4(){
while(true)  
{
   customKey = customKeypad.getKey();
     
    if (customKey!=NO_KEY)
      DetectButtons2();                            
      //Serial.println(customKey);
              
}
}

void DetectButtons2()

{ 

    if (customKey=='*')
    {
      Serial.println ("Button Clear");
      Number=Num1=Num2=0;
      return return_amount_kg_for_can();
    
    }

    if (customKey == '1') 
    {
      Serial.print ("Button 1"); 

            if (Number==0)
            {
              Number=1;
              display_function2();  
              lcd.print(Number); 
            }   

          else
            {
              Number = (Number*10) + 1; 
              display_function2(); 
              lcd.print(Number);
            }
     
    }


   if (customKey == '4') 

    {
      Serial.println ("Button 4"); 

            if (Number==0)
            {
                Number=4;
                display_function2();  
                lcd.print(Number); }   

            else
            {
                Number = (Number*10) + 4; 
                display_function2();
                lcd.print(Number);

            }
  }

  if (customKey == '7') 

    {
      Serial.println ("Button 7");

          if (Number==0)
          {          
              Number=7;
              display_function2();
              lcd.print(Number); 
          }   

          else
            {
              Number = (Number*10) + 7; 
              display_function2();
              lcd.print(Number);   
          } 
    
    }

 if (customKey == '0')

    {
      Serial.println ("Button 0"); 

            if (Number==0)
            {
              Number=0;
              display_function2(); 
              lcd.print(Number);                    
            }  

            else
            {
              Number = (Number*10) + 0; 
              display_function2();
              lcd.print(Number);
            }
  }

  if (customKey == '2') 

    {
      Serial.println ("Button 2"); 

            if (Number==0)
            {
                  Number=2;
                  display_function2();;  
                  lcd.print(Number); 
            }  

            else
            {
                Number = (Number*10) + 2; 
                display_function2(); 
                lcd.print(Number);    
            }
    }

         if (customKey == '5')

    {
      Serial.println ("Button 5"); 

              if (Number==0)
              {
                  Number=5;
                  display_function2();
                  lcd.print(Number);
              }    

              else
              {
                  Number = (Number*10) + 5; 
                  display_function2();
                  lcd.print(Number);    
              }
    }

         if (customKey == '8')

    {
      Serial.println ("Button 8"); 

                if (Number==0)
                {
                      Number=8;
                      display_function2();
                      lcd.print(Number); 
                }   

                else
                {
                      Number = (Number*10) + 8; 
                      display_function2();
                      lcd.print(Number);
                }  
    } 

      if (customKey == '#')

    {
            Num2=Number;
            Serial.println (Num2);     
            display_function2();
            
        if ( Num2 < 19.1 ){

            oil_kg=Num2;
            function2_1();
            
        } 
        else {
          
              lcd.clear(); 
                
              lcd.setCursor(0,0);
              lcd.print(" Increse Limit ");

              lcd.setCursor(16,0);
              lcd.print("Press A to return ");
              
              while(true){
                
              char customKey = customKeypad.getKey();
                
                  if (customKey){
                    
                        tone(buzzer, 1000); 
                        delay(50);       
                        noTone(buzzer);     
                        Serial.println(customKey);

                    if(customKey=='A'){
                      
                              Num2=0;
                              oil_kg=0; 
                              Number=0;
                              return_amount_kg_for_can();
                    }                 
                    
                  }  
                  }   

              }
      
    }

         if (customKey == '3')

    {
      Serial.println ("Button 3"); 

                if (Number==0)
                {
                      Number=3;
                      display_function2();
                      lcd.print(Number);  
                }  

                else
                {
                      Number = (Number*10) + 3; 
                      display_function2();
                      lcd.print(Number);    
                }
    }

       if (customKey == '6')

    {
      Serial.println ("Button 6"); 

              if (Number==0)
              {
                  Number=6;
                  display_function2();
                  lcd.print(Number);  
              }  

              else
              {
                  Number = (Number*10) + 6; 
                  display_function2();
                  lcd.print(Number);   

              }
    }

         if (customKey == '9')

    {
      Serial.println ("Button 9");

            if (Number==0)
            {
                Number=9;
                display_function2();
                lcd.print(Number);  
            }  

            else
            {
                Number = (Number*10) + 9; 
                display_function2();
                lcd.print(Number);  
            } 
    }
      if (customKey == 'D'){
              return start();
        }     
}

void display_function2(){
  
  lcd.setCursor(0,0);
  lcd.print("Amount of kg:");

}

void function2_1(){

lcd.clear();
function_print2();
delay(2000);
function2_2();

}
void function2_2(){
lcd.clear();  
while(true){

//delay(2000);
char customKey = customKeypad.getKey();
   
 if (customKey){
         
          Serial.println(customKey);
      if(customKey=='D'){
                lcd.clear();
                lcd.setCursor(0,0);
                lcd.print("Press OK to exit");
                                
                lcd.setCursor(16,0);
                lcd.print("No of Cans:");
                lcd.print(Can_count);

                lcd.setCursor(8,0);
                lcd.print("Oil Amount:");
                lcd.print(Amount_of_oil);
                //lcd.print("KG");

                        
                lcd.setCursor(24,0);
                lcd.print("Emg Oil:");
                lcd.print(emergency_exit_oil);
                lcd.print("KG");
        
            while(true){

              char customKey = customKeypad.getKey();

                if (customKey){
                        Serial.println(customKey);
                                                     
                    if(customKey=='#'){
                      Can_count=0;
                      Amount_of_oil=0; 
                      emergency_exit_oil=0;
                      emergency_exit_cane=0;
                      Num2=0;
                      oil_kg=0; 
                      Number=0;                                                                  
                            return start();
                    }  

                }              


            }          

      } 
      if(customKey=='C'){
        scale.tare(); 
      }         
  }

   
distance1=ir1();
distance2=ir2();
oil_weight=weight();

display_function2_value();

//can alignment and mouth alignment
if ( distance1 < 11  && distance1 > 9  && distance2 < 13 && distance2 >10 && oil_weight > 0.6 && oil_weight < 1.5 ){

  
      
    lcd.clear();
    lcd.setCursor(16,0);
    lcd.print(" Wait 5 Seconds"); 
    lcd.setCursor(8,0);
    lcd.print(" Identifying....");             

    Serial.print(" Can found");
    Serial.println();

    delay(5000);

    distance1=ir1();
    distance2=ir2();
   // oil_weight=weight();
     

     Serial.print(distance1);
     Serial.print(distance2);
      //delay(1000);

    if(distance1 < 11  && distance1 > 9  && distance2 < 13 && distance2 >10 && oil_weight > 0.6 && oil_weight < 1.5  ){
      
            lcd.clear();

      

            //oil_weight=weight();      
              
            Serial.print("Still Oil Can is there!!");
            Serial.println();
            Serial.print(oil_weight);

           /* lcd.setCursor(0,0);
            lcd.print("  function1 ");

            lcd.setCursor(16,0);
            lcd.print("Weight -");
                        
            lcd.print(oil_weight);
            lcd.print("KG");

            lcd.setCursor(8,0);
            lcd.print("Amount of Can-");
            lcd.print(Can_count);

            lcd.setCursor(24,0);
            lcd.print("Amount of Oil-");
            lcd.print(Amount_of_oil);
            lcd.print("KG");*/
            
            //delay(1000);
            Can_weight=oil_weight; 
            Serial.print(Can_weight);
            //delay(3000); 

          //compare the can weight to 19.1 or (can weight+18kg)                    
          while( oil_weight < (oil_kg+Can_weight) && oil_weight < 19.1  ){
    
                  distance1=ir1();
                  distance2=ir2();
                  oil_weight=weight();
                                    
                  Last_oil_weight=oil_weight;
                  display_function2_1value();

                  
              if(distance1 < 11  && distance1 > 9  && distance2 < 13 && distance2 >10 ){
                
                    
                    display_function1_1value();
                    Serial.print(" Oil is filling to Can");
                    Serial.println();
                    digitalWrite(solenoidvalve,LOW);


              } 

              else{
                digitalWrite(solenoidvalve,HIGH);
                emergency_exit_cane++;                
                emergency_exit_oil+=Last_oil_weight;
                lcd.clear();                

                    while(true){
                   
                    
                    Serial.print("Emergency Out");
                    Serial.println();
                    Serial.print(Last_oil_weight);
                    Serial.println(); 

                    lcd.setCursor(0,0);
                    lcd.print("Emergency Out!!");
                    
                      lcd.setCursor(16,0);
                      lcd.print("Filled Amount");

                      lcd.setCursor(8,0);
                      lcd.print(": ");
                      lcd.print(Last_oil_weight);
                      lcd.print("KG");                      

                        lcd.setCursor(24,0);
                        lcd.print("To continue-> E");
                                               
                    
                      tone(buzzer, 1000); 
                      delay(500);       
                      noTone(buzzer);     
                      delay(300);                      
                                          

 
                          char customKey = customKeypad.getKey();
   
 
  
                            if (customKey){
                             Serial.println(customKey);
                                                           
                               if(customKey=='C'){
                                      lcd.clear();                                  
                                      return function2_2();
                                  }   
                                  }
                               }                    
                                        
                                        
                    
                                                                                      
                    
                  }                            
            } 
              digitalWrite(solenoidvalve,HIGH);             
              lcd.clear();
              Serial.print("Oil Can successfully filled!!");
              Serial.println();
              
              Can_count++;
              Amount_of_oil+=oil_kg; 
                                                                     
                lcd.setCursor(0,0);
                lcd.print("Oil Can filled!!");
                                
                lcd.setCursor(8,0);
                lcd.print("No of Cans:");
                lcd.print(Can_count);

                lcd.setCursor(24,0);
                lcd.print("Oil Amount:");
                lcd.print(Amount_of_oil);
                lcd.print(" KG");    
                                           
              while(true){
                 Serial.print("Buzer!!");
                  Serial.println();
                      tone(buzzer, 1000); 
                      delay(1000);       
                      noTone(buzzer);     
                      delay(1000);                   
                  distance1=ir1();
                  distance2=ir2();                                        

                    if(distance1 > 9   && distance2 > 10  ){
                      lcd.clear();
                        return function2_2();                        
                    }                  




              }
                               
      }
    else{
              
        Serial.print(" Return");
        
        Serial.println();
        //delay(1000);
        return function2_2();
        
             }      
}
else{

Serial.print("Can not found!!");
Serial.println(); 

}

} 
}
void function_print2 ()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("   WELCOME TO ");

  lcd.setCursor(16,0);
  lcd.print("     ");
  lcd.print(oil_kg);
  lcd.print("KG");

  lcd.setCursor(8,0);
  lcd.print("  OIL  FILLING ");
  
  lcd.setCursor(24,0);
  lcd.print("    Function");

    
}
void display_function2_value(){
  
lcd.setCursor(0,0);
lcd.print(" ");
lcd.print(oil_kg);
lcd.print("KG oil Cans");

lcd.setCursor(16,0);
lcd.print("Weight : ");


lcd.print(oil_weight);
lcd.print("KG");

lcd.setCursor(8,0);
lcd.print("No of Cans:");
lcd.print(Can_count);

lcd.setCursor(24,0);
lcd.print("Oil Amount:");
lcd.print(Amount_of_oil);
lcd.print("KG");

}
//display the filling state
void display_function2_1value(){
  
lcd.setCursor(0,0);
lcd.print("  Filling.....");

lcd.setCursor(16,0);
lcd.print("Weight : ");


lcd.print(oil_weight);
lcd.print("KG");

lcd.setCursor(8,0);
lcd.print("No of Cans:");
lcd.print(Can_count);

lcd.setCursor(24,0);
lcd.print("Oil Amount:");
lcd.print(Amount_of_oil);
lcd.print("KG");

}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//function 3



void function3(){
lcd.clear();  
  
  lcd.setCursor(0,0);
  lcd.print("   WELCOME TO ");

  lcd.setCursor(16,0);
  lcd.print("Price filling");
  delay(2000);
  function3_3();
  }
  
void function3_3()
{
  
  lcd.clear();  
  display_function3();  
  function3_4();

  }

  
void return_amount_money()
{

  lcd.clear();  
  lcd.setCursor(0,0);
  display_function3(); 
  function3_4();
  
}


void function3_4(){
while(true)  
{
   customKey = customKeypad.getKey();
     
    if (customKey!=NO_KEY)
      DetectButtons3();                            
      //Serial.println(customKey);
              
}
}

void DetectButtons3()

{ 

    if (customKey=='*')
    {
      Serial.println ("Button Clear");
      Number=Num1=Num2=0;
      return return_amount_money();
    
    }

    if (customKey == '1') 
    {
      Serial.print ("Button 1"); 

            if (Number==0)
            {
              Number=1;
              display_function3();  
              lcd.print(Number); 
            }   

          else
            {
              Number = (Number*10) + 1; 
              display_function3(); 
              lcd.print(Number);
            }
     
    }


   if (customKey == '4') 

    {
      Serial.println ("Button 4"); 

            if (Number==0)
            {
                Number=4;
                display_function3();  
                lcd.print(Number); }   

            else
            {
                Number = (Number*10) + 4; 
                display_function3();
                lcd.print(Number);

            }
  }

  if (customKey == '7') 

    {
      Serial.println ("Button 7");

          if (Number==0)
          {          
              Number=7;
              display_function3();
              lcd.print(Number); 
          }   

          else
            {
              Number = (Number*10) + 7; 
              display_function3();
              lcd.print(Number);   
          } 
    
    }

 if (customKey == '0')

    {
      Serial.println ("Button 0"); 

            if (Number==0)
            {
              Number=0;
              display_function3(); 
              lcd.print(Number);                    
            }  

            else
            {
              Number = (Number*10) + 0; 
              display_function3();
              lcd.print(Number);
            }
  }

  if (customKey == '2') 

    {
      Serial.println ("Button 2"); 

            if (Number==0)
            {
                  Number=2;
                  display_function3();;  
                  lcd.print(Number); 
            }  

            else
            {
                Number = (Number*10) + 2; 
                display_function3(); 
                lcd.print(Number);    
            }
    }

         if (customKey == '5')

    {
      Serial.println ("Button 5"); 

              if (Number==0)
              {
                  Number=5;
                  display_function3();
                  lcd.print(Number);
              }    

              else
              {
                  Number = (Number*10) + 5; 
                  display_function3();
                  lcd.print(Number);    
              }
    }

         if (customKey == '8')

    {
      Serial.println ("Button 8"); 

                if (Number==0)
                {
                      Number=8;
                      display_function3();
                      lcd.print(Number); 
                }   

                else
                {
                      Number = (Number*10) + 8; 
                      display_function3();
                      lcd.print(Number);
                }  
    } 

      if (customKey == '#')

    {
          Num2=Number;
          Serial.println (Num2);
          
          display_function3();
          lcd.print(Num2);
          amount_of_kg_for_price=Num2/oil_price;
          amount_of_cane_for_price=amount_of_kg_for_price/18;
          remaining_kg=amount_of_kg_for_price % 18;         
        
          function3_1();
    }

         if (customKey == '3')

    {
      Serial.println ("Button 3"); 

                if (Number==0)
                {
                      Number=3;
                      display_function3();
                      lcd.print(Number);  
                }  

                else
                {
                      Number = (Number*10) + 3; 
                      display_function3();
                      lcd.print(Number);    
                }
    }

       if (customKey == '6')

    {
      Serial.println ("Button 6"); 

              if (Number==0)
              {
                  Number=6;
                  display_function3();
                  lcd.print(Number);  
              }  

              else
              {
                  Number = (Number*10) + 6; 
                  display_function3();
                  lcd.print(Number);   

              }
    }

         if (customKey == '9')

    {
      Serial.println ("Button 9");

            if (Number==0)
            {
                Number=9;
                display_function3();
                lcd.print(Number);  
            }  

            else
            {
                Number = (Number*10) + 9; 
                display_function3();
                lcd.print(Number);  
            } 
    }
      if (customKey == 'D'){
              return start();
        }       
}

void display_function3(){
  
  lcd.setCursor(0,0);
  lcd.print("Amount of money ");

}

void function3_1(){

lcd.clear();
function_print3();
delay(2000);
function3_2();

}
void function3_2(){
lcd.clear();  
while(true){

char customKey = customKeypad.getKey();
   
 if (customKey){
         
          Serial.println(customKey);
      if(customKey=='D'){
                lcd.clear();
                lcd.setCursor(0,0);
                lcd.print("Press OK to exit");
                                
                lcd.setCursor(16,0);
                lcd.print("No of Cans:");
                lcd.print(Can_count);

                lcd.setCursor(8,0);
                lcd.print("Oil Amount:");
                lcd.print(Amount_of_oil);
                //lcd.print("KG");

                        
                lcd.setCursor(24,0);
                lcd.print("Emg Oil:");
                lcd.print(emergency_exit_oil);
                lcd.print("KG");
        
            while(true){

              char customKey = customKeypad.getKey();

                if (customKey){
                        Serial.println(customKey);
                                                     
                    if(customKey=='#'){
                      Can_count=0;
                      Amount_of_oil=0; 
                      emergency_exit_oil=0;
                      emergency_exit_cane=0;
                      Num2=0;
                      oil_kg=0; 
                      Number=0;                                                                  
                            return start();
                    }  

                }              


            }          

      } 
      if(customKey=='C'){
        scale.tare(); 
      }         
  }
   
distance1=ir1();
distance2=ir2();
oil_weight=weight();

if (amount_of_cane_for_price > 0){

display_function3_value();


if ( distance1 < 11  && distance1 > 9  && distance2 < 13 && distance2 >10 && oil_weight > 0.6 && oil_weight < 1.5){

    lcd.clear();
    lcd.setCursor(16,0);
    lcd.print(" Wait 5 Seconds"); 
    lcd.setCursor(8,0);
    lcd.print(" Identifying....");             


    Serial.print(" Can found");
    Serial.println();

    delay(5000);

    distance1=ir1();
    distance2=ir2();
    
     

     Serial.print(distance1);
     Serial.print(distance2);
      //delay(1000);

    if( distance1 < 11  && distance1 > 9  && distance2 < 13 && distance2 >10 && oil_weight > 0.6 && oil_weight < 1.5 ){
      
            lcd.clear();

      

            oil_weight=weight();      
              
            Serial.print("Still Oil Can is there!!");
            Serial.println();
            Serial.print(oil_weight);

           
            Can_weight=oil_weight; 
            Serial.print(Can_weight);
            //delay(3000); 

          while( oil_weight < (18 + Can_weight) && oil_weight < 19.1  ){
    
                  distance1=ir1();
                  distance2=ir2();
                  oil_weight=weight();
                                    
                  Last_oil_weight=oil_weight;
                  display_function3_1value();          
                  
              if(distance1 < 11  && distance1 > 9  && distance2 < 13 && distance2 >10 ){
                
                    
                    display_function1_1value();
                    Serial.print(" Oil is filling to Can");
                    Serial.println();
                    digitalWrite(solenoidvalve,LOW);


              } 

              else{
                digitalWrite(solenoidvalve,HIGH);
                emergency_exit_cane++;                
                emergency_exit_oil+=Last_oil_weight;                                
                lcd.clear();                

                    while(true){
                   
                    Serial.print("Emergency Out");
                    Serial.println();
                    Serial.print(Last_oil_weight);
                    Serial.println(); 

                    lcd.setCursor(0,0);
                    lcd.print("Emergency Out!!");
                    
                      lcd.setCursor(16,0);
                      lcd.print("Filled Amount");

                      lcd.setCursor(8,0);
                      lcd.print(": ");
                      lcd.print(Last_oil_weight);
                      lcd.print("KG");                      

                        lcd.setCursor(24,0);
                        lcd.print("To continue-> E");
                                               
                    
                      tone(buzzer, 1000); 
                      delay(500);       
                      noTone(buzzer);     
                      delay(300);                      
                                          

 
                          char customKey = customKeypad.getKey();
   
 
  
                            if (customKey){
                             Serial.println(customKey);
                                                           
                               if(customKey=='C'){
                                      lcd.clear();                                  
                                      return function3_2();
                                  }   
                                  }
                               }            
                                        
                                        
                    
                                                                                      
                    
                  }                            
            } 
              digitalWrite(solenoidvalve,HIGH);             
              lcd.clear();
              Serial.print("Oil Can successfully filled!!");
              Serial.println();
              Can_count++;
              Amount_of_oil=Amount_of_oil+18;
              amount_of_cane_for_price--;                                                                      

                lcd.setCursor(0,0);
                lcd.print("Oil Can filled!!");
                                
                lcd.setCursor(8,0);
                lcd.print("No of Cans:");
                lcd.print(Can_count);

                lcd.setCursor(24,0);
                lcd.print("Oil Amount:");
                lcd.print(Amount_of_oil);
                lcd.print(" KG");  
                                           
              while(true){
                 Serial.print("Buzer!!");
                  Serial.println();
                      tone(buzzer, 1000); 
                      delay(1000);       
                      noTone(buzzer);     
                      delay(1000);                   
                  distance1=ir1();
                  distance2=ir2();                                        

                    if(distance1 > 9   && distance2 > 10 ){
                      lcd.clear();
                        return function3_2();                        
                    }                  




              }
                               
      }
    else{
              
        Serial.print(" Return");
        
        Serial.println();
        //delay(1000);
        return function3_2();
        
             }      
}
else{

Serial.print("Can not found!!");
Serial.println(); 

}

}
else{
display_function3_value();
Serial.println("function3");
 

if ( distance1 < 11  && distance1 > 9  && distance2 < 13 && distance2 >10 && oil_weight > 0.6 && oil_weight < 1.5 ){

  
      
    lcd.clear();
    lcd.setCursor(16,0);
    lcd.print(" Wait 5 Seconds"); 
    lcd.setCursor(8,0);
    lcd.print(" Identifying....");        

    Serial.print(" Can found");
    Serial.println();

    delay(5000);

    distance1=ir1();
    distance2=ir2();
    
     

     Serial.print(distance1);
     Serial.print(distance2);
      //delay(1000);

    if( distance1 < 11  && distance1 > 9  && distance2 < 13 && distance2 >10 && oil_weight > 0.6 && oil_weight < 1.5 ){
      
            lcd.clear();

      

            oil_weight=weight();      
              
            Serial.print("Still Oil Can is there!!");
            Serial.println();
            Serial.print(oil_weight);

           
            Can_weight=oil_weight; 
            Serial.print(Can_weight);
            //delay(3000); 

          while( oil_weight < (remaining_kg + Can_weight) && oil_weight < 19.1  ){
    
                  distance1=ir1();
                  distance2=ir2();
                  oil_weight=weight();
                                    
                  Last_oil_weight=oil_weight;
                  display_function3_1value();                 
                  
              if(distance1 < 14  && distance1 > 9  && distance2 < 15 && distance2 >9 ){
                
                    
                    display_function3_1value();
                    Serial.print(" Oil is filling to Can");
                    Serial.println();
                    digitalWrite(solenoidvalve,LOW);


              } 

              else{
                digitalWrite(solenoidvalve,HIGH);
                emergency_exit_cane++;                
                emergency_exit_oil+=Last_oil_weight;                
                lcd.clear();                

                    while(true){
                   
                    
                    Serial.print("Emergency Out");
                    Serial.println();
                    Serial.print(Last_oil_weight);
                    Serial.println(); 

                    lcd.setCursor(0,0);
                    lcd.print("Emergency Out!!");
                    
                      lcd.setCursor(16,0);
                      lcd.print("Filled Amount");

                      lcd.setCursor(8,0);
                      lcd.print(": ");
                      lcd.print(Last_oil_weight);
                      lcd.print("KG");                      

                        lcd.setCursor(24,0);
                        lcd.print("To continue-> E");
                                               
                    
                      tone(buzzer, 1000); 
                      delay(500);       
                      noTone(buzzer);     
                      delay(300);                      
                                          

 
                          char customKey = customKeypad.getKey();
   
 
  
                            if (customKey){
                             Serial.println(customKey);
                                                           
                               if(customKey=='C'){
                                      lcd.clear();                                  
                                      return function3_2();
                                  }   
                                  }
                               }         
                                        
                    
                                                                                      
                    
                  }                            
            } 
              digitalWrite(solenoidvalve,HIGH);             
              lcd.clear();
              Serial.print("Oil Can successfully filled!!");
              Serial.println();
              
                                                                      
                lcd.setCursor(0,0);
                lcd.print("Oil Can  filled!!");
                                
                lcd.setCursor(16,0);
                lcd.print(Can_count);                
                lcd.print("Oil Can and");
                

                lcd.setCursor(8,0);
                lcd.print("   ");
                lcd.print(remaining_kg);
                lcd.print("KG Oil");    
                
                lcd.setCursor(24,0);               
                lcd.print("successfully filled!!");                
                                           
              while(true){
                 Serial.print("Buzer!!");
                  Serial.println();
                      tone(buzzer, 1000); 
                      delay(1000);       
                      noTone(buzzer);     
                      delay(1000);  
                                       
                          char customKey = customKeypad.getKey();
   
 
  
                            if (customKey){
                             Serial.println(customKey);
                                                           
                               if(customKey=='C'){
                                      lcd.clear();                                  
                                      return function3_3();
                                  }   
                                  }



              }
                               
      }
    else{
              
        Serial.print(" Return");
        
        Serial.println();
        //delay(1000);
        return function3_2();
        
             }      
}
else{

Serial.print("Can not found!!");
Serial.println(); 

}


  
}

}}
void function_print3 ()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("  You can fill ");

  lcd.setCursor(16,0);
  lcd.print("     ");
  lcd.print(amount_of_cane_for_price);
  lcd.print("Can and");

  lcd.setCursor(8,0);
  lcd.print("   ");
  lcd.print(remaining_kg);
  lcd.print(" KG Oil");  
  
  
  
    
}
void display_function3_value(){
  
lcd.setCursor(0,0);
lcd.print(" Price Filling ");

lcd.setCursor(16,0);
lcd.print("Weight : ");


lcd.print(oil_weight);
lcd.print("KG");

lcd.setCursor(8,0);
lcd.print("No of Cans:");
lcd.print(Can_count);

lcd.setCursor(24,0);
lcd.print("Oil Amount:");
lcd.print(Amount_of_oil);
lcd.print("KG");

}
//display the filling state
void display_function3_1value(){
  
lcd.setCursor(0,0);
lcd.print("  Filling.....");

lcd.setCursor(16,0);
lcd.print("Weight : ");


lcd.print(oil_weight);
lcd.print("KG");

lcd.setCursor(8,0);
lcd.print("No of Cans:");
lcd.print(Can_count);

lcd.setCursor(24,0);
lcd.print("Oil Amount:");
lcd.print(Amount_of_oil);
lcd.print("KG");

}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//function4

void function4(){

lcd.clear();
function4_print();
delay(2000);
lcd.clear();
function4_1();

}
void function4_1(){
  
while(true){

char customKey = customKeypad.getKey();
   
 if (customKey){
         
          Serial.println(customKey);
      if(customKey=='D'){
                lcd.clear();
                lcd.setCursor(0,0);
                lcd.print("Press OK to exit");
                                
                lcd.setCursor(16,0);
                lcd.print("No of Cans:");
                lcd.print(Can_count);

                lcd.setCursor(8,0);
                lcd.print("Oil Amount:");
                lcd.print(Amount_of_oil);
                //lcd.print("KG");

                        
                lcd.setCursor(24,0);
                lcd.print("Emg Oil:");
                lcd.print(emergency_exit_oil);
                lcd.print("KG");
        
            while(true){

              char customKey = customKeypad.getKey();

                if (customKey){
                        Serial.println(customKey);
                                                     
                    if(customKey=='#'){
                      Can_count=0;
                      Amount_of_oil=0; 
                      emergency_exit_oil=0;
                      emergency_exit_cane=0;
                      Num2=0;
                      oil_kg=0; 
                      Number=0;                                                                  
                            return start();
                    }  

                }              


            }          

      } 
      if(customKey=='C'){
        scale.tare(); 
      }         
  }

   
distance1=ir1();
distance2=ir2();
oil_weight=weight();

display_function4_value();

//can alignment and mouth alignment
if ( distance1 < 11  && distance1 > 9  && distance2 < 13 && distance2 >10 && oil_weight > 0.6 && oil_weight < 1.5 ){

  
      
    lcd.clear();
    lcd.setCursor(16,0);
    lcd.print(" Wait 5 Seconds"); 
    lcd.setCursor(8,0);
    lcd.print(" Identifying....");             

    Serial.print(" Can found");
    Serial.println();

    delay(5000);

    distance1=ir1();
    distance2=ir2();
   // oil_weight=weight();
     

     Serial.print(distance1);
     Serial.print(distance2);
      //delay(1000);

    if(distance1 < 11  && distance1 > 9  && distance2 < 13 && distance2 >10 && oil_weight > 0.6 && oil_weight < 1.5  ){
      
            lcd.clear();

      

            //oil_weight=weight();      
              
            Serial.print("Still Oil Can is there!!");
            Serial.println();
            Serial.print(oil_weight);

           /* lcd.setCursor(0,0);
            lcd.print("  function1 ");

            lcd.setCursor(16,0);
            lcd.print("Weight -");
                        
            lcd.print(oil_weight);
            lcd.print("KG");

            lcd.setCursor(8,0);
            lcd.print("Amount of Can-");
            lcd.print(Can_count);

            lcd.setCursor(24,0);
            lcd.print("Amount of Oil-");
            lcd.print(Amount_of_oil);
            lcd.print("KG");*/
            
            //delay(1000);
            Can_weight=oil_weight; 
            Serial.print(Can_weight);
            //delay(3000); 

          //compare the can weight to 19.1 or (can weight+18kg)                    
          while( oil_weight < (oil_kg+Can_weight) && oil_weight < 19.1  ){
    
                  distance1=ir1();
                  distance2=ir2();
                  oil_weight=weight();
                                    
                  Last_oil_weight=oil_weight;
                  real_oil_weight=oil_weight-Can_weight;
                  oil_price_now=real_oil_weight*oil_price;                  
                  display_function4_1value();

                  
              if(distance1 < 11  && distance1 > 9  && distance2 < 13 && distance2 >10 ){
                
                    
                    display_function4_1value();
                    Serial.print(" Oil is filling to Can");
                    Serial.println();
                    digitalWrite(solenoidvalve1,LOW);


              } 

              else{
                digitalWrite(solenoidvalve1,HIGH);
                emergency_exit_cane++;                
                emergency_exit_oil+=Last_oil_weight;
                lcd.clear();                

                    while(true){
                   
                    
                    Serial.print("Emergency Out");
                    Serial.println();
                    Serial.print(Last_oil_weight);
                    Serial.println(); 

                    lcd.setCursor(0,0);
                    lcd.print("   Can Out!!!");
                    
                      lcd.setCursor(16,0);
                      lcd.print("Filled Amount:");
                      lcd.print(real_oil_weight);                      

                      lcd.setCursor(8,0);
                      lcd.print("Price:");
                      lcd.print(oil_price_now);                      

                        lcd.setCursor(24,0);
                        lcd.print("To continue-> E");
                                               
                    
                      tone(buzzer, 1000); 
                      delay(500);       
                      noTone(buzzer);     
                      delay(300);                      
                                          

 
                          char customKey = customKeypad.getKey();
   
 
  
                            if (customKey){
                             Serial.println(customKey);
                                                           
                               if(customKey=='C'){
                                      lcd.clear();                                  
                                      return function4_1();
                                  }   
                                  }
                               }                    
                                        
                                        
                    
                                                                                      
                    
                  }                            
            } 
              digitalWrite(solenoidvalve,HIGH);             
              lcd.clear();
              Serial.print("Oil Can successfully filled!!");
              Serial.println();
              
              Can_count++;
              Amount_of_oil+=18; 
                                                                     
                lcd.setCursor(0,0);
                lcd.print("Oil Can filled!!");
                                
                lcd.setCursor(16,0);
                lcd.print("Oil Amount:");
                lcd.print(real_oil_weight);
                
                lcd.setCursor(8,0);
                lcd.print("Price");
                lcd.print(oil_price_now);                

                lcd.setCursor(24,0);
                lcd.print("  Get the Can!");
   
                                           
              while(true){
                 Serial.print("Buzer!!");
                  Serial.println();
                      tone(buzzer, 1000); 
                      delay(1000);       
                      noTone(buzzer);     
                      delay(1000);                   
                  distance1=ir1();
                  distance2=ir2();                                        

                    if(distance1 > 9   && distance2 > 10  ){
                      lcd.clear();
                        return function4_1();                        
                    }                  




              }
                               
      }
    else{
              
        Serial.print(" Return");
        
        Serial.println();
        //delay(1000);
        return function2_2();
        
             }      
}
else{

Serial.print("Can not found!!");
Serial.println(); 

}

}}

void function4_print()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("   WELCOME TO ");

  lcd.setCursor(16,0);
  lcd.print("Fredom");

  lcd.setCursor(8,0);
  lcd.print("  OIL  FILLING ");
  
  lcd.setCursor(24,0);
  lcd.print("    Function");

    
}
void display_function4_value(){
  
lcd.setCursor(0,0);
lcd.print("  Freedom ");

lcd.setCursor(8,0);
lcd.print(">>Put the Can!<<");

}
void display_function4_1value(){
  
  lcd.setCursor(0,0);
  lcd.print("  Freedom ");

  lcd.setCursor(16,0);
  lcd.print("Weight -");


  lcd.print(oil_weight);
  lcd.print("KG");
 
  lcd.setCursor(8,0);
  lcd.print("Price");
  lcd.print(oil_price_now);

  lcd.setCursor(24,0);
  lcd.print("Press Push Button");  

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//function5

void function5(){

  lcd.clear();  
  lcd.setCursor(0,0);
  lcd.print("   WELCOME TO ");

  lcd.setCursor(16,0);
  lcd.print("Any KG");
  delay(2000);
  function5_3();
 
  }

  
void function5_3()
  {
  
  lcd.clear();  
  display_function5(); 
  function5_4();
  
  }


void return_amount_any_kg()
{

  lcd.clear();  
  display_function5(); 
  function5_4();
  
  }
  

void function5_4(){
while(true)  
{
   customKey = customKeypad.getKey();
     
    if (customKey!=NO_KEY)
      DetectButtons5();                            
      //Serial.println(customKey);
              
}
}

void DetectButtons5()

{ 

    if (customKey=='*')
    {
      Serial.println ("Button Clear");
      Number=Num1=Num2=0;
      return return_amount_any_kg();
    
    }

    if (customKey == '1') 
    {
      Serial.print ("Button 1"); 

            if (Number==0)
            {
              Number=1;
              display_function5();  
              lcd.print(Number); 
            }   

          else
            {
              Number = (Number*10) + 1; 
              display_function5(); 
              lcd.print(Number);
            }
     
    }


   if (customKey == '4') 

    {
      Serial.println ("Button 4"); 

            if (Number==0)
            {
                Number=4;
                display_function5();  
                lcd.print(Number); }   

            else
            {
                Number = (Number*10) + 4; 
                display_function5();
                lcd.print(Number);

            }
  }

  if (customKey == '7') 

    {
      Serial.println ("Button 7");

          if (Number==0)
          {          
              Number=7;
              display_function5();
              lcd.print(Number); 
          }   

          else
            {
              Number = (Number*10) + 7; 
              display_function5();
              lcd.print(Number);   
          } 
    
    }

 if (customKey == '0')

    {
      Serial.println ("Button 0"); 

            if (Number==0)
            {
              Number=0;
              display_function5(); 
              lcd.print(Number);                    
            }  

            else
            {
              Number = (Number*10) + 0; 
              display_function5();
              lcd.print(Number);
            }
  }

  if (customKey == '2') 

    {
      Serial.println ("Button 2"); 

            if (Number==0)
            {
                  Number=2;
                  display_function5();;  
                  lcd.print(Number); 
            }  

            else
            {
                Number = (Number*10) + 2; 
                display_function5(); 
                lcd.print(Number);    
            }
    }

         if (customKey == '5')

    {
      Serial.println ("Button 5"); 

              if (Number==0)
              {
                  Number=5;
                  display_function5();
                  lcd.print(Number);
              }    

              else
              {
                  Number = (Number*10) + 5; 
                  display_function5();
                  lcd.print(Number);    
              }
    }

         if (customKey == '8')

    {
      Serial.println ("Button 8"); 

                if (Number==0)
                {
                      Number=8;
                      display_function5();
                      lcd.print(Number); 
                }   

                else
                {
                      Number = (Number*10) + 8; 
                      display_function5();
                      lcd.print(Number);
                }  
    } 

      if (customKey == '#')

    {
      Serial.println ("Button Equal"); 
    
            Num2=Number;
            Serial.println (Num2);
                    
            display_function5();
            lcd.print(Num2);
            any_amount_of_kg=Num2;
            any_amount_of_can=any_amount_of_kg/18;
            remaining_kg=any_amount_of_kg % 18;         
          
            function5_1();
    }

         if (customKey == '3')

    {
      Serial.println ("Button 3"); 

                if (Number==0)
                {
                      Number=3;
                      display_function5();
                      lcd.print(Number);  
                }  

                else
                {
                      Number = (Number*10) + 3; 
                      display_function5();
                      lcd.print(Number);    
                }
    }

       if (customKey == '6')

    {
      Serial.println ("Button 6"); 

              if (Number==0)
              {
                  Number=6;
                  display_function5();
                  lcd.print(Number);  
              }  

              else
              {
                  Number = (Number*10) + 6; 
                  display_function5();
                  lcd.print(Number);   

              }
    }

         if (customKey == '9')

    {
      Serial.println ("Button 9");

            if (Number==0)
            {
                Number=9;
                display_function5();
                lcd.print(Number);  
            }  

            else
            {
                Number = (Number*10) + 9; 
                display_function5();
                lcd.print(Number);  
            } 
    }
          if (customKey == 'D'){
              return start();
        }   
}

void display_function5(){
  
  lcd.setCursor(0,0);
  lcd.print("Amount of kg");

}

void function5_1(){

lcd.clear();
function_print5();
delay(2000);
function5_2();

}
void function5_2(){
  
char customKey = customKeypad.getKey();
   
 if (customKey){
         
          Serial.println(customKey);
      if(customKey=='D'){
                lcd.clear();
                lcd.setCursor(0,0);
                lcd.print("Press OK to exit");
                                
                lcd.setCursor(16,0);
                lcd.print("No of Cans:");
                lcd.print(Can_count);

                lcd.setCursor(8,0);
                lcd.print("Oil Amount:");
                lcd.print(Amount_of_oil);
                //lcd.print("KG");

                        
                lcd.setCursor(24,0);
                lcd.print("Emg Oil:");
                lcd.print(emergency_exit_oil);
                lcd.print("KG");
        
            while(true){

              char customKey = customKeypad.getKey();

                if (customKey){
                        Serial.println(customKey);
                                                     
                    if(customKey=='#'){
                      Can_count=0;
                      Amount_of_oil=0; 
                      emergency_exit_oil=0;
                      emergency_exit_cane=0;
                      Num2=0;
                      oil_kg=0; 
                      Number=0;                                                                  
                            return start();
                    }  

                }              


            }          

      } 
      if(customKey=='C'){
        scale.tare(); 
      }         
  }

   
distance1=ir1();
distance2=ir2();
oil_weight=weight();

if (any_amount_of_can > 0){

display_function5_value();


if ( distance1 < 11  && distance1 > 9  && distance2 < 13 && distance2 >10 && oil_weight > 0.6 && oil_weight < 1.5 ){

  
      
    lcd.clear();
    lcd.setCursor(16,0);
    lcd.print(" Wait 5 Seconds"); 
    lcd.setCursor(8,0);
    lcd.print(" Identifying....");       

    Serial.print(" Can found");
    Serial.println();

    delay(5000);

    distance1=ir1();
    distance2=ir2();
    
     

     Serial.print(distance1);
     Serial.print(distance2);
      //delay(1000);

    if( distance1 < 11  && distance1 > 9  && distance2 < 13 && distance2 >10 && oil_weight > 0.6 && oil_weight < 1.5 ){
      
            lcd.clear();

      

            oil_weight=weight();      
              
            Serial.print("Still Oil Can is there!!");
            Serial.println();
            Serial.print(oil_weight);

           
            Can_weight=oil_weight; 
            Serial.print(Can_weight);
            //delay(3000); 

          while( oil_weight < (18 + Can_weight) && oil_weight < 19.1  ){
    
                  distance1=ir1();
                  distance2=ir2();
                  oil_weight=weight();
                                    
                  Last_oil_weight=oil_weight;
                  display_function1_1value();                  
                  
              if(distance1 < 14  && distance1 > 9  && distance2 < 15 && distance2 >9 ){
                
                    
                    display_function1_1value();
                    Serial.print(" Oil is filling to Can");
                    Serial.println();
                    digitalWrite(solenoidvalve,LOW);


              } 

              else{
                digitalWrite(solenoidvalve,HIGH);
                emergency_exit_cane++;                
                emergency_exit_oil+=Last_oil_weight;                
                lcd.clear();                

                    while(true){
                   
                    
                    Serial.print("Emergency Out");
                    Serial.println();
                    Serial.print(Last_oil_weight);
                    Serial.println(); 

                    lcd.setCursor(0,0);
                    lcd.print("Emergency Out!!");
                    
                      lcd.setCursor(16,0);
                      lcd.print("Filled Amount");

                      lcd.setCursor(8,0);
                      lcd.print(": ");
                      lcd.print(Last_oil_weight);
                      lcd.print("KG");                      

                        lcd.setCursor(24,0);
                        lcd.print("To continue-> E");
                                               
                    
                      tone(buzzer, 1000); 
                      delay(500);       
                      noTone(buzzer);     
                      delay(300);                      
                                          

 
                          char customKey = customKeypad.getKey();
   
 
  
                            if (customKey){
                             Serial.println(customKey);
                                                           
                               if(customKey=='C'){
                                      lcd.clear();                                  
                                      return function5_2();
                                  }   
                                  }
                               }                    
                                        
                                        
                    
                                                                                      
                    
                  }                            
            } 
              digitalWrite(solenoidvalve,HIGH);             
              lcd.clear();
              Serial.print("Oil Can successfully filled!!");
              Serial.println();
              Can_count++;
              Amount_of_oil=Amount_of_oil+18;
              any_amount_of_can--; 

                                                                           
                lcd.setCursor(0,0);
                lcd.print("Oil Can  filled!!");
                                
                lcd.setCursor(8,0);
                lcd.print("No of Cans:");
                lcd.print(Can_count);

                lcd.setCursor(24,0);
                lcd.print("Oil Amount:");
                lcd.print(Amount_of_oil);
                lcd.print(" KG");   
                  
              while(true){
                 Serial.print("Buzer!!");
                  Serial.println();
                      tone(buzzer, 1000); 
                      delay(1000);       
                      noTone(buzzer);     
                      delay(1000);                   
                  distance1=ir1();
                  distance2=ir2();                                        

                    if(distance1 > 9   && distance2 > 10  ){
                      lcd.clear();
                        return function5_2();                        
                    }                  




              }
                               
      }
    else{
              
        Serial.print(" Return");
        
        Serial.println();
        //delay(1000);
        return function5_2();
        
             }      
}
else{

Serial.print("Can not found!!");
Serial.println(); 

}

}
else{
display_function5_value();
Serial.println("function3");
 

if ( distance1 < 11  && distance1 > 9  && distance2 < 13 && distance2 >10 && oil_weight > 0.6 && oil_weight < 1.5 ){

  
      
    lcd.clear();
    lcd.setCursor(16,0);
    lcd.print(" Wait 5 Seconds"); 
    lcd.setCursor(8,0);
    lcd.print(" Identifying....");        

    Serial.print(" Can found");
    Serial.println();

    delay(5000);

    distance1=ir1();
    distance2=ir2();
    
     

     Serial.print(distance1);
     Serial.print(distance2);
      //delay(1000);

    if( distance1 < 11  && distance1 > 9  && distance2 < 13 && distance2 >10 && oil_weight > 0.6 && oil_weight < 1.5 ){
      
            lcd.clear();

      

            oil_weight=weight();      
              
            Serial.print("Still Oil Can is there!!");
            Serial.println();
            Serial.print(oil_weight);

           
            Can_weight=oil_weight; 
            Serial.print(Can_weight);
            //delay(3000); 

          while( oil_weight < (remaining_kg + Can_weight) && oil_weight < 19.1  ){
    
                  distance1=ir1();
                  distance2=ir2();
                  oil_weight=weight();
                                    
                  Last_oil_weight=oil_weight;
                  display_function5_1value();               
                  
              if(distance1 < 11  && distance1 > 9  && distance2 < 13 && distance2 >10 ){
                
                    
                    display_function5_1value();
                    Serial.print(" Oil is filling to Can");
                    Serial.println();
                    digitalWrite(solenoidvalve,LOW);


              } 

              else{
                digitalWrite(solenoidvalve,HIGH);
                emergency_exit_cane++;                
                emergency_exit_oil+=Last_oil_weight;                
                lcd.clear();                

                    while(true){
                   
                    
                    Serial.print("Emergency Out");
                    Serial.println();
                    Serial.print(Last_oil_weight);
                    Serial.println(); 

                    lcd.setCursor(0,0);
                    lcd.print("Emergency Out!!");
                    
                      lcd.setCursor(16,0);
                      lcd.print("Filled Amount");

                      lcd.setCursor(8,0);
                      lcd.print(": ");
                      lcd.print(Last_oil_weight);
                      lcd.print("KG");                      

                        lcd.setCursor(24,0);
                        lcd.print("To continue-> E");
                                               
                    
                      tone(buzzer, 1000); 
                      delay(500);       
                      noTone(buzzer);     
                      delay(300);                      
                                          

 
                          char customKey = customKeypad.getKey();
   
 
  
                            if (customKey){
                             Serial.println(customKey);
                                                           
                               if(customKey=='C'){
                                      lcd.clear();                                  
                                      return function5_2();
                                  }   
                                  }
                               }                   
                                        
                                        
                    
                                                                                      
                    
                  }                            
            } 
              digitalWrite(solenoidvalve,HIGH);             
              lcd.clear();
              Serial.print("Oil Can successfully filled!!");
              Serial.println();
              
                                                                                  
                lcd.setCursor(0,0);
                lcd.print("Oil Can  filled!!");
                                
                lcd.setCursor(16,0);
                lcd.print(Can_count);                
                lcd.print("Oil Can and");
                

                lcd.setCursor(8,0);
                lcd.print("   ");
                lcd.print(remaining_kg);
                lcd.print("KG Oil");    
                
                lcd.setCursor(24,0);               
                lcd.print("successfully filled!!");                
                                           
              while(true){
                
                char customKey = customKeypad.getKey();

                  if (customKey){
                    Serial.println(customKey);
                                                  
                      if(customKey=='C'){
                            lcd.clear();                                  
                            return function5_2();
                        }   
                        }                  




              }
                               
      }
    else{
              
        Serial.print(" Return");
        
        Serial.println();
        //delay(1000);
        return function5_2();
        
             }      
}
else{

Serial.print("Can not found!!");
Serial.println(); 

}


  
}

}
void function_print5 ()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("You can filled ");

  lcd.setCursor(16,0);
  lcd.print("     ");
  lcd.print(any_amount_of_can);
  lcd.print("Can and");

  lcd.setCursor(8,0);
  lcd.print("   ");
  lcd.print(remaining_kg);
  lcd.print(" KG Oil    ");  
  
  
    
}
void display_function5_value(){
  
lcd.setCursor(0,0);
lcd.print("Any amount of kg");

lcd.setCursor(16,0);
lcd.print("Weight : ");


lcd.print(oil_weight);
lcd.print("KG");

lcd.setCursor(8,0);
lcd.print("No of Cans:");
lcd.print(Can_count);

lcd.setCursor(24,0);
lcd.print("Oil Amount:");
lcd.print(Amount_of_oil);
lcd.print("KG");

}
//display the filling state
void display_function5_1value(){
  
lcd.setCursor(0,0);
lcd.print("  Filling.....");

lcd.setCursor(16,0);
lcd.print("Weight : ");


lcd.print(oil_weight);
lcd.print("KG");

lcd.setCursor(8,0);
lcd.print("No of Cans:");
lcd.print(Can_count);

lcd.setCursor(24,0);
lcd.print("Oil Amount:");
lcd.print(Amount_of_oil);
lcd.print("KG");

}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//function6

void function6(){

  lcd.clear();  
  lcd.setCursor(0,0);
  lcd.print("   WELCOME TO ");

  lcd.setCursor(16,0);
  lcd.print("Price Changer");
  delay(2000);
  function6_3();
  
  }
void function6_3()
{
  
  lcd.clear();  
  display_function6();  
  function6_4();

  }

  
void return_price_change()
{

  lcd.clear();  
  lcd.setCursor(0,0);
  display_function6(); 
  function6_4();
  
}


void function6_4(){
while(true)  
{
   customKey = customKeypad.getKey();
     
    if (customKey!=NO_KEY)
      DetectButtons6();                            
      //Serial.println(customKey);
              
}
}

void DetectButtons6()

{ 

    if (customKey=='*')
    {
      Serial.println ("Button Clear");
      Number=Num1=Num2=0;
      return return_price_change();
    
    }

    if (customKey == '1') 
    {
      Serial.print ("Button 1"); 

            if (Number==0)
            {
              Number=1;
              display_function6();  
              lcd.print(Number); 
            }   

          else
            {
              Number = (Number*10) + 1; 
              display_function6(); 
              lcd.print(Number);
            }
     
    }


   if (customKey == '4') 

    {
      Serial.println ("Button 4"); 

            if (Number==0)
            {
                Number=4;
                display_function6();  
                lcd.print(Number); }   

            else
            {
                Number = (Number*10) + 4; 
                display_function6();
                lcd.print(Number);

            }
  }

  if (customKey == '7') 

    {
      Serial.println ("Button 7");

          if (Number==0)
          {          
              Number=7;
              display_function6();
              lcd.print(Number); 
          }   

          else
            {
              Number = (Number*10) + 7; 
              display_function6();
              lcd.print(Number);   
          } 
    
    }

 if (customKey == '0')

    {
      Serial.println ("Button 0"); 

            if (Number==0)
            {
              Number=0;
              display_function6(); 
              lcd.print(Number);                    
            }  

            else
            {
              Number = (Number*10) + 0; 
              display_function6();
              lcd.print(Number);
            }
  }

  if (customKey == '2') 

    {
      Serial.println ("Button 2"); 

            if (Number==0)
            {
                  Number=2;
                  display_function6();;  
                  lcd.print(Number); 
            }  

            else
            {
                Number = (Number*10) + 2; 
                display_function6(); 
                lcd.print(Number);    
            }
    }

         if (customKey == '5')

    {
      Serial.println ("Button 5"); 

              if (Number==0)
              {
                  Number=5;
                  display_function6();
                  lcd.print(Number);
              }    

              else
              {
                  Number = (Number*10) + 5; 
                  display_function6();
                  lcd.print(Number);    
              }
    }

         if (customKey == '8')

    {
      Serial.println ("Button 8"); 

                if (Number==0)
                {
                      Number=8;
                      display_function6();
                      lcd.print(Number); 
                }   

                else
                {
                      Number = (Number*10) + 8; 
                      display_function6();
                      lcd.print(Number);
                }  
    } 

      if (customKey == '#')

    {
        lcd.clear();  
        oil_price=Number;
     
        lcd.setCursor(0,0);
        lcd.print("New Oil Price");
        lcd.print(oil_price);
                  
        lcd.setCursor(16,0);
        lcd.print("Press D to return ");
        
        while(true)
        {
              char customKey = customKeypad.getKey();
   
              if (customKey)
              {
                    tone(buzzer, 1000); 
                    delay(50);       
                    noTone(buzzer);     
                    Serial.println(customKey);

                      if(customKey=='D')
                      {
                            Number=0;
                            lcd.clear();                
                            start();
                      }                 
      
              }  
        }   
      
    }

         if (customKey == '3')

    {
      Serial.println ("Button 3"); 

                if (Number==0)
                {
                      Number=3;
                      display_function6();
                      lcd.print(Number);  
                }  

                else
                {
                      Number = (Number*10) + 3; 
                      display_function6();
                      lcd.print(Number);    
                }
    }

       if (customKey == '6')

    {
      Serial.println ("Button 6"); 

              if (Number==0)
              {
                  Number=6;
                  display_function6();
                  lcd.print(Number);  
              }  

              else
              {
                  Number = (Number*10) + 6; 
                  display_function6();
                  lcd.print(Number);   

              }
    }

         if (customKey == '9')

    {
      Serial.println ("Button 9");

            if (Number==0)
            {
                Number=9;
                display_function6();
                lcd.print(Number);  
            }  

            else
            {
                Number = (Number*10) + 9; 
                display_function6();
                lcd.print(Number);  
            } 
    }
      if (customKey == 'D'){
              return start();
        }       
}

void display_function6(){
  
  lcd.setCursor(0,0);
  lcd.print("Old Oil Price");
  lcd.print(oil_price);
  lcd.setCursor(16,0);
  lcd.print("New Oil Price");

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//function7


void function7(){
  
  lcd.clear();      
  display_function7(); 
  function7_4();

  }
void return_price_change1()
{ 

    lcd.clear();  
    display_function7(); 
    function7_4();
}
  
 

void function7_4(){
while(true)  
{
   customKey = customKeypad.getKey();
     
    if (customKey!=NO_KEY)
      DetectButtons7();                            
      //Serial.println(customKey);
              
}
}

void DetectButtons7()

{ 

    if (customKey=='*')
    {
      Serial.println ("Button Clear");
      Number=Num1=Num2=0;
      return return_price_change1();
    
    }

    if (customKey == '1') 
    {
      Serial.print ("Button 1"); 

            if (Number==0)
            {
              Number=1;
              display_function7();  
              lcd.print(Number); 
            }   

          else
            {
              Number = (Number*10) + 1; 
              display_function7(); 
              lcd.print(Number);
            }
     
    }


   if (customKey == '4') 

    {
      Serial.println ("Button 4"); 

            if (Number==0)
            {
                Number=4;
                display_function7();  
                lcd.print(Number); }   

            else
            {
                Number = (Number*10) + 4; 
                display_function7();
                lcd.print(Number);

            }
  }

  if (customKey == '7') 

    {
      Serial.println ("Button 7");

          if (Number==0)
          {          
              Number=7;
              display_function7();
              lcd.print(Number); 
          }   

          else
            {
              Number = (Number*10) + 7; 
              display_function7();
              lcd.print(Number);   
          } 
    
    }

 if (customKey == '0')

    {
      Serial.println ("Button 0"); 

            if (Number==0)
            {
              Number=0;
              display_function7(); 
              lcd.print(Number);                    
            }  

            else
            {
              Number = (Number*10) + 0; 
              display_function7();
              lcd.print(Number);
            }
  }

  if (customKey == '2') 

    {
      Serial.println ("Button 2"); 

            if (Number==0)
            {
                  Number=2;
                  display_function7();;  
                  lcd.print(Number); 
            }  

            else
            {
                Number = (Number*10) + 2; 
                display_function7(); 
                lcd.print(Number);    
            }
    }

         if (customKey == '5')

    {
      Serial.println ("Button 5"); 

              if (Number==0)
              {
                  Number=5;
                  display_function7();
                  lcd.print(Number);
              }    

              else
              {
                  Number = (Number*10) + 5; 
                  display_function7();
                  lcd.print(Number);    
              }
    }

         if (customKey == '8')

    {
      Serial.println ("Button 8"); 

                if (Number==0)
                {
                      Number=8;
                      display_function7();
                      lcd.print(Number); 
                }   

                else
                {
                      Number = (Number*10) + 8; 
                      display_function7();
                      lcd.print(Number);
                }  
    } 

      if (customKey == '#')

    {
      Serial.println ("Button Equal"); 
    
        lcd.clear();  
        oil_price=Number;
        Serial.println (Num2);
        Number=0;     
        start();        
    
    }

         if (customKey == '3')

    {
      Serial.println ("Button 3"); 

                if (Number==0)
                {
                      Number=3;
                      display_function7();
                      lcd.print(Number);  
                }  

                else
                {
                      Number = (Number*10) + 3; 
                      display_function7();
                      lcd.print(Number);    
                }
    }

       if (customKey == '6')

    {
      Serial.println ("Button 6"); 

              if (Number==0)
              {
                  Number=6;
                  display_function7();
                  lcd.print(Number);  
              }  

              else
              {
                  Number = (Number*10) + 6; 
                  display_function7();
                  lcd.print(Number);   

              }
    }

         if (customKey == '9')

    {
      Serial.println ("Button 9");

            if (Number==0)
            {
                Number=9;
                display_function7();
                lcd.print(Number);  
            }  

            else
            {
                Number = (Number*10) + 9; 
                display_function7();
                lcd.print(Number);  
            } 
    } 
}

void display_function7(){
  
  lcd.setCursor(16,0);
  lcd.print("Today Coco Oil ");
  lcd.setCursor(8,0);
  lcd.print("Price:");

}
