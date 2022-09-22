#include <stdio.h> //printf
#include <stdlib.h>
#include<stdbool.h>// Booleanos


#include <string.h>


//CONSTANTES NUMERICAS
typedef enum {
id = 1,
sim = 2,
num = 3,
palres = 4,
estadoAceptacion = 5
}TypeToken;

//NUEVA ESTRUCTURA
typedef struct {
TypeToken tipoToken;
char * lexema;
int valor;
}Token;





//DECLARACION DE FUNCION AUTOMATA PARA OBTENER IDENTIFICADOR
void obtenerIdentificador();

//DECLARACION DE FUNCION PARA CHECAR CARACTER CON ALFABETO
bool checarAlfabeto(char alfabeto[] , char caracter);

//DECLARACION DE FUNCION PARA IR ALMACENANDO CARACTER POR CARACTER EN VARIABLE
void concatenarCharEnString();

//LIMPIAR ARRAY DE CADENAS
void limpiarArrayCadena();

//DECLARACION DE ALFABETOS PARA AUTOMATAS
char alfabetoLetras[] = "ABCDEFGHIJKLMNÑOPQRSTVXYZabcdefghijklmnñopqrstvxyz";
char alfabetoNumeros[] = "0123456789";
char alfabetoSimbolos[] = ";.-_()/=?{}:!#$%&/¿'¡+*][ ";
int indice; //VARIABLE ENCARGADA DE SABER EL INDICE EN ALFABETO

//DECLARACION DE VARIABLE DE TIPO FILE PARA TRABAJAR CON ARCHIVOS DE TEXTO
FILE * archivo;

//VARIABLE ENCARGADA DE LEER CARACTER POR CARRACTER EN ARCHIVO DE TEXTO
char caracter;

//VARIABLE ENCARGADA DE LOS ESTADOS DE LOS AUTOMATAS
char estado;

//VARIABLE DONDE SE GUARDAN LOS TOKEN CARCTER POR CARACTER
char tokenCaracter[50];
char * pToken;//VARIABLE QUE SE COMPORTARA COMO PUNTERO PARA 'tokenCaracter'

//VARIABLE BOOL ENCARGADA DE DECIRLE AL PUNTERO
//DEL ARCHIVO DE TEXTO QUE VIENE DE UNA ACEPTACION DE UN AUTOMATA
//POR LO TANTO EL PUNTERO NO SE INCREMENTA...
bool VieneDeEstadoAceptacion = false;



//FUNCION PRINCIPAL DEL PROGRAMA
main() {
/*
Token token[2];
token[0].tipoToken = palres;
token[0].lexema = "int";
token[0].valor= 0;

token[1].tipoToken = palres;
token[1].lexema="val1";
token[1].valor= 0;


printf("%d",token[1].tipoToken);
//printf(token[0].lexema);

return 0;
*/


//COMPARAR CADENA
/*
if(!strcmp(cadena,"la")){
    printf("hola");
}else{
    printf(cadena);
}*/







//ABRIMOS ARCHIVO PARA LEERLO
archivo=fopen("PGM.txt","r");

//VALIDACION PARA SABER SI SE PUEDE LEER DICHO ARCHIVO
if(archivo == NULL){
    printf("Error en la apertura del archivo.");
}else{
    //ARCHIVO SI SE PUDO LEER



    //WHILE PARA RECORRER EL ARCHIVO
    while(feof(archivo) == 0){

            //IF PARA SABER SI EL PUNTERO REGRESO DE UN
            //AUTOMATA DE SU ESTADO DE ACEPTACION
            if(VieneDeEstadoAceptacion){VieneDeEstadoAceptacion = false;}
            else {caracter=fgetc(archivo);}//PUNTERO SE INCREMETA Y ASIGNO EL SIGUIENTE CARACTER

              //LIMPIAMOS EL ARRAY DE LA CADENA 'tokenCaracter'
        limpiarArrayCadena();

        //ASIGNAMOS PUNBTERO A VARIABLE
        pToken = tokenCaracter;

        //CHECAR SI CARACTER QUE ENTRO ES UNA LETRA
       if(checarAlfabeto(alfabetoLetras ,caracter)){
        estado = '1';
        printf("%c",'\n');

        //AGREGAR EL CARACTER EN ARRAY CADENA
        concatenarCharEnString(); //PARAMETRO COMO VARIABLE GLOBAL (caracter)

        //FUNCION AUTOMATA PARA VALIDAR SI LOS CARACTERES SIGUIENTES FORMAN
        //UN IDENTIFICADOR O PALABRA RESERVADA
        obtenerIdentificador();//PUNTERO DE LECTURA DE ARCHIVO ENVIADO COMO VARIABLE GLOBAL

        //ESTRUCTURA DE TIPO TOKEN
        //ESTA EN PRUEBAS NO FUNCIONAL
        Token token[1];
        token[0].tipoToken = id;
        token[0].lexema = tokenCaracter;
        token[0].valor= 0;

        printf(token[0].lexema);


       }

       //CHECAR SI CARRACTER ES UN DIJITO
       else if(checarAlfabeto(alfabetoSimbolos , caracter)){
            estado = '2';
            printf("%c",'\n');
        //AGREGAR EL CARACTER EN ARRAY CADENA
        concatenarCharEnString(); //PARAMETRO COMO VARIABLE GLOBAL (caracter)


        obtenerSimbolos();

         //ESTRUCTURA DE TIPO TOKEN
        //ESTA EN PRUEBAS NO FUNCIONAL
        Token token[1];
        token[0].tipoToken = id;
        token[0].lexema = tokenCaracter;
        token[0].valor= 0;

        printf(token[0].lexema);


       }

       //CHECAR SI CARACTER ES UN DIGITO
       else if(checarAlfabeto(alfabetoNumeros , caracter)){
            estado = '2';
            printf("%c",'\n');

            //AGREGAR EL CARACTER EN ARRAY CADENA
        concatenarCharEnString(); //PARAMETRO COMO VARIABLE GLOBAL (caracter)

        obtenerDigitos();

        //ESTRUCTURA DE TIPO TOKEN
        //ESTA EN PRUEBAS NO FUNCIONAL
        Token token[1];
        token[0].tipoToken = id;
        token[0].lexema = tokenCaracter;
        token[0].valor= 0;

        printf(token[0].lexema);



       }

    }

}




return 0;
}

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

//FUNCION AUTOMATA PARA SIMBOLOS
void obtenerSimbolos(){

          //WHILE QUE RECORRE ARCHIVO CARACTER POR CARACTER

    while(feof(archivo) == 0 && estado == '1' || estado == '2'){
        caracter=fgetc(archivo); //VARIABLE ENCARGADA DE OBTENER CARACTER QUE ENTRO

        //VERIFICAR SI EL SIGUINETE ES NUMERO
       if(checarAlfabeto(alfabetoSimbolos ,caracter)){
            estado = '2'; //CAMBIO DE ESTADO A 2 = DIJITOS
            concatenarCharEnString(); //CONCATENO EL CARACTER QUE ENTRO EN ARRAY (tokenCaracter)
        }else {
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

//FUNCION PARA CONCATENAR CHAR EN STRING
void concatenarCharEnString(){ //UTILIZA VARIABLES GLOBALES (pToken , caracter)
     *pToken = caracter;
      pToken++;
}

//LIMPIAR ARRAY CADENA
void limpiarArrayCadena(){ //UTILIZA VARIABLE GLOBAL (tokenCaracter)
    int cont = 0;
while(cont < 50){
    tokenCaracter[cont]=0;
    cont++;
}

}
