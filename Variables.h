//--------------------------------------------------------------------------------------------------
//CONTROL DE PIRATEO
//--------------------------------------------------------------------------------------------------
PROGMEM const String DesarrolladoPor1 = "Desarrollado por Javier Frauca Sasot";                               //estas variables se utilizan para saber si se ha trucado el programa
PROGMEM const String DesarrolladoPor2 = "jfrauca@proinza.com";                                                //en el momento del setup() se controla que existan y verifica
PROGMEM const String DesarrolladoPor3 = "Propiedad exclusiva de Javier Frauca";                               //aleatoriamente bytes a ver si están o no
PROGMEM const String DesarrolladoPor4 = "Queda prohibida su reproducción o modificación sin autorización";    //si no están, bloquea el programa
//--------------------------------------------------------------------------------------------------
//DEFINICIO DE PINES
//--------------------------------------------------------------------------------------------------
int Precision = 0;
int Recorrido = 0;
long MillisTaj1  = 0;
long MillisTaj2 = 0;
int Invertido = 0;
int DirActuador1 = 0;
int DirActuador2 = 0;
int PinBotonAutoMan = 2;
int PinLedAuto = 3;
int PinCerradoTotal = 4; 
int PinLedCerradoTotal = 5;
int PinAutoDosis = 6;
int PinLedAutoDosis = 7;
int PinPresionUp = 8; 
int PinPresionDown = 9; 
int PinMenu = 10;
int PinLedMenu = 11;
int PinZumbador = 13;
int PinBotonZona1 = A0;
int PinBotonZona2 = A2;
int PinBotonZona3 = A4;
int PinBotonZona4 = A6;
int PinBotonZona5 = A8;
int PinBotonZona6 = A10;
int PinBotonZona7 = A12;
int PinBotonZona8 = A14;
int PinBotonZona9 = A15;
//--------------------------------------------------------------------------------------------------
//GESTION DE ALARMAS
//--------------------------------------------------------------------------------------------------
long MillisParpadeoDisplayAlarma = 0;       //para controlar el parpadeo de la alarma en el display
int EstadoParpadeoAlarma = 0;               //indica si se muestra o no los valores de la alarma
String LastAlarmaMensaje = "";              //ultimo mensaje mostrado de alarma, se utilia para controlar que una misma alarma esté todo el rato en pantalla
String AlarmaMensaje = "";                  //mensaje de alarma
long AlarmaMillisMensaje = 0;               //variable para setear la alarma y mostrarla durante 2 segundos
long AlarmaMillisMensajeRepetida=0;         //para esperar 5 segundos antes de volver a mostrar una misma alarma
//--------------------------------------------------------------------------------------------------
//VARIABLES DE ESTADO Y CONFIGURACION DE MAQUINA
//--------------------------------------------------------------------------------------------------
int Encoder1 = 0;
int Encoder2 = 0;
int TipoActuador = 0; //0 analogico, 1 encoder
int intRuleta = 0;
int PrecisionSistema = 100;
int DetectadoGPS = 0;
int ConfiguradoGPS = 0;
int DetectadoCEREA = 0;
int MaquinaCalibrada = 0;  //flag de si la maquina a pasado por una calibracion o no
int MaquinaConfigurada = 0;//indica si la maquina ha sido configurada por primera vez o no
int NumeroTramos = 0;
int Puntos = 40;         //puntos por defecto del sistema de tajaderas
double Anchura = 24;     //tamaño fijo, se usa en formulas, pero no es necesario que el usuario pueda manipular este dat
int Actuador1Abierto = 0;   //guarda los pasos maximos que da el potenciometro de motor
int Actuador1Cerrado = 0;   //guarda los pasos minimos del potenciometro del motor
int PasosBruto1 = 0;     //guarda la lectura en bruto del potenciometro enviada desde abajo
int PasosPorPunto1 = 0;  //nos dice los pasos por punto que da este motor en funcion de los puntos de la maquina
int PuntosTajadera1 = 0; //nos dice en que punto estÃ¡ la tajadera en este momento
int PuntosDeseados1 = 0; //diremos donde tiene que estar la tajadera
int DosisReal1 = 0;      //indica la dosis que esta tirando por esta puerta en este momento
int Actuador2Abierto = 0;   //guarda los pasos maximos que da el potenciometro de motor
int Actuador2Cerrado = 0;   //guarda los pasos minimos del potenciometro del motor
int PasosBruto2 = 0;     //guarda la lectura en bruto del potenciometro enviada desde abajo
int PasosPorPunto2 = 0;  //nos dice los pasos por punto que da este motor en funcion de los puntos de la maquina
int PuntosTajadera2 = 0; //nos dice en que punto estÃ¡ la tajadera en este momento
int PuntosDeseados2 = 0; //diremos donde tiene que estar la tajadera
int DosisReal2 = 0;      //indica la dosis que esta tirando por esta puerta en este momento

int ConfiguracionDosis = 0;
int ConfiguracionPuntos1 = 0;
double ConfiguracionVelocidad1 = 0;
int ConfiguracionPuntos2 = 0;
double ConfiguracionVelocidad2 = 0;
int PuntosAplicados = 0;
double Velocidad = 0;

long MillisInformaCerea = 0;
int PermitirAutodosisCerea = 0;

int DisplayDosisDeseada = -1;
int DisplayDosisReal1 = -1;
int DisplayDosisReal2 = -1;
int DisplayValor1Tajadera = -1;
int DisplayValor2Tajadera = -1;
int MenuPos = 0;
int PantallaVisor = 0;
int DosisDeseada = 900; //la dosis que tenemos en esta sesion y pretendemos alcanzar, cuando arranca carga el valor de configuraciondosis
//int SobreDosisConsigna = 0;

int LastBotonAutomatico = 0;
int BotonAutomatico = 0;      //digitalRead(PinBotonAutoMan);
int LastBotonCerradoTotal = 0;
int BotonCerradoTotal = 0;
int BotonPresionUp = 0;   
int BotonPresionDown = 0; 
int LastBotonAutoDosis = 0;
int BotonAutoDosis = 0;   
int BotonMenu = 0;       
//--------------------------------------------------------------------------------------------------
//VARIABLES DE COMUNICACIONES
//--------------------------------------------------------------------------------------------------
int BaudRateCerea = 0;
int BaudRateReles = 0;
long TimeOutCerea = 0;
long TimeOutMando = 0;          // Para controlar el tiempo que hace que no se recibe información de la caja de relés, de esta forma controlamos si está activa
int MtrTramosComunicaCEREA[2];
//--------------------------------------------------------------------------------------------------
//VARIABLES DE CONTROL
//--------------------------------------------------------------------------------------------------
long TimeSendCEREAReles = 0;
String ZonasActivasPREV = "";
String LaststrAccion = "";
long TimeLastAccion = 0;
//int LastDIrectionPresion = 0;
//int MtrConsignas[2];
//int MtrConsignasAplicadas[2];
//int MtrPunto[2];
int MtrTramosPalancas[9];
int MtrTramosPalancasAnterior[9];
int MtrTramosCerea[9];
int MtrSalidasReles[9];
int MtrTramosReal[9];
//int MtrSalidasRelesPrevius[9];
long TimeAction = 0;
long TimeApano = 0;
long TimeBotones =0;
//--------------------------------------------------------------------------------------------------
//CARACTERES ESPECIALES
//--------------------------------------------------------------------------------------------------
byte customCharPbL[8] = {
    B11111,
    B10000,
    B10000,
    B10000,
    B10000,
    B10000,
    B10000,
    B11111
};
byte customCharPbM[8] = {
    B11111,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B00000,
    B11111
};
byte customCharPbR[8] = {
    B11111,
    B00001,
    B00001,
    B00001,
    B00001,
    B00001,
    B00001,
    B11111
};
byte customCharPbF[8] = {
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111
};
byte customCharUpDown[8] = {
    B00100,
    B01110,
    B11111,
    B00100,
    B11111,
    B01110,
    B00100,
    B00000
};
byte customCharSave[8] = {
    B01110,
    B11111,
    B11111,
    B11111,
    B11111,
    B11111,
    B01110,
    B00000
};
byte customCharKH[8] = {
    B10100,
    B11000,
    B10101,
    B00010,
    B00100,
    B01101,
    B10111,
    B00101
};
byte customCharFlecha[8] = {
    B00000,
    B01000,
    B01100,
    B01110,
    B01111,
    B01110,
    B01100,
    B01000
};

//--------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------
//FUNCIONES BASICAS
//-------------------------------------------------------------------------------
double Round05(double Valor){
    double VParsed = 0;
    int Tmp = (Valor*100);    //cojo lectura con 2 decimales como entero
    int Tmp2 = (Valor);       //le resto el entero de velocidad, asi tengo un numero de 0 al 99 para ver los decimales
    Tmp2 = Tmp2*100;
    int Diff = Tmp-Tmp2;
    if (Diff<25){
      VParsed = int(Valor);
    }else if (Diff<75){
      VParsed = int(Valor)+0.5;
    }else{
      VParsed = int(Valor)+1;
    }
    return VParsed;
}
int Round10(int Valor){
    int Tmp = Valor;     //cojo lectura con 2 decimales como entero
    int Tmp2 = Valor/10; //le resto el entero de velocidad, asi tengo un numero de 0 al 99 para ver los decimales
    Tmp2 = Tmp2*10;       //trucar la ultima cifra
    int Diff = Tmp-Tmp2;
    if (Diff<5){
      return Tmp2;
    }else{
      return Tmp2+10;
    }
}
String getValue(String data, char separator, int index)
{
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length();

    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
//-------------------------------------------------------------------------------

