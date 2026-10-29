#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

void listContacts(AddressBook *addressBook) 
{
    if(addressBook->contactCount == 0) {
        printf("\n+------------------------------------------------------+\n");
        printf("|             ADDRESS BOOK IS EMPTY                     |\n");
        printf("+------------------------------------------------------+\n");
        return;
    }
    
    printf("\n+------------------------------------------------------+\n");
    printf("|                CONTACT SORTING OPTIONS                |\n");
    printf("|------------------------------------------------------|\n");
    printf("|  1. Sort by Name                                     |\n");
    printf("|  2. Sort by Phone                                    |\n");
    printf("|  3. Sort by Email                                    |\n");
    printf("|  4. Exit                                             |\n");
    printf("+------------------------------------------------------+\n");
    
    int choice;
    printf("\nEnter your choice for sorting: ");
    scanf("%d", &choice);
    
    switch(choice)
    {
        case 1:
            for(int i = 0; i < addressBook->contactCount - 1; i++)
            {
                for(int j = 0; j < addressBook->contactCount - i - 1; j++)
                {
                    if(strcasecmp(addressBook->contacts[j].name, addressBook->contacts[j + 1].name) > 0)
                    {
                        Contact temp = addressBook->contacts[j]; 
                        addressBook->contacts[j] = addressBook->contacts[j + 1];
                        addressBook->contacts[j + 1] = temp;
                    }
                }
            }
            printf("\nSorted by Name\n");
            break;
            
        case 2:
            for(int i = 0; i < addressBook->contactCount - 1; i++)
            {
                for(int j = 0; j < addressBook->contactCount - i - 1; j++)
                {
                    if(strcmp(addressBook->contacts[j].phone, addressBook->contacts[j + 1].phone) > 0)
                    {
                        Contact temp = addressBook->contacts[j];
                        addressBook->contacts[j] = addressBook->contacts[j + 1];
                        addressBook->contacts[j + 1] = temp;
                    }
                }
            }
            printf("\nSorted by Phone\n");
            break;
            
        case 3:
            for(int i = 0; i < addressBook->contactCount - 1; i++)
            {
                for(int j = 0; j < addressBook->contactCount - i - 1; j++)
                {
                    if(strcasecmp(addressBook->contacts[j].email, addressBook->contacts[j + 1].email) > 0)
                    {
                        Contact temp = addressBook->contacts[j];
                        addressBook->contacts[j] = addressBook->contacts[j + 1];
                        addressBook->contacts[j + 1] = temp;
                    }
                }
            }
            printf("\nSorted by Email\n");
            break;
            
        case 4:
            printf("\nExiting...\n");
            return;
            
        default:
            printf("\nInvalid choice!\n");
            return;
    }
    
    printf("\n+------------------------------------------------------+\n");
    printf("|                    CONTACT LIST                      |\n");
    printf("|------+----------------+--------------+---------------|\n");
    printf("| #    | NAME           | PHONE        | EMAIL         |\n");
    printf("|------+----------------+--------------+---------------|\n");
    
    for(int i = 0; i < addressBook->contactCount; i++)
    {
        printf("| %-4d | %-14s | %-12s | %-13s |\n",
               i + 1,
               addressBook->contacts[i].name,
               addressBook->contacts[i].phone,
               addressBook->contacts[i].email);
    }
    
    printf("+------+----------------+--------------+---------------+\n");
    printf("\nTotal Contacts: %d\n", addressBook->contactCount);
}

void initialize(AddressBook *addressBook) {
    printf("\n+------------------------------------------------------+\n");
    printf("|           ADDRESS BOOK INITIALIZATION                |\n");
    printf("+------------------------------------------------------+\n");
    
    addressBook->contactCount = 0;
    populateAddressBook(addressBook);
    loadContactsFromFile(addressBook);
    
    if(addressBook->contactCount > 0) {
        printf("Loaded %d contacts successfully!\n", addressBook->contactCount);
    } else {
        printf("No contacts loaded. Starting with empty address book.\n");
    }
}

void saveAndExit(AddressBook *addressBook) {
    printf("\n+------------------------------------------------------+\n");
    printf("|              SAVING AND EXITING                      |\n");
    printf("+------------------------------------------------------+\n");
    
    saveContactsToFile(addressBook);
    printf("Contacts saved successfully!\n");
    printf("Thank you for using Address Book Manager!\n");
    printf("Goodbye!\n\n");
    exit(EXIT_SUCCESS);
}

void createContact(AddressBook *addressBook)
{
    if(addressBook->contactCount >= MAX_CONTACTS) {
        printf("\n+------------------------------------------------------+\n");
        printf("|         ADDRESS BOOK IS FULL!                       |\n");
        printf("+------------------------------------------------------+\n");
        return;
    }
    
    printf("\n+------------------------------------------------------+\n");
    printf("|              CREATE NEW CONTACT                      |\n");
    printf("+------------------------------------------------------+\n");
    
    printf("+------------------------------------------------------+\n");
    printf("| Enter Contact Details:                               |\n");
    printf("|------------------------------------------------------|\n");
    printf("| Name  : ");
    scanf(" %[^\n]", addressBook->contacts[addressBook->contactCount].name);
    printf("| Phone : ");
    scanf(" %[^\n]", addressBook->contacts[addressBook->contactCount].phone);
    printf("| Email : ");
    scanf(" %[^\n]", addressBook->contacts[addressBook->contactCount].email);
    printf("+------------------------------------------------------+\n");
    
    addressBook->contactCount++;
    printf("\nContact added successfully!\n");
}

int searchContact(AddressBook *addressBook) 
{
    printf("\n+------------------------------------------------------+\n");
    printf("|              SEARCH CONTACT                          |\n");
    printf("|------------------------------------------------------|\n");
    printf("|  1. Search by Name                                  |\n");
    printf("|  2. Search by Phone                                 |\n");
    printf("|  3. Search by Email                                 |\n");
    printf("|  4. Exit                                            |\n");
    printf("+------------------------------------------------------+\n");
    
    int choice;
    printf("\nEnter your choice: ");
    scanf("%d", &choice);
    
    char name[50], phone[15], email[50];
    
    switch(choice)
    {
        case 1:
            printf("Enter the search name: ");
            scanf(" %[^\n]", name);
            for(int i = 0; i < addressBook->contactCount; i++)
            {
                if(strcasecmp(addressBook->contacts[i].name, name) == 0)
                {
                    printf("\nContact found!\n");
                    printf("\n+------------------------------------------------------+\n");
                    printf("|                 CONTACT DETAILS                     |\n");
                    printf("|------------------------------------------------------|\n");
                    printf("| Name  : %-40s |\n", addressBook->contacts[i].name);
                    printf("| Phone : %-40s |\n", addressBook->contacts[i].phone);
                    printf("| Email : %-40s |\n", addressBook->contacts[i].email);
                    printf("+------------------------------------------------------+\n");
                    return i;
                }
            }
            printf("\nContact not found!\n");
            return -2;
            break;
         
        case 2:
            printf("Enter the phone: ");
            scanf(" %[^\n]", phone);
            for(int i = 0; i < addressBook->contactCount; i++)
            {
                if(strcmp(addressBook->contacts[i].phone, phone) == 0)
                {
                    printf("\nContact found!\n");
                    printf("\n+------------------------------------------------------+\n");
                    printf("|                 CONTACT DETAILS                     |\n");
                    printf("|------------------------------------------------------|\n");
                    printf("| Name  : %-40s |\n", addressBook->contacts[i].name);
                    printf("| Phone : %-40s |\n", addressBook->contacts[i].phone);
                    printf("| Email : %-40s |\n", addressBook->contacts[i].email);
                    printf("+------------------------------------------------------+\n");
                    return i;
                }
            }
            printf("\nContact not found!\n");
            return -2;
            break;
            
        case 3:
            printf("Enter the email: ");
            scanf(" %[^\n]", email);
            for(int i = 0; i < addressBook->contactCount; i++)
            {
                if(strcasecmp(addressBook->contacts[i].email, email) == 0)
                {
                    printf("\nContact found!\n");
                    printf("\n+------------------------------------------------------+\n");
                    printf("|                 CONTACT DETAILS                     |\n");
                    printf("|------------------------------------------------------|\n");
                    printf("| Name  : %-40s |\n", addressBook->contacts[i].name);
                    printf("| Phone : %-40s |\n", addressBook->contacts[i].phone);
                    printf("| Email : %-40s |\n", addressBook->contacts[i].email);
                    printf("+------------------------------------------------------+\n");
                    return i;
                }
            }
            printf("\nContact not found!\n");
            return -2;
            break;
            
        case 4:
            printf("\nExiting search...\n");
            return -1;
            
        default:
            printf("\nInvalid choice!\n");
            return -2;
    }
}

void editContact(AddressBook *addressBook)
{
    printf("\n+------------------------------------------------------+\n");
    printf("|              EDIT CONTACT                            |\n");
    printf("+------------------------------------------------------+\n");
    printf("Search for contact to edit:\n");
    int index = searchContact(addressBook);
    
    if(index == -1) {
        printf("Exited from search contact\n");
        return;
    }
    else if(index == -2) {
        printf("Contact not found\n");
        return;
    }
    else {
        printf("\n+------------------------------------------------------+\n");
        printf("|              WHAT DO YOU WANT TO EDIT?               |\n");
        printf("|------------------------------------------------------|\n");
        printf("|  1. Name                                            |\n");
        printf("|  2. Phone                                           |\n");
        printf("|  3. Email                                           |\n");
        printf("|  4. Exit                                            |\n");
        printf("+------------------------------------------------------+\n");
        
        int choice;
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        
        switch(choice)
        {
            case 1:
                printf("Enter the new name: ");
                scanf(" %[^\n]", addressBook->contacts[index].name);
                printf("\nName updated successfully!\n");
                break;
                
            case 2:
                printf("Enter the new phone no: ");
                scanf(" %[^\n]", addressBook->contacts[index].phone);
                printf("\nPhone updated successfully!\n");
                break;
                
            case 3:
                printf("Enter the new email: ");
                scanf(" %[^\n]", addressBook->contacts[index].email);
                printf("\nEmail updated successfully!\n");
                break;
                
            case 4:
                printf("\nExiting edit...\n");
                return;
                
            default:
                printf("\nInvalid choice!\n");
        }
    }
}

void deleteContact(AddressBook *addressBook)
{
    printf("\n+------------------------------------------------------+\n");
    printf("|              DELETE CONTACT                          |\n");
    printf("+------------------------------------------------------+\n");
    printf("Search for contact to delete:\n");
    int index = searchContact(addressBook);
    
    if(index == -1) {
        printf("Exited from search contact\n");
        return;
    }
    else if(index == -2) {
        printf("Contact not found\n");
        return;
    }
    else {
        printf("\n+------------------------------------------------------+\n");
        printf("|           CONFIRM DELETION                         |\n");
        printf("|------------------------------------------------------|\n");
        printf("|  Are you sure you want to delete this contact?      |\n");
        printf("|  1. Yes, delete it                                  |\n");
        printf("|  2. No, keep it                                     |\n");
        printf("+------------------------------------------------------+\n");
        
        int confirm;
        printf("\nEnter your choice: ");
        scanf("%d", &confirm);
        
        if(confirm == 1) {
            for(int i = index; i < addressBook->contactCount - 1; i++) {
                addressBook->contacts[i] = addressBook->contacts[i + 1];
            }
            addressBook->contactCount--;
            printf("\nContact deleted successfully!\n");
        } else {
            printf("\nDeletion cancelled.\n");
        }
    }
}