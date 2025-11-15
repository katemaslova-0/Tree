#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "Data.h"
#include "GuessFunc.h"
#include "GetFunc.h"
#include "TreeFunc.h"

/*Inside functions for GuessTheObject*/

Node_t * AskUntilTheEnd (Node_t * current) // FIXME
{
    assert(current);

    while (current->left != NULL)
    {
        printf("%s?", current->data);
        if (GetAnswer() == true)
            current = current->left;
        else
            current = current->right;
    }

    return current;
}


void AskFinalQuestion (Node_t * current)
{
    assert(current);
    printf("%s? ", current->data);
}


Err_t RequestNewObject (Tree_t * tree, Node_t * current)
{
    assert(tree);
    assert(current);

    printf("So what is it?\n");
    Err_t res = NoError;
    if ((res = AddNode(tree, current)) != NoError)
        return res;

    printf("The object has been added! ");
    return NoError;
}
