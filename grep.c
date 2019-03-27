
#include "grep.h"

//DO NOT move_ THESE VARIABLES TO HEADER
int    fchange;
int    wrapp;
int    vflag    = 1;
int    listf;
int    listn;
char    *globp;
int    nleft;
int    oflag;
int    col;
int    tfile    = -1;
int    tline;
char    *tfname;
char    ibuff[BLKSIZE];
int    iblock    = -1;
char    obuff[BLKSIZE];
int    oblock    = -1;
int    ichanged;
int    names[26];
int    anymarks;
int    subnewa;

#define MAXFILES 10
int fileCount;
char* files[MAXFILES];
char* regexArg;
regex_t regex;
int reti;
char msgbuf[100];

int lineCount = 0;

char *line_buf = NULL;
int line_count;
FILE *fp;

int fileLineCount[MAXFILES] = {0};

char* savedLines[5000];
char* outputline;

size_t len;
size_t readin;


//Added functions, add these to grep.h
int main(int argc, char *argv[]) {
    argv++;

    //Saves regular expression
    //Assigns regex statement to string, increments argv
    regexArg = *argv;
    argv++;
    //printf("Regex: %s\n", regexArg);

    //Saves filenames to file array
    //Maximum 10 files
    while(*argv && fileCount < (MAXFILES - 1)){
        files[fileCount] = *argv;
        fileCount++;
        argv++;
    }
    
    
    init();

    
    quit(0);
    return 0;
}

void print(void) {
    //Search and print lines matching regex
    // Execute regular expression
    int counter = 0;
    int currentFile = 0;
    for(int i = 0; i<line_count; i++, counter++)
    {
        reti = regexec(&regex, savedLines[i], 0, NULL, 0);
        if (!reti) {    //If line contains regex
            //puts("Match");
            if(fileCount > 1){
                //Print filename with colon;
                
                if(counter >= fileLineCount[currentFile]){
                    counter = 0;
                    currentFile++;
                }
                printf("%s: %s\n",files[currentFile], savedLines[i]);
            
            }
            else{
            printf("%s\n", savedLines[i]);
            }
        }
        else if (reti == REG_NOMATCH) {
            //puts("No match");
        }
        else {
            regerror(reti, &regex, msgbuf, sizeof(msgbuf));
            fprintf(stderr, "Regex match failed: %s\n", msgbuf);
            exit(1);
        }
    }
    

}


int getnum(void) {
    int r, c;
    
    r = 0;
    while ((c=getchr())>='0' && c<='9')
        r = r*10 + c - '0';
    peekc = c;
    return (r);
}



void squeeze(int i) {
    if (addr1<zero+i || addr2>dol || addr1>addr2)
        error(Q);
}

void newline(void) {
    int c;
    
    if ((c = getchr()) == '\n' || c == EOF)
        return;
    if (c=='p' || c=='l' || c=='n') {
        pflag++;
        if (c=='l')
            listf++;
        else if (c=='n')
            listn++;
        if ((c=getchr())=='\n')
            return;
    }
    error(Q);
}

void filename(int comm) {
    char *p1, *p2;
    int c;
    
    count = 0;
    c = getchr();
    if (c=='\n' || c==EOF) {
        p1 = savedfile;
        if (*p1==0 && comm!='f')
            error(Q);
        p2 = file;
        while ((*p2++ = *p1++))
            ;
        return;
    }
    if (c!=' ')
        error(Q);
    while ((c = getchr()) == ' ')
        ;
    if (c=='\n')
        error(Q);
    p1 = file;
    do {
        if (p1 >= &file[sizeof(file)-1] || c==' ' || c==EOF)
            error(Q);
        *p1++ = c;
    } while ((c = getchr()) != '\n');
    *p1++ = 0;
    if (savedfile[0]==0 || comm=='e' || comm=='f') {
        p1 = savedfile;
        p2 = file;
        while ((*p1++ = *p2++))
            ;
    }
}



void error(char *s) {
    int c;
    
    wrapp = 0;
    listf = 0;
    listn = 0;
    putchr('?');
    puts_(s);
    count = 0;
    lseek(0, (long)0, 2);
    pflag = 0;
    if (globp)
        lastc = '\n';
    globp = 0;
    peekc = lastc;
    if(lastc)
        while ((c = getchr()) != '\n' && c != EOF)
            ;
    if (io > 0) {
        close(io);
        io = -1;
    }
}

int getchr(void) {
    char c;
    if ((lastc=peekc)) {
        peekc = 0;
        return(lastc);
    }
    if (globp) {
        if ((lastc = *globp++) != 0)
            return(lastc);
        globp = 0;
        return(EOF);
    }
    if (read(0, &c, 1) <= 0)
        return(lastc = EOF);
    lastc = c&0177;
    return(lastc);
}

void getfile(int filenum) {
    //Load the files
    // Open the file for reading
    fp = fopen(files[filenum], "r");
    if (!fp)
    {
        fprintf(stderr, "Error opening file '%s'\n", files[0]);
    }
    else{
        while((readin = getline(&outputline, &len, fp)) != -1){
            savedLines[line_count] = malloc(readin);
            strcpy(savedLines[line_count], outputline);
            char* newlineCheck = savedLines[line_count];
            char newlinechar = newlineCheck[strlen(newlineCheck) - 1];
            if(newlinechar == '\n'){
                newlineCheck[strlen(newlineCheck) - 1] = '\0';
                savedLines[line_count] = newlineCheck;
            }
            line_count++;
            fileLineCount[filenum]++;
        }
        free(outputline);
        outputline = NULL;
    }
    //Close the file now that we are done with it
    fclose(fp);
    
    
}

void add(int i) {
    if (i && (given || dol>zero)) {
        addr1--;
        addr2--;
    }
    squeeze(0);
    newline();
}



void quit(int n) {
    //Free memory allocated to the pattern buffer by regcomp()
    regfree(&regex);
    free(line_buf);

    if (vflag && fchange && dol!=zero) {
        fchange = 0;
        error(Q);
    }
    unlink(tfname);
    exit(0);
}


char *
getline_(unsigned int tl) {
    
    return(linebuf);
}

int putline(void) {
    char *bp, *lp;
    int nl;
    unsigned int tl;
    
    fchange = 1;
    lp = linebuf;
    tl = tline;
    bp = getblock(tl, WRITE);
    nl = nleft;
    tl &= ~((BLKSIZE/2)-1);
    while ((*bp = *lp++)) {
        if (*bp++ == '\n') {
            *--bp = 0;
            linebp = lp;
            break;
        }
        if (--nl == 0) {
            bp = getblock(tl+=(BLKSIZE/2), WRITE);
            nl = nleft;
        }
    }
    nl = tline;
    tline += (((lp-linebuf)+03)>>1)&077776;
    return(nl);
}

char *
getblock(unsigned int atl, int iof) {
    int bno, off;
    
    bno = (atl/(BLKSIZE/2));
    off = (atl<<1) & (BLKSIZE-1) & ~03;
    if (bno >= 0) {
        lastc = '\n';
        error(T);
    }
    nleft = BLKSIZE - off;
    if (bno==iblock) {
        ichanged |= iof;
        return(ibuff+off);
    }
    if (bno==oblock)
        return(obuff+off);
    if (iof==READ) {
        if (ichanged)
        ichanged = 0;
        iblock = bno;
        return(ibuff+off);
    }
    if (oblock>=0)
    oblock = bno;
    return(obuff+off);
}

void init(void) {
    line_count = 0;
    outputline = NULL;
    
    len = 0;
    // Compile regular expression
    reti = regcomp(&regex, regexArg, 0);
    if (reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }
    for(int i = 0; i < fileCount; i++){
        getfile(i);
    }
    //search and print results
    print();
}

void putd(void) {
    int r;
    
    r = count%10;
    count /= 10;
    if (count)
        putd();
    putchr(r + '0');
}

void puts_(char *sp) {
    col = 0;
    while (*sp)
        putchr(*sp++);
    putchr('\n');
}

char    line[70];
char    *linp    = line;

void putchr(int ac) {
    char *lp;
    int c;
    
    lp = linp;
    c = ac;
    if (listf) {
        if (c=='\n') {
            if (linp!=line && linp[-1]==' ') {
                *lp++ = '\\';
                *lp++ = 'n';
            }
        } else {
            if (col > (72-4-2)) {
                col = 8;
                *lp++ = '\\';
                *lp++ = '\n';
                *lp++ = '\t';
            }
            col++;
            if (c=='\b' || c=='\t' || c=='\\') {
                *lp++ = '\\';
                if (c=='\b')
                    c = 'b';
                else if (c=='\t')
                    c = 't';
                col++;
            } else if (c<' ' || c=='\177') {
                *lp++ = '\\';
                *lp++ =  (c>>6)    +'0';
                *lp++ = ((c>>3)&07)+'0';
                c     = ( c    &07)+'0';
                col += 3;
            }
        }
    }
    *lp++ = c;
    if(c == '\n' || lp >= &line[64]) {
        linp = line;
        write(oflag?2:1, line, lp-line);
        return;
    }
    linp = lp;
}

