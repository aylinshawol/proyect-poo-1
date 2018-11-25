#include <iostream>
#include "Cronometro.h"

using namespace std;

void Cronometro::getTiempo(int crono){
    int minutos=crono/60;
    int segundos=crono-60*minutos;
    cout<<"\nTiempo aprox del proceso:  "<<minutos<<":"<<segundos<<endl;
}
void Cronometro::getFaltante(int producctos)
{
    int minutos=(producctos*3)/60 ;
    int segundos=producctos*3-60*minutos;
    cout<<"\nTiempo para esperado para finalizar:  "<<minutos<<":"<<segundos<<endl;
}
