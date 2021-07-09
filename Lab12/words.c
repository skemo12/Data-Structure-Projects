#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char* Key;
typedef int Value;
typedef long(*HashFunction)(Key, long);

typedef struct Element {
  Key key;
  Value value;
  struct Element *next;
} Element;

typedef struct HashTable {
  Element** elements;
  long size;
  HashFunction hashFunction;
} HashTable;

void initHashTable(HashTable **h, long size, HashFunction f) {
  // Cerinta 1
  *h = (HashTable *) calloc(1, sizeof(HashTable));
  (*h)->size = size;
  (*h)->hashFunction = f;
  (*h)->elements = (Element **) calloc(size, sizeof(Element *));
}

int exists(HashTable *hashTable, Key key) {
  // Cerinta 1
  long res = hashTable->hashFunction(key, hashTable->size);
  
  Element *node = hashTable->elements[res];

  while (node != NULL)
  {
    if (strcmp(node->key, key) == 0)
    {
      return 1;
    }
    node = node->next;
    
  }
  
  
  return 0;
}

Value get(HashTable *hashTable, Key key) {
  // Cerinta 1
  long res = hashTable->hashFunction(key, hashTable->size);
  
  Element *node = hashTable->elements[res];

  while (node != NULL)
  {
    if (strcmp(node->key, key) == 0)
    {
      return node->value;
    }
    node = node->next;
    
  }
  return (Value)0;
}

void put(HashTable *hashTable, Key key, Value value) {
  // Cerinta 1

  long res = hashTable->hashFunction(key, hashTable->size);

  if (exists(hashTable, key))
  {
    Element *node = hashTable->elements[res];
    while (node != NULL)
    {
      if (strcmp(node->key, key) == 0)
      {
        node->value++;
        return;
      }
      node = node->next;
    
    }
  }
  
  Element *node = hashTable->elements[res];

  Element *newNode = (Element *) calloc(1, sizeof(Element));
  newNode->value = value;
  newNode->key = (Key ) calloc(256, sizeof(char));
  strcpy(newNode->key, key);
  newNode->next = node;
  hashTable->elements[res] = newNode;

}

void deleteKey(HashTable *hashTable, Key key) {
  // Cerinta 1

  long res = hashTable->hashFunction(key, hashTable->size);

  Element *node = hashTable->elements[res];

  if (strcmp(node->key, key) == 0)
  {
    hashTable->elements[res] = hashTable->elements[res]->next;
    free(node);
    return;
  }
  
  while (node != NULL && node->next != NULL)
  {
    if (strcmp(node->next->key, key) ==0)
    {
      break;
    }
    
    node = node->next; 
  }
  Element *last = node->next->next;
  Element *toBeDeleted = node->next;

  node->next = last;
  free(toBeDeleted);
  return;
}

void print(HashTable *hashTable) {
  // Cerinta 1
  for (int i = 0; i < hashTable->size; i++)
  {
    if (hashTable->elements[i] != NULL)
    {
      Element *node = hashTable->elements[i];
      printf("%d:\n",i);
      while (node != NULL)
      {
        printf("  %s : %d\n",node->key, node->value);
        node = node->next;
      }
      
    }
    
  }
  
}

void freeHashTable(HashTable *hashTable) {
  // Cerinta 1
  for (int i = 0; i < hashTable->size; i++)
  {
    Element *node = hashTable->elements[i];
    Element *last;
    while (node != NULL)
    {
      last = node;
      node = node->next;
      free(last->key);
      free(last);
    }
    
  }
  free(hashTable->elements);
  free(hashTable);
}


long hash1(Key word, long size) {
  // Cerinta 2
  long h = 0;
  for (int i = 0; i < strlen(word); i++)
  {
    h = h * 17 + word[i];
  }
  
  return h % size;
}

int main(int argc, char* argv[]) {
  HashTable *hashTable;
  FILE *f1, *f2;
  char word[256];
  long hashSize, common;

  hashSize = atoi(argv[1]);
  f1 = fopen(argv[2], "r");
  f2 = fopen(argv[3], "r");

  initHashTable(&hashTable, hashSize, &hash1);
  

  // Cerinta 3

  // ...
  while (fscanf(f1, "%s", word) != EOF) 
  { 
    put(hashTable, word, 1);
    
  }

  print(hashTable);

  // Cerinta 4

  // ...
  common = 0;

  HashTable *hashTable2;
  initHashTable(&hashTable2, hashSize, &hash1);

  while (fscanf(f2, "%s", word) != EOF) 
  {
    put(hashTable2, word, 1);
    
  }

  for (int i = 0; i < hashTable->size; i++)
  {
    if (hashTable->elements[i] != NULL)
    {
      Element *node = hashTable2->elements[i];
      while (node != NULL)
      {
        if (exists(hashTable, node->key))
        {
          Element *ATableNode = hashTable->elements[i];
          while (strcmp(ATableNode->key, node->key) != 0)
          {
            ATableNode = ATableNode->next;
          }
          
          if (ATableNode->value > node->value)
          {
            common = common + node->value;
          }
          else
          {
            common = common + ATableNode->value;
          }
          
        }
        
        node = node->next;
      }
      
    }
    
  }
  
  printf("Common words: %ld\n", common);

  freeHashTable(hashTable);
  freeHashTable(hashTable2);
  fclose(f1);
  fclose(f2);
  return 0;
}
