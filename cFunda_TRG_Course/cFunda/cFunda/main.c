#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SIZE 10

int random_number_generator (int seed);
extern int add_number_to_list(int num);
extern int create_list_of_numbers(void);
extern void add_strings_to_list(void);
extern char* get_poetry_line(int num);
extern char* get_first_word(char* line);
extern void insert_node_ascending();
extern void sort_linked_list_ascending_number(void);
extern void insert_node_descending();
extern void sort_linked_list_descending_string(void);
extern int get_number(char *word);

struct num_and_string {
int number;
char *poetry;
struct num_and_string *next;
};

struct num_and_string *ns_list;

char* number_map[10] = {"One","Two","Three","Four","Five","Six","Seven","Eight","Nine","Ten"};

int main()
{
    int randNum[SIZE];
    char filename[20];
    char fileIndex[10];
    strcpy(filename,"file_");
    struct num_and_string *temp_node;
    int len = strlen(filename);
    FILE *fp;
    // Initialize list to NULL indicating that it
    // is empty
    ns_list =NULL;

    for ( int i =0; i<SIZE; i++){
    randNum[i] = random_number_generator(i);
    filename[5]=('0'+i);
    filename[6]='\0';
    strcat(filename,".txt");
    len = strlen(filename);
    printf("%d\n",randNum[i]);
    printf("%s\n",filename);
    fp = fopen(filename,"w");
    if(fp == NULL)
    {
        printf("Error opening file: %s\n",filename);
        return -1;
    }
    fprintf(fp,"%d\n", randNum[i]);
    fclose(fp);
    }
    create_list_of_numbers();
    add_strings_to_list();
    sort_linked_list_ascending_number();
    sort_linked_list_descending_string();
    /*for ( int i =0; i<SIZE; i++){
    printf("%d\n",randNum[i]);
    printf("%s\n",filename);
    }*/
    temp_node = ns_list;
    while(temp_node != NULL)
    {
        printf("list member: string: %s\n",temp_node->poetry);
        temp_node = temp_node->next; // traverse the list
    }
    return 0;
}

int random_number_generator (int seed){
int number;
number = seed * 1103515245 + 12345;
return (unsigned int)(number/65535) % 32768;
}

int create_list_of_numbers(){
    FILE *fp;
    int randomNum, len;
    char filename[20];
    struct num_and_string *new_node, *temp_node;
    for ( int i =0; i<SIZE; i++){
    strcpy(filename,"file_");
    filename[5]=('0'+i);
    filename[6]='\0';
    strcat(filename,".txt");
    len = strlen(filename);
    printf("inside create list %d\n",randomNum);
    printf("inside create list %s\n",filename);
    fp = fopen(filename,"r");
    if(fp == NULL)
    {
        printf("Error opening file: %s\n",filename);
        return -1;
    }
    fscanf(fp,"%d", &randomNum);
    add_number_to_list(randomNum);
    fclose(fp);
    }
        temp_node = ns_list; //temp_node for traversing the list
    while(temp_node != NULL)
    {
        printf("list member: number: %d\n",temp_node->number);
        temp_node = temp_node->next; // traverse the list
    }
    return 0;
    }

int add_number_to_list(int num){
    struct num_and_string *new_node,*temp_node;
    //cast the pointer from 'vanilla' to struc type
    new_node = (struct num_and_string*)malloc(sizeof(struct num_and_string));

    if(new_node == NULL)
    {
        printf("Error allocating memory: %d\n",num);
    }
    new_node->number = num;
    new_node->poetry = NULL;
    new_node->next = NULL;

    if(ns_list == NULL){
        ns_list = new_node;
        return 0;
    }
    else
    {
    temp_node = ns_list; //temp_node for traversing the list
    while(temp_node->next != NULL)
    {
        temp_node = temp_node->next; // traverse the list
    }
    temp_node->next = new_node; // If condition passes, assign new node to last element
    }
    return 0;
}
void add_strings_to_list()
{
    struct num_and_string *temp_node;
    int i;
    i=0;
    temp_node = ns_list; //temp_node for traversing  the list
    while(temp_node->next != NULL)
    {
        temp_node->poetry = get_poetry_line(i);
        i++;
        if (temp_node->poetry != NULL)
            printf("i = %d %s\n",i,temp_node->poetry);
        temp_node = temp_node->next; // traverse the list
    }
}

char* get_poetry_line(int num)
{
    FILE *fp;
    char line[80];
    char *word, *poetry_line;
    if(num>9)
    {
        printf("Wrong arg num: %d\n", num);
        return NULL;
    }
    fp = fopen("ten_green_bottles.txt","r");
    if(fp==NULL)
    {
        printf("Error: Cannot open ten_green_bottles.txt\n");
        return NULL;
    }
    while(fgets(line,70,fp))
    {
        word = get_first_word(line);
        if (word != NULL)
        {
        if(strcmp(word, number_map[num]) == 0)
        {
            poetry_line = (char*)malloc(strlen(line) + 1);
            if(poetry_line == NULL)
            {
                printf("Error in get_poetry_line: Cannot Allocate Memory: %d", num);
                fclose(fp);
                return NULL;
            }
            strcpy(poetry_line,line);
            fclose(fp);
            return poetry_line;
        }
    }
    }
    fclose(fp);
    return NULL;
}

char* get_first_word(char* line)
{
    static char word[10];
    int i,j;
    i=0;
    j=0;
    if(line==NULL)
    {
        return NULL;
    }
    while ((line[i] != 0) && isspace(line[i]))
    {
        i++;
    } // this while loop is to bypass any spaces
    if (line[i]==0)
    {
        return NULL;
    }
    while (line[i]!=0 && isalpha(line[i]))
    {
        word[j] = line[i];
        i++; j++;
    }
    word[j]=0;
    return word;
}

void sort_linked_list_ascending_number()
{
    struct num_and_string *prev, *curr, *temp_node; //temp_node is for the node that is being removed and moved to the correct location
    if (ns_list == NULL)
        return;
    
    curr=prev=ns_list;
    
    while(curr != NULL)
    {
        if (curr->number >= prev->number) // if true, already in ascending order
        {
            prev = curr;
            curr = curr->next;
        }
        else // not ascending   (curr->number < prev->number)
        {
            temp_node = curr;
            prev->next = curr->next;
            curr= curr->next;
            insert_node_ascending(temp_node);
        }
    }
}

void insert_node_ascending(struct num_and_string *new_node)
{
    struct num_and_string *iprev, *icurr;
    if(ns_list == NULL)
        return;
    iprev=icurr=ns_list;
    
    while(icurr!= NULL)
    {
        if(new_node->number > icurr->number)
        {
            iprev = icurr;
            icurr=icurr->next;
        }
        else //new_node has to be inserted before current node because this new_node->number <= icurr->number
        {
            if(icurr==iprev)
            {
                new_node->next = icurr;
                ns_list = new_node;
            }
            else
            {
                new_node->next = icurr;
                iprev->next = new_node;
            }
            return;
        }
    }
    //new_node has to be inserted at the end of the list
    new_node->next = NULL;
    iprev->next = new_node;
    return;
}

void sort_linked_list_descending_string()
{
    struct num_and_string *prev, *curr, *temp_node; //temp_node is for the node that is being removed and moved to the correct location
    char *word;
    int curr_number, prev_number;
    
    if (ns_list == NULL)
        return;
    
    curr=prev=ns_list;
    
    while(curr != NULL)
    {
        word = get_first_word(curr->poetry);
        curr_number = get_number(word);
        
        word = get_first_word(prev->poetry);
        prev_number = get_number(word);
        if (curr_number <= prev_number) // if true, already in ascending order
        {
            prev = curr;
            curr = curr->next;
        }
        else // not descending   (curr_number > prev_number)
        {
            temp_node = curr;
            prev->next = curr->next;
            curr= curr->next;
            insert_node_descending(temp_node);
        }
    }
}

void insert_node_descending(struct num_and_string *new_node)
{
    struct num_and_string *iprev, *icurr;
    char* word;
    int icurr_number, iprev_number, new_number;
    
    if(ns_list == NULL)
        return;
    iprev=icurr=ns_list;
    
    while(icurr!= NULL)
    {
        word = get_first_word(icurr->poetry);
        icurr_number = get_number(word);
        
        word = get_first_word(iprev->poetry);
        iprev_number = get_number(word);
        
        word = get_first_word(new_node->poetry);
        new_number = get_number(word);
        
        if(new_number < icurr_number)
        {
            iprev = icurr;
            icurr=icurr->next;
        }
        else //new_node has to be inserted before current node because this new_node->number >= icurr->number
        {
            if(icurr==iprev)
            {
                new_node->next = icurr;
                ns_list = new_node;
            }
            else
            {
                new_node->next = icurr;
                iprev->next = new_node;
            }
            return;
        }
    }
    //new_node has to be inserted at the end of the list
    new_node->next = NULL;
    iprev->next = new_node;
    return;
}

int get_number(char *word)
{
    int i;
    for( i = 0; i<5; i++)
    {
       // printf("numer_map is %s",number_map[i]);
       if(strcmp(word,number_map[i]) == 0)
       {
           return i++;
       }
    }
    return 0;
}
