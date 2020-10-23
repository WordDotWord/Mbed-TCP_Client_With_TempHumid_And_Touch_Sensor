# Mbed-TCP_Client_With_TempHumid_And_Touch_Sensor
Temperatur, luftfugtighed og dugpunkt måler


Til brug ved hospitaler. 
Indbygget advarsel ved for høj temperatur, og luftfugtighed der kan give ubehag for personer med eks. astma

Christian Wandsø - Embedded Controller III
September 2020


























Abstrakt 
Formålet med denne opgave er at have et måle og advarselssystem til eks hospitaler. 

Embed DISKO “Navn her” vil have temperatur og luftfugtigheds sensor
https://www.seeedstudio.com/Grove-Temperature-Humidity-Sensor-Pro-AM2302-DHT22.html 
*1 DHT22
3 to 5V power and I/O 2.5mA max current use during conversion (while requesting data)
Good for 0-100% humidity readings with 2-5% accuracy
Good for -40 to 125°C temperature readings ±0.5°C accuracy
No more than 0.5 Hz sampling rate (once every 2 seconds)
Body size: 15.1mm x 25mm x 7.7mm
*1 Data fra https://os.mbed.com/components/Grove-TempHumi-Sensor/

Via TCP/IP forbindelse til Raspberry Pi, vil boardet opsamle data fra sensor, vise data via seriel kommunikation med tilsluttet PC/Bærbar/Laptop. Data vil kunne læses via eks. Putty, og data vil opdateres hvert 5 sekund. 
Der vil komme alarm (ved brug af printf til Putty aflæsning, for lyd se fremtidige løsninger)
Og doktorer, sygeplejerske, læger osv, vil kunne træffe beslutning om at fortsætte operation/vejledning osv, eller tænde for eksternt varme/nedkøling (se fremtidige løsninger)
Opgaven er en del af “Embedded controller III, til 5. Hovedforløb. Opgaven er slået sammen med eks. “Linux rettet mod server og embedded controller” men kun “Embedded Controller III” vil der blive givet karakter for. Derfor det direkte fokus på Mbed boardet, og sensorer, og ikke kommunikation. 




Logbog

9-9: opsætning af raspberry pi efter powerpoint

10-9: arbejde hjemmefra, opsætning af phpmyadmin, mariaDB forståelse 

11-9: Arbejdet hjemmefra, dokumentation, forståelse af linux miljø, Mbed kode

14-9: TCP/IP forståelse

15-9: Port, OSI, general netværk forståelse

16-9: Opsætning Disko board, efter powerpoint

17-9: Sensorer. RGB led, prøvet at finde kode. mbed TCP/IP klient og server med temperatur virker. Opsætning af WiFi på raspberry pi
virker ikke, skal undersøges hvorfor. 

18-9: ikke fundet svar på hvorfor pi ikke kan tilslutte WiFi

21-9: kommunikation mellem mbed og pi. Virker ikke endnu

22-9: Fortsat kommunikation, kan have mbed som server, og tilgå fra en klient, men det er svært at finde noget konkret til pi. 

23-9: WiFi på pi simpel, og simpel http 200 besked kommunikation med rasp

24-9: Gennemgang og forståelse af RTC og SD kort

25-9: RTC implementation, fejlbesked så prøver et andet tidspunkt

28-9: Overført basic 200 ok http kode til sensor main kode -- ændringer i fremvisning af data

29-9: Skreven dokumentatio - /Forside, abstrakt, logbog, anvendte programstrukture

30-9: Skreven dokumentation - logbog, problemformulering, kilder

1-10: fejlbeskeder til mbed, rengøring af kode 
2-10: Skreven dokumentation - logbog, konklusion

5-10: Fremmødt og fået fået rengjort mere kode, givet eksempel af kode til Marco
Problemformulering 
Hospitaler har behov for forskellige temperaturer og luftfugtighed i forskellige situationer. Blandt andet er der forskel på operationsrum hvor patienten er under narkose, og bliver overvåget af læger, og eks. børneafdelinger hvor luftfugtigheden skal holdes nede for at få et behageligt indeklima, også for dem med astma. 

Problemformulering er derfor


1: Hvad kan vi gøre for at overvåge temperatur og luftfugtighed, og give personale mulighed for at se disse data?

2: Vil disse ændringer gøre gavn i hverdagen?


































Anvendte programstrukture
*1 https://www.redhat.com/sysadmin/lamp-server

Linux:
LAMP
“A LAMP (Linux, Apache, MySQL/MariaDB, PHP) server is an all-in-one, single-tier, data-backed, web application server” *1

Via TCP/IP kommunikerer MBED boardet med Raspberry Pi, og der er mulighed for i fremtiden at få vist data på websiden, og håndtering derfra

MBED:
MBED-OS og dertilhørende library som eks. ethernet 
Anette Powerpoint
Eks fra sidste års Embedded Controller III
DHT sensor 

Agile metoder (azure devops) sprints, user cases, scrum


























Konklusion
Hvordan man sætter kommunikation op via “tested and tried” TCP/IP, og for vist relevante informationer på sensorere, og dermed kan træffe relevante beslutninger. 
Dokumentation, og viden om hvad det kræver når det endelige resultat skal kurere til meget specifikt emne.  




































Fremtidige løsninger
Først og fremmest mere direkte kommunikation mellem server og klient. Der skal være mere end bare 200 ok besked tilbage, det næste logiske trin er at få fat i en fil, og derefter kan man arbejde videre på at gemme data fra mbed i database på serveren. 

Derudover skal “knappen” og koden dertil opdateres. Som det er nu, er det bare en tæller, og vores knap er en touch sensor. Det skal selvfølgelig ændres til interruptIn, og den korrekte knap, skal bruges. Dertil kan man kode så hvis man f eks får advarsel for temperatur eller luftfugtighed, så kan man sige “OK” ved at trykke på knappen, og få beskeden til at forsvinde. 

Mine originale tanker med knappen var at kode så forskellige tryk eks 1 tryk = normal stue. 
2 tryk = operationsstue, men dette ville uden tvivl give problemer, og ville være til gene hver gang programmet startes. 






























Kilder
https://os.mbed.com/questions/67211/Why-pcbaud115200-doesnt-work/
https://cheatography.com/davechild/cheat-sheets/linux-command-line/
https://randomnerdtutorials.com/esp32-esp8266-raspberry-pi-lamp-server/
https://randomnerdtutorials.com/raspberry-pi-apache-mysql-php-lamp-server/
Annette Powerpoint
https://os.mbed.com/docs/mbed-os/v6.2/apis/tcpsocket.html
https://os.mbed.com/users/4180_1/notebook/rgb-leds/
