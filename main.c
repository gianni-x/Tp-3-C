#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

int main() {
    printf("\n");
    
  // strLen
    printf("########### strLen ###########\n");

    // Caso vacio
    int len1 = strLen("");
    // Caso 1 caracter 
    int len2 = strLen("a");
    // Caso todos los caracteres validos distintos de cero
    int len3 = strLen("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ12345678910_+-=|;:,.<>?/~");

    printf("strDup(\"\") -> \"%i\"\n", len1);
    printf("strDup(\"a\") -> \"%i\"\n", len2);
    printf("strDup(\"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ12345678910_+-=|;:,.<>?/~\") -> \"%i\"\n", len3);
    printf("\n");




  // strDup
    printf("########### strDup ###########\n");

    // Caso vacio
    char* dup1 = strDup("");
    // Caso 1 caracter
    char* dup2 = strDup("a");
    // Caso todos los caracteres validos distintos de cero
    char* dup3 = strDup("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ12345678910_+-=|;:,.<>?/~");

    printf("strDup(\"\") -> \"%s\"\n", dup1);
    printf("strDup(\"a\") -> \"%s\"\n", dup2);
    printf("strDup(\"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ12345678910_+-=|;:,.<>?/~\") -> \"%s\"\n", dup3);
    printf("\n");

    free(dup1);
    free(dup2);
    free(dup3);
    



  // makeWheelFromString
    printf("########### makeWheelFromString ###########\n");


    // Caso 1 caracter
    struct wheel* w1 = makeWheelFromString("A");

    // Caso 10 caracteres
    struct wheel* w2 = makeWheelFromString("ABCDEFGHIJ");

    // Caso 26 caracteres
    struct wheel* w3 = makeWheelFromString("ABCDEFGHIJKLMNOPQRSTUVWXYZ"); 


    wheelPrint(w1);
    printf("\n");
    wheelPrint(w2);
    printf("\n");
    wheelPrint(w3);
    printf("\n\n");



  // rotateWheel
    printf("########### rotateWheel ###########\n");

    struct wheel* w4 = makeWheelFromString("CABDEFGHIJKLMNOPQRSTUVWXYZ"); // 26 caracteres
    struct wheel* w5 = makeWheelFromString("ZYXWVUTSRQPONMLKJIHGFEDCBA"); // 26 caracteres
    struct wheel* w6 = makeWheelFromString("ABCDE"); // 5 caracteres
    struct wheel* w7 = makeWheelFromString("A"); // 1 caracter
    
    printf("Antes");
    printf("\n");
    
    wheelPrint(w4);
    printf("\n");
    // Caso rotar 26 caracteres, 1 posicion
    rotateWheel(w4, 1);
    
    // Caso rotar 26 caracteres, 26 posiciones
    wheelPrint(w5);
    printf("\n");
    rotateWheel(w5, 26);
    
    wheelPrint(w6);
    printf("\n");
    // Caso rotar 5 caracteres, 26 posicion
    rotateWheel(w6, 26);
    
    wheelPrint(w7);
    printf("\n");
    // Caso rotar 1 caracter, 26 posicion
    rotateWheel(w7, 26);
    
    printf("Despues");
    printf("\n");
    wheelPrint(w4);
    printf("\n");
    wheelPrint(w5);
    printf("\n");
    wheelPrint(w6);
    printf("\n");
    wheelPrint(w7);
    printf("\n\n");



   // wheelDelete
    printf("########### wheelDelete ###########\n");

    struct wheel* w8 = makeWheelFromString("A");
    struct wheel* w9 = makeWheelFromString("ABCD");
    struct wheel* w10 = makeWheelFromString("ABCDEFGHIJ");  

    wheelPrint(w8);
    printf("\n");
    wheelPrint(w9);
    printf("\n");
    wheelPrint(w10);
    printf("\n");

    wheelDelete(w8);
    wheelPrint(w8);
    printf("\n");
    
    wheelDelete(w9);
    wheelPrint(w9);
    printf("\n");
    
    wheelDelete(w10);
    wheelPrint(w10);
    printf("\n\n");



  // littleEnigma
    printf("########### littleEnigmaNew ###########\n");
    
    char* alphabetPermutation[2];
    alphabetPermutation[0] = "JGDQOXUSCAMIFRVTPNEWKBLZYH";
    alphabetPermutation[1] = "NTZPSFBOKMWRCJDIVLAEYUXHGQ";
    struct littleEnigma* le = littleEnigmaNew(alphabetPermutation, 2); // 1 littleEnigma con 2 wheels
    littleEnigmaPrint(le);
    printf("\n\n");


    int password[2] = { 3 , 5 };
    littleEnigmaSet(le, password);
    littleEnigmaPrint(le);
    printf("\n\n");

    char* text = "TEXT";
    char* code = littleEnigmaEncrypt(le, text);
    littleEnigmaPrint(le);
    printf("%s -> %s\n\n", text, code);

    littleEnigmaSet(le, password);
    littleEnigmaPrint(le);
    printf("\n\n");

    char* decode = littleEnigmaDecrypt(le, code);
    littleEnigmaPrint(le);
    printf("%s -> %s -> %s\n\n", text, code, decode);

    if(code) free(code);
    if(decode) free(decode);

    littleEnigmaDelete(le);

    return 0;
}
