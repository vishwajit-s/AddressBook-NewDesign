#include <stdio.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook) //saving contacts from array to file
{

FILE *fptr = fopen("contact.csv","w"); // creating new file in write mode & open the file & store the return address in fptr variable
fprintf(fptr,"#%d\n",addressBook->contactCount); //print number of contacts to file

for (int i=0;i<addressBook->contactCount;i++) //loop to print the data to file
{
    fprintf(fptr,"%s,%s,%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email); //copying the each contact from array of structure to the file
}

}

void loadContactsFromFile(AddressBook *addressBook)  //loading contacts from file back to array 

{
FILE *fptr = fopen("contact.csv","r"); //open file in read mode
fscanf(fptr,"#%d\n",&addressBook->contactCount); //loop to read the data from file

for (int i=0;i<addressBook->contactCount;i++)
{
    fscanf(fptr,"%[^,],%[^,],%[^\n]\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email); //read contacts from file back to array
}

}



