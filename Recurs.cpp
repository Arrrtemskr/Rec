#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<time.h>

#pragma warning (disable:4996)

typedef struct words
{
	char* wordcur;
	int sym;
};

struct words wordsMas[7];

bool num[10];
int value[10] = { 0 };
int count = 0, countWORDS = 0;
char begin[100] = { '\0' };
char beginCopy[100] = { '\0' };
char alphabet[10] = { "\0" };

void enterAlph(char* mas, char* pos)
{
	for (int i = 0;i < 100;i++)
	{
		
		if (pos[i] == '\0')
			break;
		for (int j = 0;j < 10;j++)
		{
			if (pos[i] == mas[j])
				break;
			if (pos[i] != mas[j] && mas[j] == 0 && pos[i]!='+' && pos[i] != '=' && isalpha(pos[i]))
			{
				mas[j] = pos[i];
				count++;
				break;
			}
		}
	}
}



int checkSym(char* istr)
{

	int sym = 0, cur = 0;
	int sizeIstr = strlen(istr), sizeAlph = strlen(alphabet);
	for (int i = 0; i < sizeIstr && istr != NULL;i++)
	{
		for (int j = 0;j < sizeAlph;j++)
		{
			if (istr[i] == alphabet[j])
			{
				if(i==0 && value[j]==0)
					return -1;
				cur = value[j];
				sym = sym * 10 + cur;
				break;
			}
		}
		
	}
	return sym;
}

bool check()
{
	char* istr;
	istr = strtok(begin, "+=");
	int allsym = 0;
	
	for (int i = 0;i < 7 && istr != NULL;i++, countWORDS++)
	{
		wordsMas[i].wordcur = istr;
		if (checkSym(istr) == -1)
		{
			strcpy(begin, beginCopy);
			return 0;
		}
		wordsMas[i].sym = checkSym(istr);
		allsym += wordsMas[i].sym;
		istr = strtok(NULL, "+=");
	}
	if ((allsym- wordsMas[countWORDS - 1].sym) == wordsMas[countWORDS - 1].sym)
		return 1;
	countWORDS = 0;
	strcpy(begin, beginCopy);
	return 0;
}

void print()
{
	for (int i = 0;i < countWORDS;i++)
	{

		printf("%d ", wordsMas[i].sym);
		printf("%s\n", wordsMas[i].wordcur);

	}
	printf("\n");
}

float start = 0;

void reverse(int pos)
{
	
	if (pos == strlen(alphabet))
	{
		if (check())
		{
			printf("time - %f", (clock() - start) / CLOCKS_PER_SEC);
			printf("\n");
			print();
			
			exit(0);
		}
		return;
	}

	for(int number=0;number<10;number++)
	{
		if (!num[number])
		{
			num[number]=true;
			value[pos] = number;
			reverse(pos+1);

			value[pos] = 0;
			num[number]=false;

		}
	}
}

int main()
{

	printf("Enter your rebus:");
	gets_s(begin, 100);
	srand(time(NULL));
	start = clock();
	strcpy(beginCopy,begin);
	//printf("\n%s\n", begin);
	enterAlph(alphabet,begin);
	//printf("\nalphabet: %s\n", alphabet);
	
	reverse(0);
	
	return 0;
}