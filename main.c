#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct
{
  int codigo;
  char nome[100];
  char endereco[150];
} Cliente;

typedef struct
{
  int codigo;
  char marca[50];
  char modelo[50];
  char placa[20];
} Veiculo;

typedef struct
{
  int codigoLocacao;
  int codigoCliente;
  int codigoVeiculo;
  char dataInicio[11]; // Formato DD/MM/AAAA
  char dataFim[11];    // Formato DD/MM/AAAA
} Locacao;

void cadastrarCliente()
{
  Cliente novoCliente;
  FILE *arquivo;

  printf("\nCadastro de Cliente\n");

  printf("Digite o código do cliente: ");
  scanf("%d", &novoCliente.codigo);
  getchar();

  printf("Digite o nome do cliente: ");
  fgets(novoCliente.nome, 100, stdin);
  novoCliente.nome[strcspn(novoCliente.nome, "\n")] = 0;

  printf("Digite o endereço do cliente: ");
  fgets(novoCliente.endereco, 150, stdin);
  novoCliente.endereco[strcspn(novoCliente.endereco, "\n")] = 0;

  arquivo = fopen("clientes.dat", "ab");
  if (arquivo == NULL)
  {
    fprintf(stderr, "Erro ao abrir o arquivo!\n");
    return;
  }

  fwrite(&novoCliente, sizeof(Cliente), 1, arquivo);

  fclose(arquivo);
  printf("Cliente cadastrado com sucesso!\n");
}

void cadastrarVeiculo()
{
  Veiculo novoVeiculo;
  FILE *arquivo;

  printf("\nCadastro de Veículo\n");

  printf("Digite o código do veículo: ");
  scanf("%d", &novoVeiculo.codigo);
  getchar();

  printf("Digite a marca do veículo: ");
  fgets(novoVeiculo.marca, 50, stdin);
  novoVeiculo.marca[strcspn(novoVeiculo.marca, "\n")] = 0;

  printf("Digite o modelo do veículo: ");
  fgets(novoVeiculo.modelo, 50, stdin);
  novoVeiculo.modelo[strcspn(novoVeiculo.modelo, "\n")] = 0;

  printf("Digite a placa do veículo: ");
  fgets(novoVeiculo.placa, 20, stdin);
  novoVeiculo.placa[strcspn(novoVeiculo.placa, "\n")] = 0;

  arquivo = fopen("veiculos.dat", "ab");
  if (arquivo == NULL)
  {
    fprintf(stderr, "Erro ao abrir o arquivo!\n");
    return;
  }

  fwrite(&novoVeiculo, sizeof(Veiculo), 1, arquivo);

  fclose(arquivo);
  printf("Veículo cadastrado com sucesso!\n");
}

void cadastrarLocacao()
{
  Locacao novaLocacao;
  FILE *arquivo;

  printf("\nCadastro de Locação\n");

  printf("Digite o código da locação: ");
  scanf("%d", &novaLocacao.codigoLocacao);
  getchar();

  printf("Digite o código do cliente: ");
  scanf("%d", &novaLocacao.codigoCliente);
  getchar();

  printf("Digite o código do veículo: ");
  scanf("%d", &novaLocacao.codigoVeiculo);
  getchar();

  printf("Digite a data de início (DD/MM/AAAA): ");
  fgets(novaLocacao.dataInicio, 11, stdin);
  novaLocacao.dataInicio[strcspn(novaLocacao.dataInicio, "\n")] = 0;

  printf("Digite a data de fim (DD/MM/AAAA): ");
  fgets(novaLocacao.dataFim, 11, stdin);
  novaLocacao.dataFim[strcspn(novaLocacao.dataFim, "\n")] = 0;

  arquivo = fopen("locacoes.dat", "ab");
  if (arquivo == NULL)
  {
    fprintf(stderr, "Erro ao abrir o arquivo!\n");
    return;
  }

  fwrite(&novaLocacao, sizeof(Locacao), 1, arquivo);

  fclose(arquivo);
  printf("Locação cadastrada com sucesso!\n");
}

struct tm converterData(char *data)
{
  struct tm tmData;
  sscanf(data, "%d/%d/%d", &tmData.tm_mday, &tmData.tm_mon, &tmData.tm_year);
  tmData.tm_mon -= 1;
  tmData.tm_year -= 1900;
  tmData.tm_isdst = -1;

  return tmData;
}

int diferencaDias(char *dataInicio, char *dataFim)
{
  struct tm tmInicio = converterData(dataInicio);
  struct tm tmFim = converterData(dataFim);

  time_t inicio = mktime(&tmInicio);
  time_t fim = mktime(&tmFim);

  return (int)difftime(fim, inicio) / (60 * 60 * 24);
}

float calcularValorLocacao(Locacao locacao)
{
  int diasLocacao = diferencaDias(locacao.dataInicio, locacao.dataFim);
  float tarifaDiaria = 100.0f;

  float valorTotal = diasLocacao * tarifaDiaria;

  return valorTotal;
}

void baixarLocacao()
{
  int codigo;
  FILE *arquivo;
  Locacao locacao;
  int encontrou = 0;
  float valorTotal;

  printf("\nBaixa de Locação\n");
  printf("Digite o código da locação: ");
  scanf("%d", &codigo);

  arquivo = fopen("locacoes.dat", "rb+");
  if (arquivo == NULL)
  {
    fprintf(stderr, "Erro ao abrir o arquivo!\n");
    return;
  }

  while (fread(&locacao, sizeof(Locacao), 1, arquivo))
  {
    if (locacao.codigoLocacao == codigo)
    {
      encontrou = 1;
      break;
    }
  }

  if (!encontrou)
  {
    printf("Locação não encontrada.\n");
  }
  else
  {

    valorTotal = calcularValorLocacao(locacao);

    printf("Valor total da locação: %.2f\n", valorTotal);
  }

  fclose(arquivo);
}

int main()
{
  int opcao;

  do
  {
    printf("\n===== LocaMais - Sistema de Locadora de Veículos =====\n");
    printf("1. Cadastrar Cliente\n");
    printf("2. Cadastrar Veículo\n");
    printf("3. Cadastrar Locação\n");
    printf("4. Baixar Locação\n");
    printf("5. Pesquisar Cliente\n");
    printf("6. Pesquisar Veículo\n");
    printf("7. Exibir Locações de um Cliente\n");
    printf("8. Calcular Pontos de Fidelidade\n");
    printf("9. [Funcionalidade Extra]\n");
    printf("0. Sair\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);

    switch (opcao)
    {
    case 1:
      cadastrarCliente();
      break;
    case 2:
      cadastrarVeiculo();
      break;
    case 3:
      cadastrarLocacao();
      break;
    case 4:
      // baixarLocacao();
      break;
    case 5:
      // pesquisarCliente();
      break;
    case 6:
      // pesquisarVeiculo();
      break;
    case 7:
      // exibirLocacoesCliente();
      break;
    case 8:
      // calcularFidelidade();
      break;
    case 9:
      // funcionalidadeExtra();
      break;
    case 0:
      printf("Saindo do sistema...\n");
      break;
    default:
      printf("Opção inválida. Por favor, tente novamente.\n");
    }
  } while (opcao != 0);

  return 0;
}