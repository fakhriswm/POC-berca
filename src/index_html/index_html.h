const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head><title>Cubeacon Reader</title></head>
<body>
  <h1 style="color:blue;font-family:arial">READER CONFIG PAGE</h1>
  <h3>Netwok : %NETSTATE% </h3><br>
  <h2>Device Configuration</h2><br>
  <h3>Access Point Setting</h3>
  <form  action = "/config/network_ap" method="post"> 
    <table border= "0" >
      <tr>
        <td>AP SSID</td>
        <td>: <input type="text" name="ssid" id="ssid" value=%AP_SSID%></td>
      </tr>
      <tr>
        <td>AP Password</td>
        <td>: <input type="password" name="password" id="password" value=%AP_PASSWORD%></td>
      </tr>
    </table>
    <br>
    <input type="submit" value="Save AP Network Config">
  </form> 
  <br>
  <h3>Station Setting</h3>
  <form action = "/config/network_sta" method="post"> 
    <table border= "0" >
      <tr>
        <td>SSID</td>
        <td>: <input type="text" name="ssid" id="ssid" value=%STA_SSID%></td>
      </tr>
      <tr>
        <td>Password</td>
        <td>: <input type="password" name="password" id="password" value=%STA_PASSWORD%></td>
      </tr>
            <tr>
        <td></td>
      </tr> 
    </table>
    <br>
    <input type="submit" value="Save STNetwork Config">
  </form> 
  
  <br>
  <h3>Connection Setting</h3>
  <form action = "/config/backend" method="post"> 
    <table border= "0" >
      <tr>
        <td>MQTT Broker</td>
        <td>: <input type="text" name="mqtt_broker" id="mqtt_broker" value=%MQTT_BROKER%></td>
      </tr>
      <tr>
        <td>MQTT Username</td>
        <td>: <input type="text" name="mqtt_username" id="mqtt_username" value=%MQTT_USERNAME%></td>
      </tr>
      <tr>
        <td>MQTT Password</td>
        <td>: <input type="password" name="mqtt_password" id="mqtt_password" value=%MQTT_PASSWORD%></td>
      </tr>
      <tr>
        <td>MQTT Port</td>
        <td>: <input type="number" name="mqtt_port" id="mqtt_port" value=%MQTT_PORT%></td>
      </tr>
	 <tr>
				<td><input type="radio" name="network_mode" id=dhcp value="DHCP" onchange="ip_form()"> DHCP<br></td>
				<td><input type="radio" name="network_mode" id=static value="Static" onchange="ip_form()"> Static<br></td>
			</tr>
    </table>
    <br>
    <input type="submit" value="Save Backend Config">
    <br>
    <h3>Scan Setting</h3>
  </form> 
  <form action = "/config/scanning" method="post"> 
    <table border= "0" >
      <tr>
        <td>Proximity distance(m)</td>
        <td>: <input type="number" step=0.1 name="proximity" id="proximity" value=%PROXIMITY%></td>
      </tr>
      <tr>
        <td>BLE timeout (ms)</td>
        <td>: <input type="number" name="ble_timeout" id="ble_timeout" value=%BLE_TIMEOUT%></td>
      </tr>
      <tr>
        <td>Detect counter</td>
        <td>: <input type="number" name="detect_counter" id="detect_counter" value=%DETECT_COUNTER%></td>
      </tr>
      <tr>
        <td>Master Key</td>
        <td>: <input type="password" name="master_key" id="master_key" value=%MASTER_KEY%></td>
      </tr>   
    </table>
    <br>
    <input type="submit" value="Save Scan Config">
  </form> 
<p>
  <a href="/reboot"><button class="button">Reboot</button>
</p>  

<script type="text/javascript" >  

</script> 
</body>
</html>)rawliteral";

const char login_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
    <title>Cubeacon Reader Login</title>
</head>
<body>
  <h1 style="color:blue;font-family:arial">Cubeacon Reader Landing Page</h1>
  <br>
    <form action="/login" method="post">
        <fieldset>
        <legend>Login</legend>
        <p>
            <label>Username :</label>
            <input type="text" name="username" placeholder="username..." />
        </p>
        <p>
            <label>Password :</label>
            <input type="password" name="password" placeholder="password..." />
        </p>
        <p>
            <label><input type="checkbox" name="remember" value="remember" /> Remember me</label>
        </p>
        <p>
            <input type="submit" name="submit" value="Login" />
        </p>
        </fieldset>
    </form>
</body>
</html>)rawliteral";
