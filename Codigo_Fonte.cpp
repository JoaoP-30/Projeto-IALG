//======================================================
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <limits>

using namespace std;

// ====== Definição de cores (ANSI Escape Codes) ======

#define foreg "\033[38;5;154m"   // Verde claro
#define orange "\033[38;5;208m"  // Laranja
#define redS "\033[38;5;196m"    // Vermelho intenso
#define green "\033[38;5;2m"     // Verde padrão
#define back "\033[m"         // Cor padrão do terminal

// =====================================================

// ====== Estruturas de dados ======

// Representa uma data (dia, mês e ano)
struct tempo {
    int dia;
    int mes;
    int ano;
};

// Representa os dados de um(a) artista
struct bcp {
    char Nome[70];
    tempo Data_de_nascimento;
    char Nacionalidade[70];
    char Genero[70];
    char Maior_sucesso[70];
    char Grupo_ou_Carreira_solo[70];
    int Quantidade_de_albuns;
    int Tempo_de_carreira;
};
// ==================================


// ====== Protótipos das funções ======

// Exibe o menu principal do programa
void menu ();

// Lê os registros do arquivo e redimensiona o vetor dinamicamente
void leitura_redimensionada(bcp *&dados, int &numRegistros);

// Exibe todos os registros ou apenas uma parte deles
void exibe(int num);
void modo_de_exibir(unsigned &vis);
void exibir_registro(const bcp& artista, int posicao, unsigned vis);

// Cria o arquivo binário a partir de entradas do usuário
void criar_binario ();

// Lê e exibe o conteúdo do arquivo binário criado
void ler_binario();

// Funções auxiliares para ordenação (por obra e por nome)
int particiona_obra(bcp v[], int p, int r);
int particiona_nome(bcp v[], int p, int r);

// Implementações de QuickSort para diferentes critérios
void quicksort_o(bcp a[], int pos_pivo, int fim);
void quicksort_n(bcp a[], int pos_pivo, int fim);

// Inicia o processo de ordenação alfabética
void ordena_alfabetica(int num);

// Compara duas strings sem case sensitive
int comparaCaseInsensitive(const char* str1, const char* str2);

// Insere um novo registro no conjunto de dados
void inserir();

// Remove um registro específico dos dados
void remover();

// Implementações de busca binária para diferentes parâmetros
int busca_binaria_o(bcp vetor[], int tam, string target);
int busca_binaria_n(bcp vetor[], int tam, string target);

// Busca um registro pelo nome ou pela obra
void buscar(int num);

// Restaura o arquivo 'data.csv' para sua forma padrão
void recap();

// Limpa a tela do console
void limparTela();

// Exibe a mensagem final ao encerrar o programa
void displayEncerrarPrograma();

// ===========================================

int main () {

    cout << orange << "Bem-vindo!\nPressione 'C' para continuar:\n" << back;
    char iniciar;
    cin >> iniciar;

    if (tolower(iniciar) != 'c') {
        limparTela();
        displayEncerrarPrograma();
        return 1;
    }

    bool continua = true;
    while (continua) {
        menu();
        unsigned operacao;

        cout << foreg << "Digite aqui: " << back;
        cin >> operacao;
       
        switch (operacao) {
            case 1: exibe(0); 
                break;
            case 2: exibe(1); 
                break;
            case 3: criar_binario(); 
                break;
            case 4: ler_binario(); 
                break;
            case 5: ordena_alfabetica(0); 
                break;
            case 6: ordena_alfabetica(1); 
                break;
            case 7: inserir(); 
                break;
            case 8: remover(); 
                break;
            case 9: buscar(0);
                break;
            case 10: buscar(1);
                break;
            case 11: recap();
                break;
            default:
                cout << redS << "Carácter inválido \n" << back;
        }


        cout << foreg << "Deseja realizar alguma outra operação? (S/n)\n" << back;
        char continuar;
        cin >> continuar;

        continua = (tolower(continuar) == 's');
        limparTela();

        if (!continua) {
            limparTela();
            displayEncerrarPrograma();
        }
    }

    return 0;
}

void menu (){
  
   cout << orange
     << "  _______________________________ \n"
        " |                               | \n"  
     << " |         MENU PRINCIPAL        |\n"
     << " |_______________________________|\n"
     << back;

    cout << orange << " [1] Exibir todos os dados do arquivo\n" << back;
    cout << orange << " [2] Exibir um trecho dos dados\n" << back;
    cout << orange << " [3] Criar um novo arquivo binário\n" << back;
    cout << orange << " [4] Ler e exibir o arquivo binário\n" << back;
    cout << orange << " [5] Ordenar dados por nome da obra de maior sucesso\n" << back;
    cout << orange << " [6] Ordenar dados por nome do(a) artista\n" << back;
    cout << orange << " [7] Inserir um novo registro\n" << back;
    cout << orange << " [8] Remover um registro pelo índice\n" << back;
    cout << orange << " [9] Realizar uma busca pelo nome da obra de maior sucesso\n" << back;
    cout << orange << " [10] Realizar uma busca pelo nome do(a) artista\n" << back;
    cout << orange << " [11] Realizar a restauração do arquivo para forma padrão\n" << back;
    cout << orange << "-----------------------------------\n" << back;

}

void leitura_redimensionada(bcp *&dados, int &numRegistros) {
    
    ifstream arq_csv("data.csv");
    if (!arq_csv) {
        cout << redS << "Não foi possível abrir o arquivo." << '\n' << back;
        return;
    }
    
    string cabecalho;
    getline(arq_csv, cabecalho);

    int capacidade = 40;
    int tamanho = 0;
    
    dados = new bcp[capacidade];

    while (arq_csv.peek() != EOF) {
        if (tamanho >= capacidade) {
            capacidade += 5;
            bcp *novo_dadosBCP = new bcp[capacidade];
            for (int j = 0; j < tamanho; ++j) {
                novo_dadosBCP[j] = dados[j];
            }
            delete[] dados;
            dados = novo_dadosBCP;
        }
        
        char lixo;

        arq_csv.getline(dados[tamanho].Nome, 70, ',');        

        arq_csv >> dados[tamanho].Data_de_nascimento.dia >> lixo 
               >> dados[tamanho].Data_de_nascimento.mes >> lixo 
               >> dados[tamanho].Data_de_nascimento.ano;                       
        
        arq_csv >> lixo;  

        arq_csv.getline(dados[tamanho].Nacionalidade, 70, ',');        
        arq_csv.getline(dados[tamanho].Genero, 70, ',');
        arq_csv.getline(dados[tamanho].Maior_sucesso, 70, ',');
        arq_csv.getline(dados[tamanho].Grupo_ou_Carreira_solo, 70, ',');

        arq_csv >> dados[tamanho].Quantidade_de_albuns;
        arq_csv >> lixo;                          
        arq_csv >> dados[tamanho].Tempo_de_carreira;
        arq_csv >> lixo; 

        arq_csv.ignore(numeric_limits<streamsize>::max(), '\n');
        
        if(strlen(dados[tamanho].Nome) > 0){
            tamanho++;
        }
    }

    arq_csv.close();
    numRegistros = tamanho;
}

void exibe(int num){
    
    bcp *dadosBCP = nullptr;
    int numRegistros = 0;
    
    leitura_redimensionada(dadosBCP, numRegistros);
    
    unsigned vis;
    
    if(num == 0){
        modo_de_exibir(vis);
        for (int i = 0; i < numRegistros; i++) {
           exibir_registro(dadosBCP[i], i + 1,vis);
        }
    }
    else {
        short pI = 0, pF = 0;
        cout << foreg << "Digite o ponto de incial de leitura: " << back;
        cin >> pI;

        cout << foreg << "\nDigite o ponto de parada de leitura: " << back;
        cin >> pF;

        if((pI < 0) || (pI > numRegistros) || (pF < pI)){
            cout << redS << "Intervalo de posições inválido.\n" << back;
            return;
        }
        else {
            modo_de_exibir(vis);
            for (int i = pI; i < pF; i++){
                exibir_registro(dadosBCP[i], i + 1,vis);
            }
        }
    }

    delete[] dadosBCP;
}

void modo_de_exibir(unsigned &vis){
    cout << foreg << "Você deseja visualizar o(s) registro(s) em forma de texto ou tabela?\n" << back;
    cout << foreg << "Digite 1 para TEXTO ou 2 para TABELA \n" << back;
    cin >> vis;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void exibir_registro(const bcp& artista, int posicao, unsigned vis) {
    
    if(vis == 1){

        cout << string(70, '-') << '\n';

        cout << artista.Nome << ", " << artista.Nacionalidade << ", nasceu em "
            << artista.Data_de_nascimento.dia << '/' << artista.Data_de_nascimento.mes << '/' << artista.Data_de_nascimento.ano
            << ", durante " << artista.Tempo_de_carreira << " anos de carreira,\nperformou principalmente "
            << artista.Genero << ", enquanto atuava com " << artista.Grupo_ou_Carreira_solo
            << ", participou de " << artista.Quantidade_de_albuns << " álbuns \ne compôs seu maior sucesso "
            << artista.Maior_sucesso << ", marcando seu nome na história da música e ficando "
            << "na posição " << posicao << '.' << '\n';
        
        cout << string(70, '-') << '\n';
    }

    else {
        cout << string(70, '-') << '\n';                
        cout << foreg << "Posição: " << posicao << '\n' << back;        
        cout << "Nome: " << artista.Nome << '\n'
         << "Data de nascimento: " << artista.Data_de_nascimento.dia << '/'
         << artista.Data_de_nascimento.mes << '/' << artista.Data_de_nascimento.ano << '\n'
         << "Nacionalidade: " << artista.Nacionalidade << '\n'
         << "Genero: " << artista.Genero << '\n'
         << "Maior_sucesso: " << artista.Maior_sucesso << '\n'
         << "Grupo_ou_Carreira_solo: " << artista.Grupo_ou_Carreira_solo << '\n'
         << "Quantidade de albuns de estudio: " << artista.Quantidade_de_albuns << '\n'
         << "Tempo de carreira: " << artista.Tempo_de_carreira << '\n';
        cout << string(70, '-') << '\n';
    }
}

void criar_binario (){
   
    bcp *dadosBCP = nullptr;
    int numRegistros = 0;
    
    leitura_redimensionada(dadosBCP, numRegistros);

    ofstream arq_bi("data.bin", ios::out | ios::binary);

    if(!arq_bi){
        cout << redS << "Não foi possível criar arquivo binário 'data.bin' \n" << back;
        return;
    }

    for (int i = 0; i < numRegistros; i++){

        arq_bi.write((char*) &dadosBCP[i], sizeof(bcp));
    }

    cout << green << "Arquivo binario criado com sucesso. \n" << back;

    arq_bi.close();
    delete[] dadosBCP;
}

void ler_binario(){

    ifstream arq_bin("data.bin", std::ios::binary | std::ios::ate);
    
    if (!arq_bin) {
        cout << redS << "Erro ao abrir o arquivo.\n" << back;
        return;
    }
    streamsize tamanho_arquivo = arq_bin.tellg();
    arq_bin.close();

    int tamanho_registro = sizeof(bcp);
    int numRegistros = tamanho_arquivo / tamanho_registro;
    
    bcp *dadosBCP = new bcp[numRegistros];

    ifstream arq_bi("data.bin", ios::in | ios::binary);
    
    if (!arq_bi) {
        cout << redS << "Não foi possível abrir o arquivo binário." << back << '\n';
        delete[] dadosBCP;
        return;
    }
    
    for (int i = 0; i < numRegistros; i++){
        arq_bi.read((char*) &dadosBCP[i], sizeof(bcp));
    }

    
    unsigned vis;

    modo_de_exibir(vis);

    for (int i = 0; i < numRegistros; i++) {
       exibir_registro(dadosBCP[i], i + 1, vis);
    }
    
    delete[] dadosBCP;
    arq_bi.close();
    
    cout << green << "Arquivo binario lido com sucesso. \n" << back;
}

void ordena_alfabetica(int num){
    bcp *dadosBCP = nullptr;
    int numRegistros = 0;
    
    leitura_redimensionada(dadosBCP, numRegistros);

    if(num == 0){
        quicksort_o(dadosBCP, 0, numRegistros - 1);
    }
    else{
        quicksort_n(dadosBCP, 0, numRegistros - 1);
    }

    char resp;
    cout << foreg << "Deseja salvar alteração? (S/n) \n" << back;
    cin >> resp;

    if(resp == 'S' || resp == 's'){
        ofstream arq_csv("data.csv");

        if(!arq_csv){
            cout << redS << "Não foi possível abrir o arquivo." << '\n' << back;
            return;
        }

        arq_csv << "Nome,Data_de_nascimento,Nacionalidade,Genero,Maior_sucesso,Grupo_ou_Carreira_solo," 
        << "Quantidade_de_albuns,Tempo_de_carreira," << '\n';

        for (int i = 0; i < numRegistros; i++){
            arq_csv << dadosBCP[i].Nome << ','
                    << dadosBCP[i].Data_de_nascimento.dia << '/' << dadosBCP[i].Data_de_nascimento.mes << '/' 
                    << dadosBCP[i].Data_de_nascimento.ano << ','
                    << dadosBCP[i].Nacionalidade << ','
                    << dadosBCP[i].Genero << ','
                    << dadosBCP[i].Maior_sucesso << ','
                    << dadosBCP[i].Grupo_ou_Carreira_solo << ','
                    << dadosBCP[i].Quantidade_de_albuns << ','
                    << dadosBCP[i].Tempo_de_carreira << ','
                    << '\n';
        }

        cout << green << "Alteração salva!\n" << back;
    }
}

int comparaCaseInsensitive(const char* str1, const char* str2) {
    #ifdef _WIN32
        return _stricmp(str1, str2); // Windows
    #else
        return strcasecmp(str1, str2);  // outros sistemas
    #endif
}

int particiona_obra(bcp v[], int p, int r){
    string pivo = v[r].Maior_sucesso;
    int j = p;
    int k;

    for (k = p; k < r; k++){
        if((comparaCaseInsensitive(v[k].Maior_sucesso, pivo.c_str()) <= 0)){
            swap(v[j],v[k]);
            j++;
        }
    }

    swap(v[j], v[r]);
    return j;
}

int particiona_nome(bcp v[], int p, int r){
    string pivo = v[r].Nome;
    int j = p;
    int k;

    for (k = p; k < r; k++){
        if(comparaCaseInsensitive(v[k].Nome, pivo.c_str()) <= 0){
            swap(v[j],v[k]);
            j++;
        }
    }

    swap(v[j], v[r]);
    return j;
}

void quicksort_o(bcp a[], int pos_pivo, int fim){
    int pos_novo_pivo;
    if(pos_pivo < fim){
        pos_novo_pivo = particiona_obra(a, pos_pivo, fim);
        quicksort_o(a, pos_pivo, pos_novo_pivo - 1);
        quicksort_o(a, pos_novo_pivo + 1, fim);
    }
}

void quicksort_n(bcp a[], int pos_pivo, int fim){
    int pos_novo_pivo;
    if(pos_pivo < fim){
        pos_novo_pivo = particiona_nome(a, pos_pivo, fim);
        quicksort_n(a, pos_pivo, pos_novo_pivo - 1);
        quicksort_n(a, pos_novo_pivo + 1, fim);
    }
}

int busca_binaria_o(bcp vetor[], int tam, string target) {
    
    int l = 0, r = tam - 1;
    
    while (l <= r) {

        int m = (l + r) / 2; 

        int cmp = comparaCaseInsensitive(vetor[m].Maior_sucesso, target.c_str());

        if (cmp == 0) {
            return m; 
        }
        else if (cmp < 0) {
            l = m + 1;  
        }
        else {
            r = m - 1;  
        }
    }
    return -1; 
}

int busca_binaria_n(bcp vetor[], int tam, string target) {
    
    int l = 0, r = tam - 1;
    
    while (l <= r) {
        int m = (l + r) / 2; 

        int cmp = comparaCaseInsensitive(vetor[m].Nome, target.c_str());

        if (cmp == 0) {
            return m; 
        }
        else if (cmp < 0) {
            l = m + 1;  
        }
        else {
            r = m - 1;  
        }
    }
    return -1; 
}

void inserir() {
    ofstream arq_csv("data.csv", ios::app); 
    if (!arq_csv) {
        cout << redS << "Não foi possível abrir este arquivo." << back << '\n';
        return;
    }

    bcp temp;
    char resposta;
    
    cout << foreg << "\n--- Inserindo Novo Artista ---\n" << back;
    
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Nome: ";
    cin.getline(temp.Nome, 70);

    cout << "Data de nascimento (D/M/A separados por espaco): ";
    cin >> temp.Data_de_nascimento.dia >> temp.Data_de_nascimento.mes >> temp.Data_de_nascimento.ano;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Nacionalidade: ";
    cin.getline(temp.Nacionalidade, 70);

    cout << "Genero: ";
    cin.getline(temp.Genero, 70);

    cout << "Composição de maior sucesso: ";
    cin.getline(temp.Maior_sucesso, 70);

    cout << "Grupo ou carreira solo (nome da formação): ";
    cin.getline(temp.Grupo_ou_Carreira_solo, 70);

    cout << "Quantidade de albuns de estúdio: ";
    cin >> temp.Quantidade_de_albuns;

    cout << "Tempo de carreira: ";
    cin >> temp.Tempo_de_carreira;        
    
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << foreg << "Deseja salvar este registro? (S/n) \n" << back;
    cin >> resposta;
    
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (resposta == 'S' || resposta == 's') {
        arq_csv << temp.Nome << ','
                << temp.Data_de_nascimento.dia << '/' << temp.Data_de_nascimento.mes << '/' << temp.Data_de_nascimento.ano << ','
                << temp.Nacionalidade << ','
                << temp.Genero << ','
                << temp.Maior_sucesso << ','
                << temp.Grupo_ou_Carreira_solo << ','
                << temp.Quantidade_de_albuns << ','
                << temp.Tempo_de_carreira << ','
                << '\n';
        cout << green << "Registro salvo!\n" << back;
    } 
    

    arq_csv.close();
}

void remover(){
    
    bcp *dadosBCP = nullptr;
    int numRegistros = 0;
    
    leitura_redimensionada(dadosBCP, numRegistros);
    
    cout << foreg << "\n--- Lista de Registros ---\n" << back;
    for (int i = 0; i < numRegistros; i++) {
        cout << i+1 << ". " << dadosBCP[i].Nome << '\n';
    }
    
    int posRemover;
    cout << foreg << "\nDigite o número (posição) do registro a ser removido: " << back;
    cin >> posRemover;
    
    if(posRemover < 1 || posRemover > numRegistros){
        cout << redS << "Posição inválida!" << back << '\n';
        delete[] dadosBCP;
        return;
    }

    char resp = ' ';

    cout << foreg << "Deseja salvar alteração? (S/n)" << back << '\n';
    cin >> resp;

    if(resp == 'S' || resp == 's'){

        ofstream arq_saida("data.csv");
        if (!arq_saida) {
            cout << redS << "Não foi possível abrir o arquivo para escrita." << back << '\n';
            delete[] dadosBCP;
            return;
        }
        
        arq_saida << "Nome,Data_de_nascimento,Nacionalidade,Genero,Maior_sucesso,Grupo_ou_Carreira_solo,Quantidade_de_albuns,Tempo_de_carreira," << "\n";
        
        for (int i = 0; i < numRegistros; i++) {
            if(i != posRemover - 1){
                
                arq_saida << dadosBCP[i].Nome << ','
                          << dadosBCP[i].Data_de_nascimento.dia << '/' 
                          << dadosBCP[i].Data_de_nascimento.mes << '/' 
                          << dadosBCP[i].Data_de_nascimento.ano << ','
                          << dadosBCP[i].Nacionalidade << ','
                          << dadosBCP[i].Genero << ','
                          << dadosBCP[i].Maior_sucesso << ','
                          << dadosBCP[i].Grupo_ou_Carreira_solo << ','
                          << dadosBCP[i].Quantidade_de_albuns << ','
                          << dadosBCP[i].Tempo_de_carreira << ','
                          << '\n';
            }
        }

        cout << green << "Registro removido com sucesso!" << back << '\n';        
        arq_saida.close();
        delete[] dadosBCP;
    }
    
    else{
        
        delete[] dadosBCP;
    }
}

void buscar(int num){
    bcp *dadosBCP = nullptr;
    int numRegistros = 0;
    
    leitura_redimensionada(dadosBCP, numRegistros);

    string alvo;
    
    cout << foreg << "Digite de acordo com o método escolhido: " << back;
        
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 

    getline(cin, alvo);

    unsigned vis;

    if(num == 0){
        quicksort_o(dadosBCP, 0, numRegistros - 1);

        int pos = busca_binaria_o(dadosBCP, numRegistros, alvo);

        if(pos != -1){
            modo_de_exibir(vis);
            exibir_registro(dadosBCP[pos], pos + 1, vis);
        }
        else{
            cout << redS << "Registro não encontrado \n" << back;
        }
    }
    else{
        quicksort_n(dadosBCP, 0, numRegistros - 1);

        int pos = busca_binaria_n(dadosBCP, numRegistros, alvo);

        if(pos != -1){
            modo_de_exibir(vis);
            exibir_registro(dadosBCP[pos],pos + 1, vis);

        }
        else{
            cout << redS << "Registro não encontrado \n" << back;
        }
    }


    delete[] dadosBCP;
}

void recap (){
    ifstream arq_o("recap.csv");

    if(!arq_o){
        cout << redS << "Não foi possível abrir o arquivo de recap. \n" << back;
        return;
    }

    ofstream arq_f("data.csv");

    if(!arq_f){
        cout << redS << "Não foi possível abrir o arquivo de recap. \n" << back;
        arq_o.close();
        return;  
    }

    string linha;

    while(getline(arq_o, linha)){
        arq_f << linha << '\n';
    }

    cout << green << "Arquivo 'data.csv' restaurado com sucesso!" << back << '\n';

    arq_o.close();
    arq_f.close();
}

void limparTela() {
    #ifdef _WIN32
        system("cls"); // Windows
    #else
        system("clear"); // outros sistemas
    #endif
}

void displayEncerrarPrograma(){
    cout << orange
     << "  _______________________________\n"
        " |                               |\n"
     << " |     PROGRAMA ENCERRADO        |\n"
     << " |_______________________________|\n"
     << back;
}
