#include <WiFi.h>
//wifi config
const char* ssid = "YOURSSIDHERE";
const char* password = "YOURPASSWORDHERE";
const char* hostname = "evo64";
const unsigned long resetdelay = 5;
//webserver config
WiFiServer server(80);
String header;

//gpio pin config
const int LED = LED_BUILTIN;
const int KERNAL0 = 0;
const int KERNAL1 = 1;
const int KERNAL2 = 2;
const int BASIC0 = 3;
const int BASIC1 = 4;
const int CHARGEN0 = 5;
const int CHARGEN1 = 6;
const int CHARGEN2 = 7;
const int CARTMODE = 8;
const int SIDDE = 9;
const int SIDDF = 10;
const int SIDPS = 11;
const int SIDMS = 12;
const int RESET = 13;

// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0; 
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;

void setup() {
//set serial baud rate
  Serial.begin(115200);
//Define Evo Control Pins
  pinMode(KERNAL0, OUTPUT);
  pinMode(KERNAL1, OUTPUT);
  pinMode(KERNAL2, OUTPUT);
  pinMode(BASIC0, OUTPUT);
  pinMode(BASIC1, OUTPUT);
  pinMode(CHARGEN0, OUTPUT);
  pinMode(CHARGEN1, OUTPUT);
  pinMode(CHARGEN2, OUTPUT);
  pinMode(CARTMODE, OUTPUT);
  pinMode(SIDPS, OUTPUT);
  pinMode(SIDMS, OUTPUT);
  pinMode(SIDDE, OUTPUT);
  pinMode(SIDDF, OUTPUT);
  pinMode(RESET, OUTPUT);
  pinMode(LED, OUTPUT);
// Set output default state at power on.  
// Remember, these are ACTIVE LOW.  So high is like you have no jumper installed or your DIP switch is turned off.
// By pulling these signals low to 0v, you are enabling the feature.
  digitalWrite(KERNAL0, LOW);
  digitalWrite(KERNAL1, HIGH);
  digitalWrite(KERNAL2, HIGH);
  digitalWrite(BASIC0, HIGH);
  digitalWrite(BASIC1, HIGH);
  digitalWrite(CHARGEN0, LOW);
  digitalWrite(CHARGEN1, HIGH);
  digitalWrite(CHARGEN2, HIGH);
  digitalWrite(CARTMODE, HIGH);
  digitalWrite(SIDPS, HIGH);
  digitalWrite(SIDMS, HIGH);
  digitalWrite(SIDDE, HIGH);
  digitalWrite(SIDDF, HIGH); 
  digitalWrite(RESET, HIGH); 
  digitalWrite(LED, HIGH);
// Connect to wifi network
  WiFi.setHostname(hostname); 
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
// Show network config
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}
void loop(){
//webserver stuff I stole out of example configs from randomnerdtutorials.com
  WiFiClient client = server.available();  
  if (client) {                            
    currentTime = millis();
    previousTime = currentTime;
    Serial.println("New Client.");         
    String currentLine = "";               
    while (client.connected() && currentTime - previousTime <= timeoutTime) {  
      currentTime = millis();
      if (client.available()) {             
        char c = client.read();             
        Serial.write(c);                    
        header += c;
        if (c == '\n') {                    
           if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
// GPIO config scenarios based on URL sent to server
		if (header.indexOf("/action?ROM=K0") != -1)
		{
            digitalWrite(KERNAL0, 1);
            digitalWrite(KERNAL1, 1);
            digitalWrite(KERNAL2, 1);
            digitalWrite(CARTMODE, 1);
            digitalWrite(BASIC0, 1);
            digitalWrite(BASIC1, 1);
			}
		if (header.indexOf("/action?ROM=K1") != -1)
		{
            digitalWrite(KERNAL0, 0);
            digitalWrite(KERNAL1, 1);
            digitalWrite(KERNAL2, 1);
            digitalWrite(BASIC0, 1);
            digitalWrite(BASIC1, 1);
            digitalWrite(CARTMODE, 1);
			}
		if (header.indexOf("/action?ROM=K2") != -1)
		{
            digitalWrite(KERNAL0, 1);
            digitalWrite(KERNAL1, 0);
            digitalWrite(KERNAL2, 1);
            digitalWrite(BASIC0, 1);
            digitalWrite(BASIC1, 1);
            digitalWrite(CARTMODE, 1);
			}
		if (header.indexOf("/action?ROM=K3") != -1)
		{
	        	digitalWrite(KERNAL0, 0);
            digitalWrite(KERNAL1, 0);
            digitalWrite(KERNAL2, 1);
            digitalWrite(BASIC0, 1);
            digitalWrite(BASIC1, 1);
            digitalWrite(CARTMODE, 1);
			}
		if (header.indexOf("/action?ROM=K4") != -1)
		{
      	  	digitalWrite(KERNAL0, 1);
            digitalWrite(KERNAL1, 1);
            digitalWrite(KERNAL2, 0);
            digitalWrite(BASIC0, 1);
            digitalWrite(BASIC1, 1);
            digitalWrite(CARTMODE, 1);
			}
		if (header.indexOf("/action?ROM=K5") != -1)
		{
      	  	digitalWrite(KERNAL0, 0);
            digitalWrite(KERNAL1, 1);
            digitalWrite(KERNAL2, 0);
 //using different BASIC ROM slot for OpenROMS
		      	digitalWrite(BASIC0, 0);
            digitalWrite(BASIC1, 0);
            digitalWrite(CARTMODE, 1);
			}
		if (header.indexOf("/action?ROM=K6") != -1)
		{
	        	digitalWrite(KERNAL0, 1);
            digitalWrite(KERNAL1, 0);
            digitalWrite(KERNAL2, 0);
            digitalWrite(BASIC0, 1);
            digitalWrite(BASIC1, 1);
            digitalWrite(CARTMODE, 1);
			}
		if (header.indexOf("/action?ROM=K7") != -1)
		{
	        	digitalWrite(KERNAL0, 0);
            digitalWrite(KERNAL1, 0);
            digitalWrite(KERNAL2, 0);
            digitalWrite(BASIC0, 1);
            digitalWrite(BASIC1, 1);
            digitalWrite(CARTMODE, 1);
			}	
		if (header.indexOf("/noreset?ROM=C0") != -1)
		{
      	  	digitalWrite(CHARGEN0, 1);
            digitalWrite(CHARGEN1, 1);
            digitalWrite(CHARGEN2, 1);
			}
		if (header.indexOf("/noreset?ROM=C1") != -1)
		{
        		digitalWrite(CHARGEN0, 0);
            digitalWrite(CHARGEN1, 1);
            digitalWrite(CHARGEN2, 1);
			}
		if (header.indexOf("/noreset?ROM=C2") != -1)
		{
		        digitalWrite(CHARGEN0, 1);
            digitalWrite(CHARGEN1, 0);
            digitalWrite(CHARGEN2, 1);
			}
		if (header.indexOf("/noreset?ROM=C3") != -1)
		{
      	  	digitalWrite(CHARGEN0, 0);
            digitalWrite(CHARGEN1, 0);
            digitalWrite(CHARGEN2, 1);
			}
		if (header.indexOf("/noreset?ROM=C4") != -1)
		{
	        	digitalWrite(CHARGEN0, 1);
            digitalWrite(CHARGEN1, 1);
            digitalWrite(CHARGEN2, 0);
			}
		if (header.indexOf("/noreset?ROM=C5") != -1)
		{
	        	digitalWrite(CHARGEN0, 0);
            digitalWrite(CHARGEN1, 1);
            digitalWrite(CHARGEN2, 0);
			}
		if (header.indexOf("/noreset?ROM=C6") != -1)
		{
	        	digitalWrite(CHARGEN0, 1);
            digitalWrite(CHARGEN1, 0);
            digitalWrite(CHARGEN2, 0);
			}
		if (header.indexOf("/noreset?ROM=C7") != -1)
		{
		        digitalWrite(CHARGEN0, 0);
            digitalWrite(CHARGEN1, 0);
            digitalWrite(CHARGEN2, 0);
			}
		if (header.indexOf("/action?ROM=G0") != -1)
		{
		        digitalWrite(KERNAL0, 1);
            digitalWrite(KERNAL1, 1);
            digitalWrite(KERNAL2, 1);
            digitalWrite(CARTMODE, 0);
		        digitalWrite(BASIC0, 1);
            digitalWrite(BASIC1, 1);
			}
		if (header.indexOf("/action?ROM=G1") != -1)
		{
	      		digitalWrite(KERNAL0, 0);
            digitalWrite(KERNAL1, 1);
            digitalWrite(KERNAL2, 1);
	         	digitalWrite(BASIC0, 1);
            digitalWrite(BASIC1, 1);
            digitalWrite(CARTMODE, 0);
			}
		if (header.indexOf("/action?ROM=G2") != -1)
		{
	        	digitalWrite(KERNAL0, 1);
            digitalWrite(KERNAL1, 0);
            digitalWrite(KERNAL2, 1);
            digitalWrite(BASIC0, 1);
            digitalWrite(BASIC1, 1);
	        	digitalWrite(CARTMODE, 0);
			}
		if (header.indexOf("/action?ROM=G3") != -1)
		{
	        	digitalWrite(KERNAL0, 0);
            digitalWrite(KERNAL1, 0);
            digitalWrite(KERNAL2, 1);
            digitalWrite(BASIC0, 1);
            digitalWrite(BASIC1, 1);
            digitalWrite(CARTMODE,0);
			}
		if (header.indexOf("/action?ROM=G4") != -1)
		{
      	  	digitalWrite(KERNAL0, 1);
            digitalWrite(KERNAL1, 1);
            digitalWrite(KERNAL2, 0);
            digitalWrite(BASIC0, 1);
            digitalWrite(BASIC1, 1);
            digitalWrite(CARTMODE,0);
			}
		if (header.indexOf("/action?ROM=G5") != -1)
		{
          	digitalWrite(KERNAL0, 0);
            digitalWrite(KERNAL1, 1);
            digitalWrite(KERNAL2, 0);
            digitalWrite(BASIC0, 0);
            digitalWrite(BASIC1, 1);
            digitalWrite(CARTMODE, 0);
			}
		if (header.indexOf("/action?ROM=G6") != -1)
		{
	        	digitalWrite(KERNAL0, 1);
            digitalWrite(KERNAL1, 0);
            digitalWrite(KERNAL2, 0);
            digitalWrite(BASIC0, 1);
            digitalWrite(BASIC1, 1);
            digitalWrite(CARTMODE, 0);
			}
		if (header.indexOf("/action?ROM=G7") != -1)
		{
	        	digitalWrite(KERNAL0, 0);
            digitalWrite(KERNAL1, 0);
            digitalWrite(KERNAL2, 0);
            digitalWrite(BASIC0, 1);
            digitalWrite(BASIC1, 1);
            digitalWrite(CARTMODE, 0);
			}
		if (header.indexOf("/action?ROM=G8") != -1)
		{
	    	    digitalWrite(KERNAL0, 1);
            digitalWrite(KERNAL1, 1);
            digitalWrite(KERNAL2, 1);
            digitalWrite(CARTMODE, 0);
		        digitalWrite(BASIC0, 0);
            digitalWrite(BASIC1, 1);
			}
		if (header.indexOf("/action?ROM=G9") != -1)
		{
	        	digitalWrite(KERNAL0, 0);
            digitalWrite(KERNAL1, 1);
            digitalWrite(KERNAL2, 1);
	        	digitalWrite(BASIC0, 0);
            digitalWrite(BASIC1, 1);
            digitalWrite(CARTMODE, 0);
			}
		if (header.indexOf("/action?ROM=G10") != -1)
		{
	        	digitalWrite(KERNAL0, 1);
            digitalWrite(KERNAL1, 0);
            digitalWrite(KERNAL2, 1);
            digitalWrite(BASIC0, 0);
            digitalWrite(BASIC1, 1);
	        	digitalWrite(CARTMODE, 0);
			}
		if (header.indexOf("/action?ROM=G11") != -1)
		{
	        	digitalWrite(KERNAL0, 0);
            digitalWrite(KERNAL1, 0);
            digitalWrite(KERNAL2, 1);
            digitalWrite(BASIC0, 0);
            digitalWrite(BASIC1, 1);
            digitalWrite(CARTMODE,0);
			}
		if (header.indexOf("/action?ROM=G12") != -1)
		{
          	digitalWrite(KERNAL0, 1);
            digitalWrite(KERNAL1, 1);
            digitalWrite(KERNAL2, 0);
            digitalWrite(BASIC0, 0);
            digitalWrite(BASIC1, 1);
            digitalWrite(CARTMODE,0);
			}
		if (header.indexOf("/action?ROM=G13") != -1)
		{
      	  	digitalWrite(KERNAL0, 0);
            digitalWrite(KERNAL1, 1);
            digitalWrite(KERNAL2, 0);
            digitalWrite(BASIC0, 0);
            digitalWrite(BASIC1, 1);
            digitalWrite(CARTMODE, 0);
			}
		if (header.indexOf("/action?ROM=G14") != -1)
		{
	        	digitalWrite(KERNAL0, 1);
            digitalWrite(KERNAL1, 0);
            digitalWrite(KERNAL2, 0);
            digitalWrite(BASIC0, 0);
            digitalWrite(BASIC1, 1);
            digitalWrite(CARTMODE, 0);
			}
		if (header.indexOf("/action?ROM=G15") != -1)
		{
	        	digitalWrite(KERNAL0, 0);
            digitalWrite(KERNAL1, 0);
            digitalWrite(KERNAL2, 0);
            digitalWrite(BASIC0, 0);
            digitalWrite(BASIC1, 1);
            digitalWrite(CARTMODE, 0);
    }
		if (header.indexOf("/action?ROM=G16") != -1)
		{
	          digitalWrite(KERNAL0, 1);
            digitalWrite(KERNAL1, 1);
            digitalWrite(KERNAL2, 1);
            digitalWrite(CARTMODE, 0);
		        digitalWrite(BASIC0, 1);
            digitalWrite(BASIC1, 0);
			}
		if (header.indexOf("/action?ROM=G17") != -1)
		{
	       		digitalWrite(KERNAL0, 0);
            digitalWrite(KERNAL1, 1);
            digitalWrite(KERNAL2, 1);
	        	digitalWrite(BASIC0, 1);
            digitalWrite(BASIC1, 0);
            digitalWrite(CARTMODE, 0);
			}
		if (header.indexOf("/action?ROM=G18") != -1)
		{
	        	digitalWrite(KERNAL0, 1);
            digitalWrite(KERNAL1, 0);
            digitalWrite(KERNAL2, 1);
            digitalWrite(BASIC0, 1);
            digitalWrite(BASIC1, 0);
	        	digitalWrite(CARTMODE, 0);
  	}
		if (header.indexOf("/action?ROM=G19") != -1)
		{
	        	digitalWrite(KERNAL0, 0);
            digitalWrite(KERNAL1, 0);
            digitalWrite(KERNAL2, 1);
            digitalWrite(BASIC0, 1);
            digitalWrite(BASIC1, 0);
            digitalWrite(CARTMODE,0);
			}
		if (header.indexOf("/action?ROM=G20") != -1)
		{
          	digitalWrite(KERNAL0, 1);
            digitalWrite(KERNAL1, 1);
            digitalWrite(KERNAL2, 0);
            digitalWrite(BASIC0, 1);
            digitalWrite(BASIC1, 0);
            digitalWrite(CARTMODE,0);
			}
		if (header.indexOf("/action?ROM=G21") != -1)
		{
        		digitalWrite(KERNAL0, 0);
            digitalWrite(KERNAL1, 1);
            digitalWrite(KERNAL2, 0);
            digitalWrite(BASIC0, 1);
            digitalWrite(BASIC1, 0);
            digitalWrite(CARTMODE, 0);
			}
		if (header.indexOf("/action?ROM=G22") != -1)
		{
	        	digitalWrite(KERNAL0, 1);
            digitalWrite(KERNAL1, 0);
            digitalWrite(KERNAL2, 0);
            digitalWrite(BASIC0, 1);
            digitalWrite(BASIC1, 0);
            digitalWrite(CARTMODE, 0);
			}
		if (header.indexOf("/action?ROM=G23") != -1)
		{
	        	digitalWrite(KERNAL0, 0);
            digitalWrite(KERNAL1, 0);
            digitalWrite(KERNAL2, 0);
            digitalWrite(BASIC0, 1);
            digitalWrite(BASIC1, 0);
            digitalWrite(CARTMODE, 0);
			}
		if (header.indexOf("/action?ROM=G24") != -1)
		{
	   	      digitalWrite(KERNAL0, 1);
            digitalWrite(KERNAL1, 1);
            digitalWrite(KERNAL2, 1);
            digitalWrite(CARTMODE, 0);
	          digitalWrite(BASIC0, 0);
            digitalWrite(BASIC1, 0);
			}
		if (header.indexOf("/action?ROM=G25") != -1)
		{
	        	digitalWrite(KERNAL0, 0);
            digitalWrite(KERNAL1, 1);
            digitalWrite(KERNAL2, 1);
	        	digitalWrite(BASIC0, 0);
            digitalWrite(BASIC1, 0);
            digitalWrite(CARTMODE, 0);
			}
		if (header.indexOf("/action?ROM=G26") != -1)
		{
	        	digitalWrite(KERNAL0, 1);
            digitalWrite(KERNAL1, 0);
            digitalWrite(KERNAL2, 1);
            digitalWrite(BASIC0, 0);
            digitalWrite(BASIC1, 0);
          	digitalWrite(CARTMODE, 0);
			}
		if (header.indexOf("/action?ROM=G27") != -1)
		{
	        	digitalWrite(KERNAL0, 0);
            digitalWrite(KERNAL1, 0);
            digitalWrite(KERNAL2, 1);
            digitalWrite(BASIC0, 0);
            digitalWrite(BASIC1, 0);
            digitalWrite(CARTMODE,0);
			}
		if (header.indexOf("/action?ROM=G28") != -1)
		{
      	  	digitalWrite(KERNAL0, 1);
            digitalWrite(KERNAL1, 1);
            digitalWrite(KERNAL2, 0);
            digitalWrite(BASIC0, 0);
            digitalWrite(BASIC1, 0);
            digitalWrite(CARTMODE,0);
			}
		if (header.indexOf("/action?ROM=G29") != -1)
		{
       	  	digitalWrite(KERNAL0, 0);
            digitalWrite(KERNAL1, 1);
            digitalWrite(KERNAL2, 0);
            digitalWrite(BASIC0, 0);
            digitalWrite(BASIC1, 0);
            digitalWrite(CARTMODE, 0);
			}
		if (header.indexOf("/action?ROM=G30") != -1)
		{
	        	digitalWrite(KERNAL0, 1);
            digitalWrite(KERNAL1, 0);
            digitalWrite(KERNAL2, 0);
            digitalWrite(BASIC0, 0);
            digitalWrite(BASIC1, 0);
            digitalWrite(CARTMODE, 0);
			}
		if (header.indexOf("/action?ROM=G31") != -1)
		{
          	digitalWrite(KERNAL0, 0);
            digitalWrite(KERNAL1, 0);
            digitalWrite(KERNAL2, 0);
            digitalWrite(BASIC0, 0);
            digitalWrite(BASIC1, 0);
            digitalWrite(CARTMODE, 0);
    }
		if (header.indexOf("/noreset?MainSid=SID1PRI") != -1)
		{
	        digitalWrite(SIDMS, 1);
        }
		if (header.indexOf("/noreset?MainSid=SID2PRI") != -1)
		{
	        digitalWrite(SIDMS, 0);
        }
		if (header.indexOf("/noreset?SID2ADDR=SID2D400") != -1)
		{
	        digitalWrite(SIDPS, 1);
        }
		if (header.indexOf("/noreset?SID2ADDR=SID2D420") != -1)
		{
	    	digitalWrite(SIDPS, 0);
		}
		if (header.indexOf("/noreset?SID2DE=SID2DEON") != -1)
		{
	        digitalWrite(SIDDE, 0);
        }
		if (header.indexOf("/noreset?SID2DE=SID2DEOFF") != -1)
		{
	        digitalWrite(SIDDE, 1);
        }
		if (header.indexOf("/noreset?SID2DF=SID2DFON") != -1)
		{
	        digitalWrite(SIDDF, 0);
        }
		if (header.indexOf("/noreset?SID2DF=SID2DFOFF") != -1)
		{
	        digitalWrite(SIDDF, 1);
        }
    if (header.indexOf("/action") != -1)
	  	{
          client.println("Executed, resetting C64!");
          digitalWrite(RESET, 0);
          delay(resetdelay);
          digitalWrite(RESET, 1);
          client.println("<meta http-equiv=\"refresh\" content=\"0;/index.html\" />");
      }
    if (header.indexOf("/noreset") != -1)
	  	{
          client.println("Executed!");
          client.println("<meta http-equiv=\"refresh\" content=\"0;/index.html\" />");
      }
//Start HTML 
          client.println("<!DOCTYPE html><html> \
            <head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"> \
            <body style=\"background-color:#000000; color:#EAEAEA\"> \
            <link rel=\"icon\" href=\"data:,\"> \
            <style> body {font-family: Lucida Console;}</style> \
            </head> \
            <body><h1>Insanity's Terrible ROM Switch</h1> \
            <div style=\"float:left;\">");
//Kernal select form
          client.println("<form action=\"/action\"><label for=\"ROM\">Kernal:</label><br><select name=\"ROM\" id=\"ROM\"> \
              <option value=\"K0\">KERNAL1</option> \
              <option value=\"K1\">KERNAL2</option> \
              <option value=\"K2\">KERNAL3</option> \
              <option value=\"K3\">KERNAL4</option> \
              <option value=\"K4\">KERNAL5</option> \
              <option value=\"K5\">KERNAL6</option> \
              <option value=\"K6\">KERNAL7</option> \
              <option value=\"K7\">KERNAL8</option> \
            </select> \
          <input type=\"submit\"/> \
         </form><p></p>");
//Chargen select form            
        client.println("<form action=\"/noreset\"><label for=\"ROM\">Chargen:</label><br><select name=\"ROM\" id=\"ROM\"> \
              <option value=\"C0\">FONT1</option> \
              <option value=\"C1\">FONT2</option> \
              <option value=\"C2\">FONT3</option> \
              <option value=\"C3\">FONT4</option> \
              <option value=\"C4\">FONT5</option> \
              <option value=\"C5\">FONT6</option> \
              <option value=\"C6\">FONT7</option> \
              <option value=\"C7\">FONT8</option> \
             </select> \
            <input type=\"submit\"/> \
           </form><p></p>");
//game select form           
         client.println("<form action=\"/action\"><label for=\"ROM\">CartRom:</label><br><select name=\"ROM\" id=\"ROM\"> \
              <option value=\"G0\">G0</option> \
              <option value=\"G1\">G1</option> \
              <option value=\"G2\">G2</option> \
              <option value=\"G3\">G3</option> \
              <option value=\"G4\">G4</option> \
              <option value=\"G5\">G5</option> \
              <option value=\"G6\">G6</option> \
              <option value=\"G7\">G7</option> \
              <option value=\"G8\">G8</option> \
              <option value=\"G9\">G9</option> \
              <option value=\"G10\">G10</option> \
              <option value=\"G11\">G11</option> \
              <option value=\"G12\">G12</option> \
              <option value=\"G13\">G13</option> \
              <option value=\"G14\">G14</option> \
              <option value=\"G15\">G15</option> \
              <option value=\"G16\">G16</option> \
              <option value=\"G17\">G17</option> \
              <option value=\"G18\">G18</option> \
              <option value=\"G19\">G19</option> \
              <option value=\"G20\">G20</option> \
              <option value=\"G21\">G21</option> \
              <option value=\"G22\">G22</option> \
              <option value=\"G23\">G23</option> \
              <option value=\"G24\">G24</option> \
              <option value=\"G25\">G25</option> \
              <option value=\"G26\">G26</option> \
              <option value=\"G27\">G27</option> \
              <option value=\"G28\">G28</option> \
              <option value=\"G29\">G29</option> \
              <option value=\"G30\">G30</option> \
              <option value=\"G31\">G31</option> \
          	</select> \
	        <input type=\"submit\"/> \
         </form><p></p>");
          client.println("<form action=\"/noreset\"><label for=\"MainSid\">Main SID:</label><br><select name=\"MainSid\" id=\"MainSid\"> \
            <option value=\"SID1PRI\">SID1 Primary</option> \
            <option value=\"SID2PRI\">SID2 Primary</option> \
            </select> \
          <input type=\"submit\"/> \
          </form><p></p>");

          client.println("<form action=\"/noreset\"><label for=\"SID2ADDR\">SID2 Address:</label><br><select name=\"SID2ADDR\" id=\"SID2ADDR\"> \
            <option value=\"SID2D400\">SID2 @ D400</option> \
            <option value=\"SID2D420\">SID2 @ D420</option> \
            </select> \
          <input type=\"submit\"/> \
          </form><p></p>");

          client.println("<form action=\"/noreset\"><label for=\"SID2DE\">SID2 DE00:</label><br><select name=\"SID2DE\" id=\"SID2DE\"> \
            <option value=\"SID2DEON\">Enable</option> \
            <option value=\"SID2DEOFF\">Disable</option> \
            </select> \
          <input type=\"submit\"/> \
          </form><p></p>");

          client.println("<form action=\"/noreset\"><label for=\"SID2DF\">SID2 DF00:</label><br><select name=\"SID2DF\" id=\"SID2DF\"> \
            <option value=\"SID2DFON\">Enable</option> \
            <option value=\"SID2DFOFF\">Disable</option> \
            </select> \
          <input type=\"submit\"/> \
          </form><p></p>");

          client.println("<form style=\"float:left;\"action=/action\"><input type=\"submit\" value=\"RESET C64\" /><return redirect('/')></form><p></p>");
          client.println("<form style=\"float:left;\"action=/noreset/index.html\"><input type=\"submit\" value=\"Clear Page\" /><return redirect('/')></form>");
          client.println("</body></html>");
          client.println();
            // Break out of loop
            break;
          } else { 
            currentLine = "";
          }
        } else if (c != '\r') {  
          currentLine += c;     
        }
      }
    }
    // Clear the submitted variable and close up shop
    header = "";
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
}
