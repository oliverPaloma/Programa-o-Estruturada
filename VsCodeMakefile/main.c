#include <stdio.h>
#include <string.h>
#include "projeto.h"

int main() {
    Dia semana[MAX_DIAS];
    inicializar_semana(semana);
    int opcao;
    do {
        printf("Escolha uma opção:\n");
        printf("1. Adicionar tarefa\n");
        printf("2. Ver cronograma\n");
        printf("3. Ver total de tarefas\n");
        printf("4. Ver prioridade\n");
        printf("0. Sair\n");
        printf("Opção: ");
        scanf("%d", &opcao);
        switch (opcao) {
            case 1:
                adicionar_tarefa_interface(semana);
                break;
            case 2:
                imprimir_tabela_cronograma(semana);
                break;
            case 3:
                printf("Total de tarefas na semana: %d\n", total_tarefas(semana));
                break;
            case 4:
                printf("Prioridade principal: %.2f\n", maiores_prioridades(semana));
                break;
            case 0:
                printf("Saindo do programa.\n");
                break;
            default:
                printf("Opção inválida.\n");
        }
    } while (opcao != 0);
    return 0;
}
