
int CargarEEPROM(int direccion){
  byte lowByte = EEPROM.read(direccion);
  byte highByte = EEPROM.read(direccion+1);
  return ((lowByte << 0) & 0xFF) + ((highByte << 8) & 0xFF00);
}
void GuardarEEPROM(int direccion, int valor ){
   byte H = highByte(valor);
   byte L = lowByte(valor); 
   EEPROM.write(direccion, L);
   EEPROM.write(direccion+1, H);
}

void CargarConfiguraciones(){
    MaquinaCalibrada = CargarEEPROM(1000);
    MaquinaConfigurada = CargarEEPROM(1002);
    //Anchura = 10;//CargarEEPROM(1004);
    Puntos = CargarEEPROM(1006);
    NumeroTramos = CargarEEPROM(1008);
    if (NumeroTramos==0){
      //intenta recuperalo de la ct
      NumeroTramos = CargarEEPROM(20);
      if(NumeroTramos>0 && NumeroTramos < 10){
        GuardarEEPROM(1008,NumeroTramos);
      }
    }
    if(NumeroTramos>9){NumeroTramos=9;}
    if(NumeroTramos<0){NumeroTramos=1;}

    //BaudRateGPS = CargarEEPROM(1040);
    //if (BaudRateGPS>4) { BaudRateGPS = 0; }
    //if (BaudRateGPS<0) { BaudRateGPS = 0; }
    
    Actuador1Abierto = CargarEEPROM(1010);
    Actuador1Cerrado = CargarEEPROM(1020);
    Actuador2Abierto = CargarEEPROM(1012);
    Actuador2Cerrado = CargarEEPROM(1022);

    if(Actuador1Abierto<Actuador1Cerrado){
      Invertido = 1;
    }
    Recorrido = Actuador1Abierto-Actuador1Cerrado;
    if(Recorrido<0){Recorrido = Recorrido*-1;}
    PasosPorPunto1 = (Actuador1Abierto-Actuador1Cerrado)/Puntos;
    //if (PasosPorPunto1<0){PasosPorPunto1 = PasosPorPunto1 * -1;}
    PasosPorPunto2 = (Actuador2Abierto-Actuador2Cerrado)/Puntos;
    //if (PasosPorPunto2<0){PasosPorPunto2 = PasosPorPunto2 * -1;}
    if(Recorrido<400){Precision = 4;}
    if(Recorrido<600){Precision = 2;}
  /*
    Actuador1Abierto = Actuador1Abierto-10;
    Actuador1Cerrado = Actuador1Cerrado+10;
    Actuador2Abierto = Actuador2Abierto-10;
    Actuador2Cerrado = Actuador2Cerrado+10;
*/
    DosisDeseada = CargarEEPROM(1030);
    ConfiguracionDosis = DosisDeseada;
    
    ConfiguracionVelocidad1 = CargarEEPROM(1032);   
    ConfiguracionPuntos1 = CargarEEPROM(1034);
    ConfiguracionVelocidad2 = CargarEEPROM(1036);   
    ConfiguracionPuntos2 = CargarEEPROM(1038);

    PrecisionSistema = CargarEEPROM(1042);
    if (PrecisionSistema<=0){PrecisionSistema=100;}
    if (PrecisionSistema>100){PrecisionSistema=100;}

    PermitirAutodosisCerea = CargarEEPROM(1044);
    if (PermitirAutodosisCerea<=0){PermitirAutodosisCerea=0;}
    if (PermitirAutodosisCerea>1){PermitirAutodosisCerea=0;}
    
    BaudRateCerea = CargarEEPROM(1046);
    if (BaudRateCerea<=0){BaudRateCerea=0;}
    if (BaudRateCerea>3){BaudRateCerea=0;}
    
    BaudRateReles = CargarEEPROM(1048);
    if (BaudRateReles<=0){BaudRateReles=0;}
    if (BaudRateReles>3){BaudRateReles=0;}
}


