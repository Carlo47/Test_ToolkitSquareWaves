/**
 * Class      Buzzer implementation
 *
 * Author     2026-11-09 Charles Geiser (www.dodeka.ch)
 *
 * Purpose    see Buzzer.h
 */

#include "Buzzer.h"

namespace SquareWave
{
  void Buzzer::loop()
  {
    if (_isEnabled)
    {
      uint32_t t = micros();
      _chn1      = t % _usGatePeriod < _usGateOpen ? HIGH : LOW;
      _chn2      = (t - _usBeepPhase) % _usBeepPeriod < _usBeepPulseWidth ? HIGH : LOW;
      _signal    = t % _usSignalPeriod < _usSignalPulseWidth ? HIGH : LOW;

      if (_isInverted)
        gpio_set_level(_pin, (_chn1 & _chn2 & _signal) ? LOW : HIGH);
      else
        gpio_set_level(_pin, (_chn1 & _chn2 & _signal) ? HIGH : LOW);
    }
  }

  void Buzzer::off()
  {
    _isEnabled = false;
    _isInverted ? gpio_set_level(_pin, HIGH) : gpio_set_level(_pin, LOW);
  }

  void Buzzer::on()
  {
    _isEnabled = true;
    _isInverted ? gpio_set_level(_pin, HIGH) : gpio_set_level(_pin, LOW);
  }

  void Buzzer::setInvertedOutput(bool inverted)
  {
    _isInverted = inverted;
  }
} // namespace SquareWave