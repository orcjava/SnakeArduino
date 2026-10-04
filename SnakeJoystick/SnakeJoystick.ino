// ==================== Joystick ====================

#define pinJoystickX 6
#define pinJoystickY 7


// ==================== Variables ====================

int joystickX = 0;
int joystickY = 0;


// =====================================================
// SETUP
// =====================================================

void setup()
{
    Serial.begin(9600);

    Serial.println("================");
    Serial.println("   SNAKE");
    Serial.println("================");
    Serial.println("JOYSTICK TEST");
}


// =====================================================
// LOOP
// =====================================================

void loop()
{
    joystickX = analogRead(pinJoystickX);
    joystickY = analogRead(pinJoystickY);

    Serial.print("X: ");
    Serial.print(joystickX);

    Serial.print(" Y: ");
    Serial.println(joystickY);

    delay(200);
}