#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CLIENTES 100
#define MAX_VEICULOS 100
#define MAX_LOCACOES 100

typedef struct {
    int codigo;
    char nome[50];
    char endereco[100];
    char telefone[20];
} Cliente;

typedef struct {
    int codigo;
    char descricao[50];
    char modelo[50];
    char cor[20];
    char placa[15];
    float valor_diaria;
    int quantidade_ocupantes;
    char status[20]; 
} Veiculo;

typedef struct {
    int codigo_locacao;
    char data_retirada[11]; 
    char data_devolucao[11]; 
    int seguro;
    int quantidade_dias;
    int codigo_cliente;
    int codigo_veiculo;
} Locacao;

typedef struct {
    int dia;
    int mes;
    int ano;
} Data;


Cliente clientes[MAX_CLIENTES];
Veiculo veiculos[MAX_VEICULOS];
Locacao locacoes[MAX_LOCACOES];

int num_clientes = 0;
int num_veiculos = 0;
int num_locacoes = 0;

int verificarCodigoClienteExistente(int codigo) {
    for (int i = 0; i < num_clientes; ++i) {
        if (clientes[i].codigo == codigo) {
            return 1; 
        }
    }
    return 0; 
}

int gerarNovoCodigoCliente() {
    return num_clientes + 1; 
}


int codigoClientePorNome(char nome[]) {
    for (int i = 0; i < num_clientes; ++i) {
        if (strcmp(clientes[i].nome, nome) == 0) {
            return clientes[i].codigo; 
        }
    }
    return -1; 
}

void cadastrarCliente() {
    if (num_clientes >= MAX_CLIENTES) {
        printf("Limite de clientes atingido.\n");
        return;
    }

    Cliente novoCliente;

    printf("Digite o nome do cliente: ");
    scanf("%s", novoCliente.nome);
    printf("Digite o endereco do cliente: ");
    scanf("%s", novoCliente.endereco);
    printf("Digite o telefone do cliente: ");
    scanf("%s", novoCliente.telefone);

    int novoCodigo = gerarNovoCodigoCliente();
    while (verificarCodigoClienteExistente(novoCodigo)) {
        novoCodigo = gerarNovoCodigoCliente(); 
    }

    novoCliente.codigo = novoCodigo;
    clientes[num_clientes] = novoCliente;
    num_clientes++;

    printf("Cliente cadastrado com sucesso!\n");
}

int verificarCodigoVeiculoExistente(int codigo) {
    for (int i = 0; i < num_veiculos; ++i) {
        if (veiculos[i].codigo == codigo) {
            return 1; 
        }
    }
    return 0; 
}

int gerarNovoCodigoVeiculo() {
    return num_veiculos + 1; 
}

void cadastrarVeiculo() {
    if (num_veiculos >= MAX_VEICULOS) {
        printf("Limite de veiculos atingido.\n");
        return;
    }

    Veiculo novoVeiculo;

    printf("Digite a descricao do veiculo: ");
    scanf("%s", novoVeiculo.descricao);
    printf("Digite o modelo do veiculo: ");
    scanf("%s", novoVeiculo.modelo);
    printf("Digite a cor do veiculo: ");
    scanf("%s", novoVeiculo.cor);
    printf("Digite a placa do veiculo: ");
    scanf("%s", novoVeiculo.placa);
    printf("Digite o valor da diaria do veiculo: ");
    scanf("%f", &novoVeiculo.valor_diaria);
    printf("Digite a quantidade de ocupantes do veiculo: ");
    scanf("%d", &novoVeiculo.quantidade_ocupantes);
    printf("Digite o status do veiculo (alugado, disponivel ou em manutencao): ");
    scanf("%s", novoVeiculo.status);

    int novoCodigo = gerarNovoCodigoVeiculo();
    while (verificarCodigoVeiculoExistente(novoCodigo)) {
        novoCodigo = gerarNovoCodigoVeiculo(); 
    }

    novoVeiculo.codigo = novoCodigo;
    veiculos[num_veiculos] = novoVeiculo;
    num_veiculos++;

    printf("Veiculo cadastrado com sucesso!\n");
}

int buscarVeiculoDisponivel() {

    for (int i = 0; i < num_veiculos; ++i) {
        if (strcmp(veiculos[i].status, "disponivel") == 0) {
            return i; 
        }
    }
    return -1;
}

void cadastrarLocacao() {
    if (num_locacoes >= MAX_LOCACOES) {
        printf("Limite de locacoes atingido.\n");
        return;
    }
    char nomeCliente[50];
    Locacao novaLocacao;
    printf("Digite o nome do cliente: "); 
    printf("Digite a data de retirada (DD/MM/AAAA): ");
    scanf("%s", novaLocacao.data_retirada);
    printf("Digite a data de devolucao (DD/MM/AAAA): ");
    scanf("%s", novaLocacao.data_devolucao);
    printf("Digite a quantidade de ocupantes: ");
    scanf("%d", &novaLocacao.quantidade_dias);
    printf("O cliente deseja contratar um seguro? (1 para sim, 0 para nao): ");
    scanf("%d", &novaLocacao.seguro);
    printf("Digite o nome do cliente: ");
    scanf("%s", nomeCliente);
    int indiceVeiculoDisponivel = buscarVeiculoDisponivel();
    if (indiceVeiculoDisponivel == -1) {
        printf("Desculpe, nenhum veiculo disponivel no momento.\n");
        return;
    }
    int codigoCliente = codigoClientePorNome(nomeCliente);
    if (codigoCliente == -1) {
        printf("Cliente nao encontrado.\n");
        return;
    }
    novaLocacao.codigo_cliente = codigoCliente;
    novaLocacao.codigo_veiculo = veiculos[indiceVeiculoDisponivel].codigo;
    locacoes[num_locacoes] = novaLocacao;
    strcpy(veiculos[indiceVeiculoDisponivel].status, "alugado");
    num_locacoes++;
    printf("Locacao cadastrada com sucesso!\n");
}

int encontrarLocacaoPorCodigoCliente(int codigoCliente) {
    for (int i = 0; i < num_locacoes; ++i) {
        if (locacoes[i].codigo_cliente == codigoCliente) {
            return i; 
        }
    }
    return -1; 
}

Data converterStringParaData(const char *dataString) {
    Data data;
    sscanf(dataString, "%d/%d/%d", &data.dia, &data.mes, &data.ano);
    return data;
}

int calcularDiferencaDatas(const char data1[], const char data2[]) {
    Data primeiraData = converterStringParaData(data1);
    Data segundaData = converterStringParaData(data2);
    const int diasPorMes[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int totalDiasData1 = primeiraData.ano * 365 + primeiraData.dia;
    for (int i = 0; i < primeiraData.mes; ++i) {
        totalDiasData1 += diasPorMes[i];
    }
    totalDiasData1 += (primeiraData.ano / 4) - (primeiraData.ano / 100) + (primeiraData.ano / 400);
    int totalDiasData2 = segundaData.ano * 365 + segundaData.dia;
    for (int i = 0; i < segundaData.mes; ++i) {
        totalDiasData2 += diasPorMes[i];
    }
    totalDiasData2 += (segundaData.ano / 4) - (segundaData.ano / 100) + (segundaData.ano / 400);
    return abs(totalDiasData2 - totalDiasData1);
}

void darBaixaLocacao() {
    int codigoCliente;
    printf("Digite o codigo do cliente: ");
    scanf("%d", &codigoCliente);
    int indiceLocacao = encontrarLocacaoPorCodigoCliente(codigoCliente);
    if (indiceLocacao == -1) {
        printf("Locacao nao encontrada para o cliente.\n");
        return;
    }
    Locacao locacao = locacoes[indiceLocacao];
    char dataEntrega[11];
    printf("Digite a data de entrega do veiculo (DD/MM/AAAA): ");
    scanf("%s", dataEntrega);
    int diasAtraso = calcularDiferencaDatas(dataEntrega, locacao.data_devolucao);
    float valorTotal = locacao.quantidade_dias * veiculos[locacao.codigo_veiculo].valor_diaria;
    if (diasAtraso > 0) {
        float multa = (0.05 * valorTotal) + (30 * diasAtraso);
        valorTotal += multa;
    }
    strcpy(veiculos[locacao.codigo_veiculo].status, "disponivel");
    printf("Valor total a ser pago: %.2f\n", valorTotal);
}

void pesquisarClientePorNome(const char nome[]) {
    int encontrado = 0;

    for (int i = 0; i < num_clientes; ++i) {
        if (strcmp(clientes[i].nome, nome) == 0) {
            printf("Cliente Encontrado:\n");
            printf("Código: %d\n", clientes[i].codigo);
            printf("Nome: %s\n", clientes[i].nome);
            printf("Endereco: %s\n", clientes[i].endereco);
            printf("Telefone: %s\n", clientes[i].telefone);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Cliente nao encontrado.\n");
    }
}

void pesquisarClientePorCodigo(int codigo) {
    int encontrado = 0;

    for (int i = 0; i < num_clientes; ++i) {
        if (clientes[i].codigo == codigo) {
            printf("Cliente Encontrado:\n");
            printf("Código: %d\n", clientes[i].codigo);
            printf("Nome: %s\n", clientes[i].nome);
            printf("Endereco: %s\n", clientes[i].endereco);
            printf("Telefone: %s\n", clientes[i].telefone);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Cliente nao encontrado.\n");
    }
}

void pesquisarCliente() {
    int opcao;
    printf("Selecione a opcao de pesquisa:\n");
    printf("1. Pesquisar por nome\n");
    printf("2. Pesquisar por código\n");
    printf("Opcao: ");
    scanf("%d", &opcao);

    switch (opcao) {
        case 1: {
            char nome[50];
            printf("Digite o nome do cliente: ");
            scanf("%s", nome);
            pesquisarClientePorNome(nome);
            break;
        }
        case 2: {
            int codigo;
            printf("Digite o código do cliente: ");
            scanf("%d", &codigo);
            pesquisarClientePorCodigo(codigo);
            break;
        }
        default:
            printf("Opcao invalida!\n");
            break;
    }
}
void pesquisarVeiculoPorDescricao(const char descricao[]) {
    int encontrado = 0;

    for (int i = 0; i < num_veiculos; ++i) {
        if (strcmp(veiculos[i].descricao, descricao) == 0) {
            printf("Veiculo Encontrado:\n");
            printf("Código: %d\n", veiculos[i].codigo);
            printf("Descrição: %s\n", veiculos[i].descricao);
            printf("Modelo: %s\n", veiculos[i].modelo);
            printf("Cor: %s\n", veiculos[i].cor);
            printf("Placa: %s\n", veiculos[i].placa);
            printf("Valor da Diária: %.2f\n", veiculos[i].valor_diaria);
            printf("Quantidade de Ocupantes: %d\n", veiculos[i].quantidade_ocupantes);
            printf("Status: %s\n", veiculos[i].status);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Veiculo nao encontrado.\n");
    }
}

void pesquisarVeiculoPorCodigo(int codigo) {
    int encontrado = 0;

    for (int i = 0; i < num_veiculos; ++i) {
        if (veiculos[i].codigo == codigo) {
            printf("Veiculo Encontrado:\n");
            printf("Código: %d\n", veiculos[i].codigo);
            printf("Descrição: %s\n", veiculos[i].descricao);
            printf("Modelo: %s\n", veiculos[i].modelo);
            printf("Cor: %s\n", veiculos[i].cor);
            printf("Placa: %s\n", veiculos[i].placa);
            printf("Valor da Diária: %.2f\n", veiculos[i].valor_diaria);
            printf("Quantidade de Ocupantes: %d\n", veiculos[i].quantidade_ocupantes);
            printf("Status: %s\n", veiculos[i].status);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        printf("Veiculo nao encontrado.\n");
    }
}

void pesquisarVeiculo() {
    int opcao;
    printf("Selecione a opcao de pesquisa:\n");
    printf("1. Pesquisar por descrição\n");
    printf("2. Pesquisar por código\n");
    printf("Opcao: ");
    scanf("%d", &opcao);

    switch (opcao) {
        case 1: {
            char descricao[50];
            printf("Digite a descricao do veiculo: ");
            scanf("%s", descricao);
            pesquisarVeiculoPorDescricao(descricao);
            break;
        }
        case 2: {
            int codigo;
            printf("Digite o código do veiculo: ");
            scanf("%d", &codigo);
            pesquisarVeiculoPorCodigo(codigo);
            break;
        }
        default:
            printf("Opcao invalida!\n");
            break;
    }
}


void mostrarLocacoesCliente(int codigoCliente) {
    int encontradas = 0;

    printf("Locacoes do Cliente:\n");
    for (int i = 0; i < num_locacoes; ++i) {
        if (locacoes[i].codigo_cliente == codigoCliente) {
            printf("Locacao %d:\n", i + 1);
            printf("Codigo da Locacao: %d\n", locacoes[i].codigo_locacao);
            printf("Data de Retirada: %s\n", locacoes[i].data_retirada);
            printf("Data de Devolucao: %s\n", locacoes[i].data_devolucao);
            printf("Seguro: %s\n", locacoes[i].seguro ? "Sim" : "Nao");
            printf("Quantidade de Dias: %d\n", locacoes[i].quantidade_dias);
            printf("Codigo do Veiculo: %d\n", locacoes[i].codigo_veiculo);
            encontradas = 1;
        }
    }

    if (!encontradas) {
        printf("Nenhuma locacao encontrada para este cliente.\n");
    }
}

int encontrarClientePorCodigo(int codigo) {
    for (int i = 0; i < num_clientes; ++i) {
        if (clientes[i].codigo == codigo) {
            return codigo; 
        }
    }
    return -1; 
}

void mostrarLocacoesClientePorCodigo() {
    int codigoCliente;
    printf("Digite o codigo do cliente: ");
    scanf("%d", &codigoCliente);

    int codigoEncontrado = encontrarClientePorCodigo(codigoCliente);

    if (codigoEncontrado == -1) {
        printf("Cliente nao encontrado.\n");
        return;
    }

    mostrarLocacoesCliente(codigoEncontrado);
}

int calcularPontosFidelidade(int codigo_cliente) {
    int totalPontos = 0;

    for (int i = 0; i < num_locacoes; ++i) {
        if (locacoes[i].codigo_cliente == codigo_cliente) {
            int diasLocacao = calcularDiferencaDatas(locacoes[i].data_retirada, locacoes[i].data_devolucao);
            totalPontos += diasLocacao * 10;
        }
    }

    return totalPontos;
}


void pesquisarClientesPremiados() {
    printf("Clientes Premiados:\n");

    for (int i = 0; i < num_clientes; ++i) {
        int pontosFidelidade = calcularPontosFidelidade(clientes[i].codigo);
        
        if (pontosFidelidade >= 500) {
            printf("Cliente: %s - Código: %d - Pontos de Fidelidade: %d\n", 
                   clientes[i].nome, clientes[i].codigo, pontosFidelidade);
            printf("Parabéns! Este cliente atingiu 500 pontos e é elegível para o prêmio.\n");
        }
    }
}


int main() {
    int opcao;
    int codigo;
    printf("Selecione a opcao desejada:\n");
    printf("1. Cadastrar Cliente\n");
    printf("2. Cadastrar Veiculo\n");
    printf("3. Cadastrar Locacao\n");
    printf("4. Dar Baixa em Locacao\n");
    printf("5. Pesquisar Cliente\n");
    printf("6. Pesquisar Veiculo\n");
    printf("7. Mostrar Locacoes de um Cliente\n");
    printf("8. Calcular Pontos de Fidelidade de um Cliente\n");
    printf("9. Pesquisar Clientes Premiados\n");
    printf("0. Sair\n");
    printf("Opcao: ");
    scanf("%d", &opcao);

    while(opcao != 0){
        switch (opcao) {
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
                darBaixaLocacao();
                break;
            case 5:
                pesquisarCliente();
                break;
            case 6:
                pesquisarVeiculo();
                break;
            case 7:
                mostrarLocacoesClientePorCodigo();
                break;
            case 8:
                printf("Digite o código do cliente: ");
                scanf("%d", &codigo);
                int pts = calcularPontosFidelidade(codigo);
                printf("Pontos de Fidelidade: %d\n", pts);
                break;
            case 9:
                pesquisarClientesPremiados();
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
                break;
        }

            printf("Selecione a opcao desejada:\n");
            printf("1. Cadastrar Cliente\n");
            printf("2. Cadastrar Veiculo\n");
            printf("3. Cadastrar Locacao\n");
            printf("4. Dar Baixa em Locacao\n");
            printf("5. Pesquisar Cliente\n");
            printf("6. Pesquisar Veiculo\n");
            printf("7. Mostrar Locacoes de um Cliente\n");
            printf("8. Calcular Pontos de Fidelidade de um Cliente\n");
            printf("9. Pesquisar Clientes Premiados\n");
            printf("0. Sair\n");
            printf("Opcao: ");
            scanf("%d", &opcao);
    }
}
