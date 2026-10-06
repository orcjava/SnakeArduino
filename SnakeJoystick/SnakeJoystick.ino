// ==================== Joystick ====================
#define pinJoystickX 6  // ג'ויסטיק ציר X - בורג 6 הכחול (נותן כ-2000 באמצע)
#define pinJoystickY 7  // ג'ויסטיק ציר Y - בורג 7 הכחול (נותן כ-2000 באמצע)

// ==================== LEDs & Buttons ====================
#define pinLedGreen 15  // מנורה ירוקה - בורג 15 הכחול
#define pinLedRed 16    // מנורה אדומה - בורג 16 הכחול
#define pinBtnGreen 17  // כפתור ירוק - בורג 17 הכחול
#define pinBtnRed 18    // כפתור אדום - בורג 18 הכחול

// ==================== Variables ====================
int joystickX = 0;
int joystickY = 0;
int btnGreenState = 0;
int btnRedState = 0;

// =====================================================
// SETUP
// =====================================================
void setup()
{
    Serial.begin(9600);

    // הגדרת המנורות כיציאות (OUTPUT)
    pinMode(pinLedGreen, OUTPUT);
    pinMode(pinLedRed, OUTPUT);

    // הגדרת הכפתורים ככניסות עם נגד משיכה פנימי (INPUT_PULLUP)
    pinMode(pinBtnGreen, INPUT_PULLUP);
    pinMode(pinBtnRed, INPUT_PULLUP);

    Serial.println("================");
    Serial.println("   SNAKE");
    Serial.println("================");
    Serial.println("CONTROLLER TEST");
}

// =====================================================
// LOOP
// =====================================================
void loop()
{
    // 1. טיפול בכפתורים ובמנורות (לחיצה מדליקה מנורה תואמת)
    btnGreenState = digitalRead(pinBtnGreen);
    btnRedState = digitalRead(pinBtnRed);

    if (btnGreenState == LOW) { 
        digitalWrite(pinLedGreen, HIGH); // כפתור ירוק לחוץ -> מנורה ירוקה נדלקת
    } else {
        digitalWrite(pinLedGreen, LOW);
    }

    if (btnRedState == LOW) { 
        digitalWrite(pinLedRed, HIGH);  // כפתור אדום לחוץ -> מנורה אדומה נדלקת
    } else {
        digitalWrite(pinLedRed, LOW);
    }

    // 2. קריאת ערכי הג'ויסטיק (מפינים 6 ו-7)
    joystickX = analogRead(pinJoystickX);
    joystickY = analogRead(pinJoystickY);

    // הדפסת הערכים הגולמיים למסך
    Serial.print("X: "); Serial.print(joystickX);
    Serial.print(" | Y: "); Serial.print(joystickY);
    Serial.print(" -> מצב: ");

    // בדיקת כיוון לפי הטווחים (קטן מ-700 או גדול מ-3300)
    if (joystickY < 700) {
        Serial.print("למעלה ");
    } else if (joystickY > 3300) {
        Serial.print("למטה ");
    }

    if (joystickX < 700) {
        Serial.print("שמאלה ");
    } else if (joystickX > 3300) {
        Serial.print("ימינה ");
    }
    
    // בדיקה אם הג'ויסטיק באמצע (סביב 2000)
    if (joystickX >= 700 && joystickX <= 3300 && joystickY >= 700 && joystickY <= 3300) {
        Serial.print("אמצע");
    }

    Serial.println(); 
    delay(200);       
}
