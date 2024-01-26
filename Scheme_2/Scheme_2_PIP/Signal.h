#ifndef SIGNAL_H
#define SIGNAL_H

//Output
#define MCP_EXTEND 17
#define DIP_CONTRACT 16

//MCP sends 2 wires to PIP, receives two wires from DIP
void setupSignal() {
  pinMode(MCP_EXTEND, OUTPUT);
  pinMode(DIP_CONTRACT, OUTPUT);

  digitalWrite(MCP_EXTEND, LOW);
  digitalWrite(DIP_CONTRACT, LOW);
}

//Outputs
void contractDIP() {
  digitalWrite(DIP_CONTRACT, HIGH);
  delay(10);
  digitalWrite(DIP_CONTRACT, LOW);
}

void extendMCP() {
  digitalWrite(MCP_EXTEND, HIGH);
  delay(10);
  digitalWrite(MCP_EXTEND, LOW);
}

#endif