// ==================== הגדרת הפינים (חיווט) ====================
#define pinJoystickX 4  // ג'ויסטיק ציר X (ימינה/שמאלה) - בורג 4 הכחול
#define pinJoystickY 5  // ג'ויסטיק ציר Y (למעלה/למטה) - בורג 5 הכחול

#define pinLedGreen 15  // מנורה ירוקה - בורג 15 הכחול
#define pinLedRed 16    // מנורה אדומה - בורג 16 הכחול
#define pinBtnGreen 17  // כפתור ירוק - בורג 17 הכחול
#define pinBtnRed 18    // כפתור אדום - בורג 18 הכחול

// ==================== משתנים ====================
int joystickX = 0;
int joystickY = 0;
int btnGreenState = 0;
int btnRedState = 0;

void setup()
{
    // הפעלת תקשורת טורית להצגת נתונים על המסך
    Serial.begin(9600);

    // הגדרת המנורות כיציאות (OUTPUT)
    pinMode(pinLedGreen, OUTPUT);
    pinMode(pinLedRed, OUTPUT);

    // הגדרת הכפתורים ככניסות עם נגד משיכה פנימי (INPUT_PULLUP)
    pinMode(pinBtnGreen, INPUT_PULLUP);
    pinMode(pinBtnRed, INPUT_PULLUP);
}

void loop()
{
    // -------------------------------------------------
    // 1. טיפול בכפתורים ומנורות (לחיצה מדליקה מנורה)
    // -------------------------------------------------
    btnGreenState = digitalRead(pinBtnGreen);
    btnRedState = digitalRead(pinBtnRed);

    // כפתור ירוק ומנורה ירוקה
    if (btnGreenState == LOW) { 
        digitalWrite(pinLedGreen, HIGH);
    } else {
        digitalWrite(pinLedGreen, LOW);
    }

    // כפתור אדום ומנורה אדומה
    if (btnRedState == LOW) { 
        digitalWrite(pinLedRed, HIGH);
    } else {
        digitalWrite(pinLedRed, LOW);
    }

    // -------------------------------------------------
    // 2. קריאת ערכי הג'ויסטיק וזיהוי כיוונים
    // -------------------------------------------------
    joystickX = analogRead(pinJoystickX);
    joystickY = analogRead(pinJoystickY);

    // הדפסת הערכים הגולמיים (ב-ESP32 הטווח הוא בין 0 ל-4095)
    Serial.print("X: "); Serial.print(joystickX);
    Serial.print(" | Y: "); Serial.print(joystickY);
    Serial.print(" -> כיוון: ");

    // זיהוי כיוון ציר X (ימינה / שמאלה)
    if (joystickX < 1000) {
        Serial.print("שמאלה ");
    } else if (joystickX > 3000) {
        Serial.print("ימינה ");
    }

    // זיהוי כיוון ציר Y (למעלה / למטה)
    if (joystickY < 1000) {
        Serial.print("למעלה");
    } else if (joystickY > 3000) {
        Serial.print("למטה");
    }
    
    // אם הג'ויסטיק במרכז
    if (joystickX >= 1000 && joystickX <= 3000 && joystickY >= 1000 && joystickY <= 3000) {
        Serial.print("מרכז");
    }

    Serial.println(); // ירידת שורה בגרף/במסך
    delay(150);       // השהייה קלה לקריאה נוחה במסך
}
