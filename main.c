#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <ctype.h>
#include"Departamento.h"
#include"Funcionario.h"
#include"HistoricoDepartamento.h"
#include"HistoricoFuncionario.h"
#include"HistoricoSalario.h"
#include "funcoesAuxiliares.h"

void menu(FILE *funcionario,FILE *departamento,FILE *hfuncionario,FILE *hdepartamento,FILE *hsalario){
    int i;
    char opcao[3],opcao1[3],opcao2[3],opcao3[3],opcao4[3];

    do{
        //system("clear");//printf("\e[H\e[2J");
        for(i=0;i<2;i++)
            printf("\n=======================================================");
        printf("\n====================== Opções =========================");
        for(i=0;i<2;i++)
            printf("\n=======================================================");

        printf("\n");
        printf("\nEscolha uma opção: \n");
        printf("\n1-Cadastrar    \n2-Consultar    \n3-Alterar      \n4-relatorio      \n5-Sair\n");
        printf("\n=> ");
        setbuf(stdin,NULL);
        fgets(opcao,3,stdin);
        setbuf(stdin,NULL);
        flushIn();

        if(isdigit(opcao[0])==0)
            printf("\nComando incorreto!!!!\n");
        else{
            switch (opcao[0]){
            case '1':
                do{
                    //system("clear");
                    for(i=0;i<2;i++)
                        printf("\n=======================================================");
                    printf("\n====================== cadastro =========================");
                    for(i=0;i<2;i++)
                        printf("\n=======================================================");

                    printf("\n");
                    printf("\nEscolha uma opção: \n");
                    printf("\n1-Cadastrar funcionário     \n2-Cadastrar departamento      \n3-Sair\n");
                    printf("\n=> ");
                    setbuf(stdin,NULL);
                    fgets(opcao1,3,stdin);
                    setbuf(stdin,NULL);
                    flushIn();

                    if(isdigit(opcao1[0])==0)
                        printf("\nComando incorreto!!!!\n");
                    else{
                        switch (opcao1[0]){
                        case '1':
                        CadastrarFuncionario(funcionario,departamento,hsalario,hfuncionario);
                        break;

                        case '2':
                        CadastraDepartamento(departamento,hdepartamento);
                        break;

                        case '3':
                        break;

                        default:
                            printf("\nComando invalido!!!\n");
                        }
                    }
                }while(atoi(opcao1)!=3);

            break;

            case '2':
                do{
                    //system("clear");
                    for(i=0;i<2;i++)
                        printf("\n=======================================================");
                    printf("\n====================== Consulta =======================");
                    for(i=0;i<2;i++)
                        printf("\n=======================================================");

                    printf("\n");
                    printf("\nEscolha uma opção: \n");
                    printf("\n1-Consultar funcionário     \n2-Consultar departamento      \n3-Sair\n");
                    printf("\n=> ");
                    setbuf(stdin,NULL);
                    fgets(opcao2,3,stdin);
                    setbuf(stdin,NULL);
                    flushIn();

                    if(isdigit(opcao2[0])==0)
                        printf("\nComando incorreto!!!!\n");
                    else{
                        switch (opcao2[0]){
                        case '1':
                        ConsultaFuncionarioporMatricula(funcionario,departamento);
                        break;

                        case '2':
                        imprimir(departamento);
                        break;

                        case '3':
                        imprimir2(hdepartamento);
                        break;

                        case '4':
                        imprimir3(hsalario);
                        break;

                        case '5':
                        imprimir4(hfuncionario);
                        break;

                        case '6':
                        break;

                        default:
                            printf("\nComando invalido!!!\n");
                        }
                    }
                }while(opcao2[0]!='6');
            break;

            case '3':
                do{
                    //system("clear");
                    for(i=0;i<2;i++)
                        printf("\n=======================================================");
                    printf("\n====================== Alterar ========================");
                    for(i=0;i<2;i++)
                        printf("\n=======================================================");

                    printf("\n");
                    printf("\nEscolha uma opção: \n");
                    printf("\n1-Alterar funcionário     \n2-Alterar departamento do funcionário      \n3-Alterar gerente do funcionário");
                    printf("\n4-Alterar salário de um funcionário      \n5-Sair\n");
                    printf("\n=> ");
                    setbuf(stdin,NULL);
                    fgets(opcao3,3,stdin);
                    setbuf(stdin,NULL);
                    flushIn();

                    if(isdigit(opcao3[0])==0)
                        printf("\nComando incorreto!!!!\n");
                    else{
                        switch (opcao3[0]){
                        case '1':
                        AlterarFuncionario(funcionario,departamento,hsalario,hfuncionario);
                        break;

                        case '2':
                        AlterarDepartamento(funcionario,hfuncionario,departamento);
                        break;

                        case '3':
                        AlterarGerente(departamento,funcionario,hdepartamento);
                        break;

                        case '4':
                        AlterarSalario(funcionario,hsalario);
                        break;

                        case '5':
                        break;

                        default:
                            printf("\nComando invalido!!!\n");
                        }
                    }
                }while(opcao3[0]!='5');
            break;

            case '4':
                do{
                    //system("clear");
                    for(i=0;i<2;i++)
                        printf("\n=======================================================");
                    printf("\n====================== Relatório ======================");
                    for(i=0;i<2;i++)
                        printf("\n=======================================================");

                    printf("\n");
                    printf("\nEscolha uma opção: \n");
                    printf("\n1-Folhs de pagamento     \n2-Relató de funcionário por departamento      \n3-Histórico de salário");
                    printf("\n4-Gerentes de um departamento      \n5-Sair\n");
                    printf("\n=> ");
                    setbuf(stdin,NULL);
                    fgets(opcao4,3,stdin);
                    setbuf(stdin,NULL);
                    flushIn();

                    if(isdigit(opcao4[0])==0)
                        printf("\nComando incorreto!!!!\n");
                    else{
                        switch (opcao4[0]){
                        case '1':
                        FolhaDePagamento(funcionario);
                        break;

                        case '2':
                        RelatorioFuncionariosPorDepartamento(funcionario,departamento);
                        break;

                        case '3':
                        historicoDeSalario(hsalario,funcionario);
                        break;

                        case '4':
                        RelatorioGerenteDeDepartamento(departamento,funcionario);
                        break;

                        case '5':
                        break;

                        default:
                            printf("\nComando invalido!!!\n");
                        }
                    }
                }while(opcao4[0]!='5');
            break;

            case '5':
            break;

            default:
                printf("\nComando invalido!!!\n");
            }
        }
    }while(opcao[0]!='5');
}

void iniciar(){
    setlocale(LC_CTYPE,"");

    FILE *funcionario,*departamento,*hfuncionario,*hdepartamento,*hsalario;

    funcionario=fopen("funcionario.dat", "rb+");
    if(funcionario==NULL)
        funcionario=fopen("funcionario.dat", "wb+");

    departamento=fopen("departamento.dat", "rb+");
    if(departamento==NULL)
        departamento=fopen("departamento.dat", "wb+");

    hfuncionario=fopen("historicofuncionario.dat", "rb+");
    if(hfuncionario==NULL)
        hfuncionario=fopen("historicofuncionario.dat", "wb+");

    hdepartamento=fopen("historicodepartamento.dat", "rb+");
    if(hdepartamento==NULL)
        hdepartamento=fopen("historicodepartamento.dat", "wb+");

    hsalario=fopen("historicosalario.dat", "rb+");
    if(hsalario==NULL)
        hsalario=fopen("historicosalario.dat", "wb+");

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

