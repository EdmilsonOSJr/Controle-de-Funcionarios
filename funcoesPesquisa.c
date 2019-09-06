#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include<ctype.h>
#include"Departamento.h"
#include"Funcionario.h"
#include"HistoricoDepartamento.h"
#include"HistoricoFuncionario.h"
#include"HistoricoSalario.h"
#include"funcoesPesquisa.h"
#include"funcoesVerificacao.h"

//Retorna a posição da matricula caso exista, senão retorna -1
int PesquisaMatricula(FILE *fun,char *matricula){
    int pos=0;
    TFuncionario f;

    rewind(fun);

    while(fread(&f, sizeof(f), 1, fun)){
        if(strcmp(f.matricula,matricula)==0)
            return pos;
        pos++;

    }

    return -1;
}//fim PesquisaMatricula()

//Recebe o ponteiro do arquivo e o nome do departamento, retornando seu id caso exista e 0 caso contraário
long PesquisaDepartamentoNome(FILE*dep,char *depar){

    TDepartamento d;

    rewind(dep);
    while(fread(&d, sizeof(d), 1, dep)){
        if(strcmp(d.nome,depar)==0)
            return d.id;
    }
    return 0;
}//fim PesquisaDepartamentoNome()

/*realiza uma pesquisa no arquivo departamento.dat, caso encontre retorna a posição e se não encontar retorna -1 */
int PesquisaDepartamentoID(FILE *dep,long id){
    int pos=0;
    TDepartamento d;

    rewind(dep);
    while(fread(&d, sizeof(d), 1, dep)){

        if(d.id == id)
            return pos;

        pos++;

    }
    return -1;
}//fim pesquisaDepartamentoID()

/*realiza uma pesquisa no arquivo funcionario.dat, caso encontre retorna a posição e se não encontar retorna -1 */
int PesquisaFunID(FILE *fun,long id){
    int pos=0;
    TFuncionario f;

    rewind(fun);
    while(fread(&f, sizeof(f), 1, fun)){
        if(f.id == id)
            return pos;
        pos++;
    }

    return -1; //Funcionario não foi encontrada.

}//fim pesquisafunID()
