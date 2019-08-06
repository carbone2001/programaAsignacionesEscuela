#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"
#include "inputs.h"
#include "Controller.h"
#include "hermanos.h"
#include "asignaciones.h"
#include <windows.h>
#include <time.h>


int main()
{

    char *option;
    int salir=0;
    time_t t=time(NULL);
    struct tm *tm =localtime(&t);
    //int (*pFunc)();

    option = (char*) malloc (sizeof(char));
    LinkedList* listaHermanos = ll_newLinkedList();
    LinkedList* listaAsignaciones = ll_newLinkedList();
    eConfiguracion* config = (eConfiguracion*)malloc(sizeof(eConfiguracion));
    if(listaHermanos == NULL)
    {
        printf("No se ha podido crear la lista de hermanos. Reinicie el programa.\n\n");
        system("pause");
    }

    if((config = cargarConfiguracion("config.bin",1))!=NULL)
    {
        if(controller_aplicarConfiguracion(config,listaHermanos,listaAsignaciones)==0)
        {

            system("cls");
            printf("\n Un gusto volverlo a ver %s!\n",config->nombreUsuario);
            do
            {


                fflush(stdin);
                printf("\n ******** FECHA DE HOY *******");
                printf("\n ********* %02d/%02d/%04d ********",tm->tm_mday,tm->tm_mon+1,1900+tm->tm_year);
                printf("\n *****************************\n");
                printf("\n MENU:");
                printf("\n 1.  Crear nueva asignacion");
                printf("\n 2.  Agrega hermano");
                printf("\n 3.  Buscar asignacion");
                printf("\n 4.  Buscar hermano");
                printf("\n 5.  Ver lista de hermanos");
                printf("\n 6.  Ver lista de asignaciones");
                printf("\n 7.  Modificar hermano");
                printf("\n 8.  Modificar asignacion");
                printf("\n 9.  Configuracion");
                printf("\n 10. Guardar y Salir\n");
                fflush(stdin);
                printf("\n Ingrese opcion: ");
                scanf("%s",option);


                switch(atoi(option))
                {

                case 1:
                    controller_addAsignacion(listaAsignaciones,listaHermanos);
                    break;
                case 2:
                    controller_addHermano(listaHermanos);
                    break;
                case 3:
                    controller_searchAsignacion(listaAsignaciones,listaHermanos);
                    break;
                case 4:
                    controller_searchHermano(listaHermanos);
                    break;
                case 5:
                    controller_imprimirHermanos(listaHermanos);
                    break;
                case 6:
                    controller_imprimirAsignaciones(listaAsignaciones,listaHermanos);
                    break;
                case 7:
                    controller_editHermanos(listaHermanos);
                    break;
                case 8:
                    controller_editAsignaciones(listaAsignaciones,listaHermanos);
                    break;
                case 9:
                    controller_configuracion(config);
                    break;
                case 10:
                    salir = controller_saveAndExit(listaHermanos,listaAsignaciones,config);
                    break;
                default:

                    system("cls");
                    break;
                }
                system("cls");
            }
            while(salir != 3);
        }
        else
        {
            printf("\n ERROR FATAL! No se pudo aplicar la configuracion de arranque\n");
            system("pause");
        }
    }
    else
    {
        printf("\nERROR FATAL! No se ha podido cargar la configuracion de arranque.\n");
        system("pause");
    }
    free(listaHermanos);
    free(listaAsignaciones);
    free(option);
    free(config);
    return 0;
}



