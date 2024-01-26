#ifndef SIGNAL_H
#define SIGNAL_H

//Output
#define DIP_EXTEND 52
#define DIP_CONTRACT 53

//MCP sends 2 wires to PIP, receives two wires from DIP
void setupSignal() {
  pinMode(DIP_EXTEND, OUTPUT);
  pinMode(DIP_CONTRACT, OUTPUT);

  digitalWrite(DIP_EXTEND, LOW);
  digitalWrite(DIP_CONTRACT, LOW);
}

//Outputs
void contractDIP() {
  digitalWrite(DIP_CONTRACT, HIGH);
  delay(10);
  digitalWrite(DIP_CONTRACT, LOW);
}

void extendDIP() {
  digitalWrite(DIP_EXTEND, HIGH);
  delay(10);
  digitalWrite(DIP_EXTEND, LOW);
}

#endif