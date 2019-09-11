#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include<ctype.h>
#include"departamento.h"
#include"funcionario.h"

int verificaDigito(char * dado){
    int i;
    RetiraSequenciaDeEscape(dado);
    for(i=0;i<strlen(dado)-1;i++)
        if(isdigit(dado[i])==0)
            return 0;
    return 1;
}

//Verifica CPF que recebeu retornando 1 para CPF valido e 0 caso contrário
int VerificaCpf(FILE*fun,char *cpf){
    int i, j, digito1 = 0, digito2 = 0;
    //printf("%d",strlen(cpf));

    TFuncionario f;

    rewind(fun);
    while(fread(&f,sizeof(f),1,fun)){
        if(strcmp(cpf,f.CPF)==0){
            return 0;
            printf("\ncpf repitido\n");
        }
    }

    if(strlen(cpf) != 11)
        return 0;
    else if((strcmp(cpf,"00000000000") == 0) || (strcmp(cpf,"11111111111") == 0) || (strcmp(cpf,"22222222222") == 0) ||
            (strcmp(cpf,"33333333333") == 0) || (strcmp(cpf,"44444444444") == 0) || (strcmp(cpf,"55555555555") == 0) ||
            (strcmp(cpf,"66666666666") == 0) || (strcmp(cpf,"77777777777") == 0) || (strcmp(cpf,"88888888888") == 0) ||
            (strcmp(cpf,"99999999999") == 0))
        return 0; ///se o CPF tiver todos os números iguais ele é inválido.
    else
    {
        ///digito 1---------------------------------------------------
        for(i = 0, j = 10; i < strlen(cpf)-2; i++, j--) ///multiplica os números de 10 a 2 e soma os resultados dentro de digito1
            digito1 += (cpf[i]-48) * j;
        digito1 %= 11;
        if(digito1 < 2)
            digito1 = 0;
        else
            digito1 = 11 - digito1;
        if((cpf[9]-48) != digito1)
            return 0; ///se o digito 1 não for o mesmo que o da validação CPF é inválido
        else
        ///digito 2--------------------------------------------------
        {
            for(i = 0, j = 11; i < strlen(cpf)-1; i++, j--) ///multiplica os números de 11 a 2 e soma os resultados dentro de digito2
                    digito2 += (cpf[i]-48) * j;
        digito2 %= 11;
        if(digito2 < 2)
            digito2 = 0;
        else
            digito2 = 11 - digito2;
        if((cpf[10]-48) != digito2)
            return 0; ///se o digito 2 não for o mesmo que o da validação CPF é inválido
        }
    }
    return 1;
}//fim verificaCpf()

/*Esssa função verifica se a data contém valor negativo se é valida em relação aos dias de um mês e se é maior que 20/06/1960. Retornado 0 caso
se enquadre em algum desses casos*/
int verficaData(char *data){
    char *aux;
    int v[]={31,28,31,30,31,30,31,31,30,31,30,31},dia,mes,ano,i;

    aux=strtok(data,"/");
    dia=atoi(aux);
    aux=strtok(NULL,"/");//O ponteiro nulo é usado para se referir a pesquisa anterior, no caso '/'
    mes=atoi(aux);
    aux=strtok(NULL,"/");
    ano=atoi(aux);

    //se o ano for bissexto o mês de fevereiro recebe 29 dias
    if(ano%4==0)
        v[1]=29;

    //verifica datas com valores negativos
    if((dia<0) || (mes<0) || (ano<0))
        return 0;


    if((ano<1960)) // verifica se data é menor que 20/06/1960
        return 0;
    else
        if((mes<06) && ano==1960)
            return 0;
        else
            if((dia<20) && (mes=06) && (ano==1960))
                return 0;


    //verifica se o dia não ultrapassa o limeite de dia de determinado mês
    for(i=0;i<11;i++){
        if(mes==i+1)
            if(dia>v[i])
                return 0;
    }

    return 1;

}//fim verificaData()

//Recebe um ponteiro para um arquivo e verifica se o mesmo está vazio retornando 1 para vazios e 0 caso contrário
int VerificaArquivoVazio(FILE* arq){

    fseek(arq,0,SEEK_END);
    if(ftell(arq)<=0){
        return 1;
    }
    return 0;
}//fim VerificaArquivoVazio()
