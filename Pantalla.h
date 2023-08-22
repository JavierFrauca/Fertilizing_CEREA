void ConfigurarDisplay(){
    lcd.init();
    lcd.backlight();
    lcd.createChar(0, customCharPbL); 
    lcd.createChar(1, customCharPbM); 
    lcd.createChar(2, customCharPbR); 
    lcd.createChar(3, customCharPbF); 
    lcd.createChar(4, customCharUpDown);
    lcd.createChar(5, customCharSave);
    lcd.createChar(6, customCharKH);
    lcd.createChar(7, customCharFlecha);
}
int PantallaControlaPalancaMasMenos(){
  int temp = 0;
  temp = !digitalRead(PinPresionDown);
  if(temp==HIGH){
    while (temp==HIGH){
      delay(100);
      temp = !digitalRead(PinPresionDown);
      LecturaPuertosSerie();
    }
    return -1;
  }
  temp = !digitalRead(PinPresionUp);
  if(temp==HIGH){
    while (temp==HIGH){
      delay(100);
      temp = !digitalRead(PinPresionUp);
      LecturaPuertosSerie();
    }
    return 1;
  }
  return 0;
}
int PantallaControlarGrabar(){
  int temp = 0;
  temp = !digitalRead(PinMenu);
  if(temp==HIGH){
    while (temp==HIGH){
        delay(100);
        temp = !digitalRead(PinMenu);
        LecturaPuertosSerie();
    }
    return 1;
  }else{
    LecturaPuertosSerie();
    return 0;
  }    
}
void LineaOK(){
  lcd.setCursor(0, 3);
  lcd.print("                    ");
  lcd.setCursor(0, 3);
  lcd.print("["); 
  lcd.write(byte(5));
  lcd.print("GRABAR]");
}
void LineaInfo(){
  lcd.setCursor(0, 3);
  lcd.print("                    ");
  lcd.setCursor(0, 3);
  lcd.print("["); 
  lcd.write(byte(5));
  lcd.print("GRABAR]");
  lcd.setCursor(11, 3); 
  lcd.print("["); 
  lcd.write(byte(4));
  lcd.print("CAMBIA]");
}
int PantallaInformacion(String Mensaje){
  int Exit = 0;
  lcd.clear();
  lcd.setCursor(0, 0); 
  lcd.print(VERSION);
  lcd.setCursor(0, 1); 
  lcd.print(Mensaje);
  LineaOK();
  while(Exit==0){
    if (PantallaControlarGrabar()==1){
      Exit=1;
    }
  }
  lcd.clear();
}
int PantallaSINO(String Pregunta,int ValorActual,int AdrEEPROM){
  int Exit = 0;
  lcd.clear();
  lcd.setCursor(0, 0); 
  lcd.print(VERSION);
  lcd.setCursor(0, 1); 
  lcd.print(Pregunta);
  int ValorPantalla=-9; //para forzar el primer pintado
  LineaInfo();
  while(Exit==0){
    ValorActual = ValorActual+PantallaControlaPalancaMasMenos();
    if(ValorActual>1){ValorActual=1;}
    if(ValorActual<0){ValorActual=0;}
    if(ValorPantalla!=ValorActual){
      ValorPantalla = ValorActual;
      lcd.setCursor(8, 2); 
      if(ValorActual==0){
        lcd.print("[NO]"); 
      }else{
        lcd.print("[SI]"); 
      }
    }
    if (PantallaControlarGrabar()==1){
      if(AdrEEPROM>=0){GuardarEEPROM(AdrEEPROM,ValorActual);}
      Exit=1;
    }
  }
  lcd.clear();
  return ValorActual;
}
float PantallaValorFloat(String Pregunta,float ValorActual,int Range,int Precission,float Steep,float Min, float Max,String Unidades, int AdrEEPROM){
  int Exit = 0;
  float OldValue = -1;
  lcd.clear();
  lcd.setCursor(0, 0); 
  lcd.print(VERSION);
  lcd.setCursor(0, 1); 
  lcd.print(Pregunta);
  LineaInfo();
  while (Exit==0){
    ValorActual = ValorActual+(PantallaControlaPalancaMasMenos()*Steep);
    if(ValorActual>Max){ValorActual=Max;}
    if(ValorActual<Min){ValorActual=Min;}    
    if (OldValue!=ValorActual){
      lcd.setCursor(7, 2); 
      lcd.print("            ");
      lcd.setCursor(7, 2); 
      lcd.print("[");
      lcd.print(ValorActual);
      lcd.print("]");
      lcd.print(Unidades);
      OldValue = ValorActual;
    }
    if (PantallaControlarGrabar()==1){
      if(AdrEEPROM>=0){GuardarEEPROM(AdrEEPROM,ValorActual);}
      Exit=1;
    }
  }
  lcd.clear();
  return ValorActual;
}

int PantallaValorInt(String Pregunta,int ValorActual,int Range,int Steep,int Min, int Max,String Unidades,int AdrEEPROM){
  int Exit = 0;
  int OldValue = -1;
  lcd.clear();
  lcd.setCursor(0, 0); 
  lcd.print(VERSION);
  lcd.setCursor(0, 1); 
  lcd.print(Pregunta);
  LineaInfo();
  while (Exit==0){
    ValorActual = ValorActual+(PantallaControlaPalancaMasMenos()*Steep);
    if(ValorActual>Max){ValorActual=Max;}
    if(ValorActual<Min){ValorActual=Min;}
    if (OldValue!=ValorActual){
      lcd.setCursor(7, 2); 
      lcd.print("            ");
      lcd.setCursor(7, 2); 
      lcd.print("[");
      lcd.print(ValorActual);
      lcd.print("]");
      lcd.print(Unidades);
      OldValue = ValorActual;
    }
    if (PantallaControlarGrabar()==1){
      if(AdrEEPROM>=0){GuardarEEPROM(AdrEEPROM,ValorActual);}
      Exit=1;
    }
  }
  lcd.clear();
  return ValorActual;
}

void PantallaConfigurar(){
      Puntos = PantallaValorInt("Puntos de apertura",Puntos,2,1,1,99," puntos",1006);
      NumeroTramos = PantallaValorInt("Num palancas mando",NumeroTramos,2,1,1,9," palancas",1008);
      PrecisionSistema = 100;
      GuardarEEPROM(1002,1);//graba que ya estÃ¡ configurada
      delay(200);
      lcd.clear();
}
void PantallaConsignar(){
  ConfiguracionVelocidad1 = PantallaValorInt("Velocidad 1 tabla",ConfiguracionVelocidad1,2,1,1,10," Km/h",1032);
  ConfiguracionPuntos1 = PantallaValorInt("Puntos 1 tabla",ConfiguracionPuntos1,2,1,1,99," puntos",1034);
  ConfiguracionVelocidad2 = PantallaValorInt("Velocidad 2 tabla",ConfiguracionVelocidad2,2,1,1,10," Km/h",1036);
  ConfiguracionPuntos2 = PantallaValorInt("Puntos 2 tabla",ConfiguracionPuntos2,2,1,1,99," puntos",1038);
}
void PantallaDosis(){
    DosisDeseada = PantallaValorInt("Dosis deseada",DosisDeseada,4,50,0,2000," Kg/Ha",1030);
    ConfiguracionDosis = DosisDeseada;
}
void PantallaPrescripcion(){
    if(GPSConectado==1){
      if(PermitirAutodosisCerea==1){
          PermitirAutodosisCerea = 0;
          GuardarEEPROM(1044,PermitirAutodosisCerea);
      }
      PantallaInformacion("Solo con Cerea      ");
    }else{
      PermitirAutodosisCerea = PantallaSINO("Activar prescripcion",PermitirAutodosisCerea,1044);
    }
}
void PantallaCargarPerfil(int perfil){
  if(PantallaSINO("Cargar perfil? " + perfil,0,0)==1){
    int AdrBase = 1000 + (perfil*200);
    byte b;
    for(int p=AdrBase;p<AdrBase+200;p++){
      b = EEPROM.read(p);
      EEPROM.write(p,b);
    }
    CargarConfiguraciones();
  }
}
void PantallaGrabarPerfil(int perfil){
  
}
void PantallaCalibrar(){
      //antes de nada pregunta que no se acerque nadie que la tajadera se mueve sola
      lcd.clear();
      lcd.setCursor(0, 0); 
      if(PantallaSINO("Ha leido el manual?",0,0)==1){
        lcd.clear();
        lcd.setCursor(0, 0); 
        lcd.print(VERSION);
        lcd.setCursor(0, 3);
        lcd.print("Menu para continuar");
        //-----------------------------------------------------------------------
        //AJUSTE MAXIMO
        //-----------------------------------------------------------------------
        int BotonMenu = LOW; 
        String strAccion = "";

        LaststrAccion = "@CEREA;0;0;0;0;0;0;0;END";
        Serial2.println(LaststrAccion);
        
        lcd.setCursor(0, 1);
        lcd.print("Actuador 1 abierto");
        BotonMenu = LOW;
        while(BotonMenu==LOW){
            BotonPresionUp = !digitalRead(PinPresionUp);
            BotonPresionDown = !digitalRead(PinPresionDown);
            if(BotonPresionUp==HIGH){
                strAccion = "@CEREA;0;0;0;0;1;0;0;END";
            }else if(BotonPresionDown==HIGH){
                strAccion = "@CEREA;0;0;0;1;0;0;0;END";
            }else{
                strAccion = "@CEREA;0;0;0;0;0;0;0;END";
            }
            delay(10);
            if(LaststrAccion != strAccion){ Serial2.println(strAccion);}
            LaststrAccion = strAccion;
            BotonMenu = !digitalRead(PinMenu);
            while(!digitalRead(PinMenu)==HIGH){
              LecturaPuertosSerie();
            }
            LecturaPuertosSerie();
        }
        LaststrAccion = "@CEREA;0;0;0;0;0;0;0;END";
        Serial2.println(LaststrAccion);
        Actuador1Cerrado = PasosBruto1;
        GuardarEEPROM(1020,Actuador1Cerrado);
        Wait(500);
        lcd.setCursor(0, 1);
        lcd.print("Actuador 2 abierto");
        BotonMenu = LOW; 
        while(BotonMenu==LOW){
            BotonPresionUp = !digitalRead(PinPresionUp);
            BotonPresionDown = !digitalRead(PinPresionDown);
            if(BotonPresionUp==HIGH){
                strAccion = "@CEREA;0;0;0;0;0;0;1;END";
            }else if(BotonPresionDown==HIGH){
                strAccion = "@CEREA;0;0;0;0;0;1;0;END";
            }else{
                strAccion = "@CEREA;0;0;0;0;0;0;0;END";
            }
            delay(10);
            if(LaststrAccion != strAccion){ Serial2.println(strAccion);}
            LaststrAccion = strAccion;
            BotonMenu = !digitalRead(PinMenu);
            while(!digitalRead(PinMenu)==HIGH){
              LecturaPuertosSerie();
            }
            LecturaPuertosSerie();
        }
        LaststrAccion = "@CEREA;0;0;0;0;0;0;0;END";
        Serial2.println(LaststrAccion);
        Actuador2Cerrado = PasosBruto2;
        GuardarEEPROM(1022,Actuador2Cerrado);
        Wait(500);

        lcd.setCursor(0, 1);
        lcd.print("Finalizado          ");
                
        //-----------------------------------------------------------------------
        //AJUSTE MINIMO
        //-----------------------------------------------------------------------
        lcd.setCursor(0, 2);
        lcd.print("Actuador 1 cerrado");
        BotonMenu = LOW;
        while(BotonMenu==LOW){
            BotonPresionUp = !digitalRead(PinPresionUp);
            BotonPresionDown = !digitalRead(PinPresionDown);
            if(BotonPresionUp==HIGH){
                strAccion = "@CEREA;0;0;0;0;1;0;0;END";
            }else if(BotonPresionDown==HIGH){
                strAccion = "@CEREA;0;0;0;1;0;0;0;END";
            }else{
                strAccion = "@CEREA;0;0;0;0;0;0;0;END";
            }
            if(LaststrAccion != strAccion){ Serial2.println(strAccion);}
            LaststrAccion = strAccion;
            BotonMenu = !digitalRead(PinMenu);
            while(!digitalRead(PinMenu)==HIGH){
              LecturaPuertosSerie();
            }
            LecturaPuertosSerie();
        }
        LaststrAccion = "@CEREA;0;0;0;0;0;0;0;END";
        Serial2.println(LaststrAccion);
        Actuador1Abierto = PasosBruto1;
        GuardarEEPROM(1010,Actuador1Abierto);
        Wait(500);

        lcd.setCursor(0, 2);
        lcd.print("Actuador 2 cerrado");
        BotonMenu = LOW; 
        while(BotonMenu==LOW){
            BotonPresionUp = !digitalRead(PinPresionUp);
            BotonPresionDown = !digitalRead(PinPresionDown);
            if(BotonPresionUp==HIGH){
                strAccion = "@CEREA;0;0;0;0;0;0;1;END";
            }else if(BotonPresionDown==HIGH){
                strAccion = "@CEREA;0;0;0;0;0;1;0;END";
            }else{
                strAccion = "@CEREA;0;0;0;0;0;0;0;END";
            }
            if(LaststrAccion != strAccion){ Serial2.println(strAccion);}
            LaststrAccion = strAccion;
            BotonMenu = !digitalRead(PinMenu);
            while(!digitalRead(PinMenu)==HIGH){
              LecturaPuertosSerie();
            }
            LecturaPuertosSerie();
        }
        LaststrAccion = "@CEREA;0;0;0;0;0;0;0;END";
        Serial2.println(LaststrAccion);
        Actuador2Abierto = PasosBruto2;
        GuardarEEPROM(1012,Actuador2Abierto);
        Wait(500);
        lcd.clear();
        lcd.setCursor(0, 0); 
        lcd.print(VERSION);
        lcd.setCursor(0, 2);
        lcd.print("Reinicie equipo");
                  
        while(1==1){
          LecturaPuertosSerie();
        }
      }  
}

void PintarPantalla(){
    int ValorTajadera1 = 0;
    int ValorTajadera2 = 0;
    int Dif = 0;
    //---------------------|
    //|TODO CERRADO  5Km/h |
    //|DOSIS: 900          |
    //|    21        21    |  
    //|####################|
    //|--------------------|
    //
    //------------------------------------------------------------------------------------
    //PINTAR PANTALLA LINEA 1
    //------------------------------------------------------------------------------------
    lcd.setCursor(0, 0); 
    if(BotonCerradoTotal==HIGH){
      lcd.print("TODO CERRADO");       
    }else if(BotonAutomatico==HIGH){
      lcd.print("CORTE:CEREA ");       
    }else{
      lcd.print("CORTE:MANUAL");       
    }
    if(GPSConectado == 1){
      if(Satelites < SatelitesMin || HDOP > HDOPMin){
        lcd.setCursor(13, 0); 
        lcd.print("      ");
        lcd.setCursor(13, 0); 
        lcd.print("NO FIX");
      }else{
        lcd.setCursor(13, 0); 
        lcd.print("       ");
        lcd.setCursor(13, 0); 
        lcd.print(Velocidad);
        lcd.write(byte(6));
      }
    }else if(DetectadoCEREA == 1){
      lcd.setCursor(13, 0); 
      lcd.print("CEREA  ");
    }else{
      lcd.setCursor(13, 0); 
      lcd.print("       ");
    }
    //---------------------------------------------------------------------------------------------------------------------------------------------------
    //valor de dosis a dispersar
    //---------------------------------------------------------------------------------------------------------------------------------------------------
    if(BotonAutoDosis==HIGH){
      if(DisplayDosisDeseada != DosisDeseada){
        lcd.setCursor(0, 1); 
        lcd.print("                    ");
        if(PermitirAutodosisCerea==1){
          lcd.setCursor(0, 1); 
          lcd.print("                    ");      
          lcd.setCursor(0, 1); 
          lcd.print("PRESCRIPCION:");      
          lcd.print(DosisDeseada);
          lcd.write(byte(6));
        }else{
          lcd.setCursor(0, 1); 
          lcd.print("                    ");      
          lcd.setCursor(0, 1); 
          lcd.print("AUTO:");      
          lcd.print(DosisDeseada);
          lcd.write(byte(6));
        }
      }
      
      ValorTajadera1 = DosisReal1;
      Dif = DosisDeseada-ValorTajadera1;
      if(Dif<0){Dif=Dif*-1;}
      if (Dif<20){ValorTajadera1 = DosisDeseada;}
      
      ValorTajadera2 = DosisReal2;
      Dif = DosisDeseada-ValorTajadera2;
      if(Dif<0){Dif=Dif*-1;}
      if (Dif<20){ValorTajadera2 = DosisDeseada;}
      
    }else{
      if(DisplayDosisReal1!=DosisReal1 || DisplayDosisReal2!=DosisReal2){
        lcd.setCursor(0, 1); 
        lcd.print("                    ");
        lcd.setCursor(0, 1); 
        lcd.print("DOSIS:");      
        lcd.print(DosisReal1);
        lcd.print("/");
        if(ValorTajadera1==ValorTajadera2){
          lcd.print(DosisReal1);
        }else{
          lcd.print(DosisReal2);
        }
        lcd.write(byte(6));
      }

      ValorTajadera1 = PuntosDeseados1;
      if(ValorTajadera1<1){ValorTajadera1=0;}
      if(ValorTajadera1>Puntos){ValorTajadera1=Puntos;}
      
      ValorTajadera2 = PuntosDeseados2;
      if(ValorTajadera2<1){ValorTajadera2=0;}
      if(ValorTajadera2>Puntos){ValorTajadera2=Puntos;}

    }
    //---------------------------------------------------------------------------------------------------------------------------------------------------
    //VALOR INFO DE TAJADERA
    //---------------------------------------------------------------------------------------------------------------------------------------------------
    if(millis()>AlarmaMillisMensaje+2000){ //si la alarma y apaso, ignora el texto
        AlarmaMillisMensaje = 0;
        AlarmaMensaje = "";
        DisplayValor2Tajadera = -1;
        DisplayValor1Tajadera = -1;
        if(DisplayValor1Tajadera!=ValorTajadera1){
          lcd.setCursor(0, 2); 
          lcd.print("          ");
          lcd.setCursor(4, 2); 
          lcd.print(ValorTajadera1);
        }
        if(DisplayValor2Tajadera!=ValorTajadera2){
          lcd.setCursor(10, 2); 
          lcd.print("          ");
          lcd.setCursor(14, 2); 
          lcd.print(ValorTajadera2);
        }
    }
    if(AlarmaMensaje!=""){//si hay alarma, muestrala en la linea de numeros de zonas
        if(millis() > MillisParpadeoDisplayAlarma){
          MillisParpadeoDisplayAlarma = millis()+500;
          EstadoParpadeoAlarma = !EstadoParpadeoAlarma;
        }
        if(EstadoParpadeoAlarma==1){//para que el mensaje parpadee
            if(AlarmaMensaje!=LastAlarmaMensaje){
                lcd.setCursor(0, 2);
                lcd.print(AlarmaMensaje);
                LastAlarmaMensaje = AlarmaMensaje;
                tone(PinZumbador, 440, 1000);
            }
        }else{
          lcd.setCursor(0, 2);
          lcd.print("                    ");
          LastAlarmaMensaje = "";
          DisplayValor2Tajadera = -1;
          DisplayValor1Tajadera = -1;
          if(DisplayValor1Tajadera!=ValorTajadera1){
            lcd.setCursor(0, 2); 
            lcd.print("          ");
            lcd.setCursor(4, 2); 
            lcd.print(ValorTajadera1);
          }
          if(DisplayValor2Tajadera!=ValorTajadera2){
            lcd.setCursor(10, 2); 
            lcd.print("          ");
            lcd.setCursor(14, 2); 
            lcd.print(ValorTajadera2);
          }
        }
    }else{//todo con normalidad, no hay alarma
        if(LastAlarmaMensaje!=""){
          lcd.setCursor(0, 2);
          lcd.print("                    ");
          LastAlarmaMensaje = "";
          DisplayValor2Tajadera = -1;
          DisplayValor1Tajadera = -1;
        }
        if(DisplayValor1Tajadera!=ValorTajadera1){
          lcd.setCursor(0, 2); 
          lcd.print("          ");
          lcd.setCursor(4, 2); 
          lcd.print(ValorTajadera1);
        }
        if(DisplayValor2Tajadera!=ValorTajadera2){
          lcd.setCursor(10, 2); 
          lcd.print("          ");
          lcd.setCursor(14, 2); 
          lcd.print(ValorTajadera2);
        }
    }
    //---------------------------------------------------------------------------------------------------------------------------------------------------
    //MOSTRAR DATOS DE TAJADERA 1
    //---------------------------------------------------------------------------------------------------------------------------------------------------
    int PuntosPinta = 0;
    PuntosPinta = PuntosTajadera1;
    for(int p=0;p<10;p++){
      lcd.setCursor(9-p, 3); 
      if(p<(PuntosPinta*10/Puntos)){
          lcd.write(byte(3));
      }else{
        if(p==0){
            lcd.write(byte(2));
        }else if(p==9){
            lcd.write(byte(0));
        }else{
            lcd.write(byte(1));
        }
      }
    }
    PuntosPinta = PuntosTajadera2;
    for(int p=0;p<10;p++){
      lcd.setCursor(10+p, 3); 
      if(p<(PuntosPinta*10/Puntos)){
          lcd.write(byte(3));
      }else{
        if(p==0){
            lcd.write(byte(0));
        }else if(p==9){
            lcd.write(byte(2));
        }else{
            lcd.write(byte(1));
        }
      }
    }
    //---------------------------------------------------------------------------------------------------------------------------------------------------
    DisplayDosisDeseada = DosisDeseada;
    DisplayDosisReal1 = DosisReal1;
    DisplayDosisReal2 = DosisReal2;
    DisplayValor1Tajadera = ValorTajadera1;
    DisplayValor2Tajadera = ValorTajadera2;
    //---------------------------------------------------------------------------------------------------------------------------------------------------
}
void PantallaTotal(){
  lcd.clear();
  DisplayDosisDeseada = -1;
  DisplayDosisReal1 = -1;
  DisplayDosisReal2 = -1;
  DisplayValor1Tajadera = -1;
  DisplayValor2Tajadera = -1;
  PintarPantalla();
}
void ClearScreen(){
  lcd.clear();
}
void PantallaMenu(String Titulo, String Opcion1, String Opcion2, String Opcion3, String Opcion4, String Opcion5){
  lcd.setCursor(1, 0); 
  lcd.print(Titulo); 
  lcd.setCursor(1, 1); 
  lcd.print(Opcion1); 
  lcd.setCursor(1, 2); 
  lcd.print(Opcion2); 
  lcd.setCursor(11, 1); 
  lcd.print(Opcion3); 
  lcd.setCursor(11, 2); 
  lcd.print(Opcion4); 
  lcd.setCursor(11, 3); 
  lcd.print(Opcion5); 
}

void GestionMenu(int Max){
 //int PalancaAutoPresionPosicion = !digitalRead(PinAutoPresion);
 if(Max==0){Max=4;}
 if(Max>4){Max=4;}
 int Exit = 0;
 int temp = 0;
 MenuPos = 0;
 long MillisFuera = millis()+7000;
 while (Exit==0){
    if(MenuPos==0){MenuPos==1;} 
    int MenuPosOld = MenuPos;
    temp = !digitalRead(PinPresionDown);
    if(temp==HIGH){
      while (temp==HIGH){
        temp = !digitalRead(PinPresionDown);
        LecturaPuertosSerie();
        delay(100);
      }
      MenuPos = MenuPos+1;
      MillisFuera = millis()+7000;
    }
    temp = !digitalRead(PinPresionUp);
    if(temp==HIGH){
      while (temp==HIGH){
        temp = !digitalRead(PinPresionUp);
        LecturaPuertosSerie();
        delay(100);
      }
      MenuPos = MenuPos-1;
      MillisFuera = millis()+7000;
    }
    if(MenuPos<1) MenuPos = 1;
    if(MenuPos>5) MenuPos = 5;
    if(MenuPos>Max && MenuPosOld < MenuPos){
      MenuPos=5;
    }else{
        if(MenuPos>Max && Max<MenuPos && MenuPosOld > MenuPos){MenuPos=Max;}
    }
    if(MenuPos!=MenuPosOld){
          lcd.setCursor(0, 1); 
          lcd.print(" "); 
          lcd.setCursor(0, 2); 
          lcd.print(" "); 
          lcd.setCursor(10, 1); 
          lcd.print(" "); 
          lcd.setCursor(10, 2); 
          lcd.print(" "); 
          lcd.setCursor(10, 3); 
          lcd.print(" "); 
          if (MenuPos>2){
            lcd.setCursor(10,MenuPos-2);
            lcd.write(byte(7));    
          }else{
            lcd.setCursor(0,MenuPos);
            lcd.write(byte(7));    
          }
          delay(50);
    }
    temp = digitalRead(PinMenu);
    if (temp!=HIGH){
      while (temp!=HIGH){
        temp = digitalRead(PinMenu);
        LecturaPuertosSerie();
      }
      Exit=1;
    }
    LecturaPuertosSerie();
    if (millis()>MillisFuera){
      Exit=1;
      PantallaVisor = 0;
      MenuPos=0;
      PantallaTotal();
    }
  }
}
void ControlarMenus(){
  int temp = 0;
  if(PantallaVisor==1){
    ClearScreen();
                         
    PantallaMenu("Active Fertilizer:","Consignar","Dosis","Perfiles","Ajustar","Salir");
    GestionMenu(4);
    if(MenuPos==0){PantallaVisor=0;}
    if(MenuPos==1){PantallaVisor=11;}
    if(MenuPos==2){PantallaVisor=12;}
    if(MenuPos==3){PantallaVisor=13;}
    if(MenuPos==4){PantallaVisor=14;}
    if(MenuPos==5){PantallaVisor=15;}
  }else if(PantallaVisor == 11){//Consignar
    PantallaConsignar();
    PantallaVisor = 1;
  }else if(PantallaVisor == 12){//Dosis
    PantallaDosis();
    PantallaVisor = 1;
  }else if(PantallaVisor == 13){//Perfiles
    ClearScreen();
    PantallaMenu("Gestion perfiles:","Cargar 1","Cargar 2","Cargar 3","Grabar","Salir");
    GestionMenu(4);
    if(MenuPos==0){PantallaVisor=0;}
    if(MenuPos==1){PantallaVisor=131;}
    if(MenuPos==2){PantallaVisor=132;}
    if(MenuPos==3){PantallaVisor=133;}
    if(MenuPos==4){PantallaVisor=134;}
    if(MenuPos==5){PantallaVisor=135;}
  }else if(PantallaVisor == 131){
        delay(100);
        PantallaCargarPerfil(1);
        PantallaVisor = 0;
        PantallaTotal();
  }else if(PantallaVisor == 132){
        delay(100);
        PantallaCargarPerfil(2);
        PantallaVisor = 0;
        PantallaTotal();
  }else if(PantallaVisor == 133){
        delay(100);
        PantallaCargarPerfil(3);
        PantallaVisor = 0;
        PantallaTotal();
  }else if(PantallaVisor == 134){
    ClearScreen();
    PantallaMenu("Grabar perfil:","Memoria 1","Memoria 2","Memoria 3","","Salir");
    GestionMenu(3);
    if(MenuPos==0){PantallaVisor=0;}
    if(MenuPos==1){PantallaVisor=1341;}
    if(MenuPos==2){PantallaVisor=1342;}
    if(MenuPos==3){PantallaVisor=1343;}
    if(MenuPos==4){PantallaVisor=1344;}
    if(MenuPos==5){PantallaVisor=1345;}
  }else if(PantallaVisor == 1341){
      PantallaGrabarPerfil(1);
      PantallaVisor = 0;
      PantallaTotal();
  }else if(PantallaVisor == 1342){
      PantallaGrabarPerfil(2);
      PantallaVisor = 0;
      PantallaTotal();
  }else if(PantallaVisor == 1343){
      PantallaGrabarPerfil(3);
      PantallaVisor = 0;
      PantallaTotal();
  }else if(PantallaVisor == 1345){
      PantallaVisor = 0;
      PantallaTotal();
  }else if(PantallaVisor == 135){
      PantallaVisor=1;
  }else if(PantallaVisor == 14){//ajustar
    ClearScreen();
    PantallaMenu("Ajustes:","Configura","Calibrar","Prescrip.","","Salir");
    GestionMenu(3);
    if(MenuPos==0){PantallaVisor=0;}
    if(MenuPos==1){PantallaVisor=141;}
    if(MenuPos==2){PantallaVisor=142;}
    if(MenuPos==3){PantallaVisor=143;}
    if(MenuPos==4){PantallaVisor=144;}
    if(MenuPos==5){PantallaVisor=145;}
  }else if(PantallaVisor == 141){//salir
      delay(100);
      PantallaConfigurar();
      PantallaVisor=14;
  }else if(PantallaVisor == 142){//salir
      delay(100);
      PantallaCalibrar();
      PantallaVisor=14;
  }else if(PantallaVisor == 143){//salir
      delay(100);
      PantallaPrescripcion();
      PantallaVisor = 0;
      PantallaTotal();
  }else if(PantallaVisor == 144){//salir
      ClearScreen();
      PantallaMenu("BaudRates:","Cerea/GPS","Mando","","","Salir");
      GestionMenu(2);
    if(MenuPos==0){PantallaVisor=0;}
    if(MenuPos==1){PantallaVisor=1441;}
    if(MenuPos==2){PantallaVisor=1442;}
    if(MenuPos==3){PantallaVisor=1443;}
    if(MenuPos==4){PantallaVisor=1444;}
    if(MenuPos==5){PantallaVisor=1445;}
  }else if(PantallaVisor == 1441){//cerea/gps
      ClearScreen();
      PantallaMenu("Cerea/GPS:","9600","19200","57600","115200","Salir");
      GestionMenu(4);
      if(MenuPos==0){PantallaVisor=0;}
      if(MenuPos==1){PantallaVisor=14411;}
      if(MenuPos==2){PantallaVisor=14412;}
      if(MenuPos==3){PantallaVisor=14413;}
      if(MenuPos==4){PantallaVisor=14414;}
      if(MenuPos==5){PantallaVisor=14415;}
  }else if(PantallaVisor == 14411){//9600
      BaudRateCerea = 0;
      GuardarEEPROM(1046,BaudRateCerea);
      Serial3.end();
      ConfigurarSerialCerea();
  }else if(PantallaVisor == 14412){//19200
      BaudRateCerea = 1;
      GuardarEEPROM(1046,BaudRateCerea);
      Serial3.end();
      ConfigurarSerialCerea();
  }else if(PantallaVisor == 14413){//57600
      BaudRateCerea = 2;
      GuardarEEPROM(1046,BaudRateCerea);
      Serial3.end();
      ConfigurarSerialCerea();
  }else if(PantallaVisor == 14414){//115200
      BaudRateCerea = 3;
      GuardarEEPROM(1046,BaudRateCerea);
      Serial3.end();
      ConfigurarSerialCerea();
  }else if(PantallaVisor == 14415){//salir
          PantallaVisor = 144;
  }else if(PantallaVisor == 1442){//reles
      ClearScreen();
      PantallaMenu("Mando:","9600","19200","57600","115200","Salir");
      GestionMenu(4);
      if(MenuPos==0){PantallaVisor=0;}
      if(MenuPos==1){PantallaVisor=14421;}
      if(MenuPos==2){PantallaVisor=14422;}
      if(MenuPos==3){PantallaVisor=14423;}
      if(MenuPos==4){PantallaVisor=14424;}
      if(MenuPos==5){PantallaVisor=14425;}
  }else if(PantallaVisor == 14421){//9600
      BaudRateReles = 0;
      GuardarEEPROM(1048,BaudRateReles);
      Serial2.println("BAUD;0;END");
      Serial2.flush();
      delay(100);
      Serial2.end();
      Serial2.begin(9600);
  }else if(PantallaVisor == 14422){//19200
      BaudRateReles = 1;
      GuardarEEPROM(1048,BaudRateReles);
      Serial2.println("BAUD;1;END");
      Serial2.flush();
      delay(100);
      Serial2.end();
      Serial2.begin(19200);
  }else if(PantallaVisor == 14423){//57600
      BaudRateReles = 2;
      GuardarEEPROM(1048,BaudRateReles);
      Serial2.println("BAUD;2;END");
      Serial2.flush();
      delay(100);
      Serial2.end();
      Serial2.begin(57600);
  }else if(PantallaVisor == 14424){//115200
      BaudRateReles = 3;
      GuardarEEPROM(1048,BaudRateReles);
      Serial2.println("BAUD;3;END");
      Serial2.flush();
      delay(100);
      Serial2.end();
      Serial2.begin(115200);
  }else if(PantallaVisor == 14425){//salir
          PantallaVisor = 144;
  }else if(PantallaVisor == 1445){//salir
          PantallaVisor = 14;
  }else if(PantallaVisor == 145){//salir
        PantallaVisor = 1;
  }else if(PantallaVisor == 15){//salir
        PantallaVisor = 0;
        PantallaTotal();
  }
}
void PantallaPirata(){
    ClearScreen();
    lcd.setCursor(0, 0); 
    lcd.print("SISTEMA BLOQUEADO   "); 
    lcd.setCursor(0, 1); 
    lcd.print("Se ha detectado una "); 
    lcd.setCursor(0, 2); 
    lcd.print("manipulación del    "); 
    lcd.setCursor(0, 3); 
    lcd.print("programa.           "); 
}
void ControlarPirateoSoftware(){
  String a = "";
  String b = "";
  String c = "";
  String d = "";
  String e = "";
  a=DesarrolladoPor1.substring(17,19);
  b=DesarrolladoPor1.substring(20,22);
  c=DesarrolladoPor1.substring(26,28);
  d=DesarrolladoPor2.substring(0,3);
  e=DesarrolladoPor2.substring(10,12);
  if(a!="Ja" || b!="ie" || c!="au"  || d!="jfr" || e!="oi"){    //PIRATAAAAAA!!!!!!
        PantallaPirata();
        while (1 == 1){                                         //BLUCLE INFINITO DE BLOQUEO, ASI BLOQUEAMOS LA CAJA
        }
  }
}
