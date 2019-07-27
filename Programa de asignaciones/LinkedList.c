#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"


static Node* getNode(LinkedList* this, int nodeIndex);
static int addNode(LinkedList* this, int nodeIndex,void* pElement);

/** \brief Crea un nuevo LinkedList en memoria de manera dinamica
 *
 *  \param void
 *  \return LinkedList* Retorna (NULL) en el caso de no conseguir espacio en memoria
 *                      o el puntero al espacio reservado
 */
LinkedList* ll_newLinkedList(void)
{
    LinkedList* this;
    this = (LinkedList *)malloc(sizeof(LinkedList));
    if(this != NULL)
    {
        this->size=0;
        this->pFirstNode = NULL;
    }
    return this;
}

/** \brief Retorna la cantidad de elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna (-1) si el puntero es NULL o la cantidad de elementos de la lista
 *
 */
int ll_len(LinkedList* this)
{
    int len = -1;
    if(this != NULL)
    {
        len = this->size;
        if(len<0)
        {
            len = -1;
        }
    }
    return len;
}


/** \brief  Obtiene un nodo de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pElement) Si funciono correctamente
 *
 */
static Node* getNode(LinkedList* this, int nodeIndex)
{
    Node* pNode = NULL;
    if(this != NULL  && nodeIndex <(ll_len(this)) && nodeIndex >= 0)
    {
        pNode = this->pFirstNode;
        for(int i = 1; i<=nodeIndex; i++)
        {
            pNode = pNode->pNextNode;
        }
    }

    return pNode;
}

/** \brief  Permite realizar el test de la funcion getNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pElement) Si funciono correctamente
 *
 */
Node* test_getNode(LinkedList* this, int nodeIndex)
{
    return getNode(this, nodeIndex);
}


/** \brief Agrega y enlaza un nuevo nodo a la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
static int addNode(LinkedList* this, int nodeIndex,void* pElement)
{

    int error;
    Node *newNode;
    Node *prevNode;

    newNode = (Node*) malloc (sizeof(Node));
    error=-1;

    if(this != NULL && nodeIndex >= 0 && nodeIndex<=ll_len(this))
    {
        if(nodeIndex == 0)
        {
            newNode->pNextNode = this->pFirstNode;
            newNode->pElement = pElement;
            this->pFirstNode = newNode;
            this->size++;
            error=0;

        }
        else if(nodeIndex>0)
        {
            prevNode = getNode(this,nodeIndex-1);
            newNode->pNextNode = prevNode->pNextNode;
            prevNode->pNextNode = newNode;
            newNode->pElement = pElement;
            this->size++;
            error=0;
        }
    }

    return error;

}


/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
  * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int test_addNode(LinkedList* this, int nodeIndex,void* pElement)
{
    return addNode(this,nodeIndex,pElement);
}


/** \brief  Agrega un elemento a la lista
 * \param pList LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento a ser agregado
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_add(LinkedList* this, void* pElement)
{
    int error;
    error = 1;
    if(this != NULL)
    {
        error = addNode(this,ll_len(this),pElement);
    }
    return error;
}

/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a obtener
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_get(LinkedList* this, int index)
{
    void* pElement= NULL;
    Node* pNode;

    if(this != NULL && index>=0 && index<ll_len(this))
    {
        pNode = getNode(this,index);
        if(pNode != NULL)
        {
            pElement = pNode->pElement;
        }
    }
    return pElement;
}


/** \brief Modifica un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a modificar
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_set(LinkedList* this, int index,void* pElement)
{
    int error = -1;
    Node *pNode;
    if(this != NULL && index>=0 && index<ll_len(this))
    {
        pNode = getNode(this,index);
        if(pNode != NULL)
        {
            pNode->pElement = pElement;
            error = 0;
        }
    }
    return error;
}


/** \brief Elimina un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a eliminar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_remove(LinkedList* this,int index)
{
    int error = -1;
    Node* pNode;
    Node* prevNode;

    if(this != NULL && index>=0 && index<ll_len(this))
    {
        if(index == 0)
        {
            pNode = getNode(this,index);
            this->pFirstNode = pNode->pNextNode;
            this->size--;
            error = 0;
        }
        else
        {
            prevNode = getNode(this,index-1);
            pNode = getNode(this,index);
            prevNode->pNextNode = pNode->pNextNode;
            this->size--;
            error = 0;
        }
    }

    return error;
}


/** \brief Elimina todos los elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_clear(LinkedList* this)
{
    int error = -1;
    if(this != NULL)
    {
        this->pFirstNode = NULL;
        this->size=0;
        error = 0;
    }

    return error;
}


/** \brief Elimina todos los elementos de la lista y la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_deleteLinkedList(LinkedList* this)
{
    int error = -1;
    if(this != NULL)
    {
        this = NULL;
        error = 0;
    }

    return error;
}

/** \brief Busca el indice de la primer ocurrencia del elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        (indice del elemento) Si funciono correctamente
 *
 */
int ll_indexOf(LinkedList* this, void* pElement)
{
    int indice = -1;
    void* pElementFound;
    if(this != NULL)
    {
        for(int i = 0; i < ll_len(this); i++)
        {
            pElementFound = ll_get(this,i);
            if(pElement == pElementFound)
            {
                indice = i;
                break;
            }
        }
    }

    return indice;
}

/** \brief Indica si la lista esta o no vacia
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si la lista NO esta vacia
                        ( 1) Si la lista esta vacia
 *
 */
int ll_isEmpty(LinkedList* this)
{
    int empty = -1;
    if(this != NULL)
    {
        empty = 1;
        if(this->size != 0)
        {
            empty = 0;
        }
    }
    return empty;
}

/** \brief Inserta un nuevo elemento en la lista en la posicion indicada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo elemento
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_push(LinkedList* this, int index, void* pElement)
{
    int indice = -1;

    if(this != NULL && index>=0 && index<=ll_len(this))
    {
        indice = addNode(this,index,pElement);
    }


    return indice;
}


/** \brief Elimina el elemento de la posicion indicada y retorna su puntero
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento eliminar
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_pop(LinkedList* this,int index)
{
    void* aux = NULL;
    if(this != NULL && index>=0 && index<ll_len(this))
    {
        aux = ll_get(this,index);
        ll_remove(this,index);

    }

    return aux;
}


/** \brief  Determina si la lista contiene o no el elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero del elemento a verificar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 1) Si contiene el elemento
                        ( 0) si No contiene el elemento
*/
int ll_contains(LinkedList* this, void* pElement)
{
    int error = -1;
    if(this != NULL)
    {
        error = 0;
        for(int i=0; i<ll_len(this); i++)
        {
            if(pElement == ll_get(this,i))
            {
                error = 1;
                break;
            }
        }
    }

    return error;
}

/** \brief  Determina si todos los elementos de la lista (this2)
            estan contenidos en la lista (this)
 *
 * \param this LinkedList* Puntero a la lista
 * \param this2 LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si alguno de los punteros a las listas son NULL
                        ( 1) Si los elementos de (this2) estan contenidos en la lista (this)
                        ( 0) si los elementos de (this2) NO estan contenidos en la lista (this)
*/
int ll_containsAll(LinkedList* this,LinkedList* this2)
{
    int allFound = -1;
    int found = 0;
    if(this != NULL && this2 != NULL)
    {
        allFound = 0;
        for(int i=0; i<ll_len(this2); i++)
        {
            for(int j=0; j<ll_len(this); j++)
            {
                if(ll_get(this2,i) == ll_get(this,j))
                {
                    found++;
                }
            }
        }
        if(found == ll_len(this2))
        {
            allFound = 1;
        }
    }

    return allFound;
}

/** \brief Crea y retorna una nueva lista con los elementos indicados
 *
 * \param pList LinkedList* Puntero a la lista
 * \param from int Indice desde el cual se copian los elementos en la nueva lista
 * \param to int Indice hasta el cual se copian los elementos en la nueva lista (no incluido)
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                o (si el indice from es menor a 0 o mayor al len de la lista)
                                o (si el indice to es menor o igual a from o mayor al len de la lista)
                         (puntero a la nueva lista) Si ok
*/
LinkedList* ll_subList(LinkedList* this,int from,int to)
{
    LinkedList* cloneArray = NULL;

    if(this != NULL && from >= 0 && from <=ll_len(this) && to>from && to<=ll_len(this))
    {
        cloneArray = ll_newLinkedList();
        while(from<to)
        {
            ll_add(cloneArray,(ll_get(this,from)));
            from++;
        }

    }

    return cloneArray;
}



/** \brief Crea y retorna una nueva lista con los elementos de la lista pasada como parametro
 *
 * \param pList LinkedList* Puntero a la lista
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                (puntero a la nueva lista) Si ok
*/
LinkedList* ll_clone(LinkedList* this)
{
    LinkedList* cloneArray = NULL;
    int cont = 0;
    if(this != NULL)
    {
        cloneArray = ll_newLinkedList();
        while(cont<ll_len(this))
        {
            ll_add(cloneArray,(ll_get(this,cont)));
            cont++;
        }
    }

    return cloneArray;
}


/** \brief Ordena los elementos de la lista utilizando la funcion criterio recibida como parametro
 * \param pList LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio
 * \param order int  [1] Indica orden ascendente - [0] Indica orden descendente
 * \return int Retorna  (-1) Error: si el puntero a la listas es NULL
                                ( 0) Si ok
 */
int ll_sort(LinkedList* this, int (*pFunc)(void*,void*), int order)
{
    int returnAux =-1;
    void * aux = NULL;

    if(this != NULL && pFunc != NULL && (order == 1 || order == 0))
    {
        for(int i=0; i<ll_len(this)-1; i++)
        {
            for(int j=i+1; j<ll_len(this); j++)
            {
                if(pFunc(ll_get(this,i),ll_get(this,j))==1 && order == 1)
                {
                    aux = ll_get(this,i);
                    ll_set(this,i,ll_get(this,j));
                    ll_set(this,j,aux);
                }
                else if(pFunc(ll_get(this,i),ll_get(this,j))==-1 && order == 0)
                {
                    aux = ll_get(this,i);
                    ll_set(this,i,ll_get(this,j));
                    ll_set(this,j,aux);
                }
            }
        }
        returnAux = 0;
    }
    return returnAux;
}




///FUNCIONES AGREGADAS


void map(LinkedList* this,int (*pFunc)(void*))
{
    for(int i=0;i<ll_len(this);i++)
    {
        pFunc(ll_get(this,i));
    }
}

LinkedList* filter(LinkedList* this,int (*pFunc)(void*))
{
    LinkedList* vehiculo = ll_newLinkedList();
    for(int i=0;i<ll_len(this);i++)
    {
        if(pFunc(ll_get(this,i)))
        {
            ll_add(vehiculo,ll_get(this,i));
        }
    }
    return vehiculo;
}

int* ll_search(LinkedList* this,void* element,int (*pFunc) (void*,void*),int* len)
{
    int* found = (int*) malloc (sizeof(int));
    int* foundAux;
    void* aux;
    int j = 0;

    for(int i=0;i<ll_len(this);i++)
    {
        aux = ll_get(this,i);
        if(pFunc(element,aux))
        {

            j++; ///incremento el indice j para la proxima
            foundAux = (int*)realloc(found,sizeof(int)*j); ///incremento el espacio del array en 1 (intento hacerlo en un auxiliar)
            if(foundAux != NULL)
            {
                found = foundAux; ///si todo salio bien, copio el auxiliar a found
                found[j-1]=i;///copio el numero del indice obtenido al array, en el indice j-1
            }
            else
            {
                j--; ///si algo malio sal pues cancelare el incremento de j
            }
        }
    }
    *len =j;
    return found;
}
