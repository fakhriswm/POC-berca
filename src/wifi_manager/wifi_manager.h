#include <Arduino.h>
#include <WiFi.h>

typedef enum
{
	WIFI_STA_DISCONNECTED,
	WIFI_STA_CONNECTED,
}wifi_sta_state_t;

class wifi_manager{
  public :
    void setup_wifi_ap();
    void setup_wifi_sta();
    boolean wifi_status();
    void wifi_init(boolean enable_ap);
};

void wifi_event(WiFiEvent_t event, WiFiEventInfo_t info);
