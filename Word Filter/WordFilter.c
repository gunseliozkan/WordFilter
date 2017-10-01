#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define MAX_NUM_WORDS 500
#define WORD_LENGHT 50

int getAndFilterWord(char *w);
void addWord(char *w, char words[MAX_NUM_WORDS][WORD_LENGHT], int occur[MAX_NUM_WORDS], int *word_count);
void sortWords(char words[MAX_NUM_WORDS][WORD_LENGHT], int occur[MAX_NUM_WORDS], int word_count);
void removeNonAlpha(char *w); /*removes non alphanumeric characters and changes them to lowercase*/
void myTest();

int main()
{
	myTest();
	return 0;
}

int getAndFilterWord(char *w)
{
	int ret=1;
	w[0] = '\0'; /*initialize*/

	scanf("%s", w); /*scans text from user, (and from buffer)*/
	removeNonAlpha(w); /*removes non alphanumeric characters and changes them to lowercase*/

	if(strcmp(w,"end")==0) /*"end" is terminating word*/
		ret=0;

	return ret;
}

void addWord(char *w, char words[MAX_NUM_WORDS][WORD_LENGHT], int occur[MAX_NUM_WORDS], int *word_count)
{
	int i=0;
	for(i=0; i<*word_count; i++)
	{
		if(strcmp(words[i],w)==0) /*if word is already in the words array*/
		{
			occur[i]++; /*increase only the occur array*/
			break; /*break if found the same word in words array*/
		}
	}

	if(*word_count == i) /*if word is not in the words array*/
	{
		strcpy(words[i], w); /*add it to words array*/
		(*word_count)++; /*increase word count by one*/
		occur[i]=1; /*set occur(same index) 1*/
	}
}

void sortWords(char words[MAX_NUM_WORDS][WORD_LENGHT], int occur[MAX_NUM_WORDS], int word_count)
{
	/*gonna sort both of the arrays so here is variables needed for selection sort*/
	int i,j,position,tempOcc;
	char temp[WORD_LENGHT];

	/*selection sort*/
	for(i=0; i<word_count-1; i++)
	{
		position=i;
		for(j=i+1; j<word_count; j++)
		{
			if(occur[position]>occur[j])
				position = j;
		}
		if(position != i)
		{
			/*sort occur array*/
			tempOcc=occur[i];
			occur[i] = occur[position];
			occur[position]= tempOcc;
			/*sort words array*/
			strcpy(temp,words[i]);
			strcpy(words[i],words[position]);
			strcpy(words[position], temp);
		}
	}
}

void removeNonAlpha(char *w)
{
	int i=0,j=0,k=0;
	char c;

	while((c=w[i++]) != '\0')
	{
		if(isalnum(c)) /*checks if c is alphanumeric*/
			w[j++] = c;
	}
	w[j]='\0'; /*only reads alphanumeric chars*/

	while(w[k])
	{
		w[k]=tolower(w[k]); /*to lowercase every character in word*/
		k++;
	}
}

void myTest()
{
	int i,getWordRet;
	char word[WORD_LENGHT];
	char words[MAX_NUM_WORDS][WORD_LENGHT];
	int occur[MAX_NUM_WORDS];

	/*initialize arrays and others at first*/
	int word_count=0;
	word[0]= '\0';
	for(i=0; i<MAX_NUM_WORDS; i++)
	{
		occur[i] = 0;
		words[i][0]= '\0';
	}

	while(1)
	{
		getWordRet = getAndFilterWord(word);

		if(getWordRet==0)
			break; /*exit the loop if user types terminating word "end"*/
		else
			addWord(word, words, occur, &word_count); /*user keeps on typing texts, add words to words array*/
	}
	sortWords(words, occur, word_count); /*user no longer types texts so sort the words and occurances array*/

	for(i=0; i<word_count; i++) /*and at last, print both of the sorted arrays*/
		printf("Word: %s \t\tOccurance: %d\n", words[i], occur[i]);
}
