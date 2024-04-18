#include <stdio.h>
#include <string.h>

#define MAX_STATES 10
#define MAX_INPUT_SYMBOLS 10
#define MAX_STRING_LENGTH 100

typedef struct DFA
{
    int nos;                    // no of states
    int noi;                    // no of input 
    int nof;                    // no of final states 
    int delta[MAX_STATES][MAX_INPUT_SYMBOLS];  // transition 
    int final[MAX_STATES];      
    char inputSymbols[MAX_INPUT_SYMBOLS];
    char stateNames[MAX_STATES][20];  // Store state names
} DFA;

int checkSymbol(char ch, DFA d)
{
    for(int i = 0; i < d.noi; i++)
    {
        if(ch == d.inputSymbols[i])
        {
            return i;  
        }
    }
    return -1;
}

int checkFinalState(int st, DFA d)
{
    for(int i = 0; i < d.nof; i++)
    {
        if(st == d.final[i])
        {
            return 1;  
        }
    }
    return 0;
}

int getStateIndex(char stateName[], DFA d)
{
    for(int i = 0; i < d.nos; i++)
    {
        if(strcmp(stateName, d.stateNames[i]) == 0)
        {
            return i;
        }
    }
    return -1;
}

int main()
{
    DFA d;
    printf("\nEnter no of states: ");
    scanf(" %d", &d.nos);
    printf("\nEnter no of final states: ");
    scanf(" %d", &d.nof);
    printf("\nEnter no of input symbols: ");
    scanf(" %d", &d.noi);
    
    // accept the state names
    for(int i = 0; i < d.nos; i++)
    {
        printf("Enter State Name %d : ", i + 1);
        scanf(" %s", d.stateNames[i]);
    }
    
    // accept the input symbols
    for(int i = 0; i < d.noi; i++)
    {
        printf("Enter Input Symbol %d : ", i + 1);
        scanf(" %c", &d.inputSymbols[i]);
    }
    
    // accept the final states
    for(int i = 0; i < d.nof; i++)
    {
        char stateName[20];
        printf("Enter the Final State Name %d : ", i + 1);
        scanf(" %s", stateName);
        d.final[i] = getStateIndex(stateName, d);
    }

    // accept the starting state
    char startState[20];
    printf("Enter the Starting State: ");
    scanf(" %s", startState);
    int currentState = getStateIndex(startState, d);
    
    printf("\nEnter transitions: ");
    
    for(int i = 0; i < d.nos; i++)
        for(int j = 0; j < d.noi; j++)
        {
            char toState[20];
            printf("\nd(%s, %c) : ", d.stateNames[i], d.inputSymbols[j]);
            scanf(" %s", toState);
            d.delta[i][j] = getStateIndex(toState, d);
        }
    
    // print the transition table
    // print the symbols as columns of transition table
    for(int i = 0; i < d.noi; i++)
        printf("\t %c", d.inputSymbols[i]);
    printf("\n");
    for(int i = 0; i < d.nos; i++)
    {
        printf("\n%s", d.stateNames[i]);  
        for(int j = 0; j < d.noi; j++)
        {
            printf("\t%s", d.stateNames[d.delta[i][j]]);
        }
        printf("\n");
    }
    
    do
    {
        char string[MAX_STRING_LENGTH]; 
        printf("\nEnter a string: ");
        scanf("%s", string);
        int stateCounter = currentState; // Start from the specified starting state
        int flag = 1;
        
        for(int i = 0; i < strlen(string); i++) 
        {
            int symPos = checkSymbol(string[i], d);
            if(symPos == -1)
            {
                flag = 0;
                break;
            }
            stateCounter = d.delta[stateCounter][symPos];
        }
        
        if(flag == 1 && checkFinalState(stateCounter, d) == 1)
        {
            printf("Transition Path: %s", d.stateNames[currentState]);
            for(int i = 0; i < strlen(string); i++) 
            {
                int symPos = checkSymbol(string[i], d);
                currentState = stateCounter; // Update current state
                stateCounter = d.delta[stateCounter][symPos];
                printf(" -> %s", d.stateNames[stateCounter]);
            }
            printf("\n%s is accepted. ", string);
        }
        else
        {
            printf("%s is not accepted. ", string);
        }
    } while(1); 
    
    return 0;
}
