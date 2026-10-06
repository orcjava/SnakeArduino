#define pinJoystickX 6
#define pinJoystickY 7
#define pinLedGreen 15
#define pinLedRed 16
#define pinBtnGreen 17
#define pinBtnRed 18

int joystickX = 0;
int joystickY = 0;
int btnGreenState = 0;
int btnRedState = 0;
String lastCommand = ""; 

void setup() {
    Serial.begin(115200); 
    pinMode(pinLedGreen, OUTPUT);
    pinMode(pinLedRed, OUTPUT);
    pinMode(pinBtnGreen, INPUT_PULLUP);
    pinMode(pinBtnRed, INPUT_PULLUP);
}

void loop() {
    if (Serial.available() > 0) {
        String incomingData = Serial.readStringUntil('\n');
        incomingData.trim();
        if (incomingData == "GAMEOVER") {
            digitalWrite(pinLedRed, HIGH);
            delay(1000);
            digitalWrite(pinLedRed, LOW);
        }
    }

    joystickX = analogRead(pinJoystickX);
    joystickY = analogRead(pinJoystickY);
    btnGreenState = digitalRead(pinBtnGreen);
    btnRedState = digitalRead(pinBtnRed);

    if (btnGreenState == LOW)  digitalWrite(pinLedGreen, HIGH);
    else                       digitalWrite(pinLedGreen, LOW);

    if (btnRedState == LOW)    digitalWrite(pinLedRed, HIGH);
    else if (Serial.available() == 0) digitalWrite(pinLedRed, LOW);

    String currentCommand = "";

    if (joystickY < 700) {
        currentCommand = "UP";
    } else if (joystickY > 3300) {
        currentCommand = "DOWN";
    }
    
    if (currentCommand == "") {
        if (joystickX < 700)       currentCommand = "LEFT";  
        else if (joystickX > 3300) currentCommand = "RIGHT"; 
    }
    
    if (currentCommand == "") {
        if (btnGreenState == LOW)      currentCommand = "GREEN";
        else if (btnRedState == LOW)   currentCommand = "RED";
    }

    if (currentCommand != "" && currentCommand != lastCommand) {
        Serial.println(currentCommand); 
        lastCommand = currentCommand;
    }
    
    if (joystickX >= 700 && joystickX <= 3300 && joystickY >= 700 && joystickY <= 3300 && btnGreenState == HIGH && btnRedState == HIGH) {
        lastCommand = ""; 
    }

    delay(30); 
}
