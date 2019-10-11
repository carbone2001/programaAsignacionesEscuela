#include "fecha.h"
#include "LinkedList.h"
#ifndef ASIGNACIONES_H_INCLUDED
#define ASIGNACIONES_H_INCLUDED

typedef struct
{
    int idHermano;
    char sala;
    int asignacion; ///1. Lectura ** / 2. Prim. Conv(1) / 3. Prim. Conv(2) / 4. Prim. Conv(3)  **   /5. Prim. Rev(1) /6. Prim. Rev(2) /7. Prim. Rev(3) ** /8. Seg. Rev(1) /9. Seg. Rev(2) /10. Seg. Rev(3) /11. Ter. Rev(1) /12. Ter. Rev(2) /13. Ter. Rev(3)/14. Curso biblico /15. Discurso /16. Ayudante
    //int ayudante;
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
int asignacion_sortByData(eAsignacion* this, eAsignacion* this2);
int asignacion_sortAsignacion(eAsignacion* element1, eAsignacion* element2);


void harcodearAsignaciones(LinkedList* this);
void printAsignacion(eAsignacion* elemento,LinkedList* listaHermanos);
void printAsignaciones(LinkedList* this,LinkedList* listaHermanos);

#endif // ASIGNACIONES_H_INCLUDED
