#ifndef GESTAO_ESCOLAR_H
#define GESTAO_ESCOLAR_H

#include <string>
#include <vector>

using namespace std;

// Definicao das estruturas
struct Encarregado {
    int id;
    string nome;
    int idade;
};

struct Aluno {
    int id;
    string nome;
    int idEncarregado;
};

// Declaracao das variaveis globais
extern vector<Encarregado> encarregados;
extern vector<Aluno> alunos;
extern int contadorIdAluno;
extern int contadorIdEncarregado;

// --- PROTOTIPOS DAS FUNCOES ---
void salvarDados();
void carregarDados();
void adicionarEncarregado();
void removerEncarregado();
void cadastrarAluno();
void imprimirTodosAlunos();
void imprimirUmAluno();
void eliminarAluno();
void contarAlunos();
void editarAluno();
void atribuirEncarregadoAluno();

#endif
