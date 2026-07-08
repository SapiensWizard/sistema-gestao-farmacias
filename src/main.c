/*-------------------- SISTEMA DE GESTÃO DE FARMÁCIAS: CMD/TERMINAL --------------------*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#include<locale.h>
#include<time.h>

// ==================== CONSTANTES ====================
#define MAX_FUNCIONARIOS 30
#define ARQUIVO_FUNCIONARIOS "funcionarios.txt"
#define ARQUIVO_VENDAS "vendas.txt"
#define ARQUIVO_CLIENTES "clientes.txt"
#define ARQUIVO_PRODUTOS "produtos.txt"

// ========== DADOS PARA AUTENTICAÇÃO ==========
typedef struct {
    char login[30];
    char senha[30];
} pessoa; pessoa p[1];

// ========== CONSTANTES DO MENU ==========
typedef enum {
    GERIR_FUNCIONARIOS = 1,
    GERIR_VENDAS = 2,
    GERIR_CLIENTES = 3,
    GERIR_PRODUTOS = 4,
    LIMPAR_TELA = 5,
    SAIR = 6,
    TOTAL_OPCOES = 7
} MenuOpcoes;

// ========== ESTRUTURA PARA FUNCIONÁRIOS ==========
typedef struct {
    int codigo;
    char nome[100];
    char categoria[30];
    char telefone[20];
    char morada[200];
} Funcionario;

// ========== ESTRUTURA PARA VENDAS ==========
typedef struct {
    int codigo;
    int funcionario;
    int cliente;
    char data[20];
    float total;
} Venda;

// ========== ESTRUTURA PARA CLIENTES ==========
typedef struct {
    int codigo;
    char nome[100];
    char telefone[20];
    char morada[200];
} Cliente;

// ========== ESTRUTURA PARA PRODUTOS ==========
typedef struct {
    int codigo;
    char nome[100];
    int quantidade;
    float preco;
} Produto;

// ========== TEXTO DAS OPÇÕES DO MENU ==========
const char *operacoes[] = {
    "Gerir Funcionários",
    "Gerir as Vendas",
    "Gerir Clientes",
    "Gerir Produtos",
    "Limpar Tela",
    "Sair"
};

// ==================== PROTÓTIPOS ====================
void limpar_buffer();
void limpar_tela();
void exibir_texto_com_efeito(const char* str, int delay);

void gerir_funcionarios();
void adicionar_funcionario();
void listar_funcionarios();
void remover_funcionario();

void gerir_vendas();
void adicionar_venda();
void listar_vendas();
void remover_venda();

void gerir_clientes();
void adicionar_cliente();
void listar_clientes();
void remover_cliente();

void gerir_produtos();
void adicionar_produto();
void listar_produtos();
void remover_produto();

// ==================== MAIN ====================
int main(int argc, char *argv[]) {
    setlocale(LC_ALL, "portuguese_Brazil");
    SetConsoleTitle("Sistema de Gestão de Farmácias");
    system("color 0A");
    srand(time(NULL));
    
	char login[30];
	char senha[30];
    
    strcpy(p[0].login, "Sapiens");
    strcpy(p[0].senha, "123");
    
    printf("\nlogin: ");
    scanf("%s", login);
    
    printf("\nSenha: ");
    scanf("%s", senha);
    
    if((strcmp(login, p[0].login) == 0) && (strcmp(senha, p[0].senha) == 0)) {
    	printf("\nUsuário logado\n");
    	system("pause");
    	limpar_tela();
    	
    	MenuOpcoes opcao;
    
	    do {
		    const char* mensagem = "\nSISTEMA DE GESTÃO DE FARMÁCIAS";
		    exibir_texto_com_efeito(mensagem, 100);
		    
		    printf("\n========== MENU PRINCIPAL ==========\n");
		    
		    int i;
			for(i = GERIR_FUNCIONARIOS; i < TOTAL_OPCOES; i++) {
		        printf("[%d] %s\n", i, operacoes[i - 1]);
		    }
		    
		    printf("====================================\n");
		    
		    printf("Selecione uma opção [1-%d]: ", TOTAL_OPCOES - 1);
		    
		    if(scanf("%d", (int*)&opcao) != 1) {
		        printf("Entrada inválida! Digite apenas números inteiros.\n");
		        limpar_buffer();
		        printf("\nPressione Enter para continuar...");
		        getchar();
		        continue;
		    }
		    limpar_buffer();
		    
		    if(opcao >= GERIR_FUNCIONARIOS && opcao <= LIMPAR_TELA) {
		        switch(opcao) {
		            case GERIR_FUNCIONARIOS:
		                gerir_funcionarios();
		                break;
		            case GERIR_VENDAS:
		                gerir_vendas();
		                break;
		            case GERIR_CLIENTES:
		                gerir_clientes();
		                break;
		            case GERIR_PRODUTOS:
		                gerir_produtos();
		                break;
		            case LIMPAR_TELA:
		                limpar_tela();
		                system("pause");
		                break;
		            default:
		                break;
		        }
		    } else if(opcao != SAIR) {
		        printf("Opção inválida! Tente novamente.\n");
		        printf("\nPressione Enter para continuar...");
		        getchar();
		    }
		} while(opcao != SAIR);
	    
		printf("\nSistema de Gestão de Farmácias encerrado! Obrigado por usar.\n");
	} else {
		printf("Login e/senha incorretos");
	}
    
    return 0;
}

// ==================== FUNÇÕES UTILITÁRIAS ====================
void limpar_buffer() {
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

void limpar_tela() {
	#ifdef _WIN32
		system("cls");
	#else
		system("clear");
	#endif
}

void exibir_texto_com_efeito(const char* str, int delay) {
    const char* p;
	for(p = str; *p != '\0'; p++) {
        printf("%c", *p);
        fflush(stdout);
        
        int freq = 700 + (rand() % 400);
		Beep(freq, 25);
        
        Sleep(delay);
    }
    
    printf("\n");
}

// ==================== FUNCIONÁRIOS ====================
void gerir_funcionarios() {
    int opcao;
    
    do {
        limpar_tela();
        printf("\n========== GERIR FUNCIONÁRIOS ==========\n");
        printf("[1] Adicionar Funcionário\n");
        printf("[2] Listar Funcionários\n");
        printf("[3] Remover Funcionário\n");
        printf("[4] Voltar\n");
        printf("========================================\n");
        printf("Opção: ");
        
        scanf("%d", &opcao);
        limpar_buffer();
        
        switch(opcao) {
            case 1:
                adicionar_funcionario();
                break;
            case 2:
                listar_funcionarios();
                break;
            case 3:
                remover_funcionario();
                break;
            case 4:
                printf("\nVoltando...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
        
        if(opcao != 4) {
            printf("\nPressione Enter...");
            getchar();
        }
        
    } while(opcao != 4);
}

void adicionar_funcionario() {
    FILE *file = fopen(ARQUIVO_FUNCIONARIOS, "a");
    if(file == NULL) {
        printf("Erro ao abrir arquivo!\n");
        return;
    }
    
    Funcionario novo;
    int ultimo_codigo = 0;
    
    FILE *ler = fopen(ARQUIVO_FUNCIONARIOS, "r");
    if(ler != NULL) {
        Funcionario temp;
        while(fscanf(ler, "%d|%[^|]|%[^|]|%[^|]|%[^\n]\n", 
                     &temp.codigo, temp.nome, temp.categoria, temp.telefone, temp.morada) == 5) {
            if(temp.codigo > ultimo_codigo) ultimo_codigo = temp.codigo;
        }
        fclose(ler);
    }
    novo.codigo = ultimo_codigo + 1;
    
    printf("\n--- ADICIONAR FUNCIONÁRIO ---\n");
    printf("Código: %d\n", novo.codigo);
    
    printf("Nome: ");
    fgets(novo.nome, 100, stdin);
    novo.nome[strcspn(novo.nome, "\n")] = 0;
    
    printf("Categoria (enfermeiro/farmaceutico): ");
    fgets(novo.categoria, 30, stdin);
    novo.categoria[strcspn(novo.categoria, "\n")] = 0;
    
    printf("Telefone: ");
    fgets(novo.telefone, 20, stdin);
    novo.telefone[strcspn(novo.telefone, "\n")] = 0;
    
    printf("Morada: ");
    fgets(novo.morada, 200, stdin);
    novo.morada[strcspn(novo.morada, "\n")] = 0;
    
    fprintf(file, "%d|%s|%s|%s|%s\n", 
            novo.codigo, novo.nome, novo.categoria, novo.telefone, novo.morada);
    
    fclose(file);
    printf("\nFuncionário adicionado com sucesso!\n");
}

void listar_funcionarios() {
    FILE *file = fopen(ARQUIVO_FUNCIONARIOS, "r");
    if(file == NULL) {
        printf("\nNenhum funcionário cadastrado!\n");
        return;
    }
    
    Funcionario f;
    int contador = 0;
    
    printf("\n--- LISTA DE FUNCIONÁRIOS ---\n");
    
    while(fscanf(file, "%d|%[^|]|%[^|]|%[^|]|%[^\n]\n", 
                 &f.codigo, f.nome, f.categoria, f.telefone, f.morada) == 5) {
        printf("\nCódigo: %d\n", f.codigo);
        printf("Nome: %s\n", f.nome);
        printf("Categoria: %s\n", f.categoria);
        printf("Telefone: %s\n", f.telefone);
        printf("Morada: %s\n", f.morada);
        printf("----------------------------------------\n");
        contador++;
    }
    
    fclose(file);
    
    if(contador == 0) {
        printf("\nNenhum funcionário cadastrado!\n");
    } else {
        printf("Total: %d funcionário(s)\n", contador);
    }
}

void remover_funcionario() {
    int codigo, encontrado = 0;
    char confirmar;
    
    printf("\n--- REMOVER FUNCIONÁRIO ---\n");
    printf("Código do funcionário: ");
    scanf("%d", &codigo);
    limpar_buffer();
    
    FILE *file = fopen(ARQUIVO_FUNCIONARIOS, "r");
    if(file == NULL) {
        printf("Nenhum funcionário cadastrado!\n");
        return;
    }
    
    FILE *temp = fopen("temp_func.txt", "w");
    Funcionario f;
    
    while(fscanf(file, "%d|%[^|]|%[^|]|%[^|]|%[^\n]\n", 
                 &f.codigo, f.nome, f.categoria, f.telefone, f.morada) == 5) {
        if(f.codigo == codigo) {
            encontrado = 1;
            printf("\nFuncionário: %s - %s\n", f.nome, f.categoria);
            printf("Remover? (S/N): ");
            scanf("%c", &confirmar);
            limpar_buffer();
            
            if(confirmar == 'S' || confirmar == 's') {
                printf("\nFuncionário removido!\n");
            } else {
                fprintf(temp, "%d|%s|%s|%s|%s\n", f.codigo, f.nome, f.categoria, f.telefone, f.morada);
            }
        } else {
            fprintf(temp, "%d|%s|%s|%s|%s\n", f.codigo, f.nome, f.categoria, f.telefone, f.morada);
        }
    }
    
    fclose(file);
    fclose(temp);
    
    if(!encontrado) {
        printf("\nFuncionário não encontrado!\n");
        remove("temp_func.txt");
    } else {
        remove(ARQUIVO_FUNCIONARIOS);
        rename("temp_func.txt", ARQUIVO_FUNCIONARIOS);
    }
}

// ==================== VENDAS ====================
void gerir_vendas() {
    int opcao;
    
    do {
        limpar_tela();
        printf("\n========== GERIR VENDAS ==========\n");
        printf("[1] Adicionar Venda\n");
        printf("[2] Listar Vendas\n");
        printf("[3] Remover Venda\n");
        printf("[4] Voltar\n");
        printf("==================================\n");
        printf("Opção: ");
        scanf("%d", &opcao);
        limpar_buffer();
        
        switch(opcao) {
            case 1: adicionar_venda(); break;
            case 2: listar_vendas(); break;
            case 3: remover_venda(); break;
            case 4: printf("\nVoltando...\n"); break;
            default: printf("Opção inválida!\n");
        }
        
        if(opcao != 4) {
            printf("\nPressione Enter...");
            getchar();
        }
    } while(opcao != 4);
}

void adicionar_venda() {
    FILE *file = fopen(ARQUIVO_VENDAS, "a");
    if(file == NULL) {
        printf("Erro ao abrir arquivo!\n");
        return;
    }
    
    Venda nova;
    int ultimo = 0;
    
    FILE *ler = fopen(ARQUIVO_VENDAS, "r");
    if(ler != NULL) {
        Venda temp;
        while(fscanf(ler, "%d|%d|%d|%[^|]|%f\n", 
                     &temp.codigo, &temp.funcionario, &temp.cliente, temp.data, &temp.total) == 5) {
            if(temp.codigo > ultimo) ultimo = temp.codigo;
        }
        fclose(ler);
    }
    nova.codigo = ultimo + 1;
    
    printf("\n--- NOVA VENDA ---\n");
    printf("Código: %d\n", nova.codigo);
    
    printf("Código do Funcionário: ");
    scanf("%d", &nova.funcionario);
    
    printf("Código do Cliente: ");
    scanf("%d", &nova.cliente);
    limpar_buffer();
    
    printf("Data (dd/mm/aaaa): ");
    fgets(nova.data, 20, stdin);
    nova.data[strcspn(nova.data, "\n")] = 0;
    
    printf("Valor Total: R$ ");
    scanf("%f", &nova.total);
    
    fprintf(file, "%d|%d|%d|%s|%.2f\n", 
            nova.codigo, nova.funcionario, nova.cliente, nova.data, nova.total);
    
    fclose(file);
    printf("\nVenda registrada com sucesso!\n");
}

void listar_vendas() {
    FILE *file = fopen(ARQUIVO_VENDAS, "r");
    if(file == NULL) {
        printf("\nNenhuma venda registrada!\n");
        return;
    }
    
    Venda v;
    int cont = 0;
    float total_geral = 0;
    
    printf("\n--- LISTA DE VENDAS ---\n");
    
    while(fscanf(file, "%d|%d|%d|%[^|]|%f\n", 
                 &v.codigo, &v.funcionario, &v.cliente, v.data, &v.total) == 5) {
        printf("\nCódigo: %d | Func: %d | Cliente: %d | Data: %s | R$ %.2f\n", 
               v.codigo, v.funcionario, v.cliente, v.data, v.total);
        total_geral += v.total;
        cont++;
    }
    
    fclose(file);
    
    if(cont == 0) {
        printf("\nNenhuma venda!\n");
    } else {
        printf("\nTotal de vendas: %d | Faturamento: R$ %.2f\n", cont, total_geral);
    }
}

void remover_venda() {
    int codigo, encontrado = 0;
    char confirmar;
    
    printf("\n--- REMOVER VENDA ---\n");
    printf("Código da venda: ");
    scanf("%d", &codigo);
    limpar_buffer();
    
    FILE *file = fopen(ARQUIVO_VENDAS, "r");
    if(file == NULL) {
        printf("Nenhuma venda!\n");
        return;
    }
    
    FILE *temp = fopen("temp_v.txt", "w");
    Venda v;
    
    while(fscanf(file, "%d|%d|%d|%[^|]|%f\n", 
                 &v.codigo, &v.funcionario, &v.cliente, v.data, &v.total) == 5) {
        if(v.codigo == codigo) {
            encontrado = 1;
            printf("\nVenda: R$ %.2f - %s\n", v.total, v.data);
            printf("Remover? (S/N): ");
            scanf("%c", &confirmar);
            limpar_buffer();
            
            if(confirmar == 'S' || confirmar == 's') {
                printf("\nVenda removida!\n");
            } else {
                fprintf(temp, "%d|%d|%d|%s|%.2f\n", v.codigo, v.funcionario, v.cliente, v.data, v.total);
            }
        } else {
            fprintf(temp, "%d|%d|%d|%s|%.2f\n", v.codigo, v.funcionario, v.cliente, v.data, v.total);
        }
    }
    
    fclose(file);
    fclose(temp);
    
    if(!encontrado) {
        printf("\nVenda não encontrada!\n");
        remove("temp_v.txt");
    } else {
        remove(ARQUIVO_VENDAS);
        rename("temp_v.txt", ARQUIVO_VENDAS);
    }
}

// ==================== CLIENTES ====================
void gerir_clientes() {
    int opcao;
    
    do {
        limpar_tela();
        printf("\n========== GERIR CLIENTES ==========\n");
        printf("[1] Adicionar Cliente\n");
        printf("[2] Listar Clientes\n");
        printf("[3] Remover Cliente\n");
        printf("[4] Voltar\n");
        printf("====================================\n");
        printf("Opção: ");
        scanf("%d", &opcao);
        limpar_buffer();
        
        switch(opcao) {
            case 1: adicionar_cliente(); break;
            case 2: listar_clientes(); break;
            case 3: remover_cliente(); break;
            case 4: printf("\nVoltando...\n"); break;
            default: printf("Opção inválida!\n");
        }
        
        if(opcao != 4) {
            printf("\nPressione Enter...");
            getchar();
        }
    } while(opcao != 4);
}

void adicionar_cliente() {
    FILE *file = fopen(ARQUIVO_CLIENTES, "a");
    if(file == NULL) {
        printf("Erro ao abrir arquivo!\n");
        return;
    }
    
    Cliente novo;
    int ultimo = 0;
    
    FILE *ler = fopen(ARQUIVO_CLIENTES, "r");
    if(ler != NULL) {
        Cliente temp;
        while(fscanf(ler, "%d|%[^|]|%[^|]|%[^\n]\n", 
                     &temp.codigo, temp.nome, temp.telefone, temp.morada) == 4) {
            if(temp.codigo > ultimo) ultimo = temp.codigo;
        }
        fclose(ler);
    }
    novo.codigo = ultimo + 1;
    
    printf("\n--- NOVO CLIENTE ---\n");
    printf("Código: %d\n", novo.codigo);
    
    printf("Nome: ");
    fgets(novo.nome, 100, stdin);
    novo.nome[strcspn(novo.nome, "\n")] = 0;
    
    printf("Telefone: ");
    fgets(novo.telefone, 20, stdin);
    novo.telefone[strcspn(novo.telefone, "\n")] = 0;
    
    printf("Morada: ");
    fgets(novo.morada, 200, stdin);
    novo.morada[strcspn(novo.morada, "\n")] = 0;
    
    fprintf(file, "%d|%s|%s|%s\n", novo.codigo, novo.nome, novo.telefone, novo.morada);
    fclose(file);
    printf("\nCliente cadastrado com sucesso!\n");
}

void listar_clientes() {
    FILE *file = fopen(ARQUIVO_CLIENTES, "r");
    if(file == NULL) {
        printf("\nNenhum cliente cadastrado!\n");
        return;
    }
    
    Cliente c;
    int cont = 0;
    
    printf("\n--- LISTA DE CLIENTES ---\n");
    
    while(fscanf(file, "%d|%[^|]|%[^|]|%[^\n]\n", 
                 &c.codigo, c.nome, c.telefone, c.morada) == 4) {
        printf("\nCódigo: %d | Nome: %s | Tel: %s | Morada: %s\n", 
               c.codigo, c.nome, c.telefone, c.morada);
        cont++;
    }
    
    fclose(file);
    
    if(cont == 0) {
        printf("\nNenhum cliente!\n");
    } else {
        printf("\nTotal: %d cliente(s)\n", cont);
    }
}

void remover_cliente() {
    int codigo, encontrado = 0;
    char confirmar;
    
    printf("\n--- REMOVER CLIENTE ---\n");
    printf("Código do cliente: ");
    scanf("%d", &codigo);
    limpar_buffer();
    
    FILE *file = fopen(ARQUIVO_CLIENTES, "r");
    if(file == NULL) {
        printf("Nenhum cliente!\n");
        return;
    }
    
    FILE *temp = fopen("temp_c.txt", "w");
    Cliente c;
    
    while(fscanf(file, "%d|%[^|]|%[^|]|%[^\n]\n", 
                 &c.codigo, c.nome, c.telefone, c.morada) == 4) {
        if(c.codigo == codigo) {
            encontrado = 1;
            printf("\nCliente: %s - %s\n", c.nome, c.telefone);
            printf("Remover? (S/N): ");
            scanf("%c", &confirmar);
            limpar_buffer();
            
            if(confirmar == 'S' || confirmar == 's') {
                printf("\nCliente removido!\n");
            } else {
                fprintf(temp, "%d|%s|%s|%s\n", c.codigo, c.nome, c.telefone, c.morada);
            }
        } else {
            fprintf(temp, "%d|%s|%s|%s\n", c.codigo, c.nome, c.telefone, c.morada);
        }
    }
    
    fclose(file);
    fclose(temp);
    
    if(!encontrado) {
        printf("\nCliente não encontrado!\n");
        remove("temp_c.txt");
    } else {
        remove(ARQUIVO_CLIENTES);
        rename("temp_c.txt", ARQUIVO_CLIENTES);
    }
}

// ==================== PRODUTOS ====================
void gerir_produtos() {
    int opcao;
    
    do {
        limpar_tela();
        printf("\n========== GERIR PRODUTOS ==========\n");
        printf("[1] Adicionar Produto\n");
        printf("[2] Listar Produtos\n");
        printf("[3] Remover Produto\n");
        printf("[4] Voltar\n");
        printf("====================================\n");
        printf("Opção: ");
        scanf("%d", &opcao);
        limpar_buffer();
        
        switch(opcao) {
            case 1: adicionar_produto(); break;
            case 2: listar_produtos(); break;
            case 3: remover_produto(); break;
            case 4: printf("\nVoltando...\n"); break;
            default: printf("Opção inválida!\n");
        }
        
        if(opcao != 4) {
            printf("\nPressione Enter...");
            getchar();
        }
    } while(opcao != 4);
}

void adicionar_produto() {
    FILE *file = fopen(ARQUIVO_PRODUTOS, "a");
    if(file == NULL) {
        printf("Erro ao abrir arquivo!\n");
        return;
    }
    
    Produto novo;
    int ultimo = 0;
    
    FILE *ler = fopen(ARQUIVO_PRODUTOS, "r");
    if(ler != NULL) {
        Produto temp;
        while(fscanf(ler, "%d|%[^|]|%d|%f\n", 
                     &temp.codigo, temp.nome, &temp.quantidade, &temp.preco) == 4) {
            if(temp.codigo > ultimo) ultimo = temp.codigo;
        }
        fclose(ler);
    }
    novo.codigo = ultimo + 1;
    
    printf("\n--- NOVO PRODUTO ---\n");
    printf("Código: %d\n", novo.codigo);
    
    printf("Nome: ");
    fgets(novo.nome, 100, stdin);
    novo.nome[strcspn(novo.nome, "\n")] = 0;
    
    printf("Quantidade em estoque: ");
    scanf("%d", &novo.quantidade);
    
    printf("Preço: R$ ");
    scanf("%f", &novo.preco);
    
    fprintf(file, "%d|%s|%d|%.2f\n", novo.codigo, novo.nome, novo.quantidade, novo.preco);
    fclose(file);
    printf("\nProduto cadastrado com sucesso!\n");
}

void listar_produtos() {
    FILE *file = fopen(ARQUIVO_PRODUTOS, "r");
    if(file == NULL) {
        printf("\nNenhum produto cadastrado!\n");
        return;
    }
    
    Produto p;
    int cont = 0;
    
    printf("\n--- LISTA DE PRODUTOS ---\n");
    
    while(fscanf(file, "%d|%[^|]|%d|%f\n", 
                 &p.codigo, p.nome, &p.quantidade, &p.preco) == 4) {
        printf("\nCódigo: %d | Nome: %s | Qtd: %d | Preço: R$ %.2f\n", 
               p.codigo, p.nome, p.quantidade, p.preco);
        cont++;
    }
    
    fclose(file);
    
    if(cont == 0) {
        printf("\nNenhum produto!\n");
    } else {
        printf("\nTotal: %d produto(s)\n", cont);
    }
}

void remover_produto() {
    int codigo, encontrado = 0;
    char confirmar;
    
    printf("\n--- REMOVER PRODUTO ---\n");
    printf("Código do produto: ");
    scanf("%d", &codigo);
    limpar_buffer();
    
    FILE *file = fopen(ARQUIVO_PRODUTOS, "r");
    if(file == NULL) {
        printf("Nenhum produto!\n");
        return;
    }
    
    FILE *temp = fopen("temp_p.txt", "w");
    Produto p;
    
    while(fscanf(file, "%d|%[^|]|%d|%f\n", 
                 &p.codigo, p.nome, &p.quantidade, &p.preco) == 4) {
        if(p.codigo == codigo) {
            encontrado = 1;
            printf("\nProduto: %s - Qtd: %d - R$ %.2f\n", p.nome, p.quantidade, p.preco);
            printf("Remover? (S/N): ");
            scanf("%c", &confirmar);
            limpar_buffer();
            
            if(confirmar == 'S' || confirmar == 's') {
                printf("\nProduto removido!\n");
            } else {
                fprintf(temp, "%d|%s|%d|%.2f\n", p.codigo, p.nome, p.quantidade, p.preco);
            }
        } else {
            fprintf(temp, "%d|%s|%d|%.2f\n", p.codigo, p.nome, p.quantidade, p.preco);
        }
    }
    
    fclose(file);
    fclose(temp);
    
    if(!encontrado) {
        printf("\nProduto não encontrado!\n");
        remove("temp_p.txt");
    } else {
        remove(ARQUIVO_PRODUTOS);
        rename("temp_p.txt", ARQUIVO_PRODUTOS);
    }
}
