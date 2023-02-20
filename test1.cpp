#define _CRT_SECURE_NO_WARNINGS
#include <locale>
#include <iomanip>
#include <iostream>
#include <stdio.h>
#include <clocale>
#include <cmath>
#include <fstream>
#include <string>

using namespace std;
const int n = 10;
int i, j, m, k, perkol = 0;
double aa, bb, temp,  det = 1;

double aCopy[n][2 * n] = {};
double perX[n][n];
double disrep[n][n];


void isPrime(double val)
{
    char buf[100];
    sprintf(buf, "%.8f", val);
    int len = strlen(buf);

    for (int i = len - 1; i > 0; i--)
    {
        if (buf[i] == '0')
        {
            buf[i] = 0;
        }
        else if (buf[i] == '.')
        {
            buf[i] = 0;
            break;
        }
        else  break;
    }
    printf(buf);
}

void CountMart(double a[n][2* n], int msize, int vsize)
{
    for (int i = 0; i < msize; i++)
    {
        for (int j = 0; j < msize + vsize; j++)
        {
            aCopy[i][j] = a[i][j];
        }
    }

    for (int s = 0; s < vsize; s++)
    {
        for (k = 0; k < msize; k++)
        {
            temp = abs(a[k][k]);
            i = k;
            for (m = k + 1; m < msize; m++) //Поиск максимального элемента столбце
                if (abs(a[m][k]) > temp)
                {
                    i = m;
                    temp = abs(a[m][k]);
                }

            if (i != k)  //Перестановка строк если главный элемент столбца в другой строке
            {
                perkol++;   //Увеличение счётчика количества перестановок для знака определителя
                for (j = k; j < msize + 1; j++)
                {
                    bb = a[k][j];
                    a[k][j] = a[i][j];
                    a[i][j] = bb;
                }
            }

            det *= a[k][k] * pow((-1), perkol);  //Вычисление определителя матрицы        
            temp = a[k][k];

            //Преобразование строк (Вычисление масштабирующих множителей)
            for (j = k; j < msize + 1; j++)
            {
                a[k][j] = a[k][j] / temp;
            }
            for (i = k + 1; i < msize; i++)//преобразование строк с помощью k-ой строки
            {
                bb = a[i][k];
                a[i][k] = 0;
                if (bb != 0)
                    for (j = k; j < msize + 1; j++)
                    {
                        a[i][j] = a[i][j] - bb * a[k][j];
                    }
            }          
        }

        if (det == 0)   //Проверка определителя
        {
            cout << "Матрица не вырожденная. Система не имеет решений" << endl;
            exit(1);
        }

        //Обратный ход, нахождение X
        for (i = msize - 1; i >= 0; i--)
        {
            perX[s][i] = 0;
            //tempX[i] = 0;

            temp = a[i][msize];
            //bb = a[i][n];
            for (j = msize + 1; j > i; j--)
            {
                temp = temp - a[i][j] * perX[s][j];
                //bb = bb - a[i][j] * tempX[j];
            }
            perX[s][i] = temp;
            //tempX[i] = bb;

        }
        
        //Подсчёт невязок
        for (int i = 0; i < msize; i++)
        {
            disrep[s][i] = aCopy[i][msize + s];
            for (int j = 0; j < msize; j++)
            {
                disrep[s][i] -= aCopy[i][j] * perX[s][j];
            }
        }

        //Возвращение матрицы для следующего столбца св-ых членов
        for (int i = 0; i < msize; i++)
        {
            for (int j = 0; j < msize + vsize; j++)
            {
                a[i][j] = aCopy[i][j];
            }
        }
        det = 1;
        perkol = 0;
        for (int i = 0; i < msize; i++)
        {
            bb = a[i][msize];
            a[i][msize] = a[i][msize + s + 1];
            a[i][msize + s + 1] = bb;
        }        
    }
}


int main()
{
    fstream clear_file("answers.txt", ios::out);
    clear_file.close();

    setlocale(LC_ALL, "Russian");

    fstream fi; 
    fi.open("matrix.txt", ifstream::in);

    int fail = 0, msize = 0, vsize = 0;
    double obr[n][2*n] = {}, a[n][2*n] = {};

    if (!fi)
    {
        cerr << "ошибка!\n";
        exit(1);
    }
    fi >> msize;

    for (i = 0; i < msize; i++)
        for (j = 0; j < msize; j++)
            fi >> a[i][j];

    fi >> vsize;

    for (i = 0; i < msize; i++)
        for (j = 0; j < vsize; j++)
            fi >> a[i][j + msize];
   
    fi.close();

    cout << "Исходная расширенная матрица: \n";
    for (i = 0; i < msize; i++)
    {
        for (j = 0; j < msize + vsize; j++)
            cout << a[i][j] << " ";
        cout << "\n";
    }

    for (int i = 0; i < msize; i++)
    {
        for (int j = 0; j < msize; j++)
        {
            obr[i][j] = a[i][j];
        }
    }

    for (i = 0; i < msize; i++)
        for (j = 0; j < msize; j++)
            if (i == j)
            obr[i][j + msize] = 1;
    

   CountMart(a, msize, vsize);
  

    cout << "\n" << "Решение системы :" << endl;  //Вывод результатов X
    for (int s = 0; s < vsize; s++)
    {
        cout << "Столбец №" << s + 1 << " :\n";
        for (i = 0; i < msize; i++)
        {
            cout << "x[" << i + 1 << "]=";
            isPrime(perX[s][i]);
            cout << endl;

        }
    }
    cout << "\n" << "Определитель : " << det << endl;
    
    ofstream fo;
    fo.open("answers.txt", ios::app);

    if (fo.is_open())
    {
        fo << "Решение системы:\n";

        for (i = 0; i < msize; i++)
        {
            for (int s = 0; s < vsize; s++)
            {
                fo << perX[s][i] << " ";
            }
            fo << "\n";
        }
    }

    fo.close();

   
   // printf("left-justified: %-8d\n", 100);
    cout << "\nНевязки : " << "\n";

    for (i = 0; i < vsize; i++)
    {
        cout << "\nСтолбец №" << i + 1 << " :\n";
        for (j = 0; j < msize; j++)
        {
            
            cout << disrep[i][j];
            cout << "\n";
        }
        
    }

    CountMart(obr, msize, msize);
    cout << "\n" <<"Обратная матрица : \n";
  
    for (int s = 0; s < msize; s++)
    {    
        for (i = 0; i < msize; i++)
        {           
            cout << perX[s][i] << "  ";

        }
        cout << "\n";
    }


    fo.open("answers.txt", ios::app);

    if (fo.is_open())
    {
        fo << "Обратная матрица : \n"; 
        for (i = 0; i < msize; i++)
        {
            for (int s = 0; s < msize; s++)
            {       
                fo << perX[s][i] << " ";
            }
            fo << "\n";
        }     
    }

    fo.close();

    return 0;
}