//--------------------------------------------Bibliotecas e Diretivas------------------------------------------------//
#include <stdio.h>
#include "opencv/cv.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "QDebug"
#include <time.h>

#define tipoQuadrado 0
#define tipoCirculo  1
#define MAX 40
#define NIVELMAXIMOCOR 255 // Branco
#define NIVELMINIMOCOR 0 // Preto
#define QTDOBJ 4

using namespace cv;
using namespace std;
//--------------------------------------------------------X----------------------------------------------------------//


int main(int argc, char *argv[])
{
    Mat imagem (600,600,CV_8UC1);
    unsigned int i,j,k,dim,ini,pos,raio;
    unsigned int tipo;
    srand(time(NULL));
    FILE * planilha;
    char nome[30];
    int corte1;

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
        case tipoQuadrado:

            dim=rand()%300;
            corte1=dim/4;
            ini=rand()%200;
            //printf("dim %d \n",dim);
            //printf("ini %d \n",ini);
            rectangle(imagem,Point(ini,ini),Point(ini+dim,ini+dim),Scalar(255),-1,8,0);

            for(int i=0;i<QTDOBJ;i++){
                line(imagem, Point(ini,ini+corte1*i), Point(dim+ini,ini+corte1*i),Scalar(0,255,0),1,8);
            }

            //printf("dim+ini %d \n",dim+ini);
            //imprimindo dados no arquivo .csv
            fprintf(planilha,"%d;",tipoQuadrado);

            fprintf(planilha,"%d;",dim/4);
            fprintf(planilha,"%d;",dim); // Ele considera 1 pixel na largura
            fprintf(planilha,"%d;",dim);
            fprintf(planilha,"%d;",dim);
            fprintf(planilha,"%d;",dim);

            fprintf(planilha,"\n");
            break;

            //gerando um circulo de tamanho aleatorio
        case tipoCirculo:
            //printf("Circulo Gerado\n");
            pos=(imagem.cols/2)+rand()%100;
            raio=rand()%90+10;
            //printf("Posicao Gerada: %d\n", pos);
            circle(imagem,Point(pos,pos),raio,Scalar(255),-1,8,0);

            line(imagem, Point(pos/raio,pos), Point(raio+pos,pos),Scalar(0,255,0),1,8);

            //imprimindo dados no arquivo .csv
            fprintf(planilha,"%d;",tipoCirculo);
            fprintf(planilha,"%d;",raio*2);
            fprintf(planilha,"%d;",raio*2);



            // printf("Raio: %d\n", raio);
            // printf("Diametro: %d\n", raio*2);
            // printf("Ponto: %d\n", ponto);

            int pontoLinhaInferior = pos + (raio/2)*1; // Meio redundante. Eu sei, mas é que eu havia pensado que era para ser 3 pedaços, não 4
            int pontoLinhaSuperior = pos - (raio/2)*1;

            int largura1, largura2;

            // printf("PontoLinhaInferior: %d\n", pontoLinhaInferior);
            // printf("PontoLinhaSuperior: %d\n", pontoLinhaSuperior);
            // printf("==============\n");

            for(int LINHA = 0; LINHA < imagem.rows; LINHA ++) {
                for(int COLUNA = 0; COLUNA < imagem.cols; COLUNA ++){

                    if (LINHA == pontoLinhaInferior && COLUNA == pos) {
                        // printf("Estamos na parte Inferior! Linha : %d  Coluna: %d\n", LINHA, COLUNA);

                        for (int NOVACOLUNA = 0; NOVACOLUNA < imagem.cols; NOVACOLUNA++) {

                            // printf("Nivel de cor em Linha %d Coluna %d eh %d\n", LINHA, NOVACOLUNA, imagem.at<uchar>(LINHA, NOVACOLUNA));

                            if (imagem.at<uchar>(LINHA, NOVACOLUNA) == NIVELMAXIMOCOR &&
                                    imagem.at<uchar>(LINHA, NOVACOLUNA+1) == NIVELMINIMOCOR  &&
                                    imagem.at<uchar>(LINHA, NOVACOLUNA-1) == NIVELMAXIMOCOR) {
                                largura2 = NOVACOLUNA;
                                //   printf("Largura1 %d", largura1);
                            }

                            if (imagem.at<uchar>(LINHA, NOVACOLUNA) == NIVELMAXIMOCOR &&
                                    imagem.at<uchar>(LINHA, NOVACOLUNA- 1) == NIVELMINIMOCOR &&
                                    imagem.at<uchar>(LINHA, NOVACOLUNA + 1) == NIVELMAXIMOCOR) {
                                largura1 = NOVACOLUNA;
                            }


                        }


                        for (int NOVACOLUNA = 0; NOVACOLUNA < imagem.cols; NOVACOLUNA++) {
                            imagem.at<uchar>(LINHA, NOVACOLUNA) = NIVELMINIMOCOR;
                        }
                    }

                    if (LINHA == pontoLinhaSuperior && COLUNA == pos) {

                        for (int NOVACOLUNA = 0; NOVACOLUNA < imagem.cols; NOVACOLUNA++) {
                            imagem.at<uchar>(LINHA, NOVACOLUNA) = NIVELMINIMOCOR;
                        }
                    }
                }
            }

            // printf("Largura1 : %d", largura1);
            // printf("Largura2 : %d", largura2);
            fprintf(planilha,"%d;",largura2 - largura1);
            fprintf(planilha,"%d;",raio*2);
            fprintf(planilha,"%d;",largura2 - largura1);
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
