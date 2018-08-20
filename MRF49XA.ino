

void MRF49XA_init() {
 pinMode(DATA, OUTPUT);
 digitalWrite(DATA, HIGH);
 digitalWrite(SS, HIGH);
 SPI.begin();
 SPI.setClockDivider(SPI_CLOCK_DIV128);  
 SPI.setBitOrder(MSBFIRST);
 SPI.setDataMode (SPI_MODE0);
 Serial.println("The transmitter is running");
 Serial.println("Started test transmission...");
 TestTransmission();
 Serial.println("Finished test transmission");
 Serial.flush();
  }

void SerialPrint() {
    Serial.println("Bytes transfer:");
    Serial.print("A = ");
    Serial.println(DataABCDEiD[0], HEX);
    Serial.print("B = ");
    Serial.println(DataABCDEiD[1], HEX);
    Serial.print("C = ");
    Serial.println(DataABCDEiD[2], HEX);
    Serial.print("D = ");
    Serial.println(DataABCDEiD[3], HEX);
    Serial.print("E = ");
    Serial.println(DataABCDEiD[4], HEX);
    Serial.print("ID = ");
    Serial.println(DataABCDEiD[5], HEX);
  }

byte setByteQueue(byte MSB, byte LSB, byte SetDefault) {
   if (isByte(MSB) && isByte(LSB)) return getByte(MSB, LSB);
   return SetDefault;
  }

byte getByte(byte MSB, byte LSB) {
  MSB = ByteToByte(MSB) << 4;
  return (ByteToByte(LSB) | MSB);
  }

boolean isByte(byte tmp) {
  return (((tmp >= 0x30) && (tmp <= 0x39)) or ((tmp >= 0x41) && (tmp <= 0x46)) or ((tmp >= 0x61) && (tmp <= 0x66)));
  }
  
byte ByteToByte(byte tmp) {
  if ((tmp >= 0x30) && (tmp <= 0x39)) return (tmp & 0x0F);
  if ((tmp >= 0x61) && (tmp <= 0x66)) tmp = tmp & 0xDF;
  tmp = tmp + 0x09;
  return (tmp & 0x0F);
  }
  
void BitsTransfer(byte bits) {
  BitsTransferRRF(bits);
  BitsTransferRLF(bits);
  }

void BitsTransferRRF(byte bits) {
  for(uint8_t i = 0; i < 8; i++) {
  if(bits & 0x80) {
    TransferDataR();
    }
    else {
    TransferDataL();
    }
  bits = bits << 1;
  }
  }
void BitsTransferRLF(byte bits) {
  for(uint8_t i = 0; i < 8; i++) {
  if(bits & 0x01) {
    TransferDataL();
    }
    else {
    TransferDataR();
    }
  bits = bits >> 1;
  }
  }

void TransferDataR() {
    digitalWrite(DATA, HIGH);
    delayMicroseconds(PERIOD);
    digitalWrite(DATA, LOW);
    delayMicroseconds(PERIOD);
    delayMicroseconds(PERIOD);
  }
  
void TransferDataL() {
    digitalWrite(DATA, HIGH);
    delayMicroseconds(PERIOD);
    delayMicroseconds(PERIOD);
    digitalWrite(DATA, LOW);
    delayMicroseconds(PERIOD);
  }
  
  

void SynchronizingSignal() {
  for(uint8_t i = 0; i < 12; i++) {
  digitalWrite(DATA, HIGH);
  delayMicroseconds(PERIOD);
  digitalWrite(DATA, LOW);
  delayMicroseconds(PERIOD);
  }
  delay(1);
  }

void StartTransmission() {
  digitalWrite(SS, LOW);
  SPI.transfer16(CREG);
  SPI.transfer16(FSREG);
  SPI.transfer16(TCREG);
  SPI.transfer16(AFCREG);
  SPI.transfer16(PMREG0);
  digitalWrite(SS, HIGH);
  }

void EndTransmission() {
  digitalWrite(SS, LOW);
  SPI.transfer16(PMREG1);
  digitalWrite(SS, HIGH);
  }

void TestTransmission() {
  delay(1000);
  for(uint8_t i = 0; i < 2; i++){
  digitalWrite(SS, LOW);
  SPI.transfer16(PMREG1);
  SPI.transfer16(CREG);
  SPI.transfer16(FSREG);
  SPI.transfer16(TCREG);
  SPI.transfer16(AFCREG);
  SPI.transfer16(PMREG0);
  digitalWrite(SS, HIGH);
  delay(1000);
  EndTransmission();
  delay(1000);
  }
  }
