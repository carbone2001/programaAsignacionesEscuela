#ifndef dominio_H_INCLUDED
#define dominio_H_INCLUDED

 typedef struct
 {
     int id;
     char dominio[7];
     int anio;
     char tipo;
 }eDominio;

eDominio* dominio_newParametros(char* idStr,char* nombreStr,char* apellidoStr,char* telefonoStr,char* servMinistStr,char* privilegioStr,char* fechaUltimaAsignacionStr,char* estado);
int asignarTipo(eDominio* this);
int esUnAuto(eDominio* this);
int esUnaMoto(eDominio* this);

int setId(eDominio* this,int id);
int getId(eDominio* this,int* id);

int setDominio(eDominio* this,char* dominio);
int getDominio(eDominio* this,char* dominio);

int setAnio(eDominio* this,int anio);
int getAnio(eDominio* this,int* anio);

int setTipo(eDominio* this,char tipo);
int getTipo(eDominio* this,char* tipo);

void printElemento(eDominio* p);

//void printElementos(LinkedList* this);

/** \brief
 * \param elemento void*
 * \param elemento2 void*
 * \return int Devuelve (1) si el segundo elemento es mas grande. (0) Si son iguales.(-1) Si el segundo elemento es mas chico.
 */
int ordenSegunNumero(void *elemento,void* elemento2);


/** \brief
 *
 * \param elemento1 eDominio*
 * \param elemento2 eDominio*
 * \return int (1) Si el primer elemento es mas grande que el segun, (0) Si son iguales (-1) Si es menor
 *
 */
int idcmp(eDominio* elemento1, eDominio* elemento2);


#endif // dominio_H_INCLUDED
