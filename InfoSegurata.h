#include <String>
#ifndef DESAFIOFINAL_SEGURATA_H
#define DESAFIOFINAL_SEGURATA_H
using namespace std;

class InfoSegurata{
private:
    string nombre_segurata;
    int evaluacion_candidato;
    int evaluacion_candidato_max;
    int evaluacion_candidato_min;

public:
    InfoSegurata(string nombre, int puntuacion){
        InfoSegurata::nombre_segurata = nombre;
        InfoSegurata::evaluacion_candidato = puntuacion;
        InfoSegurata::evaluacion_candidato_max = 0;
        InfoSegurata::evaluacion_candidato_min = 0;
    }

    InfoSegurata(){};

    string mostrarSeguratas(){
        return "Nombre segurata: " + nombre_segurata + " evaluacion_candidato: " + to_string(evaluacion_candidato) + " Min: " + to_string(evaluacion_candidato_min) + " Max: " + to_string(evaluacion_candidato_max) ;
    }

public:
    const string &getNombreSegurata() const {
        return nombre_segurata;
    }

    void setNombreSegurata(const string &nombreSegurata) {
        nombre_segurata = nombreSegurata;
    }

    int getEvaluacionCandidato() const {
        return evaluacion_candidato;
    }

    void setEvaluacionCandidato(int evaluacionCandidato) {
        evaluacion_candidato = evaluacionCandidato;
    }

    int getEvaluacionCandidatoMax() const {
        return evaluacion_candidato_max;
    }

    void setEvaluacionCandidatoMax(int evaluacionCandidatoMax) {
        evaluacion_candidato_max = evaluacionCandidatoMax;
    }

    int getEvaluacionCandidatoMin() const {
        return evaluacion_candidato_min;
    }

    void setEvaluacionCandidatoMin(int evaluacionCandidatoMin) {
        evaluacion_candidato_min = evaluacionCandidatoMin;
    }
};

class CompararPuntuacion{
public:
    bool operator()(const InfoSegurata& a, const InfoSegurata& b) {
        return a.getEvaluacionCandidato() > b.getEvaluacionCandidato();
    }
};

#endif //DESAFIOFINAL_SEGURATA_H


