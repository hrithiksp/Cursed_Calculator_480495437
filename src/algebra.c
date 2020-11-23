#include"functions.h"

void algebra(char output_queue[]){
    char result_queue[1024][1024];
    int top_result=-1;
    // printf("%s\n",output_queue);

    char* token = strtok(output_queue,",");
    char operand1[1024];
    char operand2[1024];
    double op1,op2;
    double result=0;
    double power=1;
    double const_power=0;\
    int power1,power2;
    double constant=0;
    double constant_op1=0;
    double constant_op2=0;
    double co_eff=0;
    char power_str[1024];
    char const_str[1024];
    double coeff[1024];
    double degree[1024];
    int top_coeff=-1;
    int top_degree=-1;
    double optr=0;
    double prev_power=1;
    int on = 1;
    double co_eff_1,co_eff_2;
    double constant_1,constant_2;

    while(token != NULL){
        on =1;
        if(isalgebra(token)||isnumber(token)){
            top_result++;
            strcpy(result_queue[top_result],token);
            if(isalgebra(token)){
                prev_power=power;
                power=1;
            }
         }
        else{
            strcpy(operand2,result_queue[top_result]);
            strcpy(operand1,result_queue[top_result-1]);
            top_result-=2;
            if(token[0]=='u'){

            }
            else if(token[0]=='^'){
                if(!isalgebra(operand1)&&!isalgebra(operand2)){
                top_result++;
                snprintf(result_queue[top_result], 1024, "%0.3lf",pow(op1,op2));
                }
                else{
                    top_result++;
                    co_eff = co_efficient(operand1);
                    power = strtod(operand2,NULL);
                    co_eff = pow(co_eff,power);
                    snprintf(result_queue[top_result], 1024, "%0.3lf",co_eff);
                    strcat(result_queue[top_result],"x");
                    strcat(result_queue[top_result],"^");
                    snprintf(power_str, 1024, "%0.3lf",power);
                    strcat(result_queue[top_result],power_str);
                }
            }
            else{
                if(isalgebra(operand1)&&isalgebra(operand2)){
                    constant_1=0;constant_2=0;
                    power1 = find_power(operand1);
                    power2 = find_power(operand2);
                    if(power1==power2){
                        co_eff_1 = co_efficient(operand1);
                        co_eff_2 = co_efficient(operand2);
                    }
                    else{
                        co_eff_1 = co_efficient(operand1);
                        co_eff_2 = 0;
                        constant = co_efficient(operand2);
                        power = (double)power1;
                        const_power = (double)power2;
                    }
                }
                else if(!isalgebra(operand1)&&!isalgebra(operand1)){
                    constant_1 = strtod(operand1,NULL);
                    constant_2 = strtod(operand2,NULL);
                    // co_eff_1=co_eff;co_eff_2=0;
                }
                else if(isalgebra(operand1)){
                    co_eff_1 = co_efficient(operand1);
                    constant_2 = strtod(operand2,NULL);
                    constant_1=0;co_eff_2=0;
                    optr = 1;
                }
                else if(isalgebra(operand2)){
                    co_eff_2 = co_efficient(operand2);
                    constant_1 = strtod(operand1,NULL);
                    constant_2=0;co_eff_1=0;
                    optr = 1;
                }

                if(token[0]=='+'){
                    co_eff = co_eff_1+co_eff_2;
                    constant+= constant_1+constant_2;
                }
                else if(token[0]=='-'){
                    co_eff = co_eff_1-co_eff_2;
                    constant+= constant_1-constant_2;
                }
                else if(token[0]=='*'){
                    if(isalgebra(operand1)&&isalgebra(operand2)){
                        co_eff = co_eff_1*co_eff_2;
                        if(has_constant(operand1)){
                            constant = constant*co_eff_2;
                            const_power++;
                        }
                        else if(has_constant(operand2)){
                            constant = constant*co_eff_1;
                            const_power++;
                        }
                        power++;
                    }
                    else if(isalgebra(operand1)){
                        co_eff=co_eff_1*constant_2;
                        constant*=constant_2;
                    }
                    else if(isalgebra(operand2)){
                        co_eff=co_eff_2*constant_1;
                        constant*=constant_1;
                    }
                    else{
                        constant = constant_1*constant_2;
                    }
                }
                top_result++;
                if(co_eff==0){
                    snprintf(result_queue[top_result], 1024, "%0.3lf",constant);
                    constant=0;
                }
                else if(co_eff>=1){
                    snprintf(result_queue[top_result], 1024, "%0.3lf",co_eff);
                    strcat(result_queue[top_result],"x");
                    if(power>=2){
                        strcat(result_queue[top_result],"^");
                        snprintf(power_str, 1024, "%0.3lf",power);
                        strcat(result_queue[top_result],power_str);
                    }
                    if(constant!=0){
                        // printf("yes");
                        snprintf(const_str,1024, "%0.3lf",constant);
                        if(constant>0){
                            strcat(result_queue[top_result],"+");
                        }
                        strcat(result_queue[top_result],const_str);
                    }
                    if(const_power>0){
                        strcat(result_queue[top_result],"x");
                        if(const_power>=2){
                            strcat(result_queue[top_result],"^");
                            snprintf(power_str, 1024, "%0.3lf",const_power);
                            strcat(result_queue[top_result],power_str);
                        }
                    }

                }


            }

        }

    token = strtok(NULL,",");
    }

    printf("%s\n",result_queue[top_result]);
}
