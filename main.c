#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <ctype.h>
#include"departamento.h"
#include"funcionario.h"
#include "funcoesAuxiliares.h"
#include "funcoesVerificacoes.h"


void menu(FILE *funcionario,FILE *departamento,FILE *hfuncionario,FILE *hdepartamento,FILE *hsalario){
    int i;
    char opcao[10],opcao1[10],opcao2[10],opcao3[10],opcao4[10];

    do{

        system("clear || cls");//printf("\e[H\e[2J");
        for(i=0;i<2;i++)
            printf("\n=======================================================");
        printf("\n====================== Opções =========================");
        for(i=0;i<2;i++)
            printf("\n=======================================================");

        printf("\n");
        printf("\nEscolha uma opção: \n");
        printf("\n[1] Cadastrar    \n[2] Consultar    \n[3] Alterar      \n[4] relatório      \n[5] Sair\n");
        printf("\n=> ");
        setbuf(stdin,NULL);
        fgets(opcao,10,stdin);
        setbuf(stdin,NULL);

        if(verificaDigito(opcao)==0){
            printf("\nComando incorreto!!!!\n");
            pause();
        }
        else{
            switch (atoi(opcao)){
            case 1:
                do{
                    system("clear || cls");
                    for(i=0;i<2;i++)
                        printf("\n=======================================================");
                    printf("\n====================== cadastro =======================");
                    for(i=0;i<2;i++)
                        printf("\n=======================================================");

                    printf("\n");
                    printf("\nEscolha uma opção: \n");
                    printf("\n[1] Cadastrar funcionário     \n[2] Cadastrar departamento      \n[3] Sair\n");
                    printf("\n=> ");
                    setbuf(stdin,NULL);
                    fgets(opcao1,10,stdin);
                    setbuf(stdin,NULL);

                    if(verificaDigito(opcao1)==0){
                        printf("\nComando incorreto!!!!\n");
                        pause();
                    }
                    else{
                        switch (atoi(opcao1)){
                        case 1:
                        CadastrarFuncionario(funcionario,departamento,hsalario,hfuncionario);
                        break;

                        case 2:
                        CadastraDepartamento(departamento,hdepartamento);
                        break;

                        case 3:
                        break;

                        default:
                            printf("\nComando invalido!!!\n");
                            pause();
                        }
                    }
                }while(atoi(opcao1)!=3);

            break;

            case 2:
                do{
                    system("clear || cls");
                    for(i=0;i<2;i++)
                        printf("\n=======================================================");
                    printf("\n====================== Consulta =======================");
                    for(i=0;i<2;i++)
                        printf("\n=======================================================");

                    printf("\n");
                    printf("\nEscolha uma opção: \n");
                    printf("\n[1] Consultar funcionário     \n[2] Consultar departamento      \n[3] Sair\n");
                    printf("\n=> ");
                    setbuf(stdin,NULL);
                    fgets(opcao2,10,stdin);
                    setbuf(stdin,NULL);

                    if(verificaDigito(opcao2)==0){
                        printf("\nComando incorreto!!!!\n");
                        pause();
                    }
                    else{
                        switch (atoi(opcao2)){
                        case 1:
                        ConsultaFuncionarioporMatricula(funcionario,departamento);
                        break;

                        case 2:
                        imprimir(departamento);
                        break;

                        case 3:
                        break;

                        default:
                            printf("\nComando invalido!!!\n");
                            pause();
                        }
                    }
                }while(atoi(opcao2)!=3);
            break;

            case 3:
                do{
                    system("clear || cls");
                    for(i=0;i<2;i++)
                        printf("\n=======================================================");
                    printf("\n====================== Alterar ========================");
                    for(i=0;i<2;i++)
                        printf("\n=======================================================");

                    printf("\n");
                    printf("\nEscolha uma opção: \n");
                    printf("\n[1] Alterar funcionário     \n[2] Alterar departamento do funcionário      \n[3] Alterar gerente do funcionário");
                    printf("\n[4] Alterar salário de um funcionário      \n[5] Sair\n");
                    printf("\n=> ");
                    setbuf(stdin,NULL);
                    fgets(opcao3,10,stdin);
                    setbuf(stdin,NULL);

                    if(verificaDigito(opcao3)==0){
                        printf("\nComando incorreto!!!!\n");
                        pause();
                    }
                    else{
                        switch (atoi(opcao3)){
                        case 1:
                        AlterarFuncionario(funcionario,departamento,hsalario,hfuncionario);
                        break;

                        case 2:
                        AlterarDepartamento(funcionario,hfuncionario,departamento);
                        break;

                        case 3:
                        AlterarGerente(departamento,funcionario,hdepartamento);
                        break;

                        case 4:
                        AlterarSalario(funcionario,hsalario);
                        break;

                        case 5:
                        break;

                        default:
                            printf("\nComando invalido!!!\n");
                            pause();
                        }
                    }
                }while(atoi(opcao3)!=5);
            break;

            case 4:
                do{
                    system("clear || cls");
                    for(i=0;i<2;i++)
                        printf("\n=======================================================");
                    printf("\n====================== Relatório ======================");
                    for(i=0;i<2;i++)
                        printf("\n=======================================================");

                    printf("\n");
                    printf("\nEscolha uma opção: \n");
                    printf("\n[1] Folha de pagamento     \n[2] Relatório de funcionário por departamento      \n[3] Histórico de salário");
                    printf("\n[4] Gerentes de um departamento      \n[5] Sair\n");
                    printf("\n=> ");
                    setbuf(stdin,NULL);
                    fgets(opcao4,10,stdin);
                    setbuf(stdin,NULL);


                    if(verificaDigito(opcao4)==0){
                        printf("\nComando incorreto!!!!\n");
                        pause();
                    }
                    else{
                        switch (atoi(opcao4)){
                        case 1:
                        FolhaDePagamento(funcionario);
                        break;

                        case 2:
                        RelatorioFuncionariosPorDepartamento(funcionario,departamento);
                        break;

                        case 3:
                        historicoDeSalario(hsalario,funcionario);
                        break;

                        case 4:
                        RelatorioGerenteDeDepartamento(departamento,funcionario,hdepartamento);
                        break;

                        case 5:
                        break;

                        default:
                            printf("\nComando invalido!!!\n");
                            pause();
                        }
                    }
                }while(atoi(opcao4)!=5);
            break;

            case 5:
            break;

            default:
                printf("\nComando invalido!!!\n");
                pause();
            }
        }
    }while(atoi(opcao)!=5);
}

void iniciar(){
    setlocale(LC_CTYPE,"");

    FILE *funcionario,*departamento,*hfuncionario,*hdepartamento,*hsalario;

    funcionario=fopen("Funcionario.dat", "rb+");
    if(funcionario==NULL)
        funcionario=fopen("Funcionario.dat", "wb+");

    departamento=fopen("Departamento.dat", "rb+");
    if(departamento==NULL)
        departamento=fopen("Departamento.dat", "wb+");

    hfuncionario=fopen("HistoricoFuncionario.dat", "rb+");
    if(hfuncionario==NULL)
        hfuncionario=fopen("HistoricoFuncionario.dat", "wb+");

    hdepartamento=fopen("HistoricoDepartamento.dat", "rb+");
    if(hdepartamento==NULL)
        hdepartamento=fopen("HistoricoDepartamento.dat", "wb+");

    hsalario=fopen("HistoricoSalario.dat", "rb+");
    if(hsalario==NULL)
        hsalario=fopen("HistoricoSalario.dat", "wb+");

    menu(funcionario,departamento,hfuncionario,hdepartamento,hsalario);

    fclose(funcionario);
    fclose(departamento);
    fclose(hfuncionario);
    fclose(hsalario);
    fclose(hdepartamento);

}

int main(){
    iniciar();
    return 0;
}
