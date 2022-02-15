import processing.serial.*;

PImage img, pleft, pright, bump;
Serial mySerial;        // The serial port
String myString = null; 
int nl = 10;
float myVal;
PrintWriter output;

void setup()
{
  output = createWriter("coord.txt"); 
  
  size (1000, 1000);
  img = loadImage("car2.png");
  pleft = loadImage("potholeleft.png");
  pright = loadImage("potholeright.png");
  bump = loadImage("speedbump2.png");
  String myPort = "COM4";
  mySerial = new Serial(this, myPort, 9600);
}

void draw(){
 while(mySerial.available() > 0) 
 {
   
   myString = mySerial.readStringUntil(nl);
   
   if(myString != null)
   {
     background(0);
     image(img, 0, 0);
     myVal = float(myString);
     char c1 = myString.charAt(0);
     String[] coord = {myString.substring(2)};    
     String[] l = {"Groapa pe partea stanga a drumului la coordonatele: "};
     String[] r = {"Groapa pe partea dreapta a drumului la coordonatele: "};
     String sb[] = {"Speed bump pe drum la coordonatele: "};
     if(c1 == '1')
     {
       image(pleft, 0, 0);
       String left[] = concat(l, coord);
       output.println(left);
     }
     else if(c1 == '2')
     {
       image(pright, 0, 0);
       String right[] = concat(r, coord);
       output.println(right);
     }
     else if(c1 == '3')
     {
       image(bump, 0, 0);
       String bu[] = concat(sb, coord);
       output.println(bu);
     }
     else
     {
       
     }
   }
 }
}
