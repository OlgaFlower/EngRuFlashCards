 #include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#include<cstdlib>
#include <cstring>
#include <clocale>
#include <time.h>
#include <conio.h>


typedef struct Words
{
	char ru[30];
	char en[30];
	int id;
	int count;
	struct Words *next; // ��������� �� ���� ���� � ������
	struct Words *prev; // ��������� �� ���������� ���� � ������
}* vocab;

//---------------------------------------------------------------------------------------------

vocab create_node(FILE* fen, FILE *fru, int id)
{
	vocab NewNode =(vocab)calloc(1,sizeof(struct Words)); // ��������� �� ����� ����
	if(fscanf(fen,"%s",NewNode->en)!=EOF)// ������ ����� � ����
	{ 
		fscanf(fru,"%s",NewNode->ru);
		NewNode->id=id;
		
	}
	else 
	{
		free(NewNode); //��������� ��������� ������
		NewNode=NULL;
	}
	return NewNode; // ��������� ������� � ����� ���������� ����
}

//--------------------------------------------------------------------------------------------------

void add_node(vocab p, vocab NewNode) //�������� ������ ����
{
	NewNode->prev = p->prev;
	NewNode->next = p;
	p->prev->next = NewNode;
	p->prev = NewNode;
}

//---------------------------------------------------------------------------------------------------


vocab RU_EN_printout (vocab Head,char block[][20],int massdigit[], int x)
{
	
	vocab f, for_count;
	f = Head->next;
	
	int i,j;
	int addwords;
		
	int rand_id=1+rand()%x; //x ���� � ������, ��������� ���������
	while (f->id!=rand_id) 
	{
		f=f->next;
	}
	for_count=f;
		
	printf ("\n\tTranslate: %s\n",f->ru);
	strcpy (block [0], f->ru);
	strcpy (block[1], f->en);

	for (int i=2; i<5; i++)
	{
		addwords=1+rand()%x; 
		if (addwords!=rand_id)
	{
		f = Head->next;
		while (f->id!=addwords) 
		{
			f=f->next;
		}
					
		strcpy (block[i], f->en); //������ � ������ temp ������������ 3-� ��������� ��������
	}
				
	else 
	{
		i--;
		continue;
	}
				
	if (i>2)
	{
		for (j=2; j<i; j++)
		{
			if (strcmp (block[j], f->en)==0)
			break;
		}
				
		if (j<i)
		{
			i--;
		}
	}
	}
			

	for (int i=0; i<4; i++)
	{
	 	massdigit[i]=1+rand()%4;
	 	if (i==0) printf("\n\t%i %s\n", i+1, block[massdigit[i]]);
	 	if (i>0)
		{
			for (j=0; j<i; j++)
			if (massdigit[i]==massdigit[j])
			break;
			
			if (j<i)
			{
				i--;
			}
			
			else printf ("\n\t%i %s\n", i+1, block[massdigit[i]]); 
		}
			
	}
	
	 printf ("\n\n");
	 return for_count;
}

//-----------------------------------------------------------------------------------------------------

vocab EN_RU_printout (vocab Head,char block[][20],int massdigit[], int x)
{
	vocab f, for_count;
	f = Head->next;
	
	int i,j;
	int addwords;
		
		int rand_id=1+rand()%x; //x-���� � �������
		while (f->id!=rand_id)  
		{
			f=f->next;
		}
		for_count=f;
		
		printf ("\n\tTranslate: %s\n",f->en);
		strcpy (block [0], f->en);
		strcpy (block[1], f->ru);

		for (int i=2; i<5; i++)
		{
			addwords=1+rand()%x; 
			if (addwords!=rand_id) 
			{
				f = Head->next;
				while (f->id!=addwords) 
				{
					f=f->next;
				}
				strcpy (block[i], f->ru); //������ � ������ temp ������������ 3-� ��������� ��������
			}
			else 
			{
				i--;
				continue;
			}
			
			if (i>2)
			{
				for (j=2; j<i; j++)
				{
					if (strcmp (block[j], f->ru)==0)
					break;
				}
				
				if (j<i)
				{
					i--;
				}
			}
		}

	for (int i=0; i<4; i++)
	{
		massdigit[i]=1+rand()%4; 
	 	if (i==0) printf("\n\t%i %s\n", i+1,  block[massdigit[i]]);
	 	if (i>0)
		{	
			for (j=0; j<i; j++)
			if (massdigit[i]==massdigit[j])
			break;
			
			if (j<i)
			{
				i--;
			}
			
			else printf ("\n\t%i %s\n", i+1,  block[massdigit[i]]); 
		}
			
	 }
	 
	 printf ("\n\n");
	 return for_count;
	
}


//-----------------------------------------------------------------------------------------------------


void fill_id(vocab Head) // ��������� ���� id � ����� ������ ... (�� ���-�� ����)
{
	int x=1;
	vocab p = Head-> next;
	while (p->next!=NULL)
	{
		p->id=x;
		p=p->next;
		x++;
	}
}


//--------------------------------------------------------------------------------------------------------

void delete_node(vocab old_node)
{
	
	old_node->prev->next = old_node->next; 
	old_node->next->prev = old_node->prev;
	
	free(old_node);
}

//-----------------------------------------------------------------------------------------------------

int printout_your_choice(vocab Head, vocab Tail, char block[][20], int massdigit[], int x, char deleted_words[][20]) //���� ������ � ����������� �����
{
	vocab for_translt;
	int ichoice;
	char choice2;
	int cycle=50; 
	int z=0; //������ ������� deleted_words[][20]
	
	printf ("\n\n\t-- Question/Answer Flashcards --\n\n");
	Sleep (1000);

	
	printf ("\n\n\tMake your choice:\n\n\n\t1. RU -> EN\n\n\t2. EN -> RU\n\n\tEsc -> Exit\n\n\t");
	char choice=getch();
	
	Sleep (1000);
	system ("cls");
	
	switch (choice)  
	{
		case '1':	
			
			for (int q=0; q<cycle; q++) //����� ����� ���� cycle-���
			{
				for_translt=RU_EN_printout(Head,block,massdigit, x);
				printf ("\n\tMake your choice (1-4): ");
				
				do
				{
					choice2=getch();
					if (choice2==27)
					{
						printf ("\n\n\n\t--Good bye!--");  
						Sleep (3000);
						exit(0);
						break;
					}
				}
				while (choice2<'1' || choice2>'4');
				
				ichoice=choice2-'0';

				if (massdigit[ichoice-1]==1)
				{
				 	printf ("Correct!\n");
					printf ("\t--------------------------------\n\n");
			
					for_translt->count++; //������� �� ���������� ���������� �������
				
					if (for_translt->count == 3) //����� ������ ������� ��� �������� ����
					{
						strcpy (deleted_words[z], for_translt->ru);//������� ����� �� ����� � ��������� ������	
						z++;
			
						delete_node(for_translt);//������� ����
						fill_id(Head);
						x=Tail->prev->id;
					
						if (x<4)
						{
							printf ("\n\tWords are over!\n"); //���������� ��� ������� ���� ����
							return z;
						}
					}
				
				}
				
				else
				{
					printf ("Wrong!!!\n");
					printf ("\t--------------------------------\n\n");
					printf ("\n\tThe correct answer is - %s\n\n\n", block[1]);
				
				}
				
				Sleep (2000);
				system ("cls");
			}
			break;
			
			
			
		case '2':  
			
			for (int q=0; q<cycle; q++) //����� ����� ���� cycle-���
			{
				for_translt=EN_RU_printout(Head,block,massdigit, x);
				printf ("\n\tMake your choice (1-4): ");
				
				do
				{
					choice2=getch();
					if (choice2==27)
					{
						printf ("\n\n\n\t--Good bye!--");  
						Sleep (3000);
						exit(0);
						break;
					}
				}
				
				while (choice2<'1' || choice2>'4');
				
				ichoice=choice2-'0';

				if (massdigit[ichoice-1]==1)
				{
					printf ("Correct!\n");
					printf ("\t--------------------------------\n\n");
			
					for_translt->count++; //������� �� ���������� ���������� �������
				
					if (for_translt->count == 3) //����� ������ ������� ��� �������� ����
					{
						strcpy (deleted_words[z], for_translt->en);//������� ����� �� ����� � ��������� ������	
						z++;
					
						delete_node(for_translt);//������� ����
						fill_id(Head);
						x=Tail->prev->id;
					
						if (x<4)
						{
							printf ("\n\tWords are over!\n"); //���������� ��� ������� ���� ����
							return z;
						}
					}
				
				}
				
				else
				{
					printf ("Wrong!!!\n");
					printf ("\t--------------------------------\n\n");
					printf ("\n\tThe correct answer is - %s\n\n\n", block[1]);
				}
				
				Sleep (2000);
				system ("cls");
			}
			break;
			
			
		case 27:
			printf ("\n\n\n\t--Good bye!--");  
			Sleep (3000);
			system ("cls");
			exit(0);
			break;
	}
return z;	
}


void finish_words (vocab Head) //����� ������ ���������� ���� ����� ����������� ���������
{
	vocab p = Head->next;
	printf ("\nA list of words after verification:\n");
	while (p->next!=NULL)
	{
		printf ("%i - %s - %s\n", p->id, p->en, p->ru);
		p=p->next;
	}
}



int main ()
{
	system("color F0"); //����� ��� ������� � ������ �����
	srand (time(0)); 
	
	vocab Head=NULL, Tail=NULL;
	FILE *fen, *fru, *del;
	
	fen = fopen ("eng.txt", "r");
	fru = fopen ("rus.txt", "r");
	
	vocab p; //� p ������������ ����� ������ ��� ���������� ����
	
	char choice=0, choice2=0;
	char word_for_translt;//���������� ��� ������: ru->en ��� en->ru
	int rand_id; //���������� ��� ���������� ������ ���� �� id 
	int x; // ���������� ��� ������� - x ���� � ������
	char block [5][20]; //������ ��� ������������� ����
	int massdigit[5]; //��������� ��������� ���� ��� ������
	char deleted_words[20][20]; //������ ��� ��������� ����
	int id=0; 
	char ex;
		
	SetConsoleCP(1251); //���������� ������ � ������ ���������
	SetConsoleOutputCP(1251); //���������� ������ � ������ �����

	Head=(vocab)calloc(1,sizeof(struct Words)); // ����� ������
	Tail=(vocab)calloc(1,sizeof(struct Words)); // ������ ������

	Head->next= Tail;
	Tail->prev= Head;

	
	while(p=create_node(fen, fru, id))
	add_node(Tail,p); 	// ������������ ������
	fclose(fen);
	fclose(fru);
	
 	fill_id(Head);//��������� �����
	x=Tail->prev->id;
	
 	int z=printout_your_choice(Head, Tail, block,massdigit, x, deleted_words);//���������� ������ �����

 	finish_words(Head); 

	if (z!=NULL) //����� ������ ��������� ����
	{
		printf ("\n\nLearned words:\n");
		printf ("--------------\n\n"); 
		 
		for (int d=0; d<z; d++)
		{
		 	printf ("%s\n", deleted_words[d]);
		}
		
		printf ("\n\n--Finish!--");
		printf ("\n\n\nPress Esc to exit!\t");
		
		do
		{
			ex=getch();		
		}
		while (ex!=27);
		
		printf ("\n\n\n--Good bye!--");  
		Sleep (20000);
		exit(0);	
	}
	
	else 
	{
		printf ("\n\n\n--Finish!--"); 
		printf ("\n\n\n--Good bye!--"); 
		Sleep (20000);
		system ("cls");
		exit(0);	
	}

					
getchar ();
}
