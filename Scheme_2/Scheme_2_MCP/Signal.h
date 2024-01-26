#ifndef SIGNAL_H
#define SIGNAL_H

#define PIP_CONTRACT 17

//MCP sends 2 wires to PIP, receives two wires from DIP
void setupSignal() {
  pinMode(PIP_CONTRACT, OUTPUT);

  digitalWrite(PIP_CONTRACT, LOW);
}

void contractPIP() {
  digitalWrite(PIP_CONTRACT, HIGH);
  delay(10);
  digitalWrite(PIP_CONTRACT, LOW);
}

#endif