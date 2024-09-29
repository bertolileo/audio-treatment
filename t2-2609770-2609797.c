/*============================================================================*/
/* ICSF13 - 2023-2 - TRABALHO 2                                               */
/*----------------------------------------------------------------------------*/
/* Bogdan T. Nassu                                                            */
/* Leyza E. B. Dorini                                                         */
/* Daniel F. Pigatto                                                          */
/*----------------------------------------------------------------------------*/
/* Guilherme Kaue Johnke Novaes - 2609770                                     */
/* Leonardo Bertoli Sepulvida - 2609797                                       */
/*============================================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "trabalho2.h"

/*============================================================================*/

void mudaGanho (double* dados, int n_amostras, double ganho)
{
    int i;
    /*Um loop pra rodar todas as posições do vetor e multiplicar seus valores
     pelo ganho, mudando assim o volume*/
    for(i=0; i<n_amostras; i++)
    {
        dados[i] = dados[i] * ganho;
    }
}
/*============================================================================*/
int contaSaturacoes (double* dados, int n_amostras)
{
    int i, sat;
    /*Um loop pra rodar as posições do vetor e contar quantas vezes a saturação
    ultrapassa o limite estipulado(1)*/
    for(i=0, sat=0; i<n_amostras; i++)
    {
        if(dados[i]>1 || dados[i]<-1)
            sat++;
    }
    return sat;
}
/*============================================================================*/
int hardClipping (double* dados, int n_amostras, double limite)
{
    int i, amostras_alt;
    /*Um loop para rodar todas as posições do vetor e modificar as amostras que
    ultrapassam o limite, de forma positiva ou negativa para
    o valor do proprio limite*/
    for(i=0,amostras_alt=0; i<n_amostras; i++)
    {
        if(dados[i]>limite)
        {
            dados[i] = limite;
            amostras_alt++;
        }
        else if(dados[i]<-limite)
        {
            dados[i] =-limite;
            amostras_alt++;
        }
    }
    return amostras_alt;
}
/*============================================================================*/
void limitaSinal (double* dados, int n_amostras, int n_passos)
{
    int i, j;
    double ganho, razao, aux;
    //loop para percorrer os dados do audio
    for (i = 0; i < n_amostras; i++) {
        //caso encontre um pico entra dentro do if
        if (dados[i] > 1 || dados[i] < -1) {
            /*calculo do ganho de acordo com o pico encontrado, pois se o pico for negativo,
            todo o calculo tem q ser alterado*/
            ganho = (dados[i] > 1) ? (1 / dados[i]) : (-1 / dados[i]);
            razao = (1 - ganho) / (n_passos + 1);
            for (j = i - n_passos; j < i + n_passos; j++) {
                if (j >= 0 && j <= n_amostras) {
                    aux = ganho + razao * abs (i - j);

                    //if else para limitar a variavel aux e nao extrapolar o limite independente calculo gerado acima
                    if (aux > 1) {
                        aux = 1;
                    } else if (aux < -1) {
                        aux = -1;
                    }
                    dados[j] *= aux;
                }
            }
        }
    }
}
/*============================================================================*/
void geraOndaQuadrada (double* dados, int n_amostras, int taxa, double freq)
{
    int i, meio_per_arnd, valor;
    float meio_periodo;
    double erro;

    meio_periodo = (taxa / freq) / 2.0;
    meio_per_arnd =(int)meio_periodo; //meio periodo arredondado
    valor = -1;
    erro=0;

    for(i=0; i<n_amostras; i++)
    {
        erro+=meio_periodo-meio_per_arnd;
        if(erro>=1)
            meio_per_arnd++;
        if(i % meio_per_arnd == 0)
            valor*=-1;

        dados[i]=valor;
    }
}
