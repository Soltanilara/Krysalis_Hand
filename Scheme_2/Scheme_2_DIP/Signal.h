#ifndef SIGNAL_H
#define SIGNAL_H

//Output
#define PIP_EXTEND 16

//MCP sends 2 wires to PIP, receives two wires from DIP
void setupSignal() {
  pinMode(PIP_EXTEND, OUTPUT);

  digitalWrite(PIP_EXTEND, LOW);
}

//Outputs
void extendPIP() {
  digitalWrite(PIP_EXTEND, HIGH);
  delay(10);
  digitalWrite(PIP_EXTEND, LOW);
}

#endif