// ==================== הגדרת פינים (חיווט) ====================
#define pinJoystickX 6  // ג'ויסטיק ציר X - בורג 6 הכחול
#define pinJoystickY 7  // ג'ויסטיק ציר Y - בורג 7 הכחול

#define pinLedGreen 15  // מנורה ירוקה - בורג 15 הכחול
#define pinLedRed 16    // מנורה אדומה - בורג 16 הכחול
#define pinBtnGreen 17  // כפתור ירוק - בורג 17 הכחול
#define pinBtnRed 18    // כפתור אדום - בורג 18 הכחול

// ==================== משתנים פנימיים ====================
int joystickX = 0;
int joystickY = 0;
int btnGreenState = 0;
int btnRedState = 0;

// משתנה שזוכר את הפקודה האחרונה שנשלחה (מונע הצפה של ה-Serial)
String lastCommand = ""; 

// =====================================================
// SETUP
// =====================================================
void setup() {
    // הפעלת תקשורת טורית במהירות 115200 (חובה להתאים לדפדפן!)
    Serial.begin(115200); 

    // הגדרת המנורות (לדים) כיציאות
    pinMode(pinLedGreen, OUTPUT);
    pinMode(pinLedRed, OUTPUT);

    // הגדרת הכפתורים ככניסות עם נגד משיכה פנימי
    pinMode(pinBtnGreen, INPUT_PULLUP);
    pinMode(pinBtnRed, INPUT_PULLUP);
}

// =====================================================
// LOOP
// =====================================================
void loop() {
    // 1. קריאת המצב הפיזי של הרכיבים
    joystickX = analogRead(pinJoystickX);
    joystickY = analogRead(pinJoystickY);
    btnGreenState = digitalRead(pinBtnGreen);
    btnRedState = digitalRead(pinBtnRed);

    // 2. הפעלת המנורות לפי לחיצה על הכפתורים
    if (btnGreenState == LOW)  digitalWrite(pinLedGreen, HIGH);
    else                       digitalWrite(pinLedGreen, LOW);

    if (btnRedState == LOW)    digitalWrite(pinLedRed, HIGH);
    else                       digitalWrite(pinLedRed, LOW);

    // 3. לוגיקת זיהוי כיוונים ובניית פקודה לדפדפן
    String currentCommand = "";

    if (joystickY < 700)       currentCommand = "UP";
    else if (joystickY > 3300) currentCommand = "DOWN";
    else if (joystickX < 700)  currentCommand = "LEFT";
    else if (joystickX > 3300) currentCommand = "RIGHT";
    else if (btnGreenState == LOW) currentCommand = "GREEN";
    else if (btnRedState == LOW)   currentCommand = "RED";

    // 4. שליחת הפקודה לדפדפן רק כאשר היא משתנה
    if (currentCommand != "" && currentCommand != lastCommand) {
        Serial.println(currentCommand); // שליחת הפקודה עם ירידת שורה (\n)
        lastCommand = currentCommand;
    }
    
    // אם חזרנו למרכז (אזור ה-2000), מאפסים את הפיקוד האחרון
    if (joystickX >= 700 && joystickX <= 3300 && joystickY >= 700 && joystickY <= 3300 && btnGreenState == HIGH && btnRedState == HIGH) {
        lastCommand = "";
    }

    delay(30); // השהייה קלה מאוד לתגובתיות חלקה ומהירה במשחק
}
