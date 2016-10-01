//--------------------------------------------Bibliotecas e Diretivas------------------------------------------------//
#include <stdio.h>
#include "opencv/cv.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "QDebug"
#include <time.h>

#define TIPOQUADRADO 0
#define TIPOCIRCULO  1
#define MAX 40
#define INTENSIDADEMAXIMACOR 255 // Branco
#define INTENSIDADEMINIMACOR 0 // Preto
#define QUANTIDADEPEDACOS 4

using namespace cv;
using namespace std;
//--------------------------------------------------------X----------------------------------------------------------//

int BuscarPontoSuperior(Mat imagem, int tipoImagem)
{
    if (tipoImagem == TIPOQUADRADO)
    {
        int pontoSuperior;

        for(int LINHA = 0; LINHA < imagem.rows; LINHA ++)
        {
            for(int COLUNA = 0; COLUNA < imagem.cols; COLUNA ++)
            {
                if (imagem.at<uchar>(LINHA, COLUNA) == INTENSIDADEMAXIMACOR &&
                        imagem.at<uchar>(LINHA, COLUNA+1) == INTENSIDADEMAXIMACOR &&
                        imagem.at<uchar>(LINHA, COLUNA-1) == INTENSIDADEMINIMACOR &&
                        imagem.at<uchar>(LINHA-1, COLUNA) == INTENSIDADEMINIMACOR &&
                        imagem.at<uchar>(LINHA+1, COLUNA) == INTENSIDADEMAXIMACOR)
                {
                    pontoSuperior = LINHA;
                    break;
                }
            }
        }
        return pontoSuperior;
    }
    else if (tipoImagem == TIPOCIRCULO)
    {
        int pontoSuperior;

        for(int LINHA = 0; LINHA < imagem.rows; LINHA ++)
        {
            for(int COLUNA = 0; COLUNA < imagem.cols; COLUNA ++)
            {
                if (imagem.at<uchar>(LINHA, COLUNA) == INTENSIDADEMAXIMACOR &&
                        imagem.at<uchar>(LINHA, COLUNA+1) == INTENSIDADEMINIMACOR &&
                        imagem.at<uchar>(LINHA, COLUNA-1) == INTENSIDADEMINIMACOR &&
                        imagem.at<uchar>(LINHA-1, COLUNA) == INTENSIDADEMINIMACOR &&
                        imagem.at<uchar>(LINHA+1, COLUNA) == INTENSIDADEMAXIMACOR)
                {
                    pontoSuperior = LINHA;
                    break;
                }
            }
        }
        return pontoSuperior;
    }
    else
        return -1;
}

int BuscarPontoInferior(Mat imagem, int tipoImagem)
{
    int pontoInferior;
    if (tipoImagem == TIPOQUADRADO)
    {
        for(int LINHA = 0; LINHA < imagem.rows; LINHA ++)
        {
            for(int COLUNA = 0; COLUNA < imagem.cols; COLUNA++)
            {
                if (imagem.at<uchar>(LINHA, COLUNA) == INTENSIDADEMAXIMACOR &&
                        imagem.at<uchar>(LINHA, COLUNA+1) == INTENSIDADEMAXIMACOR &&
                        imagem.at<uchar>(LINHA, COLUNA-1) == INTENSIDADEMINIMACOR &&
                        imagem.at<uchar>(LINHA-1, COLUNA) == INTENSIDADEMAXIMACOR &&
                        imagem.at<uchar>(LINHA+1, COLUNA) == INTENSIDADEMINIMACOR)
                {
                    pontoInferior = LINHA;
                    break;
                }
            }
        }

        return pontoInferior;
    }
    else if (tipoImagem == TIPOCIRCULO)
    {
        for(int LINHA = 0; LINHA < imagem.rows; LINHA ++)
        {
            for(int COLUNA = 0; COLUNA < imagem.cols; COLUNA ++)
            {
                if (imagem.at<uchar>(LINHA, COLUNA) == INTENSIDADEMAXIMACOR &&
                        imagem.at<uchar>(LINHA, COLUNA+1) == INTENSIDADEMINIMACOR &&
                        imagem.at<uchar>(LINHA, COLUNA-1) == INTENSIDADEMINIMACOR &&
                        imagem.at<uchar>(LINHA-1, COLUNA) == INTENSIDADEMAXIMACOR &&
                        imagem.at<uchar>(LINHA+1, COLUNA) == INTENSIDADEMINIMACOR)
                {
                    pontoInferior = LINHA;
                    break;
                }
            }
        }
        return pontoInferior;
    }
    else
        return -1;
}

void DesenharLinha(Mat imagem, int linha, int intensidadeDeCor)
{
    for(int COLUNA = 0; COLUNA < imagem.cols; COLUNA++)
    {
        imagem.at<uchar>(linha, COLUNA) = intensidadeDeCor;
    }
}

int BuscarLargura(Mat imagem, int linha)
{
    int largura, primeiraColuna, segundaColuna;
    for(int COLUNA = 0; COLUNA < imagem.cols; COLUNA++)
    {
        if (imagem.at<uchar>(linha, COLUNA) == INTENSIDADEMAXIMACOR &&
                imagem.at<uchar>(linha, COLUNA-1) == INTENSIDADEMINIMACOR &&
                imagem.at<uchar>(linha, COLUNA+1) == INTENSIDADEMAXIMACOR)
        {
            primeiraColuna = COLUNA;
        }

        if (imagem.at<uchar>(linha, COLUNA) == INTENSIDADEMAXIMACOR &&
                imagem.at<uchar>(linha, COLUNA-1) == INTENSIDADEMAXIMACOR &&
                imagem.at<uchar>(linha, COLUNA+1) == INTENSIDADEMINIMACOR)
        {
            segundaColuna = COLUNA;
        }
    }
    largura = segundaColuna - primeiraColuna;
    return largura;
}

int main(int argc, char *argv[])
{
    Mat imagem (600,600,CV_8UC1);
    unsigned int i,j,k,dim,ini,pos,raio;
    unsigned int tipo;
    srand(time(NULL));
    FILE * planilha;
    char nome[30];

    int diametro, pontoSuperior, pontoInferior, corte;
    int largura[3];
    planilha=fopen("dados.csv","w");
    fprintf(planilha,"Tipo;altura;largura;larg1;larg2;larg3\n");

    //gerando MAX imagens
    for(k=0;k<MAX;k++)
    {
        //pintando o fundo de preto sempre
        for(i=0;i<imagem.rows;i++)
        {
            for(j=0;j<imagem.cols;j++)
            {
                imagem.at<uchar>(i,j)=0;
            }
        }

        //sorteando quadrado ou circulo
        tipo=rand()%2;

        switch (tipo)
        {

        //gerando um quadrado de tamanho aleatorio
        case TIPOQUADRADO:
            dim=rand()%300;
            ini=rand()%200;
            rectangle(imagem,Point(ini,ini),Point(ini+dim,ini+dim),Scalar(255),-1,8,0);

            pontoSuperior = BuscarPontoSuperior(imagem, TIPOQUADRADO);
            pontoInferior = BuscarPontoInferior(imagem, TIPOQUADRADO);
            diametro = pontoInferior - pontoSuperior;

            corte=diametro/QUANTIDADEPEDACOS;

            // Começa por 1 já que o pedaço 0 é o ponto inicial
            for(int PEDACO=1;PEDACO<QUANTIDADEPEDACOS;PEDACO++)
            {
                largura[PEDACO - 1] = BuscarLargura(imagem, pontoSuperior + (corte * PEDACO));
                DesenharLinha(imagem, pontoSuperior + (corte * PEDACO), INTENSIDADEMINIMACOR);
            }

            //imprimindo dados no arquivo .csv
            fprintf(planilha,"%d;",TIPOQUADRADO);
            fprintf(planilha,"%d;",dim);
            fprintf(planilha,"%d;",dim);
            fprintf(planilha,"%d;",largura[0]);
            fprintf(planilha,"%d;",largura[1]);
            fprintf(planilha,"%d;",largura[2]);
            fprintf(planilha,"\n");
            break;


            //gerando um circulo de tamanho aleatorio
        case TIPOCIRCULO:
            pos=(imagem.cols/2)+rand()%100;
            raio=rand()%90+10;
            circle(imagem,Point(pos,pos),raio,Scalar(255),-1,8,0);

            pontoSuperior = BuscarPontoSuperior(imagem, TIPOCIRCULO);
            pontoInferior = BuscarPontoInferior(imagem, TIPOCIRCULO);
            diametro = pontoInferior - pontoSuperior;

            corte=diametro/QUANTIDADEPEDACOS;
            // Começa por 1 já que o pedaço 0 é o ponto inicial
            for(int PEDACO=1;PEDACO<QUANTIDADEPEDACOS;PEDACO++)
            {
                largura[PEDACO - 1] = BuscarLargura(imagem, pontoSuperior + (corte * PEDACO));
                DesenharLinha(imagem, pontoSuperior + (corte * PEDACO), INTENSIDADEMINIMACOR);
            }

            //imprimindo dados no arquivo .csv
            fprintf(planilha,"%d;",TIPOCIRCULO);
            fprintf(planilha,"%d;",raio*2);
            fprintf(planilha,"%d;",raio*2);
            fprintf(planilha,"%d;",largura[0]);
            fprintf(planilha,"%d;",largura[1]);
            fprintf(planilha,"%d;",largura[2]);
            fprintf(planilha,"\n");
            break;
        }

        //gerando nomes para as imagens dinamicamente
        //imagem0.jpg, imagem1.jpg ...
        sprintf(nome,"imagem%d.jpg",k);

        //  namedWindow("teste",WINDOW_NORMAL);
        // resizeWindow("teste",200,200);

        imwrite(nome,imagem);

        //   imshow("teste",imagem);
        waitKey(0);
    }

    fclose(planilha);
    return 0;
}

