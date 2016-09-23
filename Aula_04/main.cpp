//--------------------------------------------Bibliotecas e Diretivas------------------------------------------------//
#include <stdio.h>
#include "opencv/cv.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "QDebug"
#include <time.h>
#define TipoQuadrado 0
#define AZUL 0
#define VERDE 1
#define VERMELHO 2

using namespace cv;
using namespace std;
//--------------------------------------------------------X----------------------------------------------------------//

int main(int argc, char *argv[])
{
    //Abrindo a imagem do quadrado colorido.
    int LINHA,COLUNA, resX, resY, numPixels, contBranco = 0;

    FILE *arquivo;
    arquivo = fopen("dados.CSV", "w");


    Mat quadradoRGB = imread("quadrado.png",1);
    // Deep copy
    Mat quadradoBin = quadradoRGB.clone();

    imshow("Quadrado RGB :D", quadradoRGB);

    resX = quadradoRGB.rows;
    resY = quadradoRGB.cols;

    printf("Resolução Horizontal: %d\n", resX);
    printf("Resolução Vertical: %d\n", resY);

    numPixels = resX * resY;
    fprintf_s(arquivo, "%d;", resX);
    fprintf_s(arquivo, "%d;", resY);
    fprintf_s(arquivo, "%d;", numPixels);

    // fclose(arquivo);

    for(LINHA=0;LINHA < quadradoRGB.rows;LINHA++)
    {
        for(COLUNA = 0; COLUNA < quadradoRGB.cols;COLUNA++)
        {
            // quadradoRGB.at<Vec3b>(i,j)[0] B
            // quadradoRGB.at<Vec3b>(i,j)[1] G
            // quadradoRGB.at<Vec3b>(i,j)[2] R
            if (quadradoBin.at<Vec3b>(LINHA,COLUNA)[0] > 120
                    && quadradoBin.at<Vec3b>(LINHA,COLUNA)[2] < 20)
            {
                contBranco++;
                quadradoBin.at<Vec3b>(LINHA,COLUNA)[0] = 255;
                quadradoBin.at<Vec3b>(LINHA,COLUNA)[1] = 255;
                quadradoBin.at<Vec3b>(LINHA,COLUNA)[2] = 255;
            }
            else
            {
                contBranco++;
                quadradoBin.at<Vec3b>(LINHA,COLUNA)[0] = 0;
                quadradoBin.at<Vec3b>(LINHA,COLUNA)[1] = 0;
                quadradoBin.at<Vec3b>(LINHA,COLUNA)[2] = 0;
            }
        }
    }

    int supEsqX, supEsqY, infDirX, infDirY, InfEsqX, InfEsqY, SupDirX,SupDirY;
    for(LINHA = 0; LINHA < quadradoBin.rows; LINHA++)
    {
        for(COLUNA = 0; COLUNA < quadradoBin.cols; COLUNA++)
        {
            if ((quadradoBin.at<Vec3b>(LINHA,COLUNA)[AZUL] == 255
                 && quadradoBin.at<Vec3b>(LINHA,COLUNA)[VERDE] == 255
                 && quadradoBin.at<Vec3b>(LINHA,COLUNA)[VERMELHO] == 255) &&
                    (quadradoBin.at<Vec3b>(LINHA,COLUNA-1)[AZUL] == 0
                     && quadradoBin.at<Vec3b>(LINHA,COLUNA-1)[VERDE] == 0
                     && quadradoBin.at<Vec3b>(LINHA, COLUNA-1)[VERMELHO] == 0) &&
                    (quadradoBin.at<Vec3b>(LINHA-1, COLUNA)[AZUL] == 0
                     && quadradoBin.at<Vec3b>(LINHA-1, COLUNA)[VERDE] == 0
                     && quadradoBin.at<Vec3b>(LINHA-1, COLUNA)[VERMELHO] == 0))
            {
                supEsqX = LINHA;
                supEsqY = COLUNA;
                circle(quadradoBin, Point(COLUNA,LINHA),3, Scalar(0,0,255), -1, 8,0 );
            }

            if ((quadradoBin.at<Vec3b>(LINHA,COLUNA)[AZUL] == 255
                 && quadradoBin.at<Vec3b>(LINHA,COLUNA)[VERDE] == 255
                 && quadradoBin.at<Vec3b>(LINHA,COLUNA)[VERMELHO] == 255) &&
                    (quadradoBin.at<Vec3b>(LINHA,COLUNA+1)[AZUL] == 0
                     && quadradoBin.at<Vec3b>(LINHA,COLUNA+1)[VERDE] == 0
                     && quadradoBin.at<Vec3b>(LINHA, COLUNA+1)[VERMELHO] == 0) &&
                    (quadradoBin.at<Vec3b>(LINHA+1, COLUNA)[AZUL] == 0
                     && quadradoBin.at<Vec3b>(LINHA+1, COLUNA)[VERDE] == 0
                     && quadradoBin.at<Vec3b>(LINHA+1, COLUNA)[VERMELHO] == 0))
            {
                {
                    infDirX = LINHA;
                    infDirY = COLUNA;
                    circle(quadradoBin, Point(COLUNA,LINHA),3, Scalar(0,0,255), -1, 8,0 );
                }
            }
            if ((quadradoBin.at<Vec3b>(LINHA,COLUNA)[AZUL] == 255
                 && quadradoBin.at<Vec3b>(LINHA,COLUNA)[VERDE] == 255
                 && quadradoBin.at<Vec3b>(LINHA,COLUNA)[VERMELHO] == 255) &&
                    (quadradoBin.at<Vec3b>(LINHA+1,COLUNA)[AZUL] == 0
                     && quadradoBin.at<Vec3b>(LINHA+1,COLUNA)[VERDE] == 0
                     && quadradoBin.at<Vec3b>(LINHA+1, COLUNA)[VERMELHO] == 0) &&
                    (quadradoBin.at<Vec3b>(LINHA, COLUNA-1)[AZUL] == 0
                     && quadradoBin.at<Vec3b>(LINHA, COLUNA-1)[VERDE] == 0
                     && quadradoBin.at<Vec3b>(LINHA, COLUNA-1)[VERMELHO] == 0))
            {
                InfEsqX = LINHA;
                InfEsqY = COLUNA;
                circle(quadradoBin, Point(COLUNA,LINHA),3, Scalar(0,0,255), -1, 8,0 );
            }

            if ((quadradoBin.at<Vec3b>(LINHA,COLUNA)[AZUL] == 255
                 && quadradoBin.at<Vec3b>(LINHA,COLUNA)[VERDE] == 255
                 && quadradoBin.at<Vec3b>(LINHA,COLUNA)[VERMELHO] == 255) &&
                    (quadradoBin.at<Vec3b>(LINHA-1,COLUNA)[AZUL] == 0
                     && quadradoBin.at<Vec3b>(LINHA-1,COLUNA)[VERDE] == 0
                     && quadradoBin.at<Vec3b>(LINHA-1, COLUNA)[VERMELHO] == 0) &&
                    (quadradoBin.at<Vec3b>(LINHA, COLUNA+1)[AZUL] == 0
                     && quadradoBin.at<Vec3b>(LINHA, COLUNA+1)[VERDE] == 0
                     && quadradoBin.at<Vec3b>(LINHA, COLUNA+1)[VERMELHO] == 0))
            {
                SupDirX = LINHA;
                SupDirY = COLUNA;
                circle(quadradoBin, Point(COLUNA,LINHA),3, Scalar(0,0,255), -1, 8,0 );
            }
        }
    }

    fprintf(arquivo, "%d;", contBranco);
    fprintf(arquivo, "%d;", TipoQuadrado);

    fclose(arquivo);
    imshow("Tela de teste RGB", quadradoBin);
    printf("Altura: %d", InfEsqX - supEsqX);
    printf("Largura: %d", infDirY - InfEsqY);

    waitKey(0);

    return 0;
}
