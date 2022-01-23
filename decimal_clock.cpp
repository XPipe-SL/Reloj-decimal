#include <iostream>
#include <sys/time.h>
#include <chrono>
#include <thread>

using namespace std;

int main(){
    timeval ahora;
    struct tm * hoyEpocS;
    time_t hoyEpoc;
    int msHoy, dSec, dMin, dHour;

    while (true) {
        //Tiempo en segundos desde EPOC + milisegundos
        gettimeofday(&ahora , NULL);

        //Struct de la fecha y hora actual en UTC
        hoyEpocS = gmtime(&ahora.tv_sec);

        //Ajustamos a 00:00
        hoyEpocS->tm_hour = 0; hoyEpocS->tm_min = 0; hoyEpocS->tm_sec = 0;

        //Calculamos los segundos desde EPOC hasta 00:00 de hoy
        hoyEpoc = timegm(hoyEpocS);

        //Milisegundos desde 00:00 de hoy
        msHoy = (ahora.tv_sec - hoyEpoc)*1000 + ahora.tv_usec/1000;
        
        //Ajuste por el tiempo solar en París
        //La medianoche solar en París ocurre 9 minutos 20,935 segundos = 560935 mS antes
        //Y hay que sumarlos
        //Si nos pasamos del número de mS diario pues se resta
        msHoy += 560935;
        msHoy %= 24*60*60*1000;

        dSec = msHoy/864;
        dMin = dSec/100;
        dSec %=100;
        dHour = dMin/100;
        dMin %=100;

        cout << dHour << ':' << (dMin<10?'0':'\0') << dMin << ':' << (dSec<10?'0':'\0') << dSec << endl;

        this_thread::sleep_for(chrono::milliseconds( ((msHoy/864+1)*864) - msHoy ));
        system("clear");
    }
}