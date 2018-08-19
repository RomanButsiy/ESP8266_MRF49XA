
void LANG_init(void) {
  HTTP.on("/lang", HTTP_GET, []() {
  jsonWrite(configSetup, "lang", HTTP.arg("set"));
  saveConfig();                 // Функція збереження даних у Flash
  HTTP.send(200, "text/plain", "OK"); // Відправляємо відповідь про виконання
  });
  }
