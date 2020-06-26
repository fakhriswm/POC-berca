#include <Arduino.h>

class wifi_manager{
  public :
    void setup_wifi_ap();
    void setup_wifi_sta();
    boolean wifi_status();
};

