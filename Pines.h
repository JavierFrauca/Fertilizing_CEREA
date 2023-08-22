void ConfigurarPines(){
      pinMode(PinLedAuto,OUTPUT);
    pinMode(PinLedAutoDosis,OUTPUT);
    pinMode(PinLedCerradoTotal,OUTPUT);
    pinMode(PinLedMenu,OUTPUT);      
    pinMode(PinZumbador,OUTPUT);
    
    pinMode(PinMenu, INPUT_PULLUP); 
    pinMode(PinBotonAutoMan, INPUT_PULLUP); 
    pinMode(PinPresionUp, INPUT_PULLUP); 
    pinMode(PinPresionDown, INPUT_PULLUP); 
    pinMode(PinCerradoTotal, INPUT_PULLUP); 
    pinMode(PinAutoDosis, INPUT_PULLUP);
    
    pinMode(PinBotonZona1, INPUT); 
    pinMode(PinBotonZona2, INPUT); 
    pinMode(PinBotonZona3, INPUT); 
    pinMode(PinBotonZona4, INPUT); 
    pinMode(PinBotonZona5, INPUT); 
    pinMode(PinBotonZona6, INPUT); 
    pinMode(PinBotonZona7, INPUT); 
    pinMode(PinBotonZona8, INPUT); 
    pinMode(PinBotonZona9, INPUT); 
    
    digitalWrite(PinBotonZona1, HIGH); 
    digitalWrite(PinBotonZona2, HIGH); 
    digitalWrite(PinBotonZona3, HIGH); 
    digitalWrite(PinBotonZona4, HIGH); 
    digitalWrite(PinBotonZona5, HIGH); 
    digitalWrite(PinBotonZona6, HIGH); 
    digitalWrite(PinBotonZona7, HIGH); 
    digitalWrite(PinBotonZona8, HIGH); 
    digitalWrite(PinBotonZona9, HIGH); 
      
    digitalWrite(PinLedMenu,HIGH);
    digitalWrite(PinLedAuto,HIGH);
    digitalWrite(PinLedCerradoTotal,HIGH);
    digitalWrite(PinLedAutoDosis,LOW);

}


