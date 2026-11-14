/**
 * Program      Test_ToolkitSquareWaves
 *
 * Author       2026-11-03 Charles Geiser (ww.dodeka.ch)
 *
 * Purpose      Test the functions
 *                - heartbeat()
 *                - buzzer()
 *                - pulseGen()
 *                - threePhaseGen()
 *
 *                      LED Bar
 * Wiring       GND     o------,
 *              GPIO_19 o-->|--|
 *              GPIO_18 o-->|--|
 *              GPIO_17 o-->|--|             Buzzer
 *              GPIO    o-->|--|               ____||
 *              GPIO    o-->|--|     GND    --|    ||
 *              GPIO_16 o-->|--|              |-¦¦-||
 *              GPIO    o-->|--|     GPIO_2 --|____||
 *              GPIO_2  o-->|--'                   ||
 *
 * Remarks      The program uses the `ToolkitSquareWaves` library to
 *              generate square waves on GPIO pins of an ESP32. It
 *              demonstrates the use of heartbeat signals, buzzer sounds,
 *              and pulse generation with phase shifts. The wiring
 *              diagram shows how to connect a LED Bar and a piezzo buzzer
 *              to the GPIO pins to provide visual and audible feedback.
 *
 *
 */
#include "ToolkitSquareWaves.h"

// "Heartbeat", defaults used: 1 beat/sec with 5% duty
SquareWave::PulseGen heartbeat(GPIO_NUM_16);

// 3 beeps with 25% duty and a signal of 2kHz within 1 sec followed bei a pause of 2 sec
SquareWave::Buzzer buzzer(GPIO_NUM_2, 3, 25.0F, 1'000'000, 2'000'000, 2000);

// Spike pulses on pin 4 with a frequency of 10 kHz and a pulse width of 5 µs
SquareWave::PulseGen spikes(GPIO_NUM_4, 100, 5);

// 1 pulse in 5 sec with 5% duty
SquareWave::PulseGen gen1(GPIO_NUM_17, 1, 5, 5.0F);

// 1 pulses in 5 sec with 5% duty an a phase shift of 120°
SquareWave::PulseGen gen2(GPIO_NUM_18, 1, 5, 5.0F, 120);

// 1 pulses in 5 sec with 5% duty an a phase shift of 240°
SquareWave::PulseGen gen3(GPIO_NUM_19, 1, 5, 5.0F, 240);

// Three-phase pulse trains on pins 17, 18, 19 with a
// period of 2.5 sec, a duty of 5% and a phase shift of 108°
SquareWave::ThreephaseGen threephases(GPIO_NUM_17, GPIO_NUM_18, GPIO_NUM_19, 2'500'000, 5.0F, 108);

void setup()
{
  Serial.begin(MONITOR_SPEED); // use the monitor_speed defined in platformio.ini
  vTaskDelay(pdMS_TO_TICKS(1000));

  heartbeat.on();
  buzzer.on();
  spikes.on();

  if (false)
  {
    // make up a 3-phase generator from 3 individual generators
    gen1.on();
    gen2.on();
    gen3.on();
  }
  else
  {
    // use the compact version of the 3-phase generator
    threephases.on();
  }
}

void loop()
{
  heartbeat.loop();
  spikes.loop();
  buzzer.loop();
  gen1.loop();
  gen2.loop();
  gen3.loop();
  threephases.loop();
}
