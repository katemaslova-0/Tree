#ifndef DATA_H
#define DATA_H

#define light_green "\"#C0FFC0\""
#define dark_green  "\"#008000\""
#define light_pink  "\"#ffc0f6ff\""
#define dark_pink   "\"#fa5d82ff\""
#define light_red   "\"#ff0000ff\""
#define dark_red    "\"#bd2222ff\""
#define white       "\"#ffffffff\""

const int SIZE_OF_STRING = 40;
const int STACK_SIZE = 10;

#define TREE_VERIFY(tree, place, addr, value) if (NodeVerify(tree->root, tree) != NoError) \
                                            {printf("TreeDump at %s:%d\n", __FILE__, __LINE__); \
                                            Err_t error = NodeVerify(tree->root, tree); \
                                            OutputErrorCode(error); \
                                            GraphDump(tree, NULL, place, __FUNCTION__, __FILE__, __LINE__, addr, value, ERROR); \
                                            return error;} \
                                            GraphDump(tree, NULL, place, __FUNCTION__, __FILE__, __LINE__, addr, value, SUCCESS);


enum OldOrNew
{
    Old = 0,
    New = 1
};

struct Node_t
{
    char * data;
    Node_t * left;
    Node_t * right;
    Node_t * parent;
    OldOrNew age;
};

struct Tree_t
{
    Node_t * root;
    int size;
    FILE * log;
};

enum Place_t
{
    NoArg  = 0,
    Before = 1,
    After  = 2
};

enum Dump_t
{
    SUCCESS = 0,
    ERROR   = 1
};

enum Command_t
{
    Guess   = 1,
    Define  = 2,
    Compare = 3
};

enum Err_t
{
    NoError           = 0,
    MemAllocError     = 1,
    MissingChild      = 2,
    NullNodePointer   = 3,
    TwoDads           = 4,
    SimilarChildren   = 5,
    RecursiveOverflow = 6,
    SystemError       = 7,
    FileOpeningError  = 8,
    WrongRightChild   = 9,
    WrongLeftChild    = 10
};

#endif // DATA_H
