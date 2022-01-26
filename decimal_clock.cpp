#include <iostream>
#include <chrono>
#include <thread>

using namespace std;
using namespace std::chrono;

int main(){
    time_point<system_clock> tick = system_clock::now();
    auto duration = tick.time_since_epoch();

    auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(duration);
    duration -= microseconds%1000;
    tick -= microseconds%1000;
    auto nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(duration);
    duration -= nanoseconds%1000;
    tick -= microseconds%1000;

    using Days = std::chrono::duration<int, std::ratio<86400>>;
    Days days = std::chrono::duration_cast<Days>(duration);
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration);

    int msHoy, dSec, dMin, dHour;

    while (true) {
        //Tiempo desde EPOCH
        duration = tick.time_since_epoch();

        //Tiempo desde la última media noche UTC en segundos
        //Se asume que el EPOCH está en UTC
        days = std::chrono::duration_cast<Days>(duration);
        duration -= days;

        //Milisegundos desde 00:00 de hoy
        milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration);
        msHoy = milliseconds.count();
        
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

        tick += chrono::milliseconds(((msHoy/864+1)*864) - msHoy);
        this_thread::sleep_until(tick);
        system("clear");
    }
}