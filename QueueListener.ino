
void QueueListener(void) {
  if (FlagQueue == 0x00) {
    if (bytesQueue.isEmpty()) return;
    else {
      FlagQueue = 0x01;
      return;
      }
    } else {
      if (FlagQueue == 0x01) {
        Serial.println("Data transfer is started");
        for(uint8_t j = 0; j < sizeof(DataABCDEiD); DataABCDEiD[j++] = bytesQueue.pop());
        SerialPrint();
        FlagQueue = 0x02;
        return;
        } else {
           if (FlagQueue == 0x02) {
            StartTransmission();
            SynchronizingSignal();
            for(uint8_t j = 0; j < sizeof(DataABCDEiD); BitsTransfer(DataABCDEiD[j++]));
            delayMicroseconds(PERIOD);
            EndTransmission();
            timeQueue = millis();
            countQueue++;
            if (countQueue > 15) {
            FlagQueue = 0x04;
            countQueue = 0;
            return;
              } 
            FlagQueue = 0x03;
            return;
          } else {
            if (FlagQueue == 0x03) {
              if ((millis() - timeQueue) <= 10) return;
              FlagQueue = 0x02;
              return;
              } else {
                if (FlagQueue == 0x04) {
                  Serial.println("Data transfer is finished");
                  FlagQueue = 0x00;
                  return;
                } else {
                  FlagQueue = 0x00;
                  return;
                  }
                }
            }
      }
  }
}
