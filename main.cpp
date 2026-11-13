#include <iostream>
#include "gestao_escolar.h"

using namespace std;

int main() {
    carregarDados();

    int opcao;
    do {
        cout << "\n========================================\n";
        cout << "   SISTEMA DE GESTAO - ESCOLA PRIVADA\n";
        cout << "========================================\n";
        cout << "1. Cadastrar Aluno\n";
        cout << "2. Imprimir Todos os Alunos\n";
        cout << "3. Imprimir 1 Aluno\n";
        cout << "4. Editar 1 Aluno\n";
        cout << "5. Eliminar 1 Aluno\n";
        cout << "6. Contar Alunos\n";
        cout << "7. Adicionar Encarregado\n";
        cout << "8. Remover Encarregado\n";
        cout << "9. Atribuir Encarregado a Aluno\n";
        cout << "0. Sair\n";
        cout << "Escolha uma opcao: ";
        cin >> opcao;

        switch (opcao) {
            case 1: cadastrarAluno(); break;
            case 2: imprimirTodosAlunos(); break;
            case 3: imprimirUmAluno(); break;
            case 4: editarAluno(); break;
            case 5: eliminarAluno(); break;
            case 6: contarAlunos(); break;
            case 7: adicionarEncarregado(); break;
            case 8: removerEncarregado(); break;
            case 9: atribuirEncarregadoAluno(); break;
            case 0: cout << "Encerrando o programa...\n"; break;
            default: cout << "Opcao invalida! Tente novamente.\n";
        }
    } while (opcao != 0);

    return 0;
}
