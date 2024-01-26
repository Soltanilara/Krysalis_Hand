#ifndef SIGNAL_H
#define SIGNAL_H

#define PIP_CONTRACT 12
#define PIP_EXTEND 13

//MCP sends 2 wires to PIP, receives two wires from DIP
void setupSignal() {
  pinMode(PIP_CONTRACT, OUTPUT);
  pinMode(PIP_EXTEND, OUTPUT);

  digitalWrite(PIP_CONTRACT, LOW);
  digitalWrite(PIP_EXTEND, LOW);
}

void contractPIP() {
  digitalWrite(PIP_CONTRACT, HIGH);
  delay(10);
  digitalWrite(PIP_CONTRACT, LOW);
}

void extendPIP() {
  digitalWrite(PIP_EXTEND, HIGH);
  delay(10);
  digitalWrite(PIP_EXTEND, LOW);
}

#endif