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
    Mat boneco (600,600,CV_8UC1);
    int i,j;
    int centrox,centroy;
    int centrocabecax,centrocabecay;

    //pintando fundo de preto
    for(i=0;i<boneco.rows;i++)
    {
        for(j=0;j<boneco.cols;j++)
        {
            boneco.at<uchar>(i,j)=0;
        }
    }

    //coordenadas do centro da imagem
    centrox=boneco.rows/2;
    centroy=boneco.cols/2;

    //coordenadas do centro da cabeça
    centrocabecax=centrox;
    centrocabecay=centroy-(2*(boneco.rows/6));

    circle(boneco,Point(centrocabecax,centrocabecay),(boneco.cols/12),255,2,8,0);
    //desenhando ponto de conexão da cabeça com o tronco
    //O parâmetro -1 indica preenchimento
    //coordenada x não muda e na y somamo o raio
    circle(boneco,Point(centrocabecax,centrocabecay+boneco.cols/12),5,255,-1,8,0);



    line(boneco,Point(centrocabecax,centrocabecay+boneco.cols/12),Point(centrocabecax,2*(boneco.rows/3)),255,2,8,0);
    //desenhando ponto de conexão do troco com a perna
    //O parâmetro -1 indica preenchimento
    //coordenada x não muda e na y somamo o raio
    circle(boneco,Point(centrocabecax,2*(boneco.rows/3)),5,255,-1,8,0);


    //coordenadas complicadas. Estamos fazendo a perna esquerda de maneira dinâmica. Isso acaba sendo difícil
    //depois treinar em casa desenhando bonecos desde o início
    line(boneco,Point(centrocabecax,2*(boneco.rows/3)),Point(centrocabecax-(boneco.rows/6),(2*(boneco.rows/3))+(boneco.rows/6)),255,2,8,0);

    //coordenadas complicadas. Estamos fazendo a perna direita de maneira dinâmica. Isso acaba sendo difícil
    //depois treinar em casa desenhando bonecos desde o início
    line(boneco,Point(centrocabecax,2*(boneco.rows/3)),Point(centrocabecax+(boneco.rows/6),(2*(boneco.rows/3))+(boneco.rows/6)),255,2,8,0);

    //coordenadas complicadas. Estamos fazemos o braço esquerdo.
    line(boneco,Point(centrocabecax,centrocabecay+boneco.cols/12),Point(centrocabecax-(boneco.rows/6),(2*(boneco.rows/5))),255,2,8,0);


    //coordenadas complicadas. Estamos fazemos o braço direito.
    line(boneco,Point(centrocabecax,centrocabecay+boneco.cols/12),Point(centrocabecax+(boneco.rows/6),(2*(boneco.rows/5))),255,2,8,0);



    imwrite("boneco.jpg",boneco);
    imshow("Tela de Teste", boneco);
    waitKey(0);

    return 0;
}
