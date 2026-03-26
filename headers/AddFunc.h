#ifndef ADD_H
#define ADD_H

/*Inside Add functions*/
Node_t * MakeNewNode       (char * data, Node_t * parent, OldOrNew age);
Node_t * RewriteParentNode (Node_t * node, char * data, Node_t * left, Node_t * right);

Node_t * ReadNode          (Tree_t * tree, char ** pos, char * buffer, int size_of_buffer);
void SkipSpaces            (char ** pos);
void ReadNodeName          (Node_t * node, char ** pos);
char * ReadFileToBuffer    (int * size_of_buffer);
void ReworkBuffer          (char * buffer);
int GetFileSize            (const char * filename);
char * ReadTreeFromFile    (Tree_t * tree, FILE * log);
void SetParent             (Node_t * current);
void ReadNodeNameV2        (Node_t * node, char ** pos);
void OutputBuf             (FILE * fp, char ** pos, char  * buffer, Tree_t * tree);
void MyFwrite              (FILE * fp, char * pos);


bool ReadOpenBrace          (char sym);
bool ReadCloseBrace         (char sym);
bool ReadNil                (char ** pos);
Node_t * AllocateNodeMemory (void);
void IncrementTreeNodeCount (Tree_t * tree);
void MoveToFirstLetter      (char ** pos);
void SetNodeAge             (Node_t * node);

#endif // ADD_H
