#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "projeto.h"


void inicializar_semana(Dia *semana) {
    //int i;
    for (int i = 0; i < MAX_DIAS; i++) {
    //for (i = 0; i < MAX_DIAS; i++) {
        semana[i].contagem_tarefas = 0;
        for (int j = 0; j < MAX_TAREFAS; j++) {
            semana[i].prioridade[j] = 0.0f;
            semana[i].horarios[j] = -1; 
        }
    }
}

void adicionar_tarefa_interface(Dia *semana) {
    char dia_nome[20];
    char tarefa[TAMANHO_TAREFA];
    float prioridade;
    int horario;

    printf("Informe o dia da semana (ex: Domingo, Segunda, ...): ");
    getchar(); 
    fgets(dia_nome, sizeof(dia_nome), stdin);
    dia_nome[strcspn(dia_nome, "\n")] = '\0'; 

    int dia = obter_indice_dia(dia_nome);
    if (dia == -1) {
        printf("Dia inválido.\n");
        return;
    }

    printf("Digite a tarefa: ");
    fgets(tarefa, TAMANHO_TAREFA, stdin);
    tarefa[strcspn(tarefa, "\n")] = '\0'; 

    printf("Informe a prioridade da tarefa (0.0 a 10.0): ");
    scanf("%f", &prioridade);

    printf("Informe o horário da tarefa (8 a 16, exemplo: 8 para 08h): ");
    scanf("%d", &horario);

    if (horario < 8 || horario > 16) {
        printf("Horário inválido. Escolha entre 8h e 16h.\n");
        return;
    }

   
    adicionar_tarefa(semana, dia, tarefa, prioridade, horario); //com horario
}

void adicionar_tarefa(Dia *semana, int dia, const char *tarefa, float prioridade, int horario) {
    if (dia < 0 || dia >= MAX_DIAS || semana[dia].contagem_tarefas >= MAX_TAREFAS) {
        printf("Erro: dia inválido ou já há muitas tarefas nesse dia. Não foi possível adicionar a tarefa.\n");
        return;
    }

    strncpy(semana[dia].tarefas[semana[dia].contagem_tarefas], tarefa, TAMANHO_TAREFA - 1);
    semana[dia].tarefas[semana[dia].contagem_tarefas][TAMANHO_TAREFA - 1] = '\0';
    semana[dia].prioridade[semana[dia].contagem_tarefas] = prioridade;
    semana[dia].horarios[semana[dia].contagem_tarefas] = horario;
    semana[dia].contagem_tarefas++;
}

void imprimir_tabela_cronograma(const Dia *semana) {
    int horarios[] = {8, 9, 10, 11, 13, 14, 15, 16};

    printf("+----------------+---------------+---------------+---------------+---------------+---------------+---------------+---------------+\n");
    printf("| Horário/Dia   | Dom           | Seg           | Ter           | Qua           | Qui           | Sex           | Sab           |\n");
    printf("+----------------+---------------+---------------+---------------+---------------+---------------+---------------+---------------+\n");

    for (int h = 0; h < NUM_HORARIOS; h++) {
        char horario_formatado[6];
        sprintf(horario_formatado, "%dh00", horarios[h]);

        printf("|  %-13s", horario_formatado);

        for (int i = 0; i < MAX_DIAS; i++) {
            int tarefa_impressa = 0;
            for (int j = 0; j < semana[i].contagem_tarefas; j++) {
                if (semana[i].horarios[j] == horarios[h]) {
                    printf("| %-13s", semana[i].tarefas[j]);
                    tarefa_impressa = 1;
                    break;
                }
            }
            if (!tarefa_impressa) {
                printf("|               ");
            }
        }

        printf("|\n");
        printf("+----------------+---------------+---------------+---------------+---------------+---------------+---------------+---------------+\n");
    }
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

void imprimir_tarefas_recursiva(const Dia *semana, int dia, int tarefa) {
    if (dia == MAX_DIAS) return;
    if (tarefa < semana[dia].contagem_tarefas) {
        printf("Dia %d: %s (Prioridade: %.1f)\n", dia, semana[dia].tarefas[tarefa], semana[dia].prioridade[tarefa]);
        imprimir_tarefas_recursiva(semana, dia, tarefa + 1); 
    } else {
        imprimir_tarefas_recursiva(semana, dia + 1, 0); 
    }
}

int obter_indice_dia(const char *nome_dia) {
    const char *dias[] = {"domingo", "segunda", "terca", "quarta", "quinta", "sexta", "sabado"};
    const char *abreviacoes[] = {"dom", "seg", "ter", "qua", "qui", "sex", "sab"};

    char nome_dia_normalizado[TAMANHO_TAREFA]; 
    int i;
    for (i = 0; nome_dia[i]; i++) {
        nome_dia_normalizado[i] = tolower(nome_dia[i]);
    }
    nome_dia_normalizado[i] = '\0'; 

   
    for (i = 0; i < 7; i++) {  
        if (strcmp(nome_dia_normalizado, dias[i]) == 0 || strcmp(nome_dia_normalizado, abreviacoes[i]) == 0) {
            return i;  //í correspondente
        }
    }
    printf("Dia inválido: %s\n", nome_dia);
    return -1;  
}
