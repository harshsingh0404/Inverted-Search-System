/*
  ---------------------------------------------------------
  Title       : Inverted Search
  Author      : Harsh Singh
  Date        : 25-03-2026
 
  Description :
  This program implements an Inverted Index using hashing.
  It processes multiple text files, stores words in a hash
  table, and maintains file-wise word occurrences.
 
  Features :
   - Validate input files (.txt only)
   - Create inverted index database
   - Display database contents
   - Search word in database
   - Save database to file
   - Update database from saved file
 */

#include "inverted.h"

int main(int argc, char *argv[])
{
    F_node *head = NULL;
    M_node *HT[26] = {NULL};

    if(argc < 2)
    {
        printf("Usage: ./a.out <file1.txt> <file2.txt> ...\n");
        return 0;
    }

    validate_files(argv, &head);

    if(head == NULL)   
    {
        printf("No valid files to process\n");
        return 0;
    }

    int option;
    int created = 0;   

    do
    {
        printf("\n1.Create\n2.Display\n3.Save\n4.Search\n5.Update\n6.Exit\n");
        printf("Enter choice: ");
        scanf("%d", &option);

        switch(option)
        {
            case 1:
                if(created)
                    printf("Database already created\n");
                else
                {
                    create_database(HT, head);
                    created = 1;
                }
                break;

            case 2:
                display_database(HT);
                break;

            case 3:
                save_database(HT);
                break;

            case 4:
                search_database(HT);
                break;

            case 5:
                update_database(HT, &head);
                break;

            case 6:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid option\n");
        }

    } while(option != 6);

    return 0;
}