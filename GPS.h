TinyGPS gps;

int GPSConectado = 0;
int Satelites = 0;           //numero de satelites disponibles
double HDOP = 99;            //de 0 a 100 calidad de conexion
int SatelitesMin = 6;
double HDOPMin = 1.4;
double VelocidadMinima = 1;
double VelocidadMaxima = 200;

// Frecuencias de refresco
const unsigned char ubxRate1Hz[] PROGMEM =  { 0x06,0x08,0x06,0x00,0xE8,0x03,0x01,0x00,0x01,0x00 };
const unsigned char ubxRate5Hz[] PROGMEM =  { 0x06,0x08,0x06,0x00,0xC8,0x00,0x01,0x00,0x01,0x00 };
const unsigned char ubxRate10Hz[] PROGMEM = { 0x06,0x08,0x06,0x00,0x64,0x00,0x01,0x00,0x01,0x00 };

// Desactivar sentencias NMEA https://www.gpsinformation.org/dale/nmea.htm#nmea para mas explicaciones
const unsigned char ubxDisableGGA[] PROGMEM = { 0x06,0x01,0x08,0x00,0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x01 }; //essential fix data which provide 3D location and accuracy data
const unsigned char ubxDisableGLL[] PROGMEM = { 0x06,0x01,0x08,0x00,0xF0,0x01,0x00,0x00,0x00,0x00,0x00,0x01 }; //Geographic Latitude and Longitude is a holdover from Loran data and some old units may not send the time and data active information if they are emulating Loran data
const unsigned char ubxDisableGSA[] PROGMEM = { 0x06,0x01,0x08,0x00,0xF0,0x02,0x00,0x00,0x00,0x00,0x00,0x01 }; //GPS DOP and active satellites. This sentence provides details on the nature of the fix. It includes the numbers of the satellites being used in the current solution and the DOP
const unsigned char ubxDisableGSV[] PROGMEM = { 0x06,0x01,0x08,0x00,0xF0,0x03,0x00,0x00,0x00,0x00,0x00,0x01 }; //Satellites in View shows data about the satellites that the unit might be able to find based on its viewing mask and almanac data
const unsigned char ubxDisableRMC[] PROGMEM = { 0x06,0x01,0x08,0x00,0xF0,0x04,0x00,0x00,0x00,0x00,0x00,0x01 }; //NMEA has its own version of essential gps pvt (position, velocity, time) data. It is called RMC, The Recommended Minimum
const unsigned char ubxDisableVTG[] PROGMEM = { 0x06,0x01,0x08,0x00,0xF0,0x05,0x00,0x00,0x00,0x00,0x00,0x01 }; //Velocity made good. The gps receiver may use the LC prefix instead of GP if it is emulating Loran output.
const unsigned char ubxDisableZDA[] PROGMEM = { 0x06,0x01,0x08,0x00,0xF0,0x08,0x00,0x00,0x00,0x00,0x00,0x01 }; //Data and Time

// Establecer Baudios del puerto GPS
const unsigned char ubxSet57600[] PROGMEM =  { 0x06, 0x00, 0x14, 0x00, 0x01, 0x00, 0x00, 0x00, 0xD0, 0x08, 0x00, 0x00, 0x00, 0xE1, 0x00, 0x00, 0x07, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00 };
const unsigned char ubxSet38400[] PROGMEM =  { 0x06, 0x00, 0x14, 0x00, 0x01, 0x00, 0x00, 0x00, 0xD0, 0x08, 0x00, 0x00, 0x00, 0x96, 0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00 };
const unsigned char ubxSet115200[] PROGMEM = { 0x06, 0x00, 0x14, 0x00, 0x01, 0x00, 0x00, 0x00, 0xd0, 0x08, 0x00, 0x00, 0xc2, 0x01, 0x08, 0x00, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc4, 0x96, 0xb5, 0x62, 0x06, 0x00, 0x01, 0x00, 0x01 };

void sendUBX( const unsigned char *progmemBytes, size_t len )
{
  Serial3.write( 0xB5 ); // SYNC1
  Serial3.write( 0x62 ); // SYNC2
  uint8_t a = 0, b = 0;
  while (len-- > 0) {
    uint8_t c = pgm_read_byte( progmemBytes++ );
    a += c;
    b += a;
    Serial3.write( c );
  }
  Serial3.write( a ); // CHECKSUM A
  Serial3.write( b ); // CHECKSUM B
}

void ConfigurarGPS(){
  //SOLO SE NECESITAN TRAMAS RMC Y GGA, EL RESTO LAS DESACTIVO    
  //sendUBX( ubxDisableGGA, sizeof(ubxDisableGGA));   
  sendUBX( ubxDisableGLL, sizeof(ubxDisableGLL));   
  sendUBX( ubxDisableGSA, sizeof(ubxDisableGSA));   
  sendUBX( ubxDisableGSV, sizeof(ubxDisableGSV));   
  //sendUBX( ubxDisableRMC, sizeof(ubxDisableRMC));  
  sendUBX( ubxDisableVTG, sizeof(ubxDisableVTG));  
  sendUBX( ubxDisableZDA, sizeof(ubxDisableZDA));   
  sendUBX( ubxRate10Hz, sizeof(ubxRate10Hz));       
  sendUBX( ubxSet57600, sizeof(ubxSet57600));       
  Serial3.flush();
  Serial3.end();
  delay(100);
  Serial3.begin(57600);    
  GPSConectado = 1;     
}
