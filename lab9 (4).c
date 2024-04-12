#include <stdio.h>
#include <stdlib.h>

// RecordType
struct RecordType
{
    int id;
    char name;
    int order;
};

// Fill out this structure
struct HashType
{
    struct RecordType record;
    struct HashType *next;
};

// Compute the hash function
int hash(int x)
{
    return x % 10;
}

// parses input file to an integer array
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

// prints the records
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

// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType *hashArray[], int hashSz)
{
    for (int i = 0; i < hashSz; ++i)
    {
        // If the hash table at index i is not NULL, meaning it contains records
        if (hashArray[i] != NULL)
        {
            printf("Index %d -> ", i); // Print the index

            // Iterate over the linked list at this index
            struct HashType *current = hashArray[i];
            while (current != NULL)
            {
                // Print the record details
                printf("%d %c %d -> ", current->record.id, current->record.name, current->record.order);
                current = current->next;
            }
            printf("NULL\n"); // Print "NULL" to indicate the end of the linked list
        }
    }
}



int main(void)
{
    struct RecordType *pRecords;
    int recordSz = 0;

    recordSz = parseData("input_lab_9.txt", &pRecords);
    printRecords(pRecords, recordSz);

    // Initialize hash table
    int hashSize = recordSz; // Set the hash table size to the number of records
    struct HashType *hashTable[hashSize];
    for (int i = 0; i < hashSize; ++i)
    {
        hashTable[i] = NULL;
    }

    // Populate the hash table
    for (int i = 0; i < recordSz; ++i)
    {
        int h = hash(pRecords[i].id); // Compute the hash value for the record
        struct HashType *newNode = (struct HashType *)malloc(sizeof(struct HashType)); // Create a new node
        newNode->record = pRecords[i]; // Assign the record to the node
        newNode->next = hashTable[h]; // Insert the node at the beginning of the linked list at index h
        hashTable[h] = newNode;
    }

    // Display records stored in the hash table
    displayRecordsInHash(hashTable, hashSize);

    // Free allocated memory
    free(pRecords);

    return 0;
}

