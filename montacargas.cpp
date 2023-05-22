// Felipe Parache Parcial 1 Sistema de Procesamiento de Datos Parte Domiciliaria
# include <Servo.h>

Servo miServo;

int fotodiodo = A0;
int sensorFuerza = A1;

// Leds verde y rojo
int ledVerde = 13;
int ledRoja = 12;
// Display 7 segmentos
int ledMedio = 11; // LED MEDIO
int ledSupIzq = 10; // LED ARRIBA IZQUIERDA
int ledSup = 9; // LED ARRIBA SUPERIOR
int ledSupDer = 8; // LED ARRIBA DERECHA
int ledInfIzq = 7; // LED ABAJO IZQUIERDA
int ledInf = 6; // LED ABAJO INFERIOR
int ledInfDer = 5; // LED ABAJO DERECHA
// Boton subir, bajar y detenerse
int BotonSubir = 4;
int BotonBajar = 3;
int BotonDetener = 2;
// Variables de control de pisos
int pisoActual;
int detener;
int sube;
int baja;
int estado;
int tiempo;

void setup(){
  
  miServo.attach(A2);
  // Leds verde y rojo
  pinMode(ledVerde, OUTPUT);
  pinMode(ledRoja, OUTPUT);
  // Display 7 segmentos
  pinMode(ledMedio, OUTPUT);
  pinMode(ledSupIzq, OUTPUT);
  pinMode(ledSupDer, OUTPUT);
  pinMode(ledSup, OUTPUT);
  pinMode(ledInfIzq, OUTPUT);
  pinMode(ledInfDer, OUTPUT);
  pinMode(ledInf, OUTPUT);
  // Boton subir, bajar y detenerse
  pinMode(BotonSubir, INPUT);
  pinMode(BotonBajar, INPUT);
  pinMode(BotonDetener, INPUT_PULLUP);
  
  detener = 0;
  sube = 1;
  baja = -1;
  
  estado = detener;
  
  pisoActual = 0;
  
  Serial.begin(9600);
}

void loop(){
  
  int botonSubir;
  botonSubir = digitalRead(BotonSubir);
  
  int botonBajar;
  botonBajar = digitalRead(BotonBajar);
  
  int botonDetener;
  botonDetener = digitalRead(BotonDetener);
  
  Serial.print("Piso: ");    
  Serial.println(pisoActual);
  
  numeroPiso(pisoActual);
  
  cambiarEstado(botonDetener, botonSubir, botonBajar, 0, 9);
  
  if (estado == detener) {
    digitalWrite(ledRoja, HIGH);
    
    int fotodiodoValor = analogRead(fotodiodo);
    
    digitalWrite(ledVerde, LOW);
    
  	Serial.print("Fotodiodo: ");
  	Serial.println(fotodiodoValor);
    
   	tiempo = 1000;
  }
  
  else {
    digitalWrite(ledRoja, LOW);
    int fotodiodoValor = analogRead(fotodiodo);
    digitalWrite(ledVerde, HIGH);
    
    Serial.print("Fotodiodo: ");
  	Serial.println(fotodiodoValor);
    
    subirBajarPisos(0, 9);
    tiempo = 2000;
  }
  delay(tiempo);
}

void cambiarEstado(int detener, int subir, int bajar, int primerPiso, int ultimoPiso){
  
  if (detener == LOW){
    estado = detener;
    Serial.println("Montacargas detenido");
  }
  
  else if (subir == HIGH && estado != sube && pisoActual < ultimoPiso){
    estado = sube;
    Serial.println("Montacargas subiendo");
  }
  
  else if (bajar == LOW && estado != baja && pisoActual > primerPiso){
    estado = baja;
    Serial.println("Montacargas bajando");
  }
}

void subirMontacargas(int ultimoPiso){
  
  if(pisoActual < ultimoPiso){
    pisoActual += 1;
    estado = sube;
  }
  
  else{
    estado = detener;
  }
}

void bajarMontacargas(int primerPiso){
  
  if(pisoActual > primerPiso){
    pisoActual -= 1;
  }
  
  else{
    estado = detener;
  }
}

void subirBajarPisos(int primerPiso, int ultimoPiso){
  
  if(estado == sube){
    medirFuerza();
    
  	subirMontacargas(ultimoPiso);
    
    miServo.write(0);
  	delay(1000);
    miServo.write(180);
  }
  
  else if(estado == baja){
    medirFuerza();
    
  	bajarMontacargas(primerPiso);
    
    miServo.write(0);
  	delay(1000);
    miServo.write(180);
  }
}

void cero(){
  // Display 7 segmentos. Forma 0
  
  digitalWrite(ledSupIzq, HIGH);
  digitalWrite(ledSup, HIGH);
  digitalWrite(ledSupDer, HIGH);
  digitalWrite(ledInfDer, HIGH);
  digitalWrite(ledInf, HIGH);
  digitalWrite(ledInfIzq, HIGH);
}

void uno(){
  // Display 7 segmentos. Forma 1 
  
  digitalWrite(ledSupDer, HIGH);
  digitalWrite(ledInfDer, HIGH);
}

void dos(){
  // Display 7 segmentos. Forma 2
  
  digitalWrite(ledSup, HIGH);
  digitalWrite(ledSupDer, HIGH);
  digitalWrite(ledMedio, HIGH);
  digitalWrite(ledInfIzq, HIGH);
  digitalWrite(ledInf, HIGH);
}

void tres(){
  // Display 7 segmentos. Forma 3
  
  digitalWrite(ledSup, HIGH);
  digitalWrite(ledSupDer, HIGH);
  digitalWrite(ledMedio, HIGH);
  digitalWrite(ledInfDer, HIGH);
  digitalWrite(ledInf, HIGH);
}

void cuatro(){
  // Display 7 segmentos. Forma 4
  
  digitalWrite(ledSupIzq, HIGH);
  digitalWrite(ledSupDer, HIGH);
  digitalWrite(ledMedio, HIGH);
  digitalWrite(ledInfDer, HIGH);
}

void cinco(){
  // Display 7 segmentos. Forma 5
  
  digitalWrite(ledSup, HIGH);
  digitalWrite(ledSupIzq, HIGH);
  digitalWrite(ledMedio, HIGH);
  digitalWrite(ledInfDer, HIGH);
  digitalWrite(ledInf, HIGH);
}

void seis(){
  // Display 7 segmentos. Forma 6
  
  digitalWrite(ledSup, HIGH);
  digitalWrite(ledSupIzq, HIGH);
  digitalWrite(ledMedio, HIGH);
  digitalWrite(ledInfIzq, HIGH);
  digitalWrite(ledInfDer, HIGH);
  digitalWrite(ledInf, HIGH);
}

void siete(){
  // Display 7 segmentos. Forma 7
  
  digitalWrite(ledSup, HIGH);
  digitalWrite(ledSupDer, HIGH);
  digitalWrite(ledInfDer, HIGH);
}

void ocho(){
  // Display 7 segmentos. Forma 8
  
  digitalWrite(ledSup, HIGH);
  digitalWrite(ledSupDer, HIGH);
  digitalWrite(ledSupIzq, HIGH);
  digitalWrite(ledMedio, HIGH);
  digitalWrite(ledInfDer, HIGH);
  digitalWrite(ledInfIzq, HIGH);
  digitalWrite(ledInf, HIGH);
}

void nueve(){
  // Display 7 segmentos. Forma 9
  
  digitalWrite(ledSup, HIGH);
  digitalWrite(ledSupDer, HIGH);
  digitalWrite(ledSupIzq, HIGH);
  digitalWrite(ledMedio, HIGH);
  digitalWrite(ledInfDer, HIGH);
  digitalWrite(ledInf, HIGH);
}

void apagarDisplay(){
  // Apaga display 7 segmentos.
  
  digitalWrite(ledSup, LOW);
  digitalWrite(ledSupIzq, LOW);
  digitalWrite(ledSupDer, LOW);
  digitalWrite(ledMedio, LOW);
  digitalWrite(ledInfDer, LOW);
  digitalWrite(ledInfIzq, LOW);
  digitalWrite(ledInf, LOW);
}

void numeroPiso(int numero){
  switch (numero) {
    case 0:
    apagarDisplay();
    cero();
    break;
    case 1:
    apagarDisplay();
    uno();
   	break;
    case 2:
    apagarDisplay();
    dos();
	break;
    case 3:
    apagarDisplay();
    tres();
    break;
    case 4:
    apagarDisplay();
    cuatro();
    break;
    case 5:
    apagarDisplay();
    cinco();
    break;
    case 6:
    apagarDisplay();
    seis();
    break;
    case 7:
    apagarDisplay();
    siete();
    break;
    case 8:
    apagarDisplay();
    ocho();
    break;
    case 9:
    apagarDisplay();
    nueve();
    break;
  }
}

void medirFuerza(){
  int sensorFuerzaValor = analogRead(sensorFuerza);
  Serial.print("Fuerza generada: ");
  Serial.println(sensorFuerzaValor);
}
