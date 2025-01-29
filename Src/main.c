#include "Library/BMP280.h"
#include "Driver/I2C.h"
#include "Driver/SYSTICK.h"

float temperature = 0.0f;
float pressure = 0.0f;

int main(void)
{
    I2C1_Init();

    if (BMP280_Init() != 0)
    {
        while (1);
    }

    while (1)
    {
        if (BMP280_ReadTemperature(&temperature) != 0)
        {
            temperature = -999.99f;
        }

        if (BMP280_ReadPressure(&pressure) != 0)
        {
            pressure = -99999.99f;
        }
        delay_ms(1000);
    }

    return 0;
}
