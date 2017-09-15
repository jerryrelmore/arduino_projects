// IR tank (water) depth sensor
// Version: 0.3
// Author: Jerry Elmore
// Date: 9-Jan-2014
// UPDATED to lessen number of leads needed from detector/emitters
//  Running both emitters off of one DIGITAL PIN
//  Reading detector from green wire to A1, red wire goes to D7, and black goes to ground.
//  NOTE: Not sure why, but don't need 5V to anode of IR detector. It seems that it's sensitive enough (for my purposes) to send a detectable signal to the analog
//        in on the Arduino.
//
// This sketch bounces an IR signal off a floating ball within
// a PVC tube to measure water level in an aquaponics fish tank.
//
// *** SETUP DIAGRAM (not to scale obviously :P) ***
// below (to Arduino)
//  ----x                    ______________
//      |                   ( _____________---> to growbed(s) 
//     |^|                  ||
//     |_|                  ||
//     | |                  ||
//  \--|-|------------------||--/
//   | |.|                  || |
//   | | |                  || |
//   |~|O|~~~~~~~~~~~~~~~~~~||~|
//   | | |                  || |       
//   | | |       <:x        || |
//   | |.|                  || |
//   | |.|                  || |
//   | |.|                  || |
//   | |.|           x:>    || |
//   | |.|                  || |
//   | |_|                  || |
//   |                      || |
//   |          x:>      ___|| |
//   |  <:x             |pump| |
//   |                  |____| |
//   |                         |
//   |_________________________|


// SET GLOBAL CONSTANTS
const int ANALOG_IN_PIN = A1;     // Set digital pins we use to send IR signal and then analog pin we use to measure
const int DIGITAL_OUT_LED1 = 7;   // Ditto
//const int DIGITAL_OUT_LED2 = 10;  // Ditto
const int FLASH_ON = 1;           // number of ms IR emitter is ON
const int FLASH_OFF = 1;          // number of ms IR emitter is OFF
const int IR_ARRAY_SIZE = 250;    // use this to adjust number of readings of working (not baseline) IR readings
const int MAX_FILL_LEVEL = 100;   // Maximum fish tank fill level (percentage)
const int MIN_FILL_LEVEL = 0;     // Mininum fish tank fill level (percentage)
const int FILL_LEVEL_DANGER = 25; // Fish tank fill level (percentage) at which pump needs to shut down

// SET GLOBAL VARIABLES
int average_IR_reading_BOTH_LEDS;                  // used to store final, single average from both LEDs
int base_IR_reading = 0;                           // base value to take into account ambient light - will adjust this hourly (or so) to maintain calibration
unsigned long lastTime, duration, total_sys_uptime = 0;  // time variables to measure space between reinitialization of ambient light readings 


//------------------------SETUP FUNCTION---------------------------
void setup() {
  // Setup digital pins for IR emitters
  pinMode(DIGITAL_OUT_LED1, OUTPUT);
  //pinMode(DIGITAL_OUT_LED2, OUTPUT);
  
  // Establish serial connection
  Serial.begin(115200);
  
  // Call depth gauge initialization function
  base_IR_reading = initialize_IR();
  
  // Establish base time for tracking how often ambient IR baseline needs adjusted, how long the sketch has been running, and other uses down the line
  lastTime = millis();
}



//------------------------MAIN LOOP--------------------------------
void loop() {
  
  // DETERMINE IF NEW BASELINE IR READING NEEDS ESTABLISHED AND, IF SO, ESTABLISH IT
  duration = millis() - lastTime;        // How many ms has it been since we last took a baseline IR measurement
  if (duration >= 3600000)               // 3,600,000 ms = 1 hour
  {
     base_IR_reading = initialize_IR();  // If last baseline IR was longer than an hour ago, pull a new baseline IR 
     lastTime = millis();                // Establish new lastTime
     
     //DEBUG
     Serial.print("\nbase_IR_reading = ");
     Serial.print(base_IR_reading);
  }
  
  // GET NEW IR READING AND DETERMINE CURRENT FILL LEVEL
  average_IR_reading_BOTH_LEDS = abs(current_IR_reading(base_IR_reading));    // call the function to determine current tank fill level and return abs value (since value tends to be negative under most conditions)
    // DEBUG
    Serial.print("average_IR_reading_BOTH_LEDS = ");          // Display average reading from 2 sets of 4 readings from LEDs 1 and 2
    Serial.print(average_IR_reading_BOTH_LEDS);
    Serial.print("\n\n");
       
  // IF FILL LEVEL IS AT OR BELOW DANGER LEVEL, SHUT OFF PUMP
  if (average_IR_reading_BOTH_LEDS <= FILL_LEVEL_DANGER)
  {
    pump_shutoff();
  }
  
  // TRACK DAILY HIGHS AND LOWS
    
  // LOG RESULTS TO FILE
  
  // LOG RESULTS TO WEB PAGE
}



//--------------------INFRARED INITIALIZATION FUNCTION------------------------
int initialize_IR() {   
  int x, base_IR_setup = 0;      // Setup counter and baseline IR reading
  
  for (x = 0; x <= 50; ++x)      // FOR loop to take 50 baseline IR readings with no emitter activity
  {
      base_IR_setup += analogRead(ANALOG_IN_PIN);    // Take current IR detector reading and add to previous readings
      delay(100);      // Delay 100 ms
      if ((x % 10 == 0) && (x != 0))
      { 
        Serial.print ("\nEstablishing baseline in ");
        Serial.print(6 - (x / 10));
        Serial.print(" secs...\n");
      }
  }
  
  base_IR_setup /= x;                                // Divide 5 secs worth of summed readings by the number of readings taken for an average IR detector baseline reading (with no IR emitter flashes)
  Serial.print("base_IR_setup = ");
  Serial.print(base_IR_setup);
  Serial.println("");
  return base_IR_setup;                              // Pass the result back to the main loop
}



//---------------------CURRENT INFRARED READING FUNCTION----------------------
int current_IR_reading(int current_base) {  // TAKE INFRARED READINGS TO MONITOR FISH TANK FILL LEVEL
  int IR_reading_BOTH_LEDS;                 // used to store IR detector readings from first LED's signal
  int x;                                    // Setup counter variable
  int average = 0;                          // Setup average tracker for this function
  
  digitalWrite(DIGITAL_OUT_LED1, LOW);               // Ensure both digital pins are OFF prior taking readings
  //digitalWrite(DIGITAL_OUT_LED2, LOW);
  
  for (x = 0; x < IR_ARRAY_SIZE; x++)
  {
      delay(1);        // Wait 1 ms between sets of readings
      
      // Sequence to capture readings using LED1 and LED2
      digitalWrite(DIGITAL_OUT_LED1, HIGH);        // Turn first LED ON
      //digitalWrite(DIGITAL_OUT_LED2, HIGH);      // Turn second LED ON
      IR_reading_BOTH_LEDS = analogRead(ANALOG_IN_PIN); //map(analogRead(ANALOG_IN_PIN), current_base, -1023, MIN_FILL_LEVEL, MAX_FILL_LEVEL);    // Take all readings and map them to a scale of 1 to 100
      digitalWrite(DIGITAL_OUT_LED1, LOW);        // Turn first LED OFF
      //digitalWrite(DIGITAL_OUT_LED2, LOW);      // Turn second LED OFF
      
      // Average both readings and sum them to previous reading averages
      average += IR_reading_BOTH_LEDS;
  }
  
  average /= IR_ARRAY_SIZE;        // get a final average from amongst all 80 readings
  return average;                  // send this value back to the main loop

}


//-------------------PUMP SHUTOFF FUNCTION---------------------------------
int pump_shutoff() {       // KILL THE PUMP IF WATER LINE IS BELOW DANGER LEVEL

   // Yada, yada - code here when I get valves for pump
}
