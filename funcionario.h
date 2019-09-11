#ifndef FUNCIONARIO_H_INCLUDED
#define FUNCIONARIO_H_INCLUDED

typedef struct{
    long id;
    char matricula[10];
    char nome[60];
    char dataNascimento[11];
    char CPF[12];
    long id_departamento;
    float salario;
    char rua[40];
    char bairro[30];
    unsigned int Numero;
    char complemento[30];
    char cidade[40];
    char UF[3];
    char CEP[9];
    char email[40];
}TFuncionario;


void CadastrarFuncionario(FILE*,FILE*,FILE*,FILE*);
void ConsultaFuncionarioporMatricula(FILE*,FILE*);
void FolhaDePagamento(FILE*);
void RelatorioFuncionariosPorDepartamento(FILE*,FILE*);
void AlterarSalario(FILE*,FILE*);
void AlterarDepartamento(FILE*,FILE*,FILE*);
void AlterarFuncionario(FILE*,FILE*,FILE*,FILE*);
void RelatorioGerenteDeDepartamento(FILE*,FILE*);
void historicoDeSalario(FILE*,FILE*);

#endif // FUNCIONARIO_H_INCLUDED
