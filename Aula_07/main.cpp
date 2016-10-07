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
    Mat imagem; //para ler o video
    int i,j;
    int diametro, primeiroPonto, segundoPonto, corte;
    int largura[3];

    VideoCapture camera(0);//abertura da camera
    if(!camera.isOpened())
    {
        cout << "Erro: webcam inativa" << endl;
        return -1;
    }

    VideoWriter video("video.avi",CV_FOURCC('M','J','P','G'),10,
                       Size(camera.get(CV_CAP_PROP_FRAME_WIDTH),
                            camera.get(CV_CAP_PROP_FRAME_HEIGHT)),true);

    int t = time(NULL);//pega tempo em segundos
    do
    {
        camera.read(imagem);//le frame atual da camera

        //-----------------testando o filtro de Canny aplicado frame a frame
        //        cvtColor(original,original,CV_RGB2GRAY,0);
        //        original=doCanny(original,30,70,3);
        //------------------------------------------------------------------

        //--------------------parte do código que filtra cada plano de cor--------------------------------
        //         for(i=0;i<imagemOriginal.rows;i++)
        //         {
        //             for(j=0;j<imagemOriginal.cols;j++)
        //             {
        //                 imagemOriginal.at<Vec3b>(i,j)[BLUE]=INTENSIDADEMAXIMACOR;    //comentar para não filtrar o plano azul
        //                 imagemOriginal.at<Vec3b>(i,j)[GREEN]=INTENSIDADEMAXIMACOR;  //comentar para não filtrar o plano green
        //                 imagemOriginal.at<Vec3b>(i,j)[RED]=INTENSIDADEMINIMACOR;    //comentar para não filtrar o plano red
        //             }
        //         }
        // ------------------------------------------------------------------------------------------------


        //--------------------parte que filtra a imagem para pegar quadrado azul--------------------------
                 for(i=0;i<imagem.rows;i++)
                 {
                     for(j=0;j<imagem.cols;j++)
                     {
                         if(imagem.at<Vec3b>(i,j)[BLUE] < 70 &&
                                 imagem.at<Vec3b>(i,j)[GREEN] < 70 &&
                                 imagem.at<Vec3b>(i,j)[RED] > 120)
                         {
                             imagem.at<Vec3b>(i,j)[BLUE]=INTENSIDADEMAXIMACOR;    //comentar para não filtrar o plano azul
                             imagem.at<Vec3b>(i,j)[GREEN]=INTENSIDADEMAXIMACOR;  //comentar para não filtrar o plano green
                             imagem.at<Vec3b>(i,j)[RED]=INTENSIDADEMAXIMACOR;    //comentar para não filtrar o plano red
                         }
                      else
                      {
                          imagem.at<Vec3b>(i,j)[0]=INTENSIDADEMINIMACOR;    //comentar para não filtrar o plano azul
                          imagem.at<Vec3b>(i,j)[1]=INTENSIDADEMINIMACOR;  //comentar para não filtrar o plano green
                          imagem.at<Vec3b>(i,j)[2]=INTENSIDADEMINIMACOR;    //comentar para não f
                      }
                     }
                 }

        //testar o efeito da erosao!!!
        //Mat kernel = getStructuringElement(MORPH_RECT, Size(3,3));
        //erode(input,output,kernel);

        imshow("Original", imagem);//apresenta frame lido na tela
        video.write(imagem);//grava o video no HD
        waitKey(75);

    }while(time(NULL) - t <= 15);//encerra o laco em 5 segundos

    qDebug()<<"Tempo: "<<time(NULL) - t <<" segundos";

    destroyWindow("Original");
    imagem.release();
    camera.release();
    video.release();


    //-------------------------Se quiserem gravar os frames no HD, descomentar essa parte (abaixo).

    char num[4],filename[25];
    VideoCapture vid("video.avi");
    if(!vid.isOpened())
    {
        cout << "Erro: video nao encontrado" << endl;
        return -1;
    }
    for(int i=0;;i++)
    {
        vid.read(imagem);

        if(imagem.empty())
            break;

        cvtColor(imagem,imagem,CV_RGB2GRAY,0);

        sprintf(num,"%d",i+1);

        for(int j=0;j<25;j++)
            filename[j] = '\0';

        primeiroPonto = BuscarPrimeiroPonto(imagem);
        segundoPonto = BuscarSegundoPonto(imagem);

        if (primeiroPonto != -1 && segundoPonto != -1)
        {
            diametro = segundoPonto - primeiroPonto;
            corte = diametro/QUANTIDADEPEDACOS;
            // Começa por 1 já que o pedaço 0 é o ponto inicial
            for(int PEDACO=1;PEDACO<QUANTIDADEPEDACOS;PEDACO++)
            {
                largura[PEDACO - 1] = BuscarLargura(imagem, primeiroPonto + (corte * PEDACO));
                DesenharLinha(imagem, primeiroPonto + (corte * PEDACO), INTENSIDADEMINIMACOR);
            }
        }

        primeiroPonto = -1;
        segundoPonto = -1;

        strcat(filename,"imagem");
        strcat(filename,num);
        strcat(filename,".jpg");
        imwrite(filename,imagem);
    }

    imagem.release();
    vid.release();



    return 0;
}
