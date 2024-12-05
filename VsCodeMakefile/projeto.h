#ifndef PROJETO_H
#define PROJETO_H

#define MAX_TAREFAS 10
#define MAX_DIAS 7
#define TAMANHO_TAREFA 100

typedef struct {
    char tarefas[MAX_TAREFAS][TAMANHO_TAREFA];
    int contagem_tarefas;
    float prioridade[MAX_TAREFAS];
} Dia;

void inicializar_semana(Dia *semana);
void adicionar_tarefa_interface(Dia *semana);
void adicionar_tarefa(Dia *semana, int dia, const char *tarefa, float prioridade);
void imprimir_tabela_cronograma(const Dia *semana);
int total_tarefas(const Dia *semana);
float maiores_prioridades(const Dia *semana);


#endif
