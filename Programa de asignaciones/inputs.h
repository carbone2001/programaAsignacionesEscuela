#ifndef INPUTS_H_INCLUDED
#define INPUTS_H_INCLUDED



/** \brief Solicita un dato de tipo entero y luego evalua si este dato corresponde segun los parametros dados.
 * \param input int* La direccion de la variable donde se escribira el valor ingresado
 * \param msj char* Mensaje que solicita el ingreso de un numero
 * \param eMsj char* Mensaje en caso de error
 * \param minimo int El valor minimo que puede ingresar
 * \param maximo int El valor maximo que puede ingresar
 * \param reintentos int Si la cantidad de intentos es 0, solicitara el numero correcto de forma infinita. Caso contrario, solo tendra una cantidad limitada de intentos
 * \return int Si hubo error (1) o no (0)
 */
int getIntIntentos(int* input,char* msj,char* eMsj,int minimo,int maximo,int reintentos);

/** \brief Solicita un dato de tipo entero y luego evalua si este dato corresponde segun los parametros dados. No tiene reintentos.
 *
 * \param int*input La direccion de la variable donde se escribira el valor ingresado
 * \param char*msj  Mensaje que solicita el ingreso de un numero
 * \param char*eMsj Mensaje en caso de error
 * \param minimo int El valor minimo que puede ingresar
 * \return int retorna 0 si no hubo error y 1 si hubo.
 *
 */
//int getInt(int*input,char*msj,char*eMsj,int minimo,int maximo);
int getInt(int* input,char*msj,char*eMsj,int minimo,int maximo);


/** \brief Solicita un dato de tipo flotante y luego evalua si este dato corresponde segun los parametros dados. No tiene reintentos.
 *
 * \param int*input La direccion de la variable donde se escribira el valor ingresado
 * \param char*msj  Mensaje que solicita el ingreso de un numero
 * \param char*eMsj Mensaje en caso de error
 * \param minimo int El valor minimo que puede ingresar
 * \param maximo int El valor maximo que puede ingresar
 * \return void
 *
 */
void getFloatPlus(float*input,char*msj,char*eMsj,float minimo,float maximo);
/** \brief Se genera un numero aleatorio
 *
 * \param primerNumero int El numero minimo que se desea obtener
 * \param ultimoNumero int El numero maximo que se desea obtener
 * \param primeraVez int Si se utiliza por primera vez (1) sino (0)
 * \return int El numero generado
 *
 */
int getRandom(int primerNumero, int ultimoNumero,int primeraVez);
/** \brief Solicita un dato de tipo caracter y este debe coincidir con ciertos parametros
 *
 * \param char*msj El mensaje que solicita el ingreso de un caracter
 * \param letraCorrecta char El caracter al cual debe asemejarse el dato ingresado
 * \return int El caracter ingresado
 *
 */
char getChar(char*msj);

/** \brief Solicita el ingreso de una cadena
 *
 * \param str[] char La variable a cargar
 * \param char*msj El mensaje que solicita el ingreso de una cadena
 * \param char*eMsj El mensaje que se muestra en caso de error
 * \param limite int Limite de elementos de la cadena
 * \return int Si hubo error (1) sino (0)
 *
 */
int getString(char* str,char*msj,char*eMsj,int limite);



#endif // INPUTS_H_INCLUDED
