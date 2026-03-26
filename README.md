# Gerenciador do Sistema (Arch/Manjaro)

Este é um utilitário de manutenção simples escrito em C, projetado especificamente para distribuições baseadas em Arch Linux (como Manjaro). Ele automatiza tarefas comuns de gerenciamento de pacotes e limpeza do sistema através de uma interface de linha de comando colorida e intuitiva.

## Funcionalidades

O programa oferece as seguintes opções:

1.  **Atualizar Sistema Completo**: Executa a atualização dos repositórios oficiais via `pacman` e dos pacotes do AUR via `yay`.
2.  **Limpeza Profunda**: Limpa os logs do `journalctl` (mantendo apenas os últimos 7 dias) e limpa o cache do `pacman`.
3.  **Remover Pacotes Órfãos**: Identifica e remove dependências que não são mais necessárias para nenhum pacote instalado.
4.  **Listar Erros do Sistema**: Exibe unidades do `systemd` que falharam ao iniciar ou durante a execução.
5.  **Limpar Memória RAM**: Tenta forçar a liberação de cache da RAM alocando e preenchendo temporariamente um bloco de memória (até 1GB).

## Pré-requisitos

Para utilizar todas as funções, seu sistema deve ter:

*   **Compilador GCC**: Para compilar o código-fonte.
*   **Pacman**: Gerenciador de pacotes padrão do Arch.
*   **Yay**: Auxiliar do AUR (necessário para a opção de atualização completa).
*   **Sudo**: O programa utiliza comandos que requerem privilégios de superusuário.

## Como Compilar e Executar

### 1. Compilação
Abra o terminal na pasta do projeto e execute:

```bash
gcc sys-c.c -o sys-manager
```

### 2. Execução
Após compilar, você pode iniciar o programa com:

```bash
./sys-manager
```

## Estrutura do Código

*   `limpar_tela()`: Utilitário para limpar o console e manter a interface organizada.
*   `limpar_ram()`: Função lógica que tenta alocar 1GB, 512MB ou 256MB de memória e preenchê-la com zeros para induzir o sistema a gerenciar melhor a RAM disponível antes de liberá-la.
*   `main()`: Contém o loop principal e o menu interativo que despacha os comandos do sistema via `system()`.

## Aviso de Segurança
Este programa executa comandos com `sudo`. Certifique-se de revisar o código e entender o que cada comando faz antes de executá-lo em seu sistema de produção.
