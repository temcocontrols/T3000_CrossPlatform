//  atof

/* main parser file for little C interpreter */
/* starts on page 19 */
//#include "setjmp.h"
//#include <math.h>
//#include "ctype.h"
//#include <stdlib.h>
//#include <string.h>
//#include "stdio.h"
#include <windows.h>
#include "baseclas.h"
#include "gedit.h"
#include "parser.h"

#define NUM_FUNC 				100
#define NUM_GLOBAL_VARS 100
#define NUM_LOCAL_VARS 	100
#define ID_LEN					31
#define FUNC_CALLS			31
#define FOR_NEST				31

#define TRUE 1
#define Srt '\`'

extern float ttime ;
extern unsigned long ttimed ;
extern char *prog ;
extern char *p_buf;
//extern jmp_buf e_buf ;
extern char eoi;
extern char eol;
//extern FILE *pmes;
extern int error;
extern char *pmes;
extern unsigned line_value;
extern long long_line_value;
extern struct var_type {
 char var_name[32] ;
 enum variable_type var_type ;
 int value ;
 } global_vars[NUM_GLOBAL_VARS] ;

extern struct func_type {
	char func_name[32] ;
	char *loc;
} func_stack[NUM_FUNC] ;

extern struct commands {
 char command[15] ;
 char tok ;
} table[] ;

extern struct func_table {
 char func_name[15] ;
 char tok ;
} func_table[] ;

/* This array is used by eval_exp1() */
char relops[8] = { LT , LE , GT , GE, EQ , NE , 0 } ;
char logops[7] = { AND , OR , XOR, 0 } ;

extern char token[80]  ;
extern char token_type  ;
extern char tok ;
extern GEdit *pedit;

extern int ret_value ;

void atom( float *value ) ;
void eval_exp0(float *value	) ;
void sntx_err(int err, int err_true = TRUE );
void putback( void ) ;
void assign_var( char *var_name , int value ) ;
int isdelim( char c) ;
int look_up(char *s ) ;
int look_up_func( char *s );
int iswhite( char c) ;
int find_var(char *s) ;
int get_token(void) ;
int internal_func(char *s ) ;
int is_var(char *s ) ;
char find_func(char *name) ;
void call(void) ;
void print_vars(void) ;
void get_nl(void);

/* print out the vars for inspection */

void print_vars(void)
{
/* fprintf(pmes, "*************Print out of variables************\n" ) ;
/* fprintf(pmes, "prog       :%s\n" , prog ) ; */

//fprintf(pmes, "  %3u | %3u  |%6s | %3c  |		 \n"
//	 , token_type,tok, token, *prog  	 ) ;

/* fprintf(pmes, "tok        :%c\n", tok) ;
fprintf(pmes, "token      :%s\n", token) ;
*/

} /* enmd of print_vars */



/* entry point into parser top of page 22 */
/*void eeval_exp( float *value )
{
	get_token() ;
	if (!*token){
	 sntx_err(NO_EXP) ;
	 return ;
	 }
	 if (*token==';') {
		 *value = 0 ;
		 return ;
	 }
	 eval_exp0(value);
	 putback() ;
}
*/
/* Process an assignment expression */
/*void eval_exp0(float *value)
{
	char temp[ID_LEN] ;
	register int temp_tok ;

	if( token_type==IDENTIFIER) {
		if( is_var(token) ) {
			strcpy(temp , token ) ;
			temp_tok = token_type ;
			get_token() ;
			if (*token=='=' ){
				get_token() ;
				eval_exp0(value) ;
				assign_var(temp , *value) ;
				return ;
			}
			else {
				putback() ;
				strcpy( token , temp ) ;
				token_type = temp_tok ;
			}
		}
	}
	eval_exp1(value) ;
}

*/



/* Process relational operators */
/*void eval_exp1( float *value )
{
	float partial_value ;
	register char op ;

	eval_exp2(value) ;
	op = *token;
	if( strchr(relops, op ) && op!=0) {
		get_token() ;
		eval_exp2(&partial_value) ;
		switch(op) {
			case LT :
				*value = *value < partial_value ;
				break ;
			case LE :
				*value = *value <= partial_value ;
				break ;
			case GT :
				*value = *value > partial_value ;
				break ;
			case GE :
				*value = *value >= partial_value ;
				break ;
			case EQ :
				*value = *value == partial_value ;
				break ;
			case NE :
				*value = *value != partial_value ;
				break ;
	}
}
}
*/


/* Process addition or subtraction */
/*
void eval_exp2( float *value )
{
	float partial_value ;
	register char op ;

	eval_exp3(value) ;
	while((op = *token ) == '+' || op == '-') {
		get_token() ;
		eval_exp3(&partial_value) ;
		switch(op)  {
			case '-' :
				*value = *value - partial_value ;
				break ;
			case '+' :
				*value = *value + partial_value ;
				break ;

		}
	}
}
*/

/* Process multiplication or division  */
/*void eval_exp3( float *value )
{
	float partial_value ;
	register char op ;

	eval_exp4(value) ;
	while((op = *token ) == '*' || op == '/') {
		get_token() ;
		eval_exp4(&partial_value) ;
		switch(op) {
			case '*' :
				*value = *value * partial_value ;
				break ;
			case '/' :
				*value = (*value) / partial_value ;
				break ;

		}
	}
}
*/



/* Process unary operations ie ++ and --  Page 25 */
/*
void eval_exp4( float *value )
{
	register char op ;
	op = '\0' ;

	if (*token == '+' || *token == '-') {
		op = *token ;
		get_token() ;
		}
	 eval_exp5(value) ;
	 if(op)
			if(op=='-') *value = -(*value) ;
}
*/



/* Process unparenthesized expression  */
/*void eval_exp5( float *value )
{
if ((*token == '(' )) {
 get_token() ;
 eval_exp0(value) ;
 if (*token != ')') sntx_err(PAREN_EXPECTED) ;
 get_token() ;
 }
 else
	atom(value) ;
}
*/

/* Find the value of a number, variable or function */
/*
void atom( float  *value )
{
	int i ;
	switch( token_type) {
	case IDENTIFIER :
		i = internal_func(token) ;
		if( i != -1 ) {
		 *value = (*intern_func[i].p)() ;
		}
		else
		if (find_func(token)){
			call() ;
			*value = ret_value ;
		}
		else *value = find_var(token) ;
		get_token() ;
		if (token_type==NL)
				if (eol==NL) {--prog;--prog;}
				else --prog;
		return ;

	case NUMBER:
		*value = (float)atof(token) ;
		get_token() ;
			if (token_type==NL)
				if (eol==NL) {--prog;--prog;}
				else --prog;
		return ;
	case DELIMITER :
		if(*token=='\'') {
			*value = *prog ;
			prog++ ;
			if(*prog != '\'') sntx_err(QUOTE_EXPECTED) ;
			prog++       ;
			get_token() ;
		}
		return ;
	default :
	 if (*token==')') return;
	 else sntx_err(SYNTAX) ;
	}
}
*/

/* Display an error message pg 26 */
void sntx_err(int err, int err_true )
{
	char *p , *temp ;
	int linecount = 0 ;
	register int i ;
	static char *e[] = {
	 "syntax error" ,
	 "unbalanced parentheses" ,
	 "no expression present" ,
	 "equals sign expected" ,
	 "not a variable" ,
	 "parameter error" ,
	 "semicolon expected" ,
	 "unbalanced braces" ,
	 "function undefined" ,
	 "type specifier expected" ,
	 "too many nested function calls" ,
	 "return without call" ,
	 "parentheses expected" ,
	 "while expected" ,
	 "closing quote expected" ,
	 "not a string" ,
	 "too many local variables",
	 "wrong or missing line number",
	 "point number out of range",
	 "line number too big",
	 "too many lines",
	 "number of points and variables exceeds 100",
	 "too many goto",
	 "warning: panel out of service",
	 "warning: point out of service"
	} ;
	if(!pmes) return;
	if(pmes < pedit->mesbuf + ( MES_SIZE - 100 ) )
	{
			strcpy(pmes,e[err]);
			pmes += strlen(pmes);
//			*pmes++ = 0x0d;
//	fprintf(pmes, "%s" , e[error] ) ;



//	p = p_buf ;
//	while ( p != prog) { /* find the line number */
//	 p++;
//	 if( *p == '\r' ) {
//		linecount++ ;
//		}
//	}
//	fprintf(pmes, " in line %d\n" , linecount) ;

	memcpy(pmes," in line ",9 );
	pmes += strlen(pmes);
	if(err == TOOBIG)
		ltoa(long_line_value,pmes,10);
	else
		itoa(line_value,pmes,10);
	pmes += strlen(pmes);
	if(err == NOT_VAR)
	{
	 strcpy(pmes," : ");
	 pmes += 3;
	 strcpy(pmes, token);
	 pmes += strlen(pmes);
	}
	*pmes++ = 0x0d;
	*pmes++ = 0x0a;
	error=err_true;
//	fprintf(pmes, " in line %d\n" , (int)line_value) ;

//	temp = p ;
//	for ( i = 0 ; i< 70 && p > p_buf && *p != '\n' ; i++ , p-- )
//	{
/* 		fprintf(pmes,"%i " , i );
		fprintf(pmes,"%c " , p );
*/
//	} ;
//	for( i = 0 ; i < 70 && p<=temp ; i++ , p++ ) {
//	fprintf(pmes,"%c" , *p );
//	}
//	longjmp( e_buf , 1 ); /* return to safe point */
 }
}


/* Get a token */

get_token(void)
{
	int i;
	float time1;
	char *temp ;
	token_type = 0 ; tok = 0 ;
	temp = token ;
	*temp = '\0' ;
	/* skip over white space */
/* 	fprintf(pmes, "*****GetToken****\n" ) ; */
	while( iswhite( *prog) && *prog) {
	++prog ;
/* 	fprintf(pmes, "Prog %c\n", *prog ) ; */
	}
		 /* this seems to push us beyond the end of the file */
		 if (eoi == NL)
		 {
		 if (*prog== 13  ) {            /* carriage return \r */
			++prog ;
		 if (*prog== 10  ) {            /* new line \n */
				++prog ;
				eol = NL;
				return (token_type=NL);
			}
			/* skip over white space */
		 while( iswhite( *prog) && *prog ){ ++prog ;}
		 }    /* while \r encountered */
		 }
		 else
			if (*prog == 13 || *prog == eoi ) {            /* carriage return \r */
				++prog ;
			eol=',';
			if (*prog== 10  )             /* new line \n */
				{
				 ++prog ;
				 eol=NL;
				}
			return (token_type=NL);
			}

/* 	if ( *prog=='\0') { /* end of the file */
		if ( *prog== 0  ) {      /* EOF doesn't work here */
		*token = '\0' ;
		tok = FINISHED ;
/* 		print_vars();  /* ( "End of file \n" ) ; */
		return ( token_type= DELIMITER ) ;
		}
	 if( strchr("{}" , *prog )) { /* block delimiters */
		*temp = *prog ;
		temp++;
		*temp = '\0' ;
		prog++ ;
/*		print_vars();  /*fprintf(pmes, "Block \n" ) ;*/
		return( token_type = BLOCKX ) ;
		}

		/* look for comments */
		if ( *prog=='/')
			if( *(prog+1) == '*') { /* we're in a comment */
			 prog += 2 ;
			 do { /* find the end of the comment */
					while (*prog!='*' && *prog) prog++;
					prog++ ;
			 } while ( *prog!='/' && *prog) ;
			prog++;
/*			print_vars();  /*		fprintf(pmes, "End of a comment \n" ) ; */
		}    /* end of comments */


	 if( strchr("!<>=" , *prog)) { /* is or might be a relation operator */
			switch (*prog) {
				case '=':
					prog++ ;
					*temp = EQ ;
					temp++ ;
					*temp = '\0' ;

				break ;
/*
				case '!': if (*(prog+1) =='=') {
						prog++ ; prog++ ;
						*temp = NE ;
						temp++ ; *temp = NE ; temp++;
						*temp = '\0' ;
					}
					break ;
*/
				case '<':
					if (*(prog+1) =='=') {
						prog += 2;
						*temp = LE ;
						temp++ ;
					}
					else
					{
					  if (*(prog+1) =='>')
					  {
						prog += 2;
						*temp = NE ;
						temp++ ;
					  }
					  else
					  {
						prog++ ;
						*temp = LT ;
					  }
					}
					temp++ ;
					temp = '\0' ;
					break ;

				case '>': if (*(prog+1) =='=') {
					prog += 2;
					*temp = GE ;
					temp++ ;
					}
					else {
					prog++ ;
					*temp = GT ;
					}
					temp++ ;
					temp = '\0' ;
					break ;
			} 		 /* end of the switch statement */
	 if (*token) {
/* 	 print_vars(); */
	 return( token_type = DELIMITER) ;
	 }
	 }        /* end of relaional statement check */

	 if ( strchr("+-*^/%=;()[]'," , *prog)){    /* delimiter*/
		*temp = *prog ;
		prog++ ;
		temp++ ;
		*temp = '\0' ;
/*		print_vars();  /*		fprintf(pmes, "DELIMITER \n" ) ; */
		return (token_type = DELIMITER ) ;
	 }

	 if ( *prog == '"') {    /* quoted string */
		prog++ ;
		while ( *prog!='"' && *prog != '\r' && *prog) *temp++ = *prog++ ;
		if (*prog=='\r') sntx_err(SYNTAX) ;
		prog++;
		*temp = '\0' ;
/*		print_vars();  /*		fprintf(pmes, "String \n" ) ; */
		return (token_type = STRING ) ;
	 }

	 if (isdigit(*prog) || (*prog=='.')) { /* a number */
			while( !isdelim(*prog)) *temp++ = *prog++ ;
			if (*prog==':')
				 {
					prog++;
					*temp = '\0';
					ttime = atof(token) * 100;
					ttimed = atol(token) * 3600;
					temp = token;
					*temp = '\0';
					while( !isdelim(*prog)) *temp++ = *prog++ ;
					*temp = '\0';
					time1 = atof(token) * 60;
					ttimed += atol(token) * 60;
					if (*prog==':')
						 {
							prog++;
							temp = token;
							*temp = '\0';
							while( !isdelim(*prog)) *temp++ = *prog++ ;
							*temp = '\0';
							time1 += atof(token);
							ttimed += atol(token);
						 }
				 ttime += time1 / 36;
				 return (token_type = TTIME );
				}
			if (*(prog-1)=='e' || *(prog-1)=='E')
			{
					*temp++ = *prog++ ;
					while( !isdelim(*prog)) *temp++ = *prog++ ;
					*temp = '\0' ;
					return (token_type = NUMBER );
			}
			if (*prog=='-')
				 {
					*temp++ = *prog++ ;
					while( !isdelim(*prog)) *temp++ = *prog++ ;
					token_type = TEMP ;
				 }
		 else
					{
					 *temp = '\0' ;
					 for(i=0;i<strlen(token);i++)
							if((token[i]<'0' || token[i]>'9') && (token[i]!='.' && token[i]!='E' && token[i]!='e'))
									break;
					 if (i==strlen(token))
							{
							/*		print_vars();  /*		fprintf(pmes, "NUMBER \n" ) ; */
							 return (token_type = NUMBER );
							}
					 else
							 token_type = TEMP ;
					}
	 }

	 if( isalpha(*prog)) { /* var or a command */
		while( !isdelim(*prog)) *temp++ = *prog++ ;
		 token_type = TEMP ;
	 }


		 *temp = '\0' ;

/* see if string is a command or a variable */
if( token_type == TEMP ) {
	tok = look_up(token) ; /* convert to internal representation */
	if( tok){ token_type = KEYWORD ;
/* 		fprintf(pmes, "KEYWORD \n" ) ; */
	}
	else{
	 token_type = IDENTIFIER ;
/* 	 fprintf(pmes, "IDENTIFIER \n" ) ; */
	}
}     /* end of is string a command a number or a variable */
{ /* print_vars(); */
return token_type ;
}

} 		 /* end of the get_token function  */




/* Return a token to the input stream */
void putback ( void )
{ char *t ;
 t = token ;
 for ( ; *t ; t++ )
 {
  prog-- ;
  if( *prog == Srt ) prog--;
 }
}

/* lookup atoken's internal representation in th etoken table */
int look_up( char *s )
{ register int i ;
char *p ;
 /* convert to lower case */
	p = s ;
//	 while (*p) { * p = toupper(*p) ; p++ ; }

	 /* see if token is in table */
	 for( i = 0 ; *table[i].command ; i++ )
		if (!strcmp(table[i].command , s)) return table[i].tok;
	 return 0 ; /* unkown command */
}


int look_up_func( char *s )
{ register int i ;
char *p ;
 /* convert to lower case */
	p = s ;
//	 while (*p) { * p = toupper(*p) ; p++ ; }

	 /* see if token is in table */
	 for( i = 0 ; *func_table[i].func_name ; i++ )
		if (!strcmp(func_table[i].func_name , s)) return func_table[i].tok;
	 return 0 ; /* unkown command */
}

/* return index of internal library function or -1 if not found */
/*
internal_func(char *s)
{ int i ;
 for (i = 0 ; intern_func[i].f_name[0] ; i++ ) { ;
	if (!strcmp(intern_func[i].f_name , s )) return i ;

	}
	return -1 ;
}
*/
/* return true if c is a delimiter */
isdelim(char c)
//{ if (strchr( " :!;,+-<>'/*%^=()" , c) || c == 9 || c == '\r' || c == 0 )
//  if (strchr( " :!;,<>'*%^=()[]" , c) || c == 9 || c == '\r' || c == 0 )
{
	if(c==Srt)
	{
	prog++;
	c = *prog;
	}
	if (strchr( " :!;,<>'*^=()[]" , c) || c == 9 || c == '\r' || c == 0 )
			return 1;
	else
			return 0;
}

/* return true if c is a space or a tab*/
iswhite(char c)
{ if( c == ' ' || c == '\t' || c == Srt)
	{  /* fprintf(pmes, "White:%c", c ) ; */

		 return 1;}

	else
	{
	/* fprintf(pmes, "Not white:%c", c ) ; */
	return 0;}
}



void get_nl()
{
	while( (*prog!=13) && *prog)
		++prog ;
	token[0]='\0';
/*	if (*prog)
		{
		++prog;
		token_type = NL;
		}
	else
		{
		 token_type = DELIMITER;
		 tok = FINISHED;
		}
*/
}
