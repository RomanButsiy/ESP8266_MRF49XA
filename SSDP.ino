void SSDP_init(void) {
  // SSDP дескриптор
  HTTP.on("/description.xml", HTTP_GET, []() {
    SSDP.schema(HTTP.client());
  });
   // --------------------Отримуємо SSDP зі сторінки
  HTTP.on("/ssdp", HTTP_GET, []() {
    String ssdp = HTTP.arg("ssdp");
  configJson=jsonWrite(configJson, "SSDP", ssdp);
  configJson=jsonWrite(configSetup, "SSDP", ssdp);
  SSDP.setName(jsonRead(configSetup, "SSDP"));
  saveConfig();                 // Функція збереження даних у Flash
  HTTP.send(200, "text/plain", "OK"); // Відправляємо відповідь про виконання
  });
  // Якщо версія 2.0.0 розкоментуйте наступний рядок
  SSDP.setDeviceType("upnp:rootdevice");
  SSDP.setSchemaURL("description.xml");
  SSDP.setHTTPPort(80);
  SSDP.setName(jsonRead(configSetup, "SSDP"));
  SSDP.setSerialNumber("000000000000");
  SSDP.setURL("/");
  SSDP.setModelName("SSDP-TransmitterMRF49XA");
  SSDP.setModelNumber("000000000001");
  SSDP.setModelURL("https://goo.gl/x8FL2o");
  SSDP.setManufacturer("Roman Butsiy");
  SSDP.setManufacturerURL("https://goo.gl/x8FL2o");
  SSDP.begin();
}
