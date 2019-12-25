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

#include <Arduino.h>


#ifdef ARDUINO_ARCH_AVR
// Make it compatible with the standart
#include <string.h>
namespace std { using ::memset; } 
namespace std { using ::memcpy; }
#else
#include <cstring>
#endif

namespace nd {

const uint8_t cI2CAddress = 0xC0;

IS31FL3746::IS31FL3746()
{
  _chipAddress = cI2CAddress;
}

void IS31FL3746::writeToChip(uint8_t address, uint8_t data)
{
  Wire.beginTransmission(_chipAddress/2); 
  Wire.write(address); 
  Wire.write(data); 
  Wire.endTransmission(); 
}

void IS31FL3746::clearAll()
{
  writeToChip(0xfe, 0xc5); // unlock
  writeToChip(0xfd, 0x00); // page 0
  for (uint8_t i = 0; i < 0x49; i++)
  {
    writeToChip(i, 0x00);
  }
}

void IS31FL3746::setColor(uint8_t index, uint8_t *pColor)
{
  writeToChip(0xfe, 0xc5); // unlock
  writeToChip(0xfd, 0x00); // page 0
  if (index != 18) {
    writeToChip(3*index+1, pColor[0]); // R
    writeToChip(3*index+2, pColor[1]); // G
    writeToChip(3*index+3, pColor[2]); // B
  } else {
    writeToChip(3*(index+1)+1, pColor[0]); // R
    writeToChip(3*(index+1)+2, pColor[1]); // G
    writeToChip(3*(index+1)+3, pColor[2]); // B
  }
}

void IS31FL3746::testSetColor()
{
  int8_t i;
  uint8_t j;
  uint8_t colors[7][3] = {
    {255, 0, 0},
    {0, 255, 0},
    {0, 0, 255},
    {128, 128, 0},
    {0, 128, 128},
    {128, 0, 128},
    {85, 85, 85}
  };

  for (j = 0; j < 7; j++)
  {
    for (i = 0; i < cLedNum; i++)
    {
      setColor(i, &colors[j][0]);
      delay(150);
    }
  }
  for (j = 0; j < 7; j++)
  {
    for (i = (cLedNum-1); i >= 0; i--)
    {
      setColor(i, &colors[j][0]);
      delay(150);
    }
  }
}

void IS31FL3746::rotateLine(uint8_t *pColor, bool isCW)
{
  int8_t i;
  uint8_t j;
  uint8_t lines[3][5] = {
    {0, 6, 18, 9, 3},
    {1, 7, 18, 10, 4},
    {2, 8, 18, 11, 5},
  };
  if (isCW) {
    for (i = 0; i < 6; i++)
    {
      for (j = 0; j < 5; j++)
      {
        setColor(lines[i%3][j], pColor);
      }
      delay(300);
    }
  } else {
    for (i = 5; i >=0; i--)
    {
      for (j = 0; j < 5; j++)
      {
        setColor(lines[i%3][j], pColor);
      }
      delay(300);
    }
  }
}

void IS31FL3746::rotateShortLine(uint8_t *pColor, bool isCW)
{
  int8_t i;
  uint8_t j;
  uint8_t lines[6][2] = {
    {0, 6},
    {1, 7},
    {2, 8},
    {3, 9},
    {4, 10}, 
    {5, 11},
  };
  if (isCW) {
    for (i = 0; i < 6; i++)
    {
      for (j = 0; j < 2; j++)
      {
        setColor(lines[i][j], pColor);
      }
      delay(300);
    }
  } else {
    for (i = 5; i >= 0; i--)
    {
      for (j = 0; j < 2; j++)
      {
        setColor(lines[i][j], pColor);
      }
      delay(300);
    }
  }
}

void IS31FL3746::testRotateLine()
{
  int8_t i, j;
  uint8_t colors[7][3] = {
    {255, 0, 0},
    {0, 255, 0},
    {0, 0, 255},
    {128, 128, 0},
    {0, 128, 128},
    {128, 0, 128},
    {85, 85, 85}
  };
  for (i = 0; i < 7; i++) {
    rotateLine(&colors[i][0], true);  
  }
  for (i = 0; i < 7; i++) {
    rotateLine(&colors[i][0], false);  
  }
}

void IS31FL3746::testRotateShortLine()
{
  int8_t i;
  uint8_t colors[7][3] = {
    {255, 0, 0},
    {0, 255, 0},
    {0, 0, 255},
    {128, 128, 0},
    {0, 128, 128},
    {128, 0, 128},
    {85, 85, 85}
  };
  for (i = 0; i < 7; i++) {
    rotateShortLine(&colors[i][0], true);
  }
  for (i = 0; i < 7; i++) {
    rotateShortLine(&colors[i][0], false);
  }
}


void IS31FL3746::oneColorRing(uint8_t *pColor, bool isInward, uint16_t delayms)
{
  int8_t i;
  if (isInward) {
    for (i = 0; i < cLedNum; i++)
    {
      setColor(i, pColor);
      if (i == 5 || i == 11 || i==17 || i == 18) {
        delay(delayms);
      }
    }
  } else {
    for (i = (cLedNum-1); i >= 0; i--)
    {
      setColor(i, pColor);
      if (i == 18 || i == 12 || i==6 || i == 0) {
        delay(delayms);
      }
    }
  }
}

void IS31FL3746::testRing()
{
  int8_t i, j;
  uint8_t colors[7][3] = {
    {255, 0, 0},
    {0, 255, 0},
    {0, 0, 255},
    {128, 128, 0},
    {0, 128, 128},
    {128, 0, 128},
    {85, 85, 85}
  };

  for (j = 0; j < 7; j++)
  {
    oneColorRing(&colors[j][0], false, 500);
  }
  for (j = 0; j < 7; j++)
  {
    oneColorRing(&colors[j][0], true, 500);
  }
}


}

