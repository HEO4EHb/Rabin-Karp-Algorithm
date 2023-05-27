﻿#include <iostream>
using namespace std;

//d - количество символов в алфавите
#define d 256

/*
* /Шаг 1
Прикладываем левый край образца к левому краю текста, К =
Вычисляем хеш-значения hq и hs для q и для s[0…M-1]
 /Шаг 2
Если hq == hs, то проверяем, входит ли образец в текст,
начиная с К-й позиции, последовательным сравнением
символов образца q[j] с символами текста s[K+j] слева
направо, j=0…M-1
 /Шаг 3
Если имеем M совпадений, то образец в тексте найден – конец
работы
Если K+M >= N, то образец в тексте не найден – конец работы
Иначе вычисляем hs для s[K+1…K+M], используя hs для s[K…
K+M-1], K = K+1 и переходим к шагу 2
*/

void search(char pat[], char txt[], int q)
{
    int M = strlen(pat);
    int N = strlen(txt);
    int i, j;
    int p = 0; //p - хэшфункция для образца     
    int t = 0; //t - хэшфункция для текста
    int h = 1;

    // h=pow(d, M-1)%q
    for (i = 0; i < M - 1; i++)
        h = (h * d) % q;

    // Считаем хэн фунцию образца и текста 
    for (i = 0; i < M; i++) {
        p = (d * p + pat[i]) % q;
        t = (d * t + txt[i]) % q;
    }

    // свдигаем образец над текстом 
    for (i = 0; i <= N - M; i++) {

        // проверяем хэш образца и текста . если совпадают проверяем символы один за одним
        if (p == t) {
            /* проверяем символы один за одним*/
            for (j = 0; j < M; j++) {
                if (txt[i + j] != pat[j]) {
                    break;
                }
            }

            // если p == t и pat[0...M-1] = txt[i, i+1,
            // ...i+M-1]
            if (j == M)
                cout << "Pattern found at index " << i
                << endl;
        }

        // Считаем хэш функцию для текста :
        // Удаляем начальную цифру, добавляем конечную цифру
        if (i < N - M) {
            t = (d * (t - txt[i] * h) + txt[i + M]) % q;

            // если t отрицательно делаем положительной
            if (t < 0)
                t = (t + q);
        }
    }
}

int main()
{
    char txt[] = "AABCDEFGHIKABC";
    char pat[] = "ABC";

    // делаем q макс чтобы избежать колизии
    int q = INT_MAX;
    
    search(pat, txt, q);
    return 0;
}