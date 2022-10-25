// *** Урок 16. Введение в криптографию

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>  // Для setlocale (LC_ALL, "")
#include <stdbool.h>
#include <string.h>

//#define DEBUG

/*
 * 1.Реализовать шифрование и расшифровку цезаря с передаваемым в функцию сообщением и ключом
 */

#define encCaesar(X,Y) makeCaesar((X), (Y), true)
#define decCaesar(X,Y) makeCaesar((X), (Y), false)

// encoding/decoding by rearrange
unsigned char* makeCaesar (const char* srcStr, int key, bool encrypt) {

    if (!srcStr || !(key > 0)) return NULL;
    int i, msgSize = strlen (srcStr);
    if (!msgSize) return NULL;
    unsigned char* outStr = malloc (msgSize * sizeof (unsigned char) + 1);

    key %= 128;
    for (i = 0; i < msgSize; ++i) {
        int code = (srcStr [i] + key * (encrypt ? 1 : -1)) % 128;
        code = ((code > 0) ? code : 128 + code);
        outStr [i] = (unsigned char)code;
    } // for (i = 0; i < size; i++)
    outStr [msgSize] = '\0';
    
    // return
    return outStr;
} // makeCaesar

// encoding Caesar
unsigned char* encCaesar2 (const char* srcStr, int key) {
    if (!srcStr) return NULL;
    int i, size = strlen (srcStr);
    if (!size) return NULL;
    unsigned char* encStr = malloc (size + 1);
    key %= 128;
    for (i = 0; i < size; i++) {
        if (srcStr [i] == '\0') {
            encStr [i] =  '\0';
            break;
        }
        encStr [i] = ((unsigned char)srcStr [i] + key) % 128;
    } // for (i = 0; i < size; i++)
    encStr [i] = '\0';
    // return
    return encStr;
} // encCaesar

// decoding Caesar
unsigned char* decCaesar2 (const char* encStr, int key) {
    if (!encStr) return NULL;
    int i, size = strlen (encStr);
    if (!size) return NULL;
    unsigned char* srcStr = malloc (size + 1);
    key %= 128;
    for (i = 0; i < size; i++) {
        if (encStr [i] == '\0') {
            srcStr [i] =  '\0';
            break;
        }
        int code = encStr [i] - key;
        srcStr [i] = (unsigned char)((code > 0) ? code : 128 + code);
    } // for (i = 0; i < size; i++)
    srcStr [i] = '\0';
    // return
    return srcStr;
} // decCaesar

/*
 * 2.Реализовать шифрование и расшифровку перестановками 
 *   с передаваемым в функцию сообщением и количеством столбцов
 */

#define encReArrange(X,Y) makeReArrange((X), (Y), true)
#define decReArrange(X,Y) makeReArrange((X), (Y), false)

// encoding/decoding by rearrange
unsigned char* makeReArrange (const char* srcStr, int key, bool encrypt) {

    if (!srcStr || !(key > 0)) return NULL;
    int  msgSize = strlen (srcStr);
    if (!msgSize) return NULL;

    // кол-во строк в таблице
    int rows = msgSize / key + ((msgSize % key) ? 1 : 0);
    int tblSize = key * rows;
    unsigned char* outStr = malloc (tblSize * sizeof (unsigned char) + 1);
    int count = 0;
    // если происходит расшифровка, то таблица разворачивается
    int cols = (encrypt ? key : rows);
    for (int i = 0; i < cols; ++i)
        for (int j = i; j < tblSize; j += cols)
            outStr [count++] = (unsigned char)((j < msgSize) ? srcStr [j] : '-');
    outStr [tblSize] = '\0';

    // return
    return outStr;
} // makeReArrange

// encoding by rearrange
unsigned char* encReArrange2 (const char* srcStr, const int COLS) {

    if (!srcStr || !(COLS > 0)) return NULL;
    int  size = strlen (srcStr);
    if (!size) return NULL;
        
    // кол-во строк в таблице
    int rows = size / COLS + ((size % COLS > 0) ? 1 : 0);
    unsigned char* encStr = malloc (rows * COLS + 1);
    unsigned char** array = malloc (rows * sizeof (char*));
    
    // таблица перекодировки
    for (int i = 0; i < rows; i++)
        array [i] = malloc (COLS);

    // 1.запись сообщения по горизонтали
    int count = 0;
    count = 0;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < COLS; j++)
            array [i][j] = (count < size) ? srcStr [count++] : ' ';

    // 2.сборка сообщения по вертикали
    count = 0;
    for (int j = 0; j < COLS; j++)
        for (int i = 0; i < rows; i++)
            //encStr [count++] = *(*(array + i) + j);
            encStr [count++] = array [i][j];
    
    // 3.конец строки
    encStr [rows*COLS] = '\0';

    // garbage collection
    for (int i = 0; i < rows; i++) {
        free (*(array + i));
    } // for (int i = 0; i < rows; i++)
    free (array);

    // return
    return encStr;
} // encReArrange2

// decoding by rearrange
unsigned char* decReArrange2 (const char* encStr, const int COLS) {

    if (!encStr || !(COLS > 0)) return NULL;
    int  size = strlen (encStr);
    if (!size) return NULL;
        
    // кол-во строк в таблице
    int rows = size / COLS + ((size % COLS > 0) ? 1 : 0);
    unsigned char* srcStr = malloc (rows * COLS + 1);
    unsigned char** array = malloc (rows * sizeof (char*));
    
    // таблица перекодировки
    for (int i = 0; i < rows; i++)
        array [i] = malloc (COLS);

    // 1.запись сообщения по вертикали
    int count = 0;
    for (int j = 0; j < COLS; j++)
        for (int i = 0; i < rows; i++)
            //encStr [count++] = *(*(array + i) + j);
            array [i][j] = (count < size) ? encStr [count++] : ' ';

    // 2.сборка сообщения по горизонтали
    count = 0;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < COLS; j++)
            srcStr [count++] = array [i][j];
    
    // 3.конец строки
    srcStr [rows*COLS] = '\0';

    // garbage collection
    for (int i = 0; i < rows; i++) {
        free (*(array + i));
    } // for (int i = 0; i < rows; i++)
    free (array);

    // return
    return srcStr;
} // decReArrange2

// Функция, вызываемая при завершении работы
void endFunction (void)
{
    // Вывод сообщения о завершении работы
    puts ("\nthe work is completed!");
}

// main
int main (void) {

    // Русский язык в консоли
    setlocale (LC_ALL, "");

    // Регистрация функции, которая будет вызвана, при нормальном завершении работы.
    if (atexit (endFunction)) {
        // Проверка регистрации функции endFunction
        puts ("post- function registration error!");
    }

    // Урок 16. Введение в криптографию
    puts ("Lesson 16. Introduction to Cryptography.\n");

    // Упражнение №1
    const char srcMsg1 [] = "Ave, Caesar, morituri te salutant.",
               srcMsg2 [] = "Actum est ilicet!";
    unsigned char *encMsg3, *encMsg7;
    int key3 = 3, key7 = 7;

    puts  ("\nExercise #1: Implement Caesar encryption and decryption.\n");
    printf ("1.\nthe first message is : \"%s\"\n", srcMsg1);
    encMsg3 = encCaesar (srcMsg1,key3);
    printf ("encoding with key [%d]: \"%s\"\n", key3, encMsg3);
    printf ("the second message is: \"%s\"\n", srcMsg2);
    encMsg7 = encCaesar (srcMsg2,key7);
    printf ("encoding with key [%d]: \"%s\"\n", key7, encMsg7);

    unsigned char *decMsg3, *decMsg7;
    decMsg3 = decCaesar (encMsg3, key3);
    printf ("2.\ndecoding with key [%d]: \"%s\"\n", key3, decMsg3);
    decMsg7 = decCaesar (encMsg7, key7);
    printf ("decoding with key [%d]: \"%s\"\n", key7, decMsg7);

    // garbage collection
    if (encMsg3) free (encMsg3);
    if (encMsg7) free (encMsg7);
    if (decMsg3) free (decMsg3);
    if (decMsg7) free (decMsg7);

    // Упражнение №2
    puts  ("\nExercise #2: Implement encryption and decryption by rearrange.\n");
    unsigned char *encMsg4, *encMsg5;
    int key4 = 4, key5 = 5;

    printf ("1.\nthe first message is : \"%s\"\n", srcMsg1);
    encMsg4 = encReArrange (srcMsg1, key4);
    printf ("encoding with key [%d]: \"%s\"\n", key4, encMsg4);
    printf ("the second message is: \"%s\"\n", srcMsg2);
    encMsg5 = encReArrange (srcMsg2, key5);
    printf ("encoding with key [%d]: \"%s\"\n", key5, encMsg5);

    unsigned char *decMsg4, *decMsg5;
    decMsg4 = decReArrange (encMsg4, key4);
    printf ("2.\ndecoding with key [%d]: \"%s\"\n", key4, decMsg4);
    decMsg5 = decReArrange (encMsg5, key5);
    printf ("decoding with key [%d]: \"%s\"\n", key5, decMsg5);

    // garbage collection
    if (encMsg4) free (encMsg4);
    if (encMsg5) free (encMsg5);
    if (decMsg4) free (decMsg4);
    if (decMsg5) free (decMsg5);

    // return o.k.
    return EXIT_SUCCESS;
} // main
