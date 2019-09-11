#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include <time.h>
#include"departamento.h"
#include"funcionario.h"
#include"historicoDepartamento.h"
#include"historicoFuncionario.h"
#include"historicoSalario.h"
#include"funcoesPesquisa.h"
#include"funcoesVerificacoes.h"
#include "funcoesAuxiliares.h"


void imprimir2(FILE* hfun){
    THistoricoDepartamento hf;

    fseek(hfun,0,SEEK_END);//Usa para ver se tem dados no arquivo ou não
    if(ftell(hfun)<=0){
        //printf("%d",ftell(dep));
        printf("\nSem dados no arquio");
    }
    else{
        rewind(hfun);
        while(fread(&hf, sizeof(hf), 1, hfun)){
            printf("\n---------------------\n");

            printf("\n%li",hf.id_departamento);
            printf("\n%li",hf.id_gerente);
            printf("\n%s",hf.data);


        }
    }
}

void imprimir3(FILE* hfun){
    THistoricoSalario hf;

    fseek(hfun,0,SEEK_END);//Usa para ver se tem dados no arquivo ou não
    if(ftell(hfun)<=0){
        //printf("%d",ftell(dep));
        printf("\nSem dados no arquio");
    }
    else{
        rewind(hfun);
        while(fread(&hf, sizeof(hf), 1, hfun)){
            printf("\n---------------------\n");

            printf("\n%li",hf.id_funcionario);
            printf("\n%hu",hf.mes);
            printf("\n%hu",hf.ano);
            printf("\n%f",hf.salario);


        }
    }
}

void imprimir4(FILE* hfun){
    THistoricoFuncionario hf;

    fseek(hfun,0,SEEK_END);//Usa para ver se tem dados no arquivo ou não
    if(ftell(hfun)<=0){
        //printf("%d",ftell(dep));
        printf("\nSem dados no arquio");
    }
    else{
        rewind(hfun);
        while(fread(&hf, sizeof(hf), 1, hfun)){
            printf("\n---------------------\n");

            printf("\n%s",hf.data);
            printf("\n%li",hf.id_departamento);
            printf("\n%li",hf.id_funcionario);


        }
    }
}

/// Imprimi todos os dados dos departamentos cadastrados
void imprimir(FILE*dep){

    int i,j;
    TDepartamento dp;

    fseek(dep,0,SEEK_END);//Usa para ver se tem dados no arquivo ou não
    if(ftell(dep)<=0){
        //printf("%d",ftell(dep));
        printf("\nSem dados no arquio");
    }
    else{
        system("clear");
        rewind(dep);
        while(fread(&dp, sizeof(dp), 1, dep)){
            printf("\nDados::::::::::::::::::::::::::\n");
            printf("\n%li\n",dp.id);
            for(i=0;i<strlen(dp.nome);i++)
                printf("%c",dp.nome[i]);
            printf("\n%li\n",dp.id_gerente);
            for(j=0;j<strlen(dp.sigla);j++)
               printf("%c",dp.sigla[j]);
            printf("\n%hu\n",dp.Ramal);
        }
    }
    pause();
}//fim imprimir()

///cadastra os dados no arquivo departamento.dat
void CadastraDepartamento(FILE*dep,FILE*hdep){

    int sair,m,a,dia;
    char ramal[50],nomeDepartamento[40],dataAt[12];
    unsigned short int ramalnumero;
    long nomeExiste;

    TDepartamento d;
    THistoricoDepartamento hd;

    do{
        system("clear || cls");
        printf("\n================================\n");
        printf("\nFORNEÇA OS DADOS DO DEPARTAMENTO\n");
        printf("\n================================\n");
        do{

            printf("\nForneça o nome do departamento: ");
            setbuf(stdin,NULL);
            fgets(nomeDepartamento,40,stdin);
            setbuf(stdin,NULL);

            RetiraSequenciaDeEscape(nomeDepartamento);

            nomeExiste=PesquisaDepartamentoNome(dep,nomeDepartamento);

            if(nomeExiste!=0)
                printf("\nNome existente!!!\n");

        }while((strlen(nomeDepartamento) == 0) || (nomeExiste!=0));//verifica o tamanho enquanto n for maior que 1 ele faz a pergunta novamente


        strcpy(d.nome,nomeDepartamento);

        printf("\nForneça a sigla do departamento: ");
        setbuf(stdin,NULL);
        fgets(d.sigla,10,stdin);
        setbuf(stdin,NULL);

        RetiraSequenciaDeEscape(d.sigla);


        do{
            printf("\nForneça o Ramal: ");
            setbuf(stdin,NULL);
            fgets(ramal,50,stdin);
            setbuf(stdin,NULL);

            RetiraSequenciaDeEscape(ramal);
            ramalnumero=atoi(ramal);

            if(atoi(ramal)==0)
                printf("\nO ramal deve ser um número!!!\n");
        }while(atoi(ramal)==0);

        d.Ramal=ramalnumero;
        d.id=IncrementaID(dep);

        d.id_gerente=-1; /// o valor -1 é o default


        dataAtual(&dia,&m,&a);

        sprintf(dataAt,"%d/%d/%d",dia,m,a);

        RetiraSequenciaDeEscape(dataAt);

        strcpy(hd.data,dataAt);

        fseek(dep,0,SEEK_END);
        fwrite(&d,sizeof(d),1,dep);


        hd.id_departamento=d.id;
        hd.id_gerente=d.id_gerente;


        fseek(hdep,0,SEEK_END);
        fwrite(&hd,sizeof(hd),1,hdep);

        fflush(dep);
        fflush(hdep);

       sair=sairDoLoop();

    }while(sair!=1);

}//fim cadastraDepartamento()

///Altera o gerente no arquivo departamento.dat e no historicodepartamento.dat, isso se o novo id n for um id existente
void AlterarGerente(FILE*dep,FILE*fun,FILE*hdep){

    int posicao,posicaoNovoGerente,sair,dia,mes,ano;
    long idDepartamento;
    char nomeDepartamento[40],matriculaDoNovoGerente[10],dataAt[12];

    TDepartamento d;
    TFuncionario f;
    THistoricoDepartamento hd;

    do{
        if(VerificaArquivoVazio(dep)==1)//verifica se o arquivo está vazio
            printf("\nNenhum departamento cadastrado\n");
        else{
            system("clear || cls");
            printf("\n================================\n");
            printf("\nFORNEÇA OS DADOS DO NOVO GERENTE\n");
            printf("\n================================\n");

            printf("\nForneça o nome do departamento: ");
            setbuf(stdin,NULL);
            fgets(nomeDepartamento,40,stdin);
            setbuf(stdin,NULL);

            RetiraSequenciaDeEscape(nomeDepartamento);

            idDepartamento=PesquisaDepartamentoNome(dep,nomeDepartamento);


            if(idDepartamento==0)
                printf("\nDepartamento não encontrado!!!\n");
            else{

                posicao=PesquisaDepartamentoID(dep,idDepartamento);

                fseek(dep,posicao*sizeof(d),SEEK_SET);
                fread(&d,sizeof(d),1,dep);


                printf("\nForneça a matrícula do novo gerente: ");
                setbuf(stdin,NULL);
                fgets(matriculaDoNovoGerente,10,stdin);
                setbuf(stdin,NULL);

                if(VerificaArquivoVazio(fun)==1)
                    printf("\nNenhum funcionário cadastrado!!!");
                else{

                    RetiraSequenciaDeEscape(matriculaDoNovoGerente);

                    posicaoNovoGerente=PesquisaMatricula(fun,matriculaDoNovoGerente);

                    if(posicaoNovoGerente==-1)
                        printf("\nNenhum funcionário com essa matrícula cadastrado\n");
                    else{

                        fseek(fun,posicaoNovoGerente*sizeof(f),SEEK_SET);
                        fread(&f,sizeof(f),1,fun);
                        printf("\nnovo gerente: %li",f.id);
                        printf("\nnovo gerente: %li",d.id_gerente);
                        if(f.id!=d.id_gerente){
                            dataAtual(&dia,&mes,&ano);

                            sprintf(dataAt,"%d/%d/%d",dia,mes,ano);

                            RetiraSequenciaDeEscape(dataAt);

                            strcpy(hd.data,dataAt);

                            d.id_gerente=f.id;
                            hd.id_gerente=f.id;
                            hd.id_departamento=idDepartamento;

                            fseek(dep,posicao*sizeof(d),SEEK_SET);
                            fwrite(&d,sizeof(d),1,dep);

                            fseek(hdep,0,SEEK_END);
                            fwrite(&hd,sizeof(hd),1,hdep);

                            fflush(dep);
                            fflush(hdep);
                        }
                        else
                            printf("\nEste é o gerente atual!!!");
                    }
                }
            }

        }

        sair=sairDoLoop();

    }while(sair!=1);
}//fim AlterarGerente()
