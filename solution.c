#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to reverse a string in place.
void reverse(char *s) {
    int i = 0, j = strlen(s) - 1;
    while (i < j) {
        char tmp = s[i];
        s[i] = s[j];
        s[j] = tmp;
        i++;
        j--;
    }
}

// Comparison function for qsort
int cmp_str(const void *a, const void *b) {
    char * const *s1 = (char * const *)a;
    char * const *s2 = (char * const *)b;
    return strcmp(*s1, *s2);
}

// Lower bound: first index where arr[index] >= key
int lower_bound(char **arr, int n, const char *key) {
    int low = 0, high = n;
    while(low < high) {
        int mid = low + (high - low) / 2;
        if(strcmp(arr[mid], key) < 0) {
            low = mid + 1;
        } else {
            high = mid;
        }
    }
    return low;
}

// Upper bound: first index where arr[index] > key (for prefix search, we'll adapt after lower_bound)
int upper_bound(char **arr, int n, const char *key) {
    int low = 0, high = n;
    while(low < high) {
        int mid = low + (high - low) / 2;
        if(strcmp(arr[mid], key) <= 0) {
            low = mid + 1;
        } else {
            high = mid;
        }
    }
    return low;
}

// To support prefix search, we build an artificial key by appending a character that is higher than 'z'.
// Since strings contain only lowercase letters a-z, we can append '{' (ASCII value 123) as it is one more than 'z' (122).

int main() {
    int N, Q;
    scanf("%d", &N);

    // Allocate array of strings for A, each with maximum length 101 (100 + 1 for null).
    char **A = (char **)malloc(N * sizeof(char *));
    for (int i = 0; i < N; i++) {
        A[i] = (char *)malloc(102 * sizeof(char));
        scanf("%s", A[i]);
        // Reverse each string to facilitate suffix matching with prefix search
        reverse(A[i]);
    }

    // Sort the reversed strings
    qsort(A, N, sizeof(char *), cmp_str);

    scanf("%d", &Q);
    
    // Process queries
    for (int i = 0; i < Q; i++) {
        char query[102];
        scanf("%s", query);
        // Reverse the query to convert suffix search into prefix search
        reverse(query);
        
        // For prefix search, lower_bound with query and upper_bound with query appended with '{'
        int lb = lower_bound(A, N, query);
        
        // Build the higher bound key by appending '{' to query
        char queryHigh[104];
        snprintf(queryHigh, sizeof(queryHigh), "%s%c", query, '{');
        int ub = lower_bound(A, N, queryHigh);
        
        // Count of strings having the suffix is difference between upper and lower bound indices
        int count = ub - lb;
        
        printf("%d ", count);
    }
    printf("\n");

    // Clean up
    for (int i = 0; i < N; i++) {
        free(A[i]);
    }
    free(A);
    return 0;
}