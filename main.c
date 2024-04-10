#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Gabriel Nottoli Buck Tia: 10425384
// Matheus Veiga Bacetic Joaquim RA: 10425638

// Estrutura padrão para um filme
struct filme {
  char nome[50];
  int ano;
  int idade;
  char genero[50];
  int rank;
};

// Variaveis Globais
#define MAX_FILMES 50
bool fim = false;
struct filme filmes[MAX_FILMES]; // Array de filmes
int num_filmes = 0;              // Contador de filmes

// Protótipo de todas funções
int menu();
int cadastroFilme();
void gravar_filme_arquivo(struct filme novo_filme);
void gravar_filme_array(struct filme novo_filme);
int menu_busca();
int busca_especifica();
void encerrar();
void escreve_filme(int, char[]);
bool removerFilmePorNome();
void listarFilmes();
void carregarCatalogo();

// ******************** Main ************************
int main() {

  void carregarCatalogo(); // Carrega os filmes do arquivo para o array

  // Loop de Execucao do Programa
  while (fim == false) {
    switch (menu()) {
    case 1: // Cadastro
      cadastroFilme();
      break;
    case 2: // Remover
      removerFilmePorNome();
      break;
    case 3: // Listar
      listarFilmes();
      // busca_especifica();
      break;
    case 4: // Sair
      encerrar();
      break;
    default: // Erro
      system("clear");
      printf("Opção Invalida, Tente novamente!\n");
      break;
    }
  }
  return 0;
}
// ************************** Funções ******************************

// Função para carregar o catálogo de filmes para o vetor a partir de um arquivo
void carregarCatalogo() {
  FILE *arquivo = fopen("filmes.txt", "r"); // Abre o arquivo para leitura
  if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo 'filmes.txt'!\n");
    return;
  }

  /* Loop para ler cada linha do arquivo e carregar os filmes no vetor fscanf lê
  uma linha do arquivo. O %49[^;] lê uma string de até 49
  caracteres que não contenha um ponto e vírgula (;). O \n
  indica o final da linha. Se fscanf conseguir ler e atribuir todos os valores
  corretamente, ele retorna o número de itens atribuídos com sucesso, que deve
  ser 5.*/
  while (fscanf(arquivo, "%49[^;];%d;%d;%49[^;];%d\n", filmes[num_filmes].nome,
                &filmes[num_filmes].ano, &filmes[num_filmes].idade,
                filmes[num_filmes].genero, &filmes[num_filmes].rank) == 5) {
    num_filmes++; // Incrementa o contador de filmes
    if (num_filmes >= MAX_FILMES) {
      printf("Limite de filmes alcançado.\n");
      break; // Sai do loop se atingir o limite máximo de filmes
    }
  }
  fclose(arquivo); // Fecha o arquivo após a leitura
}

// Lista os filmes
void listarFilmes() {
  int opcao;
  system("clear");
  // Menu de opções
  printf("********** Listagem de Filmes **********\n");
  printf("1. Listar todos os filmes\n");
  printf("2. Filtrar por título\n");
  printf("3. Filtrar por gênero\n");
  printf("4. Filtrar por classificação etária\n");
  printf("5. Voltar\n");
  printf("Opção: ");
  scanf("%d", &opcao);
  system("clear");

  /* Abrimos o arquivo "filmes.txt" no modo de leitura. Se houver algum
   * erro ao abrir o arquivo, uma mensagem de erro é exibida e a função
   * retorna.*/
  FILE *arquivo = fopen("filmes.txt", "r");
  if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo 'filmes.txt'!\n");
    return;
  }
  /*String para armazenar cada linha do arquivo.*/
  char linha[100];

  switch (opcao) {
  case 1:
    /*Caso o usuário escolha listar todos os filmes, percorremos o arquivo linha
     * por linha e imprimimos cada linha.*/
    printf("********** Todos os Filmes **********\n");
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
      printf("%s", linha);
    }
    break;

  case 2:
    /*Ao filtrar por título, pedimos ao usuário que digite o título do
     * filme. Em seguida, percorremos o arquivo e imprimimos apenas as linhas
     * que contêm o título digitado.*/
    printf("Digite o título do filme: ");
    char titulo[50];
    getchar(); // Limpa o buffer
    fgets(titulo, sizeof(titulo), stdin);
    /* strcspn é usada para encontrar o índice do primeiro
     * caractere de nova linha ('\n') na string titulo. O valor retornado por
     * strcspn é então usado como índice para definir o caractere nulo ('\0'),
     * substituindo a nova linha pelo caractere nulo. Isso remove o caractere de
     * nova linha da string, garantindo que não haja problemas ao compará-la
     * posteriormente.*/
    titulo[strcspn(titulo, "\n")] = '\0';
    system("clear");
    printf("********** Filmes com Título '%s' **********\n", titulo);
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
      /*Dentro do loop, usamos strstr para verificar se a linha contém o título
       * digitado pelo usuário. strstr procura uma substring
       * (título) dentro de uma string (linha). Se a substring
       * for encontrada, strstr retorna um ponteiro para o início da substring
       * na string original. Se não for encontrada, retorna NULL.*/
      if (strstr(linha, titulo) != NULL) {
        printf("%s", linha);
      }
    }
    break;

  case 3:
    /*Filtramos por gênero. Pedimos ao usuário que digite o gênero do filme e
     * exibimos apenas as linhas que contêm esse gênero.*/
    printf("Digite o gênero do filme: ");
    char genero[50];
    getchar();
    fgets(genero, sizeof(genero), stdin);
    genero[strcspn(genero, "\n")] = '\0';
    system("clear");
    printf("********** Filmes do Gênero '%s' **********\n", genero);
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
      if (strstr(linha, genero) != NULL) {
        printf("%s", linha);
      }
    }
    break;

  case 4:
    /*No filtro por classificação etária, pedimos ao usuário que digite a
     * classificação desejada. Em seguida, percorremos o arquivo, e para cada
     * linha, extraímos a idade do filme e a comparamos com a classificação
     * desejada. Se a idade do filme for menor ou igual à classificação,
     * imprimimos a linha.*/
    printf("Digite a classificação etária desejada: ");
    int classificacao;
    scanf("%d", &classificacao);
    system("clear");
    printf("********** Filmes com Classificação Etária %d **********\n",
           classificacao);

    /*Este é um laço continua executando enquanto a função fgets
     * conseguir ler uma linha do arquivo apontado por arquivo. A cada iteração
     * do loop, uma linha do arquivo é lida e armazenada na variável linha.*/
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
      int idade_filme;
      /*Tenta extrair a idade do filme da linha lida, usando a
       * função scanf com %*[^;];%*d;%d;. Esse formato diz ao scanf para ignorar
       * o texto até o primeiro ponto e vírgula (%*[^;]), depois ignorar um
       * número inteiro (%*d) e ENTÃO ler um inteiro e armazená-lo na variável
       * idade_filme. Este último inteiro é a idade do filme.*/
      scanf(linha, "%*[^;];%*d;%d;", &idade_filme);
      if (idade_filme <= classificacao) {
        printf("%s", linha);
      }
    }
    break;
  case 5:
    printf("Retornando ao menu anterior...\n");
    break;
  default:
    printf("Opção Inválida, tente novamente!\n");
    break;
  }

  fclose(arquivo);
}

// Menu Principal
int menu() {
  int entrada; // Utiliza o input da variável entrada para retornar um valor
               // para o switch na função main()
  printf("********** NETFLIX **********\n");
  printf("1. Cadastro de Filmes\n");
  printf("2. Remover de Filmes\n");
  printf("3. Listar Filmes\n");
  printf("4. Sair\n");
  printf("Opção: ");
  scanf("%d", &entrada);
  return entrada;
}

// Encerra o Programa por completo
void encerrar() {
  system("clear");
  printf("********** Netflix **********\n");
  printf("Obrigado por utilizar nosso sistema!\n");
  fim = true;
}

// Cadastro completo de um filme
int cadastroFilme(void) {
  system("clear"); // Limpa a tela

  struct filme novo_filme; // Variável para armazenar os dados do novo filme

  // Recebe o Nome do Filme
  printf("********** Cadastro de Filmes **********\n");
  printf("Digite o nome do filme: ");
  getchar(); // Limpa o buffer de entrada
  fgets(novo_filme.nome, sizeof(novo_filme.nome), stdin); // Lê o nome do filme
  novo_filme.nome[strcspn(novo_filme.nome, "\n")] =
      '\0'; // Remove o caractere de nova linha no final do nome

  // Recebe o ano
  printf("Digite o ano do filme: ");
  while (scanf("%d", &novo_filme.ano) !=
         1) { // Loop enquanto a entrada não for um inteiro
    printf("Digite o ano do filme com apenas inteiros: "); // Solicita a entrada
                                                           // correta
    // Limpa o buffer de entrada
    while (getchar() != '\n')
      ;
  }

  // Recebe a faixa etária
  printf("Digite a faixa etária do filme: ");
  while (scanf("%d", &novo_filme.idade) !=
         1) { // Loop enquanto a entrada não for um inteiro
    printf("Digite a faixa etária do filme com apenas inteiros: "); // Solicita
                                                                    // a entrada
                                                                    // correta
    // Limpa o buffer de entrada
    while (getchar() != '\n')
      ;
  }

  // Recebe o genero
  printf("Digite o gênero do filme: ");
  getchar(); // Limpa o buffer de entrada
  fgets(novo_filme.genero, sizeof(novo_filme.genero),
        stdin); // Lê o gênero do filme
  novo_filme.genero[strcspn(novo_filme.genero, "\n")] =
      '\0'; // Remove o caractere de nova linha no final do gênero

  // Recebe o rank/nota
  printf("Digite o rank do filme (1 a 5): ");
  while (scanf("%d", &novo_filme.rank) != 1 || novo_filme.rank < 1 ||
         novo_filme.rank > 5) {
    // Loop enquanto a entrada não for um inteiro ou não estiver no intervalo
    // válido (1 a 5)
    printf("Digite o rank do filme com apenas inteiros de 1 a 5: ");
    // Limpa o buffer de entrada
    while (getchar() != '\n')
      ;
  }

  gravar_filme_arquivo(novo_filme);
  gravar_filme_array(novo_filme);

  system("clear");
  return 0; // Retorna 0 indicando que o cadastro foi concluído com sucesso
}

// Grava as informacoes de um filme no Arquivo
void gravar_filme_arquivo(struct filme novo_filme) {
  FILE *arquivo = fopen("filmes.txt", "a");
  if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo para escrita.\n");
    return;
  }
  fprintf(arquivo, "%s;%d;%d;%s;%d\n", novo_filme.nome, novo_filme.ano,
          novo_filme.idade, novo_filme.genero, novo_filme.rank);
  fclose(arquivo);
}

// Grava as informacoes de um filme no array
void gravar_filme_array(struct filme novo_filme) {
  if (num_filmes < MAX_FILMES) {
    filmes[num_filmes] = novo_filme;
    num_filmes++;
  } else {
    printf("Limite de filmes alcançado.\n");
  }
}

// Menu para a Busca
int menu_busca() {
  system("clear");
  int entrada;
  printf("********** Busca de filmes **********\n");
  printf("1. Buscar por Nome\n");
  printf("2. Buscar por Ano de lançamento\n");
  printf("3. Buscar por Gênero\n");
  printf("4. Buscar por Classifcação\n");
  printf("5. Voltar\n");
  printf("Opção:");
  scanf("%d", &entrada);
  system("clear");
  return entrada;
}

// Busca de filmes
int busca_especifica() {
  char linha[100];
  FILE *arquivo = fopen("filmes.txt", "r");
  if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo 'filmes.txt'!\n");
    return 1;
  }

  int opcao_busca;
  while (1) {                   // Loop infinito para o menu de busca
    opcao_busca = menu_busca(); // Armazena a opção de busca do usuário

    switch (opcao_busca) {
    case 1: // Buscar por Nome
      while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        char *nome =
            strtok(linha, ";"); // Pega o primeiro item antes do ponto e vírgula

        // Verifica se encontrou o nome e imprime
        if (nome != NULL) {
          printf("Nome do filme: %s\n", nome);
        }
      }
      break;

    case 2: // Buscar por Ano de lançamento
      while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        strtok(linha, ";"); // Ignora o nome
        char *ano =
            strtok(NULL, ";"); // Pega o segundo item depois do ponto e vírgula

        // Verifica se encontrou o ano e imprime
        if (ano != NULL) {
          printf("Ano de lançamento: %s\n", ano);
        }
      }
      break;

    case 3: // Buscar por Gênero
      while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        strtok(linha, ";"); // Ignora o nome
        strtok(NULL, ";");  // Ignora o ano
        char *genero =
            strtok(NULL, ";"); // Pega o terceiro item depois do ponto e vírgula

        // Verifica se encontrou o gênero e imprime
        if (genero != NULL) {
          printf("Gênero: %s\n", genero);
        }
      }
      break;

    case 4: // Buscar por Classificação
      while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        strtok(linha, ";"); // Ignora o nome
        strtok(NULL, ";");  // Ignora o ano
        strtok(NULL, ";");  // Ignora o gênero
        char *classificacao =
            strtok(NULL, ";"); // Pega o quarto item depois do ponto e vírgula

        // Verifica se encontrou a classificação e imprime
        if (classificacao != NULL) {
          printf("Classificação: %s\n", classificacao);
        }
      }
      break;

    case 5: // Voltar ao menu
      fclose(arquivo);
      return 0;

    default: // Erro
      printf("Opção Inválida, tente novamente!\n");
      break;
    }

    getchar(); // Limpa o buffer de entrada
    printf("\nPressione Enter para continuar...\n");
    getchar();       // Aguarda o Enter para continuar
    rewind(arquivo); // Volta ao início do arquivo para próxima busca
  }

  fclose(arquivo);
  system("clear");
  return 0;
}

// Função para remover filme por nome
bool removerFilmePorNome() {
  FILE *arquivoEntrada = fopen("filmes.txt", "r");
  FILE *arquivoTemp = fopen("temp.txt", "w");

  if (arquivoEntrada == NULL || arquivoTemp == NULL) {
    printf("Erro ao abrir o arquivo!\n");
    return false;
  }

  char nome[50]; // Variável para armazenar o nome do filme a ser removido
  printf("Digite o nome do filme para remover: ");
  scanf("%s", nome); // Leitura da string

  char linha[100];
  bool filmeRemovido = false;

  while (fgets(linha, sizeof(linha), arquivoEntrada) != NULL) {
    // Faz uma cópia da linha para não alterar a original
    char linhaCopia[sizeof(linha)];
    strcpy(linhaCopia, linha);

    char *nomeArquivo =
        strtok(linhaCopia, ";"); // Extrai o nome do filme da linha

    if (strcmp(nomeArquivo, nome) ==
        0) { // Verifica se o nome coincide com o filme a ser removido
      filmeRemovido = true;
      continue; // Pula a linha a ser removida
    }

    fputs(linha, arquivoTemp); // Escreve a linha no arquivo temporário
  }

  fclose(arquivoEntrada);
  fclose(arquivoTemp);

  // Renomeia o arquivo temporário para substituir o arquivo original
  remove("filmes.txt");
  rename("temp.txt", "filmes.txt");

  if (filmeRemovido) {
    printf("Filme removido com sucesso!\n");
  } else {
    printf("O filme '%s' não foi encontrado no catálogo.\n", nome);
  }

  system("clear");
  return filmeRemovido;
}