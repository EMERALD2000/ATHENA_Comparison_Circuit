/*
Comparison Circuit
 * Compare 6 port values to determine one with highest voltage (indicates highest RF presence)
 * Use mcu_initial_map.ino mapping
 * This version uses LED as indicator
 */
 // look into Arduino MCU clock - how often/quickly is the comparison occuring to see which port is activated?
 // internal clock can operate at max 16 MHz
 // have array print to monitor - need mechanism to tell when MCU is still deciding the max voltage output
// requires 10mV difference between voltages to make decision
int port1 = A0, port2 = A1, port3 = A2, port4 = A3, port5 = A4, port6 = A5; // pins analog sensors are attached to
int portOn = 0; // index (port) that holds highest value
int led1 = 2, led2 = 3, led3 = 4, led4 = 5, led5 = 6, led6 = 7; // assign LEDs to digital output ports


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(led5, OUTPUT);
  pinMode(led6, OUTPUT);
}

// map inputs to output (from mcu_initial_map)
void mapPorts(int port) {
    if (portOn == 0) { // if no port has highest analog value
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    digitalWrite(led5, LOW);
    digitalWrite(led6, LOW);
    }

  else if (portOn == 1) { // if first port has highest analog value
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    digitalWrite(led5, LOW);
    digitalWrite(led6, LOW);
  }
  else if (portOn == 2) { // if second port has highest analog value
    digitalWrite(led2, HIGH);
    digitalWrite(led1, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    digitalWrite(led5, LOW);
    digitalWrite(led6, LOW);
  }
  else if (portOn == 3) { // if third port has highest analog value
    digitalWrite(led3, HIGH);
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led4, LOW);
    digitalWrite(led5, LOW);
    digitalWrite(led6, LOW);
  }
  else if (portOn == 4) { // if fourth port has highest analog value
    digitalWrite(led4, HIGH);
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led5, LOW);
    digitalWrite(led6, LOW);
  }
  else if (portOn == 5) { // if fifth port has highest analog value
    digitalWrite(led5, HIGH);
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    digitalWrite(led6, LOW);    
  }  
  else if (portOn == 6) { // if sixth port has highest analog value
    digitalWrite(led6, HIGH);
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    digitalWrite(led4, LOW);
    digitalWrite(led5, LOW);
  }

  delay(1000);  // waits for the servo to get there
}

void loop() {
  int portVals[6];
  int maxVoltage = 0;
  
  // read port values
  portVals[0] = analogRead(port1);
  portVals[1] = analogRead(port2);
  portVals[2] = analogRead(port3);
  portVals[3] = analogRead(port4);
  portVals[4] = analogRead(port5);
  portVals[5] = analogRead(port6);    

  // compare all port voltages to find maximum
  for(int i = 0; i < 6; i++) {
    if(portVals[i] > maxVoltage) {
      maxVoltage = portVals[i];
      portOn = i+1;
    }
    else if (portVals[i] == maxVoltage && maxVoltage != 0) { // if portVals[i] == maxVoltage, print an error statement
      Serial.print("Error: Equal voltage at multiple ports. Cannot decide.");
    }
    else if (maxVoltage == 0) {
       Serial.print("Error: Zero voltage recieved.");
    }
  }
  
  // Serial.print("maxVoltage: ");
  // Serial.print(maxVoltage);  // print maxVoltage after iterating through ports
  // Serial.print("\t"); // tab
  // Serial.print("\n");
//Serial.print("portOn: ");
  Serial.print(portOn); // print which port has the current maxVoltage
  Serial.print("\n");
  mapPorts(portOn);
}
