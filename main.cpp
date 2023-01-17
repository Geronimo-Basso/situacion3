#include <iostream>
#include <string>
#include <algorithm>
#include "InfoSegurata.h"
using namespace std;


template<typename InfoSegurata> class VectorPEL{
private:
    InfoSegurata * v_, * space_, * last_;

public:
    VectorPEL(): v_{new InfoSegurata[0]}, space_{v_}, last_{v_} {}
    VectorPEL(VectorPEL<InfoSegurata> const& v): v_{new InfoSegurata[v.capacity()]}, space_{v_ + v.size()}, last_{v_ + v.capacity()} {
        try{
            for(auto i = size_t{0}; i< v.size(); ++i){
                v_[i] = v[i];
            }
        }
        catch (...){
            delete[] v_;
            throw;
        }
    }
    ~VectorPEL() {delete[] v_;}

    auto capacity() const -> size_t {return last_ - v_;}
    auto size() const -> size_t {return space_ - v_;}
    auto empty() const -> bool {return v_ == last_;}
    int num(int x){
        return x;
    }
    auto now(int x) -> InfoSegurata* {return v_ + x;}

    auto begin() -> InfoSegurata* {return v_;}
    auto begin() const -> InfoSegurata const* {return v_;}
    auto end() -> InfoSegurata* {return space_;}
    auto end() const -> InfoSegurata const* {return space_;}

    auto push_back(InfoSegurata const& valor){
        if(space_ ==  last_){
            size_t cp =  capacity(), new_cp = (cp == 0)? 2:2*cp;
            InfoSegurata* new_block = new InfoSegurata[new_cp];
            try {
                for (auto i = size_t{}; i < cp; ++i) {
                    new_block[i] = v_[i];
                }
                new_block[cp] = valor;
            }
            catch (...){
                delete[] new_block;
                throw;
            }
            delete[] v_;
            v_ = new_block;
            space_ = new_block + cp + 1;
            last_ = new_block + new_cp;
        }
        else{
            *space_ = valor;
            ++space_;
        }
    }


};

int main(){
    VectorPEL<InfoSegurata> *infoSeguratas = new VectorPEL<InfoSegurata>;
    int caso;
    bool apagar = false;
    while (apagar == false){

        cout << "[1] Crear un segurata" << endl <<  "[2] Mostrar listado de seguratas" << endl << "[3] Salir" << endl;
        cout << "Elija una opcion: ";
        cin >> caso;
        cout << endl;

        switch (caso) {
            case 1: {
                string nombreSegurata;
                int puntuacionSegurata;
                cout << "Escriba el nombre del segurata: ";
                cin >> nombreSegurata;
                bool condicion = false;
                while (condicion == false) {
                    cout << "Introduzca la evaluacion del segurata (0 a 100): ";
                    cin >> puntuacionSegurata;
                    if (puntuacionSegurata >= 0 && puntuacionSegurata <= 100) {
                        condicion = true;
                    } else {
                        cout << "El valor introducido no es correcto." << endl;
                    }
                }

                if(infoSeguratas->size() == 0){
                    InfoSegurata *segurataAAgregar = new InfoSegurata(nombreSegurata, puntuacionSegurata);
                    segurataAAgregar->setEvaluacionCandidatoMax(puntuacionSegurata);
                    segurataAAgregar->setEvaluacionCandidatoMin(puntuacionSegurata);
                    infoSeguratas->push_back(*segurataAAgregar);
                    sort(infoSeguratas->begin(), infoSeguratas->end(), CompararPuntuacion());
                }else {
                    for (int i = 0; i < infoSeguratas->size(); ++i) {
                        if (!(nombreSegurata == infoSeguratas->now(i)->getNombreSegurata())) {
                            InfoSegurata *segurataAAgregar = new InfoSegurata(nombreSegurata, puntuacionSegurata);
                            segurataAAgregar->setEvaluacionCandidatoMax(puntuacionSegurata);
                            segurataAAgregar->setEvaluacionCandidatoMin(puntuacionSegurata);
                            infoSeguratas->push_back(*segurataAAgregar);
                            sort(infoSeguratas->begin(), infoSeguratas->end(), CompararPuntuacion());
                            break;
                        } else {
                            if (puntuacionSegurata > infoSeguratas->now(i)->getEvaluacionCandidatoMax()) {
                                infoSeguratas->now(i)->setEvaluacionCandidatoMax(puntuacionSegurata);
                            } else {
                                infoSeguratas->now(i)->setEvaluacionCandidatoMin(puntuacionSegurata);
                            }
                        }
                    }
                }

                    //print
                    for (int i = 0; i < infoSeguratas->size(); ++i) {
                        cout << infoSeguratas->now(i)->mostrarSeguratas() << endl;
                        cout << "------------------------" << endl;
                    }

                break;
            }
            case 2: {
                int puntuacionesSeguratas = 0;
                int promedio;
                for (int i = 0; i < infoSeguratas->size(); ++i) {
                    InfoSegurata datos = *infoSeguratas->now(i);
                    cout << "InfoSegurata " << (i + 1) << ": " << datos.getNombreSegurata() << endl;
                    cout << "Puntuacion: " << datos.getEvaluacionCandidato() << endl << endl;
                    puntuacionesSeguratas += datos.getEvaluacionCandidato();
                }
                promedio = puntuacionesSeguratas/infoSeguratas->size();
                cout << "Promedio seguratas: " << promedio << endl;

                break;
            }
            case 3: {
                return 0;
            }
            default:{
                cout << "ERROR ! Introduzca un caracter valido" << endl;
            }
        }
    }
}