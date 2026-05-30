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
    float preco;
} Produto;

typedef struct {
    int id_venda;
    int id_cliente;
    int id_produto;
    int quantidade_adquirida;
    float valor_total_item; 
    int mes_venda; 
} Venda;

typedef struct {
    char nome_mes[15];
    float faturamento;
} MesRelatorio;

// =========================================================================
// 2. FUNÇÕES DE BUSCA E UTILIDADES
// =========================================================================

// Função NOVA para limpar lixo do teclado e evitar loop infinito
void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int buscarProduto(Produto *estoque, int total_cadastrados, int id_buscado) {
    for (int i = 0; i < total_cadastrados; i++) {
        if (estoque[i].id_produto == id_buscado) return i; 
    }
    return -1; 
}

int buscarCliente(Cliente *clientes, int total_cadastrados, int id_buscado) {
    for (int i = 0; i < total_cadastrados; i++) {
        if (clientes[i].id_cliente == id_buscado) return i;
    }
    return -1;
}

// =========================================================================
// 3. FUNÇÕES DE RELATÓRIO
// =========================================================================

void gerarRelatorioDiario(Venda vendas_dia[], int total_vendas, float faturamento_dia) {
    printf("\n=== RELATORIO DIARIO ===\n");
    if (total_vendas == 0) {
        printf("Nenhuma venda realizada hoje.\n");
    } else {
        for (int i = 0; i < total_vendas; i++) {
            printf("Pedido: %d | Produto ID: %d | Qtd: %d | Valor: R$ %.2f\n", 
                   vendas_dia[i].id_venda, vendas_dia[i].id_produto, 
                   vendas_dia[i].quantidade_adquirida, vendas_dia[i].valor_total_item);
        }
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

    for (int i = 0; i < 12; i++) {
        strcpy(relatorio[i].nome_mes, nomes[i]);
        relatorio[i].faturamento = faturamento_meses[i];
        faturamento_total_ano += faturamento_meses[i];
    }

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
// 4. FUNÇÃO PRINCIPAL (MAIN) E MENU
// =========================================================================

int main() {
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
        
        // Proteção contra letras no menu
        if (scanf("%d", &opcao_menu) != 1) {
            limpar_buffer();
            opcao_menu = -1; // Força cair no 'default' para mostrar erro
        }

        switch (opcao_menu) {
            case 1: {
                int id_temp;
                printf("\n--- CADASTRO DE LIVRO (Digite 0 para cancelar) ---\n");
                printf("ID do Livro: ");
                if (scanf("%d", &id_temp) != 1) { limpar_buffer(); printf("Entrada invalida!\n"); break; }
                if (id_temp == 0) { printf("Cadastro cancelado.\n"); break; }

                total_produtos++;
                estoque = (Produto *) realloc(estoque, total_produtos * sizeof(Produto));
                int idx = total_produtos - 1;
                
                estoque[idx].id_produto = id_temp;
                printf("Titulo (sem espacos longos): ");
                scanf("%s", estoque[idx].titulo);
                printf("Preco (Ex: 25.50): ");
                while (scanf("%f", &estoque[idx].preco) != 1) {
                    limpar_buffer();
                    printf("Preco invalido! Tente novamente: ");
                }
                printf("Livro cadastrado!\n");
                break;
            }
            case 2: {
                int id_temp;
                printf("\n--- CADASTRO DE CLIENTE (Digite 0 para cancelar) ---\n");
                printf("ID do Cliente: ");
                if (scanf("%d", &id_temp) != 1) { limpar_buffer(); printf("Entrada invalida!\n"); break; }
                if (id_temp == 0) { printf("Cadastro cancelado.\n"); break; }

                total_clientes++;
                clientes = (Cliente *) realloc(clientes, total_clientes * sizeof(Cliente));
                int idx = total_clientes - 1;
                
                clientes[idx].id_cliente = id_temp;
                printf("Nome (sem espacos longos): ");
                scanf("%s", clientes[idx].nome);
                printf("Cliente cadastrado!\n");
                break;
            }
            case 3: {
                Venda vendas_diarias[50]; 
                float faturamento_dia = 0.0;
                int qtd_vendas = 0;
                int continuar = 1;

                printf("\n--- INICIANDO VENDAS DO DIA ---\n");
                printf("Dica: Digite 0 em qualquer ID ou Mes para cancelar a transacao e voltar.\n");
                
                for (int i = 0; i < 50 && continuar == 1; i++) {
                    Venda v;
                    v.id_venda = i + 1;
                    
                    int mes_informado;
                    do {
                        printf("\nMes da venda (1-12) [0 para cancelar]: ");
                        if (scanf("%d", &mes_informado) != 1) {
                            limpar_buffer();
                            mes_informado = -1;
                        }
                    } while ((mes_informado < 0 || mes_informado > 12) && printf("Mes invalido!\n"));
                    
                    if (mes_informado == 0) { printf("Cancelando... Voltando ao menu.\n"); break; }
                    v.mes_venda = mes_informado;

                    int id_cli, idx_cli;
                    do {
                        printf("ID do Cliente [0 para cancelar]: ");
                        if (scanf("%d", &id_cli) != 1) { limpar_buffer(); id_cli = -1; }
                        if (id_cli == 0) break;
                        
                        idx_cli = buscarCliente(clientes, total_clientes, id_cli);
                        if(idx_cli == -1) printf("Cliente nao encontrado!\n");
                    } while(idx_cli == -1);
                    if (id_cli == 0) { printf("Cancelando...\n"); break; }
                    v.id_cliente = id_cli;

                    int id_prod, idx_prod;
                    do {
                        printf("ID do Livro [0 para cancelar]: ");
                        if (scanf("%d", &id_prod) != 1) { limpar_buffer(); id_prod = -1; }
                        if (id_prod == 0) break;

                        idx_prod = buscarProduto(estoque, total_produtos, id_prod);
                        if(idx_prod == -1) printf("Livro nao encontrado!\n");
                    } while(idx_prod == -1);
                    if (id_prod == 0) { printf("Cancelando...\n"); break; }
                    v.id_produto = id_prod;

                    printf("Quantidade: ");
                    while (scanf("%d", &v.quantidade_adquirida) != 1) {
                        limpar_buffer();
                        printf("Quantidade invalida! Tente novamente: ");
                    }

                    v.valor_total_item = estoque[idx_prod].preco * v.quantidade_adquirida;

                    int num_devolucao = 0;
                    printf("Numero desta devolucao (0 se for venda normal): ");
                    while (scanf("%d", &num_devolucao) != 1) {
                        limpar_buffer();
                        printf("Valor invalido! Tente novamente: ");
                    }

                    if (num_devolucao == 2) {
                        v.valor_total_item += 20.00;
                        printf("Taxa de R$ 20,00 aplicada (2a devolucao).\n");
                    }

                    vendas_diarias[i] = v;
                    faturamento_dia += v.valor_total_item;
                    faturamento_meses[v.mes_venda - 1] += v.valor_total_item;
                    qtd_vendas++;

                    printf("Deseja registrar outra venda hoje? (1-Sim / 0-Nao): ");
                    if (scanf("%d", &continuar) != 1) { limpar_buffer(); continuar = 0; }
                }
                
                gerarRelatorioDiario(vendas_diarias, qtd_vendas, faturamento_dia);
                break;
            }
            case 4: {
                gerarRelatorioMensal(faturamento_meses);
                gerarRelatorioAnual(faturamento_meses);
                break;
            }
            case 0:
                printf("Limpando memoria...\n");
                if (estoque != NULL) free(estoque);
                if (clientes != NULL) free(clientes);
                printf("Sistema encerrado!\n");
                break;
            case -1:
                printf("Opcao invalida! Digite apenas numeros.\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao_menu != 0);

    return 0;
}