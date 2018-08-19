
void BUTTONS_init(void) {
  HTTP.on("/ButtonsControl", HTTP_GET, []() {
  if(bytesQueue.count() < 600) {
  uint8_t ButtonSet = HTTP.arg("set").toInt() - 1;
  if ((ButtonSet >= 0) && (ButtonSet <= 39)) { 
    HTTP.send(200, "text/plain", "OK"); // Відправляємо відповідь про виконання
    switch(ButtonSet/8){
      case 4: bytesQueue.push(0x00);
      case 3: bytesQueue.push(0x00);
      case 2: bytesQueue.push(0x00);
      case 1: bytesQueue.push(0x00);
      }
     bytesQueue.push(0x01 << (ButtonSet - (ButtonSet/8*8))); 
     switch(ButtonSet/8){
      case 0: bytesQueue.push(0x00);
      case 1: bytesQueue.push(0x00);
      case 2: bytesQueue.push(0x00);
      case 3: bytesQueue.push(0x00);
      }
     bytesQueue.push(setByteQueue(jsonRead(configSetup, "ButtonsControlMSB").charAt(0), jsonRead(configSetup, "ButtonsControlLSB").charAt(0), 0xFF));
    } else {
       HTTP.send(400, "text/plain", "Out of range 1-40"); // Відправляємо відповідь про виконання
      }
    } else {
       HTTP.send(429, "text/plain", "Too Many Requests"); // Відправляємо відповідь про виконання
    }
  });
  HTTP.on("/ButtonsControlMSB", HTTP_GET, []() {
  jsonWrite(configSetup, "ButtonsControlMSB", HTTP.arg("set"));
  saveConfig();                 // Функція збереження даних у Flash
  HTTP.send(200, "text/plain", "OK"); // Відправляємо відповідь про виконання
  });
  HTTP.on("/ButtonsControlLSB", HTTP_GET, []() {
  jsonWrite(configSetup, "ButtonsControlLSB", HTTP.arg("set"));
  saveConfig();                 // Функція збереження даних у Flash
  HTTP.send(200, "text/plain", "OK"); // Відправляємо відповідь про виконання
  });
  
  HTTP.on("/bytes", HTTP_GET, []() {
  if(bytesQueue.count() < 600) {
  bytesQueue.push(setByteQueue(HTTP.arg("AMSB").charAt(0), HTTP.arg("ALSB").charAt(0), 0x00));
  bytesQueue.push(setByteQueue(HTTP.arg("BMSB").charAt(0), HTTP.arg("BLSB").charAt(0), 0x00));
  bytesQueue.push(setByteQueue(HTTP.arg("CMSB").charAt(0), HTTP.arg("CLSB").charAt(0), 0x00));
  bytesQueue.push(setByteQueue(HTTP.arg("DMSB").charAt(0), HTTP.arg("DLSB").charAt(0), 0x00));
  bytesQueue.push(setByteQueue(HTTP.arg("EMSB").charAt(0), HTTP.arg("ELSB").charAt(0), 0x00));
  bytesQueue.push(setByteQueue(HTTP.arg("IDMSB").charAt(0), HTTP.arg("IDLSB").charAt(0), 0xFF));
  HTTP.send(200, "text/plain", "OK"); // Відправляємо відповідь про виконання
  } else {
  HTTP.send(429, "text/plain", "Too Many Requests"); // Відправляємо відповідь про виконання
    }
  });
  }
