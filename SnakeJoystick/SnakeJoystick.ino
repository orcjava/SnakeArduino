#include "USB.h"
#include "USBHIDKeyboard.h"

USBHIDKeyboard Keyboard;

// ==================== Joystick ====================

#define pinJoystickX 6
#define pinJoystickY 7

// ==================== Buttons ====================

#define pinBtnGreen 17
#define pinBtnRed 18

// ==================== LEDs ====================

#define pinLedGreen 15
#define pinLedRed 16

// ==================== Variables ====================

int joystickX = 0;
int joystickY = 0;

int greenButton = HIGH;
int redButton = HIGH;

int lastDirection = 0;

// =====================================================
// SETUP
// =====================================================

void setup()
{
    Serial.begin(9600);

    pinMode(pinBtnGreen, INPUT_PULLUP);
    pinMode(pinBtnRed, INPUT_PULLUP);

    pinMode(pinLedGreen, OUTPUT);
    pinMode(pinLedRed, OUTPUT);

    digitalWrite(pinLedGreen, LOW);
    digitalWrite(pinLedRed, LOW);

    Keyboard.begin();
    USB.begin();

    delay(3000);
}

// =====================================================
// LOOP
// =====================================================

void loop()
{
    joystickX = analogRead(pinJoystickX);
    joystickY = analogRead(pinJoystickY);

    greenButton = digitalRead(pinBtnGreen);
    redButton = digitalRead(pinBtnRed);

    int currentDirection = 0;

    if (joystickX < 1200)
    {
        currentDirection = 1;
    }

    if (joystickX > 2800)
    {
        currentDirection = 2;
    }

    if (joystickY < 1200)
    {
        currentDirection = 3;
    }

    if (joystickY > 2800)
    {
        currentDirection = 4;
    }

    if (currentDirection != 0 && currentDirection != lastDirection)
    {
        if (currentDirection == 1)
        {
            Keyboard.press(KEY_LEFT_ARROW);
            delay(20);
            Keyboard.releaseAll();
        }

        if (currentDirection == 2)
        {
            Keyboard.press(KEY_RIGHT_ARROW);
            delay(20);
            Keyboard.releaseAll();
        }

        if (currentDirection == 3)
        {
            Keyboard.press(KEY_UP_ARROW);
            delay(20);
            Keyboard.releaseAll();
        }

        if (currentDirection == 4)
        {
            Keyboard.press(KEY_DOWN_ARROW);
            delay(20);
            Keyboard.releaseAll();
        }

        lastDirection = currentDirection;
    }

    if (currentDirection == 0)
    {
        lastDirection = 0;
    }

    if (greenButton == LOW)
    {
        Keyboard.press(KEY_RETURN);
        delay(20);
        Keyboard.releaseAll();
    }

    if (redButton == LOW)
    {
        Keyboard.press(KEY_RETURN);
        delay(20);
        Keyboard.releaseAll();
    }

    if (Serial.available())
    {
        String command = Serial.readStringUntil('\n');
        command.trim();

        if (command == "FOOD")
        {
            digitalWrite(pinLedGreen, HIGH);
            delay(150);
            digitalWrite(pinLedGreen, LOW);
        }

        if (command == "GAMEOVER")
        {
            for (int i = 0; i < 3; i++)
            {
                digitalWrite(pinLedRed, HIGH);
                delay(200);
                digitalWrite(pinLedRed, LOW);
                delay(200);
            }
        }
    }

    delay(10);
}