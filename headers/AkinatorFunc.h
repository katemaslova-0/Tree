#ifndef AKINATOR_H
#define AKINATOR_H

/*Akinator functions*/
Err_t GuessTheObject (Tree_t * tree);
Err_t DefineObject   (Tree_t * tree);
Err_t CompareObjects (Tree_t * tree);

/*Strings output*/
void AskWhatToDefine       (void);
void AskToTryAgain         (void);
void AskNameOfTheFirstObj  (void);
void AskNameOfTheSecondObj (void);
void AskIfContinue         (void);

#endif // AKINATOR_H
