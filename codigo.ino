/*
En esta practica teniamos que programar el funcionamiento de una ventanilla de
coche controlada por un pulsador y dos finales de carrera uno superior y otro 
inferior que accionan dos motores uno de subida y uno de bajada. El pulsador 
debe de ser reactivo para evitar que los motores se activen al mismo tiempo 
pudiendo interrunpir en cualquier momento el funcionamiento de los motores 
con una pulsacion el paro de ambos y con la segunda pulsacion la activacion
en el sentido opuesto. Para esta practica utilizamos la practica anterior 
modificando su codigo y añadiendo dos pulsadores para simular los finales 
de carrera.

Entradas del sistema: 13 , 12 , 11
Salidas: 10 , 9

Autor: Brais Rey Mirón
Fecha: 11 / Feb / 05
*/

                               // Definir entradas y salidas en pines 12 , 11 , 10
#define PULS 12
#define ARRIBA 10
#define ABAJO 9
#define FNS 13
#define FNI 11

int estado = 1;                // Estado 0 , 1 , 2 : (0 Arriba , 1 Paro , 2 Abajo)
int tiempo = 70;               // Tiempo ciclo

void setup() {                 // Designación de entradas o salidas
 pinMode(PULS, INPUT);
 pinMode(ARRIBA, OUTPUT);
 pinMode(ABAJO, OUTPUT);
 pinMode(FNS, INPUT);
 pinMode(FNI, INPUT);
 Serial.begin(9600);
}

void loop() {
 Control();
 switch(estado) {             // Condiciones de acinamiento de la ventanilla (switch) 
  case 0:
   Subida();
   break;
  case 2:
   Bajada();
   break;
  case 1:
   Paro();
   break;
  case 3:
   Paro();
 }
 Serial.print(" Estado: "); Serial.println(estado);
}
                               // Funciones auxiliares del void loop
void Subida() {                // Estado subida
 digitalWrite(ARRIBA, HIGH);   // Activacion de motor subida
 digitalWrite(ABAJO, LOW);     // Desactivacion motor bajada
 delay(tiempo);
}
void Bajada() {                // Estado bajada
 digitalWrite(ARRIBA, LOW);    // Desactivacion motor subida
 digitalWrite(ABAJO, HIGH);    // Activacion de motor bajada
 delay(tiempo);
}
void Paro() {                  // Estado paro
 digitalWrite(ARRIBA, LOW);   // Desactivacion motor subida
 digitalWrite(ABAJO, LOW);    // Desactivacion motor bajada
 delay(tiempo);
}

void Control() {                // Lectura de todos os sensores de (Control)
 if(digitalRead(PULS)) {        // Canbiar estado en función de lectura del pulsador
  estado = (estado += 1) % 4;   // Actualizacion de estado mediante lectura del pulsador
  while(digitalRead(PULS)) {
  delay(tiempo);
  }
 }                             // Fin de lectura do pulsador (PULS)                             
 if(digitalRead(FNS)) {       
  if(estado != 2) {
   estado = 1;
  }
 }                             
 if(digitalRead(FNI)) {       
  if(estado != 0) {
   estado = 3;
  }
 }                             // Fin de la lectura de entradas (FNA , FNS , PULS)
}
