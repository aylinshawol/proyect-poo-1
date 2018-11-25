#ifndef PROMEDIO_H
#define PROMEDIO_H


class Promedio
{
    public:
        Promedio(int,int,int,float);
        ~Promedio();
        float calculoBlanco(){return (blanco/total)*100;};
        float calculoOscuro(){return (oscuro/total)*100;};;
        float calculoOtros(){return (otros/total)*100;};
    private:
        int blanco;
        int oscuro;
        int otros;
        float total;

};

#endif // PROMEDIO_H
