#ifndef TREE_H
#define TREE_H

/*Ctor, Dtor, Verify, Dump*/
Err_t TreeCtor   (Tree_t * tree, FILE * log);
Err_t NodeVerify (Node_t * node, Tree_t * tree, int count);
Err_t GraphDump  (Tree_t * tree, Node_t * node, Place_t place, const char * func_name, const char * file_name, int num_of_line, Node_t * addr, char * value, int result);
void  NodeDtor   (Node_t * node);

/*Node functions*/
void SetRoot     (Tree_t * tree, char * string);
Err_t AddNode    (Tree_t * tree, Node_t * current_node);
void OutputNode  (FILE * fp, Node_t * node);
void PrintNode   (const Node_t * node, FILE * fp);

#endif // TREE_H
