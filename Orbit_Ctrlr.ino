/*
 * created by Princton Brennan : February 28, 2020
 *
 * Currently this test code works to verify the Nema 17 control via
 * the A4988 Stepper Motor Driver.
 *
 * NOTE: The RESET NOT & the SLEEP NOT pin cannot be left floating, so they
 *       have been jumped together to avoid control issues.
 * 
 * This code has developed to work for the Arduino Nano 5V 328p
 * programmer : /dev/cu.wchusbserial-14140
 *
 */

 const byte status_led_pin = 3;
 const byte servo_step_pin = 7;
 const byte servo_ditx_pin = 8;
 const byte servo_dirx_pin = 4;
 const byte servo_sped_pin = A7;
 short speed = 0;
 bool direction_trigger = false;
 bool direction_last;
 
void setup() { 
  Serial.begin (9600);
  pinMode(status_led_pin, OUTPUT);
  pinMode(servo_step_pin, OUTPUT);
  pinMode(servo_ditx_pin, OUTPUT);
  pinMode(servo_dirx_pin, INPUT_PULLUP);
  digitalWrite(status_led_pin,HIGH);
}

void loop() {
  speed = analogRead(servo_sped_pin);
  Serial.print(speed);
  Serial.print("\t");
  if(digitalRead(servo_ditx_pin) != digitalRead(servo_dirx_pin)){
    //direction_last = HIGH;
    led_status_blink(1);
    digitalWrite(servo_ditx_pin,digitalRead(servo_dirx_pin));
    delay(1000);
  }
  digitalWrite(status_led_pin,HIGH);
  runMotor(speed*2);
}

void runMotor(short delay_time){
  digitalWrite(servo_step_pin,HIGH);
  delayMicroseconds(delay_time);
  digitalWrite(servo_step_pin,LOW);
  delayMicroseconds(delay_time);
}

void led_status_blink(byte status){
  switch (status){
    case 1:
      digitalWrite(status_led_pin,LOW);
      delay(500);
      digitalWrite(status_led_pin,HIGH);
      delay(500);
      digitalWrite(status_led_pin,LOW);
      delay(500);
      digitalWrite(status_led_pin,HIGH);
      delay(500);
      break;
    default:
      Serial.println("status trigger");
  }
}
