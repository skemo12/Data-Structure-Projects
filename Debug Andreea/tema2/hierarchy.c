#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hierarchy.h"


/* Adauga un angajat nou in ierarhie.
 * 
 * tree: ierarhia existenta
 * employee_name: numele noului angajat
 * manager_name: numele sefului noului angajat
 *
 * return: intoarce ierarhia modificata. Daca tree si manager_name sunt NULL, 
           atunci employee_name e primul om din ierarhie.
 */

Tree PointerToManager(Tree tree, char *manager_name)
{
    if (tree == NULL)
        return NULL;
    if (strcmp(tree->name, manager_name) == 0)
        return tree;

    Tree result;
    for(int i = 0; i < tree->direct_employees_no; i++) 
    {
        result = PointerToManager(tree->team[i], manager_name);
        if(result == NULL)
            continue;

        if (strcmp(result->name, manager_name) == 0) 
            return result;
        
    }
    return NULL;
}
Tree add_node(char *employee_name)
{
    Tree Node = (Tree)malloc(sizeof(TreeNode));

    Node->name = (char*)malloc(10 * sizeof(char));
    strcpy(Node->name, employee_name);
    Node->manager = NULL;
    Node->team = NULL;
    Node->direct_employees_no = 0;

    return Node;
}
Tree hire(Tree tree, char *employee_name, char *manager_name) 
{
    printf("Employee %s ManName %s ||", employee_name, manager_name);
    if(tree == NULL  && manager_name == NULL)
    {
        printf("Special %s \n", employee_name);
        tree = add_node(employee_name);
        return tree;
    }
    Tree Node = add_node(employee_name);
    Node->manager = PointerToManager(tree, manager_name);
    
    if (Node->manager == NULL)
    {   
        printf("NULL");
        return tree;
    }
    printf(" ManRes %s \n", Node->manager->name);
    Node->manager->team = (Tree*)realloc(Node->manager->team, (Node->manager->direct_employees_no+1) * sizeof(Tree));
    Node->manager->team[Node->manager->direct_employees_no++] = Node;

    for(int i = 0; i < Node->manager->direct_employees_no - 1; i++)
        for(int j = i + 1; j < Node->manager->direct_employees_no; j++)
            if(strcmp(Node->manager->team[i]->name, Node->manager->team[j]->name) > 0)
            {
                Tree aux = Node->manager->team[i];
	            Node->manager->team[i] = Node->manager->team[j];
	            Node->manager->team[j] = aux;
            }
    return tree;
}

/* Sterge un angajat din ierarhie.
 * 
 * tree: ierarhia existenta
 * employee_name: numele angajatului concediat
 *
 * return: intoarce ierarhia modificata.
 */
Tree fire(Tree tree, char *employee_name) 
{
    return NULL;
}

/* Promoveaza un angajat in ierarhie. Verifica faptul ca angajatul e cel putin 
 * pe nivelul 2 pentru a putea efectua operatia.
 * 
 * tree: ierarhia existenta
 * employee_name: numele noului angajat
 *
 * return: intoarce ierarhia modificata.
 */
Tree promote(Tree tree, char *employee_name) {
    return NULL;
}

/* Muta un angajat in ierarhie.
 * 
 * tree: ierarhia existenta
 * employee_name: numele angajatului
 * new_manager_name: numele noului sef al angajatului
 *
 * return: intoarce ierarhia modificata.
 */
Tree move_employee(Tree tree, char *employee_name, char *new_manager_name) {
    return NULL;
}

/* Muta o echipa in ierarhie.
 * 
 * tree: ierarhia existenta
 * employee_name: numele angajatului din varful echipei mutate
 * new_manager_name: numele noului sef al angajatului
 *
 * return: intoarce ierarhia modificata.
 */
Tree move_team(Tree tree, char *employee_name, char *new_manager_name) {
    return NULL;
}

/* Concediaza o echipa din ierarhie.
 * 
 * tree: ierarhia existenta
 * employee_name: numele angajatului din varful echipei concediate
 *
 * return: intoarce ierarhia modificata.
 */
Tree fire_team(Tree tree, char *employee_name) {
    return NULL;
}

/* Afiseaza toti angajatii sub conducerea unui angajat.
 * 
 * f: fisierul in care se va face afisarea
 * tree: ierarhia existenta
 * employee_name: numele angajatului din varful echipei
 */
void get_employees_by_manager(FILE *f, Tree tree, char *employee_name) {
    return;
}

/* Afiseaza toti angajatii de pe un nivel din ierarhie.
 * 
 * f: fisierul in care se va face afisarea
 * tree: ierarhia existenta
 * level: nivelul din ierarhie
 */
void get_employees_by_level(FILE *f, Tree tree, int level) {
    return;
}

/* Afiseaza angajatul cu cei mai multi oameni din echipa.
 * 
 * f: fisierul in care se va face afisarea
 * tree: ierarhia existenta
 */
void get_best_manager(FILE *f, Tree tree) {
    return;
}

/* Reorganizarea ierarhiei cu un alt angajat in varful ierarhiei.
 * 
 * tree: ierarhia existenta
 * employee_name: numele angajatului care trece in varful ierarhiei
 */
Tree reorganize(Tree tree, char *employee_name) {
    return NULL;
}

void preorder_traversal(FILE *f, Tree tree) 
{
   
    if(tree == NULL)
        return;
    int nr = tree->direct_employees_no;
    if (tree->manager == NULL)
            fprintf(f, "%s ", tree->name);
    if (nr == 0 && tree->manager != NULL)
    {
        fprintf(f, "%s-%s ", tree->name, tree->manager->name);
        return;
    }
    else
    { 
        if (tree->manager != NULL)
            fprintf(f, "%s-%s ", tree->name, tree->manager->name);
    for(int i = 0; i < nr; i++)
    {       
        
        preorder_traversal(f, tree->team[i]);    
    }

    }
    if (tree->manager == NULL)
        fprintf(f, "\n");
}

/* Elibereaza memoria alocata nodurilor din arbore
 *
 * tree: ierarhia existenta
 */
void destroy_tree(Tree tree) {
    return;
}

