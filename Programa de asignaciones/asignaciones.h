#include "fecha.h"
#include "LinkedList.h"
#ifndef ASIGNACIONES_H_INCLUDED
#define ASIGNACIONES_H_INCLUDED

typedef struct
{
    int idHermano;
    char sala;
    int asignacion; ///1. Primera visita/2.Revisita/3. Estudio biblico/4.Lectura biblica/5. Discurso biblico
    eFecha fecha;
}eAsignacion;

eAsignacion* asignacion_new(void);
eAsignacion* asignacion_newParametros(int* idHermano,int* asignacion,char* sala,eFecha* fecha);
int asignacion_searchId(eAsignacion* element1, eAsignacion* element2);
int asignacion_searchFecha(eAsignacion* element1, eAsignacion* element2);
int asignacion_searchSala(eAsignacion* element1, eAsignacion* element2);
int asignacion_searchAsignacion(eAsignacion* element1, eAsignacion* element2);
eAsignacion* asignacion_searchByIdData(int* id,eFecha* fecha,LinkedList* this);
int asignacion_searchFechaMes(eAsignacion* element1, eAsignacion* element2);


void harcodearAsignaciones(LinkedList* this);
void printAsignacion(eAsignacion* elemento);
void printAsignaciones(LinkedList* this);
#endif // ASIGNACIONES_H_INCLUDED
