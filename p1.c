#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#define LPP 94
#define MAXL 132
#define INDENT 0
#define HALF LPP

void
	clearBuffers(void),
	printBuffers(int),
	usage(char *);
unsigned short
	fillBuffers(void);
char
	*indent(int);
int
	print(char *);	
long
	lineNumber = 0;
int
	tof = 1,
	c,
	t,
	numbering = 0,
	col = 0,
	tabint = 8,
	filesPrinted = 0;
FILE
	*text,
	*lpt1 = NULL;
char
	line[LPP][MAXL+INDENT+1];

/*컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴

									main
									
컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴*/

void main(int argc, char *argv[])
{
	short int c;
	for (c = 1; c < argc; ++c)
		if (*argv[c] == '/')
			if (isdigit(*(argv[c]+1)))
			{
				sscanf(argv[c]+1,"%d",&t);
				if (t > 0)
					tabint = t;
			}
			else
			{
				if (tolower(*(argv[c]+1)) == 'n')
					numbering = !numbering;
				else
					if (tolower(*(argv[c]+1)) == 'h')
					{
						usage(argv[0]);
						exit(1);
					}
			}
		else
			filesPrinted += print(argv[c]);

	if (filesPrinted == 0)
	{
		usage(argv[0]);
		exit(1);
	}
	exit(0);
}

/*컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴

									usage
									
컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴*/

void usage(char *program)
{
	char
		drive[_MAX_DRIVE],
		dir[_MAX_DIR],
		fname[_MAX_FNAME],
		ext[_MAX_EXT];
	_splitpath(program,drive,dir,fname,ext);
	printf("\nUsage:\n\t%s [/n] [/t] FileName\n\n", fname);
	printf("where FileName is the name of the input file (wild cards allowed)\n");
	printf("and the [optional] /n toggles line numbering (default=OFF).\n");
	printf("The t in the [optional] /t represents the tab expansion interval.  If\n");
	printf("not specified then it defaults to 8.\n\n");
	printf("More than one file name may be specified and line numbering may be\n");
	printf("toggled and the tab interval changed several times.  For example:\n");
	printf("\n\t%s dd.man /n font.txt /4 *.c *.h /8 /n *.doc\n\n",program);
	printf("prints DD.MAN without line numbers and with 8-column tabs then prints\n");
	printf("FONT.TXT with line numbers, then sets tab spacing to 4 before printing\n");
	printf("all the .C and .H files (with line numbers) and finally prints all the\n");
	printf(".DOC files after resetting tab spacing to 8 and turning off line numbers.");
}

/*컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴

									 print

컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴*/

int print(char *fileName)
{
	short int
		n;
	if ((text=fopen(fileName,"r")) == NULL)
	{
		printf("Could not open input file %s\n",strupr(fileName));
		return 0;
	}
	fseek(text,0L,SEEK_END);
	if (ftell(text) == 0)
	{
		fclose(text);
		printf("Zero-length file %s not printed\n",fileName);
		return 1;
	}
	rewind(text);
	if (lpt1 == NULL)
	{
		lpt1 = fopen("LPT1","w");
//					9 lpi		7 point  16.6 cpi  fixed lp type
		fputs("\033\&l5.3333C\033(s7V\033(s16.6H\033(s0P\033(s0T",lpt1);
	}
	while (!feof(text))
	{
		clearBuffers();
		if (n=fillBuffers())
			printBuffers(n);
	}
	fclose(text);
	return 1;
}

/*컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴

								clearBuffers

컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴*/

void clearBuffers(void)
{
	unsigned short int
		x = LPP;
	while (x--)
		line[x][0] = '\0';
}

/*컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴

								fillBuffers

컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴*/

unsigned short fillBuffers(void)
{
	unsigned short int
		lines = 0,
		filling = 1;
	char
		*p;

	p = indent(0);
	while (filling)
		switch(c=fgetc(text))
		{
case EOF:
case 014:
			*p = '\0';
			filling = 0;
			break;
case '\n':
			*p = '\0';
			col = 0;
			if (++lines >= LPP)
				filling = 0;
			else
				p = indent(lines);
			break;
case '\t':
			for (t=col/tabint*tabint+tabint; col < t; ++col)
				if (col < MAXL)
					*p++ = ' ';
			break;
case 0xCD:
			c = '=';
			goto others;
case 0xC4:
			c = '-';
default:
others:
			if (col++ < MAXL)
				*p++ = (char)c;
		}
	return lines;
}

/*컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴

									indent

컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴*/

char *indent(int l)
{
	memset(&line[l][0],' ',INDENT);
	if (numbering)
	{
		if (INDENT < 8)
		{
			sprintf(&line[l][0],"%5ld: ",++lineNumber % 100000L);
			return &line[l][strlen(line[l])];
		}
		else
			sprintf(&line[l][INDENT-7],"%5ld: ",++lineNumber % 100000L);
	}
	return &line[l][INDENT];
}

/*컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴

								printBuffers

컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴*/

void printBuffers(int lines)
{
	int l;
	if (lines)
	{
		if (!tof)
		{
			fputc(014,lpt1);
			tof = 1;
		}
		fputs("\n",lpt1);
		for (l=0; l < lines; ++l)
		{
			fputs(line[l],lpt1);
			fputc('\n',lpt1);
		}
	}
	tof = 0;
}
