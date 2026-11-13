#include "gestao_escolar.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>

vector<Encarregado> encarregados;
vector<Aluno> alunos;
int contadorIdAluno = 1;
int contadorIdEncarregado = 1;

void salvarDados() {
    ofstream arqEnc("encarregados.txt");
    if (arqEnc.is_open()) {
        arqEnc << contadorIdEncarregado << "\n";
        for (const auto& enc : encarregados) {
            arqEnc << enc.id << ";" << enc.nome << ";" << enc.idade << "\n";
        }
        arqEnc.close();
    }

    ofstream arqAlu("alunos.txt");
    if (arqAlu.is_open()) {
        arqAlu << contadorIdAluno << "\n";
        for (const auto& al : alunos) {
            arqAlu << al.id << ";" << al.nome << ";" << al.idEncarregado << "\n";
        }
        arqAlu.close();
    }
    cout << "\nDados salvos com sucesso nos arquivos!\n";
}

void carregarDados() {
    ifstream arqEnc("encarregados.txt");
    if (arqEnc.is_open()) {
        string linha;
        if (getline(arqEnc, linha)) {
            contadorIdEncarregado = stoi(linha);
        }
        encarregados.clear();
        while (getline(arqEnc, linha)) {
            stringstream ss(linha);
            string sId, nome, sIdade;
            if (getline(ss, sId, ';') && getline(ss, nome, ';') && getline(ss, sIdade, ';')) {
                Encarregado enc;
                enc.id = stoi(sId);
                enc.nome = nome;
                enc.idade = stoi(sIdade);
                encarregados.push_back(enc);
            }
        }
        arqEnc.close();
    }

    ifstream arqAlu("alunos.txt");
    if (arqAlu.is_open()) {
        string linha;
        if (getline(arqAlu, linha)) {
            contadorIdAluno = stoi(linha);
        }
        alunos.clear();
        while (getline(arqAlu, linha)) {
            stringstream ss(linha);
            string sId, nome, sIdEnc;
            if (getline(ss, sId, ';') && getline(ss, nome, ';') && getline(ss, sIdEnc, ';')) {
                Aluno al;
                al.id = stoi(sId);
                al.nome = nome;
                al.idEncarregado = stoi(sIdEnc);
                alunos.push_back(al);
            }
        }
        arqAlu.close();
    }
    cout << "\nDados carregados com sucesso dos arquivos!\n";
}

void adicionarEncarregado() {
    Encarregado enc;
    enc.id = contadorIdEncarregado++;
    cout << "\n--- Cadastro de Encarregado ---\n";
    cout << "Nome do Encarregado: ";
    cin.ignore();
    getline(cin, enc.nome);
    cout << "Idade: ";
    cin >> enc.idade;
    
    encarregados.push_back(enc);
    salvarDados();
    cout << "Encarregado cadastrado com sucesso! ID atribuido: " << enc.id << "\n";
}

void removerEncarregado() {
    int id;
    cout << "\nDigite o ID do encarregado que deseja remover: ";
    cin >> id;

    auto it = remove_if(encarregados.begin(), encarregados.end(), [id](const Encarregado& e) {
        return e.id == id;
    });

    if (it != encarregados.end()) {
        encarregados.erase(it, encarregados.end());
        for (auto& aluno : alunos) {
            if (aluno.idEncarregado == id) {
                aluno.idEncarregado = -1;
            }
        }
        salvarDados();
        cout << "Encarregado removido com sucesso!\n";
    } else {
        cout << "Encarregado nao encontrado.\n";
    }
}

void cadastrarAluno() {
    Aluno al;
    al.id = contadorIdAluno++;
    al.idEncarregado = -1;
    
    cout << "\n--- Cadastro de Aluno ---\n";
    cout << "Nome do Aluno: ";
    cin.ignore();
    getline(cin, al.nome);

    alunos.push_back(al);
    salvarDados();
    cout << "Aluno cadastrado com sucesso! ID atribuido: " << al.id << "\n";
}

void imprimirTodosAlunos() {
    if (alunos.empty()) {
        cout << "\nNenhum aluno cadastrado.\n";
        return;
    }

    cout << "\n--- Lista de Alunos ---\n";
    for (const auto& al : alunos) {
        cout << "ID: " << al.id << " | Nome: " << al.nome;
        if (al.idEncarregado != -1) {
            string nomeEnc = "Desconhecido";
            for (const auto& enc : encarregados) {
                if (enc.id == al.idEncarregado) {
                    nomeEnc = enc.nome;
                    break;
                }
            }
            cout << " | Encarregado: " << nomeEnc;
        } else {
            cout << " | Encarregado: Nenhum atribuido";
        }
        cout << "\n";
    }
}

void imprimirUmAluno() {
    int id;
    cout << "\nDigite o ID do aluno que deseja buscar: ";
    cin >> id;

    for (const auto& al : alunos) {
        if (al.id == id) {
            cout << "\n--- Aluno Encontrado ---\n";
            cout << "ID: " << al.id << "\nNome: " << al.nome << "\n";
            if (al.idEncarregado != -1) {
                for (const auto& enc : encarregados) {
                    if (enc.id == al.idEncarregado) {
                        cout << "Encarregado: " << enc.nome << " (Idade: " << enc.idade << ")\n";
                        break;
                    }
                }
            } else {
                cout << "Encarregado: Nenhum atribuido\n";
            }
            return;
        }
    }
    cout << "Aluno com ID " << id << " nao encontrado.\n";
}

void eliminarAluno() {
    int id;
    cout << "\nDigite o ID do aluno que deseja eliminar: ";
    cin >> id;

    auto it = remove_if(alunos.begin(), alunos.end(), [id](const Aluno& a) {
        return a.id == id;
    });

    if (it != alunos.end()) {
        alunos.erase(it, alunos.end());
        salvarDados();
        cout << "Aluno eliminado com sucesso!\n";
    } else {
        cout << "Aluno nao encontrado.\n";
    }
}

void contarAlunos() {
    cout << "\nTotal de alunos cadastrados: " << alunos.size() << "\n";
}

void editarAluno() {
    int id;
    cout << "\nDigite o ID do aluno que deseja editar: ";
    cin >> id;

    for (auto& al : alunos) {
        if (al.id == id) {
            cout << "Nome atual: " << al.nome << "\n";
            cout << "Novo nome: ";
            cin.ignore();
            getline(cin, al.nome);
            salvarDados();
            cout << "Aluno atualizado com sucesso!\n";
            return;
        }
    }
    cout << "Aluno nao encontrado.\n";
}

void atribuirEncarregadoAluno() {
    if (alunos.empty() || encarregados.empty()) {
        cout << "\nE necessario ter pelo menos um aluno e um encarregado cadastrados.\n";
        return;
    }

    int idAluno, idEnc;
    cout << "\n--- Atribuir Encarregado a Aluno ---\n";
    cout << "Digite o ID do Aluno: ";
    cin >> idAluno;
    cout << "Digite o ID do Encarregado: ";
    cin >> idEnc;

    auto itAluno = find_if(alunos.begin(), alunos.end(), [idAluno](const Aluno& a) {
        return a.id == idAluno;
    });

    auto itEnc = find_if(encarregados.begin(), encarregados.end(), [idEnc](const Encarregado& e) {
        return e.id == idEnc;
    });

    if (itAluno != alunos.end() && itEnc != encarregados.end()) {
        itAluno->idEncarregado = itEnc->id;
        salvarDados();
        cout << "Encarregado '" << itEnc->nome << "' atribuido ao aluno '" << itAluno->nome << "' com sucesso!\n";
    } else {
        cout << "ID de aluno ou encarregado invalido.\n";
    }
}
