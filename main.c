#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// =========================================================================
// 1. DEFINIÇÃO DAS ESTRUTURAS (STRUCTS)
// =========================================================================

typedef struct {
    int id_cliente;
    char nome[100];
} Cliente;

typedef struct {
    int id_produto;
    char titulo[150];
    float preco; // valor (preço) do produto
} Produto;

typedef struct {
    int id_venda;
    int id_cliente;
    int id_produto;
    int quantidade_adquirida;
    float valor_total_item; // cálculo do valor total de cada item
    int mes_venda; 
} Venda;

typedef struct {
    char nome_mes[15];
    float faturamento;
} MesRelatorio;

// =========================================================================
// 2. FUNÇÕES DE BUSCA E VALIDAÇÃO
// =========================================================================

int buscarProduto(Produto *estoque, int total_cadastrados, int id_buscado) {
    for (int i = 0; i < total_cadastrados; i++) {
        if (estoque[i].id_produto == id_buscado) {
            return i; 
        }
    }
    return -1; 
}

int buscarCliente(Cliente *clientes, int total_cadastrados, int id_buscado) {
    for (int i = 0; i < total_cadastrados; i++) {
        if (clientes[i].id_cliente == id_buscado) {
            return i;
        }
    }
    return -1;
}

// =========================================================================
// 3. FUNÇÕES DE RELATÓRIO
// =========================================================================

void gerarRelatorioDiario(Venda vendas_dia[], int total_vendas, float faturamento_dia) {
    printf("\n=== RELATORIO DIARIO ===\n");
    for (int i = 0; i < total_vendas; i++) {
        printf("Pedido: %d | Produto ID: %d | Qtd: %d | Valor: R$ %.2f\n", 
               vendas_dia[i].id_venda, vendas_dia[i].id_produto, 
               vendas_dia[i].quantidade_adquirida, vendas_dia[i].valor_total_item);
    }
    printf("Valor total das vendas diarias: R$ %.2f\n", faturamento_dia);
    printf("========================\n");
}

void gerarRelatorioMensal(float faturamento_meses[]) {
    char meses[12][10] = {"Jan", "Fev", "Mar", "Abr", "Mai", "Jun", 
                          "Jul", "Ago", "Set", "Out", "Nov", "Dez"};
    float valor_total_consolidado = 0.0;
    
    printf("\n=== RELATORIO MENSAL ===\n");
    for (int i = 0; i < 12; i++) {
        printf("%s: R$ %.2f\n", meses[i], faturamento_meses[i]);
        valor_total_consolidado += faturamento_meses[i];
    }
    printf("Valor Total Consolidado: R$ %.2f\n", valor_total_consolidado);
    printf("========================\n");
}

void gerarRelatorioAnual(float faturamento_meses[]) {
    MesRelatorio relatorio[12];
    MesRelatorio auxiliar;
    float faturamento_total_ano = 0.0;
    char nomes[12][15] = {"Janeiro", "Fevereiro", "Marco", "Abril", "Maio", "Junho", 
                          "Julho", "Agosto", "Setembro", "Outubro", "Novembro", "Dezembro"};

    // Transferindo os dados para a struct auxiliar
    for (int i = 0; i < 12; i++) {
        strcpy(relatorio[i].nome_mes, nomes[i]);
        relatorio[i].faturamento = faturamento_meses[i];
        faturamento_total_ano += faturamento_meses[i];
    }

    // Algoritmo de Ordenacao (Bubble Sort - Ordem Decrescente)
    for (int i = 0; i < 11; i++) {
        for (int j = 0; j < 11 - i; j++) {
            if (relatorio[j].faturamento < relatorio[j + 1].faturamento) {
                auxiliar = relatorio[j];
                relatorio[j] = relatorio[j + 1];
                relatorio[j + 1] = auxiliar;
            }
        }
    }

    printf("\n=== RELATORIO ANUAL (DECRESCENTE) ===\n");
    for (int i = 0; i < 12; i++) {
        printf("%d. %s - R$ %.2f\n", i + 1, relatorio[i].nome_mes, relatorio[i].faturamento);
    }
    printf("Faturamento Total do Ano: R$ %.2f\n", faturamento_total_ano);
    printf("=====================================\n");
}

// =========================================================================
// 4. FUNCAO PRINCIPAL (MAIN) E MENU
// =========================================================================

int main() {
    // Ponteiros para alocacao dinamica
    Produto *estoque = NULL;
    Cliente *clientes = NULL;
    
    int total_produtos = 0, total_clientes = 0;
    float faturamento_meses[12] = {0.0};
    
    int opcao_menu;

    do {
        printf("\n=== SISTEMA RE-LER: SEBO E BIBLIOTECA ===\n");
        printf("1. Cadastrar Novo Livro\n");
        printf("2. Cadastrar Novo Cliente\n");
        printf("3. Iniciar Expediente de Vendas\n");
        printf("4. Gerar Relatorios\n");
        printf("0. Encerrar Sistema\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao_menu);

        switch (opcao_menu) {
            case 1: {
                total_produtos++;
                estoque = (Produto *) realloc(estoque, total_produtos * sizeof(Produto));
                int idx = total_produtos - 1;
                
                printf("ID do Livro: ");
                scanf("%d", &estoque[idx].id_produto);
                printf("Titulo (sem espacos longos): ");
                scanf("%s", estoque[idx].titulo);
                printf("Preco (Ex: 25.50): ");
                scanf("%f", &estoque[idx].preco);
                printf("Livro cadastrado!\n");
                break;
            }
            case 2: {
                total_clientes++;
                clientes = (Cliente *) realloc(clientes, total_clientes * sizeof(Cliente));
                int idx = total_clientes - 1;
                
                printf("ID do Cliente: ");
                scanf("%d", &clientes[idx].id_cliente);
                printf("Nome (sem espacos longos): ");
                scanf("%s", clientes[idx].nome);
                printf("Cliente cadastrado!\n");
                break;
            }
            case 3: {
                // A loja realiza 50 vendas por dia
                Venda vendas_diarias[50]; 
                float faturamento_dia = 0.0;
                int qtd_vendas = 0;
                int continuar = 1;

                printf("\n--- INICIANDO VENDAS DO DIA ---\n");
                
                // Laco de ate 50 vendas
                for (int i = 0; i < 50 && continuar == 1; i++) {
                    Venda v;
                    v.id_venda = i + 1;
                    
                    int mes_informado;
                    do {
                        printf("Mes da venda (1-12): ");
                        scanf("%d", &mes_informado);
                    } while (mes_informado < 1 || mes_informado > 12);
                    v.mes_venda = mes_informado;

                    int id_cli, idx_cli;
                    do {
                        printf("ID do Cliente: ");
                        scanf("%d", &id_cli);
                        idx_cli = buscarCliente(clientes, total_clientes, id_cli);
                        if(idx_cli == -1) printf("Cliente nao encontrado!\n");
                    } while(idx_cli == -1);
                    v.id_cliente = id_cli;

                    int id_prod, idx_prod;
                    do {
                        printf("ID do Livro: ");
                        scanf("%d", &id_prod);
                        idx_prod = buscarProduto(estoque, total_produtos, id_prod);
                        if(idx_prod == -1) printf("Livro nao encontrado!\n");
                    } while(idx_prod == -1);
                    v.id_produto = id_prod;

                    printf("Quantidade: ");
                    scanf("%d", &v.quantidade_adquirida);

                    // Calculo base
                    v.valor_total_item = estoque[idx_prod].preco * v.quantidade_adquirida;

                    // Regra de Negocio: Devolucao
                    int num_devolucao;
                    printf("Se for devolucao, qual o numero desta devolucao para este cliente? (Digite 0 se for venda normal): ");
                    scanf("%d", &num_devolucao);

                    if (num_devolucao == 2) {
                        v.valor_total_item += 20.00; // Taxa fixa da transportadora
                        printf("Taxa de R$ 20,00 aplicada (2a devolucao).\n");
                    }

                    // Armazenando a venda no dia e no mes
                    vendas_diarias[i] = v;
                    faturamento_dia += v.valor_total_item;
                    faturamento_meses[v.mes_venda - 1] += v.valor_total_item;
                    qtd_vendas++;

                    printf("Deseja registrar outra venda hoje? (1-Sim / 0-Nao): ");
                    scanf("%d", &continuar);
                }
                
                // Gera o relatorio diario logo apos encerrar o expediente
                gerarRelatorioDiario(vendas_diarias, qtd_vendas, faturamento_dia);
                break;
            }
            case 4: {
                gerarRelatorioMensal(faturamento_meses);
                gerarRelatorioAnual(faturamento_meses);
                break;
            }
            case 0:
                printf("Limpando memoria (free)...\n");
                if (estoque != NULL) free(estoque);
                if (clientes != NULL) free(clientes);
                printf("Sistema encerrado!\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao_menu != 0);

    return 0;
}