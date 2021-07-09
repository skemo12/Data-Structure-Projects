#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Card {
    int value;
    int size;
    char name;
    char color;
    struct Card *next;
} Pack, *APack;

void afis(APack pack, FILE *output)
{
    // Afiseaza un pachet, verificand la final ca pachetul se termina cu NULL

    APack list = pack;
    if (pack == NULL)
    {
        return;
    }
    
    for (int i = 0; i < pack->size; i++)
    {
        fprintf(output,"%c%c",list->name, list->color);
        list = list->next;
        if (i != pack->size -1)
        {
            fprintf(output," ");
        }
        
    }
    fprintf(output,"\n");
    if (list != NULL)
    {
        fprintf(output,"error\n");
    }   
    
}

void destroy(APack pack)
{
    // Functie ce distruge un pachet de carti

    while(pack != NULL)
    {
        APack current = pack;
        pack = pack->next;
        free(current);
    }
}

APack generatePack()
{
    // Functie ce reeaza pachetul initial de carti

    char names[15] = "AKQJT98765432";
    char types[5] = "shcd";
    int cardValue = 16;
    APack pack = (APack) calloc(1,sizeof(Pack));
    APack head = pack;

    for (int i = 0; i < 13; i++)
    {
        cardValue--;
        if (names[i] == 'T')
        {
            cardValue--;
        }
        
        for (int j = 0; j < 4; j++)
        {
            pack->name = names[i];
            pack->color = types[j];
            pack->value = cardValue;
            pack->size = 52;
            if (names[i] == '2' && types[j] == 'd')
            {
                pack->next = NULL;
            }
            else 
            {
                pack->next = (APack) calloc(1,sizeof(Pack));
                pack = pack->next;
            }
            
        }
        
    }
    
    return head;
}

void invert(APack *pack)
{
    // Functie ce inverseaza un pachet de carti

    APack prev = NULL;
    APack next = NULL;
    APack node = *pack;

    while (node != NULL)
    {
        next = node->next;
        node->next = prev;
        prev = node;
        node = next;
    }
   
    *pack = prev;
}

void intercalare(APack *pack)
{
    // Functia de amestecare de tip intercalare

    APack next, new;
    APack list = *pack;
    APack head = *pack;

    for (int i = 0; i < 26; i++)
    {
        list = list->next;
    }
    new = list;

    list = head; 
    for (int i = 0; i < 26; i++)
    {
        next = list->next;
        list->next = new;
        new = new->next;
        list->next->next = next;
        list = next;
    }

    list = head;
    for (int i = 0; i < 51; i++)
    {
        list = list->next;
    }
    list->next = NULL;    
    
    *pack = head;
    
}

void mongean(APack *pack)
{
    // Functie de amestecare de tip mongean

    APack first = *pack;
    APack last = *pack;
    APack newFirst, newLast;
    last = *pack;

    for (int i = 0; i < 26; i++)
    {
        newFirst = last->next;
        newLast = newFirst->next;
        newFirst->next = first;
        last->next = newLast;
        first = newFirst;
        last= newLast;        
    }
    
    *pack = newFirst;
    
}

void npiles(APack *pack, FILE *input)
{
    // Functie de amestecare de tip npiles

    APack head = *pack;
    APack list = *pack;
    APack newHead;

    int groupsNumber;
    fscanf(input,"%d",&groupsNumber);

    APack *toBeModified = (APack *) calloc(groupsNumber,sizeof(APack));
    APack *destinations =  (APack *) calloc(groupsNumber,sizeof(APack));

    int numElements = (*pack)->size / groupsNumber;

    int p1;
    fscanf(input,"%d",&p1);
    
    list = head;
    for (int i = 0; i < (p1 - 1) * numElements; i++)
    {
        list = list->next;
    }
    newHead = list;

    for (int i = 0; i < groupsNumber - 1; i++)
    {
        int p2;
        fscanf(input,"%d",&p2);

        list = head;
        for (int j = 0; j < p1 * numElements - 1; j++)
        {
            list = list->next;
        }
        toBeModified[i] = list;
        
        list = head;
        for (int j = 0; j < (p2 - 1) * numElements; j++)
        {
            list = list->next;
        }
        destinations[i] = list;
        p1 = p2;
    }

    for (int i = 0; i < groupsNumber - 1; i++)
    {
        toBeModified[i]->next = destinations[i];
    }

    for (int i = 0; i < numElements - 1; i++)
    {
        destinations[groupsNumber - 2] = destinations[groupsNumber -2]->next;
    }
    destinations[groupsNumber - 2]->next = NULL;

    *pack = newHead;
    
    free(toBeModified);
    free(destinations);

    
}

APack generatePlayer(APack pack, int n, int size)
{
    // Functie ce returneaza pozitia din pachet unde incepe un alt jucator

    APack head = pack;
    for (int i = 0; i < (n - 1) * size; i++)
    {
        head = head->next;
    }

    return head;
}

APack setNullAndSizePlayer(APack player, int size)
{
    /* Functie ce seteaza NULL la finalul listei de carti unui player
    si seteaza dimensiunea */

    APack list = player;
    for (int i = 0; i < size - 1; i++)
    {
        list->size = size;
        list = list->next;
    }
    list->size = size;
    list->next = NULL;

    return player;
}

APack *playersArraySizeFour(APack pack)
{
    // Functie ce creeza un vector cu 4 jucatori

    APack p1, p2, p3, p4;
    p1 = generatePlayer(pack,1,13);
    p2 = generatePlayer(pack,2,13);
    p3 = generatePlayer(pack,3,13);
    p4 = generatePlayer(pack,4,13);
    p1 = setNullAndSizePlayer(p1,13);
    p2 = setNullAndSizePlayer(p2,13);
    p3 = setNullAndSizePlayer(p3,13);
    p4 = setNullAndSizePlayer(p4,13);

    APack *v = (APack *) calloc(4,sizeof(APack));
    v[0] = p1;
    v[1] = p2;
    v[2] = p3;
    v[3] = p4;

    return v;
}

APack addCard(APack pack, APack card)
{
    /* Functie ce adauga o carte la finalul unui pachet
    si seteaza noul size */

    if (pack == NULL)
    {
        card->size = 1;
        card->next = NULL;
        return card;
    }   
    
    APack head = pack;
    int newSize = head->size + 1;

    while (pack->next != NULL)
    {
        pack->size = newSize;
        pack = pack->next;
    }
    
    pack->next = card;
    pack->next->next = NULL;
    pack->size = newSize;
    card->size = newSize;
    
    return head;
}

APack addHeadToEnd(APack pack)
{
    /* Functie ce muta inceputul unui pachet la final
    nu modifica size */

    APack head = pack;
    APack aux;

    while (pack->next != NULL)
    {
        pack = pack->next;
    }

    pack->next = head;
    aux = head->next;
    head->next = NULL;
    head = aux;

    return head;
}

APack moveHead(APack pack)
{
    /* Functie ce muta pointerul de inceput al listei cu o pozitie in dreapta
    si seteaza noul size */

    APack head = pack;
    head = head->next;
    while (pack != NULL)
    {
        pack->size--;
        pack = pack->next;
    }
    
    return head;
}

APack removeCard(APack pack, APack card)
{
    // Functie ce elemina o carte dintr-un pachet

    APack list = pack;
    if (pack == card)
    {
        return moveHead(pack);
    }
    while (list->next != card)
    {
        list->size--;
        list = list->next;
    }

    list->next = list->next->next;
    while (list != NULL)
    {
        list->size--;
        list = list->next;
    }
    return pack;
    
}

int findWarSize(APack p1, APack p2, APack card)
{
    //Functie ce calculeaza marimea razboilui

    //Taking out the card that is on the board at the moment
    int min = p1->size - 1;
    int p2size = p2->size -1;
    
    if (p2size < min)
    {
        min = p2size;
    }

    if (card->value < min)
    {
        min = card->value;
    }
    
    return min;
}

char fromValueToChar (int value)
{
    // Functie ce transmorfa un numar int in cartea corespunzatoare

    char names[15] = "23456789TJQKA";

    for (int i = 2; i < 11; i++)
    {
        if (i == value)
        {
            return names[i -2];
        }
        
    }
    for (int i = 12; i < 16; i++)
    {
        if (i == value)
        {
            return names[i - 3];
        }
        
    }
    
    return 'E';
    
}

void decideWinnerWar(APack p1, APack p2, int contor, FILE *output)
{
    // Functie ce determina castigatorul pentru Razboi

    if (p1 == NULL)
    {
        fprintf(output,"2");
        return;
    }
    if (p2 == NULL)
    {
        fprintf(output,"1");
        return;
    }
    
    if (contor == 100)
    {
        int v1[16], v2[16];
        for (int i = 0; i < 16; i++)
        {
            v1[i] = 0;
            v2[i] = 0;
        }
        
        APack head1 = p1;
        APack head2 = p2;
        for (int i = 0; i < head1->size; i++)
        {
            v1[p1->value]++;
            p1 = p1->next;
        }
        for (int i = 0; i < head2->size; i++)
        {
            v2[p2->value]++;
            p2 = p2->next;
        }
        for (int i = 15; i > 1; i--)
        {
            if (v2[i] > v1[i])
            {
                fprintf(output,"2 %c", fromValueToChar(i));
                break;
            }
            if (v2[i] < v1[i])
            {
                fprintf(output,"1 %c", fromValueToChar(i));
                break;
            }
        }
    }
}

void war(APack pack, FILE *output)
{  
    // Functie ce simuleaza jocul de razboi 

    // Initialiam pachetele celor 2 jucatori
    APack p1 = generatePlayer(pack,1,26);
    APack p2 = generatePlayer(pack,2,26);
    p1 = setNullAndSizePlayer(p1,26);
    p2 = setNullAndSizePlayer(p2,26);

    int contor = 0;
    
    // Simulare propriu zisa a jocului
    while (p1 != NULL && p2 != NULL && contor < 100)
    {
        if (p1->value > p2->value)
        {
            // Cazul in care Player 1 castiga direct
            APack card = p2;
            p2 = moveHead(p2);
            p1 = addHeadToEnd(p1);
            p1 = addCard(p1, card);
        }
        else if (p1->value < p2->value)
        {
            // Cazul in care Player 2 castiga direct
            APack card = p1;
            p1 = moveHead(p1);
            p2 = addHeadToEnd(p2);
            p2 = addCard(p2, card);
        }
        else if (p1->value == p2->value)
        {
            // Cazul de razboi
            int num = findWarSize(p1,p2,p1);
            APack newWarCardP1 = p1;
            APack newWarCardP2 = p2;
            APack *list1 = (APack *) calloc(num + 1,sizeof(APack));
            APack *list2 = (APack *) calloc(num + 1,sizeof(APack));
            for (int i = 0; i < num; i++)
            {
                list1[i] = newWarCardP1;
                newWarCardP1 = newWarCardP1->next;
                list2[i] = newWarCardP2;
                newWarCardP2 = newWarCardP2->next;
            }
            list1[num] = newWarCardP1;
            list2[num] = newWarCardP2;

            if (newWarCardP1->value > newWarCardP2->value)
            {
                // Cazul in care Player 1 castiga razboiului
                for (int i = num; i >= 0; i--)
                {
                    p1 = moveHead(p1);
                    p2 = moveHead(p2);
                }

                for (int i = num; i >= 0; i--)
                {
                    p1 = addCard(p1,list1[i]);    
                }

                for (int i = num; i >= 0; i--)
                {
                    p1 = addCard(p1,list2[i]);
                }

            }
            else
            {  
                // Cazul in care Player 2 castiga razboiului
                for (int i = num; i >= 0; i--)
                {
                    p1 = moveHead(p1);
                    p2 = moveHead(p2);
                }

                for (int i = num; i >= 0; i--)
                {
                    p2 = addCard(p2,list2[i]);
                }

                for (int i = num; i >= 0; i--)
                {
                    p2 = addCard(p2,list1[i]);
                }
        
            }

            free(list1);
            free(list2);
        }

        contor++;

    }

    // Determinarea castigatorului
    decideWinnerWar(p1,p2,contor,output);

    // Eliberarea memorie
    destroy(p1);
    destroy(p2);
}

APack searchCardToPlay(APack player, int round)
{
    // Functie ce cauta o carte ce poate fi jucata pentru Rolling Stones

    APack list = player;
    char turn[4] = "shcd";
    while (list != NULL && list->color != turn[round])
    {
        list = list->next;
    }
    return list;
}

void rollingStone(APack pack, FILE *output)
{
    // Functie ce simuleaza jocul de rolling stone

    APack *v = playersArraySizeFour(pack);    
    APack table = NULL;

    int round = 0;
    int i = 0;

    // Simulare propriu zisa a jocului
    while (v[0] != NULL && v[1] != NULL && v[2] != NULL && v[3] != NULL)
    {
        // Cautare carte de jucat
        APack list = searchCardToPlay(v[i], round);

        if(list != NULL)
        {
            // Cazul in care jucatorul are ce cartea sa joace
            APack card = list;
            v[i] = removeCard(v[i],card);
            table = addCard(table,card);
            if (v[i] == NULL)
            {
                break;
            }
            
        }
        else
        {
            // Cazul in care jucatorul nu are ce cartea sa joace
            while (table != NULL)
            {
                APack card = table;
                table = removeCard(table,card);
                v[i] = addCard(v[i],card);
            }

            round++;

            if(round == 4)
            {
                round = 0;
            }

            APack card = searchCardToPlay(v[i], round);
            while (card == NULL)
            {
                round++;

                if(round == 4)
                {
                    round = 0;
                }

                card =searchCardToPlay(v[i], round);
            }

            v[i] = removeCard(v[i],card);
            table = addCard(table,card);

        }
            
        i++;
        if (i == 4)
        {
            i = 0;
        }
        
    }

    for (int i = 0; i < 4; i++)
    {
        if (v[i] == NULL)
        {
            fprintf(output,"%d", i + 1);
        }
        
    }
    
    // Eliberarea memorie
    for (int i = 0; i < 4; i++)
    {
        destroy(v[i]);
    }
    free(v);
    destroy(table);
}

char changeDirection(char direction)
{
    /* Functie ce schimba directia de parcugere a jocului 
        de scarabeii egipteni */

    if (direction == '+')
    {
        return '-';
    }
    else
    {
        return '+';
    }
    
}

int nextTurn(int i, char direction)
{
    // Functie ce returneaza indicele urmatorului jucator
    if (direction == '+')
        {
            i++;
        }
        else
        {
            i--;
        }

        if (i == 4)
        {
            i = 0;
        }
        if (i == -1)
        {
            i = 3;
        }
        return i;
}

void scarabei(APack pack, FILE *output)
{
    // Functie ce simuleaza jocul de scarabei

    APack *v = playersArraySizeFour(pack);    
    APack table = NULL;

    char scarabei[4] = "AKQJ";
    char direction = '+';
    int prevPlayer = 0;
    int i = 0;
    int max = 13;
    int scarab = 0;

    // Simulare propriu zisa a jocului
    while (max < 52)
    {           
        APack card = v[i];
        if (card != NULL)
        {
            v[i] = removeCard(v[i],card);
            table = addCard(table,card);
        }
        else
        {
            i = nextTurn(i,direction);
            continue;
        }
        
        if (scarab)
        {
            if (strchr(scarabei, card->name) != NULL)
            {
                prevPlayer = i;
                i = nextTurn(i,direction);
                continue;
            }
            if (card->name == '8')
            {
                i = nextTurn(i,direction);
                continue;
            }
                scarab = 0;
                invert(&table);
                while (table != NULL)
                {
                    APack c = table;
                    table = removeCard(table,c);
                    v[prevPlayer] = addCard(v[prevPlayer],c);
                }
                i = prevPlayer;
            
        }
        else
        {
            if (card->name == '8')
            {
                direction = changeDirection(direction);
            }
            if (strchr(scarabei, card->name) != NULL)
            {
                scarab = 1;
                prevPlayer = i;
            }
            i = nextTurn(i,direction);
        }
        
        for (int i = 0; i < 4; i++)
        {
            if (v[i] != NULL)
            {
                if(v[i]->size > max)
                {
                    max = v[i]->size;
                }
            }
            
        }
        
    }
    // Verificare castigator
    for (int i = 0; i < 4; i++)
    {
        if (v[i] != NULL && v[i]->size == 52)
        {
            fprintf(output,"%d",i + 1);
        }
        
    }

    // Eliberarea memorie
    for (int i = 0; i < 4; i++)
    {
        destroy(v[i]);
    }
    free(v);
    destroy(table);  
}

int main() {

    FILE *input = fopen("in", "r");
    FILE *output = fopen("out","wb");
    
    char task[50];
    int n;

    APack pack = generatePack();
    fscanf(input,"%s\n%d",task,&n);

    for (int i = 0; i < n; i++)
    {
        char type[50];
        fscanf(input,"%s",type);
        switch (type[2])
        {
        case 'v':
            invert(&pack);
            break;
        case 't':
            intercalare(&pack);
            break;
        case 'n':
            mongean(&pack);
            break;
        case 'i':
            npiles(&pack,input);
            break;
        
        default:
            break;
        }
    }

    if (strcmp(task,"amestecare") == 0)
    {
        afis(pack,output);
        destroy(pack);
    }
    
    if (strcmp(task,"razboi") == 0)
    {
        war(pack,output);
    }

    if (strcmp(task,"rollingstone") == 0)
    {
        rollingStone(pack,output);
    }

    if (strcmp(task,"scarabei") == 0)
    {
        scarabei(pack,output);
    }
    
    fclose(input);
    fclose(output);
    
    return 0;
}