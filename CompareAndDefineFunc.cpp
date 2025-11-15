#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "Data.h"
#include "StackFunc.h"
#include "CompareAndDefine.h"

/*Inside functions for DefineObject and CompareObjects*/

Node_t * FindNode (Node_t * node, const char * string)
{
    assert(node);
    assert(string);

    if (strcmp(string, node->data) == 0)
        return node;

    Node_t * res_node = NULL;

    if (node->left)
        if ((res_node = FindNode(node->left, string)) != NULL)
            return res_node;
    if (node->right)
        if ((res_node = FindNode(node->right, string)) != NULL)
            return res_node;

    return NULL;
}



Node_t * FindDefinition (Stack_t * stk, Node_t * node, const char * string)
{
    assert(stk);
    assert(node);
    assert(string);

    if (strcmp(string, node->data) == 0)
    {
        StackPush(stk, node);
        return node;
    }

    Node_t * res_node = NULL;

    if (node->left)
    {
        res_node = FindDefinition(stk, node->left, string);
    }
    if (res_node == NULL && node->right)
    {
        res_node = FindDefinition(stk, node->right, string);
    }
    if (res_node != NULL)
    {
        StackPush(stk, node);
    }

    return res_node;
}


void OutputDefinition (Stack_t * stk)
{
    assert(stk);

    int count = stk->size - 1;
    while (count > 1) // not going to print the object itself
    {
        Node_t * current = GetElem(stk, count);
        if (current->right == GetElem(stk, count - 1))
            printf("Isn't ");
        printf("%s\n", current->data);
        count--;
    }
}


void OutputComparison (Tree_t * tree, Stack_t * stk1, Stack_t * stk2, Node_t * node1, Node_t * node2)
{
    assert(tree);
    assert(node1);
    assert(node2);

    Node_t * current1 = tree->root;
    Node_t * current2 = tree->root;
    printf("%s and %s are both ", node1->data, node2->data);
    OutputSimilarity(tree, stk1, stk2, &current1, &current2);

    printf("but %s is ", node1->data);
    OutputDifference(stk1, current1);
    printf("and %s is ", node2->data);
    OutputDifference(stk2, current2);

    StackDtor(stk1);
    StackDtor(stk2);
}


void OutputSimilarity (Tree_t * tree, Stack_t * stk1, Stack_t * stk2, Node_t ** current1, Node_t ** current2)
{
    assert(tree);
    assert(stk1);
    assert(stk2);
    assert(current1);
    assert(current2);

    while (*current1 == *current2) // FIXME don't need current
    {
        if ((*current1)->parent && ((*current1)->parent)->right == *current1 && ((*current2)->parent)->right == *current2)
            printf("not %s, ", (*current1)->parent->data);
        if ((*current1)->parent && ((*current1)->parent)->left == *current1 && ((*current2)->parent)->left == *current2)
            printf("%s, ", (*current1)->parent->data);
        StackPop(stk1, current1);
        StackPop(stk2, current2);
    }
}


void OutputDifference (Stack_t * stk, Node_t * current)
{
    assert(stk);
    assert(current);

    while (stk->size != 0)
    {
        if ((current->parent)->right == current)
            printf("not ");
        printf("%s, ", current->parent->data);
        StackPop(stk, &current);
    }
} // FIXME fix output (the last ",")


char * AllocMemAndScanfString (void)
{
    char * string = (char *) calloc (SIZE_OF_STRING, sizeof(char));
    assert(string); // FIXME

    scanf("%s", string);
    return string;
}
