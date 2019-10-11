#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "hermanos.h"

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
