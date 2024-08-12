#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h> 
#define DELIMETER ","


struct Address {
    char name[30];
    char surname[30];
    char email[30];
    char number[30];
    struct Address *next;
};
struct Address *create_address_node(char *name, char *surname, char *email, char *number);
struct  Address *create_address_node_from_line(char *address_line);
void add_to_list_end(struct Address **list, struct Address *node);
void add_to_list_by_poss(struct Address **list, struct Address *node, int poss);
void remove_address_node(struct Address **list, int poss);
void delete_address_book(struct Address **list);
void load_address_book(FILE *file, struct Address **list);// list dest
void print_address(struct Address *list);
struct Address *get_address_loc(struct Address *list, int loc);//?
struct Address *get_address_data(struct Address *list, char *name, char *surname, char *email, char *number);//?
void make_interactive(struct Address *list);

 extern int errno;
 //static char address_file_path[100] = "/home/studentas/addresses.csv"; 


int main(void)
{
    struct Address *list = NULL;



//     struct Address *tmp = get_address_loc(list, 9);
//     if (tmp != NULL) {
//        // printf(" %s  %s  %s  %s\n", tmp->name, tmp->surname, tmp->email, tmp->number);
//     } else {
//         printf("Address not found\n");
//     }
//     tmp = get_address_data(list,"vardenis","pavardenis","vardenis.pavardenis@gmail.com", "37061234567811");
//     if (tmp != NULL) {
//         //printf(" %s  %s  %s  %s\n", tmp->name, tmp->surname, tmp->email, tmp->number);
//     } else {
//         printf("Address not found\n");
//     }
//     remove_address_node(&list,0);
//    struct Address *tmp_node = create_address_node("gedas","viliu","rimtas.nerimtas@gmail.com","37063500639");
//     add_to_list_by_poss(list,tmp_node,11);
//      print_address(list);
    make_interactive(&list);
    return 0;
}

void load_address_book(FILE *address_file, struct Address **list)
{
    struct Address *address = NULL;// create one address
    char line[128];
    while (fgets(line, sizeof(line), address_file)){ // read line
   // puts(line);
        if(strcmp(line,"\n")==0){
            break;// empty line
        }
        
        address = create_address_node_from_line(line);
    if(address != NULL){
            add_to_list_end(list,address);
    }
    
}
}

struct Address *create_address_node_from_line(char *address_line)
{
    struct Address *address = NULL; // Corrected to match the struct name
    char *name;
    char *surname;
    char *email;
    char *number;
    name = strtok(address_line, DELIMETER);
    surname = strtok(NULL, DELIMETER);
    email = strtok(NULL, DELIMETER);
    number = strtok(NULL, DELIMETER);
    address = create_address_node(name, surname, email, number);
    return address;
}
struct Address *create_address_node(char *name, char *surname, char *email, char *number)
{
    struct Address *address = NULL;
    // memeory allocation
    address = (struct Address*)malloc(sizeof(struct Address));
    if(address==NULL)
         return NULL;
    strcpy(address->name,name);
    strcpy(address->surname,surname);
    strcpy(address->email,email);
    strcpy(address->number,number);
    address->next = NULL;
    return address;
}
void add_to_list_end(struct Address **list, struct Address *node)
{
    if (node == NULL)
    {
        printf("given data to is empty");
        return;
    }
    struct  Address *tmp = *list;// current value
    if (tmp == NULL){
        *list = node;
        return ;// added node to list
    }
    while (tmp->next != NULL){// until last element
        tmp = tmp->next;
    }
    tmp->next = node;
}

void add_to_list_by_poss(struct Address **list, struct Address *node, int poss)
{
    if (node == NULL){
        printf("given data to is empty");
        return;
    }
    struct  Address *tmp = list;
    if (tmp == NULL){//add as the first to the list???
      
        *list = node;
        return;
    }
    if(poss==0|| tmp == NULL){
        printf("%s %s\n",node->name,node->number);
        node->next = *list;
       *list = node;
        return;
    }
    poss--;
    while (tmp->next != NULL&&poss>0){
        tmp=tmp->next;
        poss--;
    }
    if (poss>0)
    {
        printf("Index was outside the bounds\nNode was insserted to the end of the list\n\n\n");
    }
    node->next = tmp->next;
    tmp->next =node;
}

void remove_address_node(struct Address **list, int poss)
{
    struct Address *curr = *list;
    if (curr==NULL) {
        printf("List is empty");
        return;
    }
    if (poss < 0) {
        printf("poss cannot be negative\n");
        return ;
    }
    if (poss == 0) {
        *list = curr->next;
        free(curr);
        return;
    }
    // move cursor infornt of removable node
    poss--;// advance cursor one node back
    while (curr->next != NULL&&poss>0) {
        curr=curr->next;
        poss--;
    }
     if (curr == NULL) {
        printf("Position exceeds list size\n");
        return;
    }
    struct Address *dell = curr->next;
    // delete at middle 
    curr->next = dell->next;
    free(dell);
}

void print_address(struct Address *list)
{
    struct Address *tmp = list;
    if (tmp == NULL){
        puts ("List is empty");
        return;
    }
    while (tmp != NULL)
    {
        printf("%s %s %s %s\n", tmp->name,tmp->surname, tmp->email,tmp->number);
        tmp = tmp->next;
    }
    
}
void delete_address_book(struct Address **list)
{
    struct Address *curr = *list;
    struct Address *next_node =NULL;

    while (curr != NULL) {
        next_node = curr->next;// update address
        free(curr);// free address   
        curr = next_node;// 
    }
    *list = NULL;// unsure that list is deleted
}
struct Address *get_address_loc(struct Address *list, int loc)
{
     struct Address *tmp = list;

    if (tmp == NULL) {
        printf("address book was empty\n");
        return NULL;
    }
    if (loc < 0) {
        printf("loc cannot be negative\n");
        return NULL;
    }
    while (loc > 0 && tmp != NULL) {
        tmp = tmp->next;
        loc--;
    }
    if (tmp == NULL) {
        printf("Index too large, exceeded list size\n");
        return NULL;
    }
    return tmp;
}
struct Address *get_address_data(struct Address *list, char *name, char *surname, char *email, char *number)//?
{
     struct Address *tmp = list;

    if (tmp == NULL) {
        printf("address book was empty\n");
        return NULL;
    }
    if ( name == NULL||surname == NULL||email == NULL||number == NULL) {
        printf("missing input data\n");
        return NULL;
    }
    while ( strcmp(name,tmp->name) != 0&&strcmp(surname, tmp->surname) != 0 && strcmp(email,tmp->email) != 0&&strcmp(number, tmp->number) != 0&&tmp != NULL) {
        tmp = tmp->next;
        if(tmp==NULL)// puts normaal error
            return NULL;
    }
    tmp = tmp->next;// set correct value to return
    if (tmp == NULL) {
        printf("There are no such entry\n");
        return NULL;
    }
    return tmp;
}
void make_interactive(struct Address *list)
{
    int action;
    printf("Hello, world!\n");
    printf("Choose action\n1-Read file\n2-Print list\n3-Add to list new node\n4-find address by poossition\n5-Find address by data\n6-Remove from list by possition\n7-Delete all list\n8-Exit\n");
    scanf("%d", &action);
    switch (action) {
    case 1:
            
       char address_file_path[100] = "/home/studentas/addresses.csv"; 

        // open the address file
        FILE * data = NULL;
        data = fopen(address_file_path, "r");

        //puts(address_file_path);  
        if( data == NULL) {// tires to read address file
            printf("Unable to open file\n");
            exit(1);
        } 
        load_address_book(data,&list);// gives curent value
        fclose(data);
        make_interactive(list);
        break;
    case 2:
            print_address(list);// prints
            make_interactive(&list);
        break;
    case 3/* constant-expression */:
        /* code */
        break;
      case 4/* constant-expression */:
        /* code */
        break;
    case 5/* constant-expression */:
        /* code */
        break;
    case 7/* constant-expression */:
        /* code */
        break;
    case 8/* constant-expression */:
        /* code */
        break;
    
    default:
    exit(1);
        break;
    } 
    printf("%d",action);
}



 