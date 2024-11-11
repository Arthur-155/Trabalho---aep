//Fazer um MENU com apenas 1 opção, no caso a de criptografar, dentro dela (da opção) inserir mais algumas opcoes; - feito
//fazer os arquivos irem para o bloco de notas  e armazenar todas as senhas escritas - feito
//mudança de planos, aparentemente é pra fazer um CRUD.  - feito 
//exibir na tela o usuario e senha senha(a senha criptografada) ao invés da pasta
//dentro da função onde mostra as senhas criptografadas, adicionar uma função onde ela descriptografa todas as senhas.
//adicionar funcao para alterar usuario
//organizar o programa


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define MAX_USUARIOS 100
#define MAX_LEN 256
#define NOME_ARQUIVO "criptografias.txt"

typedef struct {
    char nomeDeUsuario[MAX_LEN];
    char senha[MAX_LEN];
    char senhaCriptografada[MAX_LEN];
} Usuario;

Usuario usuarios[MAX_USUARIOS];
int quantidadeUsuarios = 0;
const int VALOR_SHIFT = 3; 

//---------------------------------------------------------------------------------------------------------------------------------------------------------------

void criptografarSenha(char *entrada, char *saida) {
	int i;
    for (i = 0; i < strlen(entrada); i++) {
        saida[i] = entrada[i] + VALOR_SHIFT;
    }
    saida[strlen(entrada)] = '\0';  
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------

void descriptografarSenha(char *entrada, char *saida) {
	int i;
    for (i = 0; i < strlen(entrada); i++) {
        saida[i] = entrada[i] - VALOR_SHIFT;
    }
    saida[strlen(entrada)] = '\0';  
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------

void exibirSenhasCriptografadas() {
	int i;
    int escolha;
    char senhaDescriptografada[MAX_LEN];
    
    printf("Deseja descriptografar as senhas? (1 - Sim, 0 - Não): ");
    scanf("%d", &escolha);

    switch (escolha) {
        case 1:  
        system("cls");
        	printf("---------------------------------LISTA------------------------------");
        	printf("\n\n");
            for (i = 0; i < quantidadeUsuarios; i++) {
                descriptografarSenha(usuarios[i].senhaCriptografada, senhaDescriptografada);
                printf(" Usuário: %s \n Senha Criptografada: %s \n Senha Descriptografada: %s\n",usuarios[i].nomeDeUsuario, usuarios[i].senhaCriptografada, senhaDescriptografada);
                printf("--------------------------------------------------------------------\n");
            }
            break;
        case 0:  
        system("cls");
            for (i = 0; i < quantidadeUsuarios; i++) {
                printf("Usuário: %s | Senha Criptografada: %s\n",usuarios[i].nomeDeUsuario, usuarios[i].senhaCriptografada);
            }
            break;
        
        default:  
            printf("Opção inválida.\n");
            break;
    }
}



//---------------------------------------------------------------------------------------------------------------------------------------------------------------

void salvarSenhasCriptografadas() {
	system("cls");
    FILE *arquivo = fopen(NOME_ARQUIVO, "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para salvar as senhas.\n");
        return;
    }
	int i;
    for (i = 0; i < quantidadeUsuarios; i++) {
        fprintf(arquivo, "Usuário: %s | Senha Criptografada: %s\n", usuarios[i].nomeDeUsuario, usuarios[i].senhaCriptografada);
    }

    fclose(arquivo);
    printf("Senhas criptografadas salvas com sucesso.\n");
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------

void carregarUsuarios() {
    FILE *arquivo = fopen(NOME_ARQUIVO, "r");
    if (arquivo == NULL) {
        printf("Nenhum arquivo encontrado. Um novo será criado.\n");
        return;
    }

    char linha[256];
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        sscanf(linha, "Usuário: %s | Senha Criptografada: %s\n", usuarios[quantidadeUsuarios].nomeDeUsuario, usuarios[quantidadeUsuarios].senhaCriptografada);
        descriptografarSenha(usuarios[quantidadeUsuarios].senhaCriptografada, usuarios[quantidadeUsuarios].senha);
        quantidadeUsuarios++;
    }
    fclose(arquivo);
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------

void criarUsuario() {
	system("cls");
    char nomeDeUsuario[MAX_LEN], senha[MAX_LEN];

    printf("Digite o nome de usuário: ");
    scanf("%s", nomeDeUsuario);
    printf("Digite a senha: ");
    scanf("%s", senha);
	
	int i;
    for (i = 0; i < quantidadeUsuarios; i++) {
        if (strcmp(usuarios[i].nomeDeUsuario, nomeDeUsuario) == 0) {
            printf("Usuário já existe.\n");
            return;
        }
    }

    strcpy(usuarios[quantidadeUsuarios].nomeDeUsuario, nomeDeUsuario);
    strcpy(usuarios[quantidadeUsuarios].senha, senha);
    criptografarSenha(senha, usuarios[quantidadeUsuarios].senhaCriptografada);
    quantidadeUsuarios++;

    salvarSenhasCriptografadas();
    printf("Usuário criado com sucesso!\n");
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------

int autenticarUsuario() {
	system("cls");
    char nomeDeUsuario[MAX_LEN], senha[MAX_LEN];

    printf("Digite o nome de usuário: ");
    scanf("%s", nomeDeUsuario);
    printf("Digite a senha: ");
    scanf("%s", senha);

	int i;
    for (i = 0; i < quantidadeUsuarios; i++) {
        if (strcmp(usuarios[i].nomeDeUsuario, nomeDeUsuario) == 0 && strcmp(usuarios[i].senha, senha) == 0) {
            printf("Autenticação bem-sucedida!\n");
            return i;
        }
    }

    printf("Usuário ou senha incorretos.\n");
    return -1;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------

void atualizarSenha(int indiceUsuario) {
	system("cls");
    char novaSenha[MAX_LEN];
    printf("Digite a nova senha: ");
    scanf("%s", novaSenha);

    strcpy(usuarios[indiceUsuario].senha, novaSenha);
    criptografarSenha(novaSenha, usuarios[indiceUsuario].senhaCriptografada);

    salvarSenhasCriptografadas();
    printf("Senha atualizada com sucesso!\n");
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------

void alterarNomeUsuario(int indiceUsuario) {
	system("cls");
    char novoNome[MAX_LEN];
    printf("Digite o novo nome de usuário: ");
    scanf("%s", novoNome);

	int i;
    for (i = 0; i < quantidadeUsuarios; i++) {
        if (strcmp(usuarios[i].nomeDeUsuario, novoNome) == 0) {
            printf("Nome de usuário já existe.\n");
            return;
        }
    }

    strcpy(usuarios[indiceUsuario].nomeDeUsuario, novoNome);
    salvarSenhasCriptografadas();
    printf("Nome de usuário alterado com sucesso!\n");
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------

void deletarUsuario(int indiceUsuario) {
	int i;
    for (i = indiceUsuario; i < quantidadeUsuarios - 1; i++) {
        usuarios[i] = usuarios[i + 1];
    }
    quantidadeUsuarios--;

    salvarSenhasCriptografadas();
    printf("Usuário deletado com sucesso!\n");
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------

void menuPrincipal() {
    int escolha, indiceUsuario;
    while (1) {
        printf("\n-------------------------MENU--------------------------------");
        printf("\n1. Criar usuário");                                         
        printf("\n-------------------------------------------------------------");
        printf("\n2. Fazer login");  
        printf("\n-------------------------------------------------------------");
        printf("\n3. Sair");
        printf("\n-------------------------------------------------------------");
        printf("\n\n");
        printf("\nEscolha uma opção:");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                criarUsuario();
                break;
            case 2:
                indiceUsuario = autenticarUsuario();
                if (indiceUsuario != -1) {
                    system("cls");
                    int acao;
                    printf("\n-------------------------BEM-VINDO(a)------------------------");
                    printf("\n1. Atualizar senha");
                    printf("\n-------------------------------------------------------------");
                    printf("\n2. Alterar nome de usuário");
                    printf("\n-------------------------------------------------------------");
                    printf("\n3. Deletar usuário");
                    printf("\n-------------------------------------------------------------");
                    printf("\n4. Exibir usuários e senhas criptografadas");
                    printf("\n-------------------------------------------------------------");
                    printf("\n5. Voltar");
                    printf("\n-------------------------------------------------------------");
                    printf("\nEscolha uma ação: ");
                    scanf("%d", &acao);
                    
                    switch (acao) {
                        case 1:
                            atualizarSenha(indiceUsuario);
                            break;
                        case 2:
                            alterarNomeUsuario(indiceUsuario);
                            break;
                        case 3:
                            deletarUsuario(indiceUsuario);
                            break;
                        case 4:
                            system("cls");
                            exibirSenhasCriptografadas();
                            printf("\n\n");
                            printf("1 - Deseja voltar ao menu?\n");
                            printf("2 - Deseja sair do programa?\n\n");
                            printf("Escolha uma opção: ");
                            int subEscolha;
                            scanf("%d", &subEscolha);
                            if (subEscolha == 2) {
                                exit(0);  
                            } else if (subEscolha != 1) {
                            	system("cls");
                                printf("Ação inválida.\n");
                            }
                            break;
                        case 5:
                            break;
                        default:
                            printf("Ação inválida.\n");
                    }
                }
                break;
            case 3:
                system("cls");
                printf("Saindo...\n");
                exit(0);
            default:
                printf("Opção inválida.\n");
                break;
        }
    }
}


int main() {
    setlocale(LC_ALL,"Portuguese");
    carregarUsuarios();
    menuPrincipal();
    return 0;
}





