/*
Copyright (c) 2018.  Todos derechos reservados.
Programa de gestión de autodosis de una abonadora dotada de actuadores eléctricos activados por relé y conectada a un sistema CEREA.

Program  : ActiveSprayer_ABONADORA
Version  : V2.1, 24 Mayo 2018
Author(s): Javier Frauca
Coauthor(s):

Special Contribuitor:
Cesar Dominguez, programador de CEREA
Javier Marco, Adolfo Franco, Test Alfa y Beta

Este programa NO es gratuito, por lo que su utilización requiere de
una licencia. La misma se puede adquirira automaticamente al comprar
un Corte de Abonadora, o bien poniendose en contacto con Javier Frauca

Este programa es distribuido tal y como está, y requiere de supervisión
de un operario cualificado para su correcta utilizacion
*/
String VERSION = "CT 2.5.0 ABONADORA";
String VersionCajaReles = "";      //en esta variable se almacenará la versión de la caja de reles
#include "TinyGPS.h"
#include "EEPROM.h"
#include "Wire.h" 
#include "LiquidCrystal_I2C.h"
LiquidCrystal_I2C lcd(0x27,20,4); 
#include "Variables.h"
#include "GPS.h"
#include "Pines.h"
#include "AccesoEEPROM.h"
#include "PuertosSerie.h"
#include "Pantalla.h"
#include "ControlarPalancas.h"
#include "MoverTajaderas.h"
#include "GestionAlarmas.h"

void setup() {
    ConfigurarDisplay();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(VERSION);
    ConfigurarPines();
    CargarConfiguraciones();  
    ConfigurarPuertosSerie();
    if(MaquinaConfigurada!=1){PantallaConfigurar();}
    if(MaquinaCalibrada!=1){PantallaCalibrar();}

    LecturaPuertosSerie();
    delay(20);
    LecturaPuertosSerie();

    PosicionarActuadores();
    //ControlarPirateoSoftware();
}
void loop(){
    LecturaEstadoPalancas();
    LecturaPuertosSerie();
    ControlarBotonMenu();
    ControlarDosis();    
    ControlarPalancas();   //siempre despues del calculo y control de dosis, porque si el tramo esta cerrado deja la dosis a cero
    ControlarAlarmas();
    if (PantallaVisor>0){
      ControlarMenus();    
    }else{
      PintarPantalla();
    }
    MoverTajaderas();
    ComunicarMarcaCEREA();
    Wait(50);//PARA EVITAR REBOTES EN PULSADORES
}
