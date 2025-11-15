#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>

#include "Data.h"
#include "AddFunc.h"
#include "GetFunc.h"
#include "TreeFunc.h"

#define CALL_DUMP  OutputBuf(fp, pos, buffer, tree); \
                   if (node->left && node->right) \
                   {GraphDump(tree, node, NoArg, __FUNCTION__, __FILE__, __LINE__, NULL, NULL, SUCCESS);} \
                   else \
                   fprintf (fp, "Node 0x%p { data = \"%s\", left = 0x%p, right = 0x%p } -- graph dump skipped\n", \
                   node, node->data, node->left, node->right);

#define ERROR_IN_TREE_CODE(fp, sym)  fprintf(fp, "<font color = red> ERROR in tree code: POS = [%c]\n <font color = black>", sym)

/*Inside functions for AddNode*/

const int LENGTH_OF_NIL = 3;

Node_t * MakeNewNode (char * data, Node_t * parent, OldOrNew age)
{
    assert(data);
    assert(parent);

    Node_t * node = (Node_t *) calloc (1, sizeof(Node_t));
    assert(node); // FIXME

    node->data   = data;
    node->parent = parent;
    node->right  = NULL;
    node->left   = NULL;
    node->age    = age;

    return node;
}


Node_t * RewriteParentNode (Node_t * node, char * data, Node_t * left, Node_t * right)
{
    assert(node);
    assert(data);
    assert(left);
    assert(right);

    node->data = data;
    node->left = left;
    node->right = right;
    node->age = New;

    return node;
}


char * ReadTreeFromFile (Tree_t * tree, FILE * log)
{
    assert(tree);
    assert(log);

    tree->log = log;
    tree->size = 0;

    int size_of_buffer = 0;
    char * buffer = ReadFileToBuffer(&size_of_buffer);
    char * pos = buffer;
    fprintf(log, "<strong> ");
    tree->root = ReadNode(tree, &pos, buffer, size_of_buffer);
    fprintf(log, "</strong> ");

    SetParent(tree->root);
    return buffer;
}


void SetParent (Node_t * current)
{
    assert(current);

    if (current->left)
    {
        (current->left)->parent = current;
        SetParent(current->left);
    }
    if (current->right)
    {
        (current->right)->parent = current;
        SetParent(current->right);
    }
}


void OutputBuf (FILE * fp, char ** pos, char  * buffer, Tree_t * tree)
{
    assert(fp);
    assert(pos);
    assert(*pos);
    assert(buffer);
    assert(tree);

    fprintf(fp, "<font color=red> &lt");
    MyFwrite(fp, *pos);
    fprintf(fp, "&gt <font color=black> <br> <br> \n");
}


void MyFwrite (FILE * fp, char * pos)
{
    assert(fp);
    assert(pos);

    while(*pos != '\0')
    {
        switch(*pos)
        {
            case '\0': fputc('\\', fp); fputc('0', fp);  break;
            case '\n': fputc('\\', fp); fputc('n', fp);  break;
            case '\t': fputc('\\', fp); fputc('t', fp);  break;
            case '\b': fputc('\\', fp); fputc('b', fp);  break;
            case '\r': fputc('\\', fp); fputc('r', fp);  break;
            case '\a': fputc('\\', fp); fputc('a', fp);  break;
            case '\\': fputc('\\', fp); fputc('\\', fp); break;
            case '\?': fputc('\\', fp); fputc('?', fp);  break;
            default:   fputc(*pos, fp);
        };
        pos++;
    }
}

Node_t * ReadNode (Tree_t * tree, char ** pos, char * buffer, int size_of_buffer)
{
    assert(tree);
    assert(pos);
    assert(*pos);
    assert(buffer);

    FILE * fp = GetLog(tree);
    assert(fp);
    SkipSpaces(pos);

    if (!ReadOpenBrace(**pos))
    {
        if (!ReadNil(pos))
            ERROR_IN_TREE_CODE(fp, **pos);
        return NULL;
    }

    IncrementTreeNodeCount(tree);
    Node_t * node = AllocateNodeMemory();
    if (!node)
        return NULL;

    MoveToFirstLetter(pos);
    ReadNodeName(node, pos);
    CALL_DUMP;
    node->left = ReadNode(tree, pos, buffer, size_of_buffer);
    CALL_DUMP;
    node->right = ReadNode(tree, pos, buffer, size_of_buffer);
    CALL_DUMP;

    SetNodeAge(node);
    SkipSpaces(pos);

    if (!ReadCloseBrace(**pos))
    {
        printf("Syntax error: no close brace found");
        return NULL;
    }
    (*pos)++; // move from close brace

    return node;
}


void SetNodeAge (Node_t * node)
{
    assert(node);

    node->age = Old;
}


void MoveToFirstLetter (char ** pos)
{
    assert(pos);

    (*pos)++; // move forward from '('
    SkipSpaces(pos);
    (*pos)++; // skip '\"'
}


void IncrementTreeNodeCount (Tree_t * tree)
{
    assert(tree);

    tree->size++;
}


Node_t * AllocateNodeMemory (void)
{
    Node_t * node = (Node_t *) calloc (1, sizeof(Node_t));

    return node;
}

bool ReadNil (char ** pos)
{
    assert(pos);
    assert(*pos);

    if (**pos == 'n')
    {
        *pos += LENGTH_OF_NIL;
        SkipSpaces(pos);
        return true;
    }

    return false;
}


bool ReadCloseBrace (char sym)
{
    if (sym == ')')
        return true;
    return false;
}


bool ReadOpenBrace (char sym)
{
    if (sym == '(')
        return true;
    return false;
}


void SkipSpaces (char ** pos)
{
    assert(pos);
    assert(*pos);

    while (isspace(**pos) != 0)
        (*pos)++;
}


void ReadNodeName (Node_t * node, char ** pos)
{
    assert(node);
    assert(pos);
    assert(*pos);

    node->data = *pos;
    while (**pos != '\"')
        (*pos)++;

    **pos = '\0';
    (*pos)++; // move from '\0'
}


char * ReadFileToBuffer (int * size_of_buffer)
{
    assert(size_of_buffer);

    FILE * fp = fopen("output.txt", "r");
    *size_of_buffer = GetFileSize("output.txt");
    char * buffer = (char *) calloc ((size_t)(*size_of_buffer) + 1, sizeof(char));
    assert(buffer);
    fread(buffer, sizeof(char), (size_t)(*size_of_buffer), fp);
    fclose(fp);

    return buffer;
}


void ReworkBuffer (char * buffer)
{
    assert(buffer);

    char * pos = buffer;
    int count = 0;

    while (pos != NULL)
    {
        pos = strchr(buffer, '\"');
        if (pos == NULL)
            break;
        count++;
        if (count % 2 == 0)
            *pos = '\0';
        pos++;
        buffer = pos;
    }
}


int GetFileSize (const char * filename)
{
    assert(filename);

    struct stat st;
    stat(filename, &st);

    return (int)st.st_size;
}
