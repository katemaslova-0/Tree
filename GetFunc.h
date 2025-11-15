#ifndef GET_H
#define GET_H

/*Get functions*/
const char * GetPlace (Place_t place);
char * GetCommand     (char * pic_name);
FILE * GetLog         (Tree_t * tree);
char * GetPicName     (void);
int GetNumOfCommand   (void);
bool GetAnswer        (void);

void TellThatAnswerIsIncorrect (void);
void AskCommandNumber          (void);

#endif // GET_H
