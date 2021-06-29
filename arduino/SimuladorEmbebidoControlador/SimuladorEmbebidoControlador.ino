//Librerias
#include <TimerOne.h>
//Declaración de Variables
volatile float a,b,h,T,dT,Tant,error,error1;
volatile int Tini,Ta,u,Ref,Kp,Ki,u1;
volatile bool s,c;


void setup() {
  //Inicializar Serial
  Serial.begin(9600);
  //SIMULADOR
  //Valores del simulador
  a=0.00549;
  b=0.03;
  h=0.5;
  Tini=27;
  Ta=25;
  u=40;
  //Valores iniciales
  Tant=Tini;
  dT=0;
  //Controlador Simulado
  Ref=36;
  Kp=1;
  Ki=0.1;
  error1=0;
  u1=0;
  //Inicializar interrupts, Si se desea simulador (variable s=true)
  s=true;
  if(s){
    Timer1.initialize(500000); //Interrupt cada ciertos micro segundos
    Timer1.attachInterrupt(simulador); //Llamar a la función cuando salte interrupt con preferencia
  }
  
}

void loop() {
  //Imprimir valores
  if(c==1){
    Serial.print(millis());
    Serial.print(",");
    Serial.print(T);
    Serial.print(",");
    Serial.println(u);
    c=0;
  }

}

void simulador(){
  //Calculo Temperatura
  T=Tant+dT*h;
  dT=b*(Ta-T)+a*u;
  //Almacen variable
  Tant=T;
  //Imprimir valor
  c=1;
  controlador();
}

void controlador(){
  //Controlar Variable Control
  error=Ref-T;
  u=error*Kp+Ki*error1+u1;
  //Saturacion
  if(u>255){
    u=255;
  }
  if(u<0){
    u=0;
  }
  //Almacen variables
  u1=u;
  error1=error;
  //Resultado
  //return u;
}
