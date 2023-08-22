void LecturaEstadoPalancas(){
    BotonAutomatico = digitalRead(PinBotonAutoMan);
    BotonCerradoTotal = !digitalRead(PinCerradoTotal);
    
    //solo escucha las palancas de presion 4 veces por segundo
    if(millis()>(TimeBotones+50)){
      BotonPresionUp = !digitalRead(PinPresionUp);
      BotonPresionDown = !digitalRead(PinPresionDown);
      TimeBotones = millis();
    }else{
      BotonPresionUp = LOW;    
      BotonPresionDown = LOW;
    }
    BotonAutoDosis = !digitalRead(PinAutoDosis);
    if(LastBotonAutoDosis!=BotonAutoDosis){
      PantallaTotal();
    }
    LastBotonAutoDosis = BotonAutoDosis;

    if(BotonAutoDosis==HIGH){
        if(PermitirAutodosisCerea==HIGH){
            //no se modifica la dosis, esta en autododis por cerea
        }else{
          if(BotonPresionDown==HIGH){
            DosisDeseada = DosisDeseada-20;
          }else if(BotonPresionUp==HIGH){
            DosisDeseada = DosisDeseada+20;
          }
        }  
    }else{
        if(BotonPresionUp == HIGH && PuntosTajadera1 >= Puntos && PuntosTajadera2 >= Puntos){BotonPresionUp = LOW;}
        if(BotonPresionDown == HIGH && PuntosTajadera1 <= 0 && PuntosTajadera2 <= 0){BotonPresionDown = LOW;}
    }
    
    if(LastBotonAutomatico!=BotonAutomatico){
      ComunicarCereaVuelveAuto();
      LastBotonAutomatico=BotonAutomatico;
      PantallaTotal();
    }
    
    if(NumeroTramos==1){
      MtrTramosPalancas[0] = !digitalRead(PinBotonZona1);
      MtrTramosPalancas[1] = !digitalRead(PinBotonZona2);
    }else if(NumeroTramos==3){
      MtrTramosPalancas[0] = !digitalRead(PinBotonZona4);
      MtrTramosPalancas[1] = !digitalRead(PinBotonZona6);
    }else if(NumeroTramos==4){
      MtrTramosPalancas[0] = !digitalRead(PinBotonZona1);
      MtrTramosPalancas[1] = !digitalRead(PinBotonZona4);
    }else if(NumeroTramos==5){
      MtrTramosPalancas[0] = !digitalRead(PinBotonZona3);
      MtrTramosPalancas[1] = !digitalRead(PinBotonZona7);
    }else if(NumeroTramos==6){
      MtrTramosPalancas[0] = !digitalRead(PinBotonZona1);
      MtrTramosPalancas[1] = !digitalRead(PinBotonZona6);
    }else if(NumeroTramos==7){
      MtrTramosPalancas[0] = !digitalRead(PinBotonZona2);
      MtrTramosPalancas[1] = !digitalRead(PinBotonZona8);
    }else if(NumeroTramos==8){
      MtrTramosPalancas[0] = !digitalRead(PinBotonZona1);
      MtrTramosPalancas[1] = !digitalRead(PinBotonZona8);
    }else if(NumeroTramos==9){
      MtrTramosPalancas[0] = !digitalRead(PinBotonZona1);
      MtrTramosPalancas[1] = !digitalRead(PinBotonZona9);
    }
    MtrTramosPalancas[2] = 0;    
    //------------------------------------------------------------------------------------
    //ESTABLECIENDO POSICION DE LEDS
    //------------------------------------------------------------------------------------
    digitalWrite(PinLedAuto,!BotonAutomatico);
    digitalWrite(PinLedCerradoTotal,BotonCerradoTotal);
    digitalWrite(PinLedAutoDosis,!BotonAutoDosis);
    digitalWrite(PinLedMenu,!BotonMenu);
}
void ControlarPalancas(){
    if(MtrTramosPalancasAnterior[0]==HIGH && MtrTramosPalancas[0]==LOW){
      MtrTramosCerea[1]=1;
    }else if(MtrTramosPalancasAnterior[1]==HIGH && MtrTramosPalancas[1]==LOW){
      MtrTramosCerea[2]=1;
    }
    MtrTramosPalancasAnterior[0]=MtrTramosPalancas[0];
    MtrTramosPalancasAnterior[1]=MtrTramosPalancas[1];
    //------------------------------------------------------------------------------------
    //INTEGRACION DE PALANCAS DE MANDO DE EMPLEADO Y CEREA
    //------------------------------------------------------------------------------------
    if(BotonCerradoTotal==LOW || (BotonAutoDosis==HIGH && Velocidad < 1)){//SI TIENE EL GENERAL, O LA VELOCIDAD ES POR DEBAJO DE 1KM/H Y ESTA EN AUTODOSIS
        if(BotonAutomatico==HIGH){
            //CONTROLAMOS NO SEA QUE CEREA DIGA DE CERRAR
            if(MtrTramosCerea[1]==HIGH){
              if(MtrTramosPalancas[0]==HIGH){
                PuntosDeseados1 = 0;
                MtrTramosReal[0]=LOW;
              }else{
                PuntosDeseados1 = PuntosAplicados;
                MtrTramosReal[0]=HIGH;
              }
            }else{
              PuntosDeseados1=0;
              MtrTramosReal[0]=LOW;
            }
            //CONTROLAMOS NO SEA QUE CEREA DIGA DE CERRAR
            if(MtrTramosCerea[2]==HIGH){
              if(MtrTramosPalancas[1]==HIGH){
                PuntosDeseados2 = 0;
                MtrTramosReal[1]=LOW;
              }else{
                PuntosDeseados2 = PuntosAplicados;
                MtrTramosReal[1]=HIGH;
              }
            }else{
              PuntosDeseados2=0;
              MtrTramosReal[1]=LOW;
            }
        }else{
          if(MtrTramosPalancas[0]==LOW){
              PuntosDeseados1=PuntosAplicados;
              MtrTramosReal[0]=HIGH;
          }else{
            PuntosDeseados1=0;
            MtrTramosReal[0]=LOW;
          }          
          if(MtrTramosPalancas[1]==LOW){
              PuntosDeseados2=PuntosAplicados;
              MtrTramosReal[1]=HIGH;
          }else{
            PuntosDeseados2=0;
            MtrTramosReal[1]=LOW;
          }          
        }
    }else{
      PuntosDeseados1=0;
      PuntosDeseados2=0;
      MtrTramosReal[0]=LOW;
      MtrTramosReal[1]=LOW;
    }
    ComunicarZONASaCEREA();    
}
void ControlarBotonMenu(){
    BotonMenu = !digitalRead(PinMenu);
    if(BotonMenu==HIGH){
      delay(100);
      while (BotonMenu==HIGH){
          BotonMenu = !digitalRead(PinMenu);
          LecturaPuertosSerie();
      }      
      PantallaVisor = 1;
    }
}

