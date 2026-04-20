#include "inverted.h"

/* Validate input files and store valid ones in linked list */
void validate_files(char *argv[], F_node **head)
{
    int i = 1;
    FILE *fptr;

    while (argv[i] != NULL)   // Traverse command line arguments
    {
        // Check file extension
        if (strstr(argv[i], ".txt") == NULL)
        {
            printf("%s -> Invalid file (not .txt)\n", argv[i]);
            i++;
            continue;
        }

        // Check file availability
        fptr = fopen(argv[i], "r");
        if (fptr == NULL)
        {
            printf("%s -> File not available\n", argv[i]);
            i++;
            continue;
        }

        // Check if file is empty
        fseek(fptr, 0, SEEK_END);
        if (ftell(fptr) == 0)
        {
            printf("%s -> File is empty\n", argv[i]);
            fclose(fptr);
            i++;
            continue;
        }

        fclose(fptr);   // Close file after checks

        // Check duplicate file
        if (check_duplicates(*head, argv[i]) == SUCCESS)
        {
            printf("%s -> Duplicate file\n", argv[i]);
            i++;
            continue;
        }

        // Insert valid file into linked list
        insert_last(head, argv[i]);
        printf("%s -> File added successfully\n", argv[i]);

        i++;
    }
}

/* Insert a new file node at the end of linked list */
int insert_last(F_node **head, char *f_name)
{
    F_node *new = malloc(sizeof(F_node));   // Allocate memory

    if(new == NULL)
        return FAILURE;

    strcpy(new->f_name, f_name);   // Copy file name
    new->link = NULL;

    if(*head == NULL)   // If list is empty
    {
        *head = new;
        return SUCCESS;
    }

    F_node *temp = *head;

    while(temp->link != NULL)   // Traverse to last node
    {
        temp = temp->link;
    }

    temp->link = new;   // Link new node

    return SUCCESS;
}

/* Check if file already exists in linked list */
int check_duplicates(F_node *head, char *f_name)
{
    F_node *temp = head;

    while(temp != NULL)   // Traverse list
    {
        if(strcmp(temp->f_name, f_name) == 0)
        {
            return SUCCESS;   // Duplicate found
        }

        temp = temp->link;
    }

    return FAILURE;   // No duplicate found
}

/* Generate hash index based on first character of word */
int get_index(char *word)
{
    char ch = word[0];

    if(ch >= 'a' && ch <= 'z')   // Lowercase
        return ch - 'a';

    if(ch >= 'A' && ch <= 'Z')   // Uppercase
        return ch - 'A';

    return -1;   // Invalid character
}

/* Print all filenames stored in linked list */
int print_filenames(F_node *head)
{
    if(head == NULL)
    {
        printf("No files available\n");
        return FAILURE;
    }

    F_node *temp = head;

    while(temp != NULL)   // Traverse list
    {
        printf("%s\n", temp->f_name);
        temp = temp->link;
    }

    return SUCCESS;
}

/* Create a sub node for file info */
S_node* create_sub_node(char *fname)
{
    S_node *new = malloc(sizeof(S_node));   // Allocate memory

    if(new == NULL)
        return NULL;   

    strcpy(new->file_name, fname);   // Store file name
    new->word_count = 1;             // Initialize count
    new->sub_link = NULL;

    return new;
}

/* Create a main node for word info */
M_node* create_mainnode(char *word, char *f_name)
{
    M_node *new = malloc(sizeof(M_node));   // Allocate memory

    if(new == NULL)
    {
        printf("Memory not allocated\n");
        return NULL;
    }

    strcpy(new->word, word);        // Store word
    new->file_count = 1;            // Initialize file count
    new->main_link = NULL;

    // Create first sub node
    new->sub_link = create_sub_node(f_name);

    return new;
}