#ifndef FUNCOESAUXILIARES_H_INCLUDED
#define FUNCOESAUXILIARES_H_INCLUDED

//Nessa funçaõ o \n do vetor de char é trocado pelo \0
void RetiraSequenciaDeEscape(char *);
int sairDoLoop();
long IncrementaIdFun(FILE*);
long IncrementaID(FILE*);

//Função usada para imprimir os dados de um funcionário incluindo seu departamento
void apresentaDadosDoFuncionario(FILE*, FILE *, int);

//void coletaDadosDoFuncionario(FILE*,FILE*,FILE*,FILE*);

void dataAtual(int*,int*,int*);
#endif // FUNCOESAUXILIARES_H_INCLUDED
