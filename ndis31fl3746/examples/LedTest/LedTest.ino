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
#include "NDIS31FL3746.h"

/// @example LedTest.ino
/// This example tests all connected LEDs.

using namespace nd;
IS31FL3746 ledDriver;


void setup() {
  // Initialize the Wire library.
  Wire.begin();
  // Set the I2C clock to 400KHz.
  Wire.setClock(400000);   

  ledDriver.clearAll();
}

void loop() {
  ledDriver.testSetColor();
  ledDriver.clearAll();
  ledDriver.testRing();
  ledDriver.clearAll();
  ledDriver.testRotateLine();
  ledDriver.clearAll();
  ledDriver.testRotateShortLine();
}

