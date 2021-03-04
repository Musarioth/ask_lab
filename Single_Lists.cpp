#include <stdio.h>
#include <stdlib.h>

struct Node {
  int value;
  Node *next; 
} *head, *tail, *curr; 

Node *create_node(int value) {
  Node *temp = (Node*)malloc(sizeof(Node));
  temp->value = value;
  temp->next = NULL;
  return temp;
}

void push_head(int value) {
  Node *temp = create_node(value);
  if(!head) head = tail = temp; 
  else { 
    temp->next = head;
    head = temp; 
  }
}


void push_tail(int value) {
  Node *temp = create_node(value); 
  if(!head) head = tail = temp; 
  else { 
    tail->next = temp; 
    tail = temp;
  }
}

void push_mid(int value) {
  Node *temp = create_node(value);
  if(!head) head = tail = temp;
  else if(temp->value < head->value) push_head(value);
  else if(temp->value > head->value) push_tail(value);
  else {
    curr = head;
    while(curr) {
      if(curr->next->value > temp->value) {
        temp->next = curr->next;
        curr->next = temp;
      }
    }
  }
}

void pop_head() {
  if (!head) return;
  else if(head == tail) {
    head = tail = NULL; 
    free(head); 
  } 
  else {
    Node *temp = head->next;
    head->next = NULL;
    free(head);
    head = temp;
  }
}

void pop_tail() {
  if (!head) {
    return; 
  } else if(head == tail) {
    head = tail = NULL;
    free(head);
  } 
  else {
    curr = head;

    while(curr) {
      if(curr->next == tail)  {
        curr->next = NULL;
        free(tail);
        break;
        tail = curr;
      }
      curr = curr -> next;
    }
  }
}

void pop_mid(int value) {
  if(!head) {
    puts("No Data");
    return;
  }
  else {
    if(value == head->value) pop_head();
    else if(value == tail->value) pop_tail();
    else {
      curr = head;
      while(curr->next->value != value && curr->next != tail) {
        curr = curr->next;
      }
      if(curr->next != tail) {
        Node *temp = curr->next;
        curr->next = temp->next;
        temp->next = NULL;
        free(temp);
      }
      else {
        puts("[Not found]");
      }
    }
  }
}

void print_list() {
  curr = head;
  while(curr) {
    printf("%d -> ", curr->value);
    curr = curr->next;
  }
  puts("NULL");
}

void search(int value) {
  curr = head;
  bool flag = false;
  while(curr) {
    if(curr->value == value) {
      printf("%d is in the lists\n", value);
      flag = true;
      break;
    }
    curr = curr->next;
  }
  if(!flag) printf("%d is not in the lists", value);
}

int main() {
  push_mid(15);
  push_mid(8);
  push_mid(16);
  push_mid(20);
  print_list();
  search(8);
  pop_head();
  pop_tail();
  print_list();
  printf("Pop mid: ");
  pop_mid(20);
  print_list();
  return 0;
}
