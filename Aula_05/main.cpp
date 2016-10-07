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
//----------------------------------------------Funcoes Caue/Opencv-------------------------------------------------//
Mat doPyrDown(Mat in){
    // Best to make sure input image is divisible by two. //
    assert( in.cols%2 == 0 && in.rows%2 == 0 );
    Mat out(in.cols/2, in.rows/2,CV_8U);
    pyrDown( in, out );
    return(out);
}

Mat doCanny(Mat in, double lowThresh, double highThresh, double aperture){
    if(in.empty())
        qDebug() << "imagem nula";
    else{
        if(in.channels() != 1)
            return Mat(); //Canny only handles gray scale images
        Mat out(in.cols, in.rows, CV_8U);
        Canny(in,out,lowThresh,highThresh,aperture,false);
        return(out);
    }
}
//--------------------------------------------------------X----------------------------------------------------------//



int main(int argc, char *argv[])
{
    Mat originalRGB,originalCinza,imgMetade,imgBordas;
    Mat original; //para ler o video
    originalRGB = imread("lena.jpg",1);//colorida
    originalCinza = imread("lena.jpg",0);//cinza
    int i,j;


    //---------------testando os filtros na imagem da lena----------------
    //     imgMetade=doPyrDown(originalRGB);
    //     imgBordas=doCanny(originalCinza,30,70,3);

    //     imshow("teste",originalRGB);
    //     waitKey(0);

    //     imshow("teste",imgBordas);
    //     waitKey(0);

    //     imshow("teste",imgMetade);
    //     waitKey(0);
    //------------------------------------------------------------------

    //---------------------------parte do codigo que grava um video a partir da webcam
    VideoCapture camvid(0);//abertura da camera
    if(!camvid.isOpened())
    {
        cout << "Erro: webcam inativa" << endl;
        return -1;
    }

    VideoWriter video1("video.avi",CV_FOURCC('M','J','P','G'),10,
                       Size(camvid.get(CV_CAP_PROP_FRAME_WIDTH),
                            camvid.get(CV_CAP_PROP_FRAME_HEIGHT)),true);

    int t = time(NULL);//pega tempo em segundos
    do
    {
        camvid.read(original);//le frame atual da camera

        //-----------------testando o filtro de Canny aplicado frame a frame
        //        cvtColor(original,original,CV_RGB2GRAY,0);
        //        original=doCanny(original,30,70,3);
        //------------------------------------------------------------------

        //--------------------parte do código que filtra cada plano de cor--------------------------------
        //         for(i=0;i<original.rows;i++)
        //         {
        //             for(j=0;j<original.cols;j++)
        //             {
        //                 original.at<Vec3b>(i,j)[0]=0;    //comentar para não filtrar o plano azul
        //                 //original.at<Vec3b>(i,j)[1]=0;  //comentar para não filtrar o plano green
        //                 original.at<Vec3b>(i,j)[2]=0;    //comentar para não filtrar o plano red
        //             }
        //         }
        //------------------------------------------------------------------------------------------------


        //--------------------parte que filtra a imagem para pegar quadrado azul--------------------------
        //         for(i=0;i<original.rows;i++)
        //         {
        //             for(j=0;j<original.cols;j++)
        //             {
        //                 if(original.at<Vec3b>(i,j)[0]>100
        //                         &&original.at<Vec3b>(i,j)[1]<100
        //                         &&original.at<Vec3b>(i,j)[2]<100)
        //                 {

        //                     original.at<Vec3b>(i,j)[0]=255;    //comentar para não filtrar o plano azul
        //                     original.at<Vec3b>(i,j)[1]=255;  //comentar para não filtrar o plano green
        //                     original.at<Vec3b>(i,j)[2]=255;    //comentar para não filtrar o plano red
        //                 }
        //                 else
        //                 {
        //                     original.at<Vec3b>(i,j)[0]=0;    //comentar para não filtrar o plano azul
        //                     original.at<Vec3b>(i,j)[1]=0;  //comentar para não filtrar o plano green
        //                     original.at<Vec3b>(i,j)[2]=0;    //comentar para não f
        //                 }
        //             }
        //         }


        //testar o efeito da erosao!!!
        //Mat kernel = getStructuringElement(MORPH_RECT, Size(3,3));
        //erode(input,output,kernel);

        imshow("Original", original);//apresenta frame lido na tela
        video1.write(original);//grava o video no HD
        waitKey(75);

    }while(time(NULL) - t <= 15);//encerra o laco em 5 segundos

    qDebug()<<"Tempo: "<<time(NULL) - t <<" segundos";

    destroyWindow("Original");
    original.release();
    camvid.release();
    video1.release();


    //-------------------------Se quiserem gravar os frames no HD, descomentar essa parte (abaixo).

    char num[4],filename[25];
    VideoCapture video("video.avi");
    if(!video.isOpened())
    {
        cout << "Erro: video nao encontrado" << endl;
        return -1;
    }
    for(int i=0;;i++)
    {
        video.read(original);

        if(original.empty())
            break;

        cvtColor(original,original,CV_RGB2GRAY,0);
        original = doCanny(original, 30,70,3);

        sprintf(num,"%d",i+1);

        for(int j=0;j<25;j++)
            filename[j] = '\0';

        strcat(filename,"imagem");
        strcat(filename,num);
        strcat(filename,".jpg");
        imwrite(filename,original);
    }

    original.release();
    video.release();



    return 0;
}
