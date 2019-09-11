#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#include <time.h>
#include "departamento.h"
#include "funcionario.h"
#include "funcoesPesquisa.h"

///Nessa função o '\n' do vetor de char é trocado pelo '\0'
void RetiraSequenciaDeEscape(char *palavra){

    if(palavra[strlen(palavra) - 1] == '\n')
        palavra[strlen(palavra) - 1] = '\0';
}//fim RetiraSequenciaDeEscape()

///Essa função é chamadda para sair de um loop que pergunta se o usuário quer sair da opção que escolheu. Nela é validada a opção
///de sair e n será uma letra apenas 1 para sair e 2 para continuar
int sairDoLoop(){
    char sair[3];
    int sairInteiro;

    do
    {
        printf("\n");
        printf("\n===========================");
        printf("\nDeseja sair?");
        printf("\n===========================");
        printf("\n1-Sim     2-Não\n");
        printf("\n=> ");
        setbuf(stdin,NULL);
        fgets(sair,3,stdin);
        setbuf(stdin,NULL);

        RetiraSequenciaDeEscape(sair);
        sairInteiro=atoi(sair);

        if((sairInteiro==0) || ((sairInteiro!=1) && (sairInteiro!=2)))
            printf("\nComando inválido!!!\n");

    }
    while((sairInteiro==0) || ((sairInteiro!=1) && (sairInteiro!=2)));

    return sairInteiro;

}//Fim sairDoLoop()

///Essa função recebe o ponteiro para o arquivo do funcionario.dat e verifica o último id, retornado o póximo válido
long IncrementaIdFun(FILE* fun){
    long proximoId,tamanho;

    fseek(fun,0,SEEK_END);
    tamanho=ftell(fun);
    proximoId=tamanho/sizeof(TFuncionario); /// Divide o tamanho do arquivo pelo tamanho da struct, conseguindo assim
                                            /// o número de registro
    return ++proximoId;

}//fim IncrementaIdFun()

///Essa função recebe o ponteiro para o arquivo do departamento.dat e verifica o último id, retornado o póximo válido
long IncrementaID(FILE* dep){
    long proximoId=0,tamanho;

    fseek(dep,0,SEEK_END);
    tamanho=ftell(dep);
    proximoId=tamanho/sizeof(TDepartamento); /// Divide o tamanho do arquivo pelo tamanho da struct, conseguindo assim
                                             /// o número de registro

    return ++proximoId;

}//fim incrementaId()

///Função usada para imprimir os dados de um funcionário incluindo seu departamento
void apresentaDadosDoFuncionario(FILE* fun, FILE *dep, int posicao){

    TDepartamento d;
    TFuncionario f;

    fseek(fun,posicao*sizeof(f),SEEK_SET);
    fread(&f,sizeof(f),1,fun);

    system("clear || cls");
    printf("\n=======================\n");
    printf("\nDADOS DO FUNCIONÁRIO\n");
    printf("\n=======================");

    printf("\nId: %li",f.id);
    printf("\nMatricula: %s",f.matricula);
    printf("\nNome: %s",f.nome);
    printf("\nData de nascimento: %s",f.dataNascimento );
    printf("\nCPF: %s",f.CPF);
    printf("\nId do departamento: %li",f.id_departamento);
    printf("\nSalario: %.2f",f.salario);
    printf("\nRua: %s",f.rua);
    // printf("\nNome departamento : %c",PesquisaDepartamentoID(dep,f.id_departamento));
    fseek(dep,PesquisaDepartamentoID(dep,f.id_departamento)*sizeof(d),SEEK_SET);
    fread(&d,sizeof(d),1,dep);

    printf("\nDepartamento: %s",d.nome);
    printf("\nCidade: %s",f.cidade);
    printf("\nEmail: %s",f.email);
    printf("\nBairro: %s",f.bairro);
    printf("\nComplemento: %s",f.complemento);
    printf("\nNumero: %u",f.Numero);
    printf("\nUF: %s",f.UF);
    printf("\nCEP: %s",f.CEP);
}//fim apresentaDadosDoFuncionario()

///Essa função retorna a data atual dosistema
void dataAtual(int *d,int *m,int *a){
    struct tm *local; /// struct da biblioteca
        time_t t;

        t = time(&t);
        local = localtime(&t);

        ///Obtem a hora do sistema.
        *m = local->tm_mon + 1;
        *a = local->tm_year + 1900;
        *d = local->tm_mday;

}

/// Pausa o programa e espera que o usuário aperte enter
void pause (){
    setbuf(stdin, NULL);
    printf("\n");
    printf("\nTecle ENTER para continuar...");
    getchar();
}
