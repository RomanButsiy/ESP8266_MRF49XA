

void Time_init() {
  HTTP.on("/Time", handle_Time);     // Синхронізувати час пристрою за запитом виду / Time
  HTTP.on("/timeZone", handle_time_zone);    // Установка часового поясу за запитом виду http://10.0.0.103/timeZone?timeZone=3
  timeSynch(jsonReadtoInt(configSetup, "timezone"));
}
void timeSynch(int zone){
  if (WiFi.status() == WL_CONNECTED) {
    // Налаштування з'єднання з NTP сервером
    configTime(zone * 3600, 0, "pool.ntp.org", "ua.pool.ntp.org");
    int i = 0;
    Serial.println("\nWaiting for time");
    while (!time(nullptr) && i < 10) {
      Serial.print(".");
      i++;
      delay(1000);
    }
  }
}
// Встановлення параметрів часового поясу за запитом виду http://10.0.0.103/timeZone?timeZone=3
void handle_time_zone() {
  jsonWrite(configSetup, "timezone", HTTP.arg("timeZone").toInt()); // Отримуємо значення timezone із запиту конвертуємо в int зберігаємо
  saveConfig();
  HTTP.send(200, "text/plain", "OK");
}

void handle_Time(){
  timeSynch(jsonReadtoInt(configSetup, "timezone"));
  HTTP.send(200, "text/plain", "OK"); // Відправляємо відповідь про виконання
  }

// Отримання поточного часу
String GetTime() {
 time_t now = time(nullptr); // Одержуємо час за допомогою бібліотеки time.h
 String Time = ""; // Рядок для результатів часу
 Time += ctime(&now); // Перетворимо час в рядок формату Thu Jan 19 15:20:11 2018
 int i = Time.indexOf(":"); // Шукаємо позицію першого символу ":"
 Time = Time.substring(i - 2, i + 6); // Виділяємо з рядка 2 символи перед символом ":" і 6 символів після
 return Time; // Повертаємо отриманий час
}

// Отримання дати
String GetDate() {
 time_t now = time(nullptr); // Одержуємо час за допомогою бібліотеки time.h
 String Data = ""; // Рядок для результатів часу
 Data += ctime(&now); // Перетворимо час в рядок формату Thu Jan 19 15:20:11 2018
 int i = Data.lastIndexOf(" "); // Шукаємо позицію останнього символу "пробіл"
 String Time = Data.substring(i - 8, i+1); // Виділяємо час і "пробіл"
 Data.replace(Time, ""); // Видаляємо з рядка 8 символів часу і "пробіл"
 Data.replace("\n", ""); // Видаляємо символ "розриву рядка"
 return Data; // Повертаємо отриману дату
}
