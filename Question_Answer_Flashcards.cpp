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
	struct Words *next; // указатель на след узел в списке
	struct Words *prev; // указатель на предыдущий узел в списке
}* vocab;

//---------------------------------------------------------------------------------------------

vocab create_node(FILE* fen, FILE *fru, int id)
{
	vocab NewNode =(vocab)calloc(1,sizeof(struct Words)); // указатель на новый узел
	if(fscanf(fen,"%s",NewNode->en)!=EOF)// запись слова в узел
	{ 
		fscanf(fru,"%s",NewNode->ru);
		NewNode->id=id;
		
	}
	else 
	{
		free(NewNode); //обнуление временной памяти
		NewNode=NULL;
	}
	return NewNode; // результат функции – адрес созданного узла
}

//--------------------------------------------------------------------------------------------------

void add_node(vocab p, vocab NewNode) //создание нового узла
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
		
	int rand_id=1+rand()%x; //x слов в списке, рандомная нумерация
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
					
		strcpy (block[i], f->en); //запись в массив temp неправильных 3-х вариантов перевода
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
		
		int rand_id=1+rand()%x; //x-слов в списках
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
				strcpy (block[i], f->ru); //запись в массив temp неправильных 3-х вариантов перевода
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


void fill_id(vocab Head) // заполняем поле id в узлах списка ... (по кол-ву слов)
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

int printout_your_choice(vocab Head, vocab Tail, char block[][20], int massdigit[], int x, char deleted_words[][20]) //меню выбора и последующий вывод
{
	vocab for_translt;
	int ichoice;
	char choice2;
	int cycle=50; 
	int z=0; //строки массива deleted_words[][20]
	
	printf ("\n\n\t-- Question/Answer Flashcards --\n\n");
	Sleep (1000);

	
	printf ("\n\n\tMake your choice:\n\n\n\t1. RU -> EN\n\n\t2. EN -> RU\n\n\tEsc -> Exit\n\n\t");
	char choice=getch();
	
	Sleep (1000);
	system ("cls");
	
	switch (choice)  
	{
		case '1':	
			
			for (int q=0; q<cycle; q++) //вывод блока слов cycle-раз
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
			
					for_translt->count++; //счетчик на количество правильных ответов
				
					if (for_translt->count == 3) //сумма верных ответов для удаления узла
					{
						strcpy (deleted_words[z], for_translt->ru);//копирую слова на вылет в отдельный массив	
						z++;
			
						delete_node(for_translt);//удаляем узел
						fill_id(Head);
						x=Tail->prev->id;
					
						if (x<4)
						{
							printf ("\n\tWords are over!\n"); //завершение при выборке всех слов
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
			
			for (int q=0; q<cycle; q++) //вывод блока слов cycle-раз
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
			
					for_translt->count++; //счетчик на количество правильных ответов
				
					if (for_translt->count == 3) //сумма верных ответов для удаления узла
					{
						strcpy (deleted_words[z], for_translt->en);//копирую слова на вылет в отдельный массив	
						z++;
					
						delete_node(for_translt);//удаляем узел
						fill_id(Head);
						x=Tail->prev->id;
					
						if (x<4)
						{
							printf ("\n\tWords are over!\n"); //завершение при выборке всех слов
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


void finish_words (vocab Head) //вывод списка оставшихся слов после прохождения программы
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
	system("color F0"); //белый фон консоли и черный текст
	srand (time(0)); 
	
	vocab Head=NULL, Tail=NULL;
	FILE *fen, *fru, *del;
	
	fen = fopen ("eng.txt", "r");
	fru = fopen ("rus.txt", "r");
	
	vocab p; //в p возвращается адрес только что созданного узла
	
	char choice=0, choice2=0;
	char word_for_translt;//переменная для выбора: ru->en или en->ru
	int rand_id; //переменная для рандомного вывода слов по id 
	int x; // переменная для рандома - x слов в списке
	char block [5][20]; //массив для перемешивания слов
	int massdigit[5]; //рандомная нумерация слов при выводе
	char deleted_words[20][20]; //массив для выученных слов
	int id=0; 
	char ex;
		
	SetConsoleCP(1251); //корректная запись в память кириллицы
	SetConsoleOutputCP(1251); //корректная запись в память кирил

	Head=(vocab)calloc(1,sizeof(struct Words)); // левый барьер
	Tail=(vocab)calloc(1,sizeof(struct Words)); // правый барьер

	Head->next= Tail;
	Tail->prev= Head;

	
	while(p=create_node(fen, fru, id))
	add_node(Tail,p); 	// формирование списка
	fclose(fen);
	fclose(fru);
	
 	fill_id(Head);//нумерация узлов
	x=Tail->prev->id;
	
 	int z=printout_your_choice(Head, Tail, block,massdigit, x, deleted_words);//считывание выбора юзера

 	finish_words(Head); 

	if (z!=NULL) //вывод списка изученных слов
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
