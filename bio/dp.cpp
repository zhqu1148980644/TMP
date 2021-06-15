#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MATCH 5
#define MISMATCH -4
#define GAP -3
#define MAX_LEN 500
#define FILE_LEN 50

char *s_gets(char *st, int n);

int fetch_sequence(FILE *fa, char *seq1, char *seq2);

int fill_matrix(int len, int (*mat)[len], int len1, int len2, char *seq1, char *seq2);

int trace_back(int len, int (*mat)[len], const char *seq1, const char *seq2, char *out1, char *out2, int row, int col);

int main(void) {
    int mode;
    FILE *fa;
    char file_name[FILE_LEN];
    char seq1[MAX_LEN];
    char seq2[MAX_LEN];
    int len1;
    int len2;
    int row, col;


    printf("Please select the mode (input for 1,file for 2,q to quit):\n");
    while (scanf("%d", &mode) == 1 && (mode == 1 || mode == 2)) {
        // mode 1,fetch sequences from stdin
        if (mode == 1) {
            while (getchar() != '\n')
                continue;
            printf("please input your first sequence:\n");
            s_gets(seq1, MAX_LEN);
            printf("please input your second sequence:\n");
            s_gets(seq2, MAX_LEN);
        }
        // mode 2,fetch sequence from file
        if (mode == 2) {
            while (getchar() != '\n')
                continue;
            printf("Please enter th file name to read:\n");
            s_gets(file_name, FILE_LEN);
            if ((fa = fopen(file_name, "r+")) == NULL) {
                fprintf(stderr, "Can't open %s\n", file_name);
                exit(EXIT_FAILURE);
            }
            fetch_sequence(fa, seq1, seq2);
        }
        // initiate (m+1, n+1) matrix
        len1 = strlen(seq1);
        len2 = strlen(seq2);
        int (*mat)[len2 + 1];
        mat = (int (*)[len2 + 1]) malloc((len1 + 1) * (len2 + 1) * sizeof(int));
        // fill the matrix
        fill_matrix(len2 + 1, mat, len1, len2, seq1, seq2);

        // show dynamic programming matrix
        printf("Dynamic programming scoring matrix is:\n");
        for (row = 0; row < (len1 + 1); row++) {
            // print first line represent seq2
            if (row == 0) {
                printf("          ");
                for (col = 0; col < len2; col++) {
                    printf("%-5c", seq2[col]);
                }
                printf("\n");
                printf("     ");
            } else {
                // print first column represent seq1
                printf("%-5c", seq1[row - 1]);
            }
            // print matrix
            for (col = 0; col < len2 + 1; col++) {
                printf("%-5d", mat[row][col]);
            }
            putchar('\n');
        }


        // trace back,find the best matching path
        char out_seq1[MAX_LEN];
        char out_seq2[MAX_LEN];
        memset(out_seq1, 0, MAX_LEN);
        memset(out_seq2, 0, MAX_LEN);

        // find trace back point
        int max_i, max_j;
        max_i = len1;
        max_j = len2;

        // trace back from point i, j
        trace_back(len2 + 1, mat, seq1, seq2, out_seq1, out_seq2, max_i, max_j);
        free(mat);
        printf("origin two sequence:\n");
        // show original two sequence
        puts(seq1);
        puts(seq2);
        // show alignment
        printf("alignment:\n");
        int len = strlen(out_seq1);
        int cor;
        for (cor = (len - 1); cor > -1; cor--) {
            putchar(out_seq1[cor]);
        }
        printf("\n");
        for (cor = (len - 1); cor > -1; cor--) {
            putchar(out_seq2[cor]);
        }
        printf("\n");

        printf("Please select the mode (input for 1,file for 2,q to quit):\n");
    }

    return 0;
}

char *s_gets(char *st, int n) {
    char *ret_val;
    char *find;
    ret_val = fgets(st, n, stdin);
    if (ret_val) {
        find = strchr(st, '\n');
        if (find) {
            *find = '\0';
        } else {
            while (getchar() != '\n')
                continue;
        }
    }
    return ret_val;
}

int fetch_sequence(FILE *fa, char *seq1, char *seq2) {
    char *find;
    fgets(seq1, MAX_LEN, fa);
    fgets(seq2, MAX_LEN, fa);
    find = strchr(seq1, '\n');
    if (find)
        *find = '\0';
    find = strchr(seq2, '\n');
    if (find)
        *find = '\0';
    return 0;
}

int fill_matrix(int len, int (*mat)[len], int len1, int len2, char *seq1, char *seq2) {
    int row, col;
    int up, left, diag;
    for (row = 0; row < (len1 + 1); row++) {
        for (col = 0; col < (len2 + 1); col++) {
            if (row == 0) {
                mat[row][col] = col * GAP;
            } else if (col == 0) {
                mat[row][col] = row * GAP;
            } else {
                up = mat[row - 1][col] + GAP;
                left = mat[row][col - 1] + GAP;
                diag = mat[row - 1][col - 1] + ((seq1[row - 1] == seq2[col - 1]) ? MATCH : MISMATCH);
                up = (up > left) ? up : left;
                mat[row][col] = (up > diag) ? up : diag;
            }
        }
    }
    return 0;
}

int trace_back(int len, int (*mat)[len], const char *seq1, const char *seq2, char *out1, char *out2, int row, int col) {
    int value;
    char *find1, *find2;
    while (!(col == 0 && row == 0)) {
        value = mat[row][col];
        find1 = strchr(out1, '\0');
        find2 = strchr(out2, '\0');
        // up
        if ((row - 1 >= 0) && (mat[row - 1][col] + GAP) == value) {
            *find1 = *(seq1 + (row - 1));
            *find2 = '-';
            row = row -1;
        }
        // left
        else if ((col - 1 >= 0) && (mat[row][col - 1] + GAP) == value) {
            *find1 = '-';
            *find2 = *(seq2 + (col - 1));
            col = col - 1;
        }
        // diag
        else {
            *find1 = *(seq1 + (row - 1));
            *find2 = *(seq2 + (col - 1));
            row = row - 1;
            col = col - 1;
        }
    }
    return 0;
}