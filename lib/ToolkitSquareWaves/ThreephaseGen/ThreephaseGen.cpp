/**
 * Class      ThreephaseGen implementation
 *
 * Author     2026-11-09 Charles Geiser (www.dodeka.ch)
 *
 * Purpose    see ThreephaseGen.h
 */

#include "ThreephaseGen.h"

namespace SquareWave
{
  void ThreephaseGen::loop()
  {
    if (_isEnabled)
    {
      uint32_t t = micros();

      if (_isInverted)
      {
        gpio_set_level(_pin1, (t - _usPhase1) % _usPeriod < _usPulseWidth ? LOW : HIGH);
        gpio_set_level(_pin2, (t - _usPhase2) % _usPeriod < _usPulseWidth ? LOW : HIGH);
        gpio_set_level(_pin3, (t - _usPhase3) % _usPeriod < _usPulseWidth ? LOW : HIGH);
      }
      else
      {
        gpio_set_level(_pin1, (t - _usPhase1) % _usPeriod < _usPulseWidth ? HIGH : LOW);
        gpio_set_level(_pin2, (t - _usPhase2) % _usPeriod < _usPulseWidth ? HIGH : LOW);
        gpio_set_level(_pin3, (t - _usPhase3) % _usPeriod < _usPulseWidth ? HIGH : LOW);
      }
    }
  }

  void ThreephaseGen::off()
  {
    _isEnabled = false;
    if (_isInverted)
    {
      gpio_set_level(_pin1, HIGH);
      gpio_set_level(_pin2, HIGH);
      gpio_set_level(_pin3, HIGH);
    }
    else
    {
      gpio_set_level(_pin1, LOW);
      gpio_set_level(_pin2, LOW);
      gpio_set_level(_pin3, LOW);
    }
  }

  void ThreephaseGen::on()
  {
    _isEnabled = true;
    if (_isInverted)
    {
      gpio_set_level((gpio_num_t) _pin1, HIGH);
      gpio_set_level((gpio_num_t) _pin2, HIGH);
      gpio_set_level((gpio_num_t) _pin3, HIGH);
    }
    else
    {
      gpio_set_level((gpio_num_t) _pin1, LOW);
      gpio_set_level((gpio_num_t) _pin2, LOW);
      gpio_set_level((gpio_num_t) _pin3, LOW);
    }
  }

  void ThreephaseGen::setInvertedOutput(bool inverted)
  {
    _isInverted = inverted;
  }
} // namespace SquareWave