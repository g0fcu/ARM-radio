# ARM-radio
VLF/LF radio receiver implemented in the STM32F746-Nucleo board

This project was initiated by Alberto di Bene, I2PHD, see www.weaksignals.com
ARM-radio section for more details including the paper describing the implementation
theory. The first version written by Alberto ran on the STM32F429-Discovery board.

Simon Kennedy, G0FCU, subsequently took the original code and converted to work 
on the faster STM32F746-Nucleo board, see www.g0fcu.com for blog posts related
to this implementation. The code in this repository works on the 
STM32F746-Nucleo board.

This project implement a SDR (Software Defined Radio) using the STM32F746-Nucleo 
board, with a minimal amount of external hardware, using all the facilities 
offered both from the various devices of the chip itself and the middleware 
support (HAL, CMSIS, STemWin, etc.) provided by ST. 

This SDR is of the direct RF sampling variety, where the RF is immediately sampled by 
an ADC, then processed in numerical form with various DSP algorithms, all implemented 
taking advantage of the floating point core of the STM32F746 chip and the CMSIS 
library, and finally sent to the on-chip DAC to be transformed again in analog format,
for reproduction by a speaker after being passed through a reconstruction filter.

ARM_Radio is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

ARM_Radio is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
