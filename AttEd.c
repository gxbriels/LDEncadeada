#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef void *tdado; // O dado que vai ser colocado no nó
  
  typedef struct tipo_No{ // Cada nó da lista
    tdado dado;
    struct tipo_No *prox;
    struct tipo_No *ant;
  }*tNo;
  
  typedef struct { // Struct Controle da lista
   int tamLista;
   struct tipo_No *prim;
   struct tipo_No *ult;
  }tLista;
  
  typedef tLista *Lista; // Primeiro ponteiro que aponta para a struct controle

Lista new_lista(){
   Lista lst = (Lista)malloc(sizeof(tLista));
   lst -> prim = NULL;
   lst -> ult = NULL;
   lst -> tamLista = 0;
   return lst;
  }
  
  int len(Lista lst){
   return lst -> tamLista; 
  }
  
  Lista appendLista(Lista lst, tdado d){ // Apenas adicionar ao final da lista 
    tNo no = (tNo)malloc(sizeof(struct tipo_No));
    no -> dado = d;
    no -> prox = NULL;
    no -> ant = NULL;
    
    if (lst -> tamLista == 0){
     lst -> prim = no; 
     lst -> ult = no;
    } else {
     lst -> ult -> prox = no; // att próximo do nó anterior para o novo nó
     no -> ant = lst -> ult; // att anterior do nó acrescentado aponta para o antigo último da struct controle
     lst -> ult = no; // e att a Struct controle
    }
    lst -> tamLista++;
    
    return lst;
  }
  
  tdado elemLista(Lista lst, int pos){
    tNo aux;
    int cont = 0;
    
    if ((pos >= 0) && (pos < lst -> tamLista) && (lst-> tamLista > 0)){
      aux = lst -> prim;
      for (cont = 0; cont < pos; cont++){
        aux = aux -> prox;
      }
      return aux -> dado;
    } else
      return NULL;
  }

  Lista insereLista(Lista lst, tdado dado, int pos) {
    if (pos < 0 || pos > lst->tamLista) return lst; // Verifica se a posição é válida

    tNo no = (tNo)malloc(sizeof(struct tipo_No)); // Aloca o novo nó
    no->dado = dado;
    no->prox = NULL;
    no->ant = NULL;

    if (lst->tamLista == 0) { // Lista vazia
        lst->prim = no;
        lst->ult = no;
    } else if (pos == 0) { // Inserir na primeira posição
        no->prox = lst->prim;
        lst->prim->ant = no;
        lst->prim = no;
    } else if (pos == lst->tamLista) { // Inserir na última posição
        no->ant = lst->ult;
        lst->ult->prox = no;
        lst->ult = no;
    } else { // Inserir no meio
        tNo aux = lst->prim;
        for (int i = 0; i < pos; i++) {
            aux = aux->prox; // Percorre até a posição desejada
        }
        no->prox = aux;
        no->ant = aux->ant;
        aux->ant->prox = no;
        aux->ant = no;
    }

    lst->tamLista++;
    return lst;
}

    tdado removeLista(Lista lst, int pos) {
    if (pos < 0 || pos >= lst->tamLista || lst->tamLista == 0) return NULL; // Verifica se posição é válida

    tNo removido;
    tdado dado_removido;

    if (pos == 0) { // Remover o primeiro elemento
        removido = lst->prim;
        lst->prim = removido->prox;
        if (lst->prim != NULL) lst->prim->ant = NULL;
        else lst->ult = NULL; // Lista ficou vazia
    } else if (pos == lst->tamLista - 1) { // Remover o último elemento
        removido = lst->ult;
        lst->ult = removido->ant;
        lst->ult->prox = NULL;
    } else { // Remover do meio
        removido = lst->prim;
        for (int i = 0; i < pos; i++) {
            removido = removido->prox;
        }
        removido->ant->prox = removido->prox;
        removido->prox->ant = removido->ant;
    }

    dado_removido = removido->dado;
    free(removido);
    lst->tamLista--;

    return dado_removido;
}

    void printLista(Lista lst) {
    tNo aux = lst->prim;
    printf("Lista: ");
    while (aux != NULL) {
        printf("%d ", *(int *)(aux->dado));
        aux = aux->prox;
    }
    printf("\nTamanho da lista: %d\n", lst->tamLista);
}



int main() {

    // Testando implementação

    Lista  minhaLista = new_lista();

    int a = 10, b = 20, c = 30, d = 40, e = 50;

    // Adicionando elementos

    printf("\n=== Implementando a lista===\n\n");

    insereLista(minhaLista, &a, 0);
    printLista(minhaLista);

    insereLista(minhaLista, &b, 1);
    printLista(minhaLista);

    insereLista(minhaLista, &c, 1);
    printLista(minhaLista);

    insereLista(minhaLista, &d, 0);
    printLista(minhaLista);

    insereLista(minhaLista, &e, 2);
    printLista(minhaLista);

    printf("\n=== Remoção de elementos ===\n\n");

    removeLista(minhaLista, 0);
    printLista(minhaLista);

    removeLista(minhaLista, 2);
    printLista(minhaLista);

    removeLista(minhaLista, minhaLista -> tamLista -1);
    printLista(minhaLista);

    printf("\n=== Final da execução ===\n");

  // Testando implementação

    /*
    Lista  minhaLista = new_lista();
    int *p;

    p = (int *)malloc(sizeof(int));
    *p = 10;
    appendLista(minhaLista, p);

    p = (int *)malloc(sizeof(int));
    *p = 20;
    appendLista(minhaLista, p);

    p = (int *)malloc(sizeof(int));
    *p = 30;
    appendLista(minhaLista, p);

    for (int i = 0; i < lenLista(minhaLista); i++){
        int *q = (int *)elemLista(minhaLista, i);
        printf("%d\n", *q);
    }
    */

  /* 
    t_dado removeLista(Lista l, int pos) {
    if (pos < 0 || pos >= l->tamanho || l->tamanho == 0) return NULL; // Verifica se posição é válida
  
    t_no removido;
    t_dado dado_removido;
  
    if (pos == 0) { // Remover o primeiro elemento
        removido = l->primeiro;
        l->primeiro = removido->proximo;
        if (l->primeiro != NULL) l->primeiro->anterior = NULL;
        else l->ultimo = NULL; // Lista ficou vazia
    } else if (pos == l->tamanho - 1) { // Remover o último elemento
        removido = l->ultimo;
        l->ultimo = removido->anterior;
        l->ultimo->proximo = NULL;
    } else { // Remover do meio
        removido = l->primeiro;
        for (int i = 0; i < pos; i++) {
            removido = removido->proximo;
        }
        removido->anterior->proximo = removido->proximo;
        removido->proximo->anterior = removido->anterior;
    }
  
    dado_removido = removido->dado;
    free(removido);
    l->tamanho--;
  
    return dado_removido;
  }
  */

    

  return 0;
}
