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

//Função usada para imprimir os dados de um funcionário incluindo seu departamento
void apresentaDadosDoFuncionario(FILE* fun, FILE *dep, int posicao){

    TDepartamento d;
    TFuncionario f;

    fseek(fun,posicao*sizeof(f),SEEK_SET);
    fread(&f,sizeof(f),1,fun);

    printf("\nDados do Funcionario\n");
    printf("\n=======================\n");

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
    printf("\nemail: %s",f.email);
    printf("\nBairro: %s",f.bairro);
    printf("\nComplemento: %s",f.complemento);
    printf("\nNumero: %u",f.Numero);
    printf("\nUF: %s",f.UF);
    printf("\nCEP: %s",f.CEP);
}//fim apresentaDadosDoFuncionario()

//Essa função recebe o ponteiro para o arquivo do funcionario.dat e verifica o último id, retornado o póximo válido
long IncrementaIdFun(FILE* fun){
    long proximoId,tamanho;

    fseek(fun,0,SEEK_END);
    tamanho=ftell(fun);
    proximoId=tamanho/sizeof(TFuncionario);

    return ++proximoId;

}//fim IncrementaIdFun()

//Cadastra o funcionario e também faz um registro dos dados no historico do funcionario e o salario no hsalario
void CadastrarFuncionario(FILE*fun,FILE*dep,FILE*hsal,FILE*hfun){
    char matricula[10],dataNascimento[12],dataNascimento1[12],cpf[13],nomed[40],UF[4];
    int matexiste,cpfexiste,sair,testedata;
    long idexiste,pid;

    TFuncionario f;
    THistoricoFuncionario hf;
    THistoricoSalario hs;

    do{
        do{
            printf("\nForneça a matrícula: ");
            setbuf(stdin,NULL);
            fgets(matricula,10,stdin);
            setbuf(stdin,NULL);

            RetiraSequenciaDeEscape(matricula);

            matexiste=PesquisaMatricula(fun,matricula);
            printf("\n%d\n",matexiste);
            if(matexiste!=-1)
                printf("\nMatrícula existente!!!");
        }while(matexiste!=-1);

        strcpy(f.matricula,matricula);

        do{
            printf("\nForneça o nome do funcionário: ");
            setbuf(stdin,NULL);
            fgets(f.nome,60,stdin);
            setbuf(stdin,NULL);
        }while(strlen(f.nome) == 1);

        RetiraSequenciaDeEscape(f.nome);

        pid=IncrementaIdFun(fun);
        f.id=pid;
        hf.id_funcionario=pid;
        hs.id_funcionario=pid;

        do{
            printf("\nForneça a data de nascimento do funcionário: ");
            setbuf(stdin,NULL);
            fgets(dataNascimento,12,stdin);
            setbuf(stdin,NULL);

            RetiraSequenciaDeEscape(dataNascimento);
            strcpy(dataNascimento1,dataNascimento);
            testedata=verficaData(dataNascimento);

            if(testedata==0)
                printf("\nData inválida!!!");
        }while(testedata==0);

        printf("\n%s\n",dataNascimento);
        strcpy(f.dataNascimento,dataNascimento1);

        do{
            printf("\nForneça o cpf: ");
            setbuf(stdin,NULL);
            fgets(cpf,13,stdin);
            setbuf(stdin,NULL);

            RetiraSequenciaDeEscape(cpf);
            cpfexiste=VerificaCpf(fun,cpf);

            if(cpfexiste==0)
                printf("\nCpf inválido!!!");

        }while(cpfexiste==0);

        strcpy(f.CPF,cpf);

        setbuf(stdin,NULL);
        printf("\nForneça o nome do departamento desse funcionário: ");
        setbuf(stdin,NULL);
        fgets(nomed,40,stdin);
        setbuf(stdin,NULL);


        RetiraSequenciaDeEscape(nomed);

        if(VerificaArquivoVazio(dep)==1)//Verifica se existem departamentos cadastrados
            printf("\nNenhum departamento cadastrado!!!\n");
        else{
            idexiste=PesquisaDepartamentoNome(dep,nomed);

            if(idexiste==0)//verifica se existe o departamento informado e recebe seu id
                printf("\nDepartamento inexistente!!!\n");
            else{
                f.id_departamento=idexiste;
                hf.id_departamento=idexiste;

                printf("\nForneça o salario desse funcionário: ");
                scanf("%f",&f.salario);

                hs.salario=f.salario;

                printf("\nForneça a rua do funcionario: ");
                setbuf(stdin,NULL);
                fgets(f.rua,40,stdin);
                setbuf(stdin,NULL);

                RetiraSequenciaDeEscape(f.rua);

                printf("\nForneça o bairro do funcionario: ");
                setbuf(stdin,NULL);
                fgets(f.bairro,30,stdin);
                setbuf(stdin,NULL);

                RetiraSequenciaDeEscape(f.bairro);

                printf("\nForneça o numero da casa do funcionario: ");
                scanf("%ui",&f.Numero);

                printf("\nForneça o complemento da casa do funcionario: ");
                setbuf(stdin,NULL);
                fgets(f.complemento,30,stdin);
                setbuf(stdin,NULL);

                RetiraSequenciaDeEscape(f.complemento);

                printf("\nForneça a cidade do funcionario: ");
                setbuf(stdin,NULL);
                fgets(f.cidade,40,stdin);
                setbuf(stdin,NULL);

                RetiraSequenciaDeEscape(f.cidade);

                printf("\nForneça o UF do funcionario: ");
                setbuf(stdin,NULL);
                fgets(UF,4,stdin);
                setbuf(stdin,NULL);

                RetiraSequenciaDeEscape(UF);

                strcpy(f.UF,UF);

                printf("\nForneça o CEP do funcionario: ");
                setbuf(stdin,NULL);
                fgets(f.CEP,9,stdin);
                setbuf(stdin,NULL);

                RetiraSequenciaDeEscape(f.CEP);

                printf("\nForneça o email do funcionario: ");
                setbuf(stdin,NULL);
                fgets(f.email,40,stdin);
                setbuf(stdin,NULL);

                RetiraSequenciaDeEscape(f.email);

                fseek(fun,0,SEEK_END);
                fwrite(&f,sizeof(f),1,fun);

                fseek(hfun,0,SEEK_END);
                fwrite(&hf,sizeof(hf),1,hfun);

                fseek(hsal,0,SEEK_END);
                fwrite(&hs,sizeof(hs),1,hsal);
            }
        }

        printf("\nDeseja sair?\n");
        printf("\n1-Sim     2-Não\n");
        scanf("%d",&sair);


    }while(sair!=1);
}//fim CadastrarFuncionario()

//Consulta um funcionario , caso exista seus dados são printados na tela, caso contrário retorna uma mensagem de funcionario inexistente
void ConsultaFuncionarioporMatricula(FILE*fun,FILE*dep){
    int posicao,sair;
    char matricula[10];

    if(VerificaArquivoVazio(fun)==1)//Verifica se existem funcionarios cadastrados
        printf("\nNenhum funcionário cadastrado!!!");
    else{
        do{
            printf("\nForneça a matrícula: ");
            setbuf(stdin,NULL);
            fgets(matricula,10,stdin);
            setbuf(stdin,NULL);

            RetiraSequenciaDeEscape(matricula);

            posicao=PesquisaMatricula(fun,matricula);

            if(posicao==-1)//Verifica se o funcionario existe
                printf("\nFuncionário nao encontrado!!!");
            else{

                apresentaDadosDoFuncionario(fun,dep,posicao);


            }

            printf("\nDeseja sair?\n");
            printf("\n1-Sim     2-Não\n");
            scanf("%d",&sair);

        }while(sair!=1);
    }
}//fim ConsultaFuncionarioporMatricula()

//Mostra a matrícula, o nome e o salário de um funcionário
void FolhaDePagamento(FILE*fun){

    int posicao,i,sair;
    char matricula[10];

    TFuncionario f;

    if(VerificaArquivoVazio(fun)==1)
        printf("\nNenhum funcionario cadastrado!!!");
    else{
        do{
        printf("\nForneça a matrícula: ");
        setbuf(stdin,NULL);
        fgets(matricula,10,stdin);
        setbuf(stdin,NULL);

        RetiraSequenciaDeEscape(matricula);

        posicao=PesquisaMatricula(fun,matricula);

        if(posicao==-1)
            printf("\nFuncionário nao encontrado!!!");
        else{
                fseek(fun,posicao*sizeof(f),SEEK_SET);
                fread(&f,sizeof(f),1,fun);

                printf("\n======================\n");
                printf("    Folha de Pagamento    ");
                printf("\n======================\n");

                printf("\nMatricula: ");
                for(i=0;i<strlen(f.matricula);i++)
                    printf("%c",f.matricula[i]);

                printf("\nNome: ");
                for(i=0;i<strlen(f.nome);i++)
                    printf("%c",f.nome[i]);

                printf("\nSalario: %.2f\n",f.salario);

            }

            printf("\nDeseja sair?\n");
            printf("\n1-Sim     2-Não\n");
            scanf("%d",&sair);

        }while(sair!=1);
    }
}//fim FolhaDePagamento()

//Imprime os dados dos funcionários de um determinado departamento
void RelatorioFuncionariosPorDepartamento(FILE *fun,FILE *dep){
    int cont;

    TFuncionario f;
    TDepartamento d;



    if(VerificaArquivoVazio(dep)==1)
        printf("\nNenhum departamento cadastrado!!!");
    else{

        rewind(dep);
        while(fread(&d,sizeof(d),1,dep)){
            printf("\n");
            printf("\n");
            printf("\nCódigo do Departamento: %li",d.id);
            printf("\nNome do departamento: %s",d.nome);
            printf("\n");
            cont=0;
            rewind(fun);
            while(fread(&f,sizeof(f),1,fun)){
                if(d.id==f.id_departamento){
                    printf("\nMatrícula\t\t\tNome\t\t\tSalário\n");
                    printf("%s\t\t\t\t",f.matricula);
                    printf("%s ",f.nome);
                    printf("%.2f",f.salario);
                    cont++;
                }
            }
            printf("\n");
            printf("\nTotal da folha de Departamento: %d",cont);
            printf("\n--------------------------------------------\n");
        }

    }

}//fim RelatorioFuncionariosPorDepartamento()

//Altera Salario dos funcionarios cadasreados e faz registro no histórico de salário
void AlterarSalario(FILE*fun,FILE*hsal){

    char matricula[10];
    int matexiste,sair;
    float novosalario;

    TFuncionario f;
    THistoricoSalario hs;

    if(VerificaArquivoVazio(fun)==1)
        printf("\nNenhum funcionario cadastrado!!!");
    else{

    do{
        printf("\nForneça a matrícula do funcionario: ");
        setbuf(stdin,NULL);
        fgets(matricula,10,stdin);
        setbuf(stdin,NULL);

        RetiraSequenciaDeEscape(matricula);
        matexiste=PesquisaMatricula(fun,matricula);

        if(matexiste==-1)
            printf("\nFuncionario inexistente!!!");
        else{

                printf("\nForneça o novo salario: ");
                scanf("%f",&novosalario);

                fseek(fun,matexiste*sizeof(f),SEEK_SET);
                fread(&f, sizeof(f), 1, fun);
                f.salario=novosalario;
                hs.id_funcionario=f.id;
                fseek(fun,matexiste*sizeof(f),SEEK_SET);
                fwrite(&f,sizeof(f),1,fun);

                //printf("\nTeste\n");

                hs.salario=novosalario;

                fseek(hsal,0,SEEK_END);
                fwrite(&hs,sizeof(hs),1,hsal);

            }

            printf("\nDeseja sair?\n");
            printf("\n1-Sim     2-Não\n");
            scanf("%d",&sair);

        }while(sair!=1);
    }
}//fim AlterarSalario()

//Altera o departamento dos funcionarios cadasreados e também faz um registro dos dados no historico do funcionario
void AlterarDepartamento(FILE*fun,FILE*hfun,FILE*dep){

    char matricula[10],novoDepartamento[40];
    int matexiste,sair;
    long dexiste;

    TFuncionario f;
    THistoricoFuncionario hf;

    if(VerificaArquivoVazio(fun)==1)
        printf("\nNenhum funcionario cadastrado!!!");
    else{
        if(VerificaArquivoVazio(dep)==1)
            printf("\nNenhum departamento cadastrado!!!");
        else{
            do{
                printf("\nForneça a matrícula do funcionario: ");
                setbuf(stdin,NULL);
                fgets(matricula,10,stdin);
                setbuf(stdin,NULL);

                RetiraSequenciaDeEscape(matricula);
                matexiste=PesquisaMatricula(fun,matricula);

                if(matexiste==-1)
                    printf("\nFuncionario inexistente!!!");
                else{
                    printf("\nForneça o novo departamento: ");
                    setbuf(stdin,NULL);
                    fgets(novoDepartamento,40,stdin);
                    setbuf(stdin,NULL);
                        //scanf("%li",&novodepartamento);
                    RetiraSequenciaDeEscape(novoDepartamento);
                    dexiste=PesquisaDepartamentoNome(dep,novoDepartamento);

                    if(dexiste==0)
                        printf("\nDepartamento inexistente!!!");
                    else{

                        //posicao=PesquisaDepartamentoID(dep,dexiste);

                        fseek(fun,matexiste*sizeof(f),SEEK_SET);
                        fread(&f, sizeof(f), 1, fun);
                        f.id_departamento=dexiste;
                        hf.id_funcionario=f.id;
                       // id=f.id;
                        fseek(fun,matexiste*sizeof(f),SEEK_SET);
                        fwrite(&f,sizeof(f),1,fun);

                        hf.id_departamento=dexiste;

                        fseek(hfun,0,SEEK_END);
                        fwrite(&hf,sizeof(hf),1,hfun);
                    }

                }

                printf("\nDeseja sair?\n");
                printf("\n1-Sim     2-Não\n");
                scanf("%d",&sair);

            }while(sair!=1);
        }
    }
}//fim AlterarDepartamento()

/*Altera os dados de um funcionário  com determinada matrícula e também faz um registro dos dados no historico do funcionario e o
salario no historico de salario*/
void AlterarFuncionario(FILE*fun,FILE*dep,FILE*hsal,FILE*hfun){
    char matricula[10],dataNascimento[11],cpf[13],nomed[40],UF[4];
    int /*dataValida*/cpfexiste,sair,posicao;
    long idexiste;



    TFuncionario f;
    THistoricoFuncionario hf;
    THistoricoSalario hs;

    do{
        if(VerificaArquivoVazio(fun)==1)
            printf("\nNenhum funcionario cadastrado!!!");
        else{

            printf("\nForneça a matrícula:");
            setbuf(stdin,NULL);
            fgets(matricula,10,stdin);
            setbuf(stdin,NULL);

            RetiraSequenciaDeEscape(matricula);

            posicao=PesquisaMatricula(fun,matricula);

            if(posicao==-1)
                printf("\nFuncionário nao encontrado!!!");
            else{

                fseek(fun,posicao*sizeof(f),SEEK_SET);
                fread(&f,sizeof(f),1,fun);

                do{
                    printf("\nForneça o nome do funcionário: ");
                    setbuf(stdin,NULL);
                    fgets(f.nome,60,stdin);
                    setbuf(stdin,NULL);
                }while(strlen(f.nome) == 1);

                RetiraSequenciaDeEscape(f.nome);

                hf.id_funcionario=f.id;
                hs.id_funcionario=f.id;

                //Falata a função de verifica data
                //do{
                printf("\nForneça a data de nascimento do funcionário: ");
                setbuf(stdin,NULL);
                fgets(dataNascimento,11,stdin);
                setbuf(stdin,NULL);

                RetiraSequenciaDeEscape(dataNascimento);
                    //dataValida=VerificaData(dataNascimento);
                    //if(strcmp(dataNascimento,"20/06/1960")==0 || dataValida==0)
                      //  printf("\nData de nascimento inválida!!!");
                //}while(strcmp(dataNascimento,"20/06/1960")!=0 && dataValida!=0);
                strcpy(f.dataNascimento,dataNascimento);

                do{
                    printf("\nForneça o cpf: ");
                    setbuf(stdin,NULL);
                    fgets(cpf,13,stdin);
                    setbuf(stdin,NULL);
                    //printf("\n%d\n",strlen(cpf));
                    RetiraSequenciaDeEscape(cpf);
                    //printf("\n%d\n",strlen(cpf));
                    cpfexiste=VerificaCpf(fun,cpf);
                    printf("\n%d\n",cpfexiste);
                    if(cpfexiste==0)
                        printf("\nCpf inválido!!!");

                }while(cpfexiste==0);

                strcpy(f.CPF,cpf);

                setbuf(stdin,NULL);
                printf("\nForneça o nome do departamento desse funcionário: ");
                setbuf(stdin,NULL);
                fgets(nomed,40,stdin);
                setbuf(stdin,NULL);


                RetiraSequenciaDeEscape(nomed);

                if(VerificaArquivoVazio(dep)==1)//Verifica se existem departamentos cadastrados
                    printf("\nNenhum departamento cadastrado!!!\n");
                else{
                    idexiste=PesquisaDepartamentoNome(dep,nomed);

                    if(idexiste==0)//verifica se existe o departamento informado e recebe seu id
                        printf("\nDepartamento inexistente!!!\n");
                    else{

                        f.id_departamento=idexiste;
                        hf.id_departamento=idexiste;

                        printf("\nForneça o salario desse funcionário: ");
                        scanf("%f",&f.salario);

                        hs.salario=f.salario;

                        printf("\nForneça a rua do funcionario: ");
                        setbuf(stdin,NULL);
                        fgets(f.rua,40,stdin);
                        setbuf(stdin,NULL);

                        RetiraSequenciaDeEscape(f.rua);

                        printf("\nForneça o bairro do funcionario: ");
                        setbuf(stdin,NULL);
                        fgets(f.bairro,30,stdin);
                        setbuf(stdin,NULL);

                        RetiraSequenciaDeEscape(f.bairro);

                        printf("\nForneça o numero da casa do funcionario: ");
                        scanf("%ui",&f.Numero);

                        printf("\nForneça o complemento da casa do funcionario: ");
                        setbuf(stdin,NULL);
                        fgets(f.complemento,30,stdin);
                        setbuf(stdin,NULL);

                        RetiraSequenciaDeEscape(f.complemento);

                        printf("\nForneça a cidade do funcionario: ");
                        setbuf(stdin,NULL);
                        fgets(f.cidade,40,stdin);
                        setbuf(stdin,NULL);

                        RetiraSequenciaDeEscape(f.cidade);

                        printf("\nForneça o UF do funcionario: ");
                        setbuf(stdin,NULL);
                        fgets(UF,4,stdin);
                        setbuf(stdin,NULL);

                        RetiraSequenciaDeEscape(UF);

                        strcpy(f.UF,UF);

                        printf("\nForneça o CEP do funcionario: ");
                        setbuf(stdin,NULL);
                        fgets(f.CEP,9,stdin);
                        setbuf(stdin,NULL);

                        RetiraSequenciaDeEscape(f.CEP);

                        printf("\nForneça o email do funcionario: ");
                        setbuf(stdin,NULL);
                        fgets(f.email,40,stdin);
                        setbuf(stdin,NULL);

                        RetiraSequenciaDeEscape(f.email);

                        fseek(fun,posicao*sizeof(f),SEEK_SET);
                        fwrite(&f,sizeof(f),1,fun);

                        fseek(hfun,0,SEEK_END);
                        fwrite(&hf,sizeof(hf),1,hfun);

                        fseek(hsal,0,SEEK_END);
                        fwrite(&hs,sizeof(hs),1,hsal);
                    }
                }

            }

        }

        printf("\nDeseja sair?\n");
        printf("\n1-Sim     2-Não\n");
        scanf("%d",&sair);

    }while(sair!=1);
}//fim AlterarFuncionario()

//Imprime os dados do gerente de um determinado departamento
void RelatorioGerenteDeDepartamento(FILE *dep,FILE *fun){
    char sair[3],nome[30];
    long dexiste;
    int pos,posicaodep;

    TDepartamento d;
    TFuncionario f;

    do{
    if(VerificaArquivoVazio(dep)==1)
        printf("\nNenhum departamento cadastrado!!!");
    else{

        printf("\nForneça o nome do departamento: ");
        setbuf(stdin,NULL);
        fgets(nome,30,stdin);
        setbuf(stdin,NULL);

        RetiraSequenciaDeEscape(nome);

        dexiste=PesquisaDepartamentoNome(dep,nome);
        printf("%li",dexiste);
        if(dexiste==0)
            printf("\nDepartamento não encontrado!!!");
        else{
            posicaodep=PesquisaDepartamentoID(dep,dexiste);
            printf("%d",posicaodep);
            fseek(dep,posicaodep*sizeof(d),SEEK_SET);
            fread(&d,sizeof(d),1,dep);
            printf("%li",d.id_gerente);
            if(d.id_gerente==-1)
                printf("\nNenhum funcionário cadastrado como gerente!!!");
            else{

                pos=PesquisaFunID(fun,d.id_gerente);
                apresentaDadosDoFuncionario(fun,dep,pos);
            }

        }

    }
    printf("\nDeseja sair?\n");
    printf("\n1-Sim     2-Não\n");
    setbuf(stdin,NULL);
    fgets(sair,3,stdin);
    setbuf(stdin,NULL);

    }while(sair[0]!='1');
}//fim RelatorioGerenteDeDepartamento()
