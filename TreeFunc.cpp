#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "Data.h"
#include "TreeFunc.h"
#include "DumpFunc.h"
#include "GetFunc.h"
#include "CompareAndDefine.h"
#include "AddFunc.h"

Err_t TreeCtor (Tree_t * tree, FILE * log)
{
    assert(tree);
    assert(log);

    tree->root = (Node_t *) calloc (1, sizeof(Node_t));
    if (!tree->root)
        return MemAllocError;

    char * string = (char *) calloc (SIZE_OF_STRING, sizeof(char));
    if (!string)
        return MemAllocError;

    sprintf(string, "Nothing");
    SetRoot(tree, string);

    tree->size = 1;
    tree->log = log;

    //TREE_VERIFY(tree, After, tree->root, (tree->root)->data);
    return NoError;
}


void SetRoot (Tree_t * tree, char * string)
{
    assert(tree);
    assert(string);
    assert(tree->root);

    (tree->root)->left   = NULL;
    (tree->root)->right  = NULL;
    (tree->root)->parent = NULL;
    (tree->root)->data   = string;
    (tree->root)->age    = New;
}


Err_t NodeVerify (Node_t * node, Tree_t * tree, int count = 0)
{
    assert(tree);

    Err_t error = NoError;

    if (count > tree->size)                              {error = RecursiveOverflow; return error;}
    if (node == NULL)                                    {error = NullNodePointer;   return error;}
    if (node->left == NULL && node->right != NULL)       {error = MissingChild;      return error;}
    if (node->left != NULL && node->right == NULL)       {error = MissingChild;      return error;}
    if (node == node->left || node == node->right)       {error = TwoDads;           return error;}
    if (node->right == node->left && node->left != NULL) {error = SimilarChildren;   return error;}
    if (node->right && (node->right)->parent != node)    {error = WrongRightChild;   return error;}
    if (node->left  && (node->left)->parent  != node)    {error = WrongLeftChild;    return error;}

    if (!node->left) NodeVerify(node->left, tree, ++count);
    if (!node->right) NodeVerify(node->right, tree, ++count);

    return error;
}


Err_t AddNode (Tree_t * tree, Node_t * current_node)
{
    assert(tree);
    assert(current_node);

    char * new_object = AllocMemAndScanfString();
    Node_t * left_node = MakeNewNode(new_object, current_node, New);
    TREE_VERIFY(tree, Before, left_node, left_node->data);
    Node_t * right_node = MakeNewNode(current_node->data, current_node, Old);

    printf("In what way %s is different from %s? It's...\n", new_object, current_node->data);
    char * new_question = AllocMemAndScanfString();

    RewriteParentNode(current_node, new_question, left_node, right_node);

    tree->size+=2;

    FILE * fp = fopen("output.txt", "w");
    PrintNode(tree->root, fp);
    fclose(fp);
    TREE_VERIFY(tree, After, left_node, left_node->data);
    return NoError;
}


void OutputNode (FILE * fp, Node_t * node)
{
    assert(fp);
    assert(node);

    fprintf(fp, "f%p [shape=Mrecord; style = filled; fillcolor = "light_pink"; ", node);
    fprintf(fp, "color = "dark_green"; label = \"{parent = %p | address = %p ", node->parent, node);
    fprintf(fp, "| %s ", node->data);
    fprintf(fp, "| {left = %p | right = %p}} \"]; \n", node->left, node->right);

    if (node->left)
    {
        OutputNode(fp, node->left);
        fprintf(fp, "f%p -> f%p [color = "dark_pink"];\n", node, node->left);
    }
    if (node->right)
    {
        OutputNode(fp, node->right);
        fprintf(fp, "f%p -> f%p [color = "dark_pink"];\n", node, node->right);
    }
}


void PrintNode (const Node_t * node, FILE * fp)
{
    assert(node);
    assert(fp);

    fprintf(fp, "( \"%s\" ", node->data);
    if (node->left)
        PrintNode(node->left, fp);
    else
        fprintf(fp, "%s ", "nil");
    if (node->right)
        PrintNode(node->right, fp);
    else
        fprintf(fp, "%s ", "nil");
    fprintf(fp, ")");
}


void NodeDtor (Node_t * node)
{
    assert(node);

    if (node->left)
        NodeDtor(node->left);
    if (node->right)
        NodeDtor(node->right);

    if (node->age == New)
        free(node->data); // FIXME

    free(node);
}


Err_t GraphDump (Tree_t * tree, Node_t * node, Place_t place, const char * func_name, const char * file_name, int num_of_line, Node_t * addr, char * value, int result)
{
    assert(tree);
    assert(func_name);
    assert(file_name);
    //assert(addr);
    //assert(value);

    MakeGraphCodeFile(tree, node);

    char * pic_name = GetPicName();
    char * command  = GetCommand(pic_name);
    const char * place_of_call = GetPlace(place);
    FILE * log = GetLog(tree);

    if (system(command) != 0)
        return SystemError;
    free(command);

    OutputTitle(log, place_of_call, func_name, file_name, num_of_line, addr, value, result);
    OutputImage(log, pic_name);

    free(pic_name);
    return NoError;
}



