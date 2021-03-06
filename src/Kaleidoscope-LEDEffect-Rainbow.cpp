#include "Kaleidoscope-LEDEffect-Rainbow.h"

namespace kaleidoscope {

void LEDRainbowEffect::update(void) {
  if (rainbow_current_ticks++ < rainbow_ticks) {
    return;
  } else {
    rainbow_current_ticks = 0;
  }

  cRGB rainbow = hsvToRgb(rainbow_hue, rainbow_saturation, rainbow_value);

  rainbow_hue += rainbow_steps;
  if (rainbow_hue >= 255) {
    rainbow_hue -= 255;
  }
  ::LEDControl.set_all_leds_to(rainbow);
}

void LEDRainbowEffect::brightness(byte brightness) {
  rainbow_value = brightness;
}


// ---------
LEDRainbowWaveEffect::LEDRainbowWaveEffect(byte brightness) {
  this->brightness(brightness);
}

LEDRainbowWaveEffect::LEDRainbowWaveEffect(byte brightness, uint16_t delay) {
  this->brightness(brightness);
  this->delay(delay);
}

LEDRainbowWaveEffect::LEDRainbowWaveEffect(byte brightness, uint16_t delay, uint8_t precision) {
  this->brightness(brightness);
  this->delay(delay);
  this->precision(precision);
}

void LEDRainbowWaveEffect::update(void) {
  if (rainbow_current_ticks++ < rainbow_wave_ticks) {
    return;
  } else {
    rainbow_current_ticks = 0;
  }

  for (uint8_t i = 0; i < LED_COUNT; i++) {
    uint16_t key_hue = rainbow_hue + 16 * (i / 4);
    if (key_hue >= 255)          {
      key_hue -= 255;
    }
    cRGB rainbow = hsvToRgb(key_hue, rainbow_saturation, rainbow_value);
    ::LEDControl.setCrgbAt(i, rainbow);
  }
  rainbow_hue += rainbow_wave_steps;
  if (rainbow_hue >= 255) {
    rainbow_hue -= 255;
  }
}

void LEDRainbowWaveEffect::brightness(byte brightness) {
  rainbow_value = brightness;
}

void LEDRainbowWaveEffect::delay(uint16_t delay_ticks) {
  rainbow_wave_ticks = delay_ticks;
}

void LEDRainbowWaveEffect::precision(uint8_t hues_to_skip) {
  rainbow_wave_steps = hues_to_skip;
}

}

kaleidoscope::LEDRainbowEffect LEDRainbowEffect;
kaleidoscope::LEDRainbowWaveEffect LEDRainbowWaveEffect;
