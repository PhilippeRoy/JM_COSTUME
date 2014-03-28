import processing.serial.*;  
import processing.video.*;

Serial myPort;


//Movie video;
Capture video;


//int w = 1280;
//int h = 720;

//int w = 640;
//int h = 480;

//%%%%%%%%%%% Screen Size %%%%%%%%%%%%%%
//make sure that the video dimesions match
int w = 320;
int h = 240;
//%%%%%%%%%%%%%%%%%%%%%%%%%

int percentage;
int threshold;
int totalPixel = w*h;


int G1Dis, G2Dis, G3Dis, G4Dis, blkDis;
int counterG5, counterG6, counterG3, counterG4, counterspeed, G5value = 0, RedG5value = 0;
int  G6value = 0, G3value = 0, G4value = 0;
int  RedG6value = 0, RedG3value = 0, RedG4value = 0;

int checksum;
int speedG5, speedG6, speedG3, speedG4;
int group1Trigger, group2Trigger, group3Trigger, group4Trigger;


Boolean trigG5 = false, trigG6 = false, trigG3 = false, trigG4 = false;

//***************************************************

void setup() {
//%%%%%%%%%%%%%%%%%%%%%%%%%
  size(520, 240, P2D);  //switch to size(w, h, P2D) to get rid of the grey side
  //size(w, h, P2D);
//%%%%%%%%%%%%%%%%%%%%%%%%%
  String[] videos = Capture.list();
  
   if (videos.length == 0) {
    println("There are no cameras available for capture.");
    exit();
  } else {
    println("Available cameras:");
    for (int i = 0; i < videos.length; i++) {
      println(videos[i]);
    }
  }
    // The camera can be initialized directly using an 
    // element from the array returned by list():
    video = new Capture(this, videos[0]);
    video.start();     
   

//  video = new Capture(this, w, h);    //For LIVE
//  video.start();                      //For LIVE

 // video = new Movie(this, "JPLS2.mov");                //For VIDEO   // Play movie
 // video.loop();                                         //For VIDEO  // Loops movie or video.play() to play once

//%%%%%%%%%%%%%%%%%%%%%%%%%
//make sure that Serial.list()[0] match USB port
  println(Serial.list());
  myPort = new Serial(this, Serial.list()[0], 9600);
//%%%%%%%%%%%%%%%%%%%%%%%%%


//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%  Variables  %%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//Change color, (0 - 255) to be compared to give percentage
  threshold = 30;//out of 255

//Change how fast the colors change from no light -> white -> red -> no light
  speedG5 = 5;      //Group 1
  speedG6 = 4;      //Group 2
  speedG3 = 2;      //Group 3
  speedG4 = 1;      //Group 4
  
  group1Trigger = 10;      //Group 1 Starts at (0 - 100)
  group2Trigger = 30;     //Group 2 Starts at (0 - 100)
  group3Trigger = 50;      //Group 3 Starts at (0 - 100)
  group4Trigger = 70;     //Group 3 Starts at (0 - 100)
//%%%%%%%%%%%%%%%%%%%%%%%%%  

}

void draw() {
  sendMessage();

  if (video.available()) {
    video.read();
    image(video, 0, 0, w, h); // Draw the  video onto the screen
    int brightestX = 0; // X-coordinate of the brightest video pixel
    int brightestY = 0; // Y-coordinate of the brightest video pixel
    float brightestValue = 0; // Brightness of the brightest video pixel
    // Search for the brightest pixel: For each row of pixels in the video image and
    // for each pixel in the yth row, compute each pixel's index in the video
    video.loadPixels();
    int index = 0;
    for (int y = 0; y < video.height; y++) {
      for (int x = 0; x < video.width; x++) {
        // Get the color stored in the pixel
        color pixelValue = video.pixels[index];

        // Determine the brightness of the pixel
        float pixelBrightness = brightness(pixelValue);
        // If that value is brighter than any previous, then store the
        // brightness of that pixel, as well as its (x,y) location
        if (pixelBrightness > threshold) {
          brightestY++;
        }

        index++;
      }
    }

    percentage = int(map(brightestY, 0, totalPixel, 0, 100));
    setThreshold();
    // checksum =  RedG5value + RedG6value + RedG4value + RedG4value;// G5value
  }
}


void sendMessage() {     
  String myPackage = ( "*" + 100+"," + G5value + "," + RedG5value + "," + G6value + "," + RedG6value  + ","  + G3value + "," + RedG3value + "," + G4value + "," + RedG4value  +  ",#");
  myPort.write(myPackage);
  println(myPackage);
}


void setThreshold() {

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// Delete this to get rid of grey Box

  fill(111);
  rect(320, 0, 200, 240);
  fill(255);
  text("%: " + percentage, 330, 140);
  text("Thres: " + threshold, 330, 160);
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

  if (percentage < 10) {
    trigG3 = false;
    trigG4 = false;
    trigG5 = false;
    trigG6 = false;
  }

  if (percentage > group2Trigger) {
    trigG5 = true;
  }
  //=========================
  if (percentage > group2Trigger) {
    trigG6 = true;
  }
  //=========================
  if (percentage > group3Trigger) {
    trigG3 = true;
  }
  //=========================
  if (percentage > group4Trigger) {
    trigG4 = true;
  }
  //*******************************
  if (trigG5) { 
    counterG5 = counterG5 + speedG5;

    if ( counterG5 < 75  ) 
      G5value = G5value + speedG5;
    if ( counterG5 < 150  ) 
      RedG5value = RedG5value + speedG5;
    if ( counterG5 > 75)
      G5value = G5value - speedG5;
    if ( counterG5 > 150)
      RedG5value = RedG5value - speedG5;
    if (G5value < 0)
      G5value = 0;
    if (RedG5value < 0)
      RedG5value = 0;
    if ( counterG5 > 300)
      trigG5 = false;
  }
  if (!trigG5) {
    RedG5value = 0;
    G5value = 0;
    counterG5 = 0;
  }

  //*******************************
  if (trigG6) {
    counterG6 = counterG6 + speedG6;

    if ( counterG6 < 75  ) 
      G6value = G6value + speedG6;
    if ( counterG6 < 150  ) 
      RedG6value = RedG6value + speedG6;
    if ( counterG6 > 75)
      G6value = G6value - speedG6;
    if ( counterG6 > 150)
      RedG6value = RedG6value - speedG6;
    if (G6value < 0)
      G6value = 0;
    if (RedG6value < 0)
      RedG6value = 0;
    if ( counterG6 > 300)
      trigG6 = false;
  }
  if (!trigG6) {
    RedG6value = 0;
    G6value = 0;
    counterG6 = 0;
  }
  //*******************************
  if (trigG3) {
    counterG3 = counterG3 + speedG3;

    if ( counterG3 < 75  ) 
      G3value = G3value + speedG3;
    if ( counterG3 < 150  ) 
      RedG3value = RedG3value + speedG3;
    if ( counterG3 > 75)
      G3value = G3value - speedG3;
    if ( counterG3 > 150)
      RedG3value = RedG3value - speedG3;
    if (G3value < 0)
      G3value = 0;
    if (RedG3value < 0)
      RedG3value = 0;
    if ( counterG3 > 300)
      trigG3 = false;
  }
  if (!trigG3) {
    RedG3value = 0;
    G3value = 0;
    counterG3 = 0;
  }
  //*******************************
  if (trigG4) {
    counterG4 = counterG4 + speedG4;

    if ( counterG4 < 75  ) 
      G4value = G4value + speedG4;
    if ( counterG4 < 150  ) 
      RedG4value = RedG4value + speedG4;
    if ( counterG4 > 75)
      G4value = G4value - speedG4;
    if ( counterG4 > 150)
      RedG4value = RedG4value - speedG4;
    if (G4value < 0)
      G4value = 0;
    if (RedG4value < 0)
      RedG4value = 0;
    if ( counterG4 > 300)
      trigG4 = false;
  }
  if (!trigG4) {
    RedG4value = 0;
    G4value = 0;
    counterG4 = 0;
  }
}

