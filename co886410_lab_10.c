#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Trie *createTrie();

// Trie structure
struct Trie
{	
    int count;
    struct Trie* next[26];
};

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word, int k)
{
    if(k == strlen(word)){
        pTrie->count++;
        return;
    }

    int nextIndex = word[k] - 'a';
    if(pTrie->next[nextIndex] == NULL)
        pTrie->next[nextIndex] = createTrie();
    
    insert(pTrie->next[nextIndex], word, k+1);
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{
    int k = 0;
    
    while(word[k] != '\0'){
        int nextIndex = word[k] - 'a';
        if(pTrie->next[nextIndex] == NULL)
            return 0;
        
        pTrie = pTrie->next[nextIndex];
        k++;
    }

    return pTrie->count;
}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{
    for(int i = 0; i < 26; i++)
        if(pTrie->next[i] != NULL)
            deallocateTrie(pTrie->next[i]);
    
    free(pTrie);
    return NULL;
}

// Initializes a trie structure
struct Trie *createTrie()
{
    struct Trie* myTree = malloc(sizeof(struct Trie));
    myTree->count = 0;

    for(int i = 0; i < 26; i++){
        myTree->next[i] = NULL;
    }

    return myTree;
}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
    int n;
    char word[100];

    FILE* ifp = fopen(filename, "r");
    fscanf(ifp, "%d", &n);

    for(int i = 0; i < n; i++){
        fscanf(ifp, "%s", word);
        pInWords[i] = malloc(strlen(word) + 1);
        strcpy(pInWords[i], word);
    }

    return n;
}

int main(void)
{
	char *inWords[256];
	
	//read the number of the words in the dictionary
	int numWords = readDictionary("dictionary.txt", inWords);
	for (int i=0;i<numWords;++i)
	{
		printf("%s\n",inWords[i]);
	}
	
	struct Trie *pTrie = createTrie();
	for (int i=0;i<numWords;i++)
	{
		insert(pTrie, inWords[i], 0);
	}
	// parse lineby line, and insert each word to the trie data structure
	char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
	for (int i=0;i<5;i++)
	{
		printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
	}
	pTrie = deallocateTrie(pTrie);
	if (pTrie != NULL)
		printf("There is an error in this program\n");
	return 0;
}