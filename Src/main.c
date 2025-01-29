#include "Driver/I2C.h"
#include "Driver/SYSTICK.h"
#include "Library/BH1750.h"

int main()
{
	uint16_t regVal = 0;
	I2C1_Init();
	BH1750_Init();

	while(1)
	{
		regVal = BH1750_ReadLightLevel();
		delay_ms(1000);
	}
}
