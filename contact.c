
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "contact.h"
#include "file.h"
/* #include "populate.h" */

int global_arr[100]; //initialise global array of 100 size 
int size=0; //initialise size as 0

void listContacts(AddressBook *addressBook) //list all the contacts
{
    printf("%-7s %-18s %14s %-25s\n","SI.NO", "NAME","PH_NUMBER","EMAIL");
    for(int i=0;i < addressBook->contactCount;i++)
    {
        printf("%-7d %-18s %14s %-25s\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,
               addressBook->contacts[i].email);  //print all the contacts with email & number
    }
}

void initialize(AddressBook *addressBook) //initialise addressbook
{
    addressBook->contactCount = 0;
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook)
{
    saveContactsToFile(addressBook); //save the contacts & exit
    exit(EXIT_SUCCESS);
}

int validate_name(AddressBook *addressBook,char *name) //check for valid name
{
    int count = 0;

    if(!isalpha(name[0])) //name first letter is not alpha 
    {
        printf("Entered char is invalid for name\n"); //invalid name
        return 0;
    }

    for(int i = 0; name[i] != '\0'; i++)
    {
        if(isalpha(name[i])) //count number of alphabets
            count++; //increase count

        else if(name[i] != ' ') //other than space present in name
        {
            printf("Invalid name: only letters and spaces are allowed\n"); //invalid name
            return 0;
        }
    }

    if (count < 3) //name length should be atleast 3 characters
    {
        printf("Name must contain at least 3 letters\n");
        return 0;
    }

    return 1; //when validation done correctly , name is valid
}

int validate_num(AddressBook *addressBook, char num[]) //validate the number
{
    if((num[0] < '6' || num[0] > '9')) //starting should be 6 to 9
    {
        printf("Number starting is not within the range of 6-9\n");
        return 0; //invalid number
    }

    if(strlen(num) != 10) //mobile number length must be 10
    {
        printf("Mobile number length is invalid\n");
        return 0; //invalid number
    }

    for(int i=0; num[i]; i++)
    {
        if(!isdigit(num[i])) //check any other character found except the digit
        {
            printf("Entered char is invalid for number : starting digit is invalid \n");
            return 0; //invalid number
        }
    }

    for(int i=0;i < addressBook->contactCount;i++)
    {
        if(strcmp(num,addressBook->contacts[i].phone)==0) //compare number with existing number in addressbook
        {
            printf("Duplicate match found for this number\n");
            return 0; //invalid number
        }
    }

    return 1; //validation done , valid number
}

int validate_email(AddressBook *addressBook,char s_email[]) //validate email
{
    if(!isalpha(s_email[0])) //first char is not alpha
    {
        printf("Entered char is invalid for email : starting char is invalid \n");
        return 0; //invalid email
    }

    int at_count = 0; //@ count
    int dot_count = 0;// . count
    int at_pos = -1; //position of @
    int dot_pos = -1; //position of .

    for(int i=0; s_email[i]; i++)
    {
        if(s_email[i] == '@') //check for @
        {
            at_count++; //increase the count
            at_pos = i; //store the position
        }
        else if(s_email[i] == '.') //check for .
        {
            dot_count++; //increase the count
            dot_pos = i; //store the position
        }
        else if(!(islower(s_email[i]) || isdigit(s_email[i]))) //anything except lowercase & digit is found
        {
            printf("Entered do not have lower or digit or other required char for email\n");
            return 0; //invalid email
        }
    }
        for(int i = at_pos + 1; i < dot_pos; i++)
    {
        if(!isalpha(s_email[i]))
        {
            printf("Only alphabets allowed after @\n"); //check for alphabets after @
            return 0;
        }
    }
    

    if(at_count != 1) //@ counts exceeds 1 or not present
    {
        printf("Double @ or missing @ in email\n");
        return 0; //invalid email
    }

    if(dot_count != 1) //. counts exceeds 1 or not present
    {
        printf("Only one dot is allowed in email\n");
        return 0;  //invalid email
    }

    if(dot_pos < at_pos) //check for both @ & . position
    {
        printf("Dot must be after @ symbol\n");
        return 0;  //invalid email
    }

    if(dot_pos - at_pos <= 1) //check for domain name
    {
        printf("Domain name missing in email\n");
        return 0;  //invalid email
    }

    if(strcmp(&s_email[dot_pos], ".com") != 0) //check the position of .com
    {
        printf(".com must be at the end of email\n");
        return 0; 
    }

    for(int i=0;i < addressBook->contactCount;i++)
    {
        if(strcmp(s_email,addressBook->contacts[i].email)==0) //compare number with existing number in addressbook
        {
            printf("Duplicate match found for this email\n");
            return 0; //invalid email
        }
    }

    return 1;//validation done, valid email
}


void createContact(AddressBook *addressBook) //create the contact
{
    char s_name[50]; //name
    char ph_no[11]; //mobile number
    char s_email[30]; //email

    int max_att=3, att=0; //max 3 attempts allowed to create contact

    while(att < max_att) //first attempt
    {
        printf("Enter name:\n");
        scanf(" %[^\n]",s_name); //read name from user

        if(validate_name(addressBook,s_name)) //pass the name to the function to check it is valid or not
            break; //valid name break & go for next

        att++; //not valid increase attempt
        printf("Attempts Left : %d\n",max_att-att);  //display remaining attempts
    }
    if(att==max_att) //when limit is exceeded
    {
        printf("Max limit reached\n");
        printf("Failed to create a contact\n"); //contact creation failed
        return;
    }

    att=0;
    while(att < max_att) //first attempt
    {
        printf("Enter phone number:\n");
        scanf("%s",ph_no);  //read number from user

        if(validate_num(addressBook,ph_no)) //pass the number to the function to check it is valid or not
            break; //valid name break & go for next

        att++;  //not valid increase attempt
        printf("Attempts left : %d\n",max_att-att);  //display remaining attempts
    }
    if(att==max_att)  //when limit is exceeded
    {
        printf("Max limit reached\n");
        printf("Failed to create a contact\n");  //contact creation failed
        return;
    }

    att=0;
    while(att < max_att) //first attempt
    {
        printf("Enter email:\n");
        scanf(" %[^\n]",s_email);  //read email from user

        if(validate_email(addressBook,s_email)) //pass the email to the function to check it is valid or not
            break; //valid name break & go for next

        att++; //not valid increase attempt
        printf("Attempts Left : %d\n",max_att-att); //display remaining attempts
    }
    if(att==max_att) //when limit is exceeded
    {
        printf("Max limit reached\n");
        printf("Failed to create a contact\n"); //contact creation failed
        return;
    }

    strcpy(addressBook->contacts[addressBook->contactCount].name,s_name); //valid name copy to the addressbook name
    strcpy(addressBook->contacts[addressBook->contactCount].phone,ph_no);  //valid number copy to the addressbook number
    strcpy(addressBook->contacts[addressBook->contactCount].email,s_email); //valid number copy to the addressbook number
    addressBook->contactCount++; //increase count after creation of one contact

    printf("Contact created successfull\n"); //display message after contact craeted
}

int searchContact(AddressBook *addressBook) //search required contact from addresbook
{
    int choice; 
  	printf("1. Name\n2. Phone Number\n3. Email\n4. Exit\n"); //choice displayed
	scanf("%d",&choice); //read choice from user
    //getchar();


	if(choice == 4) //if choice is exit return -1
{
    return -1;
}

    size=0; //size is 0

    if(choice==1) //if choice is 1
    {
        char temp[50]; 
        printf("Enter name\n");
        scanf(" %[^\n]",temp); //read name from user

        for(int i=0;i<addressBook->contactCount;i++)
        {
            if(strcmp(temp,addressBook->contacts[i].name)==0) //compare name with addressbook contacts 
            {
                global_arr[size]=i; //store that name index in global array 
                size++; //increase  the sizze of global array

                printf("%-7d %-18s %14s %-25s\n",size,addressBook->contacts[i].name,addressBook->contacts[i].phone,
                       addressBook->contacts[i].email);
            }
        }
        if(size==0) //no name found return -1
            return -1;


        return -2; //if found return -2
    }

    if(choice==2) //search by phone number
{
    char temp[11];
    printf("Enter number\n");
    scanf(" %10s", temp); //read number from user

    for(int i=0;i<addressBook->contactCount;i++) //run loop
    {
        if(strcmp(temp,addressBook->contacts[i].phone)==0) //compare this with addressbook contacts
        {
            printf("%-7s %-18s %14s %-25s\n",
                   "SI.NO","NAME","PH_NUMBER","EMAIL");
            printf("%-7d %-18s %14s %-25s\n",
                   i+1,
                   addressBook->contacts[i].name,
                   addressBook->contacts[i].phone,
                   addressBook->contacts[i].email);
            return i;
        }
    }

    printf("No contact found with this phone number\n"); // ✅ ADDED
    return -1;
}


    if(choice==3) //search by email
{
    char temp[30];
    printf("Enter email\n");
    scanf(" %29s", temp);

    for(int i=0;i<addressBook->contactCount;i++)
    {
        if(strcmp(temp,addressBook->contacts[i].email)==0)
        {
            printf("%-7s %-18s %14s %-25s\n",
                   "SI.NO","NAME","PH_NUMBER","EMAIL");
            printf("%-7d %-18s %14s %-25s\n",
                   i+1,
                   addressBook->contacts[i].name,
                   addressBook->contacts[i].phone,
                   addressBook->contacts[i].email);
            return i;
        }
    }

    printf("No contact found with this email\n"); // ✅ ADDED
    return -1;
}
}


void editContact(AddressBook *addressBook)
{
    int t_att=3;//total three attempts

    while(t_att>0) //for first attempt
    {
        int store = searchContact(addressBook); //call search function

        if(store==-2)  //check for store value
        {
            int si;
            printf("Enter the serial number\n");
            scanf("%d",&si); //read serial number from user

            if(si<=0 || si>size)   //check for serial number validation 
            {
                printf("Invalid serial number\n");
                t_att--; //decrease attempt for invalid number
                continue;
            }
            store = global_arr[si-1]; //if valid then store in global array
        }
        else if(store<0)
        {
            printf("Failed to edit - No contact found\n");
            t_att--; //reduce the attempt
            printf("left with %d attempts\n",t_att);
            continue;
        }

        int choice;
     	printf("1. Name\n2. Phone Number\n3. Email\n4. Exit\n");
		scanf("%d",&choice);  //enter for the choice

		if(choice == 4)
		{
    		printf("Edit cancelled by user\n");  //choice 4 will exit from the function
    		return;
		}

        if(choice==1) //if choice is 1
        {
            char n[50];
            scanf(" %[^\n]",n); //read string fron user
            if(validate_name(addressBook,n)) //validate name
            {
                strcpy(addressBook->contacts[store].name,n); //if valid copy that name in addressbook 
                printf("New name updated successfully\n");
                return; //return 
            }
        }
        else if(choice==2) //for choice 2
        {
            char p[11];
            scanf("%s",p); //read number from user
            if(validate_num(addressBook,p)) //validate the number
            {
                strcpy(addressBook->contacts[store].phone,p); //if number is valid copy it in the addressbook
                printf("Phone number updated successfully\n");
                return;
            }
        }
        else if(choice==3) //for choice 3
        {
            char e[30];
            scanf(" %[^\n]",e); //read email from user
            if(validate_email(addressBook,e)) //check for email validation
            {
                strcpy(addressBook->contacts[store].email,e);  //copy the email in addressbook 
                printf("Email updated successfully\n");
                return;
            }
        }
        t_att--; //if validation failed for name,number & email , reduce the attempts
    }

    printf("Maximum attempts reached - Edit Failed\n"); //print this when max value reached
}

void deleteContact(AddressBook *addressBook)  //to delete the contact
{
    int total_att=3; //three attempts to delete

    while(total_att>0) //for first attempt
    {
        int store = searchContact(addressBook); //call search function to delete which contact

        if(store==-2) //check for store value
        {
            int si;
            printf("Enter the serial number\n");
            scanf("%d",&si); //read serial  number from user

            if(si<=0 || si>size)  //check for serial number validation
            {
                printf("Invalid serial number\n");
                total_att--; //reduce attempt for wrong serial number
                continue;
            }
            store = global_arr[si-1]; //if valid store in global array
        }
        else if(store<0) //if store value is not correct
        {
            total_att--; //reduce the attempt
            printf("Contact failed to delete - No contact found !!!\n");
            printf("Attempts left : %d\n", total_att); //print remaining attempt
            continue;
        }

        for(int i=store;i<addressBook->contactCount-1;i++)
            addressBook->contacts[i]=addressBook->contacts[i+1]; //replace the next contact details in place of the contact you want to delete

        addressBook->contactCount--; //reduce the addressbook count
        printf("Contact Deleted successfully\n");
        return; //return 
    }

    printf("Maximum attempts reached - Contact Delete Failed\n");
}


