#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#define	BLKSIZE	4096
#define	NBLK	2047
#define	FNSIZE	128
#define	LBSIZE	4096
#define	ESIZE	256
#define	GBSIZE	256
#define	NBRA	5
#define	KSIZE	9
#define	CBRA	1
#define	CCHR	2
#define	CDOT	4
#define	CCL	    6
#define	NCCL	8
#define	CDOL	10
#define	CEOF	11
#define	CKET	12
#define	CBACK	14
#define	CCIRC	15
#define	STAR	01
#define	READ	0
#define	WRITE	1
#define	SIGHUP	1
#define	SIGQUIT	3
int multiple_files = 0, argv_counter = 0, file_arr_size = 1, peekc, lastc, given, io, pflag,
    vflag = 1, oflag, listf, listn, tfile = -1, tline, iblock = -1, oblock    = -1, ichanged, nleft, names[26], anymarks, nbra, subnewa, fchange, wrapp;
long count, ninbuf;
char Q[] = "", T[] = "TMP", *regex, *file_name, *files[100], savedfile[FNSIZE], file[FNSIZE], linebuf[LBSIZE], expbuf[ESIZE+4], genbuf[LBSIZE], *nextip, *linebp, *globp, *tfname, *loc1, *loc2, ibuff[BLKSIZE], obuff[BLKSIZE], *braslist[NBRA], *braelist[NBRA],tmpXXXXX[50] = "/tmp/eXXXXX";
unsigned long regex_len = 0;
unsigned int	*addr1, *addr2, *dot, *dol, *zero;
unsigned nlall = 128;
void    newline(void);
void    error(char *s);
void    cerror(char buf[], int* num);
char*   modifyRegex(char* s);
int     getchr(void);
void    global(int k);
void    setwide(void);
void    squeeze(int i);
void    print(void);
char    *getline_(unsigned int tl);
char    *getblock(unsigned int atl, int iof);
void    nonzero(void);
void    putd(void);
void    compile(int eof);
void    init(void);
void    exfile(void);
void    commands(void);
int     append(int (*f)(void), unsigned int *a);
int     putline(void);
unsigned int *address(void);
void    filename(int comm);
void    quit(int n);
int     getfile(void);
int     execute(unsigned int *addr);
int     advance(char *lp, char *ep);
int     cclass(char *set, int c, int af);
int     backref(int i, char *lp);
