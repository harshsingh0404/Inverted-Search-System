/*
 * Function: save_database
 * ---------------------------------------------------------
 * Saves the inverted index database into a file.
 * Stores word, file count, and word frequency
 * in a structured format for later retrieval.
 */

#include "inverted.h"

void save_database(M_node *HT[])
{
    char fname[20];   // Buffer to store output file name

    printf("Enter file name to save database: ");
    scanf("%s", fname);

    FILE *fptr = fopen(fname, "w");   // Open file in write mode

    if(fptr == NULL)   // Check file open error
    {
        printf("Unable to open file\n");
        return;
    }

    for(int i = 0; i < 26; i++)   // Traverse hash table
    {
        M_node *temp = HT[i];     // Pointer for main node

        while(temp != NULL)       // Traverse main nodes (words)
        {
            // Write word and file count
            fprintf(fptr, "#%s;%d;", temp->word, temp->file_count);

            S_node *sub = temp->sub_link;   // Pointer for sub nodes

            while(sub != NULL)              // Traverse sub nodes (files)
            {
                // Write file name and word count
                fprintf(fptr, "%s;%d;", sub->file_name, sub->word_count);
                sub = sub->sub_link;
            }

            fprintf(fptr, "\n");   // New line for next word
            temp = temp->main_link;
        }
    }

    fclose(fptr);   // Close file

    printf("Database saved successfully\n");   // Success message
}