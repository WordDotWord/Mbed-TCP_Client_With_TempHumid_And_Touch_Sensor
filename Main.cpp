#include "mbed.h"
#include "DHT.h"
#include "EthernetInterface.h"
//Dette library får vi fra mbed-os 

EthernetInterface net;
//Declare ethernet interface
DHT sensor(D4, DHT22);
//Sendor, der er forskel på DHT22 og DHT11
DigitalOut led1(LED1);
DigitalIn  button(D2);
int cnt = 0;
//Tæller til vores "knap" som egenligt er en touch sensor


/*
* @file main.cpp
* @brief main som looper vores program
*
* @author Christian Wandsø, Annette, Arm Limited and affiliates
*
* @date 06/10/2020
*/

int main()
{
    //Hele vores program kører i main i loop. Det skal ændres i fremtiden. Har kigget på multithreading, men ser ud til at være en stor opgave i C++
    int error = 0;
    float h = 0.0f, c = 0.0f, f = 0.0f, k = 0.0f, dp = 0.0f, dpf = 0.0f; //float x = 0 has an implicit typecast from int to float.
                                                                        //float x = 0.0f does not have such a typecast.
                                                                       //float x = 0.0 has an implicit typecast from double to float... https://stackoverflow.com/questions/5199338/what-is-the-significance-of-0-0f-when-initializing-in-c
    printf("\r\n");
    printf("\r\n");
    printf("\r\n");
    printf("\r\n");
    printf("\r\n");
    printf("\r\n");
    printf("Velkommen til temp, luftfugtighed,og dugmåler til brug ved hospitaler . Boarded aflæser sensor Vent venligst.\r\n");
    printf("Den sorte knap på bunden af boardet, er en reset knap\r\n");
    printf("\r\n");
    printf("C Wandsø - 2020 Embedded controller III\r\n");
    printf("\r\n");
    
    while(1) {
        wait(2.0f);
        error = sensor.readData();
        if (0 == error) {
            c   = sensor.ReadTemperature(CELCIUS);
            f   = sensor.ReadTemperature(FARENHEIT);
            k   = sensor.ReadTemperature(KELVIN);
            h   = sensor.ReadHumidity();
            dp  = sensor.CalcdewPoint(c, h); 
            dpf = sensor.CalcdewPointFast(c, h);
            wait(5);
            //Efter indlæst data, vent, også connect via ethernet
            net.connect();

            // Show the network address
            SocketAddress a;
            net.get_ip_address(&a);
            // gem socketadress i variabel, og gem ip i variabel. Både socket og get_ip kommer fra hver deres klasse
            printf("\r\n");
            printf("=========================================\r\n");
            printf("__________TEMPERATUR INDE INFORMATION__________\r\n");
            printf("Temperaturen i Celcius: %4.2f\r\n", c);
            printf("Fahrenheit: %4.2f\r\n", f);
            printf("Kelvin: %4.2f\r\n", k);
            printf("\r\n");
            printf("__________LUFTFUGTIUGHED INDE INFORMATION__________\r\n");
            printf("Den relative fugtighed bør ligge på 40 og 60 procent\r\n");
            printf("start 60 sommer, under 45 vinter\r\n");
            printf("Luftfugtighed er: %4.2f, Dugpunkt gennemsnit: %4.2f, Dugpunkt lige nu: %4.2f\r\n", h, dp, dpf);
            printf("__________Internet Data__________\r\n");
            printf("IP address: %s\n", a.get_ip_address() ? a.get_ip_address() : "None");
            printf("\r\n");
            //Print temp, luftfugtighed, og ip adresse
            
            if (c > 27.00) {
                printf("=========================================\r\n");
                printf("For høj remperatur!\r\n");
                led1 = !led1;
                }
                
                if (c < 15.00) {
                printf("=========================================\r\n");
                printf("For lav temperatur!\r\n");
                led1 = !led1;
                }
                
                if (h < 40.00) {
                printf("=========================================\r\n");
                printf("For lav luftfugtighed - Personer med astma!\r\n");
                led1 = !led1;
                }
                
                if (h > 60.00) {
                printf("=========================================\r\n");
                printf("For høj luftfugtighed - Personer med astma!\r\n");
                led1 = !led1;
                }
                //Alle if data fra https://www.carel.com/documents/10191/0/+4000021EN/8ad03ec9-6f9f-4216-8395-b2f95325671f
            
            TCPSocket socket;
            //declare tcp socket
            socket.open(&net);
            //open socket
            
            //net.gethostbyname("ifconfig.io", &a);
           //net.gethostbyname("192.168.1.194", &a);
          //NEDENUNDER! original IP Adresse
         //net.gethostbyname("192.168.1.122", &a);
            net.gethostbyname("10.130.17.47", &a);
            //Raspberry Ip adresse, og vores mbed socket ip
            a.set_port(80);
            //brug standard port 80. Det er ikke så sikkert, så vi skal gøre tanker om at encrypt data.
            //HTTPS on port 443 kan evt bruges. HTTPS er den nye sikre form af http, og skal bruges når der er følsomt data, som eks login.
            socket.connect(a);
            //"socket" er vores TCP socket. Så connect via socket
            
             /* 
             *Annette kode fra "mbed-os-TCPSocket"
             *
             *
             */
            // Send a simple http request
           //char sbuffer[] = "GET / HTTP/1.1\r\nHost: ofconfig.io\r\n\r\n";
          //char sbuffer[] = "GET /mecret/?sw=1 HTTP/1.1\nHost: 192.168.1.194\r\n\r\n";
            char sbuffer[] = "GET / HTTP/1.1\r\nHost: 10.130.17.47\r\n\r\n";
            //GET er en af vores kommandoer i TCP
        //char sbuffer[] = "GET / secret/sw=1 HTTP/1.1\r\nHost: 192.168.1.122\r\n\r\n";
            int scount = socket.send(sbuffer, sizeof sbuffer);
            printf("sent %d [%.*s]\n", scount, strstr(sbuffer, "\r\n") - sbuffer, sbuffer);
            printf("\r\n");
            
            
            //Print at vores get bliver sendt, og hvor stor socket send buffer er
            /*
            The default buffer size is 8 KB. The maximum size is 8 MB (8096 KB). The optimal buffer size depends on several network environment factors including types of switches and systems, 
            acknowledgment timing, error rates and network topology, memory size, and data transfer size. When data transfer size is extremely large, 
            you might want to set the buffer sizes up to the maximum value to improve throughput, reduce the occurrence of flow control, and reduce CPU cost. 
            
            Buffer sizes for the socket connections between the web server and WebSphere Application Server are set at 64KB. In most cases this value is adequate.
            https://www.ibm.com/support/knowledgecenter/SSEQTP_9.0.5/com.ibm.websphere.base.doc/ae/tprf_tunetcpip.html
            */

           // Recieve a simple http response and print out the response line
            char rbuffer[64];
            int rcount = socket.recv(rbuffer, sizeof rbuffer);
            printf("recv %d [%.*s]\n", rcount, strstr(rbuffer, "\r\n") - rbuffer, rbuffer);
            printf("\r\n");
            //Reveive buffera
            
            /*
            the client and server are advertising their window size values as they communicate. 
            Each TCP header will display the most recent window value, which can grow or shrink as the connection progresses. 
            In this example, the client has a TCP receive window of 65,535 bytes, and the server has 5,840. For many applications, 
            since clients tend to receive data rather than send it, clients often have a larger allocated window size. After the handshake, 
            the client sends an HTTP GET request to the server, which is quickly processed. Two response packets from the server arrive at the client, 
            which sends an acknowledgment along with an updated window size
            https://accedian.com/blog/tcp-receive-window-everything-need-know/
            */
    

           // Close the socket to return its memory and bring down the network interface
            socket.close();

                
                
                if (button) {
            cnt++;
            printf("Du rørte ved en knap %d\r\n", cnt);
            while(button);
            }
            
        } 
         
        else {
            printf("Fejl! Har du tilsluttet korrekt?: %d\r\n", error);
        }
       
    }
}
//https://developer.mozilla.org/en-US/docs/Web/HTTP/Session
//https://www.codecademy.com/articles/http-requests
