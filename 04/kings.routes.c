/* 
    5. Реализовать нахождение количества маршрутов шахматного короля с учётом ограничений на перемещение из урока, 
        с препятствиями (где единица - это наличие препятствия, а ноль - свободная для хода клетка)

    P.S.
    Изменение: для обозначения препятствия (для наглядности) использовано значение -1.
*/

#include <stdio.h>
#include <stdlib.h>  // Для exit () и atexit ()
#include <locale.h>  // Для setlocale (LC_ALL, "")
#include <time.h>

#define GAME_SIZE 6
#define MAX_BARRIERS 3

// Будем считать, что доска квадратная, но это не принципиально
int ** newTable (void) {
    int **iTable;

    const int sizeY = GAME_SIZE;
    const int sizeX = GAME_SIZE;

    // Выделение памяти для двухмерного массива [int][int]
    iTable = calloc (sizeY, sizeof (int*));
    for (int i = 0; i < sizeY; i++) {
        iTable [i] = calloc (sizeX, sizeof(int));
        // Инициализируем нулями
        for (int j = 0; j < sizeX; j++)
            iTable [i][j] = 0;
    }

    return iTable;
}

// Garbage collector
void delTable (int **iTable) {

    const int sizeY = GAME_SIZE;
    // Халява закончилась -(
    for (int i = 0; i < sizeY; i++)
        free (iTable [i]);

    free (iTable);
}

// Print array [int][int]
void printTable (int **iTable) {

    const int sizeY = GAME_SIZE;
    const int sizeX = GAME_SIZE;

    for (int y = 0; y < sizeY; ++y) {
        for (int x = 0; x < sizeX; ++x) {
            printf("%5d", iTable [x][y]);
        }
        printf("\n");
    }
}

// Создает случайное количество препятсвий в количестве [0...MAX_BARRIERS].
//  Размещет препятсвия в [iTable] по случайным координатам.
//  Возращает количество созданных на доске препятсвий.
int makeBarriers (int **iTable) {
    
    srand (time (NULL));
    int count = rand () % MAX_BARRIERS;

    // Генерация координат барьеров
    const int sizeY = GAME_SIZE;
    const int sizeX = GAME_SIZE;
    int i = 0;
    while (i < count) {
        int y = rand () % sizeY;
        int x = rand () % sizeX;

        // Препятсвие не может располагаться в левом верхнем или правом нижнем углу.
        if ((y == 0 && x == 0) || (y == sizeY - 1 && x == sizeX - 1))
            continue;
        else if (iTable[x][y] == -1) {
        // Если препятствие было создано ранее по этим координатами
            continue;
        }

        // Создаем препятсвие
        iTable[x][y] = -1;
        
        // Следующее препятсвие
        i++;
    }

    // return
    return count;
}

// S (m, n) = S (m-1, n) + S (m, n-1);
// S (m, n) = 1, если одна из координат равна нулю
// S (m, n) = 0, если m и n это стартовые координаты
int calcRoutes (int x, int y, int **checkTbl) {

    if (checkTbl [x][y] == -1) // Препятсвие
        return 0;
    if (x == 0 && y == 0)
        return 0;
    else if (x == 0) {
        if (calcRoutes (x, y - 1, checkTbl) == 0 && y != 1)
            return 0; // мы не можем пройти через стенку слева (x=0),
                      // при этом есть препятсвие сверху (y-1)
        return 1;
    } else if (y == 0) {
        if (calcRoutes (x - 1, y, checkTbl) == 0 && x != 1)
            return 0; // мы не можем пройти через потолок сверху (y=0),
                      // при этом есть препятсвие слева (x-1)
        return 1;
    }
    // return
    return calcRoutes (x, y - 1, checkTbl) + calcRoutes (x - 1, y, checkTbl);
}

// Функция, вызываемая при завершении работы
void endFunction (void)
{   
    // Вывод сообщения о завершении работы
    puts ("\nthe work is completed!");
}

// main
int main(void) {

    // Русский язык в консоли
    setlocale(LC_ALL, "");

    // Регистрация функции, которая будет вызвана, при нормальном завершении работы.
    if (atexit (endFunction)) {
        // Проверка регистрации функции endFunction
        puts ("post- function registration error!");
    }

    int **srcTable = newTable ();
    int **dstTable = newTable ();

    // Создать на поле препятствия
    int count = makeBarriers (srcTable);

    const int sizeY = GAME_SIZE;
    const int sizeX = GAME_SIZE;

    // Рекурсивный подсчет маршрутов
    for (int y = 0; y < sizeY; y++)
        for (int x = 0; x < sizeX; x++) 
            dstTable [x][y] = calcRoutes (x, y, srcTable);

    // Вывод в консоль
    printf("initial conditions\ntable size: %dx%d\n", sizeX, sizeY);
    printf("count of barriers: %d\n", count);
    printTable (srcTable);
    puts("\nexecution result:");
    printTable (dstTable);

    // garbage collector
    delTable (srcTable);
    delTable (dstTable);

    // return o.k.
    return EXIT_SUCCESS;
}