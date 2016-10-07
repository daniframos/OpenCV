//--------------------------------------------Bibliotecas e Diretivas------------------------------------------------//
#include <stdio.h>
#include "opencv/cv.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "QDebug"
#include <time.h>

#define INTENSIDADEMAXIMACOR 255 // Branco
#define INTENSIDADEMINIMACOR 0 // Preto

using namespace cv;
using namespace std;
//--------------------------------------------------------X----------------------------------------------------------//

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
    Mat imagemOriginal; //para ler o video
    int i,j;

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
        camera.read(imagemOriginal);//le frame atual da camera

        //-----------------testando o filtro de Canny aplicado frame a frame
        //        cvtColor(original,original,CV_RGB2GRAY,0);
        //        original=doCanny(original,30,70,3);
        //------------------------------------------------------------------

        //--------------------parte do código que filtra cada plano de cor--------------------------------
                 for(i=0;i<imagemOriginal.rows;i++)
                 {
                     for(j=0;j<imagemOriginal.cols;j++)
                     {
                         imagemOriginal.at<Vec3b>(i,j)[0]=0;    //comentar para não filtrar o plano azul
                         // original.at<Vec3b>(i,j)[1]=0;  //comentar para não filtrar o plano green
                         // imagemOriginal.at<Vec3b>(i,j)[2]=0;    //comentar para não filtrar o plano red
                     }
                 }
        // ------------------------------------------------------------------------------------------------


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

        imshow("Original", imagemOriginal);//apresenta frame lido na tela
        video.write(imagemOriginal);//grava o video no HD
        waitKey(75);

    }while(time(NULL) - t <= 15);//encerra o laco em 5 segundos

    qDebug()<<"Tempo: "<<time(NULL) - t <<" segundos";

    destroyWindow("Original");
    imagemOriginal.release();
    camera.release();
    video.release();


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
        video.read(imagemOriginal);

        if(imagemOriginal.empty())
            break;

        cvtColor(imagemOriginal,imagemOriginal,CV_RGB2GRAY,0);
        imagemOriginal = doCanny(imagemOriginal, 30,70,3);

        sprintf(num,"%d",i+1);

        for(int j=0;j<25;j++)
            filename[j] = '\0';

        strcat(filename,"imagem");
        strcat(filename,num);
        strcat(filename,".jpg");
        imwrite(filename,imagemOriginal);
    }

    imagemOriginal.release();
    video.release();



    return 0;
}
