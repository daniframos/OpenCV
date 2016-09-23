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
#define NIVELMAXIMOCOR 255
#define NIVELMINIMOCOR 0
using namespace cv;
using namespace std;

//--------------------------------------------------------X----------------------------------------------------------//

int main(int argc, char *argv[])
{
    Mat imagemCinza = imread("livro.jpg",0);

    // Função para mostrar na tela a imagem

    int i;
    int j;

    for(i = 0; i<imagemCinza.rows;i++){
        for(j = 0;j<imagemCinza.cols;j++){
            if (imagemCinza.at<uchar>(i,j) > 120){
                imagemCinza.at<uchar>(i,j) = 255;
            }
            else {
                imagemCinza.at<uchar>(i,j) = 0;
            }
        }
    }

    imshow("Teste cinza", imagemCinza);
    // Função que pausa a tela até apertar uma tecla
    waitKey(0);
}
