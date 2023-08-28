/* Reverse Polish Notation calculator. */

%{
  #include "parser.hpp"
%}

%token NUM
%define api.value.type {double}

%% /* Grammar rules and actions follow. */
input:
  %empty
| input line
;

line:
  '\n'
| exp '\n'      { printf ("%.10g\n", $1); }
;

exp:
  NUM
| exp exp '+'   { $$ = $1 + $2;      }
| exp exp '-'   { $$ = $1 - $2;      }
| exp exp '*'   { $$ = $1 * $2;      }
| exp exp '/'   { $$ = $1 / $2;      }
| exp exp '^'   { $$ = pow ($1, $2); }  /* Exponentiation */
| exp 'n'       { $$ = -$1;          }  /* Unary minus   */
;
%%

int yylex (void) {
  int c = getchar ();
  while (c == ' ' || c == '\t')
    c = getchar ();
  if (c == '.' || isdigit (c))
    {
      ungetc (c, stdin);
#pragma warning(suppress : 4996)
      if (scanf ("%lf", &yylval) != 1)
        abort ();
      return NUM;
    }
  else if (c == EOF)
    return YYEOF;
  else
    return c;
}

void yyerror (char const *s) {
  fprintf (stderr, "%s\n", s);
}
