#include "utils.h"

/////////////////////////////////////////////////////////////////////
///////////////// AUXILIARES  ///////////////////////////////////////
////////////////////////////////////////////////////////////////////
// Funcion que agrega al final de un wheel, una letra (Funcion auxiliar para makeWheelFromString)
void wheelAddLast(struct wheel* w, char letter, int position){
  //Crea un nuevo nodo
    struct letter* newLetter = (struct letter*)malloc(sizeof(struct letter));
    newLetter->letter = letter;
    newLetter->position = position;
    newLetter->next = NULL;
//Si el primero de la rueda está vacío, el primero de la rueda es el nuevo nodo creado
    if (w->first == NULL){
        w->first = newLetter;
    } else {
      //Creamos un current que apunta al primero de la rueda
        struct letter* current = w->first;
      //Mientras el siguiente de current está vacío el current es igual al siguiente
        while (current->next != NULL){
            current = current->next;
        }
    //El siguiente del current es igual 
        current->next = newLetter;
    }
    if (w->first != newLetter) {
        newLetter->next = w->first;
    }
}

/////////////////////////////////////////////////////////////////////
///////////////// EJERCICIO 1 //////////////////////////////////////
////////////////////////////////////////////////////////////////////
int strLen(char* src) {
  if (src == NULL) {
    return 0;
  } else {
    int indice = 0;
    while (src[indice] != '\0') {
      indice++;
    }
    return indice;
  }
}

char* strDup(char* src) {
  int caracteres = strLen(src);
  char* duplicate = (char*)malloc(sizeof(char) * (caracteres + 1));
  // solicitamos memoria para el nuevo str y le sumamos 1 por el ultimo caracter
  int i = 0;
  while (i < caracteres) {
    duplicate[i] = src[i]; // copiamos los caracteres de "src" a duplicate
    i++;
  }
  duplicate[i] = '\0'; // le agregamos el caracter nulo del str
  return duplicate;
}

/////////////////////////////////////////////////////////////////////
///////////////// EJERCICIO 2 //////////////////////////////////////
////////////////////////////////////////////////////////////////////

int letterToIndex(char letter) {
  if ('A' <= letter && letter <= 'Z')
    return letter - 'A';
  return 0;
}

char indexToletter(int index) {
  if (0 <= index && index <= 25)
    return index + 'A';
  return 0;
}

void setWheel(struct wheel* w, int position) {
  struct letter* current = w->first;
  while (current->position != position) {
    current = current->next;
  }
  w->first = current;
}

void wheelPrint(struct wheel* w) {
  printf("%s", w->alphabet);
  struct letter *current = w->first;
  int i = 0;
  while (i < w->count) {
    printf("(%c-%i)", current->letter, current->position);
    current = current->next;
    i++;
  }
}

struct wheel* makeWheelFromString(char* alphabetPermutation) {
    int count = strLen(alphabetPermutation);

    struct wheel* newWheel = (struct wheel*) malloc(sizeof(struct wheel));
    
    // Verifica si la asignación de memoria tuvo éxito
    if (newWheel == NULL) {
        return NULL;  // Manejo de error
    }
    
    struct letter* current = NULL; // Inicializa el puntero current
    
    for (int i = 0 ; i < count; i++) {
        struct letter* newLetter = (struct letter*) malloc(sizeof(struct letter));
        // Verifica si la asignación de memoria tuvo éxito
        if (newLetter == NULL) {
            wheelDelete(newWheel); // Libera memoria previamente asignada
            return NULL;  // Manejo de error
        }
        newLetter->letter = alphabetPermutation[i];
        newLetter->position = i; 
        
        if (i == 0) {
            newWheel->first = newLetter;
            current = newLetter;  // Establece current al primer nodo
        } else {
            current->next = newLetter;
            current = newLetter; // Avanza current al nuevo nodo
        }
        newLetter->next = newWheel->first;
    }
    
    newWheel->alphabet = strDup(alphabetPermutation); // Haz una copia del alfabeto
    newWheel->count = strLen(alphabetPermutation);
    return newWheel;
}


void rotateWheel(struct wheel* w, int steps) {
    int i = 0;
    // Verifica si el número de pasos es 0 o si la rueda está vacía
    if (steps == 0 || w->count == 0) {
        return;
    } else {
        for (i = 0; i < steps; i++) {
            w->first = w->first->next;
        }
    }
}


void rotateWheels(struct wheel** w, int wheelsCount) {
    int final = 25;
    for (int i = 0; i < wheelsCount; i++) {
        final *= 26; // Corrección: utilizar multiplicación abreviada
    }
    int p = 0;
    while (p <= final) {
        int previo = 0; // Mover la inicialización dentro del bucle
        int i = 0;

        while (w[previo]->first->position == 26) {
            rotateWheel(w[previo], 1);
        }
        rotateWheel(w[previo], 1);

        for (int contador = 0; contador < wheelsCount; contador++) {
            if (w[i]->first->position == 26) {
                rotateWheel(w[i], 1);
                i++;
                if (i < wheelsCount) {
                    rotateWheel(w[i], 1);
                }
            }
        }
        p++;
    }
}



void wheelDelete(struct wheel *w) {
    struct letter* current = w->first;
    // Caso 1 letra
    if (w->count == 1){
        free(current);
        w->first = 0;
        w->count = 0;
        free(w->alphabet);
    } 
    // Caso 2 o mas letras
    else {
        for ( int i = 0 ; i < strLen(w->alphabet) ; i++){
            struct letter* nextLetter = current->next;
            free(current);
            current = nextLetter;
        }
        w->first = 0;
        w->count = 0;
        free(w->alphabet);
        free(w);
    }
}
/////////////////////////////////////////////////////////////////////
///////////////// EJERCICIO 3 //////////////////////////////////////
////////////////////////////////////////////////////////////////////

char encryptWheel(struct wheel* w, char letter) {
  int index = letterToIndex(letter);
  struct letter *current = w->first;
  int i = 0;
  while (i < index) {
    current = current->next;
    i++;
  }
  return current->letter;
}

char decryptWheel(struct wheel* w, char letter) {
  struct letter *current = w->first;
  int i = 0;
  while (current->letter != letter) {
    current = current->next;
    i++;
  }
  return indexToletter(i);
}

void littleEnigmaPrint(struct littleEnigma* le) {
  for (int i = 0; i < le->wheelsCount; i++) {
    wheelPrint(le->wheels[i]);
    printf("\n");
  }
}

struct littleEnigma* littleEnigmaNew(char** alphabetPermutation, int count){

    struct littleEnigma* newEnigma = (struct littleEnigma*)malloc(sizeof(struct littleEnigma));
    // Caso ninguna alphabetpermutation
    if (count == 0){
        newEnigma->wheels = NULL;
        newEnigma->wheelsCount = 0;
        return newEnigma;
    } else {
        newEnigma->wheels = (struct wheel**)malloc(count * sizeof(struct wheel*));
        newEnigma->wheelsCount = count;

        for (int i = 0; i < count; i++){
            char* alphabetCopy = strDup(alphabetPermutation[i]);
            struct wheel* newWheel = makeWheelFromString(alphabetCopy);
            newEnigma->wheels[i] = newWheel;            
        }
    }
    return newEnigma;
}

void littleEnigmaSet(struct littleEnigma* le, int* positions) {
    for (int i = 0; i < le->wheelsCount; i++) {
        setWheel(le->wheels[i], positions[i]);
    }
}

char* littleEnigmaEncrypt(struct littleEnigma* le, char* text){
    char* copiaText = strDup(text);
    int largoText = strLen(text);
    for (int i = 0; i < largoText; i++){
      copiaText[i] = encryptOneLetter(le, copiaText[i]);
    }
    return copiaText;
}

char* littleEnigmaDecrypt(struct littleEnigma* le, char* code) {
    char* copiaCode = strDup(code);
    int largoCode = strLen(code);
    for (int i = 0; i < largoCode; i++){
      copiaCode[i] = decryptOneLetter(le, copiaCode[i]);
    }
    return copiaCode;
}

void littleEnigmaDelete(struct littleEnigma* le) {
    for(int i = 0; i < le->wheelsCount; i++){
      wheelDelete(le->wheels[i]);
    }
  free(le->wheels);
  free(le);
}
char encryptOneLetter(struct littleEnigma* le, char letter) {
  for (int i = 0; i < le->wheelsCount; i++) {
    letter = encryptWheel(le->wheels[i], letter);
  }
  rotateWheels(le->wheels, le->wheelsCount);
  return letter;
}

char decryptOneLetter(struct littleEnigma* le, char letter) {
  rotateWheels(le->wheels, le->wheelsCount);
  for (int i = le->wheelsCount - 1; i >= 0; i--) {
    letter = decryptWheel(le->wheels[i], letter);
  }
  return letter;
}



////////////////////////////////////////////////////////////////////
/////////////////FUNCIONES AUXILIARES///////////////////////////////
////////////////////////////////////////////////////////////////////
