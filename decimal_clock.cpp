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
        //Tiempo en segundos desde EPOCH + milisegundos
        gettimeofday(&ahora , NULL);

        //Tiempo desde la última media noche UTC en segundos
        //Se asume que el EPOCH está en UTC
        ahora.tv_sec %= 24*60*60;

        //Milisegundos desde 00:00 de hoy
        msHoy = ahora.tv_sec*1000 + ahora.tv_usec/1000;
        
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

        chrono::time_point<chrono::steady_clock> tick = chrono::steady_clock::now() + chrono::milliseconds(((msHoy/864+1)*864) - msHoy);
        this_thread::sleep_until(tick);
        system("clear");
    }
}