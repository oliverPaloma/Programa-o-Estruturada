#ifndef PROJETO_H
#define PROJETO_H

#define MAX_TAREFAS 10
#define MAX_DIAS 7
#define TAMANHO_TAREFA 100
#define NUM_HORARIOS 8 //adicionado horarios


typedef struct {    
    char tarefas[MAX_TAREFAS][TAMANHO_TAREFA];  
  int contagem_tarefas;    
  float prioridade[MAX_TAREFAS];    
  int horarios[MAX_TAREFAS]; 
  } Dia;


void inicializar_semana(Dia *semana);
void adicionar_tarefa_interface(Dia *semana);
void adicionar_tarefa(Dia *semana, int dia, const char *tarefa, float prioridade, int horario); 
void imprimir_tabela_cronograma(const Dia *semana);
void imprimir_tarefas_recursiva(const Dia *semana, int dia, int tarefa); // Função recursiva para imprimir tarefas

int total_tarefas(const Dia *semana);
int obter_indice_dia(const char *nome_dia);
int determinar_horario_por_prioridade(float prioridade);

float maiores_prioridades(const Dia *semana);

#endif
