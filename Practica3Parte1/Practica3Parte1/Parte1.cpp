

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>

// Librerías de OpenCV 4
//#include <opencv2/opencv.hpp>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/video/video.hpp>
#include <opencv2/videoio/videoio.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/objdetect/objdetect.hpp>

#include <time.h>

using namespace std;
using namespace cv;
Mat frame;


void MetodoHog(Mat peaton ,Mat filtrado)
{
    HOGDescriptor hog;
    hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());

    vector<Rect> peatones, peatonesFiltrados;


    hog.detectMultiScale(peaton, peatones, 0, Size(4, 4), Size(32, 32), 1.1, 1.5);
    Rect aux;
    int j = 0;

    for (int i = 0; i < peatones.size(); i++) {
        aux = peatones[i];
        j = 0;
        for (j = 0; j < peatones.size(); j++) {
            if (i != j && (aux & peatones[j]) == aux) //Reconocimiento (Filtrado)
                break;
        }

        if (j == peatones.size())
            peatonesFiltrados.push_back(aux);
    }
    cout << "Peatones Encontrados: " << peatonesFiltrados.size() << endl;


    for (int i = 0; i < peatones.size(); i++) {
        aux = peatones[i];
        rectangle(peaton, aux.tl(), aux.br(), Scalar(0, 255, 0), 2);
    }

    for (int i = 0; i < peatonesFiltrados.size(); i++) {
        aux = peatonesFiltrados[i];
        aux.x += cvRound(aux.width * 0.1);
        aux.width = cvRound(aux.width * 0.85);
        aux.y += cvRound(aux.height * 0.08);
        aux.height = cvRound(aux.height * 0.8);
        rectangle(filtrado, aux.tl(), aux.br(), Scalar(0, 255, 0), 2);
    }



        
    imshow("Peatones", peaton);
    imshow("Peatones Filtrados", filtrado);
    imshow("Video", frame);


}


int main(int argc, char* argv[]) {
    //Agregacion Del Video 
    string nombreVideo = "VideoCortoBajaCalidad.mp4";
    VideoCapture video(nombreVideo);
    if (video.isOpened()) {
        namedWindow("Video", WINDOW_AUTOSIZE);
        while (3 == 3) {
            video >> frame;
            resize(frame, frame, Size(200,200));
            Mat original = frame;
            Mat peatones = original.clone();
            Mat filtrado = original.clone();
     
            namedWindow("Original", WINDOW_AUTOSIZE);
            namedWindow("Peatones", WINDOW_AUTOSIZE);
            namedWindow("Peatones Filtrados", WINDOW_AUTOSIZE);


            MetodoHog(peatones, filtrado);

            imshow("Original", original);
            if (waitKey(23) == 27)
                break;
        
        }

    

}


   
}
