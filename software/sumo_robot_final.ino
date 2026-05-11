#include <Arduino.h>

#define TRIG_FRONT   22
#define ECHO_FRONT   21
#define TRIG_LEFT    32
#define ECHO_LEFT    33
#define TRIG_RIGHT   25
#define ECHO_RIGHT   26

#define LINE_SENSOR  34

#define STBY   15
#define PWMA    5
#define AIN1    0
#define AIN2    2
#define PWMB   17
#define BIN1    4
#define BIN2   16

const bool INVERT_MOTOR_A = true;
const bool INVERT_MOTOR_B = true;

const bool INVERT_LINEA_LOGICA = false;

//parametros
const int VEL_BUSCAR    =  90;
const int VEL_ATACAR    = 120;
const int VEL_RETROCESO = 120;
const int VEL_GIRO_FUGA = 120;

const float DIST_DETECCION = 80.0;
const float DIST_TIMEOUT   = 400.0;

const unsigned long ESPERA_INICIAL_MS = 5000;
const unsigned long T_RETROCESO_MS    = 250;
const unsigned long T_GIRO_FUGA_MS    = 300;

const bool ACTIVAR_DETECCION_LINEA = true;

//estado
enum Estado { ESPERANDO, BUSCANDO, ATACANDO, FUGA_RETROCESO, FUGA_GIRO };
Estado estado = ESPERANDO;

unsigned long t_inicio_estado = 0;
int  ultimo_giro = +1;

float medirDistancia(int trigPin, int echoPin);
void  motorA(int velocidad);
void  motorB(int velocidad);
void  pararMotores();
void  avanzar(int v);
void  retroceder(int v);
void  girarDerecha(int v);
void  girarIzquierda(int v);
bool  veLineaBlanca();

void setup() {
  Serial.begin(115200);
  delay(100);
  Serial.println(F("\n=== SUMO ROBOT v7 FINAL ==="));

  pinMode(TRIG_FRONT, OUTPUT);  pinMode(ECHO_FRONT, INPUT);
  pinMode(TRIG_LEFT,  OUTPUT);  pinMode(ECHO_LEFT,  INPUT);
  pinMode(TRIG_RIGHT, OUTPUT);  pinMode(ECHO_RIGHT, INPUT);
  digitalWrite(TRIG_FRONT, LOW);
  digitalWrite(TRIG_LEFT,  LOW);
  digitalWrite(TRIG_RIGHT, LOW);

  pinMode(LINE_SENSOR, INPUT);

  pinMode(STBY, OUTPUT);
  pinMode(PWMA, OUTPUT); pinMode(AIN1, OUTPUT); pinMode(AIN2, OUTPUT);
  pinMode(PWMB, OUTPUT); pinMode(BIN1, OUTPUT); pinMode(BIN2, OUTPUT);

  digitalWrite(STBY, LOW);
  pararMotores();

  Serial.println(F("Esperando 5 segundos..."));
  unsigned long t0 = millis();
  while (millis() - t0 < ESPERA_INICIAL_MS) {
    Serial.printf("  %lu ms\n", millis() - t0);
    delay(500);
  }

  digitalWrite(STBY, HIGH);
  estado = BUSCANDO;
  t_inicio_estado = millis();
  Serial.println(F("¡Empieza el combate!"));
}

void loop() {
  if (ACTIVAR_DETECCION_LINEA && veLineaBlanca() && estado != ESPERANDO) {
    Serial.println(F("¡LINEA BLANCA!"));
    estado = FUGA_RETROCESO;
    t_inicio_estado = millis();
  }

  //lectura de distancias
  float dF = medirDistancia(TRIG_FRONT, ECHO_FRONT);
  float dL = medirDistancia(TRIG_LEFT,  ECHO_LEFT);
  float dR = medirDistancia(TRIG_RIGHT, ECHO_RIGHT);

  //maquina de estados
  switch (estado) {

    case BUSCANDO: {
      bool vF = (dF > 2 && dF < DIST_DETECCION);
      bool vL = (dL > 2 && dL < DIST_DETECCION);
      bool vR = (dR > 2 && dR < DIST_DETECCION);

      if (vF || vL || vR) {
        estado = ATACANDO;
        t_inicio_estado = millis();
      } else {
        if (ultimo_giro >= 0) girarDerecha(VEL_BUSCAR);
        else                  girarIzquierda(VEL_BUSCAR);
      }
    } break;

    case ATACANDO: {
      float menor = DIST_TIMEOUT;
      char dir = 'F';
      if (dF > 2 && dF < menor) { menor = dF; dir = 'F'; }
      if (dL > 2 && dL < menor) { menor = dL; dir = 'L'; }
      if (dR > 2 && dR < menor) { menor = dR; dir = 'R'; }

      if (menor >= DIST_DETECCION) {
        estado = BUSCANDO;
        t_inicio_estado = millis();
        break;
      }

      switch (dir) {
        case 'F':
          avanzar(VEL_ATACAR);
          break;
        case 'L':
          motorA(VEL_ATACAR / 3);
          motorB(VEL_ATACAR);
          ultimo_giro = -1;
          break;
        case 'R':
          motorA(VEL_ATACAR);
          motorB(VEL_ATACAR / 3);
          ultimo_giro = +1;
          break;
      }
    } break;

    case FUGA_RETROCESO: {
      retroceder(VEL_RETROCESO);
      if (millis() - t_inicio_estado > T_RETROCESO_MS) {
        estado = FUGA_GIRO;
        t_inicio_estado = millis();
        ultimo_giro = -ultimo_giro;
      }
    } break;

    case FUGA_GIRO: {
      if (ultimo_giro >= 0) girarDerecha(VEL_GIRO_FUGA);
      else                  girarIzquierda(VEL_GIRO_FUGA);
      if (millis() - t_inicio_estado > T_GIRO_FUGA_MS) {
        estado = BUSCANDO;
        t_inicio_estado = millis();
      }
    } break;

    default: break;
  }

  static unsigned long t_last_print = 0;
  if (millis() - t_last_print > 200) {
    t_last_print = millis();
    int line_d = digitalRead(LINE_SENSOR);
    bool blanco = veLineaBlanca();
    Serial.printf("E=%d  F=%5.1f  L=%5.1f  R=%5.1f  line=%d  -> %s\n",
                  estado, dF, dL, dR, line_d, blanco ? "BLANCO" : "NEGRO");
  }
}


float medirDistancia(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(3);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  unsigned long dur = pulseIn(echoPin, HIGH, 25000UL);
  if (dur == 0) return DIST_TIMEOUT;
  return dur * 0.0343f / 2.0f;
}

bool veLineaBlanca() {
  int v = digitalRead(LINE_SENSOR);
  bool blanco = (v == LOW);
  if (INVERT_LINEA_LOGICA) blanco = !blanco;
  return blanco;
}

void motorA(int v) {
  if (INVERT_MOTOR_A) v = -v;
  v = constrain(v, -255, 255);
  if (v >= 0) {
    digitalWrite(AIN1, HIGH); digitalWrite(AIN2, LOW);
    analogWrite(PWMA, v);
  } else {
    digitalWrite(AIN1, LOW);  digitalWrite(AIN2, HIGH);
    analogWrite(PWMA, -v);
  }
}

void motorB(int v) {
  if (INVERT_MOTOR_B) v = -v;
  v = constrain(v, -255, 255);
  if (v >= 0) {
    digitalWrite(BIN1, HIGH); digitalWrite(BIN2, LOW);
    analogWrite(PWMB, v);
  } else {
    digitalWrite(BIN1, LOW);  digitalWrite(BIN2, HIGH);
    analogWrite(PWMB, -v);
  }
}

void pararMotores() {
  motorA(0); motorB(0);
  digitalWrite(AIN1, HIGH); digitalWrite(AIN2, HIGH); analogWrite(PWMA, 0);
  digitalWrite(BIN1, HIGH); digitalWrite(BIN2, HIGH); analogWrite(PWMB, 0);
}

void avanzar(int v)        { motorA( v);  motorB( v); }
void retroceder(int v)     { motorA(-v);  motorB(-v); }
void girarDerecha(int v)   { motorA( v);  motorB(-v); }
void girarIzquierda(int v) { motorA(-v);  motorB( v); }
