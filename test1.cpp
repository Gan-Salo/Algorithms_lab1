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

//double a[n][n + 2] = { {5, 7,  6,  5, 23.01, 1},   //матрица коэффициентов, где последний столбец - правая часть системы
//{7, 10,  8,  7, 31.99, 0},
//{6, 8,  10,   9, 32.99, 0},
//{5, 7,  9,   10, 31.01, 0} };

double aCopy[n][2 * n] = {};
double b[n][n] = {};
double c[n][n] = {};
double tempX[n], perX[n][n];
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
//void ReversedMatr()
//{
//    /*В одну матрицу копируем значения из исходной, другую делаем единичной*/
//    for (int i = 0; i < n; i++)
//    {
//        for (int j = 0; j < n; j++)
//        {
//            b[i][j] = a[i][j];
//            if (i == j)
//                c[i][j] = 1;
//            else
//                c[i][j] = 0;
//        }
//    }
//
//    
//    /*Приводим исходную матрицу к единичной форме, чтобы вторая матрица оказалась обратной исходной*/
//    for (int k = 0; k < n; k++)
//    {
//        temp = b[k][k];     //Разрешающий элемент на главной диагонали
//        
//        for (int j = 0; j < n; j++)   //Преобразуем элементы главной диагонали в единицу с помощью деления
//        {
//            b[k][j] = b[k][j] / temp;
//            c[k][j] = c[k][j] / temp;
//        }
//
//        for (int i = k + 1; i < n; i++)     //Обнуляем элементы столбца под эл-ом гл. диагонали, отнимая от нижестоящих строк домноженные элементы строки с текущим эл-ом на гл. диагонали
//        {
//            temp = b[i][k];
//
//            for (int j = 0; j < n; j++)
//            {
//                b[i][j] -= b[k][j] * temp;
//                c[i][j] -= c[k][j] * temp;
//            }
//        }
//    }
//
//    for (int k = n - 1; k > 0; k--)     //Обнуляем элементы выше главной диагонали, проводя аналогичные вычисления, взяв в качестве разрешающего элемента единицу последней строки
//    {
//        for (int i = k - 1; i >= 0; i--)
//        {
//            temp = b[i][k];
//
//            for (int j = 0; j < n; j++)
//            {
//                b[i][j] -= b[k][j] * temp;
//                c[i][j] -= c[k][j] * temp;
//            }
//        }
//    }
//
//}


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
        /*for (i = 0; i < msize; i++)
        {
            for (j = 0; j < msize + vsize; j++)
            {
                cout << a[i][j] << " ";
            }
            cout << "\n";
        }*/

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

        cout << "Преобразованная матрица: " << endl;
        for (i = 0; i < msize; i++)
        {
            for (j = 0; j < msize; j++)
            {

                cout << a[i][j] << " ";
            }
            cout << "\n";
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

    //for (i = n - 1; i >= 0; i--)
    //{
    //    tempX[i] = 0;

    //    bb = a[i][n];
    //    for (j = n + 2; j > i; j--)
    //    {

    //        bb = bb - a[i][j] * tempX[j];
    //    }
    //    tempX[i] = bb;

    //}

}

int main()
{
    fstream clear_file("answers.txt", ios::out);
    clear_file.close();

    setlocale(LC_ALL, "Russian");

   // ReversedMatr();
    
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

 /*   for (i = 0; i < msize; i++)
    { 
        for (j = 0; j < msize + vsize; j++)
            cout << a[i][j] << " ";
        cout << "\n";
    }*/
    fi.close();

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
    
    cout << "Обр исход" << "\n";
    for (i = 0; i < msize; i++)
    {
        for (j = 0; j < msize * 2; j++)
            cout << obr[i][j] << " ";
        cout << "\n";
    }

   CountMart(a, msize, vsize);


    cout << "\n" << "Результаты :" << endl;  //Вывод результатов X
    for (int s = 0; s < vsize; s++)
        for (i = 0; i < msize; i++)
        {
        cout << "x[" << i + 1 << "]=";// << x[i];
        //tempX[i] = x[i];
        //perX[i] = x[i];
        isPrime(perX[s][i]); 

        cout << endl; 

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



    CountMart(obr, msize, msize);
    cout << "\n" <<"Обратная матрица : \n";

    cout << "\n" << "Результаты :" << endl;  //Вывод результатов X
    for (int s = 0; s < msize; s++)
        for (i = 0; i < msize; i++)
        {
            cout << "x[" << i + 1 << "]=";
            isPrime(perX[s][i]);
            cout << endl;

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


    //for (i = 0; i < msize; i++)
    //{
    //    for (j = 0; j < msize; j++)
    //    {           
    //        cout << c[i][j] << " ";
    //    }
    //    cout << "\n";
    //}
    /*Disrep();
    for (i = 0; i < n; i++)
    {       
        cout << disrep[i] << " ";       
        cout << "\n";
    }*/
    return 0;
}