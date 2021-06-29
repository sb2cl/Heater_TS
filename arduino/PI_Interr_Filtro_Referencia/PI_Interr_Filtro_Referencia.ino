//Librerias a incluir: Wire.h para comunicación I2C, Adafruit_MLX90614.h para sensor Temperatura y LiquidCrystal.h para pantalla
#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include <LiquidCrystal.h>
#include <TimerOne.h>

//Definición del Objeto STemp como sensor de Temperatura
Adafruit_MLX90614 STemp = Adafruit_MLX90614();

//Definición del Objeto lcd como pantalla conectado a pines 7,6,5,4,3,2
LiquidCrystal lcd(7,6,5,4,3,2);

//Declaración de variables
volatile float tamb,tobj,kp,ti,ts,set,ref,e,e1=0,p0,p1,u,u1,tobj1,dT=0,alpha,beta;
volatile int gate=8,salida,a;
int b1=9,b2=10,b3=11,b4=12,demora; //Pines del stepper
volatile bool b=1; //imprimir por pantalla cada cierto tiempo

//Inicialización del Serial Monitor y del sensor, establecer gate Output, inicializar pantalla como 16 caract y 2 lineas
void setup() {
  Serial.begin(9600);
  STemp.begin();
  pinMode(gate,OUTPUT);
  lcd.begin(16, 2);
  //Valores PID
  kp=3.96*0.5;
  ti=22*10; //De 30 a 42 sin overshoot
  ts=0.5*1000;
  p0=kp;
  p1=kp*((ts-ti)/ts);
  //Valor deseado de temperatura
  set=30;
  //Valor filtro Temperatura
  alpha=0.75;

  tobj=STemp.readObjectTempC();
  tobj1=tobj;
  
  //Inicializar pines del stepper y velocidad (demora entre pasos)
  pinMode(b1, OUTPUT);
  pinMode(b2, OUTPUT);
  pinMode(b3, OUTPUT);
  pinMode(b4, OUTPUT);
  demora = 2;
  
  //Inicializar interrupts
  Timer1.initialize(500000); //Interrupt cada ciertos micro segundos
  Timer1.attachInterrupt(controlPI); //Llamar a la función cuando salte interrupt con preferencia
}

void loop() {
  //Plot en pantalla: Colocar cursor e imprimir valores
  if(b==1){
      lcd.setCursor(0,0);
      lcd.print("T Res C = ");
      lcd.print(tobj);
      lcd.setCursor(0,1);
      lcd.print("T Set C = ");
      lcd.print(set);
      Serial.print(millis());
      Serial.print(",");
      Serial.print(salida);
      Serial.print(",");
      Serial.print(tobj);
      Serial.print(",");
      Serial.print(dT*1000);
      Serial.print(",");
      Serial.println(ref);
      //Lectura de Temperatura
      tobj=STemp.readObjectTempC();
      b=0;

  }

  
  

  //Control del motor stepper remover
  remover();


}

void controlPI(){
  //Tiempo de reloj entre interrupts de 100ms para tomar 5 valores
  //y hacer la media entre ellos, de manera que tomo un valor promediado cada 500ms


  //PI
  //Filtro temperatura
  tobj=tobj*(1-alpha)+alpha*tobj1;
  //Calculo derivada
  dT=(tobj-tobj1)/0.5;
  //Control de Referencia
  beta=set-tobj-dT*60;
  if(beta<0){
    ref=0;
  }
  else{
    ref=set;
  }
  //Calculo del error
  e=ref-tobj;
  u=p0*e+p1*e1+u1;
  
  //Anti-Wind up + control de temperatura max (2V max para no alcanzar 50 grados)
  if(u>12){
    u=12;
  }
  if(u<0){
    u=0;
  }
  //Accion de control
  salida=(255.0/12.0)*u;
  analogWrite(gate,salida);
  //Almacen de variables
  e1=e;
  u1=u;
  tobj1=tobj;
  //Limpiar variable
  b=1;
}

void remover(){
  digitalWrite(b1, HIGH);  // paso 1 
  digitalWrite(b2, LOW);
  digitalWrite(b3, LOW);
  digitalWrite(b4, LOW);
  delay(demora);

  digitalWrite(b1, HIGH);  
  digitalWrite(b2, HIGH);
  digitalWrite(b3, LOW);
  digitalWrite(b4, LOW);
  delay(demora);

  digitalWrite(b1, LOW); // paso 2
  digitalWrite(b2, HIGH);
  digitalWrite(b3, LOW);
  digitalWrite(b4, LOW);
  delay(demora);

  digitalWrite(b1, LOW);
  digitalWrite(b2, HIGH);
  digitalWrite(b3, HIGH);
  digitalWrite(b4, LOW);
  delay(demora);

  digitalWrite(b1, LOW); // paso 3
  digitalWrite(b2, LOW);
  digitalWrite(b3, HIGH);
  digitalWrite(b4, LOW);
  delay(demora);

  digitalWrite(b1, LOW); 
  digitalWrite(b2, LOW);
  digitalWrite(b3, HIGH);
  digitalWrite(b4, HIGH);
  delay(demora);

  digitalWrite(b1, LOW); // paso 4
  digitalWrite(b2, LOW);
  digitalWrite(b3, LOW);
  digitalWrite(b4, HIGH);
  delay(demora);

  digitalWrite(b1, HIGH);
  digitalWrite(b2, LOW);
  digitalWrite(b3, LOW);
  digitalWrite(b4, HIGH);
  delay(demora);
}
