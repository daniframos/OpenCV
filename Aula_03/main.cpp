//--------------------------------------------Bibliotecas e Diretivas------------------------------------------------//
#include <stdio.h>
#include "opencv/cv.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "QDebug"
#include <time.h>

using namespace cv;
using namespace std;
//--------------------------------------------------------X----------------------------------------------------------//



int main()
{
    // Variável do open cv própria para receber e manipular imagens


    // a variavel logica imagem.rgb
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

    return 0;
}
