void ConfigurarSerialCerea(){
    Serial3.setTimeout(100);
    //if(BaudRateCerea==1){
    //  Serial3.begin(19200); //CEREA
    //}else if(BaudRateReles==2){
    //  Serial3.begin(57600); //CEREA
    //}else if(BaudRateReles==3){
    //  Serial3.begin(115200); //CEREA
    //}else{
      Serial3.begin(9600); //CEREA
    //}
}
void ConfigurarSerialReles(){
    Serial2.setTimeout(100);
    Serial2.begin(9600); //Reles
    /*
    if(BaudRateReles==1){
      Serial2.println("BAUD;1;END");
      Serial2.flush();
      Serial2.end();
      delay(500);
      Serial2.begin(19200); //Reles
    }else if(BaudRateReles==2){
      Serial2.println("BAUD;2;END");
      Serial2.flush();
      Serial2.end();
      delay(500);
      Serial2.begin(57600); //Reles
    }else if(BaudRateReles==3){
      Serial2.println("BAUD;3;END");
      Serial2.flush();
      delay(500);
      Serial2.begin(115200); //Reles
    }*/
    Serial2.println("@DELAY;200;END");
    Serial2.println("@CAUDAL1;0;END");
    Serial2.println("@CAUDAL2;0;END");
    Serial2.println("@ENCODER1;0;END");
    Serial2.println("@ENCODER2;0;END");
    Serial2.println("@BAR1;0;END");
    Serial2.println("@BAR2;0;END");
    Serial2.println("@BAR3;0;END");
    Serial2.println("@ANALOG1;1;END");
    Serial2.println("@ANALOG2;1;END");
    Serial2.println("@ANALOG3;0;END");
    Serial2.println("@TRAMOS;5;END");
}
void ConfigurarPuertosSerie(){
    GPSConectado=0;
    Serial.begin(9600); //Debug
    ConfigurarSerialCerea();
    ConfigurarSerialReles();
}
void LeerPuertoSerieCAJAMANDO(){
  while (Serial2.available()) {
    TimeOutMando = millis();
    String Comando = "";
    Comando = Serial2.readStringUntil('\n');
    if(Comando.substring(0,1)=="@" && Comando.indexOf(";END")>0){
      //sentencia valida
      String Accion = getValue(Comando,';',0);
      String Dato = "";
      if(Accion==F("@ANALOG1")){
          Dato = getValue(Comando,';',1);
          PasosBruto1 = Dato.toInt();
          if(Invertido==1){
            PuntosTajadera1 = Puntos-((PasosBruto1-Actuador1Cerrado)/PasosPorPunto1);
          }else{
            PuntosTajadera1 = ((PasosBruto1-Actuador1Cerrado)/PasosPorPunto1);
          }
          if(PuntosTajadera1<0){PuntosTajadera1=0;}
          if(PuntosTajadera1>Puntos){PuntosTajadera1=Puntos;}        
          Serial.print("Tajadera1:");
          Serial.println(PuntosTajadera1);
      }else if(Accion==F("@ANALOG2")){
          Dato = getValue(Comando,';',1);
          PasosBruto2 = Dato.toInt();
          if(Invertido==1){
            PuntosTajadera2 = Puntos-((PasosBruto2-Actuador2Cerrado)/PasosPorPunto2);
          }else{
            PuntosTajadera2 = ((PasosBruto2-Actuador2Cerrado)/PasosPorPunto2);
          }
          if(PuntosTajadera2<0){PuntosTajadera2=0;}
          if(PuntosTajadera2>Puntos){PuntosTajadera2=Puntos;}     
          Serial.print("Tajadera2:");
          Serial.println(PuntosTajadera2);
      }else if(Accion==F("@ENC1")){
          Dato = getValue(Comando,';',1);
          Encoder1 = Dato.toInt();
      }else if(Accion==F("@ENC2")){
          Dato = getValue(Comando,';',1);
          Encoder2 = Dato.toInt();
      }else if(Accion==F("@VERSION")){
          VersionCajaReles = getValue(Comando,';',1);
      }
    }
  }
}
void LeerPuertoSerieCEREA(){
  while (Serial3.available()) {
    if(GPSConectado==1){
        TimeOutCerea = millis();
        //parsea al lector gps
        char incomingByte = 0;
        incomingByte = Serial3.read();
        gps.encode(incomingByte);
        Satelites = gps.satellites();
        if(Satelites>50){Satelites=0;}
        if(Satelites<0){Satelites=0;}
        HDOP = gps.hdop();
        HDOP = HDOP/100.00;
        if(Satelites>=SatelitesMin && HDOP<=HDOPMin){
          Velocidad = gps.f_speed_kmph();//100.00;
          Velocidad = Round05(Velocidad);
          if(Velocidad<VelocidadMinima){Velocidad=0;}//por debajo de 2 pasando
          if(Velocidad>VelocidadMaxima){Velocidad=0;}//por debajo de 2 pasando
        }else{
          //solo pongo a cero la velocidad si se sale de rango
          if(Velocidad <0 || Velocidad >100){Velocidad = 0;}
        }            
    }else{
        String Comando = "";
        Comando = Serial3.readStringUntil('\n');
        if(Comando.indexOf("$") > 0 && Comando.indexOf(",") > 0 && Comando.indexOf("*") > 0 && DetectadoCEREA == 0){
          TimeOutCerea = millis();
          //sentencia GPS
          if(GPSConectado==0){
            if(PermitirAutodosisCerea==1){
              PermitirAutodosisCerea = 0;
              GuardarEEPROM(1044,PermitirAutodosisCerea);
            }     
            AlarmaMensaje = "DETECTADO GPS.......";
            AlarmaMillisMensaje = millis();          
            ConfigurarGPS();
          }
          GPSConectado=1;
        }else if(Comando.substring(0,1)=="@" && Comando.indexOf(";END")>0 && GPSConectado == 0){
          TimeOutCerea = millis();
          String Accion = getValue(Comando,';',0);
          String Dato = "";
          if(Accion==F("@CEREA")){
              DetectadoCEREA=1;
              Dato = getValue(Comando,';',1);
              Velocidad = Dato.toFloat();
              Dato = getValue(Comando,';',2);
              if(PermitirAutodosisCerea==1){
                DosisDeseada = Dato.toFloat();
              }
              for(int a=1;a<NumeroTramos+1;a++){
                MtrTramosCerea[a]=0;
              }
              for(int a = 1; a < NumeroTramos+1; a++){
                MtrTramosCerea[a] = getValue(Comando, ';', a+2).toInt();
              }          
          }else if(Accion==F("@VERSION")){
              Serial3.println("@VERSION:" + VERSION + ";END");
          }
        }else{
          //se desecha la trama, no entiende el comando
        }
    }  
  }
}
void ComunicarCereaVuelveAuto(){
    String ZonasActivas = "@BOOMBOX";
    ZonasActivas = ZonasActivas+";1;1";
    ZonasActivas = ZonasActivas +";END";
    if (ZonasActivasPREV!=ZonasActivas || BotonAutomatico==LOW){
      Serial3.println(ZonasActivas);
      LaststrAccion = "";
    }
    ZonasActivasPREV = ZonasActivas;
    TimeApano = millis()+200;
}
void ComunicarZONASaCEREA(){
    int PuntosDeseados = PuntosDeseados1;
    if(PuntosDeseados<1){PuntosDeseados=0;}
    if(PuntosDeseados>Puntos){PuntosDeseados=Puntos;}
    if(PuntosDeseados==0){
      MtrTramosComunicaCEREA[0]=0;
    }else{
      MtrTramosComunicaCEREA[0]=1;
    }
    //MOSTRAR DATOS DE TAJADERA2
    PuntosDeseados = PuntosDeseados2;
    if(PuntosDeseados<1){PuntosDeseados=0;}
    if(PuntosDeseados>Puntos){PuntosDeseados=Puntos;}
    if(PuntosDeseados==0){
      MtrTramosComunicaCEREA[1]=0;
    }else{
      MtrTramosComunicaCEREA[1]=1;
    }
    Serial3.flush();
    if(millis()>TimeApano){
      String ZonasActivas = "@BOOMBOX";
      if(MtrTramosReal[0]==HIGH){
          ZonasActivas = ZonasActivas+";1";
      }else{
          if(MtrTramosPalancas[0]==LOW){
            ZonasActivas = ZonasActivas+";1";
          }else{
            ZonasActivas = ZonasActivas+";0";
          }
      }
      if(MtrTramosReal[1]==HIGH){
          ZonasActivas = ZonasActivas+";1";
      }else{
          if(MtrTramosPalancas[1]==LOW){
            ZonasActivas = ZonasActivas+";1";
          }else{
            ZonasActivas = ZonasActivas+";0";
          }
      }
      ZonasActivas = ZonasActivas +";END";
      if(ZonasActivasPREV!=ZonasActivas || BotonAutomatico==LOW){
        Serial3.println(ZonasActivas);
      }
      ZonasActivasPREV = ZonasActivas;
    }else{
      MtrTramosCerea[1]=1;
      MtrTramosCerea[2]=1;
    }
}
void ComunicarMarcaCEREA(){
  if(LastBotonCerradoTotal!=BotonCerradoTotal){
    if(BotonCerradoTotal==1){
      Serial3.println("@MARC;1;END");
      ComunicarCereaVuelveAuto();
      MtrTramosCerea[1]=1;
      MtrTramosCerea[2]=1;
    }else{
      //CONTROLAR SI ALGUNA SALIDA ESTA ACTIVA, SI ALGUNA ESTA ACTIVA, PINTA, SINO NO PINTES
      int AlgunaActiva = 0;
      for(int a=0;a<2;a++){
        if (MtrTramosComunicaCEREA[a]==HIGH){
          AlgunaActiva = 1;
        }
      }      
      if(AlgunaActiva>0){
        Serial3.println("@MARC;1;END");
      }else{
        Serial3.println("@MARC;0;END");
      }
      ComunicarCereaVuelveAuto();
      MtrTramosCerea[1]=1;
      MtrTramosCerea[2]=1;
    }
    LastBotonCerradoTotal = BotonCerradoTotal;
  }
}
void SendPuntosCerea(){
   if(PuntosAplicados>=0){
      Serial3.print("@PRESION;");
      Serial3.print(PuntosAplicados);
      Serial3.println(";END");
   }
}
void SendDosisCerea(){
  if(DisplayDosisDeseada == 0 ){
    Serial3.println("@CAUDAL;0;END");
    Serial3.println("@WE;0;END");
  }else if(DisplayDosisDeseada>= 0 ){
    Serial3.print("@CAUDAL;");
    Serial3.print(DisplayDosisDeseada);
    Serial3.println(";END");
    Serial3.print("@WE;");
    Serial3.print(DisplayDosisDeseada);
    Serial3.println(";END");
  }
}
void SendLACerea(){
    /*
    if(LitrosDispersados == 0 ){
      Serial3.println("@APLICADO;0;END");
    }else if(LitrosDispersados >= 0){
      Serial3.print("@APLICADO;");
      Serial3.print(LitrosDispersados);
      Serial3.println(";END");
    }
    */
}
void InformarDatosCEREA(){
  if(millis() > MillisInformaCerea + 1000){
      SendPuntosCerea();
      SendDosisCerea();
      SendLACerea();
      MillisInformaCerea = millis();
  }
}
void LecturaPuertosSerie(){
  LeerPuertoSerieCEREA();
  LeerPuertoSerieCAJAMANDO();
  InformarDatosCEREA();
}

void Wait(int Espera){
  long l = millis();
  while(l+Espera < millis()){
    LecturaPuertosSerie();
  }
}

