#include <Arduino.h>
#include <ESPAsyncWebServer.h>
#include "index_html/index_html.h"
#include "FS_config/FS_config.h"

class webserver{
  public :
    void webserver_start();
};