#ifdef USES_P220
//#######################################################################################################
//#################################### Plugin 220: Mercury230 #######################################
//#######################################################################################################

#define PLUGIN_220
#define PLUGIN_ID_220         220
#define PLUGIN_NAME_220       "Mercury 230"
#define PLUGIN_VALUENAME1_220 "Merc_data_json"
#define PLUGIN_VALUENAME2_220 "Merc_stat_json"
#include <ESPeasySoftwareSerial.h>
#define SerialControl 5   // RS485 Direction control
#define RS485Transmit    HIGH
#define RS485Receive     LOW

byte testConnect[] = { 0x00, 0x00 };
byte Access[]      = { 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01};
byte Sn[]          = { 0x00, 0x08, 0x00 }; // серийный номер
byte Freq[]        = { 0x00, 0x08, 0x16, 0x40 }; // частота
byte Current[]     = { 0x00, 0x08, 0x16, 0x21 };//  ток
byte Suply[]       = { 0x00, 0x08, 0x16, 0x11 }; // напряжение
byte Power[]       = { 0x00, 0x08, 0x16, 0x00 };// мощность p

byte PowerQ[]       = { 0x00, 0x08, 0x16, 0x08 };// мощность Q
byte PowerS[]       = { 0x00, 0x08, 0x16, 0x04 };// мощность S

byte CosF[]       = { 0x00, 0x08, 0x16, 0x30 };// cosf


byte Angle[]       = { 0x00, 0x08, 0x16, 0x51 }; // углы
byte energyT0[]  =   { 0x00, 0x05, 0x00, 0x00 };///  суммарная энергия прямая + обратная + активная + реактивная

byte energyT1[]  =   { 0x00, 0x05, 0x00, 0x01 };///  суммарная энергия прямая + обратная + активная + реактивная
byte energyT2[]  =   { 0x00, 0x05, 0x00, 0x02 };///  суммарная энергия прямая + обратная + активная + реактивная
byte energyT3[]  =   { 0x00, 0x05, 0x00, 0x03 };///  суммарная энергия прямая + обратная + активная + реактивная
byte energyT4[]  =   { 0x00, 0x05, 0x00, 0x04 };///  суммарная энергия прямая + обратная + активная + реактивная

byte energyM1T1[] = { 0x00, 0x05, 0x31 ,0x01 };
byte energyM1T2[] = { 0x00, 0x05 ,0x31, 0x02 };
byte energyM2T1[] = { 0x00, 0x05, 0x32 ,0x01 };
byte energyM2T2[] = { 0x00, 0x05 ,0x32, 0x02 };
byte energyM3T1[] = { 0x00, 0x05, 0x33 ,0x01 };
byte energyM3T2[] = { 0x00, 0x05 ,0x33, 0x02 };
byte energyM4T1[] = { 0x00, 0x05, 0x34 ,0x01 };
byte energyM4T2[] = { 0x00, 0x05 ,0x34, 0x02 };
byte energyM5T1[] = { 0x00, 0x05, 0x35 ,0x01 };
byte energyM5T2[] = { 0x00, 0x05 ,0x35, 0x02 };
byte energyM6T1[] = { 0x00, 0x05, 0x36 ,0x01 };
byte energyM6T2[] = { 0x00, 0x05 ,0x36, 0x02 };
byte energyM7T1[] = { 0x00, 0x05, 0x37 ,0x01 };
byte energyM7T2[] = { 0x00, 0x05 ,0x37, 0x02 };
byte energyM8T1[] = { 0x00, 0x05, 0x38 ,0x01 };
byte energyM8T2[] = { 0x00, 0x05 ,0x38, 0x02 };
byte energyM9T1[] = { 0x00, 0x05, 0x39 ,0x01 };
byte energyM9T2[] = { 0x00, 0x05 ,0x39, 0x02 };
byte energyM10T1[] = { 0x00, 0x05, 0x3A ,0x01 };
byte energyM10T2[] = { 0x00, 0x05 ,0x3A, 0x02 };
byte energyM11T1[] = { 0x00, 0x05, 0x3B ,0x01 };
byte energyM11T2[] = { 0x00, 0x05 ,0x3B, 0x02 };
byte energyM12T1[] = { 0x00, 0x05, 0x3C ,0x01 };
byte energyM12T2[] = { 0x00, 0x05 ,0x3C, 0x02 };

byte response[19];
int byteReceived;
int byteSend;
int netAdr;
int SCAN_YES_NO=0;
int TST_YES_NO=0;
int ACCESS_YES_NO=0;
int ALLOW=0;
int count_stat=0;
int date_day;

ESPeasySoftwareSerial *RS485Serial;

boolean Plugin_220(byte function, struct EventStruct *event, String& string)
{
  boolean success = false;

  switch (function)
  {
    case PLUGIN_DEVICE_ADD:
      {
        Device[++deviceCount].Number = PLUGIN_ID_220;
        Device[deviceCount].Type = DEVICE_TYPE_DUAL;
       // Device[deviceCount].VType = SENSOR_TYPE_JSON;
        Device[deviceCount].Ports = 0;
        Device[deviceCount].PullUpOption = false;
        Device[deviceCount].InverseLogicOption = false;
        Device[deviceCount].FormulaOption = true;
        Device[deviceCount].ValueCount = 0;
        Device[deviceCount].SendDataOption = true;
        Device[deviceCount].TimerOption = true;
        Device[deviceCount].GlobalSyncOption = true;
        break;
      }

    case PLUGIN_GET_DEVICENAME:
      {
        string = F(PLUGIN_NAME_220);
        break;
      }

    case PLUGIN_GET_DEVICEVALUENAMES:
      {
        strcpy_P(ExtraTaskSettings.TaskDeviceValueNames[0], PSTR(PLUGIN_VALUENAME1_220));
        strcpy_P(ExtraTaskSettings.TaskDeviceValueNames[1], PSTR(PLUGIN_VALUENAME2_220));

      break;
      }

    case PLUGIN_WEBFORM_LOAD:
      {
 	      addFormCheckBox(F("Read month stat"), F("plugin_220_stat"), Settings.TaskDevicePluginConfig[event->TaskIndex][0]);
        addFormNumericBox(F("Start time to read stat for every month, hour"), F("plugin_220_start_hour"), Settings.TaskDevicePluginConfig[event->TaskIndex][1], 0, 23);
        addFormNumericBox(F("Start time to read stat for every month, min"), F("plugin_220_start_min"), Settings.TaskDevicePluginConfig[event->TaskIndex][2], 0, 59);
	      addFormNumericBox(F("End time to read stat for every month, hour"), F("plugin_220_end_hour"), Settings.TaskDevicePluginConfig[event->TaskIndex][3], 0, 23);
        addFormNumericBox(F("End time to read stat for every month, min"), F("plugin_220_end_min"), Settings.TaskDevicePluginConfig[event->TaskIndex][4], 0, 59);

        //addFormNote(F("Select controler to send all data"));
        addFormNumericBox(F("Select MQTT controller to publish data in json format "), F("plugin_220_controller"), Settings.TaskDevicePluginConfig[event->TaskIndex][5], 1, 4);
        addFormNote(F("MQTT topic to publish runtime data is: \"Mercury230/Merc_data_json\""));
        addFormNote(F("MQTT topic to publish history data is: \"Mercury230/Merc_stat_json\""));
        addFormNote(F("Interval (below) must be shorter then period between end and start"));

        success = true;
        break;
      }

        case PLUGIN_WEBFORM_SAVE:
      {
        Settings.TaskDevicePluginConfig[event->TaskIndex][0] = isFormItemChecked(F("plugin_220_stat"));
        Settings.TaskDevicePluginConfig[event->TaskIndex][1] = getFormItemInt(F("plugin_220_start_hour"));
        Settings.TaskDevicePluginConfig[event->TaskIndex][2] = getFormItemInt(F("plugin_220_start_min"));
        Settings.TaskDevicePluginConfig[event->TaskIndex][3] = getFormItemInt(F("plugin_220_end_hour"));
        Settings.TaskDevicePluginConfig[event->TaskIndex][4] = getFormItemInt(F("plugin_220_end_min"));
        Settings.TaskDevicePluginConfig[event->TaskIndex][5] = getFormItemInt(F("plugin_220_controller"));
        success = true;
        break;
      }

      case PLUGIN_INIT:
      {
        RS485Serial = new ESPeasySoftwareSerial(Settings.TaskDevicePin1[event->TaskIndex], Settings.TaskDevicePin2[event->TaskIndex]);
        RS485Serial->begin(9600);
       Serial.begin(9600);
	     pinMode(SerialControl, OUTPUT);
	     digitalWrite(SerialControl, RS485Receive);
	     delay(300);
	     success = true;
      break;
      }


    case PLUGIN_READ:
      {
        TST_YES_NO=0;
        ACCESS_YES_NO=0;
        ALLOW=0;
        String getS = "loop_000";
        if(getS.substring(0,5) == "loop_")
          { ALLOW=1;
            SCAN_YES_NO=1;
            netAdr=getS.substring(5,8).toInt();
            
          }
        if(ALLOW==1 or SCAN_YES_NO==1)
          {
           testConnect[0] = netAdr;
           response[0] = 0;
           send(testConnect, sizeof(testConnect), response);
           if(response[0] == netAdr)
             {      TST_YES_NO=1;
             }
            else
             {      TST_YES_NO=0;
             }

           if(TST_YES_NO==1)
            {
             delay(100);
             Access[0] = netAdr;
             response[0] = 0;
             send(Access, sizeof(Access), response);
             if(response[0] == netAdr)
              {      ACCESS_YES_NO=1;
              }
             else
              {      ACCESS_YES_NO=0;
              }
            }


        if(ACCESS_YES_NO==1)
         {
          float* Uv = getCurrent(netAdr,Suply,12);
          float* Ia = getCurrent(netAdr,Current,12);
          float* Pw = getPowerNow(netAdr,15);
          float  T1 = getEnergyMT(netAdr,energyT1,19);
          float  T2 =getEnergyMT(netAdr,energyT2,19);
          float  T3 = getEnergyMT(netAdr,energyT3,19);
          float  T4 = getEnergyMT(netAdr,energyT4,19);
          String result1 = String("{");
          result1 += String( "\"Ia1\":" + String(Ia[0]/10) + ",\"Ia2\":"+   String(Ia[1]/10) + ",\"Ia3\":" +   String(Ia[2]/10) + ",");
          result1 += String( "\"Uv1\":" + String(Uv[0]) + ",\"Uv2\":"+   String(Uv[1]) + ",\"Uv3\":" +   String(Uv[2]) + ",");
          result1 += String( "\"Pw0\":" + String(Pw[0]) + ",\"Pw1\":"+   String(Pw[1]) + ",\"Pw2\":" +   String(Pw[2]) +   ",\"Pw3\":" +  String(Pw[3]) + ",");
          result1 += String( "\"T1\":" + String(T1) + ",\"T2\":"+   String(T2) + ",\"T3\":"+   String(T3)+   ",\"T4\":"+   String(T4));
          result1 += String("}");
          String value = "";
          value = result1;
          String tmppubname = "/Mercury230/Merc_data_json";
          int controller = Settings.TaskDevicePluginConfig[event->TaskIndex][5];
          int Hours = hour();
          int Minutes = minute();
          int date_day = day();
          int start_hour = Settings.TaskDevicePluginConfig[event->TaskIndex][1];
          int start_min = Settings.TaskDevicePluginConfig[event->TaskIndex][2];
          int end_hour = Settings.TaskDevicePluginConfig[event->TaskIndex][3];
          int end_min = Settings.TaskDevicePluginConfig[event->TaskIndex][4];
          bool checked_stat = false;
          checked_stat = Settings.TaskDevicePluginConfig[event->TaskIndex][0];
          if ((checked_stat == true) & (count_stat == 0))
            {
              if ((start_hour <= Hours) & (end_hour >= Hours) & ( start_min <= Minutes) & (end_min >= Minutes) )
                {
                  String log = F("start get stat");
                  addLog(LOG_LEVEL_INFO, log);
                  float  M1T1 = getEnergyMT(netAdr,energyM1T1,19);
                  float  M1T2 = getEnergyMT(netAdr,energyM1T2,19);
                  float  M2T1 = getEnergyMT(netAdr,energyM2T1,19);
                  float  M2T2 = getEnergyMT(netAdr,energyM2T2,19);
                  float  M3T1 = getEnergyMT(netAdr,energyM3T1,19);
                  float  M3T2 = getEnergyMT(netAdr,energyM3T2,19);
                  float  M4T1 = getEnergyMT(netAdr,energyM4T1,19);
                  float  M4T2 = getEnergyMT(netAdr,energyM4T2,19);
                  float  M5T1 = getEnergyMT(netAdr,energyM5T1,19);
                  float  M5T2 = getEnergyMT(netAdr,energyM5T2,19);
                  float  M6T1 = getEnergyMT(netAdr,energyM6T1,19);
                  float  M6T2 = getEnergyMT(netAdr,energyM6T2,19);
                  float  M7T1 = getEnergyMT(netAdr,energyM7T1,19);
                  float  M7T2 = getEnergyMT(netAdr,energyM7T2,19);
                  float  M8T1 = getEnergyMT(netAdr,energyM8T1,19);
                  float  M8T2 = getEnergyMT(netAdr,energyM8T2,19);
                  float  M9T1 = getEnergyMT(netAdr,energyM9T1,19);
                  float  M9T2 = getEnergyMT(netAdr,energyM9T2,19);
                  float  M10T1 = getEnergyMT(netAdr,energyM10T1,19);
                  float  M10T2 = getEnergyMT(netAdr,energyM10T2,19);
                  float  M11T1 = getEnergyMT(netAdr,energyM11T1,19);
                  float  M11T2 = getEnergyMT(netAdr,energyM11T2,19);
                  float  M12T1 = getEnergyMT(netAdr,energyM12T1,19);
                  float  M12T2 = getEnergyMT(netAdr,energyM12T2,19);
                  String result2 = String("{");
                  result2 += String( "\"M1T1\":" + String(M1T1) + ",\"M1T2\":"+   String(M1T2)      + ",\"M2T1\":" +   String(M2T1) + ",\"M2T2\":" +   String(M2T2)+ ",");
                  result2 +=  String( "\"M3T1\":" + String(M3T1) + ",\"M3T2\":"+   String(M3T2)     + ",\"M4T1\":" +   String(M4T1) + ",\"M4T2\":" +   String(M4T2)+ ",");
                  result2 +=  String( "\"M5T1\":" + String(M5T1) + ",\"M5T2\":"+   String(M5T2)     + ",\"M6T1\":" +   String(M6T1) + ",\"M6T2\":" +   String(M6T2)+ ",");
                  result2 += String( "\"M7T1\":" + String(M7T1)  + ",\"M7T2\":"+   String(M7T2)     + ",\"M8T1\":" +   String(M8T1) + ",\"M8T2\":" +   String(M8T2)+ ",");
                  result2 += String( "\"M9T1\":" + String(M9T1)  + ",\"M9T2\":"+   String(M9T2)     + ",\"M10T1\":" +   String(M10T1) + ",\"M10T2\":" +   String(M10T2)+ ",");
                  result2 += String( "\"M11T1\":" + String(M11T1)  + ",\"M11T2\":"+   String(M11T2)     + ",\"M12T1\":" +   String(M12T1) + ",\"M12T2\":" +   String(M12T2));
                  result2 += String("}");
                  value=result2;
                  //log = F("Mercury stat data: ");
                  //log += result2;
                  //addLog(LOG_LEVEL_INFO, log);
                  tmppubname = "/Mercury230/Merc_stat_json";
                  count_stat == 1;
                }
             }
          MQTTpublish(controller, tmppubname.c_str(), value.c_str(), Settings.MQTTRetainFlag);
        } //IF TST_YES_NO
        delay(1000);
        if ((count_stat == 1) & (day() != date_day))
          {count_stat = 0; }
        success = true;
        break;
      } //if
      }  //PLUGIN_READ
  } //switch
  return success;
} //boolean Plugin_220

String getSerialNumber(int netAdr)
 {
  String s1,s2,s3,s4;
  response[0]=0;
  Sn[0] = netAdr;
  send(Sn, sizeof(Sn),response);
  if((int)response[1] < 10) { s1="0" + String((int)response[1]); } else {s1=String((int)response[1]);}
  if((int)response[2] < 10) { s2="0" + String((int)response[2]); } else {s2=String((int)response[2]);}
  if((int)response[3] < 10) { s3="0" + String((int)response[3]); } else {s3=String((int)response[3]);}
  if((int)response[4] < 10) { s4="0" + String((int)response[4]); } else {s4=String((int)response[4]);}
  String n = s1+s2+s3+s4;
  String log = F("Sernumber ");
  log += n;
  addLog(LOG_LEVEL_INFO, log);
  return String(response[0])+";"+n;
}

float* getPowerNow(int netAdr, int length_resp)
{
  response[0]=0;
  Power[0] = netAdr;
  send(Power, sizeof(Power),response);
  int l = length_resp;
  //String log = F("Byte response 15 bytes:");
  //for(int i=0; i<l; i++)
  //  {
  //    log += response[i];
  //  }
  //addLog(LOG_LEVEL_INFO, log);
  byte crcb1=response[l-2];
  byte crcb2=response[l-1];
  unsigned int crcm = crc16MODBUS(response, l-2);
  unsigned int crc1m = crcm & 0xFF;
  unsigned int crc2m = (crcm>>8) & 0xFF;
  if ((crcb1 == crc1m) & (crcb2 ==crc2m) )
    {
    }
  else
    {
      String log = F("CRC is error!");
      addLog(LOG_LEVEL_INFO, log);
      return 0;
    }
  long* P = new long[4];
  response[1] &= ~(1<<6);
  response[1] &= ~(1<<7);
  response[4] &= ~(1<<6);
  response[4] &= ~(1<<7);
  response[7] &= ~(1<<6);
  response[7] &= ~(1<<7);
  response[10] &= ~(1<<6);
  response[10] &= ~(1<<7);

  P[0] = ((response[1] << 16)+ (response[3] << 8) + response[2]);
  P[1] = ((response[4] << 16)+ (response[6] << 8) + response[5]);
  P[2] = ((response[7] << 16)+ (response[9] << 8) + response[8]);
  P[3] = ((response[10] << 16)+ (response[12] << 8) + response[11]);
  float* U = new float[4];
  U[0] = ((float)P[0])/100;
  U[1] = ((float)P[1])/100;
  U[2] = ((float)P[2])/100;
  U[3] = ((float)P[3])/100;
  if(response[0] == netAdr)   return (U);
    else   return 0;
}

float* getCurrent(int netAdr,byte cmdget[], int length_resp)
{
  response[0]=0;
  Current[0] = netAdr;
  long* P = new long[3];
  send(cmdget, sizeof(Current),response);
  int l = length_resp;
  //String log = F("Byte response 12 bytes:");
  //for(int i=0; i<l; i++)
  //  {
  //    log += response[i];
  //  }
  //addLog(LOG_LEVEL_INFO, log);
  byte crcb1=response[l-2];
  byte crcb2=response[l-1];
  unsigned int crcm = crc16MODBUS(response, l-2);
  unsigned int crc1m = crcm & 0xFF;
  unsigned int crc2m = (crcm>>8) & 0xFF;
  if ((crcb1 == crc1m) & (crcb2 ==crc2m) )
    {
    }
  else
    {
      String log = F("CRC is error!");
      addLog(LOG_LEVEL_INFO, log);
      return 0;
    }

  P[0] = ((response[1] << 16)+ (response[3] << 8) + response[2]);
  P[1] = ((response[4] << 16)+ (response[6] << 8) + response[5]);
  P[2] = ((response[7] << 16)+ (response[9] << 8) + response[8]);
  float* U = new float[3];
  U[0] = ((float)P[0])/100;
  U[1] = ((float)P[1])/100;
  U[2] = ((float)P[2])/100;
      if(response[0] == netAdr)   return (U);
    else   return 0;
}

float getEnergyMT(int netAdr,byte cmdget[], int length_resp)
{
  response[0]=0;
  send(cmdget, sizeof(cmdget),response);
  int l = length_resp;
  //String log = F("Byte response 19 bytes:");
  //for(int i=0; i<l; i++)
  //  {
  //    log += response[i];
  //  }
  //addLog(LOG_LEVEL_INFO, log);
  byte crcb1=response[l-2];
  byte crcb2=response[l-1];
  unsigned int crcm = crc16MODBUS(response, l-2);
  unsigned int crc1m = crcm & 0xFF;
  unsigned int crc2m = (crcm>>8) & 0xFF;
  if ((crcb1 == crc1m) & (crcb2 ==crc2m) )
      {
      }
  else
      {
      String log = F("CRC is error!");
      addLog(LOG_LEVEL_INFO, log);
      return 0;
      }

  long  P0 = ((response[2] << 24)+(response[1] << 16)+ (response[4] << 8) + response[3]);
  float U0 = ((float)P0)/1000;
  return   U0;
}


void send(byte *cmd, int s, byte *response) {
  unsigned int crc = crc16MODBUS(cmd, s);
  unsigned int crc1 = crc & 0xFF;
  unsigned int crc2 = (crc>>8) & 0xFF;
  delay(10);
  digitalWrite(SerialControl, RS485Transmit);  // Init Transceiver
       for(int i=0; i<s; i++)
       {
              RS485Serial->write(cmd[i]);
       }
  RS485Serial->write(crc1);
  RS485Serial->write(crc2);
  byte i = 0;
  digitalWrite(SerialControl, RS485Receive);  // Init Transceiver
  delay(200);
         if (RS485Serial->available())
           {
             while (RS485Serial->available())
               {
                byteReceived= RS485Serial->read();    // Read received byte
                delay(10);
                response[i++] = byteReceived;
                }
           }


  delay(20);
}

unsigned int crc16MODBUS(byte *s, int count) {
  unsigned int crcTable[] = {
        0x0000, 0xC0C1, 0xC181, 0x0140, 0xC301, 0x03C0, 0x0280, 0xC241,
        0xC601, 0x06C0, 0x0780, 0xC741, 0x0500, 0xC5C1, 0xC481, 0x0440,
        0xCC01, 0x0CC0, 0x0D80, 0xCD41, 0x0F00, 0xCFC1, 0xCE81, 0x0E40,
        0x0A00, 0xCAC1, 0xCB81, 0x0B40, 0xC901, 0x09C0, 0x0880, 0xC841,
        0xD801, 0x18C0, 0x1980, 0xD941, 0x1B00, 0xDBC1, 0xDA81, 0x1A40,
        0x1E00, 0xDEC1, 0xDF81, 0x1F40, 0xDD01, 0x1DC0, 0x1C80, 0xDC41,
        0x1400, 0xD4C1, 0xD581, 0x1540, 0xD701, 0x17C0, 0x1680, 0xD641,
        0xD201, 0x12C0, 0x1380, 0xD341, 0x1100, 0xD1C1, 0xD081, 0x1040,
        0xF001, 0x30C0, 0x3180, 0xF141, 0x3300, 0xF3C1, 0xF281, 0x3240,
        0x3600, 0xF6C1, 0xF781, 0x3740, 0xF501, 0x35C0, 0x3480, 0xF441,
        0x3C00, 0xFCC1, 0xFD81, 0x3D40, 0xFF01, 0x3FC0, 0x3E80, 0xFE41,
        0xFA01, 0x3AC0, 0x3B80, 0xFB41, 0x3900, 0xF9C1, 0xF881, 0x3840,
        0x2800, 0xE8C1, 0xE981, 0x2940, 0xEB01, 0x2BC0, 0x2A80, 0xEA41,
        0xEE01, 0x2EC0, 0x2F80, 0xEF41, 0x2D00, 0xEDC1, 0xEC81, 0x2C40,
        0xE401, 0x24C0, 0x2580, 0xE541, 0x2700, 0xE7C1, 0xE681, 0x2640,
        0x2200, 0xE2C1, 0xE381, 0x2340, 0xE101, 0x21C0, 0x2080, 0xE041,
        0xA001, 0x60C0, 0x6180, 0xA141, 0x6300, 0xA3C1, 0xA281, 0x6240,
        0x6600, 0xA6C1, 0xA781, 0x6740, 0xA501, 0x65C0, 0x6480, 0xA441,
        0x6C00, 0xACC1, 0xAD81, 0x6D40, 0xAF01, 0x6FC0, 0x6E80, 0xAE41,
        0xAA01, 0x6AC0, 0x6B80, 0xAB41, 0x6900, 0xA9C1, 0xA881, 0x6840,
        0x7800, 0xB8C1, 0xB981, 0x7940, 0xBB01, 0x7BC0, 0x7A80, 0xBA41,
        0xBE01, 0x7EC0, 0x7F80, 0xBF41, 0x7D00, 0xBDC1, 0xBC81, 0x7C40,
        0xB401, 0x74C0, 0x7580, 0xB541, 0x7700, 0xB7C1, 0xB681, 0x7640,
        0x7200, 0xB2C1, 0xB381, 0x7340, 0xB101, 0x71C0, 0x7080, 0xB041,
        0x5000, 0x90C1, 0x9181, 0x5140, 0x9301, 0x53C0, 0x5280, 0x9241,
        0x9601, 0x56C0, 0x5780, 0x9741, 0x5500, 0x95C1, 0x9481, 0x5440,
        0x9C01, 0x5CC0, 0x5D80, 0x9D41, 0x5F00, 0x9FC1, 0x9E81, 0x5E40,
        0x5A00, 0x9AC1, 0x9B81, 0x5B40, 0x9901, 0x59C0, 0x5880, 0x9841,
        0x8801, 0x48C0, 0x4980, 0x8941, 0x4B00, 0x8BC1, 0x8A81, 0x4A40,
        0x4E00, 0x8EC1, 0x8F81, 0x4F40, 0x8D01, 0x4DC0, 0x4C80, 0x8C41,
        0x4400, 0x84C1, 0x8581, 0x4540, 0x8701, 0x47C0, 0x4680, 0x8641,
        0x8201, 0x42C0, 0x4380, 0x8341, 0x4100, 0x81C1, 0x8081, 0x4040
    };

    unsigned int crc = 0xFFFF;

    for(int i = 0; i < count; i++) {
        crc = ((crc >> 8) ^ crcTable[(crc ^ s[i]) & 0xFF]);
    }

    return crc;
}

#endif // USES_P220
