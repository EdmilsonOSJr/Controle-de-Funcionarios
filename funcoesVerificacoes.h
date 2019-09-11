#ifndef FUNCOESVERIFICACOES_H_INCLUDED
#define FUNCOESVERIFICACOES_H_INCLUDED

int VerificaArquivoVazio(FILE*);
int VerificaCpf(FILE*,char *);
int verficaData(char *);
void RetiraSequenciaDeEscape(char *);
int verificaDigito(char *);

#endif // FUNCOESVERIFICACOES_H_INCLUDED
