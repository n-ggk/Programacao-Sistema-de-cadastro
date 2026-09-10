#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Estrutura para os dados da série
struct Serie {
    string titulo;
    int temporadas;
    int episodios;
    float nota;
    string localidade;
    string diretor;
    string streaming;
    bool ativo; // Para remoção da série
};

// Estrutura que gerencia o vetor dinâmico
struct VetorSeries {
    Serie* dados;
    int capacidade;
    int tamanho;
};

// Funções para manipulação do vetor
void redimensionar(VetorSeries &v, int incremento);
void inicializar(VetorSeries &v);
void inserirManualmente(VetorSeries &v, int incremento)
void carregarArquivo(VetorSeries &v, string nomeArquivo);
void buscarPorTitulo(VetorSeries v, string termo);
void salvarArquivo(VetorSeries v, string nomeArquivo);
void menu(int &opcao);
void opcaoMenu(int &opcao, VetorSeries &meuCadastro);
void exibirSerie(Serie s, int idx);

// procedimento de redimensionamento do vetor
void redimensionar(VetorSeries &v, int incremento) {
  v.capacidade += incremento;
  Serie* novoVetor = new Serie[v.capacidade];

  // Copia os dados do vetor antigo para o novo
  for (int i = 0; i < v.tamanho; i++) {
      novoVetor[i] = v.dados[i];
  }

  delete[] v.dados; // Libera o espaço da memória
  v.dados = novoVetor; // Aponta para a nova memória
  cout << "\n[Aviso] Vetor redimensionado para " << v.capacidade << " posicoes.\n";
}

void inicializar(VetorSeries &v) {
  v.capacidade = 40;
  v.tamanho = 0;
  v.dados = new Serie[v.capacidade];
}
// Função para inserir uma nova série manualmente
void inserirManualmente(VetorSeries &v, int incremento) {
    // Verifica se o vetor precisa de mais espaço antes de inserir
    if (v.tamanho == v.capacidade) {
        redimensionar(v, incremento); // incremento = 10 
    }

    Serie nova;
    cout << "\n--- Cadastrar Nova Serie ---\n";

    // O campo deve aceitar strings com espaços 
    cout << "Titulo: ";
    getline(cin, nova.titulo);

    cout << "Temporadas: ";
    cin >> nova.temporadas;

    cout << "Episodios: ";
    cin >> nova.episodios;

    cout << "Nota: ";
    cin >> nova.nota;
    cin.ignore(); // Limpa o buffer para o próximo getline

    cout << "Localidade: ";
    getline(cin, nova.localidade);

    cout << "Diretor: ";
    getline(cin, nova.diretor);

    cout << "Streaming: ";
    getline(cin, nova.streaming);

    nova.ativo = true; // Define como ativo por padrão

    // Insere no final do vetor 
    v.dados[v.tamanho] = nova;
    v.tamanho++;

    cout << "\nSerie cadastrada com sucesso no indice " << v.tamanho - 1 << "!\n";
}

void carregarArquivo(VetorSeries &v, string nomeArquivo) {

    ifstream arq(nomeArquivo.c_str());

    if (!arq.is_open()) {
        cout << "Erro ao abrir arquivo.\n";
        return;
    }

    string linha;
    getline(arq, linha); // pula cabeçalho

    while (getline(arq, linha)) {

        if (v.tamanho == v.capacidade)
            redimensionar(v, 10);

        Serie s;
        s.ativo = true;

        int pos;
        string campo;

        // TITULO
        pos = linha.find(';');
        s.titulo = linha.substr(0, pos);
        linha = linha.substr(pos + 2);

        // TEMPORADAS
        pos = linha.find(';');
        campo = linha.substr(0, pos);
        s.temporadas = stoi(campo);
        linha = linha.substr(pos + 2);

        // EPISODIOS
        pos = linha.find(';');
        campo = linha.substr(0, pos);
        s.episodios = stoi(campo);
        linha = linha.substr(pos + 2);

        // NOTA
        pos = linha.find(';');
        campo = linha.substr(0, pos);
        s.nota = stof(campo);
        linha = linha.substr(pos + 2);

        // LOCALIDADE
        pos = linha.find(';');
        s.localidade = linha.substr(0, pos);
        linha = linha.substr(pos + 2);

        // DIRETOR
        pos = linha.find(';');
        s.diretor = linha.substr(0, pos);
        linha = linha.substr(pos + 2);

        // STREAMING
        s.streaming = linha;

        v.dados[v.tamanho++] = s;
    }

    arq.close();
}
// Função para buscar séries por título
void buscarPorTitulo(VetorSeries v, string termo) {
    for (int i = 0; i < v.tamanho; i++) {
        if (v.dados[i].ativo && v.dados[i].titulo.find(termo) != string::npos) {
            cout << "ID " << i << ": " 
                << v.dados[i].titulo << "; " 
                << v.dados[i].temporadas << " temporadas; "
                << v.dados[i].episodios << " episodios; nota "
                << v.dados[i].nota << "; localidade:"
                << v.dados[i].localidade << "; diretor:" 
                << v.dados[i].diretor << "; streaming:"
                << v.dados[i].streaming << "\n";
        }
    }
}
// Função para salvar o vetor em um arquivo
void salvarArquivo(VetorSeries v, string nomeArquivo) {
    ofstream arquivo(nomeArquivo);
    arquivo << "# Título; Temporadas; Episodios; Nota; Localidade; Diretor; Streaming\n";
    for (int i = 0; i < v.tamanho; i++) {
        if (v.dados[i].ativo) { // Só salva os que não foram removidos
            arquivo << v.dados[i].titulo << "; " 
                << v.dados[i].temporadas << "; "
                << v.dados[i].episodios << "; "
                << v.dados[i].nota << "; "
                << v.dados[i].localidade << "; " 
                << v.dados[i].diretor << "; "
                << v.dados[i].streaming << "\n";
        }
    }
    arquivo.close();
}
// Função para exibir uma série se não excluída
void exibirSerie(Serie s, int idx) {
    if (s.ativo) {
        cout << "[" << idx << "] " << s.titulo << " | Nota: " << s.nota 
                  << " | Streaming: " << s.streaming << "\n";
    }
}
// Mostra o menu de opções
void menu(int &opcao){
  cout << "\n--- SISTEMA DE SERIES ---\n"
      << "1. Listar Tudo\n"
      << "2. Adicionar Serie\n"
      << "3. Listar Trecho\n"
      << "4. Buscar por Titulo\n"
      << "5. Remover Serie\n"
      << "6. Salvar Lista\n"
      << "0. Sair\n"
      << "Escolha: ";
  cin >> opcao;
  cin.ignore();
}
// Trata a opção que será escolhida no menu
void opcaoMenu(int &opcao, VetorSeries &meuCadastro){
    while (opcao != 0) {
        menu(opcao);
        if (opcao == 1) {
            for (int i = 0; i < meuCadastro.tamanho; i++) exibirSerie(meuCadastro.dados[i], i);
        } 
        else if (opcao == 2) {
            inserirManualmente(meuCadastro, 10);
        }
        else if (opcao == 3) {
            int ini, fim;
            cout << "Inicio e Fim: "; cin >> ini >> fim;
            for (int i = ini; i <= fim && i < meuCadastro.tamanho; i++)
                exibirSerie(meuCadastro.dados[i], i);
        }
        else if (opcao == 4) {
            string t;
            cout << "Titulo: "; getline(cin, t);
            buscarPorTitulo(meuCadastro, t);
        }
        else if (opcao == 5) {
            int id;
            cout << "ID para remover: "; cin >> id;
            if (id >= 0 && id < meuCadastro.tamanho) {
                meuCadastro.dados[id].ativo = false;
                cout << "Removido logicamente.\n";
            }
        }
        else if (opcao == 6) {
            salvarArquivo(meuCadastro, "series.txt");
            cout << "Arquivo atualizado com sucesso!\n";
        }
    }
}

int main() {
    VetorSeries meuCadastro;
    inicializar(meuCadastro);
    carregarArquivo(meuCadastro, "series.txt");

    int opcao = -1;
    opcaoMenu(opcao, meuCadastro);

    delete[] meuCadastro.dados; // Limpeza final de memória
    return 0;
}
