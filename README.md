# **Sistema de Gerenciamento de Artistas Musicais**

## 📖 **Sobre o Projeto**

Este é um projeto em C++ que implementa um sistema de gerenciamento de dados de artistas musicais via console. O programa lê, processa e manipula registros de artistas armazenados em um arquivo CSV (`data.csv`). As principais funcionalidades incluem exibição, ordenação, busca, inserção, remoção e manipulação de arquivos binários.

O sistema foi desenvolvido como uma solução prática para aplicar conceitos de manipulação de arquivos, alocação dinâmica de memória, algoritmos de ordenação (QuickSort) e busca (Busca Binária).

-----

## ✨ **Funcionalidades**

O programa oferece um menu interativo com as seguintes opções:

  * **[1] Exibir todos os dados:** Mostra todos os registros de artistas contidos no arquivo `data.csv`.
  * **[2] Exibir um trecho dos dados:** Permite ao usuário especificar um intervalo (posição inicial e final) para visualizar uma parte dos registros.
  * **[3] Criar arquivo binário:** Gera um arquivo `data.bin` a partir dos dados atuais, oferecendo uma forma mais eficiente de armazenamento e leitura.
  * **[4] Ler arquivo binário:** Lê e exibe os dados diretamente do arquivo `data.bin`.
  * **[5] Ordenar por obra de maior sucesso:** Ordena os registros em ordem alfabética com base no nome da música de maior sucesso de cada artista.
  * **[6] Ordenar por nome do artista:** Ordena os registros em ordem alfabética com base no nome do artista.
  * **[7] Inserir novo registro:** Permite ao usuário adicionar um novo artista ao final do arquivo `data.csv`.
  * **[8] Remover um registro:** Remove um artista da lista com base em sua posição (índice).
  * **[9] Buscar por obra de maior sucesso:** Realiza uma busca binária para encontrar um artista pelo nome de sua obra de maior sucesso (requer que os dados estejam ordenados por este critério).
  * **[10] Buscar por nome do artista:** Realiza uma busca binária para encontrar um registro pelo nome do artista (requer que os dados estejam ordenados por nome).
  * **[11] Restaurar arquivo padrão:** Restaura o arquivo `data.csv` ao seu estado original, utilizando o backup `recap.csv`.

-----

## 🔧 **Estrutura dos Dados**

Os dados de cada artista são armazenados em uma `struct` e manipulados em memória. O arquivo `data.csv` deve seguir o seguinte formato, com os campos separados por vírgula:

```
Nome,Data_de_nascimento,Nacionalidade,Genero,Maior_sucesso,Grupo_ou_Carreira_solo,Quantidade_de_albuns,Tempo_de_carreira,
```

#### **Exemplo de linha no `data.csv`:**

```csv
Michael Jackson,29/8/1958,Norte-americano,Pop,Billie Jean,Carreira solo,10,45,
```

-----

## 🚀 **Como Compilar e Executar**

Para compilar e executar este projeto, você precisará de um compilador C++, como o G++.

### **Pré-requisitos**

  * Compilador G++ (ou similar) instalado.
  * Os arquivos `Codigo_Fonte.cpp`, `data.csv` e `recap.csv` devem estar no mesmo diretório.

### **Passos para Compilação**

1.  Abra o terminal ou prompt de comando.
2.  Navegue até o diretório onde os arquivos do projeto estão localizados.
3.  Execute o seguinte comando para compilar o código:
    ```sh
    g++ Codigo_Fonte.cpp -o programa
    ```
    *Isso criará um arquivo executável chamado `programa` (ou `programa.exe` no Windows).*

### **Execução**

1.  Após a compilação, execute o programa com o comando:
    ```sh
    ./programa
    ```
    *No Windows, o comando é apenas `programa`.*
2.  O programa exibirá uma mensagem de boas-vindas. Pressione 'C' para continuar e acessar o menu principal.

-----

## 🛠️ **Algoritmos e Estratégias Utilizadas**

  * **Leitura e Alocação Dinâmica:** A função `leitura_redimensionada` lê os dados do CSV e aloca dinamicamente um array de `structs`, redimensionando-o conforme necessário para acomodar todos os registros.
  * **Ordenação:** O algoritmo **QuickSort** é utilizado para ordenar os dados por nome do artista ou por obra de maior sucesso. A implementação é otimizada para ser *case-insensitive* (não diferencia maiúsculas de minúsculas).
  * **Busca:** A **Busca Binária** é implementada para encontrar registros de forma eficiente. Antes de realizar a busca, o programa garante que o conjunto de dados esteja ordenado pelo critério escolhido (nome ou obra).
  * **Compatibilidade:** O código utiliza diretivas de pré-processador (`#ifdef _WIN32`) para garantir a compatibilidade de comandos como limpar a tela (`cls`/`clear`) e comparação de strings *case-insensitive* (`_stricmp`/`strcasecmp`) entre Windows e sistemas baseados em Unix (Linux, macOS).
  
  ![Mensagem final](https://media1.giphy.com/media/v1.Y2lkPTc5MGI3NjExcm5wcjd4dzkxM2cyNTMzaWwzYTB5NnQ4N2Q1Mm9reXB2eWxwc2RrbiZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/lD76yTC5zxZPG/giphy.gif)
