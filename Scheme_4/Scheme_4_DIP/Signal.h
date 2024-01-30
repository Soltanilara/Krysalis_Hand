#ifndef SIGNAL_H
#define SIGNAL_H

//Output
#define MCP 16
#define PIP 17

//MCP sends 2 wires to PIP, receives two wires from DIP
void setupSignal() {
  pinMode(MCP, OUTPUT);
  pinMode(PIP, OUTPUT);

  digitalWrite(MCP, LOW);
  digitalWrite(PIP, LOW);
}

//Outputs
void sendComplete() {
  digitalWrite(MCP, HIGH);
  digitalWrite(PIP, HIGH);
  delay(10);
  digitalWrite(MCP, LOW);
  digitalWrite(PIP, LOW);
}
#endif