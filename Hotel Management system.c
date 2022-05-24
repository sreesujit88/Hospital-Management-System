#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node
{
	int room, days;
	char name[99], address[99], phone[99], nationality[99], email[99], arrival[99];
	struct Node *next;
};

typedef struct Node node;

void clear()
{
	printf("\033[H\033[J");
	#if 1
		system("cls");
	#endif
	#ifdef LINUX
		system("clear");
	#endif
}

int rooms[21] = { 0 };

void push(node **head, int room, int days, char name[], char address[], char phone[], char nationality[], char email[], char arrival[])
{
	node *temp = (node *)malloc(sizeof(node));
	temp->room = room;
	temp->days = days;
	strcpy(temp->name, name);
	strcpy(temp->address, address);
	strcpy(temp->phone, phone);
	strcpy(temp->nationality, nationality);
	strcpy(temp->email, email);
	strcpy(temp->arrival, arrival);
	temp->next = *head;
	*head = temp;
}

void view(node **head)
{
	clear();
	printf("View Customer Record:\n");
	printf("---------------------\n");
	node *temp = *head;
	if (temp == NULL)
	{
		printf("\nNo record has been added yet!\n");
		printf("\nPress enter to continue.\n\n");
		getchar();
		return;
	}
	while (temp != NULL)
	{
		printf("\nRoom Number: %d\n", temp->room);
		printf("Customer's Details:\n");
		printf("-----------------\n");
		printf("Name: %s\nAddress: %s\nPhone: %s\nNationality: %s\nEmail: %s\nStaying For: %d\nArrival Date: %s\n", temp->name, temp->address, temp->phone, temp->nationality, temp->email, temp->days, temp->arrival);
		temp = temp->next;
	}
	printf("\nPress enter to continue.\n\n");
	getchar();
}

void show()
{
	clear();
	printf("View Available Rooms:\n");
	printf("---------------------\n\n");
	for (int i=1; i<=20; i++)
	{
		printf("Room Number: %d - %s\n", i, (rooms[i] == 1) ? "Booked" : "Available");
	}
	printf("\nPress enter to continue.\n\n");
	getchar();
}

void search(node **head)
{
	clear();
	printf("Search Customer Record:\n");
	printf("-----------------------\n");
	node *temp = *head;
	if (temp == NULL)
	{
		printf("\nNo record has been added yet!\n");
		printf("\nPress enter to continue.\n\n");
		getchar();
		return;
	}
	int num;
	printf("\nEnter Room Number to Search for: ");
	scanf("%d%*c", &num);
	if (num > 20 || num < 1)
	{
		printf("\nThis room number is invalid!\n");
		printf("\nPress enter to continue.\n\n");
		getchar();
		return;
	}
	if (!rooms[num])
	{
		printf("\nThis room is not booked yet!\n");
		printf("\nPress enter to continue.\n\n");
		getchar();
	}
	while (temp != NULL)
	{
		if (temp->room == num)
		{
			printf("\nRoom Number: %d\n", temp->room);
			printf("Customer's Details:\n");
			printf("-----------------\n");
			printf("Name: %s\nAddress: %s\nPhone: %s\nNationality: %s\nEmail: %s\nStaying For: %d\nArrival Date: %s\n", temp->name, temp->address, temp->phone, temp->nationality, temp->email, temp->days, temp->arrival);
			printf("\nPress enter to continue.\n\n");
			getchar();
			return;
		}
		temp = temp->next;
	}
}

void edit(node **head)
{
	clear();
	printf("Edit Customer Record:\n");
	printf("---------------------\n");
	node *temp = *head;
	if (temp == NULL)
	{
		printf("\nNo record has been added yet!\n");
		printf("\nPress enter to continue.\n\n");
		getchar();
		return;
	}
	int num;
	printf("\nEnter Room Number to Edit: ");
	scanf("%d%*c", &num);
	if (num > 20 || num < 1)
	{
		printf("\nThis room number is invalid!\n");
		printf("\nPress enter to continue.\n\n");
		getchar();
		return;
	}
	if (!rooms[num])
	{
		printf("\nThis room is not booked yet!\n");
		printf("\nPress enter to continue.\n\n");
		getchar();
	}
	while (temp != NULL)
	{
		if (temp->room == num)
		{
			printf("\nRoom Number: %d\n", temp->room);
			printf("Customer's New Details:\n");
			printf("-----------------------\n");
			printf("Name: ");
			scanf("%[^\n]%*c", temp->name);
			printf("Address: ");
			scanf("%[^\n]%*c", temp->address);
			printf("Phone: ");
			scanf("%[^\n]%*c", temp->phone);
			printf("Nationality: ");
			scanf("%[^\n]%*c", temp->nationality);
			printf("Email: ");
			scanf("%[^\n]%*c", temp->email);
			printf("Staying For: ");
			scanf("%d%*c", &temp->days);
			printf("Arrival Date (dd/mm/yyyy): ");
			scanf("%[^\n]%*c", temp->arrival);
			printf("\nPress enter to continue.\n\n");
			getchar();
			return;
		}
		temp = temp->next;
	}
}

void Delete(node **head)
{
	clear();
	printf("Delete Customer Record:\n");
	printf("-----------------------\n");
    node *temp = *head, *prev;
	if (temp == NULL)
	{
		printf("\nNo record has been added yet!\n");
		printf("\nPress enter to continue.\n\n");
		getchar();
		return;
	}
	int num;
	printf("\nEnter Room Number to Delete: ");
	scanf("%d%*c", &num);
	if (num > 20 || num < 1)
	{
		printf("\nThis room number is invalid!\n");
		printf("\nPress enter to continue.\n\n");
		getchar();
		return;
	}
	if (!rooms[num])
	{
		printf("\nThis room is not booked yet!\n");
		printf("\nPress enter to continue.\n\n");
		getchar();
	}
    if (temp != NULL && temp->room == num)
    {
        *head = temp->next;
        free(temp);
		rooms[num] = 0;
		printf("\nDeleted Successfully!\n");
		printf("\nPress enter to continue.\n\n");
		getchar();
        return;
    }
    while (temp != NULL && temp->room != num)
    {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL)
	{
		printf("\nThis room number is not booked yet!\n");
		printf("\nPress enter to continue.\n\n");
		getchar();
		return;
	}
    prev->next = temp->next;
	rooms[num] = 0;
	printf("\nDeleted Successfully!\n");
	printf("\nPress enter to continue.\n\n");
	getchar();
    free(temp);
}

int main()
{
	node *head = NULL;
	int option = 1;
	while (option != 7)
	{
		clear();
		printf("HOTEL MANAGEMENT SYSTEM\n");
		printf("=======================\n");
		printf("\n1. View Available Rooms");
		printf("\n2. Add Customer Record");
		printf("\n3. View Customer Record");
		printf("\n4. Search Customer Record");
		printf("\n5. Edit Customer Record");
		printf("\n6. Delete Customer Record");
		printf("\n7. Exit Programme\n");
		printf("\nEnter Option: ");
		scanf("%d%*c", &option);
		switch (option)
		{
			case 1:
			{
				show();
				break;
			}
			case 2:
			{
				printf("Add Customer Record:\n");
				printf("--------------------\n");
				printf("\nHow many records do you want to add: ");
				int n, room, day;
				char name[99], address[99], phone[99], nationality[99], email[99], arrival[99];
				scanf("%d%*c", &n);
				for (int i=0; i<n; i++)
				{
					printf("\nRoom Number: ");
					scanf("%d%*c", &room);
					if (rooms[room])
					{
						printf("\nThis room is already booked!\n");
						continue;
					}
					rooms[room] = 1;
					printf("Customer's Details:\n");
					printf("-------------------\n");
					printf("Name: ");
					scanf("%[^\n]%*c", name);
					printf("Address: ");
					scanf("%[^\n]%*c", address);
					printf("Phone: ");
					scanf("%[^\n]%*c", phone);
					printf("Nationality: ");
					scanf("%[^\n]%*c", nationality);
					printf("Email: ");
					scanf("%[^\n]%*c", email);
					printf("Staying For: ");
					scanf("%d%*c", &day);
					printf("Arrival Date (dd/mm/yyyy): ");
					scanf("%[^\n]%*c", arrival);
					push(&head, room, day, name, address, phone, nationality, email, arrival);
				}
				printf("\nAdded Successfully!\n");
				printf("\nPress enter to continue.\n\n");
				getchar();
				break;
			}
			case 3:
			{
				view(&head);
				break;
			}
			case 4:
			{
				search(&head);
				break;
			}
			case 5:
			{
				edit(&head);
				break;
			}
			case 6:
			{
				Delete(&head);
				break;
			}
			case 7:
			{
				return 0;
			}
			default:
			{
				printf("\nInvalid Option!\n");
				printf("\nPress enter to try again.\n\n");
				getchar();
			}
		}
	}
	return 0;
}
