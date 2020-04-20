/*
 * Copyright (c) 2017, CATIE, All Rights Reserved
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "mbed.h"
#include "bme280.h"

namespace {
#define PERIOD_MS 1000
}

using namespace sixtron;

static I2C i2c(I2C_SDA, I2C_SCL);
static BME280 bme(&i2c, BME280::I2CAddress::Address1);

int main()
{
    if (!bme.initialize()) {
        printf("Couldn't initialize the BME280...\n");
        return -1;
    }

    bme.set_sampling(BME280::SensorMode::NORMAL,
            BME280::SensorSampling::OVERSAMPLING_X1,
            BME280::SensorSampling::OVERSAMPLING_X1,
            BME280::SensorSampling::OVERSAMPLING_X1,
            BME280::SensorFilter::OFF,
            BME280::StandbyDuration::MS_1000);

    while (true) {
        printf("\n\rAlive!\n");
        printf("Temperature: %.3f °C\n", bme.temperature());
        printf("Pressure:    %.3f hPa\n", (bme.pressure() / 100.0f));
        printf("Humidity:    %.3f %%\n", bme.humidity());
        ThisThread::sleep_for(PERIOD_MS);
    }

}
