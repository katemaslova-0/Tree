#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "Data.h"
#include "DumpFunc.h"
#include "AddFunc.h"
#include "TreeFunc.h"

/*Inside functions for Dump*/

Err_t MakeGraphCodeFile (Tree_t * tree, Node_t * node)
{
    assert(tree);

    FILE * fp = fopen("akinatordump.txt", "w");
    if (!fp)
        return FileOpeningError;

    fprintf(fp, "digraph G{\nrankdir=HR;\n");
    if (node != NULL)
        OutputNode(fp, node);
    else
        OutputNode(fp, tree->root);
    fprintf(fp, "}");

    fclose(fp);
    return NoError;
}


void OutputTitle (FILE * log, const char * place, const char * func_name, const char * file_name, int num_of_line, Node_t * addr, char * value, int result)
{
    assert(log);
    assert(place);
    assert(func_name);
    assert(file_name);
    //assert(value);

    if (strcmp(func_name, "TreeCtor") == 0)
        fprintf(log, "<pre>\n<h3> DUMP <font color=red>%s</font> %s", place, func_name);
    else
    {
        fprintf(log, "<pre>\n<h3> DUMP <font color=red>%s</font> %s %p", place, func_name, addr);
        fprintf(log, " (element = %s) ", value);
    }

    if (result == SUCCESS)
        fprintf(log, " <font color=green>(SUCCESS)<font color=black></h3>\n");
    else
        fprintf(log, " <font color=red>(ERROR)<font color=black></h3>\n");
    fprintf(log, "Verified at: %s:%d\n\n\n          ", file_name, num_of_line);
}


void OutputImage (FILE * log, char * pic_name)
{
    assert(log);
    assert(pic_name);

    fprintf(log, "\nIMAGE:\n\n <img src=%s width=800px>\n\n\n", pic_name);
}


void OutputErrorCode (Err_t error)
{
    switch (error)
    {
        case NoError:                                                break;
        case MemAllocError:     printf("Memory allocation error\n"); break;
        case MissingChild:      printf("Missing child\n");           break;
        case NullNodePointer:   printf("Null node pointer\n");       break;
        case TwoDads:           printf("Two dads\n");                break;
        case SimilarChildren:   printf("Similar children\n");        break;
        case RecursiveOverflow: printf("Recursive overflow\n");      break;
        case SystemError:       printf("System command failed\n");   break;
        case FileOpeningError:  printf("File opening error\n");      break;
        case WrongRightChild:   printf("Wrong right child\n");       break;
        case WrongLeftChild:    printf("Wrong left child\n");        break;
        default: ;
    }
}
