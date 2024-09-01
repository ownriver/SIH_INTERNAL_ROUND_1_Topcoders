#include "time.h"
#include <LiquidCrystal_I2C.h>
#include "thingProperties.h"

LiquidCrystal_I2C lcd(0x27, 16, 2);
int k = 5; // Example value to add to hours
int o = 30;
int alarmHour = 0;
int alarmMinute = 1;
int currentHour = 0;
int currentMinute = 0;
bool alarmActive = false;
bool alarmSnoozed = false;
const char* ntpServer1 = "pool.ntp.org";
const char* ntpServer2 = "time.nist.gov";
const long  gmtOffset_sec = 0;
const int   daylightOffset_sec = 0;

// Button Pins
const int button1Pin = 4; // Button to toggle screens
const int button2Pin = 5; // Button to start/stop/reset timer
const int button3Pin = 18; // Button to stop/snooze alarm

// Screen States
enum ScreenState { CLOCK_SCREEN, ALARM_SCREEN, TIMER_SCREEN };
ScreenState currentScreen = CLOCK_SCREEN;

bool timerRunning = false;
bool timerReset = false;
unsigned long timerStartMillis;
unsigned long timerElapsedMillis = 0;

void setup() {
  Serial.begin(115200);
  delay(1500); 
  initProperties();

  ArduinoCloud.begin(ArduinoIoTPreferredConnection);
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();

  pinMode(button1Pin, INPUT_PULLUP);
  pinMode(button2Pin, INPUT_PULLUP);
  pinMode(button3Pin, INPUT_PULLUP);
  pinMode(13, OUTPUT);
  lcd.init();
  lcd.backlight();

  // Initialize WiFi and NTP
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer1, ntpServer2);
}

void loop() {
  ArduinoCloud.update();
  
  // Handle screen toggling
  if (digitalRead(button1Pin) == LOW) {
    delay(200); // Debounce delay
    toggleScreen();
  }
  
  // Handle stop/snooze button for alarm
  if (digitalRead(button3Pin) == LOW && alarmActive) {
    delay(200); // Debounce delay
    if (alarmSnoozed) {
      stopAlarm();
    } else {
      snoozeAlarm();
    }
  }

  switch (currentScreen) {
    case CLOCK_SCREEN:
      showClockScreen();
      break;
    case ALARM_SCREEN:
      showAlarmScreen();
      break;
    case TIMER_SCREEN:
      showTimerScreen();
      break;
  }

  checkAlarm();
  delay(1000); // Update every second
}

void toggleScreen() {
  if (currentScreen == CLOCK_SCREEN) {
    currentScreen = ALARM_SCREEN;
  } else if (currentScreen == ALARM_SCREEN) {
    currentScreen = TIMER_SCREEN;
  } else {
    currentScreen = CLOCK_SCREEN;
  }
  lcd.clear();
}

void showClockScreen() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("No time available (yet)");
    lcd.clear();
    lcd.print("No time available");
    return;
  }

  // Adjust time by offset values
  timeinfo.tm_min += o;
  if (timeinfo.tm_min >= 60) {
    timeinfo.tm_min -= 60;
    timeinfo.tm_hour++;
  } else if (timeinfo.tm_min < 0) {
    timeinfo.tm_min += 60;
    timeinfo.tm_hour--;
  }

  timeinfo.tm_hour += k;
  if (timeinfo.tm_hour >= 24) {
    timeinfo.tm_hour -= 24;
  } else if (timeinfo.tm_hour < 0) {
    timeinfo.tm_hour += 24;
  }

  currentHour = timeinfo.tm_hour;
  currentMinute = timeinfo.tm_min;

  char period[] = "AM";
  int displayHour = currentHour;
  if (bool_1) {  // 12-hour format
    if (currentHour == 0) {
      displayHour = 12;
    } else if (currentHour > 12) {
      displayHour = currentHour - 12;
      strcpy(period, "PM");
    } else if (currentHour == 12) {
      strcpy(period, "PM");
    }
  }

  char formattedTime[9];
  if (bool_1) {
    sprintf(formattedTime, "%02d:%02d %s", displayHour, currentMinute, period);
  } else {
    sprintf(formattedTime, "%02d:%02d", currentHour, currentMinute);
  }

  char formattedDate[12];
  strftime(formattedDate, sizeof(formattedDate), "%b %d %Y", &timeinfo);

  time02 = String(formattedDate) + "\n" + String(formattedTime);

  lcd.clear();
  lcd.print(formattedDate);
  lcd.setCursor(0, 1);
  lcd.print(formattedTime);

  // Debugging
  Serial.print("Current Time: ");
  Serial.println(formattedTime);
}

void showAlarmScreen() {
  lcd.clear();
  lcd.print("Alarm Set for");
  char alarmTimeStr[6];
  sprintf(alarmTimeStr, "%02d:%02d", alarmHour, alarmMinute);
  lcd.setCursor(0, 1);
  lcd.print(alarmTimeStr);

  // Debugging
  Serial.print("Alarm Time: ");
  Serial.println(alarmTimeStr);
}

void showTimerScreen() {
  if (digitalRead(button2Pin) == LOW) {
    delay(200); // Debounce delay
    handleTimerButtonPress();
  }
  
  lcd.clear();
  lcd.print("Timer: ");
  lcd.setCursor(0, 1);
  
  unsigned long displayMillis = timerElapsedMillis;
  if (timerRunning) {
    displayMillis += millis() - timerStartMillis;
  }

  int seconds = (displayMillis / 1000) % 60;
  int minutes = (displayMillis / (1000 * 60)) % 60;
  lcd.printf("%02d:%02d", minutes, seconds);
}

void handleTimerButtonPress() {
  if (timerRunning) {
    timerElapsedMillis += millis() - timerStartMillis;
    timerRunning = false;
    timerReset = true;
  } else if (timerReset) {
    timerElapsedMillis = 0;
    timerReset = false;
  } else {
    timerStartMillis = millis();
    timerRunning = true;
  }
}

void onTime02Change() {}

void onBool1Change() {}

void onAlarm1Change() {
  unsigned long alarmTimestamp = static_cast<unsigned long>(alarm_1);

  time_t rawtime = alarmTimestamp;
  struct tm* timeinfo = localtime(&rawtime);

  alarmHour = timeinfo->tm_hour;
  alarmMinute = timeinfo->tm_min;

  Serial.print("Alarm updated to ");
  Serial.print(alarmHour);
  Serial.print(":");
  if (alarmMinute < 10) {
    Serial.print("0");
  }
  Serial.println(alarmMinute);
}

void onCityChange() {
  switch (city) {
    case 1: k = 5; o = 30; break; // New Delhi
    case 2: k = 1; o = 0; break;  // London
    case 3: k = 3; o = 0; break;  // Istanbul
    case 4: k = -4; o = 0; break; // New York
    case 5: k = 2; o = 0; break;  // Prague
    case 6: k = 9; o = 0; break;  // Tokyo
    case 7: k = 2; o = 0; break;  // Amsterdam
    default: k = 5; o = 30; break; // Default case if needed
  }
}

void stopAlarm() {
  alarmActive = false;
  alarmSnoozed = false;
  lcd.clear();
  lcd.print("Alarm Stopped");
  digitalWrite(13, LOW);
  delay(2000);
  lcd.clear();

  // Debugging
  Serial.println("Alarm Stopped");
}

void snoozeAlarm() {
  alarmSnoozed = true;
  alarmMinute += 2; // Add snooze duration to alarm time
  if (alarmMinute >= 60) {
    alarmMinute -= 60;
    alarmHour++;
    if (alarmHour >= 24) {
      alarmHour = 0;
    }
  }
  lcd.clear();
  lcd.print("Alarm Snoozed");
  delay(2000);
  lcd.clear();

  // Debugging
  Serial.print("Alarm Snoozed to: ");
  Serial.print(alarmHour);
  Serial.print(":");
  if (alarmMinute < 10) {
    Serial.print("0");
  }
  Serial.println(alarmMinute);
}

void triggerAlarm() {
  alarmActive = true;
  lcd.clear();
  lcd.print("ALARM! Press Btn3");
  digitalWrite(13, HIGH);

  // Debugging
  Serial.println("Alarm Triggered!");
}

void checkAlarm() {
  if (!alarmActive && currentHour == alarmHour && currentMinute == alarmMinute) {
    triggerAlarm();
  }
}
