//
//  grep.h
//  Project 1.1
//
//  Created by William Covington on 3/19/19.
//  Copyright © 2019 William Covington. All rights reserved.
//

#ifndef grep_h
#define grep_h

#include <signal.h>
#include <setjmp.h>
#include <regex.h>
#include <string.h> //remove this and include strcpy function

#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

#define    BLKSIZE    4096
#define    NBLK    2047

#define    FNSIZE    128
#define    LBSIZE    4096
#define    ESIZE    256
#define    GBSIZE    256
#define    READ    0
#define    WRITE    1


char    Q[]    = "";
char    T[]    = "TMP";


int    peekc;
int    lastc;
char    savedfile[FNSIZE];
char    file[FNSIZE];
char    linebuf[LBSIZE];
char    rhsbuf[LBSIZE/2];
char    expbuf[ESIZE+4];
int    given;
unsigned int    *addr1, *addr2;
unsigned int    *dot, *dol, *zero;
char    genbuf[LBSIZE];
long    count;
char    *nextip;
char    *linebp;
int    ninbuf;
int    io;
int    pflag;
int    close(int);
int    fork(void);
int    wait(int *);

char *getblock(unsigned int atl, int iof);
char *getline_(unsigned int tl);
char *place(char *sp, char *l1, char *l2);
void add(int i);
int advance(char *lp, char *ep);
int append(int (*f)(void), unsigned int *a);
void error(char *s);
void exfile(void);
void filename(int comm);
int getchr(void);
int getcopy(void);
void getfile(int);
int getnum(void);
int getsub(void);
void global(int k);
void init(void);
unsigned int *address(void);
void newline(void);
void print(void);
void putchr(int ac);
void putd(void);
void putfile(void);
int putline(void);
void puts_(char *sp);
void quit(int n);
void setnoaddr(void);
void squeeze(int i);
void substitute(int inglob);


//these two are not in ansi, but we need them
#define    SIGHUP    1    //hangup
#define    SIGQUIT    3    // quit (ASCII FS)


#endif /* grep_h */
