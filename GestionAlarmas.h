void ControlarAlarmas(){
  //las alarmas mas importantes al final de la rutina,de tal forma que siempre se mostrara la mas importante
  if(AlarmaMillisMensaje==0){
    int AlgunaAbierta = 0;
    if(MtrTramosReal[0]==HIGH || MtrTramosReal[1] == HIGH){AlgunaAbierta = 1;}
    if(BotonAutoDosis==HIGH){
      if(DetectadoGPS || DetectadoCEREA){
        if(Velocidad < 2){
          AlarmaMensaje = F("POCA VELOCIDAD      ");
          AlarmaMillisMensaje = millis();
        }
      }
      if(AlgunaAbierta == 0){//no hay zonas abiertas, queda en standby
          AlarmaMensaje = F("TODAS ZONAS CERRADAS");
          AlarmaMillisMensaje = millis();
      }
    }
    if(DetectadoGPS || DetectadoCEREA){
      if(PuntosTajadera1 >= Puntos || PuntosTajadera2 >= Puntos){
            AlarmaMensaje = "DEMASIADA VELOCIDAD ";
            AlarmaMillisMensaje = millis();
      }
    }
    if(BotonAutomatico!=0 && DetectadoCEREA == 0 && DetectadoGPS == 0){
          AlarmaMensaje = "SIN DATOS VELOCIDAD ";
          AlarmaMillisMensaje = millis();      
    }    
    if(DetectadoCEREA!=0){
      if((TimeOutCerea+2000) < millis()){
          AlarmaMensaje = "SIN CONEXION CEREA  ";
          AlarmaMillisMensaje = millis();
      }
    }
    if((TimeOutMando+4000) < millis()){
        AlarmaMensaje = "SIN CONEXION RELES  ";
        AlarmaMillisMensaje = millis();
    } 
  }
}
