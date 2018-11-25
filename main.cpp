#include <iostream>

//Libreria utilizada para modificar hacer minuscula una letra (tolower())
#include <cctype>

//Libreria utilizada para dar un tiempo de espera (Sleep();)
#include <Windows.h>

//Libreria utilizada para dar un tiempo de espera (getch();)
#include <conio.h>

//Libreria utilizada para salir del programa (exit(0);)
#include <stdlib.h>

//Libreria para nombrar el producto
#include <string>

//Clase utilizada para crear una conexion serial entre arduino y c++
#include "SerialClass.h"

//Clase utilizada para hacer el promedio de cada color
#include "Promedio.h"

#include "Cronometro.h"

using namespace std;

int main () {
    //Titulo de la ventana
    SetConsoleTitle("Separador De Colores");
    //Puerto serial
    Serial* Arduino = new Serial("COM4");

    //Cadenas para el arduino
    char Encender[2]="e";
    char Pausar[2]="p";
    char Color[2] = "\0";

    //Productos
    string producto1;
    int Npiezas1{0};
    string producto2;
    int Npiezas2{0};

    char respuesta;

    Cronometro tiempo;

    //Contadores
    int cronos{0};
    int blanco{0};
    int oscuro{0};
    int otros{0};


    /*Se le pregunta al usuario el nombre de los dos productos a separar, al ingresar el ultimo nombre, se enviara
    al Arduino que una "s" para que los dos programas se inicien al mismo tiempo*/
    cout<<"Introduzca el nombre del primer \"producto\""<<endl;
    cin>>producto1;
    cout<<"Introduzca el numero de piezas a separar "<<endl;
    cin>>Npiezas1;
    cout<<"Introduzca el nombre del segundo \"producto\""<<endl;
    cin>>producto2;
    cout<<"Introduzca el numero de piezas a separar "<<endl;
    cin>>Npiezas2;

    Arduino->WriteData(Encender,sizeof(Encender)-1);

    /*Mientras el Arduino este conectado se realizara el codigo*/
    while( Arduino->IsConnected() ){
        Sleep(1000);
        cronos++;
        system("cls");

        /*El Arduino, segun el color que detecte mandara una letra (B-blanco,A-amarilloy O-otros)
        el programa la leera y la guardara en la cadena "Color" para ser analizada y poner contador*/
        Arduino->ReadData(Color,sizeof(Color)-1);
        Sleep(1000);
	    cronos++;

	    switch(Color[0]){
        case 'B':
            system("color 07");
            blanco++;
            cout<<producto1<<endl<<endl;
            break;
        case 'N':
            system("color 01");
            oscuro++;
            cout<<producto2<<endl<<endl;
            break;
        case 'A':
            system("color 06");
            otros++;
            cout<<"Producto no identificado\n"<<endl;
            break;
        }
        //Muestra la cantidades de productos separados y muestra el promedio
        Promedio pro(blanco,oscuro,otros,blanco+oscuro+otros);
        cout<<producto1<<":  "<<blanco <<"\tPromedio: "<<pro.calculoBlanco()<<"%"<<endl
            <<producto2<<":  "<<oscuro <<"\tPromedio: "<<pro.calculoOscuro()<<"%"<<endl
            <<"PNI: "<<otros<<"\tPromedio: "<<pro.calculoOtros()<<"%"<<endl
            <<"\nPNI.-Productos no identificados\n"<<endl;

        tiempo.getFaltante(Npiezas1+Npiezas2-blanco-oscuro);
        //Se pone tope de productos a separar para parar el proceso o si detecta demaciados errores
        if(blanco==Npiezas1){
            Arduino->WriteData(Pausar,sizeof(Pausar)-1);
            cout<<"se separaron "<<Npiezas1<<" piezas de "<<producto1<<endl;
            tiempo.getTiempo(cronos);

            if (respuesta!='s'){
                cout<<"Presione enter para continuar"<<endl;
                getch();
                respuesta='s';
                Arduino->WriteData(Encender,sizeof(Encender)-1);
            }
            else{
                exit(0);
            }
        }

        else if(oscuro==Npiezas2){
            Arduino->WriteData(Pausar,sizeof(Pausar)-1);
            cout<<"se separaron "<<Npiezas2<<" piezas de "<<producto2<<endl;
            tiempo.getTiempo(cronos);

            if (respuesta!='s'){
                cout<<"Presione enter para continuar"<<endl;
                getch();
                respuesta='s';
                Arduino->WriteData(Encender,sizeof(Encender)-1);
            }
            else{
                exit(0);
            }
        }
        else if(otros==10){
            cout<<"Se detectaron 10 PNI, por favor revise el proceso anterior"<<endl;
            tiempo.getTiempo(cronos);
            cout<<"Presione enter para continuar"<<endl;
            getch();
        }
    Sleep(1000);
	cronos++;
	}
}
