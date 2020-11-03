#include <bits/stdc++.h>
#define MAXSTRLEN 255
using namespace std;

typedef unsigned char SString[MAXSTRLEN + 1];
int nextM[MAXSTRLEN + 1];

int getNext(SString T)
{
    int i = 1, j = 0;
    nextM[1] = 0;
    while(i < T[0])
    {
        if(j == 0 || T[i] == T[j])
        {
            j++;
            i++;
            nextM[i] = j;
        }
        else{
            j = nextM[j];
        }
    }
}

int indexKMP(SString S, SString T, int pos)
{
    int i = pos, j = 1;
    while (i <= S[0] && j <= T[0])
    {
        if (j == 0 || S[i] == T[j])
        {
            i++;
            j++;
        }
        else
        {
            j = nextM[j];
        }
    }
    if (j > T[0])
    {
        return i - T[0];
    }
    else
    {
        return 0;
    }
}

int main()
{
    SString S, T;
    
}