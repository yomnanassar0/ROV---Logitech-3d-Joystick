
#include <usbhid.h>
#include <hiduniversal.h>
#include <usbhub.h>
#include "le3dp_rptparser.h"
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>


//MOTORDRIVER1:UP,DOWN,TILT RIGHT & TILT LEFT
int upper1_up=42;
int upper1_down=44;
int upper2_up=46;
int upper2_down=48;
int upper1_speed=6;
int upper2_speed=7;

//MOTORDRIVER2:FORWARD,BACKWARD,LEFT & RIGHT
int right_forward=26;
int right_backward=28;
int left_forward=22;
int left_backward=24;
int right_speed=12; 
int left_speed=13;

USB Usb;
USBHub Hub(&Usb);
HIDUniversal Hid(&Usb);
JoystickEvents JoyEvents;
JoystickReportParser Joy(&JoyEvents);

volatile byte gamepad_Slider = 0x08; // Default value
volatile boolean beepFlag = false;
uint32_t yy;
uint32_t xx;
uint32_t tt;
uint32_t a;
void setup()
{
  Serial.begin( 115200 );
#if !defined(__MIPSEL__)
  while (!Serial); 
#endif
  Serial.println("Start");
  if (Usb.Init() == -1)
    Serial.println("OSC did not start.");
  delay( 200 );
  if (!Hid.SetReportParser(0, &Joy))
    ErrorMessage<uint8_t>(PSTR("SetReportParser"), 1  );

pinMode(upper1_speed,OUTPUT);
pinMode(upper2_speed,OUTPUT);
pinMode(right_speed,OUTPUT);
pinMode(left_speed,OUTPUT);
pinMode(right_forward,OUTPUT);
pinMode(right_forward,OUTPUT);
pinMode(left_forward,OUTPUT);
pinMode(left_backward,OUTPUT);
pinMode(upper1_down,OUTPUT);
pinMode(upper1_down,OUTPUT);
pinMode(upper2_up,OUTPUT);
pinMode(upper2_down,OUTPUT);
}
void loop()
{
  
  Usb.Task();
  Speed();
  
if(yy == 0x000)
{
  forward();
  //Serial.println("forward");
}
else if(yy == 0x3FF)
{
  backward();
  //Serial.println("backward");
}
else if (xx==0x000)
{
  left();
  //Serial.println("left");
}
else if (xx==0x3ff)
{
  right();
  //Serial.println("right");
}
else if (a==0x1)
{
  tiltr();
  //Serial.println("tiltr");
}
else if (a==0x2)
{
  tiltl();
  //Serial.println("tiltl");
}
else if(tt==0xff)
{
  up();
  //Serial.println("up");
}
else if(tt==0x00)
{
  down();
  //Serial.println("down");
}
else  
{
  stop1();
  stop2();
  //Serial.println("STOP");
}
  
  
}

void JoystickEvents::OnGamePadChanged(const GamePadEventData *evt)
{

  yy=evt->y;
  xx = evt->x;
  tt=evt->twist;
  a=evt->buttons_a;
}

void Speed()
{
  analogWrite(right_speed,250);
  analogWrite(left_speed,255);
  analogWrite(upper1_speed,255);
  analogWrite(upper2_speed,255);
}
//MOTORDRIVER2:FORWARD,BACKWARD,LEFT & RIGHT
void left(){
digitalWrite(right_forward,HIGH);
digitalWrite(right_backward,LOW);
digitalWrite(left_forward,HIGH);
digitalWrite(left_backward,LOW);
}
void right(){
digitalWrite(right_forward,LOW);
digitalWrite(right_backward,HIGH);
digitalWrite(left_forward,LOW);
digitalWrite(left_backward,HIGH);
}
void backward(){
digitalWrite(right_forward,HIGH);
digitalWrite(right_backward,LOW);
digitalWrite(left_forward,LOW);
digitalWrite(left_backward,HIGH);
}
void forward(){
digitalWrite(right_forward,LOW);
digitalWrite(right_backward,HIGH);
digitalWrite(left_forward,HIGH);
digitalWrite(left_backward,LOW);
}
void stop1(){
digitalWrite(right_forward,LOW);
digitalWrite(right_backward,LOW);
digitalWrite(left_forward,LOW);
digitalWrite(left_backward,LOW);
}
//MOTORDRIVER1:UP,DOWN,TILT RIGHT & TILT LEFT
void tiltr(){
digitalWrite(upper1_up,HIGH);
digitalWrite(upper1_down,LOW);
digitalWrite(upper2_up,HIGH);
digitalWrite(upper2_down,LOW);
}
void tiltl(){
digitalWrite(upper1_up,LOW);
digitalWrite(upper1_down,HIGH);
digitalWrite(upper2_up,LOW);
digitalWrite(upper2_down,HIGH);
}
void up(){
digitalWrite(upper1_up,HIGH);
digitalWrite(upper1_down,LOW);
digitalWrite(upper2_up,LOW);
digitalWrite(upper2_down,HIGH);
}
void down(){
digitalWrite(upper1_up,LOW);
digitalWrite(upper1_down,HIGH);
digitalWrite(upper2_up,HIGH);
digitalWrite(upper2_down,LOW);
}

void stop2(){
digitalWrite(upper1_up,LOW);
digitalWrite(upper1_down,LOW);
digitalWrite(upper2_up,LOW) ;
digitalWrite(upper2_down,LOW);
}
