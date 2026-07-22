/*

placeholders - ill change later:
- Threshold
- Servo open angle
- Servo closed angle
*/

#include <Servo.h>

//picking the pins 
const int servo_pin = 9; //yellow 
const int emg_pin   = A0;
//power pins provide power to the motor (we use 5V). 
//digital pin (yellow wire) either gives upper or lower limit of the voltages (0 or 5). 
//in depth explanation: so basically the digital pin will send either an on or off 
//signal to the servo and depending on how long this signal lasts will tell servo how much  to move.
//analog pins can measure voltages, so EMG will go into analog pins, and compare to a threshold


/* ai summary:
    Forearm muscle contracts
        ↓
EMG electrodes pick up electrical signal
        ↓
Amplifier & filters condition the signal
        ↓
Arduino Analog Pin (A0) measures the voltage
        ↓
Arduino compares voltage to a threshold
        ↓
If above threshold → move servo
If below threshold → don't move servo
        ↓
Digital pin sends pulses to servo
        ↓
Servo moves fingers
*/

//uno uses a 10bit adc, so voltages are represented in 10 bits (0-1023). 
int emg_threshold = 512;

int hand_open  = 0; //assuming open hand is position 0, and closed is 180 degrees
int hand_close = 180;

//1k ms / 20 = 50 readings per second. 
int loop_delay = 20;

//object. 
Servo prostheticHand; //now we can call servo functions on "prostheticHand"

//runs when u turn it on. 
void setup()
{
    Serial.begin(9600);

    prostheticHand.attach(servo_pin);

    //start with open hand config
    prostheticHand.write(hand_open);

    //logs
    Serial.println("hand is on.");
    
}

void loop() //read emg, make a decision, then move servo, then wait, then repeat. 
{
    //read emg - look at the voltage currently on that pin. This is an ADC that converts voltage into a number
    int emgValue = analogRead(emg_pin);

    // Display value for tuning
    Serial.print("EMG = ");
    Serial.println(emgValue);

    //compare against 2.5
    if (emgValue >= emg_threshold)
    {
        //contracts
        prostheticHand.write(hand_close);
    }
    else
    {
        //relax. 
        prostheticHand.write(hand_open);
    }

    delay(loop_delay);
}
