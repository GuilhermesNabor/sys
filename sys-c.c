#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"

void limpar_tela() {
    system("clear");
}

void pressionar_enter() {
    printf("\nPressione [ENTER] para voltar ao menu...");
    while(getchar() != '\n'); // Limpa o buffer de entrada
    getchar(); // Espera pelo Enter do usuário
}

void limpar_ram() {
    printf(GREEN " ...Tentando limpar a Memória RAM...\n" RESET);
    printf("Alocando uma grande quantidade de memória para forçar o sistema a liberar cache.\n");

    size_t size_1gb = 1024 * 1024 * 1024;
    size_t size_512mb = 512 * 1024 * 1024;
    size_t size_256mb = 256 * 1024 * 1024;
    char *ptr = NULL;
    size_t allocated_size = 0;

    // Tenta alocar 1GB
    ptr = malloc(size_1gb);
    if (ptr != NULL) {
        allocated_size = size_1gb;
    } else {
        printf(RED "Falha ao alocar 1GB de memória. Tentando com 512MB...\n" RESET);
        ptr = malloc(size_512mb);
        if (ptr != NULL) {
            allocated_size = size_512mb;
        } else {
            printf(RED "Falha ao alocar 512MB de memória. Tentando com 256MB...\n" RESET);
            ptr = malloc(size_256mb);
            if (ptr != NULL) {
                allocated_size = size_256mb;
            }
        }
    }

    if (ptr != NULL) {
        printf(GREEN "Memória alocada (%.0fMB). Preenchendo a memória...\n" RESET, (double)allocated_size / (1024*1024));
        memset(ptr, 0, allocated_size);
        free(ptr);
        printf(GREEN "Memória liberada. A limpeza da RAM foi concluída.\n" RESET);
    } else {
        printf(RED "Não foi possível alocar memória suficiente para a limpeza.\n" RESET);
    }
}

int main(void) {
    int esc = 0;

    limpar_tela();
    printf(GREEN "\n Iniciando Ferramenta de Manutenção...\n" RESET);
    sleep(2);

    while(1) {
        limpar_tela();
        printf(CYAN "\n === GERENCIADOR DO SISTEMA (ARCH/MANJARO) === \n" RESET);
        printf(" 1 - Atualizar Sistema Completo (Pacman + Yay)\n");
        printf(" 2 - Limpeza Profunda (Journal + Cache Pacman)\n");
        printf(" 3 - Remover Pacotes Orfãos (Dependências inúteis)\n");
        printf(" 4 - Listar erros do Sistema (Systemctl failed)\n");
        printf(" 5 - Limpar Memória RAM\n");
        printf(" 0 - Sair\n");
        printf("\n Escolha uma Opção: ");

        if (scanf("%d", &esc) != 1) {
            printf(RED "Entrada inválida!\n" RESET);
            while(getchar() != '\n');
            sleep(1);
            continue;
        }

        switch(esc) {
            case 1:
                printf(GREEN " ...Iniciando Atualização...\n" RESET);
                system("sudo pacman -Syu && yay -Syu");
                pressionar_enter();
                break;

            case 2:
                printf(GREEN " ...Iniciando Limpeza de Logs e Cache...\n" RESET);
                system("sudo journalctl --vacuum-time=7d && sudo pacman -Sc");
                pressionar_enter();
                break;

            case 3:
                printf(GREEN " ...Removendo Pacotes Orfãos...\n" RESET);
                system("sudo pacman -Rns $(pacman -Qtdq)");
                pressionar_enter();
                break;

            case 4:
                printf(GREEN " ...Verificando falhas no Systemd...\n" RESET);
                system("systemctl --failed");
                pressionar_enter();
                break;
            
            case 5:
                limpar_ram();
                pressionar_enter();
                break;

            case 0:
                printf("\n Encerrando aplicação. Até logo!\n");
                sleep(1);
                return 0;

            default:
                printf(RED "\n Opção Inválida! Tente novamente.\n" RESET);
                sleep(1);
        }
    }

    return 0;
}
