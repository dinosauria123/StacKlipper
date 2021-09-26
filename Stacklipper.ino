#include <vector>
#include <M5Stack.h>
#include <M5TreeView.h>         // https://github.com/lovyan03/M5Stack_TreeView
#include <M5OnScreenKeyboard.h> // https://github.com/lovyan03/M5OnScreenKeyboard/
#include <MenuItemToggle.h>
#include <M5ButtonDrawer.h>
#include <Preferences.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <Arduino_JSON.h>

#include "HeaderSample.h"

M5TreeView treeView;
M5OnScreenKeyboard osk;
HeaderSample header;
HTTPClient http;

const char* ssid = "*************";
const char* password = "****************";
const char* serverName = "http://192.168.0.5:7125/";
String serverPath = serverName;
String command;
int httpResponseCode = http.GET();

JSONVar payload;

typedef std::vector<MenuItem*> vmi;

void drawFrame() {
  Rect16 r = treeView.clientRect;
  r.inflate(1);
  M5.Lcd.drawRect(r.x -1, r.y, r.w +2, r.h, MenuItem::frameColor[1]);
  M5.Lcd.drawRect(r.x, r.y -1, r.w, r.h +2, MenuItem::frameColor[1]);
}

void CallBackToggletest(MenuItem* sender) 
{
  MenuItemToggle* mi = static_cast<MenuItemToggle*>(sender);
  if (!mi) return;

  pinMode(mi->tag, OUTPUT);
  digitalWrite(mi->tag, mi->value);
}

void ShowData(MenuItem* sender){
  
  M5.Lcd.clear();
  drawFrame();
  command = "api/printer";
  http.begin(serverPath.c_str()+command);
  http.GET();
    M5.Lcd.setCursor(0, 30);
    payload = JSON.parse(http.getString());
    M5.Lcd.print(" Bed Temp. : ");
    M5.Lcd.println(payload["temperature"]["bed"]["actual"]);
    M5.Lcd.println();
    M5.Lcd.print(" Nozzle Temp. : ");
    M5.Lcd.println(payload["temperature"]["tool0"]["actual"]);
    M5.Lcd.println();
                
    command = "printer/objects/query?gcode_move&gcode_position";  
    http.begin(serverPath.c_str()+command);
    http.GET();
    payload = JSON.parse(http.getString());
    M5.Lcd.print(" X:");
    float xval = JSON.stringify(payload["result"]["status"]["gcode_move"]["position"][0]).toFloat();
    M5.Lcd.print(String(xval,2));        
    M5.Lcd.print(" Y:");
    float yval = JSON.stringify(payload["result"]["status"]["gcode_move"]["position"][1]).toFloat();
    M5.Lcd.print(String(yval,2));                
    M5.Lcd.print(" Z:");
    float zval = JSON.stringify(payload["result"]["status"]["gcode_move"]["position"][2]).toFloat();
    M5.Lcd.print(String(zval,2));
    delay(5000);
}

void SetBedTemp(MenuItem* sender) 
{
  MenuItemNumeric* mi = static_cast<MenuItemNumeric*>(sender);
  if (!mi) return;
  command = "printer/gcode/script?script=M140%20S"+String(mi->value);
  http.begin(serverPath.c_str()+command);
  http.GET();
}

void SetNozzleTemp(MenuItem* sender) 
{
  MenuItemNumeric* mi = static_cast<MenuItemNumeric*>(sender);
  if (!mi) return;
  command = "printer/gcode/script?script=M104%20S"+String(mi->value);
  http.begin(serverPath.c_str()+command);
  http.GET();
}

void PreheatPLA(MenuItem* sender) 
{
  MenuItemNumeric* mi = static_cast<MenuItemNumeric*>(sender);
  if (!mi) return;
  command = "printer/gcode/script?script=M140%20S60";
  http.begin(serverPath.c_str()+command);
  http.GET();
  command = "printer/gcode/script?script=M104%20S200";
  http.begin(serverPath.c_str()+command);
  http.GET();
}

void PreheatABS(MenuItem* sender) 
{
  MenuItemNumeric* mi = static_cast<MenuItemNumeric*>(sender);
  if (!mi) return;
  command = "printer/gcode/script?script=M140%20S90";
  http.begin(serverPath.c_str()+command);
  http.GET();
  command = "printer/gcode/script?script=M104%20S220";
  http.begin(serverPath.c_str()+command);
  http.GET();
}

void CoolDown(MenuItem* sender) 
{
  MenuItemNumeric* mi = static_cast<MenuItemNumeric*>(sender);
  if (!mi) return;
  command = "printer/gcode/script?script=M140%20S0";
  http.begin(serverPath.c_str()+command);
  http.GET();
  command = "printer/gcode/script?script=M104%20S0";
  http.begin(serverPath.c_str()+command);
  http.GET();
}

void HomeAll(MenuItem* sender) 
{
  MenuItemNumeric* mi = static_cast<MenuItemNumeric*>(sender);
  if (!mi) return;
  command = "printer/gcode/script?script=G28";
  http.begin(serverPath.c_str()+command);
  http.GET();
}

void HomeXY(MenuItem* sender) 
{
  MenuItemNumeric* mi = static_cast<MenuItemNumeric*>(sender);
  if (!mi) return;
  command = "printer/gcode/script?script=G28%20X%20Y";
  http.begin(serverPath.c_str()+command);
  http.GET();
}

void HomeZ(MenuItem* sender) 
{
  MenuItemNumeric* mi = static_cast<MenuItemNumeric*>(sender);
  if (!mi) return;
  command = "printer/gcode/script?script=G28%20Z";
  http.begin(serverPath.c_str()+command);
  http.GET();
}

void DisableSteppers(MenuItem* sender) 
{
  MenuItemNumeric* mi = static_cast<MenuItemNumeric*>(sender);
  if (!mi) return;
  command = "printer/gcode/script?script=M18%20E%20X%20Y%20Z";
  http.begin(serverPath.c_str()+command);
  http.GET();
}

void MoveX(MenuItem* sender) 
{
  MenuItemNumeric* mi = static_cast<MenuItemNumeric*>(sender);
  if (!mi) return;
  command = "printer/gcode/script?script=G1%20X"+String(mi->value);
  http.begin(serverPath.c_str()+command);
  http.GET();
}

void MoveY(MenuItem* sender) 
{
  MenuItemNumeric* mi = static_cast<MenuItemNumeric*>(sender);
  if (!mi) return;
  command = "printer/gcode/script?script=G1%20Y"+String(mi->value);
  http.begin(serverPath.c_str()+command);
  http.GET();
}

void MoveZ(MenuItem* sender) 
{
  MenuItemNumeric* mi = static_cast<MenuItemNumeric*>(sender);
  if (!mi) return;
  command = "printer/gcode/script?script=G1%20Z"+String(mi->value);
  http.begin(serverPath.c_str()+command);
  http.GET();
}

void Restart(MenuItem* sender) 
{
  MenuItemNumeric* mi = static_cast<MenuItemNumeric*>(sender);
  if (!mi) return;
  command = "printer/gcode/script?script=FIRMWARE_RESTART";
  http.begin(serverPath.c_str()+command);
  http.GET();
}

void EmergencyStop(MenuItem* sender) 
{
  MenuItemNumeric* mi = static_cast<MenuItemNumeric*>(sender);
  if (!mi) return;
  command = "printer/gcode/script?script=M112";
  http.begin(serverPath.c_str()+command);
  http.GET();
}

void setup() {
  M5.begin();
  Wire.begin();
  WiFi.begin(ssid, password);
  M5.Lcd.setTextSize(2); 
  M5.Lcd.print("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    M5.Lcd.print(".");
  }
  M5.Lcd.clear();
  treeView.clientRect.x = 2;
  treeView.clientRect.y = 16;
  treeView.clientRect.w = 316;
  treeView.clientRect.h = 200;
  treeView.itemWidth    = 220;

  treeView.useFACES       = true;
  treeView.useJoyStick    = true;
  treeView.usePLUSEncoder = true;
  treeView.useFACESEncoder= true;
  osk.useTextbox     = true;
  osk.useFACES       = true;
  osk.useCardKB      = true;
  osk.useJoyStick    = true;
  osk.usePLUSEncoder = true;
  osk.useFACESEncoder= true;
  osk.msecHold   = treeView.msecHold;
  osk.msecRepeat = treeView.msecRepeat;

  treeView.fontColor[0]  = 0xFFFF;
  treeView.backColor[0]  = 0x6314;
  treeView.frameColor[0] = 0x0118;
  treeView.fontColor[1]  = 0x7FFF;
  treeView.backColor[1]  = 0x441F;
  treeView.frameColor[1] = 0xFFF0;
  treeView.backgroundColor = 0x0008;
  treeView.itemHeight = 20;
  treeView.setFreeFont(&FreeMono9pt7b);
  M5ButtonDrawer::setFreeFont(&FreeMono9pt7b);
  M5ButtonDrawer::height = 20;
  M5ButtonDrawer::width = 106;

  for (int i = 0; i < 2; ++i) {
    M5ButtonDrawer::fontColor[i] = treeView.fontColor[i];
    M5ButtonDrawer::backColor[i] = treeView.backColor[i];
    M5ButtonDrawer::frameColor[i] = treeView.frameColor[i];
    osk.fontColor[i] = treeView.fontColor[i];
    osk.backColor[i] = treeView.backColor[i];
    osk.frameColor[i]= treeView.frameColor[i];
  }
  M5.Lcd.fillRect(0, 218, M5.Lcd.width(), 22, 0);
  
  treeView.setItems(vmi
               {new MenuItem("Show Data", ShowData) 
               , new MenuItem("Temperature ", vmi
                 { new MenuItemNumeric("Bed Temp", 20, 260, 20, 5, SetBedTemp)
                 , new MenuItemNumeric("Nozzle Temp", 100, 260, 100, 5, SetNozzleTemp)
                 , new MenuItem("Preheat PLA", PreheatPLA)
                 , new MenuItem("Preheat ABS", PreheatABS)
                 , new MenuItem("Cool Down", CoolDown)
                 } )
               , new MenuItem("Control ", vmi
                 { new MenuItem("HOME all", HomeAll)
                 , new MenuItem("HOME XY", HomeXY)
                 , new MenuItem("HOME Z", HomeZ)
                 , new MenuItem("Disable Steppers", DisableSteppers)
                 , new MenuItemNumeric("Move X", 0, 230, 0, 1, MoveX)
                 , new MenuItemNumeric("Move Y", 0, 230, 0, 1, MoveY)
                 , new MenuItemNumeric("Move Z", 0, 230, 0, 1, MoveZ)
                 } )
               , new MenuItem("Restart", Restart)  
               , new MenuItem("Emergency Stop", EmergencyStop)  
               } );

  treeView.begin();
  drawFrame();
}

uint32_t loopcounter = 0;

void loop() {
  MenuItem* mi = treeView.update();

  if (!(loopcounter % 10))  header.draw();

  if (treeView.isRedraw()) {
    drawFrame();
  }
}
