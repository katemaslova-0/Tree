#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "Data.h"
#include "StackFunc.h"
#include "AkinatorFunc.h"
#include "DumpFunc.h"
#include "CompareAndDefine.h"
#include "GuessFunc.h"
#include "GetFunc.h"


Err_t GuessTheObject (Tree_t * tree)
{
    assert(tree);

    bool if_continue = true;
    while (if_continue == true)
    {
        Node_t * current = AskUntilTheEnd(tree->root);
        AskFinalQuestion(current);
        if (GetAnswer() == false)
            RequestNewObject(tree, current);

        AskIfContinue();
        if_continue = GetAnswer();
    }

    return NoError;
}


Err_t CompareObjects (Tree_t * tree)
{
    assert(tree);

    AskNameOfTheFirstObj();
    char * first_obj  = AllocMemAndScanfString();
    AskNameOfTheSecondObj();
    char * second_obj = AllocMemAndScanfString();

    Stack_t stk1 = {};
    StackCtor(&stk1, STACK_SIZE);
    Stack_t stk2 = {};
    StackCtor(&stk2, STACK_SIZE);

    Node_t * node1 = FindDefinition(&stk1, tree->root, first_obj);

    if (!node1) // FIXME
    {
        AskToTryAgain();
        CompareObjects(tree);
    }
    else
    {
        Node_t * node2 = FindDefinition(&stk2, tree->root, second_obj);
        if (!node2)
        {
            AskToTryAgain();
            CompareObjects(tree);
        }
        else
            OutputComparison(tree, &stk1, &stk2, node1, node2);
    }

    free(first_obj);
    free(second_obj);
    return NoError;
}


Err_t DefineObject (Tree_t * tree)
{
    assert(tree);

    Stack_t stk = {};
    StackCtor(&stk, SIZE_OF_STACK);
    Node_t * defined_node = NULL;
    while (!defined_node || defined_node->left != NULL)
    {
        AskWhatToDefine(); // strings to functions
        char * object = AllocMemAndScanfString();

        defined_node = FindDefinition(&stk, tree->root, object);
        free(object);

        if (!defined_node || defined_node->left != NULL)
            AskToTryAgain();
    }

    OutputDefinition(&stk);
    StackDtor(&stk);
    return NoError;
}


void AskWhatToDefine (void)
{
    printf("What do you want to define? ");
}

void AskToTryAgain (void)
{
    printf("The object does not exist!\nTry again.");
}

void AskNameOfTheFirstObj (void)
{
    printf("Name of the first object: ");
}

void AskNameOfTheSecondObj (void)
{
    printf("Name of the second object: ");
}

void AskIfContinue (void)
{
    printf("Continue? (yes/no) \n");
}
