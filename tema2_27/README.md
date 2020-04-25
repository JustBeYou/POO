Hotel Management System
===
## Documentatie
Cerinta a fost sa se scrie un program de management pentru rezervari intr-un hotel. Pot exista mai multe tipuri de camere si servicii pe care le pot solicita clientii. Se suporta de asemenea anularea unei rezervari. Clasele sunt implementate intr-o maniera extensibila si generica, astfel se pot adauga tipuri noi de camere si servicii fara a modifica codul deja existent.

Definim urmatoarele entitati:
1. Camera reprezentata de clasa de baza `RoomType` - aceasta implementeaza functionalitatile generale ale oracarei camere, de exemplu: verificarea daca este libera, daca se poate imparti sau nu, locurile disponibile, ocuparea/eliberarea locurilor, afisarea continutului. Din aceasta clasa s-au mostenit clase precum `BedRoom`, `Apartment` sau `Restaurant` si s-au utilizat metode virtuale pentru implementarea comportamentului specific (de exemplu metoda `write` pentru afisare sau metoda `clone` pentru copierea unui obiect). De asemenea, orice camera contine o lista de dotari, aceasta fiind stocata intr-un container STL de tip `set`.
2. Un serviciu oferit de hotel este reprezentat de un set de camere cu anumite dotari. Pentru aceasta, avem clasa `ServiceManager` care se ocupa de management-ul mai multor camere diferite, dar care apartin aceluiasi serviciu. Managerul permite interactionarea cu camerele prin ocuparea sau eliberarea lor dar si o serie de interogari despre capacitatile disponibile. Camere sunt tinute in mai multe containere specializate pentru a eficientiza operatiile. (de exemplu lista pentru camerele goale, hashmap pentru dotarile disponibile totale, etc). Ca exemplu concret avem serviciul `BREAKFAST` pe care l-ar putea solicita un client, deci vom avea un `ServiceManager` cu numele corespunzator care se va ocupa de o serie de camere de tip `Restaurant`.
3. Hotelul se ocupa de evidenta tuturor serviciilor implementand algoritmul de rezervare/eliberare a camerelor. Clasa `Hotel` retine un vector de zile, fiecare zi avand o copie a intregii situatii a hotelului (toate `ServiceManager`-ele, respectiv camerele lor). Algoritmul de ocupare este in mare parte naiv cu mici optimizari deoarece pare a fi o problema din clasa NP. 

Mai jos se observa un exemplu de output pentru cererile din fisierul `hotel.txt`.

## Sample output for `hotel.txt`:
```
BOOKING
--------------------------------------------------------
Booking #1, time period 0-4:
For ACCOMODATION: 1 2 3 4
For BREAKFAST: 1
For MEETINGS: 3
--------------------------------------------------------

CANCEL
--------------------------------------------------------
Invalid action when cancelling a booking.
There is no booking with this id!
--------------------------------------------------------

CANCEL
--------------------------------------------------------
Booking 1 was canceled.
--------------------------------------------------------

BOOKING
--------------------------------------------------------
Booking #2, time period 0-4:
For ACCOMODATION: 5 1 2 3 4
For BREAKFAST: 1
For MEETINGS: 4
--------------------------------------------------------

BOOKING
--------------------------------------------------------
Booking #3, time period 5-9:
For ACCOMODATION: 1 2 3 4
--------------------------------------------------------

BOOKING
--------------------------------------------------------
Couldn't book this year :(
--------------------------------------------------------

BOOKING
--------------------------------------------------------
Booking #4, time period 10-14:
For ACCOMODATION: 1 2
For BREAKFAST: 1
--------------------------------------------------------

BOOKING
--------------------------------------------------------
Booking #5, time period 10-14:
For ACCOMODATION: 3 4
For BREAKFAST: 1
--------------------------------------------------------

Welcome to the Hotel California
Our services for day 10 are:
 -  has 5 rooms.
Bedroom #1 : 2/2
Bedroom #2 : 1/2
Bedroom #3 : 2/2
Apartment #4 : 1/4
Apartment #5 : 0/4

 -  has 2 rooms.
Restaurant #1 : 6/100
Restaurant #2 : 0/30

 -  has 4 rooms.
Conference room #1 : 0/30
Features:
Conference room #2 : 0/50
Features:
 - HAS_SCENE
Conference room #3 : 0/30
Features:
 - HAS_SCENE
 - HAS_TABLES
Conference room #4 : 0/30
Features:
 - HAS_PROJECTOR
 - HAS_SCENE
 - HAS_TABLES
```
