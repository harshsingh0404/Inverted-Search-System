#include "inverted.h"

void create_database(M_node *HT[], F_node *head)
{
    F_node *curfile = head;          // Pointer to traverse file list
    char word[25];                   // Buffer to store each word

    while(curfile != NULL)           // Loop through all files
    {
        FILE *fptr = fopen(curfile->f_name, "r");   // Open file

        if(fptr == NULL)             // Check file open error
        {
            printf("File not open\n");
            curfile = curfile->link;
            continue;
        }

        while(fscanf(fptr, "%s", word) != EOF)   // Read words from file
        {
            int index = get_index(word);         // Get hash index

            if(index < 0 || index > 25)          // Validate index
                continue;

            if(HT[index] == NULL)                // If no main node exists
            {
                HT[index] = create_mainnode(word, curfile->f_name);
            }
            else
            {
                M_node *temp = HT[index];        // Traverse main nodes

                while(temp != NULL)
                {
                    if(strcmp(temp->word, word) == 0)   // Word match found
                    {
                        S_node *sub = temp->sub_link;   // Traverse sub nodes

                        while(sub != NULL)
                        {
                            if(strcmp(sub->file_name, curfile->f_name) == 0) // File match
                            {
                                sub->word_count++;      // Increment word count
                                break;
                            }

                            if(sub->sub_link == NULL)   // End of sub list
                                break;

                            sub = sub->sub_link;
                        }

                        if(strcmp(sub->file_name, curfile->f_name) != 0) // New file entry
                        {
                            sub->sub_link = create_sub_node(curfile->f_name);
                            temp->file_count++;        // Increment file count
                        }

                        break;
                    }

                    if(temp->main_link == NULL)         // Word not found, create new main node
                    {
                        temp->main_link = create_mainnode(word, curfile->f_name);
                        break;
                    }

                    temp = temp->main_link;             // Move to next main node
                }
            }
        }

        fclose(fptr);               // Close file
        curfile = curfile->link;    // Move to next file
    }

    printf("Database created successfully\n");  // Success message
}