#ifndef GUESS_H
#define GUESS_H

/*Inside functions for Guess*/
Node_t * AskUntilTheEnd (Node_t * current);
void AskFinalQuestion   (Node_t * current);
Err_t RequestNewObject  (Tree_t * tree, Node_t * current);

#endif // GUESS_H
