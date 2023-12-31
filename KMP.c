#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSTR 1000000
#define MAXPAT 100000

void build_next(char *pat, int next[]){
    int lenth = strlen(pat), j = 0, k = -1;
    next[0] = -1;
    while (j < lenth - 1){
        if (k == -1 || pat[j] == pat[k]){
            k++;
            j++;
            next[j] = k;
        }
        else
            k = next[k];
    }
}

int KMP1(char *str, char *pat){
    int n = strlen(str), m = strlen(pat), s = 0, p = 0, *next = malloc(sizeof(int) * m);
    build_next(pat, next);
    while (s < n && p < m){
        if (p == -1 || str[s] == pat[p]){
            s++;
            p++;
        }
        else
            p = next[p];
    }
    free(next);
    return (p == m) ? s - m : -1;
}

void build_match(char *pat, int match[]){
    int lenth = strlen(pat);
    match[0] = -1;
    for (int j = 1; j < lenth; j++){
        int i = match[j - 1];
        while (i >= 0 && pat[i + 1] != pat[j])
            i = match[i];
        if (pat[i + 1] == pat[j])
            match[j] = i + 1;
        else
            match[j] = -1;
    }
}

int KMP2(char *str, char *pat){
    int n = strlen(str), m = strlen(pat), s = 0, p = 0, *match = malloc(sizeof(int) * m);
    build_match(pat, match);
    while (s < n && p < m){
        if (str[s] == pat[p]){
            s++;
            p++;
        }
        else if (p > 0)
            p = match[p - 1] + 1;
        else
            s++;
    }
    return (p == m) ? s - m : -1;
}

int main(){
    char str[MAXSTR + 1];
    scanf("%s", str);
    int N;
    scanf("%d", &N);
    for (int i = 0; i < N; i++){
        char pat[MAXPAT + 1];
        scanf("%s", pat);
        int p = KMP2(str, pat);
        if (p == -1)
            printf("Not Found\n");
        else
            printf("%s\n", str + p);
    }
}