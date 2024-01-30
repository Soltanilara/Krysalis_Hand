#ifndef SIGNAL_H
#define SIGNAL_H

//Output
#define MCP 16
#define DIP 17

//MCP sends 2 wires to PIP, receives two wires from DIP
void setupSignal() {
  pinMode(MCP, OUTPUT);
  pinMode(DIP, OUTPUT);

  digitalWrite(MCP, LOW);
  digitalWrite(DIP, LOW);
}

//Outputs
void sendComplete() {
  digitalWrite(MCP, HIGH);
  digitalWrite(DIP, HIGH);
  delay(10);
  digitalWrite(MCP, LOW);
  digitalWrite(DIP, LOW);
}

#endif