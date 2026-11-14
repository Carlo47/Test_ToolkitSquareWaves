/**
 * Class      PulseGen implementation
 *
 * Author     2026-11-09 Charles Geiser (www.dodeka.ch)
 *
 * Purpose    see PulseGen.h
 */

#include "PulseGen.h"

namespace SquareWave
{
  void PulseGen::loop()
  {
    if (_isEnabled)
    {
      if (_isInverted)
        gpio_set_level(_pin, (micros() - _usPhase) % _usPeriod < _usPulseWidth ? LOW : HIGH);
      else
        gpio_set_level(_pin, (micros() - _usPhase) % _usPeriod < _usPulseWidth ? HIGH : LOW);
    }
  }

  void PulseGen::off()
  {
    _isEnabled = false;
    _isInverted ? gpio_set_level(_pin, HIGH) : gpio_set_level(_pin, LOW);
  }

  void PulseGen::on()
  {
    _isEnabled = true;
    _isInverted ? gpio_set_level(_pin, HIGH) : gpio_set_level(_pin, LOW);
  }

  void PulseGen::setPhase(uint32_t usPhase)
  {
    _usPhase = usPhase;
  }

  void PulseGen::setPeriod(uint32_t usPeriod)
  {
    _usPeriod = usPeriod;
  }

  void PulseGen::setPulseWidth(uint32_t usPulseWidth)
  {
    _usPulseWidth = usPulseWidth;
  }

  void PulseGen::setInvertedOutput(bool inverted)
  {
    _isInverted = inverted;
  }
} // namespace SquareWave