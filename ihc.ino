#include <BleKeyboard.h>

BleKeyboard bleKeyboard("Mando ESP32", "Creador Pro", 100);

const int pinX = 34;
const int pinY = 35;
const int btnSaltar = 18;
const int btnReset = 19;

// Variables para evitar envíos repetidos
bool moviendoW = false, moviendoS = false, moviendoA = false, moviendoD = false;

void setup() {
  Serial.begin(115200);
  pinMode(btnSaltar, INPUT_PULLUP);
  pinMode(btnReset, INPUT_PULLUP);
  bleKeyboard.begin();
}

void loop() {
  if(bleKeyboard.isConnected()) {
    int xValue = analogRead(pinX);
    int yValue = analogRead(pinY);

    // Movimiento Vertical (W / S)
    if(yValue < 1000 && !moviendoW) { bleKeyboard.press('w'); moviendoW = true; }
    else if(yValue >= 1000 && moviendoW) { bleKeyboard.release('w'); moviendoW = false; }
    
    if(yValue > 3000 && !moviendoS) { bleKeyboard.press('s'); moviendoS = true; }
    else if(yValue <= 3000 && moviendoS) { bleKeyboard.release('s'); moviendoS = false; }

    // Movimiento Horizontal (A / D)
    if(xValue < 1000 && !moviendoA) { bleKeyboard.press('a'); moviendoA = true; }
    else if(xValue >= 1000 && moviendoA) { bleKeyboard.release('a'); moviendoA = false; }

    if(xValue > 3000 && !moviendoD) { bleKeyboard.press('d'); moviendoD = true; }
    else if(xValue <= 3000 && moviendoD) { bleKeyboard.release('d'); moviendoD = false; }

    // Botón Saltar
    if(digitalRead(btnSaltar) == LOW) bleKeyboard.press(' '); 
    else bleKeyboard.release(' ');

    delay(20); // Delay necesario para estabilidad
  }
}