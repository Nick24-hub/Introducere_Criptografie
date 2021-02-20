#include <iostream>
#include <fstream>
#include <cstring>
#include <time.h>  

using namespace std;

ifstream fin("in.txt");
ofstream fout("out.txt");
ofstream kout("key.txt");
ofstream edout("inputedit.txt");


void key_generator(char key[100])
{
    srand(time(NULL));
    int k = 0;
    // generez aleatoriu lungimea si cheia in sine
    int klg = rand() % 99 + 2;
    for (int i = 0;i < klg;i++)
    {
        key[k] = rand() % 26 + 'A';
        kout << key[k];
        k++;
    }
}

void edit_and_encript(char key[100])
{
    int i = 0, j = 0, a;
    int klg = strlen(key);
    char x, y;
    // citesc caracter cu caracter din fisier
    while (!fin.eof())
    {
        fin >> x;
        if (x >= 'a' && x <= 'z' || x >= 'A' && x <= 'Z') // daca e litera
        {
            edout << (char)toupper(x); // o convertesc in litera mare si o salvez
            a = i % klg; // creez indexul pentru cheie
            y = (toupper(x) + key[a] - 2 * 'A') % 26 + 'A'; // am adaptat formula de la laborator
            fout << y;
            i++;
        }
    }
}


int main()
{
    char key[100];
    memset(key, '\0', 100);
    key_generator(key);
    edit_and_encript(key);
}
