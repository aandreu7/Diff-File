#include <iostream>
#include <string>
#include <vector>
using namespace std;

int Diff(const std::string in1, const std::string in2, std::string& out) 
{
    int m = in1.size();
    int n = in2.size();

    int** matriuCostos;

    // INITIALIZES COSTS MATRIX
    matriuCostos = new int* [m + 1];

    for (int i = 0; i < m + 1; i++)
        matriuCostos[i] = new int[n + 1];

    // BUILDS COSTS MATRIX
    for (int i = 0; i <= m; i++)
        matriuCostos[i][0] = i;
    for (int j = 0; j <= n; j++)
        matriuCostos[0][j] = j;

    for (int x = 1; x <= m; x++)
    {
        for (int y = 1; y <= n; y++)
        {
            int xm1 = x - 1;
            int ym1 = y - 1;

            if (in1[xm1] == in2[ym1])
                matriuCostos[x][y] = matriuCostos[xm1][ym1];
            else
            {
                int cost1 = matriuCostos[xm1][y] + 1;
                int cost2 = matriuCostos[x][ym1] + 1;
                int cost3 = matriuCostos[xm1][ym1] + 1;

                int minCost = cost1;

                if (cost2 < minCost)
                    minCost = cost2;

                if (cost3 < minCost)
                    minCost = cost3;

                matriuCostos[x][y] = minCost;
            }
        }
    }

	// BACKTRACKS TO GET THE DIFFERENCE

    int x = m, y = n;
    out = in1;
    std::string modificador;
    std::string operacioActual="";
    int numCaractsMod = 0;

    while (x != 0 && y != 0)
    {
        if (in1[x-1]==in2[y-1])
        {
            if (operacioActual != "") // S'ACABA UNA AGRUPACIÓ ANTERIOR
            {
                if (operacioActual == "#" || operacioActual == "-")
                    out.erase(x, numCaractsMod);
                out.insert(x, modificador);
                operacioActual = "";
                
            }

            // AVANCEM EN DIAGONAL
            if (x > 0)
                x = x - 1;
            if (y > 0)
                y = y - 1;
        }

        else
        {
            // !!!!!!! FINDS MINIMUM COST OPERATION !!!!!!
            int costSubst = matriuCostos[x - 1][y - 1];
            int costElim = matriuCostos[x - 1][y];
            int costInsert = matriuCostos[x][y - 1];

            int minCost = std::min({ costSubst, costElim, costInsert });

            if (minCost == costSubst) // CAS INTERCANVIAR
            {
                if (operacioActual == "#")
                {
                    modificador.insert(2, 1, in1[x - 1]);
                    modificador.insert(modificador.size() - 1 - numCaractsMod, 1, in2[y - 1]);
                    numCaractsMod++;
                }
                else
                {
                    if (operacioActual != "") // S'ACABA UNA AGRUPACIÓ ANTERIOR
                    {
                        if (operacioActual == "#" || operacioActual == "-")
                            out.erase(x, numCaractsMod);
                        out.insert(x, modificador);
                        operacioActual = "";

                    }

                    operacioActual = "#";
                    modificador = "$" + operacioActual + in1[x - 1] + "$" + in2[y - 1] + "$";
                    numCaractsMod = 1;
                }

                // AVANCEM EN DIAGONAL
                if (x > 0)
                    x = x - 1;
                if (y > 0)
                    y = y - 1;
            }

            else if (minCost == costElim) // CAS ELIMINAR
            {
                if (operacioActual == "-")
                {
                    modificador.insert(2, 1, in1[x - 1]);
                    numCaractsMod++;
                }

                else
                {
                    if (operacioActual != "") // S'ACABA UNA AGRUPACIÓ ANTERIOR
                    {
                        if (operacioActual == "#" || operacioActual == "-")
                            out.erase(x, numCaractsMod);
                        out.insert(x, modificador);
                        operacioActual = "";

                    }
                    operacioActual = "-";
                    modificador = "$" + operacioActual + in1[x - 1] + "$";
                    numCaractsMod = 1;
                }
                // AVANCEM UNA FILA CAP AMUNT
                if (x > 0)
                    x = x - 1;
            }

            else // CAS INSERIR
            {
                if (operacioActual == "+")
                {
                    modificador.insert(2, 1, in2[y - 1]);
                    numCaractsMod++;
                }
                else
                {
                    if (operacioActual != "") // S'ACABA UNA AGRUPACIÓ ANTERIOR
                    {
                        if (operacioActual == "#" || operacioActual == "-")
                            out.erase(x, numCaractsMod);
                        out.insert(x, modificador);
                        operacioActual = "";

                    }
                    operacioActual = "+";
                    modificador = "$" + operacioActual + in2[y - 1] + "$";
                    numCaractsMod = 1;
                }
                // AVANCEM UNA COLUMNA CAP A L'ESQUERRA
                if (y > 0)
                    y = y - 1;
            }
        } 
    }

    if (x == 0 && y > 0) // CAS INSERIR AL PRINCIPI
    {
        string op = "+";
        modificador = "$" + op + in2.substr(0, y) + "$";
        out.insert(0, modificador);
    }

    if (x > 0 && y == 0) // CAS ELIMINAR AL PRINCIPI
    {
        string op = "-";
        modificador = "$" + op + in1.substr(0, x) + "$";
        out.erase(0, x);
        out.insert(0, modificador);
    }

	int retValue = matriuCostos[m][n];

    for (int i = 0; i < m + 1; i++)
    {
        if (matriuCostos[i] != nullptr)
        {
            delete[] matriuCostos[i];
			matriuCostos[i] = nullptr;
        }			
    }

    return retValue;
}

int main()
{
    std::string out = "";

    std::string in1 =
        "#include <stdio.h>\n"
        "int main() {\n"
        "   printf(\"Hello World!\");\n"
        "   return 0;\n"
        "};

    std::string in2 = 
        "#include <windows.h>\n"
        "#include <stdio.h>\n"
        "int main() {\n"
        "   printf(\"Hello World!\");\n"
        "   return 0;\n"
        "}";

    Diff(in1, in2, out);

    //std::cout << Diff(in1, in2, out) << std::endl;
    //std::cout << out << endl;
    return 0;
}