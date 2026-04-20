/*
 * Function: search_database
 * ---------------------------------------------------------
 * Searches for a given word in the inverted index database.
 * Displays the files in which the word is present along
 * with its occurrence count in each file.
 */

#include "inverted.h"

void search_database(M_node *HT[])
{
    char word[25];   // Buffer to store search word

    printf("Enter the word to search: ");
    scanf("%s", word);

    int index = get_index(word);   // Get hash index

    if(index < 0 || index > 25)   // Validate index
    {
        printf("Invalid word\n");
        return;
    }

    M_node *temp = HT[index];   // Pointer for main node traversal

    if(temp == NULL)   // No data at this index
    {
        printf("Word not found in database\n");
        return;
    }

    while(temp != NULL)   // Traverse main nodes (words)
    {
        if(strcmp(temp->word, word) == 0)   // Word match found
        {
            printf("\nWord found!\n");
            printf("Word: %s\n", temp->word);
            printf("Found in %d file(s)\n", temp->file_count);

            S_node *sub = temp->sub_link;   // Pointer for sub nodes

            while(sub != NULL)              // Traverse sub nodes (files)
            {
                printf("File: %s -> Count: %d\n",
                        sub->file_name, sub->word_count);
                sub = sub->sub_link;
            }

            return;   // Exit after finding word
        }

        temp = temp->main_link;   // Move to next word
    }

    printf("Word not found in database\n");   // If not found after traversal
}