#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <string.h>

#include "Data.h"
#include "GetFunc.h"
#include "CompareAndDefine.h"

const int SIZE_OF_PIC_NAME = 80;
const int SIZE_OF_COMMAND = 80;

int GetNumOfCommand (void)
{
    int num = 0;

    AskCommandNumber();

    scanf("%d", &num);
    int c = getchar();
    if (c != '\n' && c != ' ')
        return -1;

    return num;
}


const char * GetPlace (Place_t place)
{
    if (place == Before)
        return "BEFORE";
    else if (place == After)
        return "AFTER"; // FIXME: fix return
    else
        return "AT";
}


char * GetCommand (char * pic_name)
{
    assert(pic_name);

    char * command = (char *) calloc (SIZE_OF_COMMAND, sizeof(char));
    assert(command); // FIXME: check

    sprintf(command, "dot akinatordump.txt -T png -o %s", pic_name);

    return command;
}


char * GetPicName (void)
{
    static int pic_count = 0;

    char * pic_name = (char *) calloc (SIZE_OF_PIC_NAME, sizeof(char));
    assert(pic_name); // FIXME: return error

    sprintf(pic_name, "akinatordump%d.png", pic_count);
    pic_count++;

    return pic_name;
}


FILE * GetLog (Tree_t * tree)
{
    assert(tree);

    return tree->log;
}


bool GetAnswer (void) // FIXME bool to enum (yes/no)
{
    for (;;)
    {
        char * answer = AllocMemAndScanfString();
        if (strcmp(answer, "yes") == 0)
        {
            free(answer);
            return true;
        }
        else if (strcmp(answer, "no") == 0)
        {
            free(answer);
            return false;
        }
        else
        {
            free(answer);
            TellThatAnswerIsIncorrect();
        }
    }
}


void TellThatAnswerIsIncorrect (void)
{
    printf("You should answer \"yes\" or \"no\".\n");
}


void AskCommandNumber (void)
{
    printf("Choose command number: 1) Guess the object 2) Define the object 3) Compare two objects\n");
    printf("(command number): ");
}
