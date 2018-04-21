#include <iostream>
#include <iterator>
#include <string>
#include <fstream>
#include <iomanip>
#include <cmath>

using namespace std;

const double eps = 0.00001; // stała przybliżenia zera

bool gauss(int n, double ** AB, double * X)
{

  int ile = n;
  int i,j,k;
  double m,s;
  //szukamy najwiekszego elementu w pierwszej kolumnie
   for(i = 0; i < n ; i++)
    {
      for(j = 0; j < n-1; j++)
      {
        if(AB[j][0]<=AB[j+1][0])
        {
          for(int k = 0; k <= n ; k++)
          {
            swap(AB[j][k], AB[j+1][k]);
          }
        }
      }
    }
    //jesli go nie znalezlismy to sortujemy po ostatniej kolumnie
    	if(AB[0][0]==AB[1][0])
    	{
       		for(i = 0; i < n ; i++)
        	{
          		for(j = 0; j < n-1; j++)
          		{
            		if(AB[j][n]<=AB[j+1][n])
            		{
              			for(int k = 0; k <= n ; k++)
              			{
                			swap(AB[j][k], AB[j+1][k]);
              			}
            		}
          		}
        	}
    	}
// eliminacja współczynników
  for(i = 0; i < n - 1; i++)
    {
      for(j = i + 1; j < n; j++)
      {
        if(fabs(AB[i][i]) < eps)
        {
          cout << "Układ sprzeczny\n";
          return false;
        }
        m = -AB[j][i] / AB[i][i];
        for(k = i + 1; k <= n; k++)
          AB[j][k] += m * AB[i][k];
      }
    }
// sprawdzenie czy uklad nieoznaczony
  if(fabs(AB[n-1][n-1])<eps && fabs(AB[n-1][n])<eps) 
  {
    cout << "Układ nieoznaczony\n";
    return false;
  }
// obliczanie niewiadomych
  for(i = n - 1; i >= 0; i--)
  {
    s = AB[i][n];
    for(j = n - 1; j >= i + 1; j--)
      s -= AB[i][j] * X[j];
    if(fabs(AB[i][i]) < eps)
    {
      cout << "Układ sprzeczny\n";
      return false;
    }
    X[i] = s / AB[i][i];
  }
  return true;
}


int main()
{
  double **AB, *X;
  int      n,i,j;
  
  // odczytujemy liczbę niewiadomych

  cin >> n;

  // tworzymy macierze AB i X

  AB = new double * [n];
  X  = new double [n];

  for(i = 0; i < n; i++) AB[i] = new double[n + 1];

  // odczytujemy dane dla macierzy AB z pliku tekstowego
  ifstream plik;
  plik.open("plik.txt");
  plik.precision(10);

    for(i = 0; i < n; i++)
    {
      for(j = 0; j <= n; j++)
    {
    plik >> AB[i][j];
    }
    }
    
    for(i = 0; i < n ; i++)
    {
      for(j = 0; j <= n; j++)
      {
        cout  << AB[i][j] << '\t' ;
      }
      cout  << endl;
    }
  if(gauss(n,AB,X))
  {
    for(i = 0; i < n; i++)
      cout << "x" << i + 1 << " = " << setw(9) << X[i]
           << endl;
  }
  else
    cout << "Brak wynikow\n";

  // usuwamy macierze z pamięci

  for(i = 0; i < n; i++) delete [] AB[i];
  delete [] AB;
  delete [] X;

  return 0;
} 
