//Untitled by Philippe Roy
//for Joseph Medaglia

#include <Scissors.h>

Scissors messageFromPro;        // SCISSORS parse messages

#define STRIP_LENGTH 121 //38 LEDs per strip 


long strip_colors[STRIP_LENGTH];

int SDI_C1 = 2; //Red wire (not the red 5V wire!) 
int CKI_C1 = 3; //Green wire

int valG1s, valG2s, valG3s, valG4s;
int valG1Red, valG2Red, valG3Red, valG4Red;

int redG1Counter = 100;

unsigned long G1c;
unsigned long G2c;
unsigned long G3c;
unsigned long G4c;

int checksum, totalval, errorcheck;
//************************************************************************
void setup() 
{ 
  messageFromPro.begin(9600);

  pinMode(SDI_C1, OUTPUT); 
  pinMode(CKI_C1, OUTPUT);


  //Clear out the array
  for(int x = 0 ; x < STRIP_LENGTH ; x++){
    strip_colors[x] = 0; 
  }

  messageFromPro.setMaxElements( 14 ) ;

}
//************************************************************************
void loop() 
{ 
  readVal();


//  Serial.print(valG1s);    
//  Serial.print(" , ");  
//  Serial.print(valG1Red);  
//  Serial.print(" , ");  
//  Serial.print(valG2s);    
//  Serial.print(" , ");  
//  Serial.print(valG2Red);  
//  Serial.print(" , "); 
//  Serial.print(valG3s);    
//  Serial.print(" , ");  
//  Serial.print(valG3Red);  
//  Serial.print(" , ");  
//  Serial.print(valG4s);    
//  Serial.print(" , ");  
//  Serial.print(valG4Red);
//  Serial.print(" , ");  
//  Serial.print(checksum);  
//  Serial.print(" , ");  
//  Serial.println(totalval);    


} 
//************************************************************************
void readVal(){

  if (messageFromPro.update() > 0) {         // poll the SCISSOR object -- any new MESSAGES (returns element count)

    valG1s = messageFromPro.getInt(1);
    valG1Red = messageFromPro.getInt(2);  

    valG2s = messageFromPro.getInt(3); 
    valG2Red = messageFromPro.getInt(4);  

    valG3s = messageFromPro.getInt(5);
    valG3Red = messageFromPro.getInt(6);

    valG4s = messageFromPro.getInt(7);
    valG4Red = messageFromPro.getInt(8);

    checksum = messageFromPro.getInt(0);



  } 
//  totalval = valG1Red + valG2Red + valG2Red + valG2Red;// + errorcheck;

  if (checksum == 100 ){
    colorSelector();
    sections();
    C_One();
  }
    if (checksum != 100 ){

  }
  
//    if (checksum == 0 ){
//    }
  

}




//************************************************************************
void colorSelector(){

  byte G1inputr = valG1s;
  byte G1inputg = valG1s;
  byte G1inputb = valG1Red;

  G1c = (unsigned long)G1inputr << 16 | (unsigned long)G1inputg << 8 | (unsigned long)G1inputb;

  byte G1r = (G1c >> 16) & 0xFF;  
  byte G1g = (G1c >> 8) &  0xFF;  
  byte G1b = G1c & 0xFF;   

  //************************************************************************
  byte G2inputb = valG2Red;
  byte G2inputg = valG2s;
  byte G2inputr = valG2s;

  G2c = (unsigned long)G2inputr << 16 | (unsigned long)G2inputg << 8 | (unsigned long)G2inputb;

  byte G2r = (G2c >> 16) & 0xFF;  
  byte G2g = (G2c >> 8) &  0xFF;  
  byte G2b = G2c & 0xFF;    


  //************************************************************************
  byte G3inputb = valG3Red;
  byte G3inputg = valG3s;
  byte G3inputr = valG3s;

  G3c = (unsigned long)G3inputr << 16 | (unsigned long)G3inputg << 8 | (unsigned long)G3inputb;

  byte G3r = (G3c >> 16) & 0xFF;  
  byte G3g = (G3c >> 8) &  0xFF;  
  byte G3b = G3c & 0xFF;  

  //************************************************************************ 

  byte G4inputb = valG4Red;
  byte G4inputg = valG4s;
  byte G4inputr = valG4s;

  G4c = (unsigned long)G4inputr << 16 | (unsigned long)G4inputg << 8 | (unsigned long)G4inputb;

  byte G4r = (G4c >> 16) & 0xFF;  
  byte G4g = (G4c >> 8) &  0xFF;  
  byte G4b = G4c & 0xFF; 

}
//************************************************************************


//************************************************************************
void sections(){

  //Red

  strip_colors[41] = G1c;
  strip_colors[42] = G1c;

  strip_colors[47] = G1c;
  strip_colors[48] = G1c;

  strip_colors[53] = G1c;
  strip_colors[54] = G1c;

  strip_colors[67] = G1c;
  strip_colors[68] = G1c;

  strip_colors[71] = G1c;
  strip_colors[72] = G1c;

  strip_colors[77] = G1c;
  strip_colors[78] = G1c;


  //Blue 

  strip_colors[5] = G2c;
  strip_colors[6] = G2c;

  strip_colors[13] = G2c;
  strip_colors[14] = G2c;

  strip_colors[17] = G2c;
  strip_colors[18] = G2c;

  strip_colors[23] = G2c;
  strip_colors[24] = G2c;

  strip_colors[29] = G2c;
  strip_colors[30] = G2c;

  strip_colors[59] = G2c;
  strip_colors[60] = G2c;

  strip_colors[79] = G2c;
  strip_colors[80] = G2c;

  strip_colors[85] = G2c;
  strip_colors[86] = G2c;

  strip_colors[93] = G2c;
  strip_colors[94] = G2c;

  strip_colors[99] = G2c;
  strip_colors[100] = G2c;

  strip_colors[109] = G2c;
  strip_colors[110] = G2c;

  strip_colors[117] = G2c;
  strip_colors[118] = G2c;


  // Green
  strip_colors[1] = G3c;
  strip_colors[2] = G3c;

  strip_colors[9] = G3c;
  strip_colors[10] = G3c;

  strip_colors[13] = G3c;
  strip_colors[14] = G3c;

  strip_colors[21] = G3c;
  strip_colors[22] = G3c;

  strip_colors[25] = G3c;
  strip_colors[26] = G3c;

  strip_colors[35] = G3c;
  strip_colors[36] = G3c;

  strip_colors[39] = G3c;
  strip_colors[40] = G3c;

  strip_colors[45] = G3c;
  strip_colors[46] = G3c;

  strip_colors[49] = G3c;
  strip_colors[50] = G3c;

  strip_colors[57] = G3c;
  strip_colors[58] = G3c;

  strip_colors[63] = G3c;
  strip_colors[64] = G3c;

  strip_colors[69] = G3c;
  strip_colors[70] = G3c;

  strip_colors[75] = G3c;
  strip_colors[76] = G3c;

  strip_colors[81] = G3c;
  strip_colors[82] = G3c;

  strip_colors[89] = G3c;
  strip_colors[90] = G3c;

  strip_colors[95] = G3c;
  strip_colors[96] = G3c;

  strip_colors[101] = G3c;
  strip_colors[102] = G3c;

  strip_colors[105] = G3c;
  strip_colors[106] = G3c;

  strip_colors[113] = G3c;
  strip_colors[114] = G3c;

  strip_colors[121] = G3c;
  strip_colors[122] = G3c;




  //Purple

  strip_colors[3] = G4c;
  strip_colors[4] = G4c;

  strip_colors[7] = G4c;
  strip_colors[8] = G4c;

  strip_colors[11] = G4c;
  strip_colors[12] = G4c;

  strip_colors[15] = G4c;
  strip_colors[16] = G4c;

  strip_colors[19] = G4c;
  strip_colors[20] = G4c;
  
  strip_colors[27] = G4c;
  strip_colors[28] = G4c;

  strip_colors[31] = G4c;
  strip_colors[32] = G4c;

  strip_colors[33] = G4c;
  strip_colors[34] = G4c;

  strip_colors[37] = G4c;
  strip_colors[38] = G4c;

  strip_colors[43] = G4c;
  strip_colors[44] = G4c;

  strip_colors[51] = G4c;
  strip_colors[52] = G4c;

  strip_colors[55] = G4c;
  strip_colors[56] = G4c;

  strip_colors[61] = G4c;
  strip_colors[62] = G4c;

  strip_colors[65] = G4c;
  strip_colors[66] = G4c;

//  strip_colors[71] = G4c;
//  strip_colors[72] = G4c;
  
  strip_colors[73] = G4c;
  strip_colors[74] = G4c;

  strip_colors[83] = G4c;
  strip_colors[84] = G4c;

  strip_colors[87] = G4c;
  strip_colors[88] = G4c;

  strip_colors[91] = G4c;
  strip_colors[92] = G4c;

  strip_colors[97] = G4c;
  strip_colors[98] = G4c;

  strip_colors[103] = G4c;
  strip_colors[104] = G4c;

  strip_colors[107] = G4c;
  strip_colors[108] = G4c;

  strip_colors[111] = G4c;
  strip_colors[112] = G4c;

  strip_colors[115] = G4c;
  strip_colors[116] = G4c;

  strip_colors[119] = G4c;
  strip_colors[120] = G4c;

}



//************************************************************************
void C_One(){
  for(int LED_number = 1 ; LED_number < STRIP_LENGTH ; LED_number++) { 
    long this_led_color = strip_colors[LED_number];
    for(byte color_bit = 23 ; color_bit != 255 ; color_bit--) { 
      digitalWrite(CKI_C1, LOW); 
      long mask = 1L << color_bit;
      if(this_led_color & mask) digitalWrite(SDI_C1, HIGH);
      else
        digitalWrite(SDI_C1, LOW);
      digitalWrite(CKI_C1, HIGH); 
    }
  }
  digitalWrite(CKI_C1, LOW);
  delayMicroseconds(500); 
}






























