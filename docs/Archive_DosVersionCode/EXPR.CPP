#include "setjmp.h"
#include "math.h"
#include "ctype.h"
#include "stdlib.h"
#include "string.h"
#include "stdio.h"
#include "t3000def.h"
#include "parser.h"

#define TRUE 1
#define FALSE 0


void parse_atom( float  *value );
void parse_exp5( float *value );
void parse_exp4( float *value );
void parse_exp3( float *value );
void parse_exp2( float *value );
void parse_exp1( float *value );
void parse_exp0( float *value );
void parse_exp( float *value );
extern void sntx_err(int err, int err_true = TRUE );
extern void putback( void ) ;
extern void assign_var( char *var_name , int value ) ;
extern int isdelim( char c) ;
extern int look_up(char *s ) ;
extern int look_up_func( char *s );
extern int iswhite( char c) ;
extern void eval_exp( float *value ) ;
extern void	get_nl(void);
extern int varoffsetlast(int cur);


/* entry point into parser top of page 22 */

extern struct variable_table *vars_table;

extern int DORU_SYSTEM;
extern float ttime ;
extern unsigned long ttimed ;

extern char *prog ;
extern char *p_buf;
extern jmp_buf e_buf ;
extern char eoi;
extern char eol;

extern char token[80]  ;
extern char token_type  ;
extern char tok ;
extern int n_var;
extern struct buf_str *buf_v;
extern int index_buf,index_op,type_eval;
extern float res;
extern int ret_value ;
extern char relops[8],logops[7] ;
extern int define_var(char *token, int t=FLOAT_TYPE,int l=0,int c=0, int lstr=LENGTHSTRING);
extern  get_token(void) ;
extern int error;

char address_item;

extern int isarray(char *tok);
extern int checklocalvar(char *tok);
extern int checkonlyarray(char *tok);

void parse_exp( float *value )
{
	get_token() ;
	if (!*token || *token==','){
	 sntx_err(NO_EXP) ;
	 return ;
	}
	parse_exp0(value);
	putback() ;
}

/* Process logical operators */
void parse_exp0( float *value )
{
	float partial_value ;
	register char op ;

	parse_exp1(value) ;
	op = tok;
	if( strchr(logops, op ) && op!=0) {
		get_token() ;
		parse_exp0(value) ;
		if(type_eval)
			buf_v[index_buf-1].op[index_op++]=op;
	}
} /* end of function eval_exp(1) */




/* Process relational operators */
void parse_exp1( float *value )
{
	float partial_value ;
	register char op ;

	parse_exp2(value) ;
	op = *token;
	if( strchr(relops, op ) && op!=0) {
		get_token() ;
		parse_exp2(value) ;
		if(type_eval)
			buf_v[index_buf-1].op[index_op++]=op;
	}
} /* end of function eval_exp(1) */



/* Process addition or subtraction */
void parse_exp2( float *value )
{
	float partial_value ;
	register char op ;

	parse_exp3(value) ;
	while((op = *token ) == '+' || op == '-') {
		get_token() ;
		parse_exp3(value) ;
		if(type_eval)
			buf_v[index_buf-1].op[index_op++]=op;
	}   /* while statement */
}     /* end of function */


/* Process multiplication or division  */
void parse_exp3( float *value )
{
	float partial_value ;
	register char op ;

	parse_exp4(value) ;
	while((op = *token ) == '*' || op == '/' || op == '%') {
		get_token() ;
		parse_exp4(value) ;
		if(type_eval)
			buf_v[index_buf-1].op[index_op++]=op;
	}
}     /* end of function */



/*

// Process unary operations ie ++ and --
void parse_exp4( float *value )
{
	register char op ;
	op = '\0' ;

	if ((*token == '+' || *token == '-') && token_type!=NL && tok!=FINISHED) {
		op = *token;
		get_token() ;
	} // if statement
	parse_exp5(value) ;
	if (op)
		 if(op=='-') *value = -(*value);
} // end of function

*/
/* Process power */
void parse_exp4( float *value )
{
	float partial_value ;
	register char op ;

	parse_exp5(value) ;
	while((op = *token ) == '^' ) {
		get_token() ;
		parse_exp5(value) ;
		if(type_eval)
			buf_v[index_buf-1].op[index_op++]=op;
	}
}     /* end of function */



/* Process unparenthesized expression  */
void parse_exp5( float *value )
{
 if ((*token == '(' )) {
	get_token() ;
	parse_exp0(value) ;
	if (*token != ')') sntx_err(PAREN_EXPECTED) ;
	get_token() ;
	if (token_type==NL)
	 if (eol==NL) {--prog;--prog;}
		else --prog;
 }
 else
	parse_atom(value) ;
}     /* end of function */


/* Find the value of a number, variable or function */
void parse_atom( float  *value )
{
	float res;
	int i,t ;
	int ftok;
	char pt[14];
	switch( token_type) {
	case IDENTIFIER :
	 if((ftok=look_up_func(token))==NOT)
	 {
		 get_token();
		 if ((*token == '(' ))
		 {
			 get_token() ;
			 parse_exp0(value) ;
			 if (*token != ')')
			 {
				sntx_err(PAREN_EXPECTED) ;
				error = TRUE;
				*value = FALSE ;
				get_nl();
				return;
			 }
			 get_token() ;
		 }
		 else
			parse_atom(value) ;
		 if (type_eval)
			 buf_v[index_buf-1].op[index_op++]=ftok;
		 return;
	 }
	 if(*prog=='(')
	 {
		 if((ftok=look_up_func(token))==0)
		 {
			memcpy(pt,token,13);
			if (!type_eval)
			{
//			 if((ftok=isarray(pt))==1 )
//			 {
//			  ftok=checklocalvar(pt);
//			 }
			 if( isarray(pt) )
//			 if(ftok)
			 {
				*value = TRUE ;
				get_token() ;
				if (token_type==NL)
				if (eol==NL) {--prog;--prog;}
				else --prog;
			 }
			 else
			 {
			  error = TRUE;
			  *value = FALSE ;
			  sntx_err(SYNTAX);
			  get_nl();
			 }
			}
			else
			{
/*				 ftok=checkarray(pt);
				 if( !vars_table[ftok-1].l )
				 {
					buf[index_buf].fvar = 1;
					strcpy(buf[index_buf].var,"");
					buf[index_buf].v=0;
					index_op=0;
					for(i=0;i<MAX_OP;i++)
						 buf[index_buf].op[i]=0;
					index_buf++;
					n_var++;
				 }
*/
				 prog++;
				 get_token();
				 parse_exp0(value) ;
				 if (*token==',')
				 {
				  get_token();
				  parse_exp0(value) ;
				  buf_v[index_buf-1].op[index_op++]=ASSIGNARRAY_2;
				 }
				 else
				  buf_v[index_buf-1].op[index_op++]=ASSIGNARRAY_1;
//
				 buf_v[index_buf].v=1;
				 index_op=0;
				 for(i=0;i<MAX_OP;i++)
					 buf_v[index_buf].op[i]=0;
				 memcpy(buf_v[index_buf].var,pt,13);
				 buf_v[index_buf].fvar=0;
				 if( address_item )
					buf_v[index_buf].op[index_op++]=ASSIGNARRAY;
				 index_buf++;
				 n_var++;
//
				 get_token() ;
					if (token_type==NL)
						if (eol==NL) {--prog;--prog;}
						else --prog;
			}
			return;
		 }
		 else
		 {
			 prog++ ;
			 get_token();
			 switch (ftok) {
				 case ABS:
				 case INT:
				 case LN:
				 case LN_1:
				 case SQR:
				 case Status:
				 case RUNTIME:
				 case SENSOR_ON:
				 case SENSOR_OFF:
								 parse_exp0(value) ;
								 if (*token != ')') {	error = TRUE; *value = FALSE ; sntx_err(SYNTAX); get_nl();return;}
								 if(type_eval)
									 buf_v[index_buf-1].op[index_op++]=ftok;
								 break;
				 case TIME_ON:
				 case TIME_OFF:
				 case INTERVAL:
								 parse_exp0(value) ;
								 if (*token != ')') {	error = TRUE; *value = FALSE ;get_nl(); sntx_err(SYNTAX);return;}
								 if(type_eval)
								 {
									buf_v[index_buf-1].op[index_op++]=ftok;
									if (ftok == INTERVAL)
									{
									 buf_v[index_buf-1].op[index_op++]=0;
									 buf_v[index_buf-1].op[index_op++]=0;
									 buf_v[index_buf-1].op[index_op++]=0;
									 buf_v[index_buf-1].op[index_op++]=0;
									}
								 }
								 break;
				 case AVG:
				 case MAX:
				 case MIN:
							  {
								 char eoiold = eoi;
								 eoi = NL;
								 parse_exp0(value) ;
								 i=1;
								 while(*token == ',')
											{
											 get_token();
											 parse_exp0(value) ;
											 i++;
											}
								 eoi = eoiold;
								 if (*token != ')') {	error = TRUE; *value = FALSE ; sntx_err(SYNTAX);get_nl();return;}
								 if(type_eval)
								 {
									buf_v[index_buf-1].op[index_op++]=ftok;
									buf_v[index_buf-1].op[index_op++]=i;
								 }
								}
								 break;
				 case INKEYD:
				 case OUTPUTD:
								 address_item = 1;
				 case CONPROP:
				 case CONRATE:
				 case CONRESET:
				 case Tbl:
				 case WR_ON:
				 case WR_OFF:
								 if(ftok==INKEYD || ftok==OUTPUTD)
								 {
									memcpy(pt,token,13);
								 }
								 parse_exp0(value) ;
								 if(ftok==INKEYD || ftok==OUTPUTD)
									 address_item = 0;
								 if (*token != ',') {	error = TRUE; *value = FALSE ; sntx_err(SYNTAX);get_nl();return;}
								 get_token();
								 parse_exp0(value) ;
								 if (*token != ')') {	error = TRUE; *value = FALSE ; sntx_err(SYNTAX);get_nl();return;}
								 if(ftok==INKEYD || ftok==OUTPUTD)
								 {
									i=checklocalvar(pt);
									if(i)
									{
									  if(type_eval && ftok==INKEYD)
									  {
										 buf_v[index_buf].fvar = varoffsetlast(i-1);
										 strcpy(buf_v[index_buf].var,"");
										 buf_v[index_buf].v=0;
										 index_op=0;
										 for(i=0;i<MAX_OP;i++)
											 buf_v[index_buf].op[i]=0;
										 index_buf++;
										 n_var++;
									  }
									}
									else
									 {	error = TRUE; *value = FALSE ; sntx_err(SYNTAX);get_nl();return;}
								 }
								 if(type_eval)
									 buf_v[index_buf-1].op[index_op++]=ftok;
								 break;
				 default:
								{	error = TRUE; *value = FALSE ; sntx_err(SYNTAX);get_nl();return;}
			 }
			 get_token();
			 if (token_type==NL)
				if (eol==NL) {--prog;--prog;}
				else --prog;
		 }
		 return;
	 }

	 if((ftok=look_up_func(token))!=0)
	 {
		 switch (ftok) {
				case SUN:
				case MON:
				case TUE:
				case WED:
				case THU:
				case FRI:
				case SAT:
				case JAN:
				case FEB:
				case MAR:
				case APR:
				case MAY:
				case JUN:
				case JUL:
				case AUG:
				case SEP:
				case OCT:
				case NOV:
				case DEC:
				case DOM:
				case DOW:
				case DOY:
				case MOY:
				case POWER_LOSS:
				case SCANS:
				case TIME:
				case USER_A:
				case USER_B:
				case UNACK:
				 if (type_eval)
				 {
					buf_v[index_buf].var[0]=ftok;
					buf_v[index_buf].v=-1;
					index_op=0;
					for(i=0;i<MAX_OP;i++)
						 buf_v[index_buf].op[i]=0;
					index_buf++;
					n_var++;
				 }
				else
					*value = TRUE ;
				get_token() ;
				if (token_type==NL)
						if (eol==NL) {--prog;--prog;}
						else --prog;
				return ;
				break;
			 }
	 }

	 if (type_eval)
	 {
		 if(*prog=='[')
		 {
				 buf_v[index_buf].v=1;
				 index_op=0;
				 for(i=0;i<MAX_OP;i++)
					 buf_v[index_buf].op[i]=0;
				 memcpy(buf_v[index_buf].var,token,13);
				 buf_v[index_buf].fvar=0;
				 index_buf++;
				 n_var++;

				 prog++;
				 get_token();
				 parse_exp0(value) ;
				 buf_v[index_buf-1].op[index_op++]=ASSIGNAR;
		}
		else
		{
		 buf_v[index_buf].v=1;
		 index_op=0;
		 for(i=0;i<MAX_OP;i++)
				 buf_v[index_buf].op[i]=0;
		 strcpy(buf_v[index_buf].var,token);
		 buf_v[index_buf].fvar=0;

		 if( checkonlyarray(token) )
			buf_v[index_buf].op[index_op++]=ASSIGNARRAY;

		 index_buf++;
		 n_var++;
		}
		get_token() ;
		if (token_type==NL)
			if (eol==NL) {--prog;--prog;}
				else --prog;
	 }
	 else
		if (define_var(token))
		{
			*value = TRUE ;
			get_token() ;
			if (*token=='[')
			{
//				 type_eval=0;
				 parse_exp(&res);
				 if(!res)
				 {
					error = TRUE;
					*value = FALSE ;
					sntx_err(SYNTAX);
					get_nl();
				 }
				 get_token();
				 if (*token!=']')
				 {
					error = TRUE;
					*value = FALSE ;
					sntx_err(SYNTAX);
					get_nl();
				 }
				 get_token();
			}
			if (token_type==NL)
				if (eol==NL) {--prog;--prog;}
				else --prog;
		}
		else
		{
//			error = TRUE;
			*value = FALSE ;
//			sntx_err(SYNTAX);
			get_nl();
		}
		return ;

	case TTIME:
	case NUMBER:
		if (type_eval)
		{
			if (token_type==TTIME)
				if (DORU_SYSTEM)
					buf_v[index_buf].fvar=ttimed;
				else
					buf_v[index_buf].fvar=ttime;
			else
			{
			 putback();
			 eval_exp(&buf_v[index_buf].fvar) ;
			}
			strcpy(buf_v[index_buf].var,"");
			buf_v[index_buf].v=0;
			index_op=0;
			for(i=0;i<MAX_OP;i++)
				 buf_v[index_buf].op[i]=0;
			if(token_type == TTIME)
				 buf_v[index_buf].op[index_op++]=TIME_FORMAT;
			index_buf++;
			n_var++;
		}
		else
		{
			*value = TRUE ;
/*			get_token();
			if(!strcmp(token,"e") || !strcmp(token,"E"))
			{
			 get_token();
			 if(token[0]=='-' || token[0]=='+')
				 get_token();
			 if(token_type!=NUMBER)
			 {
				error = TRUE;
				*value = FALSE ;
				get_nl();
				return;
			 }
			}
			else
			 putback();
*/
		}
		get_token() ;
		if (token_type==NL)
				if (eol==NL) {--prog;--prog;}
				else --prog;
		return ;
	case DELIMITER :
		if(*token=='\'') {
			*value = *prog ;
			prog++ ;
			if(*prog != '\'')
			{	error = TRUE; *value = FALSE ; sntx_err(QUOTE_EXPECTED) ;get_nl();return;}
			prog++;

		 if (type_eval)
		 {
			buf_v[index_buf].fvar=*value ;
			strcpy(buf_v[index_buf].var,"");
			buf_v[index_buf].v=0;
			index_op=0;
			for(i=0;i<MAX_OP;i++)
				 buf_v[index_buf].op[i]=0;
			index_buf++;
			n_var++;
		 }
		 *value = TRUE ;
		 get_token() ;
		}
		else
		if(*token=='-') {
		 get_token() ;
		 parse_exp0(value) ;
		 if (type_eval)
			 buf_v[index_buf-1].op[index_op++]=MINUSUNAR;
		 else
			 *value = TRUE ;
		}
		else
			{
			*value = FALSE ;
			error = TRUE;
			get_nl();
			sntx_err(SYNTAX) ;
			}
		return ;
	default :
	 if (*token==')') return; /* process an empty expression */
	 else
		{
			*value = FALSE ;
			error = TRUE;
			get_nl();
			sntx_err(SYNTAX) ;
		}
	}   /* end of switch statement */
}     /* end of atom() */
