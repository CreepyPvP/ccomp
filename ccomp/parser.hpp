#pragma once

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>

int yylex (void);
void yyerror (char const *);
int yyparse(void);
