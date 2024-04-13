#include <stdio.h>

struct RecordType
{
    int id;
    char name;
    int order;
};

struct HashType
{
    struct RecordType record;
    struct HashType *next;
};

int hash(int x)
{
    return x % 23;
}


int parseData(char *inputFileName, struct RecordType **ppData)
{
    FILE *inFile = fopen(inputFileName, "r");
    int dataSz = 0;
    int i, n;
    char c;
    struct RecordType *pRecord;
    *ppData = NULL;

    if (inFile)
    {
        fscanf(inFile, "%d\n", &dataSz);
        *ppData = (struct RecordType *)malloc(sizeof(struct RecordType) * dataSz);
        if (*ppData == NULL)
        {
            printf("Cannot allocate memory\n");
            exit(-1);
        }
        for (i = 0; i < dataSz; ++i)
        {
            pRecord = *ppData + i;
            fscanf(inFile, "%d ", &n);
            pRecord->id = n;
            fscanf(inFile, " %c ", &c);
            pRecord->name = c;
            fscanf(inFile, "%d ", &n);
            pRecord->order = n;
        }
        fclose(inFile);
    }
    return dataSz;
}

void printRecords(struct RecordType pData[], int dataSz)
{
    int i;
    printf("\nRecords:\n");
    for (i = 0; i < dataSz; ++i)
    {
        printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
    }
    printf("\n\n");
}

void displayRecordsInHash(struct HashType* hashArray[], int hashSz)
{
    for (int i = 0; i < hashSz; ++i)
    {
        if (hashArray[i] != NULL)
        {
            printf("Index %d -> ", i);
            struct HashType* current = hashArray[i];
            while (current != NULL)
            {
                printf("%d, %c, %d ", current->record.id, current->record.name, current->record.order);
                if (current->next != NULL)
                {
                    printf("-> ");
                }
                current = current->next;
            }
            printf("\n");
        }
    }
}

int main(void)
{
    struct RecordType *pRecords;
    int recordSz = 0;

    recordSz = parseData("input_lab_9.txt", &pRecords);
    printRecords(pRecords, recordSz);

    int hashSize = 23;
    struct HashType *hashTable[hashSize];
    for (int i = 0; i < hashSize; ++i)
    {
        hashTable[i] = NULL;
    }

    for (int i = 0; i < recordSz; ++i)
    {
        int h = hash(pRecords[i].id);
        struct HashType *newNode = (struct HashType *)malloc(sizeof(struct HashType));
        newNode->record = pRecords[i];
        newNode->next = hashTable[h];
        hashTable[h] = newNode;
    }

    displayRecordsInHash(hashTable, hashSize);

    free(pRecords);

    return 0;
}
