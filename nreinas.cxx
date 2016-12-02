#include <iostream>
#include <stdlib.h>
#include <vector>
#include <limits>

using namespace std;

const int INF = numeric_limits<int>::max();

int N = 8;
int *damas;

int *contadorColumna;
int *contadorDiagonalSuperior;
int *contadorDiagonalInferior;

int Conflictos(int);
int Conflictos();
void Inicializar();
void Imprimir();
void ConflictosMinimos();
int ConflictosMaximos();
void ConflictosMinimos();

int main(int argc, char **argv)
{
    if (argc > 2)
        {
            cerr << "Uso:" << endl;
            cerr << "\t" << argv[0] << endl;
            cerr << "\t" << argv[0] << " [Numero de Damas]" << endl;
            exit(1);

        }
    else if (argc == 2)
        {
            N = atoi(argv[1]);
        }

    if (N < 4)
        {
            cerr << "No existen soluciones para N<4" << endl;
            exit(2);
        }

    srand(time(0));
    int nMaximoMostrar = 40;

    Inicializar();

    if (N <= nMaximoMostrar)
        {
            Imprimir();
        }

    int conflictosPrevios = Conflictos();
    int conflictosNuevos;

    cout << "Conflictos iniciales: " << conflictosPrevios << endl << endl;

    int contador = 0;
    int iteraciones = 0;

    while (conflictosPrevios != 0)
        {
            ConflictosMinimos();
            iteraciones++;
            conflictosNuevos = Conflictos();

            if (conflictosPrevios == conflictosNuevos)
                {
                    contador++;

                    if (contador > 1)
                        {
                            damas[rand() % N] = rand() % N;
                            contador = 0;
                        }
                }

            conflictosPrevios = conflictosNuevos;
        }

    if (N <= nMaximoMostrar)
        {
            Imprimir();
        }

    cout << "Cantidad de iteraciones: " << iteraciones << endl;

    return 0;
}


int Conflictos(int filaExcluida)
{
    int conflictos = 0;

    for (int i = 0; i < 2 * N - 1; i++)
        {
            if (i < N)
                {
                    contadorColumna[i] = 0;
                }

            contadorDiagonalSuperior[i] = contadorDiagonalInferior[i] = 0;
        }

    for (int i = 0; i < N; i++)
        {
            if (i != filaExcluida)
                {
                    contadorColumna[damas[i]] += 1;
                    contadorDiagonalSuperior[damas[i] + i] += 1;
                    contadorDiagonalInferior[(N - damas[i]) + i - 1] += 1;
                }
        }

    for (int i = 0; i < 2 * N - 1; i++)
        {
            if (i < N)
                {
                    conflictos += ((contadorColumna[i] - 1) * contadorColumna[i]) / 2;
                }

            conflictos += ((contadorDiagonalSuperior[i] - 1) * contadorDiagonalSuperior[i])
                          / 2;
            conflictos += ((contadorDiagonalInferior[i] - 1) * contadorDiagonalInferior[i])
                          / 2;
        }

    return conflictos;
}

int Conflictos()
{
    return Conflictos(-1);
}

void Inicializar()
{
    damas = new int[N];

    contadorColumna = new int[N];
    contadorDiagonalSuperior = new int[(2 * N) - 1];
    contadorDiagonalInferior = new int[(2 * N) - 1];

    for (int i = 0; i < 2 * N - 1; i++)
        {
            if (i < N)
                {
                    contadorColumna[i] = 0;
                }

            contadorDiagonalSuperior[i] = contadorDiagonalInferior[i] = 0;
        }

    vector<int> conflictoMinimoColumnas;
    int conflictoMinimo = INF;
    int conflictosAux;

    // choose first queen randomly
    damas[0] = rand() % N;

    contadorColumna[damas[0]] += 1;
    contadorDiagonalSuperior[damas[0] + 0] += 1;
    contadorDiagonalInferior[(N - damas[0]) + 0 - 1] += 1;

    // i=row index
    for (int i = 1; i < N; i++)
        {
            conflictoMinimoColumnas.clear();
            conflictoMinimo = INF;

            // j=col index
            for (int j = 0; j < N; j++)
                {
                    conflictosAux = ((contadorColumna[j] + 1) * contadorColumna[j]) / 2;
                    conflictosAux += ((contadorDiagonalSuperior[j + i] + 1) *
                                      contadorDiagonalSuperior[j + i]) / 2;
                    conflictosAux += ((contadorDiagonalInferior[(N - j) + i - 1] + 1) *
                                      contadorDiagonalInferior[(N - j) + i - 1]) / 2;

                    if (conflictosAux < conflictoMinimo)
                        {
                            conflictoMinimo = conflictosAux;
                            conflictoMinimoColumnas.clear();
                            conflictoMinimoColumnas.push_back(j);

                        }
                    else if (conflictosAux == conflictoMinimo)
                        {
                            conflictoMinimoColumnas.push_back(j);
                        }
                }

            damas[i] = conflictoMinimoColumnas[rand() % conflictoMinimoColumnas.size()];

            contadorColumna[damas[i]] += 1;
            contadorDiagonalSuperior[damas[i] + i] += 1;
            contadorDiagonalInferior[(N - damas[i]) + i - 1] += 1;
        }
}

void Imprimir()
{
    for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < damas[i]; j++)
                {
                    cout << "| ";
                }

            cout << "|Q";

            for (int j = 0; j < N - damas[i] - 1; j++)
                {
                    cout << "| ";
                }

            cout << "|" << endl;
        }

    cout << "Conflictos: " << Conflictos() << endl;
}

// Calcula la fila con mayor cantidad de conflictos
int ConflictosMaximos()
{
    int conflictosFila = 0;
    int conflictosAux;
    vector<int> conflictoMaximoFilas;

    for (int i = 0; i < N; i++)
        {
            conflictosAux = ((contadorColumna[damas[i]] - 1) * contadorColumna[damas[i]]) /
                            2;
            conflictosAux += ((contadorDiagonalSuperior[damas[i] + i] - 1) *
                              contadorDiagonalSuperior[damas[i] + i]) / 2;
            conflictosAux += ((contadorDiagonalInferior[(N - damas[i]) + i - 1] - 1) *
                              contadorDiagonalInferior[(N - damas[i]) + i - 1]) / 2;

            if (conflictosAux > conflictosFila)
                {
                    conflictosFila = conflictosAux;
                    conflictoMaximoFilas.clear();
                    conflictoMaximoFilas.push_back(i);

                }
            else if (conflictosAux == conflictosFila)
                {
                    conflictoMaximoFilas.push_back(i);
                }
        }

    return conflictoMaximoFilas[rand() % conflictoMaximoFilas.size()];
}

// Calcula la fila con menor cantidad de conflictos
void ConflictosMinimos()
{
    int conflictoMaximoFila = ConflictosMaximos();

    int conflictoMinimo = INF;
    int conflictosAux;
    vector<int> conflictoMinimoColumnas;

    //Imprimir();
    Conflictos(conflictoMaximoFila);

    for (int i = 0; i < N; i++)
        {
            conflictosAux = ((contadorColumna[i] + 1) * contadorColumna[i]) / 2;
            conflictosAux += ((contadorDiagonalSuperior[i + conflictoMaximoFila] + 1) *
                              contadorDiagonalSuperior[i + conflictoMaximoFila]) / 2;
            conflictosAux += ((contadorDiagonalInferior[(N - i) + conflictoMaximoFila - 1] +
                               1) * contadorDiagonalInferior[(N - i) + conflictoMaximoFila - 1]) / 2;

            if (conflictosAux < conflictoMinimo)
                {
                    conflictoMinimo = conflictosAux;
                    conflictoMinimoColumnas.clear();
                    conflictoMinimoColumnas.push_back(i);

                }
            else if (conflictosAux == conflictoMinimo)
                {
                    conflictoMinimoColumnas.push_back(i);
                }
        }

    damas[conflictoMaximoFila] = conflictoMinimoColumnas[rand() %
                                 conflictoMinimoColumnas.size()];
}
