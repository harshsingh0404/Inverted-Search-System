#include "inverted.h"

int update_database(M_node *HT[], F_node **head)
{
    char fname[20];   // Buffer to store input file name

    printf("Enter the file name to update database: ");
    scanf("%s", fname);

    FILE *fptr = fopen(fname, "r");   // Open file in read mode

    if(fptr == NULL)   // Check file existence
    {
        printf("File not found\n");
        return FAILURE;
    }

    char line[100];   // Buffer to read each line

    while(fgets(line, sizeof(line), fptr))   // Read file line by line
    {
        line[strcspn(line, "\n")] = '\0';   // Remove newline character

        if(line[0] != '#')   // Skip invalid lines
            continue;

        char *token = strtok(line, "#;");   // Extract word
        char word[25];
        strcpy(word, token);

        token = strtok(NULL, "#;");        // Extract file count
        int file_count = atoi(token);

        int index = get_index(word);       // Get hash index

        if(index < 0 || index > 25)        // Validate index
            continue;

        // Create new main node
        M_node *new_main = malloc(sizeof(M_node));

        strcpy(new_main->word, word);
        new_main->file_count = file_count;
        new_main->main_link = NULL;
        new_main->sub_link = NULL;

        S_node *last_sub = NULL;   // Pointer to link sub nodes

        // Loop through file entries
        for(int i = 0; i < file_count; i++)
        {
            char fname[20];
            int count;

            token = strtok(NULL, "#;");
            strcpy(fname, token);        // Extract file name

            token = strtok(NULL, "#;");
            count = atoi(token);         // Extract word count

            // Create new sub node
            S_node *new_sub = malloc(sizeof(S_node));

            strcpy(new_sub->file_name, fname);
            new_sub->word_count = count;
            new_sub->sub_link = NULL;

            // Link sub nodes
            if(new_main->sub_link == NULL)
            {
                new_main->sub_link = new_sub;
            }
            else
            {
                last_sub->sub_link = new_sub;
            }

            last_sub = new_sub;

            // Add file to file list if not duplicate
            if(check_duplicates(*head, fname) == FAILURE)
            {
                insert_last(head, fname);
            }
        }

        // Insert main node into hash table
        if(HT[index] == NULL)
        {
            HT[index] = new_main;
        }
        else
        {
            M_node *temp = HT[index];

            while(temp->main_link != NULL)   // Traverse to end
            {
                temp = temp->main_link;
            }

            temp->main_link = new_main;   // Link new node
        }
    }

    fclose(fptr);   // Close file

    printf("Database updated successfully\n");   // Success message
    return SUCCESS;
}