/*
  Semaforo

  Prende y apaga 3 LED conectados a las salidas digitales de acuerdo al color.
  Se conecta una salida para el LED VERDE otra para el LED AMARILLO y otra para el LED ROJO.
  El programa enciende durante un tiempo el LED verde, lo apaga luego enciende el LED amarillo
  durante un tiempo menor y lo apaga y luego enciende el LED rojo durante un tiempo y luego lo apaga
  para volver a empezar la secuencia. ( SEMAFORO DE AUTOS ) 
  
  Los LED se conectaran a los PINES:
  SEMAFORO 1
  PIN 12 -> LED ROJO
  PIN 11 -> LED AMARILLO
  PIN 10 -> LED VERDE
  SEMAFORO 2
  PIN 9 -> LED ROJO
  PIN 8  -> LED AMARILLO
  PIN 7  -> LED VERDE

  tiempos
  tiempo de encendido del rojo 5 segundos
  tiempo de encendido del amarillo 2 segundos
  tiempo de encendido del verde 3 segundos.

  tiempo rojo = tiempo verde + tiempo amarillo.

  Desarrollado sobre placa Arduino UNO 

  Inicio 19 Agosto 2021
  by Leonardo Lujan

*/

#define TIEMPO_STOP     5000        // 5000 ms -> 5s
#define TIEMPO_ADELANTE 3000      // 3000 ms -> 3s
#define TIEMPO_PREC     2000      //  2000 ms -> 2s

// SEMAFORO 1
const int LED_ROJO1 = 12;
const int LED_AMARILLO1 = 11;
const int LED_VERDE1 = 10;

// SEMAFORO 2
const int LED_ROJO2 =  9;
const int LED_AMARILLO2 = 8;
const int LED_VERDE2 = 7;

// variable que controlan los cambios de estados.
// los LED se prenden por bajo (LOW) de acuerdo a la conexión
int estadoLedR1 = HIGH;   // estado High = alto en 1
int estadoLedA1 = HIGH;   // 
int estadoLedV1 = LOW;    // comienza con Verde prendido LOW = BAJO en 0

int estadoLedR2 = LOW;
int estadoLedA2 = HIGH;
int estadoLedV2 = HIGH;

// El valor será bastante grande para guardarse en un int
// por lo tanto se deberá declarar unsigned long
unsigned long previos_ms1 = 0;  // variable para controlar el tiempo de encendidos
unsigned long previos_ms2 = 0;
// variable de 
long intervalo1 = TIEMPO_ADELANTE;
long intervalo2 = TIEMPO_STOP;

// Variable para guardar el color
int semaforo1 = 2;   // proxima Luz 
int semaforo2 = 2;  // proxima luz 

void setup() {
  
  // inicializa los pines en salidas digitales.
  pinMode(LED_ROJO1, OUTPUT);    
  pinMode(LED_AMARILLO1, OUTPUT);
  pinMode(LED_VERDE1, OUTPUT);
  pinMode(LED_ROJO2, OUTPUT);
  pinMode(LED_AMARILLO2, OUTPUT);
  pinMode(LED_VERDE2, OUTPUT);

  // Escribe las salidas conectadas.
  digitalWrite(LED_ROJO1, HIGH );
  digitalWrite(LED_ROJO2, LOW );
  digitalWrite(LED_AMARILLO1, HIGH );
  digitalWrite(LED_AMARILLO2, HIGH );
  digitalWrite(LED_VERDE1, LOW );
  digitalWrite(LED_VERDE2, HIGH );
}

// the loop function runs over and over again forever
void loop() {
  
  unsigned long actual_ms1 = millis();

  if ( actual_ms1 - previos_ms1 >=  intervalo1 ) {
      // guarda el ultimo periodo que parpadea el LED
      previos_ms1 = actual_ms1;
      switch ( semaforo1 )
      {
        // VERDE
        case 1:
          estadoLedV1 = cambiaEstado( estadoLedV1 );  
          estadoLedR1 = cambiaEstado( estadoLedR1 );  
          digitalWrite(LED_ROJO1, estadoLedR1 );        // prende verde
          digitalWrite(LED_VERDE1, estadoLedV1 );       // apago rojo                    
          intervalo1 = TIEMPO_ADELANTE;                 // programa tiempo
          break;
        // AMARILLO
        case 2:
          estadoLedV1 = cambiaEstado( estadoLedV1 ); 
          estadoLedA1 = cambiaEstado( estadoLedA1 ); 
          digitalWrite(LED_VERDE1, estadoLedV1 );       // apaga Verde
          digitalWrite(LED_AMARILLO1, estadoLedA1 );    // prende amarillo
          intervalo1 = TIEMPO_PREC;
        break;
        // ROJO
      default:
          estadoLedA1 = cambiaEstado( estadoLedA1 );  
          estadoLedR1 = cambiaEstado( estadoLedR1 );  
          digitalWrite(LED_AMARILLO1, estadoLedA1 );    // apaga amarillo
          digitalWrite(LED_ROJO1, estadoLedR1 );        // prende rojo
          intervalo1 = TIEMPO_STOP;
        break;
      } // fin del switch
      semaforo1 = cambiaColor( semaforo1 );

  } // fin de if

  unsigned long actual_ms2 = millis();

  if( actual_ms2 - previos_ms2 >= intervalo2 )
  {
    previos_ms2 = actual_ms2;
    switch ( semaforo2 )
    {
        // ROJO
        case 1:               
          estadoLedA2 = cambiaEstado( estadoLedA2 );  
          estadoLedR2 = cambiaEstado( estadoLedR2 );  
          digitalWrite(LED_AMARILLO2, estadoLedA2 );    // apaga amarillo
          digitalWrite(LED_ROJO2, estadoLedR2 );        // prende rojo                                               
          intervalo2 = TIEMPO_STOP;                   // programa tiempo
          break;
        // VERDE
        case 2:
          estadoLedR2 = cambiaEstado( estadoLedR2 ); 
          estadoLedV2 = cambiaEstado( estadoLedV2 ); 
          digitalWrite(LED_ROJO2, estadoLedR2 );      // apaga rojo
          digitalWrite(LED_VERDE2, estadoLedV2 );     // prende verde
          intervalo2 = TIEMPO_ADELANTE;
        break;
        // AMARILLO
      default:
          estadoLedV2 = cambiaEstado( estadoLedV2 ); 
          estadoLedA2 = cambiaEstado( estadoLedA2 );          
          digitalWrite(LED_VERDE2, estadoLedV2 );       // apaga verde
          digitalWrite(LED_AMARILLO2, estadoLedA2 );    // prende amarillo      
          intervalo2 = TIEMPO_PREC;
        break;
    } // fin de switch
    semaforo2 = cambiaColor( semaforo2 );

  } // fin de if

} // fin del programa



// Si el valor del semaforo1 es 1 es porque este semaforo 
// esta en verde, lo que indiva que va a pasar a 2 en amarillo y 
// luego al 3 que es el rojo.
// Y el semaforo2 es 1 empieza en rojo, el proximo estado es el
// verde en el estado 2 para luego pasar al amarillo en el 3.
// Y luego todo vuelve a comenzar.
int cambiaColor( int semaforo ){
 
  if( semaforo == 1 ){       // 1 - Verde 
    semaforo = 2;
  }else if (semaforo == 2)    // 2 - amarillo
  {
    semaforo = 3;
  }else{                      // 3 - rojo
    semaforo = 1;
  }
  return semaforo;
}


// funcion que cambia el estado.
int cambiaEstado( int estado ){
    if ( estado == 1 ){
      estado = 0;
    }else{
      estado = 1;
    }
    return estado;
}
