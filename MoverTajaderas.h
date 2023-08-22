
void MoverActuadores(){
  String Actu1 = "";
  String Actu2 = "";
  if(Invertido==1){
    if(DirActuador1>0){
      Actu1 = "1;0";
    }else if(DirActuador1<0){
      Actu1 = "0;1";
    }else{
      Actu1 = "0;0";
    }
    if(DirActuador2>0){
      Actu2 = "1;0";
    }else if(DirActuador2<0){
      Actu2 = "0;1";
    }else{
      Actu2 = "0;0";
    }
  }else{
    if(DirActuador1>0){
      Actu1 = "0;1";
    }else if(DirActuador1<0){
      Actu1 = "1;0";
    }else{
      Actu1 = "0;0";
    }
    if(DirActuador2>0){
      Actu2 = "0;1";
    }else if(DirActuador2<0){
      Actu2 = "1;0";
    }else{
      Actu2 = "0;0";
    }
  }  
  String strAccion = "@CEREA;0;0;0;" + Actu1 + ";" + Actu2 + ";END";
  if(LaststrAccion!=strAccion){
      Serial2.println(strAccion);
      Serial.println(strAccion);
  }
  LaststrAccion = strAccion;
}

void ControlarDosis(){
    //------------------------------------------------------------------------------------
    //CONTROL DE POSICION DE LAS 2 TAJADERAS
    //------------------------------------------------------------------------------------
    double DosisMinutoRef1 = (ConfiguracionVelocidad1*Anchura*ConfiguracionDosis)/600;
    double DosisMinutoRef2 = (ConfiguracionVelocidad2*Anchura*ConfiguracionDosis)/600;

    /*
     * Ya se los dos puntos, ahora tengo que sacar la ecuacion de la recta
     * con la ecuacion de la recta tengo que sacar 2 cosas
     *    una es la dosis que se está echando ahora (DosisReal)
     *    otra es el punto que tenemos que llevar para la dosis que deseamos, esta parte solo se calcula si tiene presionado autodosis
     *    
     */
    double k = (ConfiguracionPuntos2-ConfiguracionPuntos1) / (DosisMinutoRef2-DosisMinutoRef1);
    
    double DosisMinutoAhora1 = ((PuntosTajadera1-ConfiguracionPuntos1)/k)+DosisMinutoRef1;
    if(DosisMinutoAhora1<0) { DosisMinutoAhora1 = DosisMinutoAhora1*-1;}
    DosisReal1 = (DosisMinutoAhora1*600)/(Velocidad*Anchura);
    if (PuntosTajadera1<=0){DosisReal1=0;}

    double DosisMinutoAhora2 = ((PuntosTajadera2-ConfiguracionPuntos1)/k)+DosisMinutoRef1;
    if(DosisMinutoAhora2<0) { DosisMinutoAhora2 = DosisMinutoAhora2*-1;}
    DosisReal2 = (DosisMinutoAhora2*600)/(Velocidad*Anchura);
    if (PuntosTajadera2<=0){DosisReal2=0;}
    
    if(BotonAutoDosis==HIGH){
        if(GPSConectado==1 && (Satelites<6 || HDOP>1.2)){
          //no hacemos nada, el gps se ha ido a la mierda
        }else{
          //actuar sobre PuntosDeseados1 y PuntosDeseados2
          //se los puntos que llevo, en cada tajadera, se la velocidad y el ancho
          //tengo que saber los puntos que deberia de llevar
          double DosisMinutoDeseada = Velocidad*Anchura*DosisDeseada/600;
          if (DosisMinutoDeseada<=0){
            PuntosAplicados = 0;
          }else{
            PuntosAplicados = ((DosisMinutoDeseada-DosisMinutoRef1)*k)+ConfiguracionPuntos1;
            if(PuntosAplicados<0){PuntosAplicados=0;}
            if(PuntosAplicados>Puntos){PuntosAplicados=Puntos;}
          }
          if(Velocidad<=0){PuntosAplicados=0;}
          if(GPSConectado==1 && Velocidad <2){PuntosAplicados=0;}
        }     
           
    }else{//no tiene autodosis activado
        if(BotonPresionDown==HIGH){
            if(PuntosAplicados>0){
              PuntosAplicados = PuntosAplicados-1;
            }
        }else if(BotonPresionUp==HIGH){
            if(PuntosAplicados<Puntos){
              PuntosAplicados = PuntosAplicados+1;
            }
        }
    }
}
void MoverTajaderas(){

      DirActuador1=0;
      DirActuador2=0;

      String strAccion = "";
      int Direccion = 0;
      int Diferencia1 = 0;
      int Diferencia2 = 0;

      Direccion = 0;
      Diferencia1 = PuntosDeseados1-PuntosTajadera1;
      if(Diferencia1>0){Direccion=1;}
      if(Diferencia1<0){Direccion=-1;Diferencia1=Diferencia1*-1;}
      if(Direccion<0 && PuntosTajadera1<0) {Diferencia1=0;}
      if(Direccion>0 && PuntosTajadera1>Puntos) {Diferencia1=0;}
      if(Direccion!=0 && Diferencia1!=0){
        if(Diferencia1 < 2 && PuntosDeseados1 > 0 && PuntosDeseados1 < Puntos){
        }else if(Diferencia1<2){
            if(millis()-MillisTaj1>1000){
              DirActuador1=Direccion;
              MillisTaj1 = millis();
            }
        }else if(Diferencia1<4){
            if(millis()-MillisTaj1>500){
              DirActuador1=Direccion;
              MillisTaj1 = millis();
            }
        }else{
            MillisTaj1 = millis();
            DirActuador1=Direccion;
        }
      }      
      Direccion = 0;
      Diferencia2 = PuntosDeseados2-PuntosTajadera2;
      if(Diferencia2>0){Direccion=1;}
      if(Diferencia2<0){Direccion=-1;Diferencia2=Diferencia2*-1;}
      if(Direccion<0 && PuntosTajadera2<2) {Diferencia2=0;}
      if(Direccion>0 && PuntosTajadera2>Puntos) {Diferencia2=0;}
      if(Direccion!=0 && Diferencia2 != 0){
        if(Diferencia2<2 && PuntosDeseados2 > 0 && PuntosDeseados2 < Puntos){
        }else if(Diferencia2<2){
            if(millis()-MillisTaj2>1000){
              DirActuador2=Direccion;
              MillisTaj2 = millis();
            }
        }else if(Diferencia2<4){
            if(millis()-MillisTaj2>500){
              DirActuador2=Direccion;
              MillisTaj2 = millis();
            }
        }else{
            DirActuador2=Direccion;
            MillisTaj2 = millis();
        }
      }      
      MoverActuadores();
}
void PosicionarActuadores(){
    long Espera = 0;
    int Fallo = 0;

    Serial.print("Invertido:");
    Serial.println(Invertido);
    Serial.print("Actuador1:");
    Serial.println(PuntosTajadera1);
    Serial.print("Cerrado 1:");
    Serial.println(Actuador1Cerrado);
    Serial.print("Abierto 1:");
    Serial.println(Actuador1Abierto);
    Serial.print("Actuador2:");
    Serial.println(PuntosTajadera2);
    Serial.print("Cerrado 2:");
    Serial.println(Actuador2Cerrado);
    Serial.print("Abierto 2:");
    Serial.println(Actuador2Abierto);
   
    lcd.setCursor(0, 2);
    lcd.print("Posicionando....");
    
    Espera = millis()+5000;
    while(PuntosTajadera1> 0 && Fallo == 0){
      DirActuador1 = -1;
      DirActuador2 = 0;
      MoverActuadores();
      LecturaPuertosSerie();
      if (millis()>Espera){Fallo = 1;}
    }
    DirActuador1 = 0;
    DirActuador2 = 0;
    MoverActuadores();
    if(Fallo==0){
      Espera = millis()+5000;
      while(PuntosTajadera1<0){
        DirActuador1 = 1;
        DirActuador2 = 0;
        MoverActuadores();
        LecturaPuertosSerie();
        if (millis()>Espera){Fallo = 1;}
        if(Fallo==1){break;}
      }
      DirActuador1 = 0;
      DirActuador2 = 0;
      MoverActuadores();
    }
    if(Fallo==0){  
      Espera = millis()+5000;
      while(PuntosTajadera2>0){
        DirActuador1 = 0;
        DirActuador2 = -1;
        MoverActuadores();
        LecturaPuertosSerie();
        if (millis()>Espera){ Fallo = 1; }
        if(Fallo==1){break;}
      }
      DirActuador1 = 0;
      DirActuador2 = 0;
      MoverActuadores();
    }
    if(Fallo==0){
      Espera = millis()+5000;
      while(PuntosTajadera2<0){
        DirActuador1 = 0;
        DirActuador2 = 1;
        MoverActuadores();
        LecturaPuertosSerie();
        if (millis()>Espera){Fallo = 1;}
        if(Fallo==1){break;}
      }
      DirActuador1 = 0;
      DirActuador2 = 0;
      MoverActuadores();
    }
    if(Fallo!=0){
      PantallaCalibrar();
    }else{
      lcd.setCursor(0, 2);
      lcd.print("Posicionado     ");
      lcd.clear();
    }
}

