
void HTTP_init(void) {

  // --------------------Видаємо дані configJson
  HTTP.on("/config.live.json", HTTP_GET, []() {
    jsonWrite(configJson, "time", GetTime());
    jsonWrite(configJson, "date", GetDate());
    HTTP.send(200, "application/json", configJson);
  });
  // -------------------Видаємо дані configSetup
  HTTP.on("/config.setup.json", HTTP_GET, []() {
    HTTP.send(200, "application/json", configSetup);
  });
  // -------------------Перезавантажуємо пристрій
  HTTP.on("/restart", HTTP_GET, []() {
    String restart = HTTP.arg("device");          // Отримуємо значення device із запиту
    if (restart == "ok") {                        // Якщо значення дорівнює Ок
      HTTP.send(200, "text / plain", "Reset OK"); // Відправляємо відповідь Reset OK
      ESP.restart();                              // Перезавантажуємо модуль
    }
    else {                                        // або
      HTTP.send(200, "text / plain", "No Reset"); // Відправляємо відповідь No Reset
    }
  });
  // Додаємо функцію Update для перезапису прошивки по WiFi при 1М (256K SPIFFS) і вище
  httpUpdater.setup(&HTTP);
  // Запускаємо HTTP сервер
  HTTP.begin();
}
