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

#include <QCoreApplication>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    return a.exec();
}
