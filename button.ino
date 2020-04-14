boolean brightDirection;

void buttonTick() {
  enc.tick();
  if (enc.isClick()) {
    Serial.println("Click");
    if (dawnFlag) {
      manualOff = true;
      dawnFlag = false;
      loadingFlag = true;
      FastLED.setBrightness(modes[currentMode].brightness);
      changePower();
    } else {
      if (ONflag) {
        ONflag = false;
        changePower();
      } else {
        ONflag = true;
        changePower();
      }
      sendSettings_flag = true;
    }
  }

  if (ONflag && enc.isLeft()){
    Serial.println("isLeft");
    Serial.println(modes[currentMode].brightness);
    if (modes[currentMode].brightness < 10) modes[currentMode].brightness += 1;
    else if (modes[currentMode].brightness < 250) modes[currentMode].brightness += 15;
    else modes[currentMode].brightness = 255;
    FastLED.setBrightness(modes[currentMode].brightness);
    settChanged = true;
    eepromTimer = millis();
    sendSettings_flag = true;
  }

  if (ONflag && enc.isRight()){
    Serial.println("isRight");
    Serial.println(modes[currentMode].brightness);
    if (modes[currentMode].brightness > 15) modes[currentMode].brightness -= 15;
    else if (modes[currentMode].brightness > 1) modes[currentMode].brightness -= 1;
    else modes[currentMode].brightness = 1;
    FastLED.setBrightness(modes[currentMode].brightness);
    settChanged = true;
    eepromTimer = millis();
    sendSettings_flag = true;
  }

  if (enc.isRightH()){
    if (++currentMode >= MODE_AMOUNT) currentMode = 0;
    FastLED.setBrightness(modes[currentMode].brightness);
    loadingFlag = true;
    settChanged = true;
    eepromTimer = millis();
    FastLED.clear();
    delay(1);
    sendSettings_flag = true;
  }

  if (enc.isLeftH()){
    if (--currentMode < 0) currentMode = MODE_AMOUNT - 1;
    FastLED.setBrightness(modes[currentMode].brightness);
    loadingFlag = true;
    settChanged = true;
    eepromTimer = millis();
    FastLED.clear();
    delay(1);
    sendSettings_flag = true;
  }
}
