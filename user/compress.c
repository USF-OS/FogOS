#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/spinlock.h"
#include "kernel/sleeplock.h"
#include "kernel/fs.h"
#include "kernel/file.h"
#include "user/user.h"
#include "kernel/fcntl.h"

#define NULL ((void *) 0)

// Huffman tree node definition
typedef struct Node {
    char data; // store char
    unsigned freq; // store frequency
    struct Node *left, *right; // left node and right node
} Node;

// MinHeap definition
typedef struct {
    int size;      // Number of elements in the heap
    int capacity;  // Maximum capacity in the heap
    Node **array;  // A pointer to the node array
} MinHeap;


// Swap the pointers of two nodes
void swapNode(Node **a, Node **b) {
    Node *t = *a;
    *a = *b;
    *b = t;
}

// Create a MinHeap
MinHeap *createMinHeap(int capacity) {
    MinHeap *minHeap = (MinHeap *) malloc(sizeof(MinHeap));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (Node **) malloc(minHeap->capacity * sizeof(Node *));
    return minHeap;
}

// Create a new node and initialize it
Node *newNode(char data, unsigned freq) {
    Node *temp = (Node *) malloc(sizeof(Node));
    temp->left = NULL;
    temp->right = NULL;
    temp->data = data;
    temp->freq = freq;
    return temp;
}

// Insert a node into the MinHeap
void insertMinHeap(MinHeap *minHeap, Node *node) {
    minHeap->size += 1;
    int i = minHeap->size - 1;

    while (i && node->freq < minHeap->array[(i - 1) / 2]->freq) {
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    minHeap->array[i] = node;
}

// Maintain the character of MinHeap
void maintainMinHeap(MinHeap *minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->array[left]->freq < minHeap->array[smallest]->freq)
        smallest = left;

    if (right < minHeap->size && minHeap->array[right]->freq < minHeap->array[smallest]->freq)
        smallest = right;

    if (smallest != idx) {
        swapNode(&minHeap->array[smallest], &minHeap->array[idx]);
        maintainMinHeap(minHeap, smallest);
    }
}

// Build MinHeap
void buildMinHeap(MinHeap *minHeap) {
    int n = minHeap->size - 1;
    for (int i = (n - 1) / 2; i >= 0; i--)
        maintainMinHeap(minHeap, i);
}

// Create and build MinHeap with char array and corresponding frequency
MinHeap *createAndBuildMinHeap(char data[], int freq[], int size) {
    MinHeap *minHeap = createMinHeap(size);

    for (int i = 0; i < size; ++i)
        minHeap->array[i] = newNode(data[i], freq[i]);

    minHeap->size = size;
    buildMinHeap(minHeap);

    return minHeap;
}

// Get the size of the MinHeap
int minHeapSize(MinHeap *minHeap) {
    return minHeap->size;
}

// Get the Minimum node from the MinHeap
Node *getMin(MinHeap *minHeap) {
    if (minHeapSize(minHeap) == 0) {
        return NULL;
    }
    // Root node
    Node *temp = minHeap->array[0];
    // Move last node to the place of root node
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    // Decrease the size of the MinHeap
    minHeap->size -= 1;
    // Maintain the MinHeap
    maintainMinHeap(minHeap, 0);
    return temp;
}

// Build up Huffman Tree
Node *buildHuffmanTree(char data[], int freq[], int size) {
    Node *left, *right, *top;

    MinHeap *minHeap = createAndBuildMinHeap(data, freq, size);

    while (minHeapSize(minHeap) > 1) {
        left = getMin(minHeap);
        right = getMin(minHeap);

        top = newNode('-', left->freq + right->freq);

        top->left = left;
        top->right = right;

        insertMinHeap(minHeap, top);
    }
    return getMin(minHeap);
}

void printCodes(Node *root, int arr[], int top, int fd) {
    if (root->left) {
        arr[top] = 0;
        printCodes(root->left, arr, top + 1, fd);
    }

    if (root->right) {
        arr[top] = 1;
        printCodes(root->right, arr, top + 1, fd);
    }

    if (!root->left && !root->right) {
        if (!root->left && !root->right) {
            if (root->data == '\n') {
                fprintf(fd, "~:");
            } else {
                fprintf(fd, "%c:", root->data);
            }
            for (int i = 0; i < top; ++i) {
                fprintf(fd, "%c", '0' + arr[i]);
            }
            fprintf(fd, "\n");
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 3) return 1;
    char *filename = argv[1];
    compress(filename);
    int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        // Handle error: file open failed
        return 1;
    }
    int freq[256] = {0};

    char buffer;
    int readsize;
    while ((readsize = read(fd, &buffer, 1)) > 0) {
        freq[(unsigned char) buffer]++;
    }

    close(fd);

    int count = 0;
    for (int i = 0; i < 256; i++) {
        if (freq[i] > 0) {
            count++;
        }
    }

    char chars[count];
    int counts[count];
    int j = 0;
    for (int i = 0; i < 256; i++) {
        if (freq[i] > 0) {
            chars[j] = i;
            counts[j] = freq[i];
            j++;
        }
    }

    struct Node *root = buildHuffmanTree(chars, counts, sizeof(chars) / sizeof(chars[0]));
    int huffmanCode[256];

    int fd2 = open(argv[2], O_CREATE | O_RDWR);

    printCodes(root, huffmanCode, 0, fd2);

    // Read huffman code from table

    int fd3 = open(argv[2], O_RDONLY);

    int count3 = 0;
    char temp3, buffer3[129];
    int index3 = 0;
    char *symbol3 = malloc(256);
    char **code3 = malloc(256);
    while (read(fd3, &temp3, 1) > 0) {
        if (temp3 != '\n' && index3 < 128) {
            buffer3[index3++] = temp3;
        } else {
            buffer3[index3] = '\0';
            if (index3 > 1) {
                symbol3[count3] = buffer3[0];
                code3[count3] = (char *) malloc(strlen(buffer3 + 1) + 1);
                if (code3[count3] != NULL) {
                    strcpy(code3[count3], buffer3 + 2);
                }
                count3++;
            }
            index3 = 0;
        }
    }

    fprintf(fd2, "\n\n");
    int fd4 = open(filename, O_RDONLY);
    if (fd4 < 0) {
        // Handle error: file open failed
        return 1;
    }

    char buffer4;
    int readsize4;
    while ((readsize4 = read(fd4, &buffer4, 1)) > 0) {
        if (buffer4 == '\n')buffer4 = '~';
        for (int i = 0; i < count3; i++) {
            if (symbol3[i] == (unsigned char) buffer4) {
                fprintf(fd2, "%s ", code3[i]);
            }
        }
    }

    close(fd2);
    close(fd3);
    close(fd4);

    return 0;
}
