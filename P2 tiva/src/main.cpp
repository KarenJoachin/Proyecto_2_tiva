//--------------------------------------------------------------------------------
//Universidad del Valle de Guatemala
//BE3015 Electronica Digital 2
//Karen Joachin
//Proyecto 2
//codigo tiva
//-----------------------------------------------------------------------------
//Librerias
//-----------------------------------------------------------------------------
#include <Arduino.h>

//-----------------------------------------------------------------------------
//Definiciond de etiquetas
//-----------------------------------------------------------------------------

#define BTN PF_0
//#define BTN2 PF_4
// COMUNICACION UART
# define Rx2 PD_6
# define Tx2 PD_7


//-----------------------------------------------------------------------------
//Variabls Globales
//-----------------------------------------------------------------------------
int sube = 0;
int contador = 0;
bool presionar = false;


int pesoR;
//-----------------------------------------------------------------------------
//ISR
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//Configuracion
//-----------------------------------------------------------------------------

void setup()
{
  Serial.begin(115200);  //  serial para monitor
  Serial2.begin(115200); // con esp32


  //botones de tiva
  pinMode(BTN, INPUT_PULLUP);
  // pinMode(BTN2, INPUT_PULLUP);
}

//-----------------------------------------------------------------------------
//loop principal
//-----------------------------------------------------------------------------

void loop()
{
  //********** control de boton -----
  int suma = digitalRead(BTN);// se lee el estado del boton
  if (suma != sube) // comparo el estado actual con el anterior
  {
    if (suma == LOW)// si la lectura del boton es 0 se toma como cambio
    {
      presionar = true; // siginifica que si se presiono el boton
      contador++; // cuenta +1
      //Serial.println(contador);
    }
    sube = suma;
    if (contador > 1)
    {
      contador = 0;
    }
  }

  //-----------------------------------
  // RECIBIR DE ESP32 y enviar
  if (contador == 1)
  {
    pesoR = Serial2.read();
    Serial.println("Recibi:");
    Serial.println(pesoR);
    delay(500);
    contador = 0;
    Serial2.write (1);
  } 
}

