#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "locadora.h" 

typedef struct {
    int codigo_locacao;
    char data_retirada[20];
    char data_devolucao[20];
    int seguro;
    int quantidade_dias;
    int codigo_cliente;
    int codigo_veiculo;
} Locacao;

typedef struct {
    int codigo;
    char nome[50];
    char endereco[100];
    char telefone[20];
} Cliente;

#define MAX_LOCACOES 10
Locacao locacoes[MAX_LOCACOES];
int num_locacoes = 0;

#define MAX_CLIENTES 10
Cliente clientes[MAX_CLIENTES];
int num_clientes = 0;

void inicializarLocacoes() {
    Locacao loc1 = {1, "01/01/2023", "05/01/2023", 1, 5, 1, 1};
    Locacao loc2 = {2, "10/02/2023", "15/02/2023", 0, 5, 2, 2};

    locacoes[num_locacoes++] = loc1;
    locacoes[num_locacoes++] = loc2;
}



void inicializarClientes() {
    Cliente cli1 = {1, "Joao", "Rua A", "12345"};
    Cliente cli2 = {2, "Maria", "Rua B", "67890"};

    clientes[num_clientes++] = cli1;
    clientes[num_clientes++] = cli2;
}



void testCadastrarPesquisarCliente() {
    Cliente novoCliente;
    novoCliente.codigo = 1;
    strcpy(novoCliente.nome, "Joao");
    strcpy(novoCliente.endereco, "Rua A");
    strcpy(novoCliente.telefone, "12345");

    cadastrarCliente(novoCliente);

    Cliente clienteEncontrado = pesquisarClientePorCodigo(1);

    assert(clienteEncontrado.codigo == novoCliente.codigo);
    assert(strcmp(clienteEncontrado.nome, novoCliente.nome) == 0);
    assert(strcmp(clienteEncontrado.endereco, novoCliente.endereco) == 0);
    assert(strcmp(clienteEncontrado.telefone, novoCliente.telefone) == 0);
}

void testCadastrarPesquisarVeiculo() {
    Veiculo novoVeiculo;
    novoVeiculo.codigo = 1;
    strcpy(novoVeiculo.descricao, "Carro");
    strcpy(novoVeiculo.modelo, "Modelo X");
    strcpy(novoVeiculo.cor, "Vermelho");
    strcpy(novoVeiculo.placa, "ABC1234");
    novoVeiculo.valor_diaria = 100.0;
    novoVeiculo.quantidade_ocupantes = 5;
    strcpy(novoVeiculo.status, "disponivel");

    cadastrarVeiculo(novoVeiculo);

    Veiculo veiculoEncontrado = pesquisarVeiculoPorCodigo(1);

    assert(veiculoEncontrado.codigo == novoVeiculo.codigo);
    assert(strcmp(veiculoEncontrado.descricao, novoVeiculo.descricao) == 0);
    assert(strcmp(veiculoEncontrado.modelo, novoVeiculo.modelo) == 0);
    assert(strcmp(veiculoEncontrado.cor, novoVeiculo.cor) == 0);
    assert(strcmp(veiculoEncontrado.placa, novoVeiculo.placa) == 0);
    assert(veiculoEncontrado.valor_diaria == novoVeiculo.valor_diaria);
    assert(veiculoEncontrado.quantidade_ocupantes == novoVeiculo.quantidade_ocupantes);
    assert(strcmp(veiculoEncontrado.status, novoVeiculo.status) == 0);
}

void testCadastrarLocacao() {
    Locacao novaLocacao;
    novaLocacao.codigo_locacao = 1;
    strcpy(novaLocacao.data_retirada, "10/12/2023");
    strcpy(novaLocacao.data_devolucao, "15/12/2023");
    novaLocacao.seguro = 1;
    novaLocacao.quantidade_dias = 5;
    novaLocacao.codigo_cliente = 1; 
    novaLocacao.codigo_veiculo = 1; 

    cadastrarLocacao(novaLocacao);

    Locacao locacaoEncontrada = pesquisarLocacaoPorCodigo(1);

    assert(locacaoEncontrada.codigo_locacao == novaLocacao.codigo_locacao);
    assert(strcmp(locacaoEncontrada.data_retirada, novaLocacao.data_retirada) == 0);
    assert(strcmp(locacaoEncontrada.data_devolucao, novaLocacao.data_devolucao) == 0);
    assert(locacaoEncontrada.seguro == novaLocacao.seguro);
    assert(locacaoEncontrada.quantidade_dias == novaLocacao.quantidade_dias);
    assert(locacaoEncontrada.codigo_cliente == novaLocacao.codigo_cliente);
    assert(locacaoEncontrada.codigo_veiculo == novaLocacao.codigo_veiculo);
}

void testCalcularValorTotalLocacao() {
    inicializarLocacoes(); 
    float valorTotalEsperado = calcularValorTotalLocacao(1);
    assert(valorTotalEsperado >= 0);
}

void testCalcularPontosFidelidade() {
    inicializarClientes();
    int pontosFidelidade = calcularPontosFidelidade(1);
    assert(pontosFidelidade >= 0);
}

void testPesquisarClientesPremiados() {
    inicializarClientes(); 
    clientes[0].pontos_fidelidade = 500;
    clientes[1].pontos_fidelidade = 600;
    pesquisarClientesPremiados();
    assert(clientesPremiados[0].codigo == clientes[0].codigo);
    assert(clientesPremiados[1].codigo == clientes[1].codigo);
}




int main() {

    testCadastrarPesquisarCliente();
    testCadastrarPesquisarVeiculo();
    testCadastrarLocacao();
    testCalcularValorTotalLocacao();
    testCalcularPontosFidelidade();
    testPesquisarClientesPremiados();

    printf("Todos os testes foram concluídos com sucesso!\n");

    return 0;
}
