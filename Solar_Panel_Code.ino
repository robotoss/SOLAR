   #include <Servo.h> // include Servo library 

Servo horizontal; // horizontal servo
int servoh = 90; // stand horizontal servo
//
Servo vertical; // vertical servo 
int servov = 90; // stand vertical servo

int Tolerance = 100;

// LDR pin connections
//name = analogpin;
const int TOPpin = 0; //LDR TOP
const int BOTTOMpin = 1; //LDR BOTTOM
const int LEFTpin = 2; //LDR LEFT
const int RIGHTpin = 3; //LDR RIGHT

int TOP = 0;
int BOTTOM = 0;
int LEFT = 0;
int RIGHT = 0;

int averageTOP = 0;
int averageBOTTOM = 0;
int averageLEFT = 0;
int averageRIGHT = 0;

int averageVERTICAL = 0;
int averageHORIZONTAL = 0;

void setup()
{
  analogReference(EXTERNAL);
  Serial.begin(9600);
//servo connections
//name.attacht(pin);
  horizontal.attach(10); 
  vertical.attach(9);


}

void loop() 
{ //start loop
 
    TOP = 0;
    BOTTOM = 0;
    LEFT = 0;
    RIGHT = 0;
    
    for (int i = 0; i <=10; i++)
    {
    TOP = TOP + analogRead(TOPpin);delay(1);
    BOTTOM = BOTTOM + analogRead(BOTTOMpin);delay(1);
    LEFT = LEFT + analogRead(LEFTpin);delay(1);
    RIGHT = RIGHT + analogRead(RIGHTpin);delay(1);}
    
    TOP = TOP/10;
    BOTTOM = BOTTOM/10;
    LEFT = LEFT/10;
    RIGHT = RIGHT/10;

  Serial.print("TOP = "); Serial.println(TOP); //Serial.print(" TOP average= "); Serial.println(averageTOP);
  Serial.print("BOTTOM = ") ;Serial.println(BOTTOM); //Serial.print(" BOTTOM average= "); Serial.println(averageBOTTOM);
  Serial.print("LEFT = ") ;Serial.println(LEFT); //Serial.print(" LEFT average= "); Serial.print(averageLEFT);
  Serial.print("RIGHT = ") ;Serial.println(RIGHT); //Serial.print(" RIGHT average= "); Serial.println(averageRIGHT);
  Serial.println();
  
// delay(1000);

    
Serial.print("TOLERANCE = "); Serial.println(Tolerance);
//Serial.println("");

 

  int verticalDIFFERENCE = TOP - BOTTOM; // check the diffirence of up and down
  int horizontalDIFFERENCE = LEFT - RIGHT;// check the difference of left and right

  if (abs(verticalDIFFERENCE) > Tolerance) // check if the diffirence is in the tolerance else change vertical angle
  {vertical.attach(9);
    if (TOP > BOTTOM && servov < 110)
    {
      servov = servov + 1;
      Serial.println("");
      Serial.println("GOING UP  ^ ");
      Serial.println("");
      vertical.write(servov);
      Serial.print("servo v =");Serial.println(servov);
    }
    else if (TOP < BOTTOM && servov > 60)
    {
      servov = servov - 1;
      Serial.println("");
      Serial.println("GOING DOWN v ");
      Serial.println("");
      vertical.write(servov);
      Serial.print("servo v =");Serial.println(servov);
    }
    else if (TOP == BOTTOM)
    {
       // nothing
    }
      vertical.detach();
  }

  if (abs(horizontalDIFFERENCE) > Tolerance) // check if the diffirence is in the tolerance else change horizontal angle
  {horizontal.attach(10);
      if (LEFT < RIGHT && servoh > 50)
      {
       servoh = servoh - 1;
       Serial.println("");
       Serial.println("GO COUNTER-CLOCKWISE  >>  ");
       Serial.println("");
       horizontal.write(servoh);
       Serial.print("servo h =");Serial.println(servoh);
      }
      else if (LEFT > RIGHT && servoh < 110)
      {
       servoh = servoh + 1;
       Serial.println("");
       Serial.println("GO CLOCKWISE <<  ");
       Serial.println("");
       horizontal.write(servoh);
       Serial.print("servo h =");Serial.println(servoh);
      }
      else if (LEFT == RIGHT)
      {
         // nothing
      }
        horizontal.detach();     
  }
    
  
}  //end loop
