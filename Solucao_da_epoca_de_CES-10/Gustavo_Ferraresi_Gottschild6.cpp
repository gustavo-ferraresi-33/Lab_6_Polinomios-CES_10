/*  Gustavo Ferraresi Gottschild              */
/*  Turma T22-1                               */
/*  Exercicio 6: Polinomios                   */
/*  Programa compilado com Code::Blocks 17.12 */
/*  Data de conclusao: 16/05/2018             */
///Bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
///Inclusao de variaveis booleanas
#define TRUE 1
#define FALSE 0
#define boolean int
///Numero muito pequeno usado para testar se um numero "float" eh igual a zero, pois, para "float", ha erro de arredondamento
#define epsilon 0.000005
int main()
{
    ///Declaracao de variaveis
    FILE * entrada,
         * saida;
    int grau,
        ///Contador, usado para mostrar qual o numero do resultado apresentado em relacao aos demais
        k = 1,
        m,
        grau1,
        grau2;
    float polinomio[2][11] = {0},
          resultado[21] = {0},
          ///O polinomio "resto" tem 11 posicoes por causa do algoritmo da divisao
          resto[11] = {0},
          coeficiente = 0,
          coeflider1,
          coeflider2;
    char operacao,
         sinal1[11] = {0},
         sinal2[11] = {0},
         caractere = 'a';
    ///Variaveis booleanas
    boolean acabou = FALSE,
            resultadonulo = TRUE,
            restonulo = TRUE;
    ///Abertura de arquivos
    entrada = fopen("C:\\Lab6\\entrada6.txt", "r");
    saida = fopen("C:\\Lab6\\Gustavo_Ferraresi_Gottschild6.txt", "w");
    ///Limpeza do buffer do teclado
    fflush (stdin);
    ///Leitura da operacao
    fscanf (entrada, " %c", &operacao);
    ///Ver se o arquivo acabou
    if (operacao == 'F' || operacao == 'f')
        acabou = TRUE;
    ///Se houverem operacoes a serem realizadas
    else
    {
        ///Loop executado uma vez para cada operacao realizada
        while (!acabou)
        {

            fscanf (entrada, " %c", &caractere);
            ///Leitura do primeiro polinomio
            while (caractere != ';')
            {
                fscanf (entrada, "%f", &coeficiente);
                fscanf (entrada, " %c", &caractere);
                fscanf (entrada, " %c", &caractere);
                fscanf (entrada, "%d", &grau);
                polinomio[0][grau] = coeficiente;
                fscanf (entrada, " %c", &caractere);
                if (caractere == '+' || caractere == '-')
                    sinal1[grau] = caractere;
            }
            caractere = 'a';
            fscanf (entrada, " %c", &caractere);
            ///Leitura do segundo polinomio
            while (caractere != ';')
            {
                fscanf (entrada, "%f", &coeficiente);
                fscanf (entrada, " %c", &caractere);
                fscanf (entrada, " %c", &caractere);
                fscanf (entrada, "%d", &grau);
                polinomio[1][grau] = coeficiente;
                fscanf (entrada, " %c", &caractere);
                if (caractere == '+' || caractere == '-')
                    sinal2[grau] = caractere;
            }
            ///Soma dos polinomios
            if (operacao == 'S' || operacao == 's')
            {
                for (int i = 0; i < 11; i++)
                {
                    if (sinal1[i] == '+' && sinal2[i] == '+')
                        resultado[i] = polinomio[0][i] + polinomio[1][i];
                    if (sinal1[i] == '-' && sinal2[i] == '+')
                        resultado[i] = polinomio[1][i] - polinomio[0][i];
                    if (sinal1[i] == '+' && sinal2[i] == '-')
                        resultado[i] = polinomio[0][i] - polinomio[1][i];
                    if (sinal1[i] == '-' && sinal2[i] == '-')
                        resultado[i] = (-1) * (polinomio[0][i] + polinomio[1][i]);
                }
            }
            ///Produto dos polinomios, ck, eh o coeficiente do monomio de grau "k" do produto
            if (operacao == 'P' || operacao == 'p')
            {
                ///Esse loop calcula soh ate "c10"
                for (int i = 0; i < 12; i++)
                {
                    for (int j = 0; j <= i; j++)
                    {
                        if (sinal1[j] == sinal2[i - j])
                            resultado[i] += polinomio[0][j] * polinomio[1][i - j];
                        else resultado[i] -= polinomio[0][j] * polinomio[1][i - j];
                    }
                }
                ///Esse loop calcula de "c11" ate "c20"
                for (int i = 1; i < 11; i++)
                {
                    for (int j = i; j < 11; j++)
                    {
                        if (sinal1[j] == sinal2[10 + i - j])
                            resultado[i + 10] += polinomio[0][j] * polinomio[1][10 + i - j];
                        else resultado[i + 10] -= polinomio[0][j] * polinomio[1][10 + i - j];
                    }
                }
            }
            ///Divisao dso polinomios
            if (operacao == 'D' || operacao == 'd')
            {
                ///Loop para achar o grau do polinomio 1
                m = 11;
                do
                {
                  coeflider1 = polinomio[0][m];
                  grau1 = m;
                  m--;
                }while (fabs(polinomio[0][m]) < epsilon && m >= 0);
                ///Loop para achar o grau do polinomio 2
                m = 11;
                do
                {
                  coeflider2 = polinomio[1][m];
                  grau2 = m;
                  m--;
                }while (fabs(polinomio[1][m]) < epsilon & m >= 0);
                ///Observacao: Os algoritmos acima para leitura de grau dos polinomios consideram que o polinomio identicamente nulo tem grau "0"
                ///Tentando detectar possiveis erros na entrada
                if (grau2 > grau1 || (coeflider1 == coeflider2 && fabs(coeflider1) < epsilon ))
                {
                    printf ("A entrada de numero %d esta errada\n", k);
                }
                ///Se tudo estiver correto, entao:
                else
                {
                    ///Fazer o resto receber o dividendo
                    for (int i = 0; i < 11; i++)
                    {
                        resto[i] = polinomio[0][i];
                    }
                    ///Algoritmo da chave propriamente dito
                    ///Sera suposto que o grau do polinomio 1 eh maior que o grau do polinomio 2
                    while (grau1 >= grau2)
                    {
                        resultado[grau1 - grau2] = coeflider1/coeflider2;
                        for (int i = grau1; i >= 0; i--)
                        {
                            resto[i] -= resultado[grau1 - grau2] * polinomio[1][i];
                        }
                        m = 9;
                        do
                        {
                            coeflider1 = resto[m];
                            grau1 = m;
                            m--;
                        }while (fabs(resto[m]) < epsilon && m >= 0);

                    }///Chave do fim do "while"
                }///Chave que determina o fim da execucao do algoritmo da chave
            }
            ///Agora, imprimir o resultado de cada operacao
            fprintf (saida, "%d: ", k);
            ///Loop para ver se o polinomio resultado eh nulo
            for (int i = 0; i <21 && resultadonulo; i++)
            {
                if (fabs(resultado[i]) > epsilon)
                    resultadonulo = FALSE;
            }
            ///Imprimir o polinomio resultado
            if (!resultadonulo)
            {
                for (int i = 20; i >= 2; i--)
                {

                    if (fabs(resultado[i]) > epsilon)
                    {
                        fprintf (saida, "%gx^%d + ", resultado[i], i);
                    }
                }
                if (fabs(resultado[1]) > epsilon)
                    fprintf (saida, "%gx +", resultado[1]);
                if (fabs(resultado[0]) > epsilon)
                    fprintf (saida, "%g", resultado[0]);
            }
            else fprintf (saida, "0");
            ///Agora, imprimir o resto da divisao (se houve divisao)
            if (operacao == 'D' || operacao == 'd' )
            {
                fprintf (saida, " com resto ");
                ///Loop para verificar se o resto eh nulo
                for (int i = 0; i < 11 && restonulo; i++)
                    if (fabs(resto[i]) > epsilon)
                        restonulo = FALSE;
                ///Agora, imprimir o resto
                if (restonulo)
                    fprintf (saida, "0");
                ///Imprimir o resto se ele nao for nulo
                else
                {
                    for (int i = 10; i >= 2; i--)
                    {
                        if (fabs(resto[i]) > epsilon)
                            fprintf (saida, "%gx^%d + ", resto[i], i);
                    }
                    if (fabs(resto [1]) > epsilon)
                        fprintf (saida, "%gx + ", resto[1]);
                    if (fabs(resto[0]) > epsilon)
                        fprintf (saida, "%g\n", resto[0]);
                }
            }
            ///Pula a linha se a operacao nao for uma divisao
            else fprintf (saida, "\n");
            ///Incremento no contador "k"
            k++;
            ///Anular todos os coeficientes dos polinomios de entrada
            for (int i = 0; i < 2; i++)
            {
                for (int  j = 0; j < 11; j++)
                    polinomio[i][j] = 0;
            }
            ///Anular todos os coeficientes do polinomio resultado
            for (int i = 0; i < 21; i++)
                resultado[i] = 0;
            ///Anular todos os coeficientes do resto
            for (int i = 0; i < 11; i++)
                resto[i] = 0;
            ///Colocar sinais positivos em todas as posicoes dos dois vetores de sinais para os polinomioa de entrada
            for (int i = 0; i < 11; i++)
            {
                sinal1[i] = '+';
                sinal2[i] = '+';
            }
            ///Loop para saber se o arquivo de entrada acabou ou nao
            fscanf (entrada, " %c", &operacao);
            if (operacao == 'F' || operacao == 'f')
                acabou = TRUE;
        }///Fim do loop realizado uma vez para cada operacao com polinomios
    }
    ///Fachamento dos arquivos de entrada e de saida
    fclose (entrada);
    fclose (saida);
    ///Retornar 0
    return 0;
}
