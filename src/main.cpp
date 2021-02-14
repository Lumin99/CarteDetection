#include <Arduino.h>
#include <RPLidar.h>

RPLidar lidar;

#define RPLIDAR_MOTOR 6
#define D_NEGLIGE 3000
#define ANGLE_DOBSERVATION 46

void setup() {
  Serial.begin(9600);
  lidar.begin(Serial1);

  pinMode(RPLIDAR_MOTOR, OUTPUT);

  analogWrite(RPLIDAR_MOTOR, 250);
  pinMode(13, OUTPUT);
}

void loop() {
  digitalWrite(13,HIGH);
  int i = 0;
  //int y;
  float distance, angle, valeur[200][2];

  do{

    if (IS_OK(lidar.waitPoint())) {
      distance = lidar.getCurrentPoint().distance;
      angle = lidar.getCurrentPoint().angle;

      if((angle >= 0 && angle <= ANGLE_DOBSERVATION) || (angle >= 180 - ANGLE_DOBSERVATION && angle <= 180 + ANGLE_DOBSERVATION) || (angle >= 360 - ANGLE_DOBSERVATION && angle < 360)){
        //if(distance < 3000){
          valeur[i][0] = distance;
          valeur[i][1] = angle;
          i++;
        //}
      }

    } else {
      //mettre en commentaire
      analogWrite(RPLIDAR_MOTOR, 0); //stop the rplidar motor

      // try to detect RPLIDAR...
      rplidar_response_device_info_t info;
      if (IS_OK(lidar.getDeviceInfo(info, 100))) {
         // detected...
         lidar.startScan();

         // start motor rotating at max allowed speed
         analogWrite(RPLIDAR_MOTOR, 250);
         delay(1000);
      }
    }

  }while(i!=200);

  /*Serial.println("Valeur :");
  Serial.println("");

  for(y=0; y<200; y++){

    Serial.print(" Distance : ");
    Serial.println(valeur[y][0]);
    Serial.print(" Angle : ");
    Serial.println(valeur[y][1]);

  }
  Serial.println("");*/

  //Transferer le tableau valeur vers la carte Stratégie
}
