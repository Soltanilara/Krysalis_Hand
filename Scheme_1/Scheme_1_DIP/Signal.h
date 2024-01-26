#ifndef SIGNAL_H
#define SIGNAL_H

//Output
#define MCP_CONTRACT 50
#define MCP_EXTEND 51

//MCP sends 2 wires to PIP, receives two wires from DIP
void setupSignal() {
  pinMode(MCP_CONTRACT, OUTPUT);
  pinMode(MCP_EXTEND, OUTPUT);

  digitalWrite(MCP_CONTRACT, LOW);
  digitalWrite(MCP_EXTEND, LOW);
}

//Outputs
void contractMCP() {
  digitalWrite(MCP_CONTRACT, HIGH);
  delay(10);
  digitalWrite(MCP_CONTRACT, LOW);
}

void extendMCP() {
  digitalWrite(MCP_EXTEND, HIGH);
  delay(10);
  digitalWrite(MCP_EXTEND, LOW);
}

#endif