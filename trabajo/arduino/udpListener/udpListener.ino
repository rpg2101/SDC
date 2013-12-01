#include <EtherCard.h>
#include <IPAddress.h>
#include <dht.h>

dht DHT;
#define DHT11_PIN 2

#define STATIC 1  // set to 1 to disable DHCP (adjust myip/gwip values below)
#if STATIC
// ethernet interface ip address
static byte myip[] = { 192,168,1,200 };
// gateway ip address
static byte gwip[] = { 192,168,1,1 };
#endif

int online = 0;

// ethernet mac address - must be unique on your network
static byte mymac[] = { 0x70,0x69,0x69,0x2D,0x30,0x31 };

byte Ethernet::buffer[500]; // tcp/ip send and receive buffer

//callback that prints received packets to the serial port
void udpDato(word port, byte ip[4], const char *data, word len) {
  Serial.println ("recibi 1050");
  //if(!online){
  IPAddress src(ip[0], ip[1], ip[2], ip[3]);
  Serial.println(src);
  Serial.println(port);
  Serial.println(data);
  Serial.println(len);
 
  
  Serial.print("DHT11, \t");
  int chk = DHT.read11(DHT11_PIN);
  switch (chk)
  {
    case DHTLIB_OK:  
                Serial.print("OK,\t"); 
                break;
    case DHTLIB_ERROR_CHECKSUM: 
                Serial.print("Checksum error,\t"); 
                break;
    case DHTLIB_ERROR_TIMEOUT: 
                Serial.print("Time out error,\t"); 
                break;
    default: 
                Serial.print("Unknown error,\t"); 
                break;
  }
  Serial.print(DHT.humidity,1);
  Serial.print(",\t");
  Serial.println(DHT.temperature,1);
 
  char  cadena [4]; 
  char  stringtmp [7];
  
  dtostrf(DHT.humidity, 3, 1, cadena);
  strcpy (stringtmp,"1:");
  strcat (stringtmp,cadena);
  ether.sendUdp(stringtmp,sizeof(stringtmp),1051,gwip,1051);
  
  dtostrf(DHT.temperature , 3, 1, cadena);
  strcpy (stringtmp,"2:");
  strcat (stringtmp,cadena);
  ether.sendUdp(stringtmp,sizeof(stringtmp),1051,gwip,1051);
}

void udpOnline(word port, byte ip[4], const char *data, word len) {
  Serial.println ("recibi 1051"); 
   
  if (!strcmp(data,"BEACON")){
   Serial.println ("recibi senal servidor activo");
   online = 1; 
   ether.sendUdp("HELLO",sizeof("HELLO"),1051,gwip,1051);
  }
  if (!strcmp(data,"ACK")){
    Serial.println ("servidor registro dispositivo con exito");
    online = 1;
  }
}
  
void setup(){
  Serial.begin(115200);
  Serial.println("\n[backSoon]");

  if (ether.begin(sizeof Ethernet::buffer, mymac,53) == 0)
    Serial.println( "Failed to access Ethernet controller");
#if STATIC
  ether.staticSetup(myip, gwip);
#else
  if (!ether.dhcpSetup())
    Serial.println("DHCP failed");
#endif

  ether.printIp("IP:  ", ether.myip);
  ether.printIp("GW:  ", ether.gwip);
  ether.printIp("DNS: ", ether.dnsip);

  //register udpSerialPrint() to port 1337
  //ether.udpServerListenOnPort(&udpOnline, 1050);

  //register udpSerialPrint() to port 42.
  ether.udpServerListenOnPort(&udpDato, 1050);
}

void loop(){
  //this must be called for ethercard functions to work.
  ether.packetLoop(ether.packetReceive());
}

