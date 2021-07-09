#ifndef __HUFFMAN_H__
#define __HUFFMAN_H__

#include <string.h>

typedef struct {
    unsigned char value;
    int left, right;
} HuffmanNode;

#define Item int
#define MAX_SIZE 256
// Including below so `Item` is defined.
#include "heap.h"

void computeFreqs(char *text, int size, int freqs[256]) {

    for (int i = 0; i < 256; i++)
    {
        freqs[i] = 0;
    }
    
    for (int i = 0; i < size; i++)
    {
        
        int code = text[i];
        freqs[code]++;
        //printf("%d %d || ",code, freqs[code]);
    }
    
}

int getPoz (HuffmanNode *nodes, int size, unsigned char value)
{
    int poz = -1;
    for (int i = 0; i < size; i++)
    {
        if (nodes[i].value == value)
        {
            poz = i;
        }
        
    }
    return poz;
}

HuffmanNode *makeTree(int freqs[256], int *size) {

    for (int i = 0; i < MAX_SIZE; i++)
    {
        if (freqs[i] != 0)
        {
            (*size)++;
        }
        
    }
    int capacity = *size;
    if (capacity == 0)
    {
        return NULL;
    }
    
    HuffmanNode *nodes = (HuffmanNode *) calloc((*size), sizeof(HuffmanNode));
    if (capacity == 1)
    {
        nodes[0].value = 'a';
        return nodes;
    }
    
    APriQueue minHeap = makeQueue(capacity);
    
    int len = 0;

    for (int i = 0; i < 256; i++)
    {
        if (freqs[i] != 0)
        {
            ItemType x;
            x.prior = freqs[i];
            x.content = i;
            insert(minHeap, x);
            nodes[len].value = i;
            nodes[len].left = -1;
            nodes[len].right = -1;
            len++;
        }
        
    }
    int leafNo = len;
    while (minHeap->size >= 2)
    {
        
        ItemType last1 = removeMin(minHeap);
        ItemType last2 = removeMin(minHeap);

        int poz1 = getPoz(nodes, len, last1.content);
        int poz2 = getPoz(nodes, len, last2.content);
        if (poz1 > leafNo)
        {
            nodes[poz1].value = -1;
        }
        
        if (poz2 > leafNo)
        {
            nodes[poz2].value = -1;
        }
        
        HuffmanNode newNode;
        newNode.value = last1.content + last2.content;
        newNode.left = poz1;
        newNode.right = poz2;
        if (len == *size)
        {
            (*size) = (*size) * 2;
            nodes = (HuffmanNode *) realloc(nodes, (*size) * sizeof(HuffmanNode));
            
        }
        nodes[len++] = newNode;

        ItemType toInsert;
        toInsert.content = last1.content + last2.content;
        toInsert.prior = last1.prior + last2.prior;
        insert(minHeap, toInsert);
    }
    (*size) = len;
    return nodes;
}

void createCode(int index, HuffmanNode *nodes, int size, int cInd, char *code, int *ok)
{    
    if (cInd == -1)
    {
        return;
    }
    
    if (cInd == index)
    {
        *ok = 1;
        memmove(code, code + 1, strlen(code));
        return;
    }
    if (nodes[cInd].left == -1 && nodes[cInd].right == -1)
    {
        int len = strlen(code);
        memmove(code + len - 1, code + len, strlen(code));
        return;
    }
    int leftPoz = nodes[cInd].left;
    int rightPoz = nodes[cInd].right;
    createCode(index, nodes, size, leftPoz, strcat(code, "0"), ok);
    if (code[0] != 'i')
    {
        return;
    }
    
    createCode(index, nodes, size, rightPoz, strcat(code, "1"), ok);
    if ((*ok) == 1)
    {
        return;
    }
    int len = strlen(code);
    memmove(code + len - 1, code + len, strlen(code));
}

void makeCodes(int index, HuffmanNode *nodes, char **codes, char *code) {

    int leafNo = 0;
    while (nodes[leafNo].left == -1 && nodes[leafNo].right == -1)
    {
        leafNo++;
    }
    int *ok = (int *) calloc(1, sizeof(int));
    (*ok) = 0;
   for (int i = 0; i < leafNo; i++)
    {
        strcpy(code, "i");
        (*ok) = 0;
        createCode(i, nodes, index, index, code, ok);
        strcpy(codes[i], code);
    }

}

char *compress(char *text, int textSize, HuffmanNode *nodes, int numNodes) {

    if (nodes == NULL)
    {
        return "empty text";
    }
    
    int ok = 1;
    for (int i = 0; i < textSize; i++)
    {
        if (text[i] != text[0])
        {
            ok = 0;
        }
        
    }
    if (ok)
    {
        char *encodedText = (char *) calloc(textSize, sizeof(char));
        nodes[0].value = text[0];
        for (int i = 0; i < textSize; i++)
        {
            encodedText[i] = '0';
        }
        encodedText[textSize] = '\0';
        return encodedText;
    }
    
    char **codes = (char **) calloc(MAX_SIZE, sizeof(char *));
    for (int i = 0; i < numNodes; i++)
    {
        codes[i] = (char *) calloc(MAX_SIZE, sizeof(char));
        strcpy(codes[i], "o");
    }
    char *code = (char *) calloc(MAX_SIZE, sizeof(char));
    strcpy(code, "i");
    makeCodes(numNodes - 1,nodes,codes,code);

    int len = strlen(text);
    char *encodedText = (char *) calloc(MAX_SIZE, sizeof(char));
    char c = text[0];
    int poz = getPoz(nodes, numNodes, c);
    strcpy(encodedText, codes[poz]);
    for (int i = 1; i < len; i++)
    {
        c = text[i];
        
        poz = getPoz(nodes, numNodes, c);
        strcat(encodedText, codes[poz]);
    }
    for (int i = 0; i < MAX_SIZE; i++)
    {
        free(codes[i]);
    }
    free(codes);
    free(code);
    return encodedText;
}

void findChar(char *text, HuffmanNode *nodes, int *cInd, int *seqLen, int maxL)
{
    if ((*cInd) == -1)
    {
        return;
    }
    if (maxL == (*seqLen))
    {
        return;
    }
    
    
    if (nodes[*cInd].right == -1 && nodes[*cInd].left == -1)
    {
        return;
    }
    char c = text[0];
    memmove(text, text + 1, strlen(text));
    int direction = c - '0';
    if (direction == 0)
    {
        *cInd = nodes[*cInd].left;
    }
    else
    {
        *cInd = nodes[*cInd].right;
    }
    (*seqLen)++;
    findChar(text, nodes, cInd, seqLen, maxL);

}
char *decompress(char *text, int textSize, HuffmanNode *nodes, int numNodes) {

    if (nodes == NULL)
    {
        return "";
    }
    int ok = 1;
    for (int i = 0; i < textSize; i++)
    {
        if (text[i] != text[0])
        {
            ok = 0;
        }
        
    }
    if (ok)
    {
        char *decodedText = (char *) calloc(textSize, sizeof(char));
        for (int i = 0; i < textSize; i++)
        {
            decodedText[i] = nodes[0].value;
        }
        decodedText[textSize] = '\0';
        return decodedText;
    }  

    int len = 0;
    char *normalText = (char *) calloc(100 , sizeof(char));
    int *index = (int *) calloc(1, sizeof(int));
    (*index) = numNodes - 1;
    int *seqLen = (int *) calloc(1, sizeof(int));
    (*seqLen) = 0;
    
    while (textSize - (*seqLen) > 0)
    {
        findChar(text, nodes, index, seqLen, textSize);
        normalText[len++] = nodes[*index].value;
        (*index) = numNodes - 1;
    }

    normalText[len] = '\0';
    return normalText;
}

#endif
