#include <Arduino.h>
#include "StepMotor28BYJ48.h"
#include "StepMotorA4988.h"
#include <VL53L0XManager.h>
#include "Adafruit_VL53L0X.h"
#include "Fan.h"

// Configurações dos sensores

// Sensores de distância

// struct distanceSensor
// {
//   int shutdownPin;
//   int address;
//   Adafruit_VL53L0X sensor;
//   VL53L0X_RangingMeasurementData_t measure;
//   int measurements[]
// };

distanceSensor distanceSensors[] = {
  {
    8,
    0x30,
    Adafruit_VL53L0X(),
    VL53L0X_RangingMeasurementData_t(),
  },
  {
    9,
    0x31,
    Adafruit_VL53L0X(),
    VL53L0X_RangingMeasurementData_t(),
  },
  {
    11,
    0x32,
    Adafruit_VL53L0X(),
    VL53L0X_RangingMeasurementData_t(),
  },
  {
    10,
    0x33,
    Adafruit_VL53L0X(),
    VL53L0X_RangingMeasurementData_t(),
  },
};

VL53L0XManager distanceSensorsManager = VL53L0XManager(4, distanceSensors);


// Configurações de todos os motores
const int STEPS_PER_REVOLUTION = 2048;
#define STEP_LENGTH 10
#define SPEED 15

#define IN1_CILINDRICA 34
#define IN2_CILINDRICA 36
#define IN3_CILINDRICA 38
#define IN4_CILINDRICA 40

#define UP_BUTTON_CILINDRICA 42
#define DOWN_BUTTON_CILINDRICA 44

StepMotor28BYJ48 cilindrica_motor = StepMotor28BYJ48(STEPS_PER_REVOLUTION,
IN1_CILINDRICA, IN2_CILINDRICA, IN3_CILINDRICA, IN4_CILINDRICA,
  SPEED, STEP_LENGTH, UP_BUTTON_CILINDRICA, DOWN_BUTTON_CILINDRICA);


#define IN1_PRISMA 27
#define IN2_PRISMA 29
#define IN3_PRISMA 31
#define IN4_PRISMA 33

#define UP_BUTTON_PRISMA 49
#define DOWN_BUTTON_PRISMA 51

StepMotor28BYJ48 prisma_motor = StepMotor28BYJ48(STEPS_PER_REVOLUTION,
IN1_PRISMA, IN2_PRISMA, IN3_PRISMA, IN4_PRISMA,
  SPEED, STEP_LENGTH, UP_BUTTON_PRISMA, DOWN_BUTTON_PRISMA);

#define IN1_COLIMADORA 26
#define IN2_COLIMADORA 28
#define IN3_COLIMADORA 30
#define IN4_COLIMADORA 32

#define UP_BUTTON_COLIMADORA 48
#define DOWN_BUTTON_COLIMADORA 50

StepMotor28BYJ48 colimadora_motor = StepMotor28BYJ48(STEPS_PER_REVOLUTION,
IN1_COLIMADORA, IN2_COLIMADORA, IN3_COLIMADORA, IN4_COLIMADORA,
  SPEED, STEP_LENGTH, UP_BUTTON_COLIMADORA, DOWN_BUTTON_COLIMADORA);


#define IN1_CAMERA 35
#define IN2_CAMERA 37
#define IN3_CAMERA 39
#define IN4_CAMERA 41

#define UP_BUTTON_CAMERA 43
#define DOWN_BUTTON_CAMERA 45

StepMotor28BYJ48 camera_motor = StepMotor28BYJ48(STEPS_PER_REVOLUTION,
IN1_CAMERA, IN2_CAMERA, IN3_CAMERA, IN4_CAMERA,
  SPEED, STEP_LENGTH, UP_BUTTON_CAMERA, DOWN_BUTTON_CAMERA);


#define MOTOR_STEPS_CAMERA_FEEDFORWARD 200
#define FORWARD_BUTTON_CAMERA 46
#define BACKWARD_BUTTON_CAMERA 47
#define DIR 24
#define STEP 25
#define ENB 22

StepMotorA4988 feedfoward_camera_motor = StepMotorA4988(
  DIR, STEP, ENB,
  FORWARD_BUTTON_CAMERA, BACKWARD_BUTTON_CAMERA
);

// Relay
/*
  Botão que liga é o 2
  Porta de ligar é o 3
  e o sensor dht é o 12
*/



#define fanRelayPin 4
#define switchFanButtonPin 2
#define DHTPin 12
#define biasTemperature 27
Fan cooler = Fan(fanRelayPin, switchFanButtonPin, DHTPin, biasTemperature);

void switchFanStatus(){
  cooler.switchStatus();
}

ISR(TIMER1_COMPA_vect){
  cooler.switchStatusByTemperature();
}

void setup() {
  Serial.begin(9600);
  Serial.println("Iniciando aplicacao");
  // distanceSensorsManager.setAddresses();
  cooler.configure();
  attachInterrupt(
    digitalPinToInterrupt(switchFanButtonPin),
    switchFanStatus,
    FALLING
  );
}

unsigned long time;

void loop() {
  // time = millis();
  colimadora_motor.listenButtons();
  prisma_motor.listenButtons();
  cilindrica_motor.listenButtons();
  camera_motor.listenButtons();
  // feedfoward_camera_motor.listenButtons();
  // Serial.println(millis()-time);
  // delay(1000);

  // for (int i = 0; i < 10; i++)
  // {
  //   feedfoward_camera_motor.rotateAntiClockWise();
  // }

  // delay(1000);
  // feedfoward_camera_motor.wakeUp();
  // feedfoward_camera_motor.rotateClockWise();
  // feedfoward_camera_motor.putToSleep();


  // delay(1000);

  // Serial.print("Distancia colimadora: ");
  // Serial.println(distanceSensorsManager.getSensorDistance(0));
  // // delay(1000);
  // Serial.print("Distancia Cilindrica: ");
  // Serial.println(distanceSensorsManager.getSensorDistance(1));
  // // delay(1000);
  // Serial.print("Distancia Camera: ");
  // Serial.println(distanceSensorsManager.getSensorDistance(2));
  // // delay(1000);
  // Serial.print("Distancia Prisma: ");
  // Serial.println(distanceSensorsManager.getSensorDistance(3));
  // // delay(1000);


}