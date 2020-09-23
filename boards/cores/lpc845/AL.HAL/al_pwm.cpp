#include "al_pwm.h"

AL_PWM *PWMS_Instances[7] = { NULL, NULL, NULL, NULL, NULL, NULL, NULL };

AL_PWM::AL_PWM(uint8_t channel, uint8_t pin, uint32_t frequency)
{
  if (channel > FSL_FEATURE_SOC_PWMS_COUNT) return;
  // Valutate to use a static constructor to return exiting instance
  this->channel = channel;
  this->frequency = frequency;

  PWMS_Instances[channel] = this;

  // Set pin swd
  IOCON_PinMuxSet(IOCON, IOCON_INDEX_BP_ARRAY[pin], 0);
  SWM_SetMovablePinSelect(SWM0, SWM_PWMS_ARRAY[channel], SWM_PORTPIN_BP_ARRAY[pin]);

  sctimer_config_t sctimerInfo;
  sctimer_pwm_signal_param_t pwmParam;

  // TODO: Check if SCT0 timer is already initialized
  {
    SCTIMER_GetDefaultConfig(&sctimerInfo);

    /* Initialize SCTimer module */
    SCTIMER_Init(SCT0, &sctimerInfo);
  }

  /* Configure PWM params with frequency 24kHZ from output */
  pwmParam.output           = SCTIMER_OUT_ARRAY[channel];
  pwmParam.level            = kSCTIMER_HighTrue;
  pwmParam.dutyCyclePercent = 5;
  if (SCTIMER_SetupPwm(SCT0, &pwmParam, kSCTIMER_CenterAlignedPwm, frequency, SCTIMER_CLK_FREQ, &(this->eventNumberOutput)) == kStatus_Fail)
    return;
  
  /* Start the 32-bit unify timer */
  SCTIMER_StartTimer(SCT0, kSCTIMER_Counter_U);
}

void AL_PWM::Write(uint8_t dutyCyclePercent)
{
  /* Update PWM duty cycle */
  SCTIMER_UpdatePwmDutycycle(SCT0, SCTIMER_OUT_ARRAY[this->channel], dutyCyclePercent, this->eventNumberOutput);
}