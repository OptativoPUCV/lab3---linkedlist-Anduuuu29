#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;


Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
  List * list = (List *)malloc(sizeof(List));
  list->head = list->tail = list->current = NULL;
  return list;
  ;
}

void * firstList(List * list) {
  list->current = list->head;
  if(list->current) return list->current->data;
  return NULL;
}

void * nextList(List * list) {
  if(list->current!= NULL)
    list->current = list->current->next;
  if(list->current) return list->current->data;
    return NULL;
}

void * lastList(List * list) {
  Node* aux = list->head;
  while(aux->next != NULL)
    aux = aux->next;
  list->current = aux;
  if(list->current) 
    return list->current->data;
  return NULL;
}

void * prevList(List * list) {
  if(list->current!= NULL)
    list->current = list->current->prev;
  if(list->current) return list->current->data; 
    return NULL;
}

void pushFront(List * list, void * data) {
  Node * new_nodo = createNode(data);
  if(list->head) list->head->prev = new_nodo;
  new_nodo->next = list->head;
  list->head = new_nodo;
  if(list->tail == NULL) list->tail = new_nodo;
  
  

}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
  Node * new_nodo = createNode(data);
  if(list->current->next) list->current->next->prev = new_nodo;
  new_nodo->next = list->current->next;
  new_nodo->prev = list->current;
  list->current->next = new_nodo;
  if(list->current == list->tail) list->tail = new_nodo;
  
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
  void* data = list->current->data;
  Node* izq = list->current->prev;
  Node* der = list->current->next;
  if(izq) izq->next = der;
  if(der) der->prev = izq;
  
  if(list->current == list->head) list->head = der;
  if(list->current == list->tail) list->tail = izq;
  free(list->current);
  list->current = NULL;
  return data;
  
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}