/*

placeholders - ill change later:
- Threshold
- Servo open angle
- Servo closed angle
*/

#include <Servo.h>

//picking the pins 
const int SERVO_PIN = 9; //yellow 
const int EMG_PIN   = A0;

//5v is 1023 so 2.5v is 512
int EMG_THRESHOLD = 512;

int HAND_OPEN  = 0; //assuming open hand is position 0, and closed is 180 degrees
int HAND_CLOSE = 180;

//1k ms / 20 = 50 readings per second. 
int LOOP_DELAY = 20;

//object. 
Servo prostheticHand;

//runs when u turn it on. 
void setup()
{
    Serial.begin(9600);

    prostheticHand.attach(SERVO_PIN);

    //start with open hand config
    prostheticHand.write(HAND_OPEN);

    //logs
    Serial.println("hand is on.");
    
}

void loop() //read emg, make a decision, then move servo, then wait, then repeat. 
{
    //read emg
    int emgValue = analogRead(EMG_PIN);

    // Display value for tuning
    Serial.print("EMG = ");
    Serial.println(emgValue);

    //compare against 2.5
    if (emgValue >= EMG_THRESHOLD)
    {
        //contracts
        prostheticHand.write(HAND_CLOSE);
    }
    else
    {
        //relax. 
        prostheticHand.write(HAND_OPEN);
    }

    delay(LOOP_DELAY);
}