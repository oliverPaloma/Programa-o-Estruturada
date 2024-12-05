#include <stdio.h>
#include <string.h>
#include "projeto.h"

void inicializar_semana(Dia *semana) {
    for (int i = 0; i < MAX_DIAS; i++) {
        semana[i].contagem_tarefas = 0;
        for (int j = 0; j < MAX_TAREFAS; j++) {
            semana[i].prioridade[j] = 0.0f;
        }
    }
}

void adicionar_tarefa_interface(Dia *semana) {
    int dia;
    char tarefa[TAMANHO_TAREFA];
    float prioridade;

    printf("Informe o dia da semana (0 = Domingo, 1 = Segunda, ..., 6 = Sábado): ");
    scanf("%d", &dia);
    if (dia < 0 || dia >= MAX_DIAS) {
        printf("Dia inválido.\n");
        return;
    }
    printf("Digite a tarefa: ");
    getchar();  
    fgets(tarefa, TAMANHO_TAREFA, stdin);
    tarefa[strcspn(tarefa, "\n")] = '\0';  

    printf("Informe a prioridade da tarefa (0.0 a 10.0): ");
    scanf("%f", &prioridade);

    adicionar_tarefa(semana, dia, tarefa, prioridade);
}

void adicionar_tarefa(Dia *semana, int dia, const char *tarefa, float prioridade) {
    if (dia < 0 || dia >= MAX_DIAS || semana[dia].contagem_tarefas >= MAX_TAREFAS) {
        printf("Erro: não foi possível adicionar a tarefa.\n");
        return;
    }
    strncpy(semana[dia].tarefas[semana[dia].contagem_tarefas], tarefa, TAMANHO_TAREFA - 1);
    semana[dia].tarefas[semana[dia].contagem_tarefas][TAMANHO_TAREFA - 1] = '\0';
    semana[dia].prioridade[semana[dia].contagem_tarefas] = prioridade;
    semana[dia].contagem_tarefas++;
}

void imprimir_tabela_cronograma(const Dia *semana) {
const char *dias[] = {"Dom", "Seg", "Ter", "Qua", "Qui", "Sex", "Sab"};
 printf("+---------------+---------------+-------------- Cronograma Semanal--------------+---------------+---------------+\n");
 printf("+---------------+---------------+---------------+---------------+---------------+---------------+---------------+\n");
    
    for (int i = 0; i < MAX_DIAS; i++) {
        printf("| %-13s ", dias[i]);
    }
    printf("|\n");
    printf("+---------------+---------------+---------------+---------------+---------------+---------------+---------------+\n");

    for (int j = 0; j < MAX_TAREFAS; j++) {
        for (int i = 0; i < MAX_DIAS; i++) {
            if (j < semana[i].contagem_tarefas) {
                printf("| %-13s ", semana[i].tarefas[j]);
            } else {
                printf("|               ");
            }
        }
        printf("|\n");

        if (j < MAX_TAREFAS - 1) {
            printf("|_______________|_______________|_______________|_______________|_______________|_______________|_______________|\n");
        }
    }
    printf("|               |               |               |               |               |               |               |\n");
    printf("+---------------+---------------+---------------+---------------+---------------+---------------+---------------+\n");
}


int total_tarefas(const Dia *semana) {
    int total = 0;
    for (int i = 0; i < MAX_DIAS; i++) {
        total += semana[i].contagem_tarefas;
    }
    return total;
}

float maiores_prioridades(const Dia *semana) {
    float maior_prioridade = -1.0;
    for (int i = 0; i < MAX_DIAS; i++) {
        for (int j = 0; j < semana[i].contagem_tarefas; j++) {
            if (semana[i].prioridade[j] > maior_prioridade) {
                maior_prioridade = semana[i].prioridade[j];
            }
        }
    }
    if (maior_prioridade == -1.0) {
        printf("Não há tarefas na semana.\n");
        return maior_prioridade;
    }
    
    printf("Tarefas com a maior prioridade:\n");

    for (int i = 0; i < MAX_DIAS; i++) {
        for (int j = 0; j < semana[i].contagem_tarefas; j++) {
            if (semana[i].prioridade[j] == maior_prioridade) {
                printf("Dia %d: %s (Prioridade: %.1f)\n", i, semana[i].tarefas[j], semana[i].prioridade[j]);
            }
        }
    }

    return maior_prioridade;
}
