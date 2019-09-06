#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include<ctype.h>
#include"Departamento.h"
#include"Funcionario.h"
#include"HistoricoFuncionario.h"
#include"HistoricoSalario.h"
#include"funcoesPesquisa.h"
#include"funcoesVerificacao.h"
#include "funcoesAuxiliares.h"


//Cadastra o funcionario e também faz um registro dos dados no historico do funcionario e o salario no hsalario
void CadastrarFuncionario(FILE*fun,FILE*dep,FILE*hsal,FILE*hfun){
    char matricula[10],dataNascimento[12],dataNascimento1[12],cpf[13],nomed[40],UF[4],dataAt[11],nomeFuncionario[60],rua[40],email[40],CEP[10],cidade[40],complemento[30], bairro[30];
    int matexiste,cpfexiste,sair,testedata,dia,mes,ano;
    long idexiste,pid;;

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
            if(matexiste!=-1)
                printf("\nMatrícula existente!!!\n");
        }while(matexiste!=-1);

        strcpy(f.matricula,matricula);

        do{
            printf("\nForneça o nome do funcionário: ");
            setbuf(stdin,NULL);
            fgets(nomeFuncionario,60,stdin);
            setbuf(stdin,NULL);

            RetiraSequenciaDeEscape(nomeFuncionario);
        }while(strlen(nomeFuncionario) == 0);

        strcpy(f.nome,nomeFuncionario);


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

        strcpy(f.dataNascimento,dataNascimento1);

        do{
            printf("\nForneça o cpf: ");
            setbuf(stdin,NULL);
            fgets(cpf,13,stdin);
            setbuf(stdin,NULL);

            RetiraSequenciaDeEscape(cpf);
            printf("%d",strlen(cpf));
            cpfexiste=VerificaCpf(fun,cpf);

            if(cpfexiste==0)
                printf("\nCpf inválido!!!\n");

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
                fgets(rua,40,stdin);
                setbuf(stdin,NULL);


                RetiraSequenciaDeEscape(rua);

                strcpy(f.rua,rua);

                printf("\nForneça o bairro do funcionario: ");
                setbuf(stdin,NULL);
                fgets(bairro,30,stdin);


                RetiraSequenciaDeEscape(bairro);

                strcpy(f.bairro,bairro);

                printf("\nForneça o numero da casa do funcionario: ");
                scanf("%ui",&f.Numero);

                printf("\nForneça o complemento da casa do funcionario: ");
                setbuf(stdin,NULL);
                fgets(complemento,30,stdin);
                setbuf(stdin,NULL);

                RetiraSequenciaDeEscape(complemento);

                strcpy(f.complemento,complemento);

                printf("\nForneça a cidade do funcionario: ");
                setbuf(stdin,NULL);
                fgets(cidade,40,stdin);
                setbuf(stdin,NULL);


                RetiraSequenciaDeEscape(cidade);
                strcpy(f.cidade,cidade);

                printf("\nForneça o UF do funcionario: ");
                setbuf(stdin,NULL);
                fgets(UF,4,stdin);
                setbuf(stdin,NULL);

                RetiraSequenciaDeEscape(UF);

                strcpy(f.UF,UF);

                printf("\nForneça o CEP do funcionario: ");
                setbuf(stdin,NULL);
                fgets(CEP,10,stdin);
                setbuf(stdin,NULL);

                RetiraSequenciaDeEscape(CEP);
                strcpy(f.CEP,CEP);

                printf("\nForneça o email do funcionario: ");
                setbuf(stdin,NULL);
                fgets(email,40,stdin);
                setbuf(stdin,NULL);

                RetiraSequenciaDeEscape(f.email);
                strcpy(f.email,email);

                dataAtual(&dia,&mes,&ano);

                sprintf(dataAt,"%d/%d/%d",dia,mes,ano);

                RetiraSequenciaDeEscape(dataAt);

                strcpy(hf.data,dataAt);

                hs.mes=mes;
                hs.ano=ano;

                fseek(fun,0,SEEK_END);
                fwrite(&f,sizeof(f),1,fun);

                fseek(hfun,0,SEEK_END);
                fwrite(&hf,sizeof(hf),1,hfun);

                fseek(hsal,0,SEEK_END);
                fwrite(&hs,sizeof(hs),1,hsal);

                fflush(fun);
                fflush(hsal);
                fflush(hfun);
            }
        }


        sair=sairDoLoop();
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
                printf("\nFuncionário nao encontrado!!!\n");
            else{

                apresentaDadosDoFuncionario(fun,dep,posicao);


            }

            sair=sairDoLoop();
        }while(sair!=1);
    }
}//fim ConsultaFuncionarioporMatricula()

//Mostra a matrícula, o nome e o salário de um funcionário
void FolhaDePagamento(FILE*fun){

    int posicao,i,sair;
    char matricula[10];

    TFuncionario f;

    if(VerificaArquivoVazio(fun)==1)
        printf("\nNenhum funcionario cadastrado!!!\n");
    else{
        do{
        printf("\nForneça a matrícula: ");
        setbuf(stdin,NULL);
        fgets(matricula,10,stdin);
        setbuf(stdin,NULL);

        RetiraSequenciaDeEscape(matricula);

        posicao=PesquisaMatricula(fun,matricula);

        if(posicao==-1)
            printf("\nFuncionário nao encontrado!!!\n");
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

            sair=sairDoLoop();

        }while(sair!=1);
    }
}//fim FolhaDePagamento()

//Imprime os dados dos funcionários de um determinado departamento
void RelatorioFuncionariosPorDepartamento(FILE *fun,FILE *dep){
    int cont;

    TFuncionario f;
    TDepartamento d;



    if(VerificaArquivoVazio(dep)==1)
        printf("\nNenhum departamento cadastrado!!!\n");
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
    int matexiste,sair,dia,mes,ano;;
    float novosalario;

    TFuncionario f;
    THistoricoSalario hs;

    if(VerificaArquivoVazio(fun)==1)
        printf("\nNenhum funcionario cadastrado!!!\n");
    else{

    do{
        printf("\nForneça a matrícula do funcionario: ");
        setbuf(stdin,NULL);
        fgets(matricula,10,stdin);
        setbuf(stdin,NULL);

        RetiraSequenciaDeEscape(matricula);
        matexiste=PesquisaMatricula(fun,matricula);

        if(matexiste==-1)
            printf("\nFuncionario inexistente!!!\n");
        else{

                printf("\nForneça o novo salario: ");
                scanf("%f",&novosalario);

                dataAtual(&dia,&mes,&ano);


                hs.mes=mes;
                hs.ano=ano;

                fseek(fun,matexiste*sizeof(f),SEEK_SET);
                fread(&f, sizeof(f), 1, fun);
                f.salario=novosalario;
                hs.id_funcionario=f.id;
                fseek(fun,matexiste*sizeof(f),SEEK_SET);
                fwrite(&f,sizeof(f),1,fun);

                hs.salario=novosalario;

                fseek(hsal,0,SEEK_END);
                fwrite(&hs,sizeof(hs),1,hsal);

                fflush(hsal);
                fflush(fun);

            }

            sair=sairDoLoop();

        }while(sair!=1);
    }
}//fim AlterarSalario()

//Altera o departamento dos funcionarios cadasreados e também faz um registro dos dados no historico do funcionario
void AlterarDepartamento(FILE*fun,FILE*hfun,FILE*dep){

    char matricula[10],novoDepartamento[40],dataAt[11];
    int matexiste,sair,mes,ano,dia;
    long dexiste;

    TFuncionario f;
    THistoricoFuncionario hf;

    if(VerificaArquivoVazio(fun)==1)
        printf("\nNenhum funcionario cadastrado!!!\n");
    else{
        if(VerificaArquivoVazio(dep)==1)
            printf("\nNenhum departamento cadastrado!!!\n");
        else{
            do{
                printf("\nForneça a matrícula do funcionario: ");
                setbuf(stdin,NULL);
                fgets(matricula,10,stdin);
                setbuf(stdin,NULL);

                RetiraSequenciaDeEscape(matricula);
                matexiste=PesquisaMatricula(fun,matricula);

                if(matexiste==-1)
                    printf("\nFuncionario inexistente!!!\n");
                else{
                    printf("\nForneça o novo departamento: ");
                    setbuf(stdin,NULL);
                    fgets(novoDepartamento,40,stdin);
                    setbuf(stdin,NULL);
                        //scanf("%li",&novodepartamento);
                    RetiraSequenciaDeEscape(novoDepartamento);
                    dexiste=PesquisaDepartamentoNome(dep,novoDepartamento);

                    if(dexiste==0)
                        printf("\nDepartamento inexistente!!!\n");
                    else{

                        //posicao=PesquisaDepartamentoID(dep,dexiste);

                        fseek(fun,matexiste*sizeof(f),SEEK_SET);
                        fread(&f, sizeof(f), 1, fun);
                        f.id_departamento=dexiste;
                        hf.id_funcionario=f.id;

                        dataAtual(&dia,&mes,&ano);

                        sprintf(dataAt,"%d/%d/%d",dia,mes,ano);

                        RetiraSequenciaDeEscape(dataAt);

                        strcpy(hf.data,dataAt);

                        RetiraSequenciaDeEscape(dataAt);
                        strcpy(hf.data,dataAt);

                        fseek(fun,matexiste*sizeof(f),SEEK_SET);
                        fwrite(&f,sizeof(f),1,fun);

                        hf.id_departamento=dexiste;

                        fseek(hfun,0,SEEK_END);
                        fwrite(&hf,sizeof(hf),1,hfun);

                        fflush(fun);
                        fflush(hfun);
                    }

                }

                sair=sairDoLoop();

            }while(sair!=1);
        }
    }
}//fim AlterarDepartamento()

/*Altera os dados de um funcionário  com determinada matrícula e também faz um registro dos dados no historico do funcionario e o
salario no historico de salario*/
void AlterarFuncionario(FILE*fun,FILE*dep,FILE*hsal,FILE*hfun){
    char matricula[10],dataNascimento[12],dataNascimento1[12],cpf[13],nomed[40],UF[4],dataAt[11],nomeFuncionario[60],rua[40],email[40],CEP[10],cidade[40],complemento[30], bairro[30];
    int cpfexiste,sair,posicao,testeData,dia,mes,ano;;
    long idexiste;



    TFuncionario f;
    THistoricoFuncionario hf;
    THistoricoSalario hs;

    do{
        if(VerificaArquivoVazio(fun)==1)
            printf("\nNenhum funcionario cadastrado!!!\n");
        else{

            printf("\nForneça a matrícula: ");
            setbuf(stdin,NULL);
            fgets(matricula,10,stdin);
            setbuf(stdin,NULL);

            RetiraSequenciaDeEscape(matricula);

            posicao=PesquisaMatricula(fun,matricula);

            if(posicao==-1)
                printf("\nFuncionário nao encontrado!!!\n");
            else{

                fseek(fun,posicao*sizeof(f),SEEK_SET);
                fread(&f,sizeof(f),1,fun);

                do{
                    printf("\nForneça o nome do funcionário: ");
                    setbuf(stdin,NULL);
                    fgets(nomeFuncionario,60,stdin);
                    setbuf(stdin,NULL);

                    RetiraSequenciaDeEscape(nomeFuncionario);
                }while(strlen(nomeFuncionario) == 0);

                strcpy(f.nome,nomeFuncionario);
                hf.id_funcionario=f.id;
                hs.id_funcionario=f.id;

                do{
                    printf("\nForneça a data de nascimento do funcionário: ");
                    setbuf(stdin,NULL);
                    fgets(dataNascimento,12,stdin);
                    setbuf(stdin,NULL);

                    RetiraSequenciaDeEscape(dataNascimento);
                    strcpy(dataNascimento1,dataNascimento);
                    testeData=verficaData(dataNascimento);

                    if(testeData==0)
                        printf("\nData inválida!!!\n");
                }while(testeData==0);

                strcpy(f.dataNascimento,dataNascimento1);

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
                        printf("\nCpf inválido!!!\n");

                }while(cpfexiste==0);

                strcpy(f.CPF,cpf);

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
                        fgets(rua,40,stdin);
                        setbuf(stdin,NULL);

                        RetiraSequenciaDeEscape(rua);
                        strcpy(f.rua,rua);


                        printf("\nForneça o bairro do funcionario: ");
                        setbuf(stdin,NULL);
                        fgets(bairro,30,stdin);
                        setbuf(stdin,NULL);

                        RetiraSequenciaDeEscape(bairro);
                        strcpy(f.bairro,bairro);

                        printf("\nForneça o numero da casa do funcionario: ");
                        scanf("%ui",&f.Numero);

                        printf("\nForneça o complemento da casa do funcionario: ");
                        setbuf(stdin,NULL);
                        fgets(complemento,30,stdin);
                        setbuf(stdin,NULL);

                        RetiraSequenciaDeEscape(complemento);
                        strcpy(f.complemento,complemento);

                        printf("\nForneça a cidade do funcionario: ");
                        setbuf(stdin,NULL);
                        fgets(cidade,40,stdin);
                        setbuf(stdin,NULL);

                        RetiraSequenciaDeEscape(cidade);
                        strcpy(f.cidade,cidade);

                        printf("\nForneça o UF do funcionario: ");
                        setbuf(stdin,NULL);
                        fgets(UF,4,stdin);
                        setbuf(stdin,NULL);

                        RetiraSequenciaDeEscape(UF);

                        strcpy(f.UF,UF);

                        printf("\nForneça o CEP do funcionario: ");
                        setbuf(stdin,NULL);
                        fgets(CEP,10,stdin);
                        setbuf(stdin,NULL);


                        RetiraSequenciaDeEscape(CEP);
                        strcpy(f.CEP,CEP);

                        printf("\nForneça o email do funcionario: ");
                        setbuf(stdin,NULL);
                        fgets(email,40,stdin);
                        setbuf(stdin,NULL);


                        RetiraSequenciaDeEscape(email);
                        strcpy(f.email,email);

                        dataAtual(&dia,&mes,&ano);

                        sprintf(dataAt,"%d/%d/%d",dia,mes,ano);

                        RetiraSequenciaDeEscape(dataAt);

                        strcpy(hf.data,dataAt);

                        hs.mes=mes;
                        hs.ano=ano;


                        fseek(fun,posicao*sizeof(f),SEEK_SET);
                        fwrite(&f,sizeof(f),1,fun);

                        fseek(hfun,0,SEEK_END);
                        fwrite(&hf,sizeof(hf),1,hfun);

                        fseek(hsal,0,SEEK_END);
                        fwrite(&hs,sizeof(hs),1,hsal);

                        fflush(fun);
                        fflush(hfun);
                        fflush(hsal);
                    }
                }

            }

        }

        sair=sairDoLoop();

    }while(sair!=1);
}//fim AlterarFuncionario()

//Imprime os dados do gerente de um determinado departamento
void RelatorioGerenteDeDepartamento(FILE *dep,FILE *fun){
    char nome[30];
    long dexiste;
    int sair,pos,posicaodep;

    TDepartamento d;
//    TFuncionario f;

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
                printf("\nDepartamento não encontrado!!!\n");
            else{
                posicaodep=PesquisaDepartamentoID(dep,dexiste);

                fseek(dep,posicaodep*sizeof(d),SEEK_SET);
                fread(&d,sizeof(d),1,dep);
                printf("%li",d.id_gerente);
                if(d.id_gerente==-1)
                    printf("\nNenhum funcionário cadastrado como gerente!!!\n");
                else{

                    pos=PesquisaFunID(fun,d.id_gerente);
                    apresentaDadosDoFuncionario(fun,dep,pos);
                }


            }

        }

        sair=sairDoLoop();

    }while(sair!=1);
}//fim RelatorioGerenteDeDepartamento()

void historicoDeSalario(FILE* hsal,FILE*fun){
    char matricula[10];
    long matexiste;
    unsigned short int mesInicial,mesFinal,anoInicial,anoFinal;
    int cont=0;

    THistoricoSalario hs;
    TFuncionario f;

    do{
        printf("\nForneça a matrícula: ");
        setbuf(stdin,NULL);
        fgets(matricula,10,stdin);
        setbuf(stdin,NULL);


        RetiraSequenciaDeEscape(matricula);
        matexiste=PesquisaMatricula(fun,matricula);
        if(matexiste==-1)
            printf("\nMatrícula inexistente!!!\n");
    }while(matexiste==-1);

    fseek(fun,matexiste*sizeof(f),SEEK_SET);
    fread(&f,sizeof(f),1,fun);

    printf("\nForneça os anos inicial e final: ");
    scanf("\n%hu%hu",&anoInicial,&anoFinal);

    printf("\nForneça os meses inicial e final: ");
    scanf("\n%hu%hu",&mesInicial,&mesFinal);


    rewind(hsal);
    while(fread(&hs,sizeof(hs),1,hsal)){
        if(f.id==hs.id_funcionario){
            if((hs.ano>=anoInicial) && (hs.ano<=anoFinal))
                if((hs.mes>=mesInicial) && (hs.mes<=mesFinal)){
                    printf("\n===================================");
                    printf("\nMes %u : %.2f",hs.mes,hs.salario);
                    printf("\nAno %u : %.2f",hs.ano,hs.salario);
                    printf("\n===================================\n");
                    cont++;
                }
        }
    }
    if(cont==0)
        printf("\nFuncionário sem histórico!!!");

}
