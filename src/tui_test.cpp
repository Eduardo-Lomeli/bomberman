#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <iostream>
#include <string>
#include <thread>  //cintrolar ciclos
#include <ftxui/screen/color.hpp>
#include <experimental/random>
#include <list>
#include <fstream>

using namespace std;
using namespace ftxui;


int main(int argc, char const *argv[])
{
    list<string> textos;
    fstream imagen;
    imagen.open("./assets/imagen.txt");
    string linea;

    while (getline(imagen, linea))
    {
        textos.push_back(linea);
    }
    imagen.close();
    



    int fotograma = 0;
    string reset;
    int posX = 0;
    int posY = 0;
    while (true)
    {
        fotograma ++;

        int r = experimental::randint(0,255);
        int g = experimental::randint(0,255);
        int b = experimental::randint(0,255);


        Element personaje = spinner(21, fotograma);
        Decorator ColorFondo = bgcolor(Color::RGB(b,r,g));
        Decorator ColorTexto = color(Color::RGB(r,g,b));
        Element dibujo  = border({
            hbox(personaje) | ColorFondo | ColorTexto
        });

        Dimensions Alto = Dimension::Full();
        Dimensions Ancho = Dimension::Full();

        Screen pantalla = Screen::Create(Ancho, Alto);
        Render(pantalla, dibujo);
        
        int l = 0;
        for (auto &&texto : textos)
        {
            int i = 0;
            for (auto &&letra : texto)
            {
                pantalla.PixelAt(posX +i, posY +l).character =letra;
                i++;
            }
            l++;
        }
        posX++;
        

        pantalla.Print();
        reset = pantalla.ResetPosition();
        cout << reset;
        this_thread::sleep_for(0.1s);
    }

    return 0;
}
