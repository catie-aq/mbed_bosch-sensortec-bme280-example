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
#define PERIOD_MS 2000
}

static I2C i2c(I2C_SDA, I2C_SCL);
static BME280 bme(&i2c);
static double temp;
static double pressure;
static double humidity;
static BME280::SensorMode mode;

void read_print_data(){
    bme.read_temperature(&temp);
    bme.read_humidity(&humidity);
    bme.read_pressure(&pressure);

    printf("Temperature: %.3f °C\n", temp);
    printf("Pressure:    %.3f Pa\n", pressure);
    printf("Himidity:   %.3f %%\n", humidity);
}

int main() {

    if (!bme.initialize()){
        printf("Couldn't initialize the BME280...\n=======================\n");
        return -1;
    }
    
    bme.get_power_mode(&mode);
    while (true){

        printf("\nPower mode: "); 
        switch (static_cast<int>(mode)){
        case 0:
            printf("Forced\n");
            break;
        case 1:
            printf("Sleep\n");
            break;
        default:
            printf("Normal\n");
            break;
        }
        read_print_data();
        wait_ms(PERIOD_MS);
    }
}
