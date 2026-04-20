#include "inverted.h"

void display_database(M_node *HT[])
{
    int flag = 0;   // Flag to check if database is empty

    for(int i = 0; i < 26; i++)   // Traverse all hash indices
    {
        if(HT[i] != NULL)         // Check if index has data
        {
            flag = 1;

            printf("\nIndex [%d]:\n", i);

            M_node *temp = HT[i];   // Pointer for main node traversal

            while(temp != NULL)     // Traverse main nodes (words)
            {
                printf("Word: %s | File Count: %d\n",
                        temp->word, temp->file_count);

                S_node *sub = temp->sub_link;   // Pointer for sub nodes

                while(sub != NULL)              // Traverse sub nodes (files)
                {
                    printf("   File: %s | Count: %d\n",
                            sub->file_name, sub->word_count);  
                    sub = sub->sub_link;
                }

                temp = temp->main_link;   // Move to next word
            }
        }
    }

    if(flag == 0)   // If no data found in hash table
    {
        printf("Database is empty\n");
    }
}