#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h> 
#include "paloma.h"

void inicializar_semana(Dia *semana) {
    for (int i = 0; i < MAX_DIAS; i++) {
        semana[i].tarefas = (char **)malloc(MAX_TAREFAS * sizeof(char *));
        semana[i].prioridade = (float *)malloc(MAX_TAREFAS * sizeof(float));
        semana[i].horarios = (int *)malloc(MAX_TAREFAS * sizeof(int));
        semana[i].contagem_tarefas = 0;

        for (int j = 0; j < MAX_TAREFAS; j++) {
            semana[i].tarefas[j] = (char *)malloc(TAMANHO_TAREFA * sizeof(char));
        }
    }
}

void liberar_memoria(Dia *semana) {
    for (int i = 0; i < MAX_DIAS; i++) {
        for (int j = 0; j < MAX_TAREFAS; j++) {
            free(semana[i].tarefas[j]);
        }
        free(semana[i].tarefas);
        free(semana[i].prioridade);
        free(semana[i].horarios);
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

    horario=determinar_horario_por_prioridade(prioridade);

    if (horario < 8 || horario > 16) { //ja houver tarefa nesse dia com essa prioridade
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
    int horarios[] = {8, 9, 10, 11, 13, 14, 15, 16,19}; //add e não aparece automaticamente, devo alterar o código para funcionar mais eficiente


    printf("+----------------+---------------+---------------+---------------+---------------+---------------+---------------+---------------+\n");
    printf("| Horário/Dia    | Dom           | Seg           | Ter           | Qua           | Qui           | Sex           | Sab           |\n");
    printf("+----------------+---------------+---------------+---------------+---------------+---------------+---------------+---------------+\n");

    for (int h = 0; h < NUM_HORARIOS; h++) {
        char horario_formatado[6];
        sprintf(horario_formatado, " %dh00", horarios[h]);

        printf("|   %-13s", horario_formatado);

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

int imprimir_tarefas_txt(const Dia *semana){
    FILE *arquivo = fopen("tarefas.txt", "a+");  
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
    }

    char linha[100];

    printf("Tarefas atuais:\n");
    while (fgets(linha, sizeof(linha), arquivo)) {
        printf("- %s", linha); 
    }

    char resposta;
    printf("\nDeseja adicionar uma tarefa? [Y ou N]: ");
    scanf(" %c", &resposta); 
    resposta = tolower(resposta); 

    if (resposta == 'y') {
        char tarefa[256]; 
        printf("Digite a tarefa: ");
        getchar();  

        fgets(tarefa, sizeof(tarefa), stdin); 
        fprintf(arquivo, "%s", tarefa);
        printf("Tarefa adicionada!\n");

    } else if (resposta == 'n') {
        printf("Nenhuma tarefa foi adicionada.\n");
    } else {
        printf("Resposta inválida! Por favor, insira 'Y' ou 'N'.\n");
    }

    fclose(arquivo);
    return 0;
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

int determinar_horario_por_prioridade(float prioridade) {
       if (prioridade >= 9.0) {
        return 8;  // Alta prioridade, marca para as 8h......
    } else if (prioridade >= 8.0) {
        return 9;  
    } else if (prioridade >= 7.0) {
        return 10;  
    } else if (prioridade >= 6.0) {
        return 11;  
    } else if (prioridade >= 5.0) {
        return 13;  
    } else if (prioridade >= 4.0) {
        return 14;  
    } else if (prioridade >= 3.0) {
        return 15;
    } else {
        return 16;  
    }
}


