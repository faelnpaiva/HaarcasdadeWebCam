# HaarcasdadeWebCam
Testing Haarcascade with WebCam and OpenCv 

Compile isso assim :

g++ -Wall -g -lm -DDEBUG `pkg-config --cflags opencv` Camera.cpp `pkg-config --libs opencv` -o Camera

Para cross compilar para raspberry pi , fiz uma tentativa na outra pasta mas ainda nao compilei e testei na placa . 
Provavelmente existem erros . A idéia é usar o haarcascade com a raspcam !
