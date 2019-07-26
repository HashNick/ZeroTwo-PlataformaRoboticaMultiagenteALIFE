#include <QTRSensors.h>
#include <SoftwareSerial.h>

// QTR_NO_EMITTER_PIN.

#define NUM_SENSORS   8     // number of sensors used
#define TIMEOUT       2500  // waits for 2500 microseconds for sensor outputs to go low
#define EMITTER_PIN   4     // emitter is controlled by digital pin 2 
#define DEBUG true

// sensors 0 through 7 are connected to digital pins 3 through 10, respectively
QTRSensorsRC qtrrc((unsigned char[]) {A0,9,A1,A2,A3,A4,7,A5},
  NUM_SENSORS, TIMEOUT, EMITTER_PIN);
unsigned int sensorValues[NUM_SENSORS];
 
SoftwareSerial modulo(2,3); // Pin 2 receptor, Pin 3 transmisor

int IN1=5;
int IN2=6;
int IN3=10;
int IN4=11;
int value_of_speed = 255;
int delayON = 20;
int num;
String cadena;

void setup() {
  delay(500);//Calibra los sensores
  for (int i = 0; i < 400; i++)  // make the calibration take about 10 seconds
  {
    qtrrc.calibrate();       // reads all sensors 10 times at 2500 us per read (i.e. ~25 ms per call)
  }//Finaiza la calibración.
  
  configPins();// Configura los pines para darle movimiento al robot
  
  modulo.begin(9600);//Inicia la comunicación con el modulo Wi-Fi
  delay(1000);
  
  Serial.begin(9600);
  
  for (int i = 0; i < NUM_SENSORS; i++)
  {
    Serial.print(qtrrc.calibratedMinimumOn[i]);
    Serial.print(' ');
  }
  Serial.println();

  // print the calibration maximum values measured when emitters were on
  for (int i = 0; i < NUM_SENSORS; i++)
  {
    Serial.print(qtrrc.calibratedMaximumOn[i]);
    Serial.print(' ');
  }
  Serial.println();
  Serial.println();
  delay(1000);
  
  modulo.begin(9600);
  
  pinMode(13,OUTPUT);
  digitalWrite(13,LOW);
  
  qtrrc.readLine(sensorValues);

  // print the sensor values as numbers from 0 to 1000, where 0 means maximum reflectance and
  // 1000 means minimum reflectance, followed by the line position
  for (unsigned char i = 0; i < NUM_SENSORS; i++)
  {
    Serial.print(sensorValues[i]);
    Serial.print('\t');
  }
  Serial.println();

}

void loop(){
  String cadena = modulo.readString();
  if(cadena == "1" || cadena == "2" || cadena == "3" || cadena == "4"){
    int state = cadena.toInt(); // Obtener el estado del pin a mostrar
    switch( state ){
      case 1:
        Serial.print("Avanzando\n");
        avanzar();
        break;
      case 2:
        Serial.print("Retrocediendo\n");
        retroceder();
        break;
      case 3:
        Serial.print("Derecha\n");
        derecha();
        break;
      case 4:
        Serial.print("Izquierda\n");
        izquierda();
        break;
    }
    qtrrc.readLine(sensorValues);

    // print the sensor values as numbers from 0 to 1000, where 0 means maximum reflectance and
    // 1000 means minimum reflectance, followed by the line position
    cadena = "";
    for ( unsigned char i = 0; i < NUM_SENSORS; i++ ){
      Serial.print(sensorValues[i]);
      Serial.print('\t');
      cadena += ( ( String )sensorValues[i] ) + " ";
    }
    Serial.println(); // uncomment this line if you are using raw values

    
    //responder y cerrar la conexión para que el navegador no se quede cargando 
    // página web a enviar
    String webpage = "";
    if (state==1)
      webpage += "Avanzo " + cadena;
    else if (state==2)
      webpage += "Retrocedio " + cadena;
    else if (state==3)
      webpage += "Giro a la derecha "  + cadena;
    else if (state==4)
      webpage += "Giro a la izquierda " + cadena;
    else{
      webpage += "Nada";
    }
    modulo.println(webpage);
  }
}

void configPins() {
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(IN3,OUTPUT);
  pinMode(IN4,OUTPUT);
}

void avanzar(){
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
  analogWrite(IN1, 0);
  analogWrite(IN2, value_of_speed);
  analogWrite(IN3, value_of_speed);
  analogWrite(IN4, 0);
  Serial.println("Avanzan ambos motores");
  Serial.print("\t");
  delay(delayON);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
}

void retroceder(){
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
  analogWrite(IN1, value_of_speed);
  analogWrite(IN2, 0);
  analogWrite(IN3, 0);
  analogWrite(IN4, value_of_speed);
  Serial.println("Avanzan ambos motores");
  Serial.print("\t");
  delay(delayON);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
}

void derecha(){
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
  analogWrite(IN1, 0);
  analogWrite(IN2, value_of_speed);
  analogWrite(IN3, 0);
  analogWrite(IN4, value_of_speed);
  Serial.println("Avanzan ambos motores");
  Serial.print("\t");
  delay(delayON);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
}

void izquierda(){
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
  analogWrite(IN1, value_of_speed);
  analogWrite(IN2, 0);
  analogWrite(IN3, value_of_speed);
  analogWrite(IN4, 0);
  Serial.println("Avanzan ambos motores");
  Serial.print("\t");
  delay(delayON);
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
}
