
#ifndef FECHA_H_INCLUDED
#define FECHA_H_INCLUDED
typedef struct
{
    int dia;
    int mes;
    int anio;

}eFecha;

eFecha strToData(char* str);

eFecha* newFecha(int dia,int mes,int anio);
eFecha* pedirFecha(void);
void printFecha(eFecha* fecha);

#endif // FECHA_H_INCLUDED
