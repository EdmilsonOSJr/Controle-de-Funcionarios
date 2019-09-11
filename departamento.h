#ifndef DEPARTAMENTO_H_INCLUDED
#define DEPARTAMENTO_H_INCLUDED

typedef struct{
    long id;
    char nome[40];
    long id_gerente;
    char sigla[10];
    unsigned short int Ramal;
}TDepartamento;

void CadastraDepartamento(FILE*,FILE*);
void AlterarGerente(FILE*,FILE*,FILE*);
void imprimir(FILE*);

#endif // DEPARTAMENTO_H_INCLUDED
