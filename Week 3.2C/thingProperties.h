// Code generated by Arduino IoT Cloud, DO NOT EDIT.

#include <ArduinoIoTCloud.h>
#include <Arduino_ConnectionHandler.h>
#include "arduino_secrets.h"

const char SSID[]     = SECRET_SSID;    // Network SSID (name)
const char PASS[]     = SECRET_OPTIONAL_PASS;    // Network password (use for WPA, or use as key for WEP)

void onAlarmMessageChange();
void onAlarmStatusChange();

String alarmMessage;
bool alarmStatus;

void initProperties(){

  ArduinoCloud.addProperty(alarmMessage, READWRITE, ON_CHANGE, onAlarmMessageChange);
  ArduinoCloud.addProperty(alarmStatus, READWRITE, ON_CHANGE, onAlarmStatusChange);

}

WiFiConnectionHandler ArduinoIoTPreferredConnection(SSID, PASS);
