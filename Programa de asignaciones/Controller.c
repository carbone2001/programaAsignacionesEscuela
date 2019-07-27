#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <ctype.h>
#include "Controller.h"
#include "LinkedList.h"
#include "hermanos.h"
#include "asignaciones.h"
#include "parser.h"
#include "inputs.h"

/** \brief Carga los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayList LinkedList*
 * \return int
 */
int controller_loadFromText(char* path, LinkedList* pArrayList)
{
    int error = 1;
    FILE * file;

    file = fopen(path,"r");
    if(file!=NULL && pArrayList != NULL)
    {
        error = parser_FromText(file,pArrayList);
    }
    system("cls");
    if(error)
    {
        printf("\nError al cargar el texto de archivo \n");
    }
    else
    {
        printf("\nLa carga se ha realizado con exito \n");
    }
    fclose(file);
    return error;
}

/** \brief Carga los datos de los empleados desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayList LinkedList*
 * \return int
 *
 */
int controller_loadFromBinary(char* path, LinkedList* pArrayList)
{
    FILE * pFile;
    int error;
    pFile = fopen(path,"rb");
    error = parser_FromBinary(pFile,pArrayList);
    fclose(pFile);
    system("cls");
    if(error)
    {
        printf("\nError al cargar desde el archivo binario.\n");
    }
    else
    {
        printf("\nSe ha cargado desde el archivo binario con exito!!\n");
    }
    return error;
}

/** \brief Alta de empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_addHermano(LinkedList* pArrayList)
{

    int error;
    error = 1;
    eHermano* nuevoHno;

    int id = otorgarID(pArrayList);
    char nombre[30];
    char apellido[30];
    char telefono[20];
    int* servMinist = (int*) malloc (sizeof(sizeof(int)));
    int* privilegio = (int*) malloc (sizeof(sizeof(int)));
    eAsignacion* ultimaAsignacion = asignacion_new();
    int* estado=(int*) malloc (sizeof(sizeof(int)));
    *estado = 1;

    system("cls");

    printf("\n *** AGREGAR HERMANO ***");
    if(getString(nombre,"\nIngrese el nombre del hermano: ","El nombre no debe superar los 30 caracteres",30)==0 )
    {
        strlwr(nombre);
        nombre[0] = toupper(nombre[0]);
        if(getString(apellido,"\nIngrese el apellido del hermano: ","El apellido no debe superar los 30 caracteres",30)==0)
        {
            strlwr(apellido);
            apellido[0] = toupper(apellido[0]);
            if(getString(telefono,"\nIngrese el telefono del hermano: ","El telefono no debe superar los 20 caracteres",20)==0)
            {
                if(getIntIntentos(servMinist,"\nIngrese su servicio de ministerio. (1)publicador /(2) P. Auxiliar /(3) P. Regular /(4) P. Especial \nIngrese opcion: ","\nOPCION INCORRECTA!\n",1,4,1)==0)
                {
                    if(getIntIntentos(privilegio,"\nIngrese su privilegio. (1)anciano /(2) Siervo Ministerial / (3) Ninguno \nIngrese opcion: ","\nOPCION INCORRECTA!\n",1,3,1)==0)
                    {
                        nuevoHno = hermano_newParametros(&id,nombre,apellido,telefono,servMinist,privilegio,ultimaAsignacion,estado);
                        printHermano(nuevoHno);
                        if(nuevoHno != NULL)
                        {
                            error = ll_add(pArrayList,nuevoHno);
                        }
                    }
                }
            }
        }
    }
    system("cls");
    if(error)
    {
        printf("\nHubo un error al agregar el hermano\n");
        system("pause");
    }
    else
    {
        printf("\nEl hermano ha sido agregado exitosamente\n");
        system("pause");
    }

    return error;
}

/** \brief Modificar datos de empleado
 *
 * \param path char*
 * \param pArrayList LinkedList*
 * \return int
 *
 */
int controller_addAsignacion(LinkedList* listaAsignaciones,LinkedList* listaHermanos)
{
    int error = 1;

    int* id;
    char* sala;
    int* asignacion;
    eFecha* fecha;
    eAsignacion* new = (eAsignacion*) malloc (sizeof(eAsignacion));
    eHermano* hno = (eHermano*) malloc (sizeof(eHermano));

    system("cls");
    if(listaAsignaciones != NULL && listaHermanos != NULL)
    {

        if( tolower((getChar("\n Desea agregar una nueva asignacion? (s/n): "))=='s'))
        {
            id = (int*) malloc (sizeof(int));
            if(getInt(id,"\nIngrese ID del hermano: ","\nEl ID ingresado es invalido",1,999) == 0 && (hno = hermano_searchGetById(id,listaHermanos))!=NULL && hno->estado != 0)
            {

                sala = (char*) malloc (sizeof(char));
                *sala = getChar("\nIngrese la sala (A/B): ");
                *sala = toupper(*sala);
                if(*sala == 'A' || *sala == 'B' || *sala == 'a' || *sala == 'b')
                {
                    asignacion = (int*) malloc (sizeof(int));
                    if(getInt(asignacion,"\nIngrese numero de asignacion (1. Primera Conversarion / 2. Revisita / 3. Estudio Biblico / 4. Lectura de la Biblia / 5. Discurso biblico)\n Ingrese opcion: ","\nOpcion Invalida!",0,5) == 0)
                    {
                        printf("\nIngrese fecha de asignacion:");
                        fecha = (eFecha*) malloc(sizeof(eFecha));
                        if((fecha=pedirFecha())!=NULL)
                        {
                            new = asignacion_newParametros(id,asignacion,sala,fecha);
                            if(new != NULL)
                            {

                                error = ll_add(listaAsignaciones,new);

                            }
                        }
                    }
                }
            }
            else
            {
                printf("\nNo se ha encontrado el hermano del ID %d\n",*id);
            }
        }
        else
        {
            printf("\n Se ha cancelado la creacion de nueva asignacion\n");
            system("pause");
            error = 2;
        }
    }

    if(error == 1)
    {
        printf("\n No se ha podido agregar la asignacion\n");
        system("\npause");
    }
    else if(error==0)
    {
        printf("\n Se ha creado la asignacion exitosamente!\n");
        setUltAsig(hno,new);
        printf("   ID del hermano       Sala            Asignacion                  Fecha\n");
        printAsignacion(new);
        system("pause");
    }

    return error;



}

/** \brief Baja de empleado
 *
 * \param path char*
 * \param pArrayList LinkedList*
 * \return int
 *
 */

int controller_removeEmployee(LinkedList* pArrayList)
{
    int error = -1;
    eHermano* hno;
    int id;
    char option;
    int found = 0;
    printf("\nIngrese ID del empleado a eliminar: ");
    scanf("%d",&id);

    for(int i = 0; i<ll_len(pArrayList); i++)
    {
        hno = ll_get(pArrayList,i);
        if(hno->id == id)
        {
            found = i;
            break;
        }
    }
    if(found)
    {
        printf("\nEl ID ingresado corresponde a: ");
        printf("%s",hno->nombre);
        printf("\nDesea proseguir con la eliminacion? (s/n): ");
        fflush(stdin);
        scanf("%c",&option);
        if(option == 's')
        {
            if(ll_remove(pArrayList,found))
            {
                printf("\nNo se ha podido eliminar al empleado");
            }
            else
            {
                printf("\nLa eliminacion ha sido exitosa");
            }
        }
        else
        {
            printf("\nSe ha cancelado la eliminacion");
        }
    }
    else
    {
        printf("\nNo se ha encontrado al empleado de ID: %d",id);
    }

    return error;
}



/** \brief Ordenar empleados
 *
 * \param path char*
 * \param pArrayList LinkedList*
 * \return int
 *
 */

int controller_sortEmployee(LinkedList* pArrayList)
{
    int error = 1;
    eHermano* empI;
    eHermano* empJ;
    eHermano* aux;
    aux = (eHermano*) malloc (sizeof(eHermano));
    if(aux != NULL)
    {
        for(int i = 0; i<ll_len(pArrayList)-1; i++)
        {
            empI = ll_get(pArrayList,i);
            for(int j=i+1; j<ll_len(pArrayList); j++)
            {
                empJ = ll_get(pArrayList,j);
                if(strcmp(empI->nombre,empJ->nombre)>0)
                {
                    aux = empI;
                    empI = empJ;
                    empJ = aux;
                    error = ll_set(pArrayList,i,empI);
                    error = ll_set(pArrayList,j,empJ);
                }
            }
            if(i<ll_len(pArrayList)-1)
            {
                error = 0;
            }
        }
    }
    if(error)
    {
        system("cls");
        printf("\nATENCION! Hubo un error en el ordenamiento.");
    }
    else
    {
        system("cls");
        printf("\nEl ordenamiento se ha realizado con exito!");
    }
    free(aux);
    return 1;
}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayList LinkedList*
 * \return int
 *
 */

int controller_saveAsText(char* path, LinkedList* pArrayList)
{


    FILE* pFile;
    eHermano* hno; ///EL PUNTERO AL TIPO DE ELEMENTO ESTRUCTURA
    int error = 0;

    pFile = fopen (path,"w");
    if(pFile != NULL)
    {
        ///SE IMPRIMEN LOS NOMBRES DE CADA CAMPO
        fprintf(pFile,"\nid,dominio,anio\n");
        for(int i=0; i<ll_len(pArrayList); i++)
        {
            hno = ll_get(pArrayList,i);
            if(hno==NULL)
            {
                error = 1;
                break;
            }
            ///SE IMPRIMEN LOS DATOS
            //fprintf(pFile,"%d,%s,%d\n",hno->id,hno->dominio,hno->anio);
        }
        system("pause");
    }
    else
    {
        error = 1;
    }
    fclose(pFile);
    free(hno);
    return error;
}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayList LinkedList*
 * \return int
 *
 */

int controller_saveAsBinary(char* path, LinkedList* pArrayList)
{
    FILE * pFile;
    eHermano* hno; ///Puntero a estructura
    int error = 1;
    int cant;

    hno = (eHermano*) malloc (sizeof(eHermano));
    if(hno != NULL)
    {
        pFile = fopen (path,"wb");
        if(pFile != NULL)
        {
            for(int i=1; i<ll_len(pArrayList); i++)
            {
                fseek(pFile,0L,SEEK_END);
                hno = ll_get(pArrayList,i);
                if(hno == NULL)
                {
                    break;
                }
                if((cant = fwrite(hno,sizeof(eHermano),1,pFile))!=1)
                {
                    break;
                }
                if(i==ll_len(pArrayList)-1)
                {
                    error = 0;
                }
            }
            fclose(pFile);
        }
    }
    system("cls");
    if(error)
    {
        printf("\nError al cargar como binario\n");
    }
    else
    {
        printf("\nLa carga se ha realizado con exito!!\n");
    }
    return error;
}

eConfiguracion* configuracion_newParam(int logo,char* userName,char* listaHermanos,char* listaAsignaciones,int primeraVez)
{
    eConfiguracion* config = (eConfiguracion*)malloc(sizeof(eConfiguracion));

    if(config != NULL && userName != NULL && listaAsignaciones != NULL && listaHermanos != NULL)
    {
        config->arranqueLogo=logo;
        strcpy(config->nombreUsuario,userName);
        strcpy(config->pathListaHermanos,listaHermanos);
        strcpy(config->pathListaAsignaciones,listaAsignaciones);
        config->primeraVez=primeraVez;
        strcpy(config->temaConsola,"COLOR F0");
    }

    return config;
}

int controller_searchHermano(LinkedList* this)
{
    int error = 1;
    int len;
    eHermano* hno = (eHermano*)malloc(sizeof(eHermano));
    char* string;
    int* num;
    int* indices = (int*) malloc (sizeof(int));
    int indice;
    int (*pFunc)();
    int opcion=0;


    while(opcion != 6)
    {
        system("cls");
        printf("\n*** Buscar hermano ***\n");
        printf("\n1. Buscar por nombre");
        printf("\n2. Buscar por apellido");
        printf("\n3. Buscar por privilegio");
        printf("\n4. Buscar por servicio del ministerio");
        printf("\n5. Buscar por ID");
        printf("\n6. Volver al menu\n");
        getInt(&opcion,"\nIngrese opcion: ","\nOpcion de invalida!\n",1,6);
        len=-1;
        switch(opcion)
        {
        case 1:
            string = (char*) malloc (sizeof(char)*30);
            if(getString(string,"\nIngrese nombre: ","\nEl nombre ingresado es invalido!",30)==0)
            {
                strlwr(string);
                string[0] = toupper(string[0]);
                strcpy(hno->nombre,string);
                pFunc = hermano_searchName;
                indices = ll_search(this,hno,pFunc,&len);
            }
            break;
        case 2:
            string = (char*) malloc (sizeof(char)*30);
            if(getString(string,"\nIngrese apellido: ","\nEl nombre ingresado es invalido!",30)==0)
            {
                strlwr(string);
                string[0] = toupper(string[0]);
                strcpy(hno->apellido,string);
                pFunc = hermano_searchSurname;
                indices = ll_search(this,hno,pFunc,&len);
            }
            break;
        case 3:
            num = (int*) malloc (sizeof(int));
            if((getIntIntentos(num,"\nIngrese su privilegio. (1)anciano /(2) Siervo Ministerial / (3) Ninguno \nIngrese opcion: ","\nOPCION INCORRECTA!\n",1,3,1)==0))
            {
                hno->privilegio=*num;
                pFunc = hermano_searchPrivilegio;
                indices = ll_search(this,hno,pFunc,&len);
            }
            break;
        case 4:
            num = (int*) malloc (sizeof(int));
            if(getIntIntentos(num,"\nIngrese su servicio de ministerio. (1)publicador /(2) P. Auxiliar /(3) P. Regular /(4) P. Especial \nIngrese opcion: ","\nOPCION INCORRECTA!\n",1,4,1)==0)
            {
                hno->servMinist=*num;
                pFunc = hermano_searchServicio;
                indices = ll_search(this,hno,pFunc,&len);
            }
            break;
        case 5:
            num = (int*) malloc (sizeof(int));
            if(getIntIntentos(num,"\nIngrese ID: ","\nID invalido!\n",1,999,1)==0)
            {
                hno->id=*num;
                pFunc = hermano_searchId;
                indices = ll_search(this,hno,pFunc,&len);
            }
            break;

        default:
            system("cls");
            break;
        }
        if(len==0)
        {
            printf("\nNo se ha encontrado resultados para: '%s'\n",string);
            system("pause");
            free(string);
            free(num);
        }
        else if(len != 0 && len != -1 && indices!=NULL)
        {
            printf("   ID          Nombre        Apellido             Telefono      Serv. Minist           Privilegio      Ultima Asignacion              Estado\n");
            for(int i=0; i<len; i++)
            {
                indice = indices[i];
                printHermano(ll_get(this,indice));

            }
            printf("\n");
            free(string);
            free(num);
            system("pause");
        }
    }
    free(indices);
    free(hno);

    return error;
}

int controller_searchAsignacion(LinkedList* listaAsignaciones, LinkedList* listaHermanos)
{
    int error = 1;
    int len;
    eAsignacion* asig = (eAsignacion*) malloc (sizeof(eAsignacion));
    eHermano* hno = (eHermano*)malloc(sizeof(eHermano));
    char* letra;
    int* num;
    eFecha* fecha;
    int* indices;// = (int*) malloc (sizeof(int));
    int indice;
    int (*pFunc)();
    int opcion=0;


    while(opcion != 5)
    {
        system("cls");
        printf("\n*** Buscar Asignaciones ***\n");
        printf("\n1. Buscar por ID de hermano");
        printf("\n2. Buscar por fecha");
        printf("\n3. Buscar por sala");
        printf("\n4. Buscar por numero de asignacion");
        printf("\n5. Volver al menu\n");
        getInt(&opcion,"\nIngrese opcion: ","\nOpcion de invalida!\n",1,5);
        len=-1;
        switch(opcion)
        {
        case 1:
            num = (int*) malloc (sizeof(int));
            if((getIntIntentos(num,"\nIngrese ID del hermano: ","\nID invalido!\n",1,999,1)==0))
            {
                asig->idHermano=*num;
                pFunc = asignacion_searchId;
                indices = ll_search(listaAsignaciones,asig,pFunc,&len);
            }
            hno = hermano_searchGetById(num,listaHermanos);
            if(hno != NULL)
            {
                printf("\n\n%s %s \n",hno->apellido,hno->nombre);
            }
            break;
        case 2:
            printf("\nIngrese fecha: ");
            fecha = pedirFecha(); ///Dentro de la funcion ya se inicializa la variable fecha

            if(fecha != NULL)
            {
                asig->fecha=*fecha;
                pFunc = asignacion_searchFecha;
                indices = ll_search(listaAsignaciones,asig,pFunc,&len);
            }


            break;
        case 3:
            letra = (char*)malloc(sizeof(char));

            *letra = getChar("\nIngrese la sala: ");
            *letra = toupper(*letra);


            if(*letra == 'A' || *letra == 'B')
            {
                printf("\nLa letra ingresada: %c \n",*letra);
                asig->sala=*letra;
                pFunc = asignacion_searchSala;
                indices = ll_search(listaAsignaciones,asig,pFunc,&len);
                printf("\nLen = %d, indices[0]=%d \n",len,*indices);
            }
            else
            {
                printf("\nLa sala ingresada es invalida\n");
                system("pause");
            }

            break;
        case 4:
            num = (int*) malloc (sizeof(int));
            if((getIntIntentos(num,"\nIngrese numero de asignacion (1. Primera Conversarion / 2. Revisita / 3. Estudio Biblico / 4. Lectura de la Biblia / 5. Discurso biblico)\n Ingrese opcion: ","\nAsignacion invalida!\n",1,5,1)==0))
            {
                asig->asignacion=*num;
                pFunc = asignacion_searchAsignacion;
                indices = ll_search(listaAsignaciones,asig,pFunc,&len);
            }

            break;
        case 5:
            error=0;
            system("cls");
            break;
        default:
            system("cls");
            break;

        }
        if(len==0)
        {
            printf("\nNo se ha encontrado resultados\n");
            free(num);
            system("pause");
            error=0;


        }
        else if(len != 0 && len != -1 && indices!=NULL)
        {

            printf("   ID del hermano       Sala                   Asignacion             Fecha\n");
            for(int i=0; i<len; i++)
            {
                indice = indices[i];
                printAsignacion(ll_get(listaAsignaciones,indice));
            }
            printf("\n");
            free(num);
            system("pause");
            error=0;

        }

    }

    free(asig);
    free(indices);
    return error;

}

int controller_editHermanos(LinkedList* this)
{
    int opcion;
    int subOpcion;
    int id;
    eHermano* hno;
    char* string;
    int* num;
    int indice;
    char confirmacion;


    do
    {
        system("cls");
        printf("    *** Editar hermanos ****\n");
        printf("\n 1. Eliminar hermano.");
        printf("\n 2. Desabilitar hermano.");
        printf("\n 3. Hablitiar hermano.");
        printf("\n 4. Modificar hermano.");
        printf("\n 5. Volver atras.\n");
        getInt(&opcion,"\nIngrese opcion: ","\nOpcion invalida",1,5);

        switch(opcion)
        {
        case 1:
            if(getIntIntentos(&id,"\n\nIngrese ID del hermano: ","\nID Invalido",1,999,1)==0)
            {
                printf("\nQue quiere eliminar al siguiente hermano? (s/n)");
                hno = hermano_searchGetById(&id,this);
                printHermano(hno);
                fflush(stdin);
                printf("\nIngrese opcion: ");
                scanf("%c",&confirmacion);
                if(confirmacion == 's')
                {
                    indice = ll_indexOf(this,hno);
                    if(ll_remove(this,indice)==0)
                    {
                        printf("\nLa eliminacion se ha realizado con exito!\n");
                        system("pause");
                    }
                    else
                    {
                        printf("\nNo se ha podido realizar la eliminacion.\n");
                        system("pause");
                    }
                }

            }
            break;
        case 2:
            if(getIntIntentos(&id,"\n\nIngrese ID del hermano: ","\nID Invalido",1,999,1)==0)
            {
                printf("\nQue quiere dehabilitar al siguiente hermano? (s/n)");
                hno = hermano_searchGetById(&id,this);
                printHermano(hno);
                fflush(stdin);
                printf("\nIngrese opcion: ");
                scanf("%c",&confirmacion);
                if(confirmacion == 's')
                {
                    indice = ll_indexOf(this,hno);
                    if(setEstado(hno,0)==0)
                    {
                        printf("\nEl hermano ha sido deshabilitado!\n");
                        system("pause");
                    }
                    else
                    {
                        printf("\nNo se ha podido deshabilitar el hermano.\n");
                        system("pause");
                    }
                }
            }
            break;
        case 3:
            if(getIntIntentos(&id,"\n\nIngrese ID del hermano: ","\nID Invalido",1,999,1)==0)
            {
                printf("\nQue quiere habilitar al siguiente hermano? (s/n)");
                hno = hermano_searchGetById(&id,this);
                printHermano(hno);
                fflush(stdin);
                printf("\nIngrese opcion: ");
                scanf("%c",&confirmacion);
                if(confirmacion == 's')
                {
                    indice = ll_indexOf(this,hno);
                    if(setEstado(hno,0)==0)
                    {
                        printf("\nEl hermano ha sido habilitado!\n");
                        system("pause");
                    }
                    else
                    {
                        printf("\nNo se ha podido habilitado el hermano.\n");
                        system("pause");
                    }
                }
            }
            break;
        case 4:

            if(getIntIntentos(&id,"\n\nIngrese ID del hermano: ","\nID Invalido",1,999,1)==0)
            {
                printf("\nQue quiere modificar al siguiente hermano? (s/n)");
                hno = hermano_searchGetById(&id,this);
                printHermano(hno);
                fflush(stdin);
                printf("\nIngrese opcion: ");
                scanf("%c",&confirmacion);
                if(confirmacion == 's')
                {
                    indice = ll_indexOf(this,hno);
                    do
                    {
                        system("cls");
                        printf("\nQue desea modificar?\n");
                        printf("\n 1. Nombre");
                        printf("\n 2. Apellido");
                        printf("\n 3. Privilegio");
                        printf("\n 4. Servicio de Ministerio");
                        printf("\n 5. Numero de telefono");
                        printf("\n 6. Volver atras\n");
                        getInt(&subOpcion,"\nIngrese opcion: ","\nOpcion invalida",1,6);

                        switch(subOpcion)
                        {
                        case 1:
                            string = (char*)malloc(sizeof(char));
                            if(getString(string,"\nIngrese nombre: ","\nEl nombre no debe superar los 30 caracteres",30)==0)
                            {
                                if(setNombre(hno,string)==0)
                                {
                                    printf("\nSe ha modificado el nombre con exito!\n");
                                    system("pause");
                                }
                                else
                                {
                                    printf("\nError al modificar el nombre!\n");
                                    system("pause");
                                }
                            }
                            break;
                        case 2:
                            string = (char*)malloc(sizeof(char));
                            if(getString(string,"\nIngrese apellido: ","\nEl apellido no debe superar los 30 caracteres",30)==0)
                            {
                                if(setApellido(hno,string)==0)
                                {
                                    printf("\nSe ha modificado el apellido con exito!\n");
                                    system("pause");
                                }
                                else
                                {
                                    printf("\nError al modificar el apellido!\n");
                                    system("pause");
                                }
                            }
                            break;
                        case 3:
                            num = (int*) malloc (sizeof(int));
                            if((getIntIntentos(num,"\nIngrese su privilegio. (1)anciano /(2) Siervo Ministerial / (3) Ninguno \nIngrese opcion: ","\nOPCION INCORRECTA!\n",1,3,1)==0))
                            {
                                if(setPrivilegio(hno,*num)==0)
                                {
                                    printf("\nSe ha modificado los privilegios del hermano.\n");
                                    system("pause");
                                }
                                else
                                {
                                    printf("\nNo se ha podido modificar los privilegios del hermano.\n");
                                    system("pause");
                                }
                            }

                            break;
                        case 4:
                            num = (int*) malloc (sizeof(int));
                            if(getIntIntentos(num,"\nIngrese su servicio de ministerio. (1)publicador /(2) P. Auxiliar /(3) P. Regular /(4) P. Especial \nIngrese opcion: ","\nOPCION INCORRECTA!\n",1,4,1)==0)
                            {
                                if(setServMinist(hno,*num)==0)
                                {
                                    printf("\nSe ha modificado el Servicio de Ministerio del hermano.\n");
                                    system("pause");
                                }
                                else
                                {
                                    printf("\nNo se ha podido modificar el Servicio de Ministerio del hermano.\n");
                                    system("pause");
                                }
                            }
                            break;
                        case 5:
                            string = (char*)malloc(sizeof(char));
                            if(getString(string,"\nIngrese numero de telefono: ","\nEl numero de telefono no debe superar los 20 caracteres",20)==0)
                            {
                                if(setTelefono(hno,string)==0)
                                {
                                    printf("\nSe ha modificado el numero de telefono con exito!\n");
                                    system("pause");
                                }
                                else
                                {
                                    printf("\nError al modificar el numero de telefono!\n");
                                    system("pause");
                                }
                            }

                            break;
                        case 6:
                            system("pause");
                            break;
                        }

                    }
                    while(subOpcion!=6);
                }
            }
            break;
        case 5:
            system("pause");
            break;
        default:
            system("cls");
            break;
        }

    }
    while(opcion != 5);
    free(num);
    free(string);

    return 0; ///retorna error

}

int controller_editAsignaciones(LinkedList* this, LinkedList* this2)
{
    int id;
    int error = 1;
    char* sala;
    int* asignacion;
    eFecha* fecha;
    int indice;
    eHermano* hno = (eHermano*)malloc(sizeof(eHermano));
    eAsignacion* asig = (eAsignacion*)malloc(sizeof(eAsignacion));
    int opcion;

    if(getIntIntentos(&id,"\nIngrese el ID del hermano: ","\nID invalido!",1,999,1)==0)
    {
        hno = hermano_searchGetById(&id,this2);
        printf("   ID          Nombre        Apellido             Telefono      Serv. Minist           Privilegio      Ultima Asignacion              Estado\n");
        printHermano(hno);
        printf("\n\n");
        if(hno != NULL)
        {
            printf("\nIngrese la semana de la asignacion:\n");
            fecha = pedirFecha();
            if(fecha != NULL)
            {
                asig = asignacion_searchByIdData(&id,fecha,this);
                if(asig != NULL)
                {
                    do
                    {
                        system("cls");
                        printf("\n Que desea modificar?");
                        printf("\n 1. Modificar sala");
                        printf("\n 2. Modificar Asignacion");
                        printf("\n 3. Modificar fecha");
                        printf("\n 4. Eliminar asignacion");
                        printf("\n 5. Volver antras\n");
                        getIntIntentos(&opcion,"\nIngrese opcion: ","\nOpcion invalida\n",1,5,1);
                        switch(opcion)
                        {
                        case 1:
                            sala = (char*) malloc (sizeof(char));
                            *sala = getChar("\nIngrese la sala (A/B): ");
                            *sala = toupper(*sala);
                            if(*sala == 'A' || *sala == 'B' || *sala == 'a' || *sala == 'b')
                            {
                                asig->sala = *sala;
                                error = 0;
                            }
                            break;
                        case 2:
                            asignacion = (int*)malloc(sizeof(int));
                            if(getIntIntentos(asignacion,"\nIngrese numero de asignacion (1. Primera Conversarion / 2. Revisita / 3. Estudio Biblico / 4. Lectura de la Biblia / 5. Discurso biblico)\n Ingrese opcion: ","\nOpcion Invalida!",0,5,1) == 0)
                            {
                                asig->asignacion = *asignacion;
                                error = 0;
                            }
                            break;
                        case 3:
                            printf("\nIngrese fecha: \n");
                            fecha = pedirFecha();
                            if(fecha != NULL)
                            {
                                asig->fecha = *fecha;
                                error = 0;
                            }
                            break;
                        case 4:
                            if((indice = ll_indexOf(this,asig)) != -1)
                            {
                                if(ll_remove(this,indice)!=0)
                                {
                                    printf("\nNo se pudo eliminar al hermano\n");
                                    system("pause");
                                }
                                error = 0;
                            }
                            break;
                        default:
                            error = 0;
                            system("cls");
                            break;
                        }

                    }
                    while(opcion != 5);
                }
                else
                {
                    printf("\nNo se ha encontrado la asignacion. Verifique que la fecha sea correcta.\n");
                    system("pause");
                }
            }
        }
        else
        {
            printf("\nEl hermano ingresado no existe\n");
            system("pause");
        }
    }
    return error;
}

eConfiguracion* cargarConfiguracion(char* path,int aplicar)
{
    FILE* configFile;
    int error = 1;
    int cant;
    eConfiguracion* auxConfig = (eConfiguracion*)malloc(sizeof(eConfiguracion));
    char* nombreUsuario = (char*) malloc (sizeof(char)*30);


    if(aplicar == 1 && path != NULL)
    {
        configFile = fopen(path,"rb");
        if(configFile == NULL)
        {
            configFile = fopen(path,"wb");
            if(configFile == NULL)
            {
                printf("\nERROR FATAL! No se pudo crear archivo de configuracion de arranque. Reinicie el programa\n");
                system("pause");
            }
            else
            {
                if(getString(nombreUsuario,"\n\n  Ingrese nombre de usuario: ","\nError. No debe superar los 30 caracteres\n",30)==0)
                {
                    strlwr(nombreUsuario);
                    nombreUsuario[0] = toupper(nombreUsuario[0]);
                    printf("\n  Perfecto!!  \n");
                    system("pause");
                    system("cls");
                    auxConfig = configuracion_newParam(1,nombreUsuario,"listaHermanos.bin","listaAsignaciones.bin",0);
                    if(auxConfig != NULL)
                    {
                        cant = fwrite(auxConfig,sizeof(eConfiguracion),1,configFile);
                        if(cant == 1)
                        {
                            error = 0;
                        }
                    }

                }
            }
        }
        else
        {
            if(auxConfig != NULL)
            {
                cant = fread(auxConfig,sizeof(eConfiguracion),1,configFile);
                if(cant == 1)
                {
                    error = 0;
                }
            }


        }

    }
    if(error)
    {
        auxConfig=NULL;
    }
    fclose(configFile);
    return auxConfig;

}

int controller_aplicarConfiguracion(eConfiguracion* config,LinkedList* listaHermanos,LinkedList* listaAsignaciones)
{
    FILE* hermanosFile;
    int error = 1;
    FILE* asignacionesFiles;
    eHermano* hno;
    eAsignacion* asig;
    int cant;

    if(config->arranqueLogo==1)
    {
        showLogo();
        Sleep(2000);
    }
    system(config->temaConsola);



    hermanosFile = fopen(config->pathListaHermanos,"rb");
    if(hermanosFile == NULL)
    {
        hermanosFile = fopen(config->pathListaHermanos,"wb");
        if(hermanosFile == NULL)
        {
            printf("\nError al crear el archivo de hermanos(%s)\n",config->pathListaHermanos);
            system("pause");
        }
        else
        {
            printf("\nSe ha creado el archivo de hermanos(%s)\n",config->pathListaHermanos);
            error=0;
            system("pause");
        }

    }
    else
    {
        //fseek(hermanosFile,0L,SEEK_SET);
        rewind(hermanosFile);
        while(!feof(hermanosFile))
        {
            hno = (eHermano*)malloc(sizeof(eHermano));
            cant = fread(hno,sizeof(eHermano),1,hermanosFile);

            if(cant != 1)
            {
                if(feof(hermanosFile))
                {
                    error = 0;
                    break;
                }
            }
            if(hno != NULL)
            {

                if(ll_add(listaHermanos,hno))
                {

                    error = 1;
                    break;
                }

                fflush(stdin);
            }
        }
    }
    fclose(hermanosFile);





    asignacionesFiles = fopen(config->pathListaAsignaciones,"rb");
    if(asignacionesFiles == NULL)
    {
        asignacionesFiles = fopen(config->pathListaAsignaciones,"wb");
        if(asignacionesFiles == NULL)
        {
            printf("\nError al crear el archivo de asignaciones (%s)\n",config->pathListaAsignaciones);

            system("pause");
        }
        else
        {
            printf("\nSe ha creado el archivo de asignaciones(%s)\n",config->pathListaAsignaciones);
            error=0;
            system("pause");
        }

    }
    else
    {
        //fseek(asignacionesFiles,0L,SEEK_SET);

        rewind(asignacionesFiles);
        while(!feof(asignacionesFiles))
        {
            asig = (eAsignacion*)malloc(sizeof(eAsignacion));
            cant = fread(asig,sizeof(eAsignacion),1,asignacionesFiles);

            if(cant != 1)
            {
                if(feof(asignacionesFiles))
                {
                    error = 0;
                    break;
                }
            }

            if(ll_add(listaAsignaciones,asig))
            {

                error = 1;
                break;
            }

            fflush(stdin);
        }
    }
    fclose(asignacionesFiles);



    return error;
}

int controller_saveHermanosAsignaciones(LinkedList* listaHermanos,LinkedList* listaAsignaciones,eConfiguracion* config)
{
    FILE* asignacionesFile;
    FILE* hermanosFile;
    FILE* configFile;

    eHermano* hno;
    eAsignacion* asig;

    int error=1;
    int cant;

    ///GUARDAR HERMANOS
    hermanosFile = fopen(config->pathListaHermanos,"wb");
    if(hermanosFile!=NULL)
    {
        fseek(hermanosFile,0L,SEEK_END);
        for(int i=0; i<ll_len(listaHermanos); i++)
        {
            hno = ll_get(listaHermanos,i);

            if(hno != NULL)
            {
                cant = fwrite(hno,sizeof(eHermano),1,hermanosFile);
                if(cant == 1)
                {
                    error = 0;
                }
                else
                {
                    error = 1;
                    break;
                }
            }
            else
            {
                break;
            }
        }
    }
    else
    {
        printf("\nError al intentar guardar el archivo. Parece que el destino(%s) no existe.",config->pathListaHermanos);
    }
    fclose(hermanosFile);



    ///GUARDAR ASIGNACIONES
    asignacionesFile = fopen(config->pathListaAsignaciones,"wb");
    if(asignacionesFile!=NULL)
    {
        fseek(asignacionesFile,0L,SEEK_END);
        for(int i=0; i<ll_len(listaAsignaciones); i++)
        {
            asig = ll_get(listaAsignaciones,i);
            if(asig != NULL)
            {

                cant = fwrite(asig,sizeof(eAsignacion),1,asignacionesFile);
                if(cant == 1)
                {
                    error = 0;
                }
                else
                {
                    error = 1;
                    break;
                }
            }
            else
            {
                break;
            }
        }
    }
    else
    {
        printf("\nError al intentar guardar el archivo. Parece que el destino(%s) no existe.",config->pathListaAsignaciones);
        error = 1;
    }
    fclose(asignacionesFile);

    ///GUARDAR CONFIGURACIONES
    configFile = fopen("config.bin","wb");
    if(configFile != NULL)
    {

        cant = fwrite(config,sizeof(eConfiguracion),1,configFile);
        if(cant != 1)
        {
            printf("\nError al guardar configuraciones\n");
            error = 1;
            system("pause");
        }

    }
    else
    {
        printf("\nNo se ha guardar las configuraciones de arranque. Estamos en un grave problema.\n");
        system("pause");
    }
    fclose(configFile);



    if(error == 0)
    {
        printf("\n Se han guardado los cambios realizados\n");
        system("pause");
    }
    else
    {
        printf("\n Ha ocurrido un error al guardar los cambios\n");
        system("pause");
    }



    return error;
}

int controller_configuracion(eConfiguracion* config)
{
    int opcion;
    int error = 1;
    char* string;

    do
    {
        printf("\n *** Configuraciones ***");
        printf("\n 1. Modificar nombre de usuario");
        printf("\n 2. Modifcar destino del archivo de hermanos");
        printf("\n 3. Modificar destino del archivo de asignaciones");
        printf("\n 4. Cambiar a color de consola");
        printf("\n 5. Desactivar logo");
        printf("\n 6. Volver al menu");
        getIntIntentos(&opcion,"\nIngrese opcion: ","\nOpcion invalida!\n",1,6,1);
        switch(opcion)
        {
        case 1:
            string = (char*)malloc(sizeof(char)*30);
            if(getString(string,"\nIngrese su nombre de usuario: ","\nEl nombre no debe superar los 30 caracteres.\n",30)==0)
            {
                strcpy(config->nombreUsuario,string);
                printf("\nEl nombre ha sido modificado con exito\n");
                error=0;
                system("pause");
            }
            else
            {
                printf("\nNo se ha podido cambiar el nombre\n");
                system("pause");
            }
            break;
        case 2:
            string = (char*)malloc(sizeof(char)*30);
            if(getString(string,"\nIngrese su nombre de destino: ","\nEl nombre no debe superar los 50 caracteres.\n",50))
            {
                strcpy(config->pathListaHermanos,string);
                printf("\nEl nombre de destino ha sid modificado con exito\n");
                error=0;
                system("pause");
            }
            break;
        case 3:
            string = (char*)malloc(sizeof(char)*30);
            if(getString(string,"\nIngrese su nombre de destino: ","\nEl nombre no debe superar los 50 caracteres.\n",50))
            {
                strcpy(config->pathListaAsignaciones,string);
                printf("\nEl nombre de destino ha sid modificado con exito\n");
                error=0;
                system("pause");
            }
            break;
        case 4:
            if(strcmp(config->temaConsola,"COLOR F0")==0)
            {
                strcpy(config->temaConsola,"COLOR 0F");
                error=0;
            }
            else
            {
                strcpy(config->temaConsola,"COLOR F0");
                error=0;
            }
            system(config->temaConsola);
            break;
        case 5:
            if(config->arranqueLogo==1)
            {
                config->arranqueLogo=0;
                printf("\n Se ha deshabilitado el logo\n");
                system("pause");
            }
            else
            {
                config->arranqueLogo=1;
                printf("\n Se ha habilitado el logo\n");
                system("pause");
            }
            break;
        }
        system("cls");
    }
    while(opcion != 6);
    if(error)
    {
        printf("\nNo se ha podido aplicar la configuracion\n");
        system("pause");
    }

    return error;
}

int controller_saveHermanosAsignacionesCSV(LinkedList* listaHermanos,LinkedList* listaAsignaciones)
{
    int len;
    int* listaIndicesAsig;
    FILE* csvFile;
    eHermano* hnos = (eHermano*)malloc(sizeof(eHermano));
    eAsignacion* asigAux = (eAsignacion*)malloc(sizeof(eAsignacion));
    eAsignacion* asig =  asignacion_new();
    char nombreArchivo[25] = " ";
    char nombreAsignacion[25];
    int (*pFunc)();
    int mes;
    int cant;
    int error = 0;

    char anio[4];




    if(getIntIntentos(&mes,"\nIngrese el mes que desea registrar: ","\n Mes invalido!\n",1,12,1)==0)
    {

        (*asig).fecha.mes = mes;
        printf("mes ingresado: %d",(*asig).fecha.mes);
        system("pause");
        switch(mes)
        {
        case 1:
            strcat(nombreArchivo,"Enero ");
            break;
        case 2:
            strcat(nombreArchivo,"Febrero ");
            break;
        case 3:
            strcat(nombreArchivo,"Marzo ");
            break;
        case 4:
            strcat(nombreArchivo,"Abril ");
            break;
        case 5:
            strcat(nombreArchivo,"Mayo ");
            break;
        case 6:
            strcat(nombreArchivo,"Junio ");
            break;
        case 7:
            strcat(nombreArchivo,"Julio ");
            break;
        case 8:
            strcat(nombreArchivo,"Agosto ");
            break;
        case 9:
            strcat(nombreArchivo,"Septiembre ");
            break;
        case 10:
            strcat(nombreArchivo,"Octubre ");
            break;
        case 11:
            strcat(nombreArchivo,"Noviembre ");
            break;
        case 12:
            strcat(nombreArchivo,"Diciembre ");
            break;
        }

        if(getString(anio,"\nIngrese el anio de dicho mes: ","\n Anio invalido!\n",4)==0)
        {


            (*asig).fecha.anio = atoi(anio);
            strcat(nombreArchivo,anio);
            strcat(nombreArchivo,".csv");
            //printf("Nombre del archivo: %s Nombre mes %d\n",nombreArchivo,mes);
            //system("pause");

            csvFile = fopen(nombreArchivo,"w+");

            if(csvFile != NULL)
            {
                fprintf(csvFile,"Hermanos\tAsignacion\tSala\tFecha\r");
                pFunc = asignacion_searchFechaMes;
                listaIndicesAsig = ll_search(listaAsignaciones,asig,pFunc,&len);
                for(int i=0; i<len; i++)
                {
                    asigAux = ll_get(listaAsignaciones,listaIndicesAsig[i]);
                    if(asigAux != NULL)
                    {
                        ///1. Primera visita/2.Revisita/3. Estudio biblico/4.Lectura biblica/5. Discurso biblico
                        switch(asigAux->asignacion)
                        {
                        case 1:
                            strcpy(nombreAsignacion,"Primera visita");
                            break;
                        case 2:
                            strcpy(nombreAsignacion,"Revisita");
                            break;
                        case 3:
                            strcpy(nombreAsignacion,"Estudio biblico");
                            break;
                        case 4:
                            strcpy(nombreAsignacion,"Lectura biblica");
                            break;
                        case 5:
                            strcpy(nombreAsignacion,"Discurso");
                            break;
                        }

                        hnos = hermano_searchGetById(&(asigAux->idHermano),listaHermanos);
                        if(hnos!=NULL)
                        {
                            cant = fprintf(csvFile,"%s %s\t%s\t%c\t%02d/%02d/%04d\r",hnos->apellido,hnos->nombre,nombreAsignacion,asigAux->sala,asigAux->fecha.dia,asigAux->fecha.mes,asigAux->fecha.anio);
                            if(cant == 0)
                            {
                                printf("\nHubo un error en la escritura de datos\n");
                                system("pause");
                                error = 1;
                                break;
                            }
                        }
                        else
                        {
                            printf("\nError al buscar los hermanos\n");
                            error = 1;
                            system("pause");
                        }

                    }
                    else
                    {
                        printf("\nError al buscar las asignaciones\n");
                        error = 1;
                        system("pause");
                        break;
                    }

                }
            }
            else
            {
                printf("\nNo se ha podido crear el archivo. Seguro ya existe otro del mismo mes y anio.\n Eliminelo para crear otro nuevo\n");
                error = 1;
                system("pause");
            }



        }
        else
        {
            error = 1;
        }
    }
    else
    {
        error = 1;
    }
    fclose(csvFile);
    return error;
}



int controller_saveAndExit(LinkedList* listaHermanos,LinkedList* listaAsignaciones,eConfiguracion* config)
{
    char respuesta;
    int error=1;
    int opcion;
    respuesta = getChar("\n Desea guardar los cambios? (s/n) \n");
    switch(respuesta)
    {
    case 's':
        printf("\nComo lo quiere guardar?\n");
        printf("\n1. Guardar solo el archivo predeterminado");
        printf("\n2. Guardar lista un mes de asignaciones para Exel");
        printf("\n3. Salir sin guardar");
        if(getIntIntentos(&opcion,"\nIngrese opcion: ","\nOpcion invalida!",1,3,1)==0)
        {
            switch(opcion)
            {
            case 1:
                if(controller_saveHermanosAsignaciones(listaHermanos,listaAsignaciones,config)==0)
                {
                    printf("\n Se han guardado los cambios!\n");
                    error=0;
                    system("pause");
                }
                break;
            case 2:
                controller_saveHermanosAsignacionesCSV(listaHermanos,listaAsignaciones);

                break;
            case 3:
                printf("\n Ok! Los cambios nos se guardaran.");
                error=0;
                Sleep(1000);
                break;
            }
        }
        break;
    case 'n':
        printf("\n Ok! Los cambios nos se guardaran.");
        error=0;
        Sleep(1000);
        break;
    }

    printf("\n Hasta luego! :D\n");
    Sleep(1000);

    return error;




}



void showLogo(void)
{
    printf("\n                                                                    ```                               \n");
    printf("                            .---.                             -ohMMMmy+`                           \n");
    printf("                          +hMMMMNm+.                        -yMMMMMMMMMh:                          \n");
    printf("                        `hMMMMMMMMMNs`                    `oNMMMMMMMMMMMN/                         \n");
    printf("                        hMMMMMMMMMMMMd-                  .mMMMMMMMMMMMMMMM                         \n");
    printf("                        MMMMMMMMMMMMMMN+                .mMMMMMMMMMMMMMMMM:                        \n");
    printf("                       MMMMMMMMMdMMMMMMy.             -NMMMMMMNMMMMMMMMMMh                         \n");
    printf("                       -MMMMMMMMMMMMMMMMMd.           .dMMMMMNhmMMMMMMMMMMM`                       \n");
    printf("                       oMMMMMMMMMMMMMMMMMMN:         .dMMMMMMMMMMMMMMMMMMMN`                       \n");
    printf("                       oMMMMMMMMMMMMMMMMMMMd.       `yMMMMMMMMMMMMMMMMMMMMs                        \n");
    printf("                       `MMMMMMMMMMMMMMMMMMMMd.      yMMMMMMMMMMMMMMMMMMMMMo                        \n");
    printf("                        dMMMMMMMMMMMMMNMNMMMMy     :MMMMMMNmMMMMMMMMMMMMMM:                        \n");
    printf("                        oMMMMMMMMMMMMMMMNNNhNN/`  `dMymNNMMNMMMMMMMMMMMMMMm`                       \n");
    printf("                        hMMMMMMMMMMMMMMMNs-`:+/o :omy`./sNmMMMMMdyMMMMMMMMM`                       \n");
    printf("                        MMMMMMMMMMMMMMMmh+`   `- d:/`   /hoMmh+dddMoyMMMMMh                        \n");
    printf("                        NMMMMMMMMMMMMMMyo.  `s/-:..+`   `-yhoomMMMMNNMMMMM                         \n");
    printf("                        :mMMMMMMMMMMNm/:s+   yNhy+.d.   `o/.sohNMMMMMMMMMM                         \n");
    printf("                         +MMMMMMMMNmho`hh   /-shmohs.`/` yNs/sshMMMMMMMMMs                         \n");
    printf("                         +MMMMMMMMMyo: -s  /Ndysomh+/sM: `h../+oNMMMMMMMh.                         \n");
    printf("                         /MMMMMMMMmys.``/: mMMMMNMMMMMM/ `-``+mshhmmMMMm-                          \n");
    printf("                         `NhyMMdMyyNm+-:./:dMMMMMMMMMMm````  +NN/+my+mMm/                          \n");
    printf("                          dmdMo`MNms.   `  :NMMMMMMMMMs` .  ``yMNNh`od/oh                          \n");
    printf("                          /MMMd/NMMm+   `   dMMMMMMMMm`:-  `--NMMMs-+:`o-                          \n");
    printf("                          `sNNNNdMMMNy-``   +MMMMMMMMd  .`.:sdMMMm.:``                             \n");
    printf("                            .:.s/yMMMMNmd/  .dMN+hMMy/  .dNNMMMdd+oy` `                            \n");
    printf("                               ohhNdMMMMM``` -h/  hd- `  MMMMMMddyd:.+y`                           \n");
    printf("                              `dhyNmydMMd.s+  .       :h:hMMNmmdysy-../                            \n");
    printf("                           `/:yo`ymh::MM+mMd+.      -smMMdMMd++o:`` `:h                            \n");
    printf("                           -ysd- .oNNmMMMMMMMd:`  .+NMMMMMMMMdso. `` `.                            \n");
    printf("                           :Nh+shh++hNMMMMMMMMNh .mMMMMMMMMNd-   `y+                               \n");
    printf("                         `:sMm`/dMy:.+omMMMMNho/..+ohNNNNds/-..:o/-                                \n");
    printf("                  `.``  +hMMMMy`/mmmm+ `+hmMNdNMNNMNmd:-:.   sddd/                                 \n");
    printf("                 -ys. `:/-sNMMMmy.-/My  y `/yNNNMMNmh+.  -  omNNh.                                 \n");
    printf("              -o+   `+mMMNmNMNNMd:`sd-../    -:://:`     -. +y:.`/                                 \n");
    printf("            .yNm:  `hMMhmNMMMosMmhdMmy`.-                 --:s+-                                   \n");
    printf("          .ymMMy `  hMmsymMms+yohNMMNy` ``               -.:do/-/-                                 \n");
    printf("         :NMMMy `s/`yMMMs:yms-   `Nmyhhyyh/:``.  ` ``.--+++sdNdhN-                                 \n");
    printf("        sNNsdo  hMMNNMNm.`hMMN-``/mMMMMm--./hms-.oyhydMMMMMNmMMN-                                  \n");
    printf("`./.  .+Mhydh `sMmhmh/-`.sMNNMNddNNMMMMMdhydmo-`hNhmMMMMMMMmmmMN.                                  \n");
    printf(".-:` .sNMh-hs` +MmsdNy`` mMd::mMMMMMMm+-ohmMMd/+dMMMMMMMMMMhNMMMm-                                 \n");
    printf(" `.+NMMmNm.   -ms+/`    `hsdNMMNMMMMd+.  -oodMMMMMMMMMMMMMyshNs-                                   \n");
    printf("/y1mMMN+MMh.   -dyMMMd-:ydo+Nmms- oMMMMMMdo:` +NMMMMMMMMMMMMMMMN-                                  \n");
    printf("MMMMMMMh.   /ymhds++mMMMM: ` ` :mmNo:/yhMMMmhosyN:+ymmMNNMMMMm+`/h-                                \n");
    printf("MNNNMMm/    dMds-    yMMh.-` .oms-y/` `/MMMMMMMMMdo:.`.``-h/.`-+mNy                                \n");
    printf("MmNMd/`    :MMN+  `` -NMMMNhymo-/+mNdmNNMMMMMdNMMMMMNdsydshssmMMMm/                                \n");
    printf("MMMMMh`  ./dMMho:. shNMMMo -Nd.-m-./+mmooMMhodysydMMmMMMMMMMMMMMMM/                                \n");
    printf("ooy/-   -MMMMMMm+ ydhd+.:/odNsoys-m:ysodMMd+/hy`omMM+oNMNMdyNMMMMMs                                \n");
    printf("\n\n SERVAL TECHNOLOGIES 2019\t by Lucas Carbone\n");
}


