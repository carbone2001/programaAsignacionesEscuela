#include "LinkedList.h"

typedef struct
{
    char fondo;
    char fuente;
    int arranqueLogo;
    char nombreUsuario[30];
    char pathListaHermanos[30];
    char pathListaAsignaciones[30];
    int primeraVez;
}eConfiguracion;


int controller_loadFromText(char* path , LinkedList* pArrayList);
int controller_loadFromBinary(char* path , LinkedList* pArrayList);
int controller_addHermano(LinkedList* pArrayList);
int controller_addAsignacion(LinkedList* listaAsignacion,LinkedList* listaHermanos);
int controller_searchHermano(LinkedList* this);
int controller_searchAsignacion(LinkedList* listaAsignaciones, LinkedList* listaHermanos);
int controller_editEmployee(LinkedList* pArrayList);
int controller_removeEmployee(LinkedList* pArrayList);
int controller_ListEmployee(LinkedList* pArrayList);
int controller_sortEmployee(LinkedList* pArrayList);
int controller_saveAsText(char* path , LinkedList* pArrayList);

int controller_saveAsBinary(char* path , LinkedList* pArrayList);

int controller_asignarTipos(LinkedList* this,int(*pFn)(void*elementA, void*elementB));


eConfiguracion* configuracionDeArranque(int iniciar);
