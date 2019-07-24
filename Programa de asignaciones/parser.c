#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "hermanos.h"

/** \brief Parsea los datos los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int parser_FromText(FILE* pFile, LinkedList* pArrayList)
{
    int error=0;
    /*
    char buffer[8][30];
    int cant;
    eHermano* hno; ///Estructura a parsear
    error = 0;
    if(pFile != NULL && pArrayList != NULL)
    {
        //Leida fantasma
        cant = fscanf(pFile,"%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n",buffer[0],buffer[1],buffer[2],buffer[3],buffer[4],buffer[5],buffer[6],buffer[7]);
        if(cant==8)
        {
            while(!feof(pFile))
            {
                cant = fscanf(pFile,"%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n",buffer[0],buffer[1],buffer[2],buffer[3],buffer[4],buffer[5],buffer[6],buffer[7]);
                if(cant!=8)
                {
                    if(feof(pFile))
                    {
                        break;
                    }
                    error = 1;
                    break;
                }
                hno = hermano_newParametros(buffer[0],buffer[1],buffer[2],buffer[3],buffer[4],buffer[5],buffer[6],buffer[7]);
                if(hno == NULL)
                {
                    error = 1;
                    break;
                }
                if(ll_add(pArrayList,hno))
                {
                    error = 1;
                    break;
                }
            }
        }
    }

    free(hno);*/

    return error;
}

/** \brief Parsea los datos los datos de los empleados desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayList LinkedList*
 * \return int
 *
 */

int parser_FromBinary(FILE* pFile, LinkedList* pArrayList)
{

    eHermano *hno;
    int error = 1;
    int cant;
    if(pFile != NULL && pArrayList != NULL)
        while(!feof(pFile))
        {
            hno = (eHermano*) malloc (sizeof(eHermano));
            if(hno == NULL)
            {
                break;
            }
            cant = fread(hno,sizeof(eHermano),1,pFile);
            if(cant != 1)
            {
                if(feof(pFile))
                {
                    error = 0;
                    break;
                }
                break;
            }

            if(ll_add(pArrayList,hno))
            {
                break;
            }
        }
    return error;
}

int parser_FromTextLogo(FILE* pFile)
{
    int error;
    char buffer[110];
    int cant;
    error = 0;
    if(pFile != NULL)
    {
        while(!feof(pFile))
        {
            cant = fscanf(pFile,"%s",buffer);
            if(cant!=1)
            {
                if(feof(pFile))
                {
                    break;
                }
                error = 1;
                break;
            }
            printf("%s",buffer);
        }
    }
    return error;
}
