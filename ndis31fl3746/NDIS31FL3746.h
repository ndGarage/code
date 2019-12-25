//
// ndGarage's IS31FL3746 Library
// ---------------------------------------------------------------------------
// (c)2019 by ndGarage. See LICENSE for details.
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>
//
#pragma once

#include <Wire.h>

#ifdef ARDUINO_ARCH_AVR
#include <inttypes.h>
#else
#include <cinttypes>
#endif


namespace nd {


/// @brief A low-level IS31Fl3746 chip access class.
///
/// IS31FL3746 is capable of driving 24 RGB Leds. 
/// However ColourSnow has used 19 RGB Leds.
/// 
/// All the functions has no limitations to access the chip. 
/// But you have to pay attention to the details of ColourSnow.
///
///

class IS31FL3746
{
public:

  /// @brief Total number of RGB Leds of ColourSnow.
  ///
  const uint8_t cLedNum = 19;

public:
  IS31FL3746();

public:
  void writeToChip(uint8_t address, uint8_t data);

public:
  void clearAll(void);
  void setColor(uint8_t index, uint8_t *pColor);
  void oneColorRing(uint8_t *pColor, bool isInward, uint16_t delayms);
  void rotateLine(uint8_t *pColor, bool isCW);
  void rotateShortLine(uint8_t *pColor, bool isCW);
  void testRotateLine();
  void testRotateShortLine();
  void testSetColor(void);
  void testRing(void);

private:
  uint8_t _chipAddress;
};

}
  
