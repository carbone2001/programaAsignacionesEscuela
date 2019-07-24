#include <stdio.h>
#include <stdlib.h>
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
            if(getInt(id,"\nIngrese ID del hermano: ","\nEl ID ingresado es invalido",1,999) == 0 && (hno = hermano_searchGetById(id,listaHermanos))!=NULL)
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


int controller_editEmployee(LinkedList* pArrayList)
{
    /*int opcion;
    int id;
    int error = 0;
    int empFound=-1;
    eHermano* hno;
    eHermano* aux;

    int newId;
    char* newNombre;
    int newHorasTrabajadas;
    int newSueldo;
    newNombre = (char*) malloc (sizeof(char));
    printf("Ingrese ID del empleado a modificar: ");
    scanf("%d",&id);
    for(int i = 0; i<ll_len(pArrayList); i++)
    {
        hno = ll_get(pArrayList,i);
        if(hno->id == id)
        {
            empFound = i;
            break;
        }
    }

    if(empFound != -1)
    {
        system("cls");
        printf("*** MODIFICAR EMPLEADO ***");
        printf("\n1) ID");
        printf("\n1) Nombre");
        printf("\n1) Horas Trabajdas");
        printf("\n1) Sueldo");
        scanf("%d",&opcion);

        switch (opcion)
        {
        case 1:
            printf("Ingrese nuevo ID: ");
            scanf("%d",&newId);
            for(int i=0; i<ll_len(pArrayList); i++)
            {
                aux = ll_get(pArrayList,i);
                if(aux == NULL)
                {
                    error = 1;
                    break;
                }
                if(aux->id == newId)
                {
                    printf("\nEl ID ingresado ya exite. Intente ingresar otro\n");
                    error = 1;
                }
            }
            if(error)
            {
                break;
            }
            if((error = employee_setId(hno,newId)))
            {
                break;
            }
            error = ll_set(pArrayList,empFound,hno);
            break;
        case 2:
            printf("Ingrese nuevo Nombre: ");
            fflush(stdin);
            gets(newNombre);
            if((error = employee_setNombre(hno,newNombre)))
            {
                break;
            }
            error = ll_set(pArrayList,empFound,hno);
            break;
        case 3:
            printf("Ingrese nuevo numero de horas trabajdas: ");
            scanf("%d",&newHorasTrabajadas);
            if((error = employee_setHorasTrabajadas(hno,newHorasTrabajadas)))
            {
                break;
            }
            error = ll_set(pArrayList,empFound,hno);
            break;
        case 4:
            printf("Ingrese nuevo sueldo: ");
            scanf("%d",&newSueldo);
            if((error = employee_setSueldo(hno,newSueldo)))
            {
                break;
            }
            error = ll_set(pArrayList,empFound,hno);
            break;
        default:
            printf("\nOpcion invalida");
            break;


        }
        if(error)
        {
            printf("\nError al modificar empleado\n");
            system("pause");
        }
        else
        {
            printf("\nEl empleado se ha modifcado exitosamente\n");
            system("pause");
        }

    }
    else
    {
        printf("\nNo se ha encontrado al empleado de ID %d\n",id);
    }
    */

    return 1;
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

/** \brief Listar empleados
 *
 * \param path char*
 * \param pArrayList LinkedList*
 * \return int
 *
 */

/*int controller_ListEmployee(LinkedList* pArrayList)
{
    int error = 0;
    eHermano* empleado;
    for(int i=0; i<ll_len(pArrayList); i++)
    {
        empleado = ll_get(pArrayList,i);
        if(empleado == NULL)
        {
            error = 1;
            break;
        }
        printf("\n%d %15s %d %d \n",empleado->id,empleado->nombre,empleado->sueldo,empleado->horasTrabajadas);
    }
    if(error)
    {
        printf("\n\nError al listar los empleados\n");
    }
    system("pause");
    system("cls");


    return error;
}*/

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

eConfiguracion* configuracionDeArranque(int iniciar)
{
    eConfiguracion* config;
    if(iniciar)
    {
        config = (eConfiguracion*) malloc (sizeof(eConfiguracion));
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



            /*

            while(opcion != 4)
            {
                system("cls");
                printf("\n1.Buscar por numero de asignacion");
                printf("\n2.Buscar por semana");
                printf("\n3. Buscar por ID de hermano");
                printf("\n4. Volver atras\n");
                getInt(&opcion,"\nIngrese opcion: ","\nOpcion de invalida!\n",1,4);
                switch(opcion)
                {
                case 1:

                    break;
                case 2:
                    break;
                case 3:
                    num = (int*) malloc (sizeof(int)*30);
                    if(getIntIntentos(num,"\nIngrese ID del hermano: ","\nID invalido!\n",1,999,1)==0)
                    {
                        hno->id=*num;
                        pFunc = hermano_searchAsignacionId;
                        indices = ll_search(this,hno,pFunc,&len);
                    }

                    break;
                }
            }*/

            break;

        default:
            system("cls");
            break;
        }
        if(len==0)
        {
            printf("\nNo se ha encontrado resultados para: '%s'\n",string);
            system("pause");


        }
        else if(len != 0 && len != -1 && indices!=NULL)
        {
            printf("   ID          Nombre        Apellido             Telefono      Serv. Minist           Privilegio      Ultima Asignacion\n");
            for(int i=0; i<len; i++)
            {
                indice = indices[i];
                printHermano(ll_get(this,indice));

            }
            printf("\n");
            system("pause");

        }

    }
    free(num);
    free(string);
    free(hno);
    free(indices);
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
    int* indices = (int*) malloc (sizeof(int));
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
            break;
        case 2:
            printf("\nIngrese fecha: ");
            fecha = pedirFecha();

            if(fecha != NULL)
            {
                asig->fecha=*fecha;
                pFunc = asignacion_searchFecha;
                indices = ll_search(listaAsignaciones,asig,pFunc,&len);
            }


            break;
        case 3:

            break;
        case 4:

            break;
        case 5:
            /*

            while(opcion != 4)
            {
                system("cls");
                printf("\n1.Buscar por numero de asignacion");
                printf("\n2.Buscar por semana");
                printf("\n3. Buscar por ID de hermano");
                printf("\n4. Volver atras\n");
                getInt(&opcion,"\nIngrese opcion: ","\nOpcion de invalida!\n",1,4);
                switch(opcion)
                {
                case 1:

                    break;
                case 2:
                    break;
                case 3:
                    num = (int*) malloc (sizeof(int)*30);
                    if(getIntIntentos(num,"\nIngrese ID del hermano: ","\nID invalido!\n",1,999,1)==0)
                    {
                        hno->id=*num;
                        pFunc = hermano_searchAsignacionId;
                        indices = ll_search(this,hno,pFunc,&len);
                    }

                    break;
                }
            }*/
            break;

        default:
            system("cls");
            break;
        }
        if(len==0)
        {
            printf("\nNo se ha encontrado resultados\n");
            system("pause");


        }
        else if(len != 0 && len != -1 && indices!=NULL)
        {
            hno = hermano_searchGetById(num,listaHermanos);
            if(hno != NULL)
            {
                printf("\n\n%s %s \n",hno->apellido,hno->nombre);
            }
            printf("   ID del hermano       Sala            Asignacion                  Fecha\n");
            for(int i=0; i<len; i++)
            {
                indice = indices[i];
                printAsignacion(ll_get(listaAsignaciones,indice));
            }
            printf("\n");
            system("pause");

        }

    }
    free(num);
    free(asig);
    free(indices);


    return error;

}
