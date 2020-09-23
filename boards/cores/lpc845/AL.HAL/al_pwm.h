#ifndef _AL_PWM_H_
#define _AL_PWM_H_

#include "../Arduino.h"

#define SCTIMER_CLK_FREQ CLOCK_GetFreq(kCLOCK_Fro)

class AL_PWM;

extern AL_PWM *PWMS_Instances[7];

class AL_PWM
{
  private:
    uint32_t eventNumberOutput;

  public:
    uint8_t channel;

    uint32_t frequency;
    uint8_t dutyCyclePercent;

    AL_PWM(void) : AL_PWM(0, 9, 50) {}
    AL_PWM(uint8_t channel, uint8_t pin, uint32_t frequency);

    void Write(uint8_t dutyCyclePercent);
};

#endif