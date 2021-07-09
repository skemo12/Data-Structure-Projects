#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hierarchy.h"

void swap(Tree *xp, Tree *yp)
{
    Tree temp = *xp;
    *xp = *yp;
    *yp = temp;
}
int min(int num1, int num2) 
{
    return (num1 >= num2 ) ? num2 : num1;
}

void bubbleSort(Tree team[], int n)
{
   // print_team(team,n,f);
    //fprintf(f,"\n");
    int i, j;
  //  int okay;
    //int k;
    for (i = 0; i < n-1; i++) {  
       // Last i elements are already in place   
       for (j = 0; j < n - i - 1; j++)  {
           //printf("%s ", team[j]->name);
            int len = strlen(team[j]->name);
            int len1 = strlen(team[j + 1]->name);
            int min_len = min(len, len1);
            int k;
            //okay = 0;
            if(!strncmp(team[j]->name, team[j + 1]->name, min_len)) {
                if(len > len1) {
                    swap(&team[j], &team[j+1]);
                }
            } else {
                for(k = 1; k <= min_len; k++) {
                    
                    if(strncmp(team[j]->name, team[j + 1]->name, k) > 0) {
                       // okay = 1;
                        swap(&team[j], &team[j+1]);
                        
                        k = min_len + 1;
                    }
                }
            }

        }
   }
}



/////////////// VERIFICA UNICITATEA NUMELUI /////////////// 
int check_unicity1(Tree tree, char *employee_name) {
    
    for(int i = 0; i < tree->direct_employees_no; i++) {
        if(tree->team[i]->name == employee_name) {
            return 0;
        }
    }
    return 1;

}

/* Adauga un angajat nou in ierarhie.
 * 
 * tree: ierarhia existenta
 * employee_name: numele noului angajat
 * manager_name: numele sefului noului angajat
 *
 * return: intoarce ierarhia modificata. Daca tree si manager_name sunt NULL, 
           atunci employee_name e primul om din ierarhie.
 */

Tree hire(Tree tree, char *employee_name, char *manager_name) {
    Tree new_node;
  
    if(tree == NULL) {
        new_node = (TreeNode*)malloc(sizeof(TreeNode)); 
        new_node->direct_employees_no = 0;
        new_node->team = NULL;
        new_node->name = malloc(15*sizeof(char));
        strcpy(new_node->name,  employee_name);
        new_node->manager = NULL;
        tree = new_node;
        return tree;
    }

    int check = 0;
    check = check_unicity1(tree, employee_name);

    int no_of_direct_employees = tree->direct_employees_no;
        
    if(check == 1) {
        if(strcmp(tree->name, manager_name) == 0) {
            
            // am creat un nod cu datele persoanei pe care dorim sa o angajam
            new_node = malloc(sizeof(TreeNode));
            new_node->name = malloc(15*sizeof(char));
            strcpy(new_node->name,  employee_name);
            new_node->direct_employees_no = 0;
            new_node->manager = tree;
            

            if(tree->direct_employees_no == 0) {
                tree->team = calloc(tree->direct_employees_no + 1, sizeof(Tree));
                tree->team[tree->direct_employees_no] = new_node;
                tree->direct_employees_no++;
            } else {
                no_of_direct_employees++;
                tree->team = realloc(tree->team,no_of_direct_employees * sizeof(Tree)); 
                tree->team[tree->direct_employees_no] = new_node;
               
                tree->direct_employees_no++;
                bubbleSort(tree->team, tree->direct_employees_no);
               // selectionSort(tree->team, tree->direct_employees_no);
             //   team_ordered(&tree->team, tree->direct_employees_no,new_node);
               // tree->direct_employees_no++;
            }
        } else {
            for(int j = 0; j < tree->direct_employees_no; j++) {
                hire(tree->team[j],employee_name,manager_name);
            }
        }
    }
    return tree;
    
}


//////// VERIFICA UNCITATEA NUMELUI FIECARUI ANGAJAT //////// 
int check_unicity(Tree tree, char *employee_name) {
    static int a = -1;
    for(int i = 0; i < tree->direct_employees_no; i++) {
       if(!strcmp(tree->team[i]->name, employee_name)) {
            a = 0;
       } 
        check_unicity(tree->team[i], employee_name);
    }
    if(a == 0) {
        return 0;
    } else {
        return 1;
    }
    
   // return 1;

}

int number_employees(char *employee_name, Tree manager) {
    for(int i = 0; i < manager->direct_employees_no; i++) {
        if(strcmp(employee_name, manager->team[i]->name) == 0) {
            return i;
        }
    }
    return -1;
}

/* Sterge un angajat din ierarhie.
 * 
 * tree: ierarhia existenta
 * employee_name: numele angajatului concediat
 *
 * return: intoarce ierarhia modificata.
 */
Tree fire(Tree tree, char *employee_name) {
    // cazul in care nu exista niciun angajat
    if(tree == NULL) {
        return NULL;
    }

    
    if(strcmp(tree->name, employee_name) == 0) {
        // cazul in care se doreste concedierea CEO-ul (nodul radacina) -> lucru care nu e posibil
        if(tree->manager == NULL) {
           return tree;  
        } else {
            //verificam daca nu este manager si il stergem daca nu e
            if(tree->direct_employees_no == 0) {
                //verificam al catelea angajat este din punct de vedere alfabetic in echipa in care este
                //repartizat
                int no_employees = 0;
                no_employees = number_employees(employee_name, tree->manager);
                for(int i = no_employees; i < tree->manager->direct_employees_no - 1; i++) {
                    tree->manager->team[i] = tree->manager->team[i + 1];
                } 
                tree->manager->team[tree->manager->direct_employees_no - 1] = NULL;
                tree->manager->direct_employees_no--;
                Tree manager = tree->manager;
                destroy_tree(tree);
                if (manager->direct_employees_no == 0)
                {
                    free(manager->team);
                }
                

                return tree;
            } else {
               for(int i = 0; i < tree->direct_employees_no; i++) {
                   hire(tree->manager, tree->team[i]->name, tree->manager->name);
                   if(tree->team[i]->direct_employees_no != 0) {
                       for(int j = 0; j < tree->team[i]->direct_employees_no; j++) {
                            hire(tree->manager, tree->team[i]->team[j]->name, tree->team[i]->name);
                        }
                    }
                }
                int no_employees = 0;
                no_employees = number_employees(employee_name, tree->manager);
                for(int i = no_employees; i < tree->manager->direct_employees_no - 1; i++) {
                    tree->manager->team[i] = tree->manager->team[i + 1];
                }
                tree->manager->direct_employees_no--;
                destroy_tree(tree);
                

                return tree; 
            }
        }
    }

    // cazul in care se doreste concedierea unei persoane care nu lucreaza in cadrul companiei
    // check = 1 -> nu exista un angajat cu numele respectiv
    // check = 0 -> exista
    int check = 0;
    check = check_unicity(tree,employee_name);
    if(check == 1) {
        return tree;
    } else {
        if(tree->name != employee_name) {
            
            for(int i = 0; i < tree->direct_employees_no; i++) {
                fire(tree->team[i], employee_name);
            }
        }
    }

    return tree;
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
    
    if(tree == NULL) {
        return tree;
    }
    static Tree copy;
    if(tree->manager == NULL) {
        copy = tree;
    }
    if(!strcmp(employee_name, tree->name) && tree->manager == NULL) {
     //   fprintf(f,"\n Nu se poate promova CEO-ul \n");
        return tree;
    }
    if(!strcmp(employee_name, tree->name)  && tree->manager->manager == NULL) {
       // fprintf(f,"\n Nu se pot promova angajatii de pe nivelul 1 \n");
        return tree;
    }

    char *future_manager;
    // cazul in care se poate efectua promovarea 
    if(!strcmp(employee_name, tree->name)) {
        future_manager = tree->manager->manager->name;
        //fprintf(f,"\n Future manager %s \n", future_manager);
       // new_node = tree;
        fire(copy, employee_name);
        hire(copy, employee_name, future_manager);
        return copy;
        //print_node(new_node, f); 
    }


    // cazul in care se doreste promovarea unei persoane care nu lucreaza in cadrul companiei
    // check = 1 -> nu exista un angajat cu numele respectiv
    // check = 0 -> exista
    int check = 0;
    check = check_unicity(tree,employee_name);
    if(check == 1) {
        return tree;
    } else {
        if(tree->name != employee_name) {
            
            for(int i = 0; i < tree->direct_employees_no; i++) {
                promote(tree->team[i], employee_name);
            }
        }
    }
    

    return tree;
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
    if(tree == NULL) {
        return tree;
    }
    if(tree->manager == NULL && !strcmp(employee_name, tree->name)) {
        return tree;
    }
    static Tree copy;
    if(tree->manager == NULL) {
        copy = tree;
    }
    if(!strcmp(employee_name, tree->name)) {
        if(!strcmp(tree->manager->name, new_manager_name)) {
            return tree;
        } else {
          //  new_node = tree;
            fire(copy,employee_name);
            hire(copy,employee_name, new_manager_name);
            
            return copy;   
        }
    }
     // cazul in care se doreste mutarea unei persoane care nu lucreaza in cadrul companiei
    // check = 1 -> nu exista un angajat cu numele respectiv
    // check = 0 -> exista
    int check = 0;
    check = check_unicity(tree,employee_name);
    if(check == 1) {
        return tree;
    } else {
        if(strcmp(tree->name, employee_name)) {
            
            for(int i = 0; i < tree->direct_employees_no; i++) {
                move_employee(tree->team[i], employee_name,new_manager_name);
            }
        }
    }
    return tree;
}

Tree search_employee(Tree tree, char *employee_name, int i) {
    if(tree == NULL) {
        return NULL;
    }
    if(i == 0) {
        if(!strcmp(tree->name,employee_name)) {
            i = 1;
            return tree;
        } else {
            for(int j = 0; j < tree->direct_employees_no; j++) {   
                Tree a = search_employee(tree->team[j], employee_name , 0);
                if(a != NULL) {
                    if(!strcmp(tree->name,employee_name)) {
                        return tree;
                    } else {
                        return search_employee(tree->team[j], employee_name, 0);
                    }
                }
            }
            
        }
    }
    return NULL;
}
Tree delete(Tree tree, Tree new_node,char *old_manager_name) {

        int no_employees1 = number_employees(new_node->name, tree);
        int no = tree->direct_employees_no;
        for(int i = no_employees1; i < no - 1; i++) {
            tree->team[i] = tree->team[i + 1];
        } 
        tree->direct_employees_no--;
        if (tree != NULL && tree->direct_employees_no == 0)
        {
            free(tree->team);
        }
        return tree;
 

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
      if(tree == NULL) {
        return tree;
    }
    // cazul CEO-ului
    if(tree->manager == NULL && !strcmp(tree->name,employee_name)) {
        return tree;
    }
    static Tree new_node = NULL;
    static Tree old_manager = NULL;
    static Tree new_manager = NULL;
    if(tree->manager == NULL) {
     //   copy_tree = tree;
        new_node = search_employee(tree, employee_name, 0);
        if (new_node == NULL)
        {
            //printf("Sunt null");
            return tree;
        }
        
        old_manager = search_employee(tree, new_node->manager->name, 0);
        new_manager = search_employee(tree,new_manager_name,0);
    }
    
    delete(old_manager,new_node, old_manager->name);
   // introduce(tree,new_node,new_manager,f);
    if (new_manager->direct_employees_no == 0)
    {
        new_manager->team = (Tree*)calloc(new_manager->direct_employees_no + 1, sizeof(Tree));
    }
    else
    {
        new_manager->team = (Tree*)realloc(new_manager->team,(new_manager->direct_employees_no + 1) *sizeof(Tree));
    }
    
    new_node->manager = new_manager;
    new_manager->team[new_manager->direct_employees_no] = new_node;
    new_manager->direct_employees_no++;
    
    //team_ordered1(&new_manager->team,new_manager->direct_employees_no, new_node);
    bubbleSort(new_manager->team,new_manager->direct_employees_no);
    return tree;
}

/* Concediaza o echipa din ierarhie.
 * 
 * tree: ierarhia existenta
 * employee_name: numele angajatului din varful echipei concediate
 *
 * return: intoarce ierarhia modificata.
 */
Tree fire_team(Tree tree, char *employee_name) {
     if(tree == NULL) {
        return tree;
    }
    // cazul CEO-ului
    if(tree->manager == NULL && !strcmp(tree->name,employee_name)) {
        return tree;
    }
     static Tree new_node = NULL;
  //  static Tree copy_tree = NULL;
    static Tree old_manager = NULL;
    if(tree->manager == NULL) {
   //     copy_tree = tree;
        new_node = search_employee(tree, employee_name, 0);
        if (new_node == NULL)
        {
            return tree;
        }
        
        old_manager = search_employee(tree, new_node->manager->name, 0);
    }
    
    delete(old_manager,new_node, old_manager->name);
    destroy_tree(new_node);

    return tree;
}
int size(Tree tree);
void introduce_into_ordered_array(Tree t,Tree subtree_to_be_displayed,char *first_name, FILE *f) {
    static int  number_of_nodes = 0;
    if(!strcmp(subtree_to_be_displayed->name, first_name)) {
        number_of_nodes = size(subtree_to_be_displayed);
    }
    

    hire(t,subtree_to_be_displayed->name,"Not_a_name");

    for(int i = 0; i < subtree_to_be_displayed->direct_employees_no; i++) {
        introduce_into_ordered_array(t,subtree_to_be_displayed->team[i], first_name,f);   
    }
    if(subtree_to_be_displayed->manager == NULL || !strcmp(subtree_to_be_displayed->name,first_name)) {
      //  preorder_traversal(f,t);
        for(int i = 0; i < number_of_nodes; i++) {
            fprintf(f,"%s ", t->team[i]->name);
        }
        fprintf(f,"\n");
    } 

}


/* Afiseaza toti angajatii sub conducerea unui angajat.
 * 
 * f: fisierul in care se va face afisarea
 * tree: ierarhia existenta
 * employee_name: numele angajatului din varful echipei
 */
void get_employees_by_manager(FILE *f, Tree tree, char *employee_name) {
   Tree subtree_to_be_displayed = search_employee(tree, employee_name,0);
    if(subtree_to_be_displayed == NULL) {
        fprintf(f,"\n");
    } else {
  
    Tree t = hire(NULL, "Not_a_name", NULL);
    introduce_into_ordered_array(t,subtree_to_be_displayed,subtree_to_be_displayed->name, f);
    destroy_tree(t);
    }
    
    return;
}

/* Afiseaza toti angajatii de pe un nivel din ierarhie.
 * 
 * f: fisierul in care se va face afisarea
 * tree: ierarhia existenta
 * level: nivelul din ierarhie
 */
void get_employees_by_level(FILE *f, Tree tree, int level) {
    if(level < 0) {
        fprintf(f,"\n");
        return;
    }
    
    static Tree t = NULL;
    static int j = 0;
    if(tree->manager == NULL) {
        t = hire(NULL, "No_name", NULL);
        j = 0;
    }
    if(tree == NULL) {
        return;
    }
    if(level == 0) {
        j++;
        hire(t,tree->name,"No_name");
    } else {
        for(int i = 0; i < tree->direct_employees_no; i++) {
            get_employees_by_level(f,tree->team[i],level - 1);
        }
    }


    if(tree->manager == NULL) {
        for(int i = 0; i < j; i++) {
            fprintf(f,"%s ",t->team[i]->name);
        }
        fprintf(f,"\n"); 
        destroy_tree(t);
    }
}

/* Afiseaza angajatul cu cei mai multi oameni din echipa.
 * 
 * f: fisierul in care se va face afisarea
 * tree: ierarhia existenta
 */
void get_best_manager(FILE *f, Tree tree) {
     if(tree == NULL) {
        return;
    }
    if(tree->manager == NULL && tree->direct_employees_no == 0) {
        fprintf(f,"%s ", tree->name);
        //fprintf(f,"\n");
    }
    static int no_max_employees = 0;
    static Tree t = NULL;
    static int j = 0;
    if(tree->manager == NULL) {
        t = hire(NULL, "No_name", NULL);
        j = 0;
        no_max_employees = -1;
    }
    
    if(tree->direct_employees_no != 0) {
        if(tree->direct_employees_no > no_max_employees) {
            no_max_employees = tree->direct_employees_no;
            if(t->direct_employees_no != 0) {
                for(int k = 0; k < j; k++) {
                    fire(t, t->team[k]->name);
                }
            }
            j = 1;
            hire(t, tree->name, "No_name");
        } else if(tree->direct_employees_no == no_max_employees) {
            j++;
            hire(t,tree->name,"No_name");
        }
    } 
    for(int i = 0; i < tree->direct_employees_no; i++) {
        get_best_manager(f,tree->team[i]);
    }
    if(tree->manager == NULL) {
       // fprintf(f,"J este %d\n ", j);
        for(int k = 0; k < j; k++) {
            fprintf(f,"%s ", t->team[k]->name);
        }
        fprintf(f,"\n");
        destroy_tree(t);
    } 
    return; 
}


Tree organize(Tree new_manager, Tree old_tree, char *manager_name, char *root) {
 //   fprintf(f,"\n Name_manager %s\n", manager_name);
    if(!strcmp(manager_name, root)) {
       // fprintf(f,"Aici intra");
        if (new_manager->direct_employees_no == 0)
        {
            new_manager->team = calloc(new_manager->direct_employees_no + 1,  sizeof(Tree));
        }
        else
        {
            new_manager->team = realloc(new_manager->team,(new_manager->direct_employees_no + 1) *sizeof(Tree));
        }
        
        new_manager->team[new_manager->direct_employees_no] = old_tree;
        old_tree->manager = new_manager;
        new_manager->direct_employees_no++;
        bubbleSort(new_manager->team, new_manager->direct_employees_no);
        return new_manager;
    } 
    char *copy = manager_name;
    Tree subtree_employee = search_employee(old_tree,manager_name, 0);
    delete(subtree_employee->manager,subtree_employee, subtree_employee->manager->name);
    manager_name = subtree_employee->manager->name;

    subtree_employee->manager = NULL;
   
    if (new_manager->direct_employees_no == 0)
    {
        new_manager->team = calloc(new_manager->direct_employees_no + 1, sizeof(Tree));
    }
    else
    {
        new_manager->team = realloc(new_manager->team,(new_manager->direct_employees_no + 1) *sizeof(Tree));
    }
    
    new_manager->team[new_manager->direct_employees_no] = subtree_employee;
    subtree_employee->manager = new_manager;
    new_manager->direct_employees_no++;
   
    bubbleSort(new_manager->team, new_manager->direct_employees_no);
   // fprintf(f,"\nNew_manager->name este %s\n", new_manager->name);
   // print_team(new_manager->team,new_manager->direct_employees_no,f);
    
 //   fprintf(f,"Manager_name is %s", manager_name);
     if(manager_name == NULL) {
      //  fprintf(f," intra aiciiiii");
        return new_manager;
    } else {
        for(int i = 0; i < new_manager->direct_employees_no; i++) {
            if(!strcmp(new_manager->team[i]->name,copy))
                organize(new_manager->team[i], old_tree, manager_name,root);
        }
        //return b;
    }
    
    return new_manager;
   // return new_manager;
}
/* Reorganizarea ierarhiei cu un alt angajat in varful ierarhiei.
 * 
 * tree: ierarhia existenta
 * employee_name: numele angajatului care trece in varful ierarhiei
 */
Tree reorganize(Tree tree, char *employee_name) {
     if(tree == NULL) {
        return tree;
    }
    Tree employee_tree = search_employee(tree, employee_name, 0);
    if(employee_tree == NULL) {
        return tree;
    } else {
        // cazul CEO-ului
        if(employee_tree->manager == NULL) {
            return tree;
        }
        // angajat direct al CEO-ului
        if(employee_tree->manager->manager == NULL) {
            delete(employee_tree->manager,employee_tree, employee_tree->manager->name);
            employee_tree->manager = NULL;
            if (employee_tree->direct_employees_no == 0)
            {
                employee_tree->team = calloc(employee_tree->direct_employees_no + 1, sizeof(Tree));
            }
            else
            {
                employee_tree->team = realloc(employee_tree->team,(employee_tree->direct_employees_no + 1) *sizeof(Tree));
            }
            

            employee_tree->team[employee_tree->direct_employees_no] = tree;
            tree->manager = employee_tree;
            employee_tree->direct_employees_no++;

            bubbleSort(employee_tree->team, employee_tree->direct_employees_no);
            return employee_tree;
          
        } else {
            delete(employee_tree->manager, employee_tree, employee_tree->manager->name);

            char *manager_name;
            manager_name = employee_tree->manager->name;
            employee_tree->manager = NULL;
            organize(employee_tree, tree, manager_name, tree->name);
            return employee_tree;
        }
    }
    return tree;;
}


/////////////// VERIFICA CATE NODURI ARE ARBORELE ///////////////
int size(Tree tree) {
    if(tree == NULL) {
        return 0;
    }
    int res = 0;
    res++;

    for(int i = 0; i < tree->direct_employees_no; i++) {
        res = res + size(tree->team[i]);
    }
    return res;   
}

/* Parcurge ierarhia conform parcurgerii preordine.
 *
 * f: fisierul in care se va face afisarea
 * tree: ierarhia existenta
 */

void preorder_traversal(FILE *f, Tree tree) {
   if(tree == NULL) {
        return;
    }
    static int  number_of_nodes = 0;
    if(tree->manager == NULL) {
        number_of_nodes = size(tree);
    }
    
    if(tree->manager == NULL) {
        number_of_nodes--;
        fprintf(f,"%s ", tree->name); 
    /*    if(tree->direct_employees_no == 0) {
            fprintf(f,"\n");
        } */
    } else {
        number_of_nodes--;
        fprintf(f,"%s-%s ",tree->name,tree->manager->name);
    }

    for(int i = 0; i < tree->direct_employees_no; i++) {
        preorder_traversal(f,tree->team[i]);   
     /*   if(number_of_nodes == 0) {
             fprintf(f,"\n");
            return;
        } */
    }
    if(tree->manager == NULL) {
        fprintf(f,"\n");
    }
    
}

/* Elibereaza memoria alocata nodurilor din arbore
 *
 * tree: ierarhia existenta
 */

void destroy_tree(Tree tree) {
    if(tree == NULL) {
        return;
    }

    for(int i = 0; i < tree->direct_employees_no; i++) {
        destroy_tree(tree->team[i]);
    }
     if (tree == NULL)
    {
        return;
    }
    
    free(tree->name);
    if (tree->direct_employees_no != 0)
    {
        free(tree->team);
    }
    
    free(tree); 
    return;
}


