/*
   https://github.com/gashtaan/sinowealth-fw-disabler

   Copyright (C) 2023, Michal Kovacik

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License version 3, as
   published by the Free Software Foundation.
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

const int USBP = 2;
const int USBM = 3;
const int USBVDD = 4;

void setup()
{
	pinMode(LED_BUILTIN, OUTPUT);

	pinMode(USBVDD, OUTPUT);
	pinMode(USBP, INPUT);
	pinMode(USBM, INPUT_PULLUP);

	digitalWrite(USBVDD, 1);

	delay(5);

	for (uint8_t n = 0; n < 20; ++n)
	{
		while (digitalRead(USBM));

		pinMode(USBP, OUTPUT);
		digitalWrite(USBP, 0);

		while (!digitalRead(USBM));

		pinMode(USBP, INPUT);
	}
}

void loop()
{
	digitalWrite(LED_BUILTIN, digitalRead(USBM));
}
