#include <Arduino.h>
#include <VL53L0XManager.h>

VL53L0XManager::VL53L0XManager(
    int numberSensors,
    struct distanceSensor *distanceSensors
)
{
    this->numberSensors = numberSensors;
    this->distanceSensors = distanceSensors;

}

void VL53L0XManager::setAddresses()
{
    for (int i = 0; i < this->numberSensors; i++)
    {
        pinMode(this->distanceSensors[i].shutdownPin, OUTPUT);
        digitalWrite(this->distanceSensors[i].shutdownPin, LOW);
    }

    delayMicroseconds(10);

    for (int i = 0; i < this->numberSensors; i++)
    {
        digitalWrite(this->distanceSensors[i].shutdownPin, HIGH);
    }

    delayMicroseconds(10);

    for (int i = 0; i < this->numberSensors; i++)
    {
        digitalWrite(this->distanceSensors[i].shutdownPin, HIGH);
        for (int j = i+1; j < this->numberSensors; j++)
        {
            digitalWrite(this->distanceSensors[j].shutdownPin, LOW);
        }
        while (!this->distanceSensors[i].sensor.begin(this->distanceSensors[i].address))
        {
            Serial.print("Failed to boot ");
            Serial.print(i);
            Serial.print(" VL53L0X Sensor");
            Serial.println("");
        }
        delayMicroseconds(10);
    }
}

uint16_t VL53L0XManager::getSensorDistance(int sensorNumber){
    this->distanceSensors[sensorNumber].sensor.rangingTest(
        &this->distanceSensors[sensorNumber].measure, false
    );
    if (this->distanceSensors[sensorNumber].measure.RangeStatus!=4)
    {
        return this->distanceSensors[sensorNumber].measure.RangeMilliMeter;
    }
    return 0;
}
