#ifndef SIGNAL_H
#define SIGNAL_H

#define PIP 17
#define DIP 16

//MCP sends 2 wires to PIP, receives two wires from DIP
void setupSignal() {
  pinMode(PIP, OUTPUT);
  pinMode(DIP, OUTPUT);

  digitalWrite(PIP, LOW);
  digitalWrite(DIP, LOW);
}

void sendComplete() {
  digitalWrite(PIP, HIGH);
  digitalWrite(DIP, HIGH);
  delay(10);
  digitalWrite(PIP, LOW);
  digitalWrite(DIP, LOW);
}

#endif