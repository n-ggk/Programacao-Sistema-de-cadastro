#include <iostream>
#include <fstream>
using namespace std;

struct seriesTelevisivas {
    string nome, streaming, localizacao, diretor; int temporadas, episodios; float nota;
};

void menu(int &opcao);
bool menuVerifica(int &opcao);
//void adicionarSerie();
//void redimensionar();
int menuCaso(int &opcao);

int main() {
  int opcao;// int tamanho = 40, totalItens = 0;
  menu(opcao);
  if ( menuVerifica(opcao) == true){
    cerr << "Opção inválida. Fim do programa..." << endl;
    return 0;
  }
  menuCaso(opcao);
  return 0;
}
// Mostra o menu de opções
void menu(int &opcao) {
  cout << "1. Adicionar uma série\n"
     << "2. Listar séries\n"
     << "3. Buscar série por título\n"
     << "4. Buscar sédie por streaming\n"
     << "5. Buscar série por nota mínima\n"
     << "6. Excluir série\n"
     << "7. Salvar lista\n"
     << "Digite -1 para Sair\n";
  cin >> opcao;
  cin.ignore();
}
// Verifica se a opção é válida
bool menuVerifica(int &opcao){
  return (opcao == 0 | opcao > 7)? true : false; 
}
/*
void adicionarSerie(){
  cout << "Digite o nome da série" << endl;
  getline(cin, seriesTelevisivas.nome);
  cout << "Digite o nome do streaming" << endl;
  cin >> seriesTelevisivas.streaming;
  cout << "Digite a quantidade de temporadas e episódios" << endl;
  cin >> seriesTelevisivas.temporadas >> seriesTelevisivas.episodios;
  cout << "Digite a nota da série" << endl;
  cin >> seriesTelevisivas.nota;
  cout << "Digite a localização(País)" << endl;
  cin >> seriesTelevisivas.localizacao;
  cin.ignore();
  cout << "Digite o nome do diretor" << endl;
  getline(cin, seriesTelevisivas.diretor);
}
*/
/*
void redimensionar() {
    tamanho += 10;
    SeriesTelevisivas* novoVetor = new SeriesTelevisivas[tamanho];
    for (int i = 0; i < totalItens; i++) {
        novoVetor[i] = bancoDados[i];
    }
    delete[] bancoDados;
    bancoDados = novoVetor;
    cout << "Log: Vetor redimensionado para " << tamanho << " posições." << endl;
} 
*/

int menuCaso(int &opcao) {
  switch (opcao){
    case 1:
      /*
      if (totalItens == tamanho){
          redimensionar("variavel",tamanho);
      }
      totalItens++;
      adicionarSerie();
      */
      break;
    case 2:
      /*
      cout << "Listando séries..." << endl;

      if (arquivoLista.is_open()){
        while (getline(arquivoLista,lista)){
          cout << lista << endl;
        }
        arquivoLista.close();
      }else
        cerr << "Não foi possível abrir o arquivo" << endl;
        */ 
      
      //atualize sempre que não funcionar >> tentativas = 58
      break;
    case 3:
      cout << "Buscar série por título" << endl;
      break;
    case 4:
      cout << "Buscar série por streaming" << endl;
      break;
    case 5:
      cout << "Buscar série por nota mínima" << endl;
      break;
    case 6:
      cout << "Excluir série" << endl;
      break;
    case 7:
      cout << "Salvar lista" << endl;
      break;
    case -1:
      cout << "Fim do programa..." << endl;
  }
  return 0;
}


#include <iostream>
#include <fstream>
#include <string>

// Estrutura para os dados da série
struct Serie {
    std::string titulo;
    int temporadas;
    int episodios;
    float nota;
    std::string localidade;
    std::string diretor;
    std::string streaming;
    bool ativo; // Para remoção lógica
};

// Estrutura para gerenciar o vetor dinâmico (Vetor "na mão")
struct VetorSeries {
    Serie* dados;
    int capacidade;
    int tamanho;
};

void redimensionar(VetorSeries &v, int incremento) {
  v.capacidade += incremento;
  Serie* novoVetor = new Serie[v.capacidade];

  // Copia os dados do vetor antigo para o novo
  for (int i = 0; i < v.tamanho; i++) {
      novoVetor[i] = v.dados[i];
  }

  delete[] v.dados; // Libera a memória antiga
  v.dados = novoVetor; // Aponta para a nova memória
  std::cout << "\n[Aviso] Vetor redimensionado para " << v.capacidade << " posicoes.\n";
}

void inicializar(VetorSeries &v) {
  v.capacidade = 40;
  v.tamanho = 0;
  v.dados = new Serie[v.capacidade];
}

void carregarArquivo(VetorSeries &v, std::string nomeArquivo) {
    std::ifstream arquivo(nomeArquivo);
    std::string linha, lixo;

    if (!arquivo.is_open()) return;

    // Pula o cabeçalho
    std::getline(arquivo, lixo);

    while (std::getline(arquivo, linha)) {
        if (v.tamanho == v.capacidade) {
            redimensionar(v, 10); // Incremento de 10 conforme solicitado
        }

        // Usamos um stringstream ou tratamento manual para separar os campos
        // Exemplo simplificado de leitura por delimitador ';'
        Serie s;
        // ... lógica de separação de campos (ex: s.titulo, s.temporadas...)
        s.ativo = true;
        v.dados[v.tamanho] = s;
        v.tamanho++;
    }
    arquivo.close();
}

void buscarPorTitulo(VetorSeries v, std::string termo) {
    for (int i = 0; i < v.tamanho; i++) {
        if (v.dados[i].ativo && v.dados[i].titulo.find(termo) != std::string::npos) {
            std::cout << "ID " << i << ": " << v.dados[i].titulo << "\n";
        }
    }
}

void salvarArquivo(VetorSeries v, std::string nomeArquivo) {
    std::ofstream arquivo(nomeArquivo);
    arquivo << "# Título; Temporadas; Episodios; Nota; Localidade; Diretor; Streaming\n";
    for (int i = 0; i < v.tamanho; i++) {
        if (v.dados[i].ativo) { // Só salva os que não foram removidos logicamente
            arquivo << v.dados[i].titulo << "; " << v.dados[i].temporadas << "; "
                    << v.dados[i].episodios << "; " << v.dados[i].nota << "; "
                    << v.dados[i].localidade << "; " << v.dados[i].diretor << "; "
                    << v.dados[i].streaming << "\n";
        }
    }
    arquivo.close();
}
