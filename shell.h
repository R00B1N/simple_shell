#ifndef CHELLY
#define CHELLY

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/stat.h>
#include <signal.h>
#include <errno.h>

extern char **environ;

/* These are inside stringS. */
char *_strdupS(char *str);
char *str_concatS(char *s1, char *s2);
int _strlenS(char *s);
int _strcmpS(char *s1, char *s2);
char *_strchrS(char *s, char c);

/* These are inside utilitiesS.c */
int dotChecker(char *buffer, int getty, int valChecker,
char **argv, int counter, unsigned int *statusOut);
void commandExec(int getty, char *buffer, char **arr, char **argv, int found,
int counter, unsigned int *statusOut);
int customCmmExec(int getty, char *buffer, char **arr, int chkVal, int counter,
char **argv, unsigned int *statusOut);
void execExit(char *buffer, char **arr, int counter, char **argv,
unsigned int *statusOut);
void execEnv(void);

/* These are inside utilitiesS1.c */
int _atoiS(char *s);
void checkPATH(char **arr, struct stat *buf);
char *_getenv(const char *name);
char **pathonizer(char *buf);
int valChecker(char *buffer, int getty);

/* These are inside utilitiesS2.c */
void WilliamWallace(char **liberty);
char *Commentator(int getty, char *buffer);
char *intToStr(unsigned long int num);
void rev_string(char *s);
void writeErrPerm(char *name, char *comm, int counter);

/* These are inside utilitiesS3.c */
void echoinator(char **arr, unsigned int *statusOut);
void decomposer(char **decompositron, unsigned int position);
void variableinator(char **arr, unsigned int *statusOut,
int counter, char **argv);
void writeCompoundError(char *name, char *command0,
char *command1, int counter);
int slsChecker(char *buffer, int getty, int valChecker,
char **argv, int counter, unsigned int *statusOut);

/* THese are inside envhanderl.c */
void initializer(void);
int _setenv(char *key, char *value, int overwrite);
int _unsetenv(char *key);
void Auxenv(char **arr, unsigned int *statusOut);
void Auxunenv(char **arr, unsigned int *statusOut);

/* These are in changedir.c */
int cdCustomCmmd(int found, char *buffer, char **arr,
char **argv, unsigned int *statusOut, int counter);
void execCd(char **arr, int counter, char **argv,
unsigned int *statusOut, int chRet);
void writeCdError(char **arr, int counter, char **argv);
void writeOptErr(char **arr, int counter, char **argv);
void execCdPrev(char **arr, int counter, char **argv, unsigned int *statusOut);

/* These are in minishell.c */
char **command(char *buf);
void writedol(void);
void writeErr(char *name, char *comm, int counter);
void ctrlC(int signal __attribute__((unused)));

#endif /* of CHELLY */
