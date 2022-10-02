#include <stdio.h> //printf
#include <stdlib.h>
#include<stdbool.h>// Booleanos


#include <string.h>

//TABLA DE PALABRAS RESERVADAS
#define FILAS 11
#define LONGITUD_CADENA 20
#define LONGITUD_LEXEMA 100

 int result;

//CONSTANTES NUMERICAS
typedef enum {
id,
sim,
simr,
siml,
cad,
num,
palres,
}TypeToken;

//NUEVA ESTRUCTURA TIPO TOKEN
typedef struct Token {
TypeToken tipoToken;
char lexema[LONGITUD_LEXEMA];
int valor;
}TOKEN;



//NODOS PARA LA LISTA DOBLEMENTE ENLAZADA
typedef struct nodo {
struct Token info;
struct nodo *izq;
struct nodo *der;
}NODO;


struct nodo *raiz;
struct nodo *actual;


//DECLARACION DE FUNCION AUTOMATA PARA OBTENER IDENTIFICADOR
void obtenerIdentificador();

//DECLARACION DE FUNCION AUTOMATA PARA OBTENER SIMBOLOS
void obtenerSimbolos();

//DECLARACION DE FUNCION AUTOMATA PARA OBTENER DIGITOS
void obtenerDigitos();

//DECLARACION DE FUNCION AUTOMATA PARA OBTENER SIMBOLOS RELACIONALES
void obtenerRelacionales();

//DECLARACION DE FUNCION AUTOMATA PARA OBTENER SIMBOLOS LOGICOS
void obtenerLogicos();

//DECLARACION DE FUNCION AUTOMATA PARA OBTENER CADENAS
void obtenerCadena();

//DECLARACION DE FUNCION PARA CHECAR CARACTER CON ALFABETO
bool checarAlfabeto(char alfabeto[] , char caracter);

//DECLARACION DE FUNCION PARA IR ALMACENANDO CARACTER POR CARACTER EN VARIABLE
void concatenarCharEnString();

//LIMPIAR ARRAY DE CADENAS
void limpiarArrayCadena();

//FUNCION PÁRA CREAR NODO
NODO* CrearNodo(TOKEN token);

//INSERTAR TOKEN EN LISTA ENLAZADA
void insertar(TOKEN token);

//FUNCION PARA RECORRER LISTA Y MOSTRAR EN PANTALLA LOS DATOS
void ImprimirLista();

//FUNCION PARA RECORRER LISTA Y MOSTRAR EN PANTALLA LOS DATOS (DE MANERA INVERSA)
void ImprimirListaRev();


//DECLARACION DE ALFABETOS PARA AUTOMATAS
char alfabetoLetras[] = "ABCDEFGHIJKLMNÑOPQRSTUVWXYZabcdefghijklmnñopqrstuvxyz";
char alfabetoNumeros[] = "0123456789";
char palabrasRes[FILAS][LONGITUD_CADENA] = { "Inicio", "Fin", "Entero", "Real", "Cadena", "Caracter","Si", "Sino", "Para", "Imprimir", "Entrada"};
char alfabetoSimbolos[] = {';',' ','$','+','-','|', '(', ')', '{','}'};
char alfabetoLogicos[] = {'|','&'};
char alfabetoRelacionales[] = {'<','>', '='};
char alfabetoCadena[] = {'"'};
int indice; //VARIABLE ENCARGADA DE SABER EL INDICE EN ALFABETO

//DECLARACION DE VARIABLE DE TIPO FILE PARA TRABAJAR CON ARCHIVOS DE TEXTO
FILE * archivo;

//VARIABLE ENCARGADA DE LEER CARACTER POR CARRACTER EN ARCHIVO DE TEXTO
char caracter;

//VARIABLE ENCARGADA DE LOS ESTADOS DE LOS AUTOMATAS
char estado;

//VARIABLE DONDE SE GUARDAN LOS TOKEN CARCTER POR CARACTER
char tokenCaracter[LONGITUD_LEXEMA];
char *pToken;//VARIABLE QUE SE COMPORTARA COMO PUNTERO PARA 'tokenCaracter'

//VARIABLE BOOL ENCARGADA DE DECIRLE AL PUNTERO
//DEL ARCHIVO DE TEXTO QUE VIENE DE UNA ACEPTACION DE UN AUTOMATA
//POR LO TANTO EL PUNTERO NO SE INCREMENTA...
bool VieneDeEstadoAceptacion = false;



//FUNCION PRINCIPAL DEL PROGRAMA
main() {

    //ABRIMOS ARCHIVO PARA LEERLO
    archivo=fopen("PGM.txt","r");

    //VALIDACION PARA SABER SI SE PUEDE LEER DICHO ARCHIVO
    if(archivo == NULL){
        printf("Error en la apertura del archivo.");
    }else{
        //ARCHIVO SI SE PUDO LEER

        //WHILE PARA RECORRER EL ARCHIVO DE TEXTO
        while(feof(archivo) == 0){

            //IF PARA SABER SI EL PUNTERO REGRESO DE UN
            //AUTOMATA DE SU ESTADO DE ACEPTACION
            if(VieneDeEstadoAceptacion){VieneDeEstadoAceptacion = false;}
            else {caracter=fgetc(archivo);}//PUNTERO SE INCREMETA Y ASIGNO EL SIGUIENTE CARACTER

            //LIMPIAMOS EL ARRAY DE LA CADENA 'tokenCaracter'
            limpiarArrayCadena();

            //ASIGNAMOS PUNBTERO A VARIABLE (espacio en memoria compartido)
            pToken = tokenCaracter;

            //CHECAR SI CARACTER QUE ENTRO ES UNA LETRA
           if(checarAlfabeto(alfabetoLetras ,caracter)){
                estado = '1';
                //AGREGAR EL CARACTER EN ARRAY CADENA
                concatenarCharEnString(); //PARAMETRO COMO VARIABLE GLOBAL (caracter)

                //FUNCION AUTOMATA PARA VALIDAR SI LOS CARACTERES SIGUIENTES FORMAN
                //UN IDENTIFICADOR O PALABRA RESERVADA
                obtenerIdentificador();//PUNTERO DE LECTURA DE ARCHIVO ENVIADO COMO VARIABLE GLOBAL

                //ESTRUCTURA DE TIPO TOKEN
                TOKEN token;
                strcpy(token.lexema, tokenCaracter);
                token.valor= 0;
                token.tipoToken = id;

                 for(int i = 0; i <= 11; i++){

                  // VERIFICA SI ES UNA PALABRA RESERVADA
                    result = strcmp(token.lexema,palabrasRes[i]);

                      if(result == 0){
                           token.tipoToken = palres;

                      }
                 }

                //INSERTARLO EN LA LISTA ENLAZADA
                insertar(token);
            //CHECAR SI CARACTER ES UN SIMBOLO
           }else if(checarAlfabeto(alfabetoSimbolos , caracter) && (caracter == '>') || (caracter == '<') || (caracter == '=')){
                estado = '2';
               //AGREGAR EL CARACTER EN ARRAY CADENA
               concatenarCharEnString(); //PARAMETRO COMO VARIABLE GLOBAL (caracter)

                obtenerRelacionales();

                 //ESTRUCTURA DE TIPO TOKEN

                TOKEN token;
                token.tipoToken = simr;
                strcpy(token.lexema, tokenCaracter);

                token.valor= 0;

                //INSERTARLO EN LA LISTA ENLAZADA
                insertar(token);

            //CHECAR SI CARACTER PUEDE SER UNA CADENA
           }else if(checarAlfabeto(alfabetoCadena , caracter)){
                estado = '2';

                //AGREGAR EL CARACTER EN ARRAY CADENA
                concatenarCharEnString(); //PARAMETRO COMO VARIABLE GLOBAL (caracter)

                obtenerCadena();

                 //ESTRUCTURA DE TIPO TOKEN
                TOKEN token;
                token.tipoToken = cad;
                strcpy(token.lexema, tokenCaracter);
                token.valor= 0;

                //INSERTARLO EN LA LISTA ENLAZADA
                insertar(token);

            //CHECAR SI CARACTER ES UN DIGITO
           }else if(checarAlfabeto(alfabetoLogicos , caracter)){
                estado = '2';


                //AGREGAR EL CARACTER EN ARRAY CADENA
                concatenarCharEnString(); //PARAMETRO COMO VARIABLE GLOBAL (caracter)

                obtenerLogicos();

                //ESTRUCTURA DE TIPO TOKEN
                //ESTA EN PRUEBAS NO FUNCIONAL
                TOKEN token;
                token.tipoToken = siml;
                strcpy(token.lexema, tokenCaracter);
                token.valor= 0;

                //INSERTARLO EN LA LISTA ENLAZADA
                insertar(token);

            //CHECAR SI CARRACTER ES UN DIJITO
           }else if(checarAlfabeto(alfabetoSimbolos , caracter)){
                estado = '2';
                //AGREGAR EL CARACTER EN ARRAY CADENA
                concatenarCharEnString(); //PARAMETRO COMO VARIABLE GLOBAL (caracter)

                 //ESTRUCTURA DE TIPO TOKEN

                TOKEN token;
                token.tipoToken = sim;
                strcpy(token.lexema, tokenCaracter);

                token.valor= 0;


                //INSERTARLO EN LA LISTA ENLAZADA
                insertar(token);

            //CHECAR SI CARACTER ES UN DIGITO
           }else if(checarAlfabeto(alfabetoNumeros , caracter)){
                estado = '2';

                //AGREGAR EL CARACTER EN ARRAY CADENA
                concatenarCharEnString(); //PARAMETRO COMO VARIABLE GLOBAL (caracter)

                obtenerDigitos();

                //ESTRUCTURA DE TIPO TOKEN
                TOKEN token;
                token.tipoToken = num;
                strcpy(token.lexema, tokenCaracter);
                token.valor=strtol(tokenCaracter, NULL, 10);

                //INSERTARLO EN LA LISTA ENLAZADA
                insertar(token);

           }

        } //FIN DE WHILE QUE RECORRE ARCHIVO DE TEXTO

    }//FIN DE

    //RECORRER LA LISTA ENLAZADA Y MUESTRA LOS DATOS
    ImprimirLista();

return 0;
}//FIN DE MAIN



//FUNCION PARA CHECAR CARACTER EN ALFABETO
bool checarAlfabeto(char alfabeto[] , char caracter){
    for (indice = 0; indice < strlen(alfabeto); indice++)
    {
        char caracterActual = alfabeto[indice];

        if(caracterActual == caracter){
            return true;
        }
    }
    return false;
}


void obtenerRelacionales(){

    //WHILE QUE RECORRE ARCHIVO CARACTER POR CARACTER
    while(feof(archivo) == 0 && estado == '1' || estado == '2'){
        caracter=fgetc(archivo); //VARIABLE ENCARGADA DE OBTENER CARACTER QUE ENTRO

        //VERIFICAR SI EL SIGUINETE ES NUMERO
       if(checarAlfabeto(alfabetoRelacionales ,caracter)&&(caracter == '>') || (caracter == '=' )){
            estado = '2'; //CAMBIO DE ESTADO A 2 = DIJITOS
            concatenarCharEnString(); //CONCATENO EL CARACTER QUE ENTRO EN ARRAY (tokenCaracter)
        }else {
            //ESTADO DE ACEPTACION (CORTE DE CADENA)
            estado = '3';
            VieneDeEstadoAceptacion = true;
        }
    }
}

void obtenerSimbolos(){

          //WHILE QUE RECORRE ARCHIVO CARACTER POR CARACTER

    while(feof(archivo) == 0 && estado == '1' || estado == '2'){
        caracter=fgetc(archivo); //VARIABLE ENCARGADA DE OBTENER CARACTER QUE ENTRO

        //VERIFICAR SI EL SIGUINETE ES NUMERO
       if(checarAlfabeto(alfabetoSimbolos ,caracter )){
            estado = '2'; //CAMBIO DE ESTADO A 2 = DIJITOS
            concatenarCharEnString(); //CONCATENO EL CARACTER QUE ENTRO EN ARRAY (tokenCaracter)
        }else {
            //ESTADO DE ACEPTACION (CORTE DE CADENA)
            estado = '3';
            VieneDeEstadoAceptacion = true;
        }
    }
}


void obtenerLogicos(){

          //WHILE QUE RECORRE ARCHIVO CARACTER POR CARACTER

    while(feof(archivo) == 0 && estado == '1' || estado == '2'){
        caracter=fgetc(archivo); //VARIABLE ENCARGADA DE OBTENER CARACTER QUE ENTRO

        //VERIFICAR SI EL SIGUINETE ES NUMERO
       if(checarAlfabeto(alfabetoLogicos ,caracter)&&(caracter == '&') || (caracter == '|' )){
            estado = '2'; //CAMBIO DE ESTADO A 2 = DIJITOS
            concatenarCharEnString(); //CONCATENO EL CARACTER QUE ENTRO EN ARRAY (tokenCaracter)
        }else {
            //ESTADO DE ACEPTACION (CORTE DE CADENA)
            estado = '3';
            VieneDeEstadoAceptacion = true;
        }
    }
}

void obtenerCadena(){

          //WHILE QUE RECORRE ARCHIVO CARACTER POR CARACTER

    while(feof(archivo) == 0 && estado == '1' || estado == '2'){
        caracter=fgetc(archivo); //VARIABLE ENCARGADA DE OBTENER CARACTER QUE ENTRO

        //VERIFICAR SI EL SIGUINETE ES CAENA
       if(checarAlfabeto(alfabetoCadena ,caracter)|| checarAlfabeto(alfabetoLetras,caracter) || checarAlfabeto(alfabetoNumeros ,caracter) || caracter == ' ' ){
            estado = '2'; //CAMBIO DE ESTADO A 2 = CADENA
            concatenarCharEnString();

        }else  {
            //ESTADO DE ACEPTACION (CORTE DE CADENA)

            estado = '3';
             VieneDeEstadoAceptacion = true;
        }
    }


}

//FUNCION AUTOMATA PARA OBTENER DIGITOS
void obtenerDigitos(){

         //WHILE QUE RECORRE ARCHIVO CARACTER POR CARACTER

    while(feof(archivo) == 0 && estado == '1' || estado == '2'){
        caracter=fgetc(archivo); //VARIABLE ENCARGADA DE OBTENER CARACTER QUE ENTRO

        //VERIFICAR SI EL SIGUINETE ES NUMERO
       if(checarAlfabeto(alfabetoNumeros ,caracter)){
            estado = '2'; //CAMBIO DE ESTADO A 2 = DIJITOS
            concatenarCharEnString(); //CONCATENO EL CARACTER QUE ENTRO EN ARRAY (tokenCaracter)
        }else {
            //ESTADO DE ACEPTACION (CORTE DE CADENA)
            estado = '3';
            VieneDeEstadoAceptacion = true;
        }
    }
}

//FUNCION AUTOMATA PARA OBTENER IDENTIFICADOR O PALABRA RESERVADA
void obtenerIdentificador(){
    //WHILE QUE RECORRE ARCHIVO CARACTER POR CARACTER

    while(feof(archivo) == 0 && estado == '1' || estado == '2'){
        caracter=fgetc(archivo); //VARIABLE ENCARGADA DE OBTENER CARACTER QUE ENTRO

        //VERIFICAR SI EL SIGUINETE CARACTER ES LETRA O NUMERO
        if(checarAlfabeto(alfabetoLetras , caracter)){
            estado = '1'; //CAMBIO DE ESTADO A 1 = LETRAS
            concatenarCharEnString(); //CONCATENO EL CARACTER QUE ENTRO EN ARRAY (tokenCaracter)

        }else if(checarAlfabeto(alfabetoNumeros ,caracter)){
            estado = '2'; //CAMBIO DE ESTADO A 2 = DIJITOS
            concatenarCharEnString(); //CONCATENO EL CARACTER QUE ENTRO EN ARRAY (tokenCaracter)
        }else {
            //ESTADO DE ACEPTACION (CORTE DE CADENA)
            estado = '3';
            VieneDeEstadoAceptacion = true;
        }
    }
}


void concatenarCharEnString(){ //UTILIZA VARIABLES GLOBALES (pToken , caracter)
     *pToken = caracter;
      pToken++;
}




void limpiarArrayCadena(){ //UTILIZA VARIABLE GLOBAL (tokenCaracter)
    int cont = 0;
while(cont < 50){
    tokenCaracter[cont]=0;
    cont++;
}

}

NODO* CrearNodo(TOKEN token){
    NODO *nuevo = NULL;

    nuevo = (NODO*)malloc(sizeof(NODO));

    if(nuevo != NULL){
        nuevo->info = token;
        nuevo->der = NULL;
        nuevo->izq = NULL;
    }

    return nuevo;

}

//LISTA
void insertar(struct Token token){
    NODO *nuevo = NULL;
    nuevo = CrearNodo(token);

    if(raiz == NULL){
        raiz = nuevo;
        actual = nuevo;
   }else{
        nuevo->izq = actual;
        actual->der = nuevo;
        actual = nuevo;
   }
}




void ImprimirLista(){
    printf("\n");
    actual = raiz;
    printf("\n");
    printf("----------LISTA ENLAZADA----------");
    printf("\n");
	if(raiz!=NULL){
		while(actual != NULL){
			printf("\n-------STRUCT TOKEN------\n");
			printf(actual->info.lexema);
			printf("\n");
			printf("[%d]",actual->info.tipoToken);
			printf("\n");
			printf("[%d]",actual->info.valor);
			printf("\n");
			printf("-------FIN STRUCT TOKEN------");
			actual = actual->der;
		}
	}else{
		printf("\n La lista se encuentra vacia\n\n");
	}
}

void ImprimirListaRev(){
     //RECORREMOS HASTA YEGAR A LA ULTIMA POSICION
     while(actual->der != NULL){
        actual = actual->der;
    }

    while(actual != NULL){
        printf("%c",'\n');
        printf(actual->info.lexema);
        actual = actual->izq;
    }
}



