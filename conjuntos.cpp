/* DAVID BRITO 30521360   */


#include <iostream>
using namespace std;


const int bloques = 4;
const int conjuntos = 2;
const int palabras = 1;

int memoria[palabras][bloques];
int memoriaVisitados[palabras][bloques];

void inicializarMemoria (){
    int i;
    for (i=0;i<bloques;i++){
        memoria[0][i]= -1;
        memoriaVisitados[0][i]= 0;
    }    
}

void escribirEnBloque(int bloque, int palabra, int direccion){
    memoria[palabra][bloque] = direccion;
}
int determinarConjunto (int direccion){
    return direccion % conjuntos;
}

int verificarBloque (int bloque, int direccion){
    int acierto;

    if (memoria[0][bloque] == direccion){
        acierto=1;
    }else{
        acierto=0;
    }
    return acierto;
}

int buscarLRU(int conjunto){
    int i, indiceMenor=0;
    int menor = 500;

    for (i=0;i< bloques/conjuntos; i++){
        if (memoriaVisitados[0][(bloques/conjuntos) * conjunto + i] < menor){
            menor = memoriaVisitados[0][(bloques/conjuntos) * conjunto + i];
            indiceMenor=i;
        }
    }
    return (bloques / conjuntos * conjunto + indiceMenor);
}

int verificarConjunto (int conjunto, int direccion, int *secuencia){
    int acierto=0,i=0, band=0;
    int bloqueSeleccionado;


    while(i < bloques / conjuntos && !band){
        if (memoriaVisitados[0][(bloques/conjuntos) * conjunto + i] > 0){
            if (verificarBloque((bloques/conjuntos) * conjunto + i, direccion)){
                band=1;
                acierto=1;
                memoriaVisitados[0][(bloques/conjuntos) * conjunto + i] = *secuencia;
            }
        }else{
            acierto=0;
            band=1;
            escribirEnBloque((bloques/conjuntos) * conjunto + i,0,direccion);
            memoriaVisitados[0][(bloques/conjuntos) * conjunto + i] = *secuencia;
        }
        i++;
    }
    if (!band){
        bloqueSeleccionado = buscarLRU(conjunto);
        escribirEnBloque(bloqueSeleccionado,0,direccion);
        memoriaVisitados[0][bloqueSeleccionado] = *secuencia;
    }
    *secuencia = *secuencia + 1;

    return acierto;
}



int main(){
    int secuencia = 1;
    int fallos=0, i=0, direccion,conjunto, estado;
    string msg;
    inicializarMemoria();
    int elementos = bloques / conjuntos;

    cout << "dir" << "   " << "A/F" << "   " << "C0" << "   " << "C1" << "   " << "C2" << "   " << "C3" << "\n";
    while(cin >> direccion){

        conjunto = determinarConjunto(direccion);
        estado = verificarConjunto(conjunto,direccion, &secuencia);
        if (!estado) {
            msg = "F";
            fallos++;
        }else{
            msg = "A";
        }
        cout << direccion << "   " << msg << "   " << memoria[0][0] << "   " << memoria[0][1] << "   " << memoria[0][2] << "   " << memoria[0][3] << "\n";
    }

    return 0;
}