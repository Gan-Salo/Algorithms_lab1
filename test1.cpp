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
const int n = 4;
int i, j, m, k, perkol = 0;
double aa, bb, temp,  det = 1;

double a[n][n + 1] = { {5, 7,  6,  5, 23.1},   //матрица коэффициентов, где последний столбец - правая часть системы
{7, 10,  8,  7, 31.9},
{6, 8,  10,   9, 32.9},
{5, 7,  9,   10, 31.1} };

double b[n][n] = {};
double c[n][n] = {};
double tempX[n], perX[n];
double disrep[n] = {};

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

/*Вычисление обратной матрицы*/
void ReversedMatr()
{
    /*В одну матрицу копируем значения из исходной, другую делаем единичной*/
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            b[i][j] = a[i][j];
            if (i == j)
                c[i][j] = 1;
            else
                c[i][j] = 0;
        }
    }

    /*Приводим исходную матрицу к единичной форме, чтобы вторая матрица оказалась обратной исходной*/
    for (int k = 0; k < n; k++)
    {
        temp = b[k][k];     //Разрешающий элемент на главной диагонали
        
        for (int j = 0; j < n; j++)   //Преобразуем элементы главной диагонали в единицу с помощью деления
        {
            b[k][j] = b[k][j] / temp;
            c[k][j] = c[k][j] / temp;
        }

        for (int i = k + 1; i < n; i++)     //Обнуляем элементы столбца под эл-ом гл. диагонали, отнимая от нижестоящих строк домноженные элементы строки с текущим эл-ом на гл. диагонали
        {
            temp = b[i][k];

            for (int j = 0; j < n; j++)
            {
                b[i][j] -= b[k][j] * temp;
                c[i][j] -= c[k][j] * temp;
            }
        }
    }

    for (int k = n - 1; k > 0; k--)     //Обнуляем элементы выше главной диагонали, проводя аналогичные вычисления, взяв в качестве разрешающего элемента единицу последней строки
    {
        for (int i = k - 1; i >= 0; i--)
        {
            temp = b[i][k];

            for (int j = 0; j < n; j++)
            {
                b[i][j] -= b[k][j] * temp;
                c[i][j] -= c[k][j] * temp;
            }
        }
    }

}


void Disrep()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            b[i][j] = a[i][j];            
        }       
    }
    cout << "\n";
    //for (int i = 0; i < n; i++)
    //{       
    //    tempX[i] = a[i][n];      
    //}

    for (int i = 0; i < n; i++)
    {
        cout << tempX[i] << " ";
        cout << "\n";
    }
    for (int i = 0; i < n; i++)
    {
        disrep[i] = tempX[i];
        for (int j = 0; j < n; j++)
        {
            disrep[i] -= b[i][j] * perX[j];
        }
    }
}

int main()
{

    setlocale(LC_ALL, "Russian");

    double* x;
    x = (double*)malloc(n * sizeof(double));
    
    ReversedMatr();
    //fstream fi;
    //fi.open("matrix.txt", ifstream::in);

    //int fail = 0;
    //double tab[3][3] = {};

    //if (!fi)
    //{
    //    cerr << "ошибка!\n";
    //    exit(1);
    //}
    //
    //for (i = 0; i < 3; i++)
    //    for (j = 0; j < 3; j++)
    //        fi >> tab[i][j];

    //for (i = 0; i < 3; i++)
    //{ 
    //    for (j = 0; j < 3; j++)
    //        cout << tab[i][j] * 2 << " ";
    //    cout << "\n";
    //}
    //fi.close();

    for (k = 0; k < n; k++) 
    {
        temp = abs(a[k][k]);
        i = k;
        for (m = k + 1; m < n; m++) //Поиск максимального элемента столбце
            if (abs(a[m][k]) > temp)
            {
                i = m;
                temp = abs(a[m][k]);
            }

        if (i != k)  //Перестановка строк если главный элемент столбца в другой строке
        {
            perkol++;   //Увеличение счётчика количества перестановок для знака определителя
            for (j = k; j < n + 1; j++)
            {
                bb = a[k][j];
                a[k][j] = a[i][j];
                a[i][j] = bb;            
            }
        }       
        
        det *= a[k][k] * pow((-1),perkol);  //Вычисление определителя матрицы        
        temp = a[k][k];  

        //Преобразование строк (Вычисление масштабирующих множителей)
        for (j = k; j < n + 1; j++)
        {
            a[k][j] = a[k][j] / temp;
        }
        for (i = k + 1; i < n; i++)//преобразование строк с помощью k-ой строки
        {
            bb = a[i][k];
            a[i][k] = 0;
            if (bb != 0)
                for (j = k + 1; j < n + 1; j++)
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

    cout << "Преобразованная матрица: " << endl;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {

            cout << a[i][j] << " ";
        }
        cout << "\n";
    }
    //Обратный ход, нахождение X
    for (i = n - 1; i >= 0; i--)   
    {
        x[i] = 0;
        temp = a[i][n];
        for (j = n; j > i; j--)
            temp = temp - a[i][j] * x[j];
        x[i] = temp;
    }
       
    cout << "\n" << "Результаты :" << endl;  //Вывод результатов X
    for (i = 0; i < n; i++)
    {
        cout << "x[" << i + 1 << "]=";// << x[i];
        tempX[i] = x[i];
        perX[i] = x[i];
        isPrime(x[i]); 
        cout << endl; 

    }
    cout << "\n" << "Determinant : " << det << endl;
    cout << "\n" <<"Обратная матрица:\n";
    
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {           
            cout << c[i][j] << " ";
        }
        cout << "\n";
    }
    Disrep();
    for (i = 0; i < n; i++)
    {       
        cout << disrep[i] << " ";       
        cout << "\n";
    }
    return 0;
}