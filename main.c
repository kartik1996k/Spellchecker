#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include<malloc.h>
int depth=0;
//the use of trie data structure gives an efficient way of searching for a string.
//the string with O(n) size and a substring with O(m) size takes O(n) minimum time to be searched,and takes least amount of memory.
//this algorithm searches the substring in O(m) time which is independent of the source string.
//TIME= O(|m|)!
//the program has successfully loaded a dictionary onto a trie.
struct trie
{
    int val;
    struct trie *alpha[26];
}*root=NULL;
struct trie* newnode()
{
    int i;
   struct trie *n= malloc(sizeof(struct trie));
        if(n==NULL)
            printf("YOU ARE DOOMED");
        n->val=1;
    for(i=0;i<26;i++)
            n->alpha[i]=NULL;
    return n;
}
void insertin(char a[])
{
    int i=0,l=strlen(a);
    if(l!=0)
    {if(root==NULL)
    {
        root=newnode();
        root->val=1;
    }
struct trie* n=root;
    while(i<l)
        {
            while(n->alpha[a[i]-'a']!=NULL)
            {
                n=n->alpha[a[i]-'a'];
                i++;
                if(i==l)break;
            }
            if(i==l)break;
            if(i!=l)
            {
            n->alpha[a[i]-'a']=newnode();
            }
        }
        n->val=0;
    }
}
int search(char a[])
{
    int i=0,l=strlen(a);
    struct trie* n=root;
    while(i<l)
        {
            while(n->alpha[a[i]-'a']!=NULL && i<l)
            {
                n=n->alpha[a[i]-'a'];
                i++;
            }
            if(i==l)
            {
                if(n->val==0)
                printf("FOUND!");
                else
                    printf("NOT FOUND!");
                return 1;
            }
            else
            {
                printf("NOT FOUND!");
                return 0;
            }
            }
    printf("NOT FOUND");
    return 0;
}
void unload_trie(struct trie *temp)
{
    struct trie *t=temp;
    int i=0;
    for(i=0;i<26;i++)
    {
        if(t->alpha[i]!=NULL)
            unload_trie(t->alpha[i]);
    }
    free(t);
}
int main()
{
    int i=0,n=0;
    char ins[40],c;
    FILE *f;
    f=fopen("words.txt","r");
    while(1)
    {
        i=0;
        c=fgetc(f);
        while(c=='\n')c=fgetc(f);
        if(c==EOF)break;
        while(isalpha(c))
        {
            if(c<'a')
                c='a'+c-'A';
            ins[i++]=c;
            c=fgetc(f);
        }
        n++;
        ins[i]='\0';
            insertin(ins);
           // printf("\n%s %d",ins,n);
    }
   printf("Dictionary loaded successfully on the TRIE DATA STRUCTURE!");
    printf("\nEnter \"END\" to stop.");
    printf("\nenter words to search:(lower_case only)\n");
    while(1)
    {
        scanf("%s",ins);
        if(strcmp(ins,"END")==0)break;
        else
            search(ins);
            printf("\n");
    }
    unload_trie(root);
    printf("\nTRIE UNLOADED!");
    return 0;
}
