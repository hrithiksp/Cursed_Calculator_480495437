#include "functions.h"


void user_command(){
    char user_input[1024];
    printf(">>> ");
    fgets(user_input,1024,stdin);
    char result[100];
    double output;
    if(user_input[0] == 'q'||user_input[0] == 'Q'){
        printf("Goodbye!\n");
        exit(0);
    }
    if(user_input[0] == 'h'||user_input[0] == 'H'){
        if(user_input[2]=='\0'){
            help();
            user_command();
        }
        else{
            error(2);
        }
    }
    else{
        calculation(user_input);
        user_command();
    }
    return;
}

void calculation(char user_input[]){
    char output_queue[1024];
    char operator_stack[1024];
    int top_output = -1;
    int top_operator = -1;

    user_input = clear_whitespace(user_input);
    char* expression = user_input;
    //printf("%s\n",expression);

    
    for(int i=0;i<strlen(expression);i++){
        // printf("%d,%d\n",isunary(expression,i),isoperator(expression[i]));
        if(is_digit(expression[i])||expression[i]=='.'||expression[i]=='x'||expression[i]=='X'){
            top_output++;
            output_queue[top_output]=expression[i];
           
        }
        else if(isunary(expression,i)==1){
            
            top_output++;
            output_queue[top_output]='0';
            top_output++;
            output_queue[top_output]=','; 
            top_operator++;
            operator_stack[top_operator]='u';
            // printf("%c\n",operator_stack[top_operator]);
        }
        else if(expression[i]=='('){
            // printf("last: %c\n",expression[i-1]);
            if(top_output>=0&&output_queue[top_output]!=','){
                top_output++;
                output_queue[top_output]=',';
            }
            if(expression[i-1]==')'){
                top_operator++;
                operator_stack[top_operator]='*';     
            }
            else if(is_digit(expression[i-1])||expression[i-1]=='x'||expression[i-1]=='X'){
            //top_output++;
            //output_queue[top_output]=',';
                top_operator++;
                operator_stack[top_operator]='*';     
            }
            top_operator++;
            operator_stack[top_operator]=expression[i]; 

        }
        else if(isoperator(expression[i])){

            // printf("%c",operator_stack[top_operator]);
            while(!is_better_operator(expression[i],operator_stack[top_operator])){
                //  printf("I am here\n");
                // printf("8");
                top_output++;
                output_queue[top_output]=','; 
                top_output++;
                output_queue[top_output]=operator_stack[top_operator];
                top_operator--;
                
                
            }
            top_operator++;
            operator_stack[top_operator]=expression[i];
            top_output++;
            output_queue[top_output]=','; 
            
        }
       

        else if(expression[i]==')'){

            while(operator_stack[top_operator]!='('){
                top_output++;
                output_queue[top_output]=',';
                top_output++;
                output_queue[top_output]=operator_stack[top_operator];
                top_operator--;

            }
            if(operator_stack[top_operator]=='('){

                top_operator--;
            }            
        } 
    }
    while(top_operator>=0){
        top_output++;
        output_queue[top_output]=',';
        top_output++;
        output_queue[top_output]=operator_stack[top_operator];
        top_operator--;
    }

 /* stuck hererehrehrehrherhehrerhehrehrherhe*/   
    // printf("%s\n",output_queue);
    if(isalgebra(output_queue)){
        algebra(output_queue);
    }
    else{
        arithmetic(output_queue);
    }
}

void arithmetic(char output_queue[]){
    double result_queue[1024];
    int top_result=-1;
    // printf("%s\n",output_queue);
    char* token = strtok(output_queue,",");
    double operand1=0;
    double operand2=0;
    while(token != NULL){
         
        if(is_digit(token[0])){
            top_result++;
            result_queue[top_result]=strtod(token,NULL);
            // printf("%s, ",token);
            
        }
        else{
            if(top_result<=0){
            //if there are no enough arguments
                error(2);
            }
            operand2 = result_queue[top_result];
            operand1 = result_queue[top_result-1];
            //printf("operands: %lf,%lf;;;", operand1,operand1);
            top_result-=2;

            if(token[0]=='u'){
                top_result++;
                result_queue[top_result]=operand1+operand2*(-1);
            }

            else if(token[0]=='+'){
                // printf("%lf,%lf::%s\n",operand1,operand2,token);
                top_result++;
                result_queue[top_result]=operand1+operand2;
                // printf("%lf\n",result_queue[top_result]);
            }
            else if(token[0]=='/'){
                
                top_result++;
                if(operand2 == 0){
                    error(1);
                }
                result_queue[top_result]=operand1/operand2;
                
            }
            else if(token[0]=='*'){
                top_result++;
                result_queue[top_result]=operand1*operand2;
                
            }
            else if(token[0]=='-'){
                
                top_result++;
                result_queue[top_result]=operand1-operand2;
                
            }
            else if(token[0]=='^'){
                
                top_result++;
                result_queue[top_result]=pow(operand1,operand2);
                
            }
            else if(token[0]=='e'){
                top_result++;
                result_queue[top_result]=operand1*pow(10,operand2);
            }
            
        }
    token = strtok(NULL,",");
    }
    printf("%0.3lf\n",result_queue[top_result]);
}


char* addx(char input[],char operand[]){
    char xpart[1024];
    int i =0;
    int top = -1;
    char term[1024];
    while(operand[i]!='\0'){
        if(operand[i]=='x'||operand[i]=='X'){
            int j =i;
            while(operand[j]!='\0'){
                top++;
                xpart[top]=operand[j];
                j++;
            }
            break;  
        }
        i++;
    }
    // printf("%s\n",xpart);
    strcat(input,xpart);
    return input;
}
int is_same_power(char* operand1, char* operand2){
    if(find_power(operand1)==find_power(operand2)){
        return 1;
    }
    else 
        return 0;

}

double co_efficient(char input[]){
    double output = strtod(input,NULL);
    if (output==0){
        output=1;
    }
    return output;
}

int has_constant(char* operand){
    int i =0;
    int flag=0;
    while(operand[i]!='\0'){
        if(operand[i]=='x'||operand[i]=='X'){
            int j =i+1;
            while(operand[j]!='\0'){
                if(is_digit(operand[j])){
                    flag=1;
                }
                else if(operand[j]=='x'||operand[j]=='X'){
                    flag = 0;
                    break;
                }
                j++;
            }
            break;  
        }
        i++;
    }
    return flag;
}

int find_power(char operand[]){
    int i =0;
    int power=1;
    char power_str[1024];
    int top=-1;
    while(operand[i]!='\0'){
        if(operand[i]=='^'){
            int j =i+1;
            while(operand[j]>=48&&operand[j]<=57){
                top++;
                power_str[top]=operand[j];
                j++;
            }
            break;  
        }
        else{
            power=1;
        }
        i++;
    }
    power = atoi(power_str);
    while(top>=-1){
        power_str[top]='\0';
        top--;
    }
    if(power==0){
        power=1;
    }
    return power;
}

char* clear_whitespace(char string[]){
    for(int i=strlen(string)-1;i>=0;i--){
        if(string[i]==' '){
            for(int x = i; x<=strlen(string); x++){
                string[x]=string[x+1];
            }
        }
    }    

    return string;
}
void help(){
    FILE *f;
    char s;
    f=fopen("help.txt","r");
    while((s=fgetc(f))!=EOF) {
        printf("%c",s);
    }
    fclose(f);
}

int is_digit(char input){
    if(input>47&&input<=57){
        return 1;
    }
    else{
        return 0;
    }
}
int isoperator(char input){
    if(input=='+'||input=='-'||input=='*'||input=='/'||input=='^'||input=='e'||input=='u'){
        return 1;
    }
    else{
        return 0;
    }
}
int is_better_operator(char token,char top_operator_on_stack){
   
if(isoperator(top_operator_on_stack)){
//    printf("yy");
    if(precedence(top_operator_on_stack)>precedence(token)){
        if(top_operator_on_stack!='('){
            return 0;
        }
    }
    else if(precedence(top_operator_on_stack)==precedence(token)){
        if(isleft_assosciative(token)){
            if(top_operator_on_stack!='('){
                return 0;
            }
        }
    }
}
else{
    return 1;
}
}
int isleft_assosciative(char input){
    if(input == '^'){
        return 0;
    }
    else{
        return 1;
    }
}
int precedence(char input){
    int precedence = 0;
    switch (input){
        case 'u':
            precedence = 5;
            break;
        case '^':
            precedence = 4;
            break;
        case '*':
            precedence = 3;
            break;
        case '/':
            precedence = 3;
            break;
        case '+':
            precedence = 2;
            break;
        case '-':
            precedence = 2;
            break;

    }
    return precedence;
}

int isunary(char expression[], int index){

    if(index==0&&expression[index]=='-'){
        return 1;
    }
    else if(isoperator(expression[index-1])&&expression[index]=='-'){
        return 1;
    }
    else if(expression[index-1]=='('&&expression[index]=='-'){
        return 1;
    }
    else{
        return 0;
    }
}

int isalgebra(char* input){
    char* term = input;
    int result = 0;
    int i = 0;
    while(input[i]!='\0'){
        if(input[i]=='x'||input[i]=='X'){
            result = 1;
        }
    i++;
    }
    return result;
}

int isnumber(char* input){
    char* term = input;
    int result = 1;
    int i = 0;
    while(input[i]!='\0'){
        if(!is_digit(input[i])&&input[i]!='.'){
            result = 0;
        }
    i++;
    }
    return result;
}

void error(int flag){
    if(flag==1){
        printf("Error: Divide by zero!\n");
    }
    else{
        printf("Error: Illegal input!\n");
    }
    user_command();

}


