#include <Arduino.h>
#include <MAIN/ps4.h>
#include <MAIN/ros_com.h>
// test

bool connected = false;
bool emergency_break = false;
int battery_level = 0; 
bool circle = false;
bool triangle = false; 

void setup() {
  // Serial.begin(115200);
  pinMode(LED_BUILDIN,OUTPUT);
  digitalWrite(LED_BUILDIN, LOW);
  ros_init();
  PS4setup();
}

void loop() {
  connected = ps4Connected();

  if(connected){
    digitalWrite(LED_BUILDIN, HIGH);

    cmd_linear = ps4Linear();
    cmd_angular = ps4Angular();

    emergency_break = ps4X();
    circle = ps4Circle();
    triangle = ps4Triangle();

    battery_level = battery();
    
    // if(battery(30)){
    //     //ADD BLINK 
    //   //  digitalWrite(LED_BUILDIN, LOW);
    //   //  Serial.print("BAT LOW ");
    // }

    // Serial.print("| Linear: ");
    // Serial.print(cmd_linear);
    // Serial.print("| Angular: ");
    // Serial.print(cmd_angular);
    // Serial.println("");


  }else{
    digitalWrite(LED_BUILDIN, LOW);
  }
  ros_loop(cmd_linear,cmd_angular,emergency_break, triangle,circle,battery_level,connected);

  nh.spinOnce();
}