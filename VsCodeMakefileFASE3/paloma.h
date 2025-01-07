#ifndef PROJETO_H
#define PROJETO_H

#define MAX_TAREFAS 10
#define MAX_DIAS 7
#define TAMANHO_TAREFA 100
#define NUM_HORARIOS 9//adicionado horarios


typedef struct {
    char **tarefas;  // Alocação dinâmica para tarefas
    int contagem_tarefas;
    float *prioridade;  // Alocação dinâmica para prioridades
    int *horarios;  // Alocação dinâmica para horários
} Dia;

void inicializar_semana(Dia *semana);
void adicionar_tarefa_interface(Dia *semana);
void adicionar_tarefa(Dia *semana, int dia, const char *tarefa, float prioridade, int horario); 
void imprimir_tabela_cronograma(const Dia *semana);
void imprimir_tarefas_recursiva(const Dia *semana, int dia, int tarefa); // Função recursiva para imprimir tarefas
void liberar_memoria(Dia *semana);
int imprimir_tarefas_txt(const Dia *semana);

int total_tarefas(const Dia *semana);
int obter_indice_dia(const char *nome_dia);
int determinar_horario_por_prioridade(float prioridade);

float maiores_prioridades(const Dia *semana);

#endif