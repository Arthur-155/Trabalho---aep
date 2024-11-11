//Fazer um MENU com apenas 1 op��o, no caso a de criptografar, dentro dela (da op��o) inserir mais algumas opcoes; - feito
//fazer os arquivos irem para o bloco de notas  e armazenar todas as senhas escritas - feito
//mudan�a de planos, aparentemente � pra fazer um CRUD.  - feito 
//exibir na tela o usuario e senha senha(a senha criptografada) ao inv�s da pasta
//dentro da fun��o onde mostra as senhas criptografadas, adicionar uma fun��o onde ela descriptografa todas as senhas.
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
    
    printf("Deseja descriptografar as senhas? (1 - Sim, 0 - N�o): ");
    scanf("%d", &escolha);

    switch (escolha) {
        case 1:  
        system("cls");
        	printf("---------------------------------LISTA------------------------------");
        	printf("\n\n");
            for (i = 0; i < quantidadeUsuarios; i++) {
                descriptografarSenha(usuarios[i].senhaCriptografada, senhaDescriptografada);
                printf(" Usu�rio: %s \n Senha Criptografada: %s \n Senha Descriptografada: %s\n",usuarios[i].nomeDeUsuario, usuarios[i].senhaCriptografada, senhaDescriptografada);
                printf("--------------------------------------------------------------------\n");
            }
            break;
        case 0:  
        system("cls");
            for (i = 0; i < quantidadeUsuarios; i++) {
                printf("Usu�rio: %s | Senha Criptografada: %s\n",usuarios[i].nomeDeUsuario, usuarios[i].senhaCriptografada);
            }
            break;
        
        default:  
            printf("Op��o inv�lida.\n");
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
        fprintf(arquivo, "Usu�rio: %s | Senha Criptografada: %s\n", usuarios[i].nomeDeUsuario, usuarios[i].senhaCriptografada);
    }

    fclose(arquivo);
    printf("Senhas criptografadas salvas com sucesso.\n");
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------

void carregarUsuarios() {
    FILE *arquivo = fopen(NOME_ARQUIVO, "r");
    if (arquivo == NULL) {
        printf("Nenhum arquivo encontrado. Um novo ser� criado.\n");
        return;
    }

    char linha[256];
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        sscanf(linha, "Usu�rio: %s | Senha Criptografada: %s\n", usuarios[quantidadeUsuarios].nomeDeUsuario, usuarios[quantidadeUsuarios].senhaCriptografada);
        descriptografarSenha(usuarios[quantidadeUsuarios].senhaCriptografada, usuarios[quantidadeUsuarios].senha);
        quantidadeUsuarios++;
    }
    fclose(arquivo);
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------

void criarUsuario() {
	system("cls");
    char nomeDeUsuario[MAX_LEN], senha[MAX_LEN];

    printf("Digite o nome de usu�rio: ");
    scanf("%s", nomeDeUsuario);
    printf("Digite a senha: ");
    scanf("%s", senha);
	
	int i;
    for (i = 0; i < quantidadeUsuarios; i++) {
        if (strcmp(usuarios[i].nomeDeUsuario, nomeDeUsuario) == 0) {
            printf("Usu�rio j� existe.\n");
            return;
        }
    }

    strcpy(usuarios[quantidadeUsuarios].nomeDeUsuario, nomeDeUsuario);
    strcpy(usuarios[quantidadeUsuarios].senha, senha);
    criptografarSenha(senha, usuarios[quantidadeUsuarios].senhaCriptografada);
    quantidadeUsuarios++;

    salvarSenhasCriptografadas();
    printf("Usu�rio criado com sucesso!\n");
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------

int autenticarUsuario() {
	system("cls");
    char nomeDeUsuario[MAX_LEN], senha[MAX_LEN];

    printf("Digite o nome de usu�rio: ");
    scanf("%s", nomeDeUsuario);
    printf("Digite a senha: ");
    scanf("%s", senha);

	int i;
    for (i = 0; i < quantidadeUsuarios; i++) {
        if (strcmp(usuarios[i].nomeDeUsuario, nomeDeUsuario) == 0 && strcmp(usuarios[i].senha, senha) == 0) {
            printf("Autentica��o bem-sucedida!\n");
            return i;
        }
    }

    printf("Usu�rio ou senha incorretos.\n");
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
    printf("Digite o novo nome de usu�rio: ");
    scanf("%s", novoNome);

	int i;
    for (i = 0; i < quantidadeUsuarios; i++) {
        if (strcmp(usuarios[i].nomeDeUsuario, novoNome) == 0) {
            printf("Nome de usu�rio j� existe.\n");
            return;
        }
    }

    strcpy(usuarios[indiceUsuario].nomeDeUsuario, novoNome);
    salvarSenhasCriptografadas();
    printf("Nome de usu�rio alterado com sucesso!\n");
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------

void deletarUsuario(int indiceUsuario) {
	int i;
    for (i = indiceUsuario; i < quantidadeUsuarios - 1; i++) {
        usuarios[i] = usuarios[i + 1];
    }
    quantidadeUsuarios--;

    salvarSenhasCriptografadas();
    printf("Usu�rio deletado com sucesso!\n");
}

//---------------------------------------------------------------------------------------------------------------------------------------------------------------

void menuPrincipal() {
    int escolha, indiceUsuario;
    while (1) {
        printf("\n-------------------------MENU--------------------------------");
        printf("\n1. Criar usu�rio");                                         
        printf("\n-------------------------------------------------------------");
        printf("\n2. Fazer login");  
        printf("\n-------------------------------------------------------------");
        printf("\n3. Sair");
        printf("\n-------------------------------------------------------------");
        printf("\n\n");
        printf("\nEscolha uma op��o:");
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
                    printf("\n2. Alterar nome de usu�rio");
                    printf("\n-------------------------------------------------------------");
                    printf("\n3. Deletar usu�rio");
                    printf("\n-------------------------------------------------------------");
                    printf("\n4. Exibir usu�rios e senhas criptografadas");
                    printf("\n-------------------------------------------------------------");
                    printf("\n5. Voltar");
                    printf("\n-------------------------------------------------------------");
                    printf("\nEscolha uma a��o: ");
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
                            printf("Escolha uma op��o: ");
                            int subEscolha;
                            scanf("%d", &subEscolha);
                            if (subEscolha == 2) {
                                exit(0);  
                            } else if (subEscolha != 1) {
                            	system("cls");
                                printf("A��o inv�lida.\n");
                            }
                            break;
                        case 5:
                            break;
                        default:
                            printf("A��o inv�lida.\n");
                    }
                }
                break;
            case 3:
                system("cls");
                printf("Saindo...\n");
                exit(0);
            default:
                printf("Op��o inv�lida.\n");
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





