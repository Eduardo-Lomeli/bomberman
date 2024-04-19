#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <iostream>
#include <string>
#include <thread>  //cintrolar ciclos
#include <ftxui/screen/color.hpp>
#include <experimental/random>

using namespace std;
using namespace ftxui;


int main(int argc, char const *argv[])
{
    int fotograma = 0;
    string reset;
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

        Dimensions Alto = Dimension::Fixed(10);
        Dimensions Ancho = Dimension::Full();

        Screen pantalla = Screen::Create(Ancho, Alto);

        Render(pantalla, dibujo);
        pantalla.Print();
        reset = pantalla.ResetPosition();
        cout << reset;
        this_thread::sleep_for(0.5s);
    }

    return 0;
}
