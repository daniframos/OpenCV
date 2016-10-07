//--------------------------------------------Bibliotecas e Diretivas------------------------------------------------//
#include <stdio.h>
#include "opencv/cv.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "QDebug"
#include <time.h>

#define INTENSIDADEMAXIMACOR 255 // Branco
#define INTENSIDADEMINIMACOR 0 // Preto

#define BLUE 0 // AZUL
#define GREEN 1 // VERDE
#define RED 2 // VERMELHO

#define QUANTIDADEPEDACOS 4

using namespace cv;
using namespace std;
//-------------------------------------------------------------------------------------------------------------------//

int BuscarPrimeiroPonto(Mat imagem)
{
    int primeiroPonto = -1;

    for(int LINHA = 0; LINHA < imagem.rows; LINHA ++)
    {
        for(int COLUNA = 0; COLUNA < imagem.cols; COLUNA ++)
        {
            if (imagem.at<uchar>(LINHA, COLUNA) > (INTENSIDADEMAXIMACOR - 15) &&
                    imagem.at<uchar>(LINHA, COLUNA+1) > (INTENSIDADEMAXIMACOR - 15) &&
                    imagem.at<uchar>(LINHA, COLUNA-1) < (INTENSIDADEMINIMACOR + 15) &&
                    imagem.at<uchar>(LINHA-1, COLUNA) < (INTENSIDADEMINIMACOR + 15) &&
                    imagem.at<uchar>(LINHA+1, COLUNA) > (INTENSIDADEMAXIMACOR - 15))
            {
                primeiroPonto = LINHA;
                return primeiroPonto;
            }
        }
    }
    return primeiroPonto;
}

int BuscarSegundoPonto(Mat imagem)
{
    int segundoPonto = -1;

    for(int LINHA = imagem.rows - 1; LINHA >= 0; LINHA --)
    {
        for(int COLUNA = 0; COLUNA < imagem.cols; COLUNA++)
        {
            if (imagem.at<uchar>(LINHA, COLUNA) > (INTENSIDADEMAXIMACOR -15) &&
                    imagem.at<uchar>(LINHA, COLUNA+1) > (INTENSIDADEMAXIMACOR - 15) &&
                    imagem.at<uchar>(LINHA, COLUNA-1) < (INTENSIDADEMINIMACOR + 15) &&
                    imagem.at<uchar>(LINHA-1, COLUNA) > (INTENSIDADEMAXIMACOR - 15) &&
                    imagem.at<uchar>(LINHA+1, COLUNA) < (INTENSIDADEMINIMACOR + 15))
            {
                segundoPonto = LINHA;
                return segundoPonto;
            }
        }
    }

    return segundoPonto;

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
        if (imagem.at<uchar>(linha, COLUNA) > (INTENSIDADEMAXIMACOR -15) &&
                imagem.at<uchar>(linha, COLUNA-1) < (INTENSIDADEMINIMACOR + 15) &&
                imagem.at<uchar>(linha, COLUNA+1) > (INTENSIDADEMAXIMACOR -15))
        {
            primeiraColuna = COLUNA;
        }

        if (imagem.at<uchar>(linha, COLUNA) > (INTENSIDADEMAXIMACOR - 15) &&
                imagem.at<uchar>(linha, COLUNA-1) > (INTENSIDADEMAXIMACOR - 15) &&
                imagem.at<uchar>(linha, COLUNA+1) < (INTENSIDADEMINIMACOR + 15))
        {
            segundaColuna = COLUNA;
        }
    }
    largura = segundaColuna - primeiraColuna;
    return largura;
}


int main(int argc, char *argv[])
{
    Mat imagem;
    int diametro, primeiroPonto, segundoPonto, corte;
    int largura[3];

    imagem = imread("Demo.jpg", CV_LOAD_IMAGE_GRAYSCALE);

    primeiroPonto = BuscarPrimeiroPonto(imagem);
    segundoPonto = BuscarSegundoPonto(imagem);
    printf("Primeiro Ponto: %d", primeiroPonto);
    printf("Segundo Ponto: %d", segundoPonto);

    diametro = segundoPonto - primeiroPonto;

    corte = diametro/QUANTIDADEPEDACOS;
    // Começa por 1 já que o pedaço 0 é o ponto inicial
    for(int PEDACO=1;PEDACO<QUANTIDADEPEDACOS;PEDACO++)
    {
        largura[PEDACO - 1] = BuscarLargura(imagem, primeiroPonto + (corte * PEDACO));
        DesenharLinha(imagem, primeiroPonto + (corte * PEDACO), INTENSIDADEMINIMACOR);
    }

    namedWindow( "Display window", WINDOW_AUTOSIZE );// Create a window for display.
    imshow( "Display window", imagem );
    waitKey(0);


    return 0;
}
