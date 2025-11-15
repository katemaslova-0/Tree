#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "Data.h"
#include "TreeFunc.h"
#include "AkinatorFunc.h"
#include "AddFunc.h"
#include "GetFunc.h"
#include "DumpFunc.h"
#include "LogFunc.h"

#define OUTPUT_ERROR_AND_FINISH(res) {OutputErrorCode(res); return -1;}

int main (void)
{
    Tree_t tree = {};

    Err_t res = NoError;
    FILE * log = fopen("akinator.htm", "w");

    if (!log)
    {
        OutputErrorCode(FileOpeningError);
        return -1;
    }

    OutputLogTitle(log);

    char * buffer = ReadTreeFromFile(&tree, log);
    GraphDump(&tree, NULL, NoArg, __FUNCTION__, __FILE__, __LINE__, NULL, NULL, SUCCESS);

    int num = GetNumOfCommand();
    switch(num)
    {
        case Guess:
                    if ((res = GuessTheObject(&tree)) != NoError)
                        OUTPUT_ERROR_AND_FINISH(res);
                    break;
        case Define:
                    if ((res = DefineObject(&tree))   != NoError)
                        OUTPUT_ERROR_AND_FINISH(res);
                    break;
        case Compare:
                    if ((res = CompareObjects(&tree)) != NoError)
                        OUTPUT_ERROR_AND_FINISH(res);
                    break;
        default:      printf("Incorrect command number.\n");
    };

    fclose(log);
    free(buffer);
    NodeDtor(tree.root);

    return 0;
}
