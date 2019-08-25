#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#include"Departamento.h"
#include"Funcionario.h"
#include"HistoricoDepartamento.h"
#include"HistoricoFuncionario.h"
#include"HistoricoSalario.h"
#include"funcoesPesquisa.h"
#include"funcoesVerificacao.h"

//Recebe um ponteiro para um arquivo e verifica se o mesmo está vazio retornando 1 para vazios e 0 caso contrário
int VerificaArquivoVazio(FILE* arq){

    fseek(arq,0,SEEK_END);
    if(ftell(arq)<=0){
        return 1;
    }
    return 0;
}//fim VerificaArquivoVazio()

void imprimir(FILE*dep){

    int i,j;
    TDepartamento dp;

    fseek(dep,0,SEEK_END);//Usa para ver se tem dados no arquivo ou não
    if(ftell(dep)<=0){
        //printf("%d",ftell(dep));
        printf("\nSem dados no arquio");
    }
    else{
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
}

/*realiza uma pesquisa no arquivo departamento.dat, caso encontre retorna a posição e se não encontar retorna 0 */
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

/*realiza uma pesquisa no arquivo funcionario.dat, caso encontre retorna a posição e se não encontar retorna 0 */
int PesquisaFunID(FILE *fun,long id){
    int pos=0;
    TFuncionario f;

    rewind(fun);
    while(fread(&f, sizeof(f), 1, fun)){
        if(f.id == id)
            return pos;
        pos++;
    }

    return 0; //Funcionario não foi encontrada.

}//fim pesquisafunID()

//Essa função recebe o ponteiro para o arquivo do departamento.dat e verifica o último id, retornado o póximo válido
long IncrementaID(FILE* dep){
    long proximoId,tamanho;

    fseek(dep,0,SEEK_END);
    tamanho=ftell(dep);
    proximoId=tamanho/sizeof(TDepartamento);

    return proximoId++;

}//fim incrementaId()

//Nessa funçaõ o \n do vetor de char é trocado pelo \0
void RetiraSequenciaDeEscape(char *palavra){

    if(palavra[strlen(palavra) - 1] == '\n')
        palavra[strlen(palavra) - 1] = '\0';
}//fim RetiraSequenciaDeEscape()

//cadastra os dados no arquivo departamento.dat
void CadastraDepartamento(FILE*dep,FILE*hdep){

    int sair;
    //char ramal[100];

    TDepartamento d;
    THistoricoDepartamento hd;

    do{
        do{
            printf("\nForneça o nome do departamento: ");
            setbuf(stdin,NULL);
            fgets(d.nome,40,stdin);
            setbuf(stdin,NULL);

        }while(strlen(d.nome) == 1);//verifica o tamanho enquanto n for maior que 1 ele faz a pergunta novamente

        RetiraSequenciaDeEscape(d.nome);

        printf("\nForneça a sigla do departamento: ");
        setbuf(stdin,NULL);
        fgets(d.sigla,10,stdin);
        setbuf(stdin,NULL);

        RetiraSequenciaDeEscape(d.sigla);


        printf("\nForneça o Ramal: ");
        scanf("%hu",&d.Ramal);

        d.id=IncrementaID(dep);

        d.id_gerente=-1;

        fseek(dep,0,SEEK_END);
        fwrite(&d,sizeof(d),1,dep);

        hd.id_departamento=d.id;
        hd.id_gerente=d.id_gerente;

        printf("\nTestando\n");

        fseek(hdep,0,SEEK_END);
        fwrite(&hd,sizeof(hd),1,hdep);

        printf("\nDeseja sair?\n");
        printf("\n1-Sim     2-Não\n");
        printf("\n=> ");
        scanf("%d",&sair);

    }while(sair!=1);

}//fim cadastraDepartamento()

//Altera o gerente no arquivo departamento.dat e no historicodepartamento.dat, isso se o novo id n for um id existente
void AlterarGerente(FILE*dep,FILE*fun,FILE*hdep){

    int posicao,posicaoNovoGerente,sair;
    long idDepartamento;
    char nomeDepartamento[40],matriculaDoNovoGerente[10];

    TDepartamento d;
    TFuncionario f;
    THistoricoDepartamento hd;

    do{
        if(VerificaArquivoVazio(dep)==1)//verifica se o arquivo está vazio
            printf("\nNenhum departamento cadastrado\n");
        else{

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

                printf("\n%d\n",posicao);

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

                        printf("\n%d\n",posicaoNovoGerente);
                        fseek(fun,posicaoNovoGerente*sizeof(f),SEEK_SET);
                        fread(&f,sizeof(f),1,fun);

                        d.id_gerente=f.id;
                        hd.id_gerente=f.id;
                        hd.id_departamento=idDepartamento;

                        fseek(dep,posicao*sizeof(d),SEEK_SET);
                        fwrite(&d,sizeof(d),1,dep);

                        fseek(hdep,0,SEEK_END);
                        fwrite(&hd,sizeof(hd),1,hdep);
                    }
                }
            }

        }

        printf("\nDeseja sair?\n");
        printf("\n1-Sim     2-Não\n");
        scanf("%d",&sair);

    }while(sair!=1);
}//fim AlterarGerente()
