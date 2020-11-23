#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H


#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<getopt.h>
#include <math.h>


#define EXPONENT 1
#define DIVISION 2
#define MULTIPLICATION 3
#define ADDITION 4
#define SUBTRACTION 5

typedef struct {
    double co_efficient; 
    double degree; 
} x_algebra;

//stack operators
// char* xpart(char* term);
int find_power(char operand[]);
int is_digit(char input);
char* addx(char input[],char operand[]);
double co_efficient(char input[]);

int is_same_power(char* operand1, char* operand2);
int has_constant(char* operand);
int isalgebra(char* input);
int precedence(char input);
int isleft_assosciative(char input);
int is_better_operator(char token,char top_operator_on_stack);
int isoperator(char input);

int isnumber(char* input);
int isunary(char expression[], int index);
void error(int flag);
void arithmetic(char output_queue[]);
void algebra(char output_queue[]);



//

double* stack_operator(char* expression);
double* stack_number(char* expression);
char* clear_whitespace(char string[]);
void calculation(char user_input[]);
void help();
void user_command();




#endif

