#include <stdio.h>
#include <stdlib.h>

int count(int tarefadia[], int size, int valor);

int main()
{
  FILE *f;
  int x = 0, i, imax = 0, j, max, jmax, n = 0, workers, *tarefadia, taskwrkr[30] = {0}, diatarefa[30] = {0};
  char *vtask, task;
  // Qual o dia em que se terminaram mais tarefas? --- tarefadia vai ser um vetor dinâmico tal que tarefadia[n] = i --> a tarefa 'n' demorou 'i-1' dias a terminar.
  // Qual a tarefa que ocupou mais trabalhadores? --- taskwrkr (vtask-worker)  tal que taskwrkr[n] = x ---> na tarefa 'n' houve 'x' trabalhadores.
  // Qual o dia em que se trabalhou no maior numero de tarefas? --- diatarefa é um vetor de dimensão 30 (30 dias do mês) tal que diatarefa[i] = t ---> no dia 'i' trabalharam-se em 't' tarefas.
  // vtask é um vetor dinâmico tal que vtask[n] = f ---> a tarefa 'n' (número inteiro) corresponde à tarefa 'f' (caracter)

  f = fopen ("work.txt", "r");
  if ( f == NULL)
  {
    printf ("Erro na abertura do ficheiro \"input.txt\"!\n");
    return 1;
  }

  vtask = (char *) malloc (sizeof(char));
  if (vtask == NULL)
  {
    free (vtask);
    printf("Erro na alocacao de memoria!\n");
    return 1;
  }
  tarefadia = (int *) malloc (sizeof(int));
  if (tarefadia == NULL)
  {
    free (tarefadia);
    printf ("Erro na alocacao de memoria!\n");
    return 1;
  }


  while (fscanf (f, "%c", &task) != EOF)
  {
    vtask[n] = task;
    i = 0;
    while (fscanf (f, "%d", &workers) && !feof (f) > 0)
    {
      tarefadia[n] = i + 1;
      if (workers != 0 && workers != -1)
      {
        taskwrkr[n] = taskwrkr[n] + workers;
        diatarefa[i] = diatarefa[i] + 1;
      }
      if (i > imax) imax = i;
      i++;
    }
    realloc (tarefadia, (n+2) * sizeof (int));
    if (tarefadia == NULL)
      {
        printf ("Erro na alocacao de memoria!\n");
        free (tarefadia);
        return 1;
      }
    realloc (vtask, (n+2) * sizeof (char));
    if (vtask == NULL)
      {
        printf("Erro na alocacao de memoria!\n");
        free (vtask);
        return 1;
      }
    n++;
  }


// Qual a tarefa que ocupou mais trabalhadores? Máximo do vetor taskwrkr[]
  max = 0;
  for (j = 0 ; j < n ; j++)
  {
    if (taskwrkr[j] > max)
      {
        max = taskwrkr[j];
        jmax = j;
      }
  }
  printf("Tarefa que ocupou mais trabalhadores: %c\n", vtask[jmax]);


// Qual o dia em que se trabalhou no maior número de tarefas? Máximo de diatarefa[]
  max = 0;
  for (j = 0 ; j < imax ; j++)
  {
    if (diatarefa[j] > max)
      {
        max = diatarefa[j];
        jmax = j;
      }
  }
  printf("Dia em que se trabalhou em mais tarefas: %d\n", jmax + 1);


// Qual o dia em que se terminaram mais tarefas? Número que mais vezes se repete do vetor tarefadia[]
  max = 0;
  for (j = 0 ; j < n-1 ; j++)
    if (count (tarefadia, n, tarefadia[j]) > max) max = tarefadia[j];
  printf("Dia com mais tarefas acabadas: %d\n", max - 1);
}

int count(int tarefadia[], int size, int valor)
{
  int i, count = 0;
  for (i = 0; i < size ; i++)
  {
    if (tarefadia[i] == valor) count++;
  }
  return count;
}
