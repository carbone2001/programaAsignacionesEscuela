#include "LinkedList.h"

typedef struct
{
    int arranqueLogo;
    char nombreUsuario[30];
    char pathListaHermanos[50];
    char pathListaAsignaciones[50];
    char temaConsola[30];
    int primeraVez;
}eConfiguracion;

void showLogo(void);

int controller_loadFromText(char* path , LinkedList* pArrayList);
int controller_loadFromBinary(char* path , LinkedList* pArrayList);

///HERMANOS
int controller_addHermano(LinkedList* pArrayList);
int controller_addAsignacion(LinkedList* listaAsignacion,LinkedList* listaHermanos);
int controller_searchHermano(LinkedList* this);
int controller_searchAsignacion(LinkedList* listaAsignaciones, LinkedList* listaHermanos);
int controller_editHermanos(LinkedList* this);
int controller_editAsignaciones(LinkedList* this, LinkedList* this2);
int controller_imprimirHermanos(LinkedList* listaHermanos);
int controller_imprimirAsignaciones(LinkedList* listaAsignaciones,LinkedList* listaHermanos);
int controller_saveAndExit(LinkedList* listaHermanos,LinkedList* listaAsignaciones,eConfiguracion* config);




int controller_editEmployee(LinkedList* pArrayList);
int controller_removeEmployee(LinkedList* pArrayList);
int controller_ListEmployee(LinkedList* pArrayList);
int controller_sortEmployee(LinkedList* pArrayList);
int controller_saveAsText(char* path , LinkedList* pArrayList);

int controller_saveAsBinary(char* path , LinkedList* pArrayList);


///CONFIGURACIONES
eConfiguracion* configuracion_newParam(int logo,char* userName,char* listaHermanos,char* listaAsignaciones,int primeraVez);
int controller_aplicarConfiguracion(eConfiguracion* config,LinkedList* listaHermanos,LinkedList* listaAsignaciones);
eConfiguracion* cargarConfiguracion(char* path,int aplicar);
int controller_saveHermanosAsignaciones(LinkedList* listaHermanos,LinkedList* listaAsignaciones,eConfiguracion* config);
int controller_configuracion(eConfiguracion* config);
