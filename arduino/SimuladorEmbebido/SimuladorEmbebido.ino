//Librerias
#include <TimerOne.h>
//Declaración de Variables
volatile float a,b,h,T,dT,Tant;
volatile int Tini,Ta,u;
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
    Serial.println(T);
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
}
