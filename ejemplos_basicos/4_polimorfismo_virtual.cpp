#include <iostream>
using namespace std;


class Estudiante{  //Base
    public:
        void come(){cout<< "Alimentos Baratos \n";}  //se llama en tiempo de compilaci�n
        virtual  void toma(){cout<< "Bebidas Baratas \n";} //se llama en tiempo de ejecuci�n
};

class Programador : public Estudiante{
    public:
        void come(){cout << "Pizza \n";}
        void toma(){cout << "cafe \n";}
};

/** Al usar apuntadores al obejto padre (Estudiante),
se define come() en tiempo de compilacion(Memoria Est�tica) por lo que se manda a
llamar a la funcion de come de Estudiante.

Pero toma() es virtual lo que hace que se mande en tiempo de ejecuci�n (Memoria Din�mica)
como "new" es memoria din�mica que crea el objeto en tiempo de ejecuci�n
entonces es hasta que programador ya est� creado que se manda a llama toma()
**/

int main(){
   //Mem.Estatica   o  //Mem. Din�mica
   //Tiempo de comp    //tiempo de ejecuci�n
    Estudiante *est =  new Programador();

    est->come();   //imprime Alimentos Baratos  (sin virtual)
    est->toma();   //imprime Cafe               (con virtual)

}
