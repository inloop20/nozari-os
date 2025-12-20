#include "string.h"
void itoa(int n, char* str) {
    int i = 0;
    if (n == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return;
    }

    while (n > 0) {
        str[i++] = (n % 10) + '0';
        n /= 10;
    }
    str[i] = '\0';
    reverse(str);
}

int strlen(char* str){
    int i;
    for(i=0;str[i]!='\0';i++){
    }
    return i;
}

void reverse(char *str){
    int i,j;
    i=0,j=strlen(str)-1;
    while(i<j){
        char tmp = str[i];
        str[i] = str[j];
        str[j] = tmp;
        i++;
        j--;
    }
}

void push(char s[],char c){
    int len = strlen(s);
    s[len] = c;
    s[len+1] = '\0';
}

void pop(char s[]){
    int len = strlen(s);
    s[len-1] = '\0';
}

int strcmp(char s1[], char s2[]) {
    int i;
    for (i = 0; s1[i] == s2[i]; i++) {
        if (s1[i] == '\0') return 0;
    }
    return s1[i] - s2[i];
}