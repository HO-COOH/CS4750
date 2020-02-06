# Homework 6 - Fall 2019
Use backtracking search to to solve the Boolean satisfiability problem.

---

## Project Overview
I accidently named the project to HW5. It should be HW6 instead.
/src/HW5.sln    ...The Visual Studio solution file
/src/x64/       ...The executable
/src/3SAT.h     ...The header file
/src/3SAT.cpp   ...The source file for the algorithm
/src/main.cpp   ...The main function for testing cases

#### Team Members:
Wenhao Li

#### Language/Environment Used:
C++ /Windows X64 bit

#### Description of Implementation:
Backtracking is done by a recursive function. The function started first by picking a variable according to the two heuristics. Then it tries whether the remaining value of the variable is consistent with the assignments. If it is, recursively calls the function itself. Otherwise, it tries the next value of the variable. If none value is consistent, return false.

Forward checking is done by checking the values of variables in one single clause. Usually, the clause contains three variables. If two of them are already assigned, and they are all false, then the third variable must be assigned to be true to satisfy this clause. Forward checking is called after one variable is assigned to a new value.

#### System Hardware:
Ryzen 7. I didn't implement multithreading functions, so it shouldn't matter much.

---

## Solutions

### MRV and Degree Heuristic
Way too long to get an answer. I tried running the program for one whole day, and it doesn't finish either one of the two test cases. I have to terminate.

1. __Test Case 1__:
    - First 8 Variable Assignments:
    - Final Solution:
    - Total Number of Assignments Tried:
    - CPU Execution Time: ∞
2. __Test Case 2__:
    - First 8 Variable Assignments:
    - Final Solution:
    - Total Number of Assignments Tried:
    - CPU Execution Time: ∞

### MRV and Degree Heuristic with Forward Checking
1. __Test Case 1__:
I copied this from my console. The variable index starts from 0.
    - First 8 Variable Assignments: 
        assignment0 V63
        assignment1 V81
        assignment2 V8
        assignment3 V13
        assignment4 V19
        assignment5 V33
        assignment6 V37
        assignment7 V40
    - Final Solution: 
        V0=F V1=T V2=T V3=T V4=T V5=F V6=T V7=T V8=T V9=T
        V10=T V11=F V12=T V13=T V14=F V15=T V16=T V17=T V18=F V19=T
        V20=T V21=T V22=T V23=T V24=T V25=T V26=T V27=T V28=F V29=T
        V30=T V31=F V32=F V33=T V34=F V35=F V36=T V37=T V38=T V39=T
        V40=T V41=F V42=F V43=T V44=T V45=F V46=T V47=T V48=T V49=F
        V50=T V51=T V52=T V53=T V54=F V55=T V56=T V57=T V58=T V59=T
        V60=T V61=T V62=T V63=T V64=F V65=T V66=T V67=T V68=T V69=F
        V70=F V71=T V72=T V73=T V74=T V75=F V76=F V77=T V78=T V79=T
        V80=T V81=T V82=T V83=T V84=T V85=T V86=T V87=T V88=T V89=T
        V90=T V91=T V92=T V93=F V94=T V95=F V96=T V97=T V98=T V99=T
    - Total Number of Assignments Tried: 217155
    - CPU Execution Time: 0.16s
2. __Test Case 2__:
    - First 8 Variable Assignments:
        assignment0 V181
        assignment1 V2
        assignment2 V4
        assignment3 V7
        assignment4 V11
        assignment5 V12
        assignment6 V18
        assignment7 V24
    - Final Solution:
        V0=T V1=T V2=F V3=F V4=F V5=F V6=F V7=F V8=F V9=T
        V10=F V11=F V12=F V13=F V14=F V15=F V16=T V17=T V18=F V19=F
        V20=F V21=F V22=F V23=F V24=F V25=F V26=F V27=F V28=F V29=T
        V30=F V31=F V32=F V33=T V34=F V35=F V36=F V37=T V38=F V39=F
        V40=F V41=F V42=F V43=T V44=T V45=T V46=F V47=F V48=F V49=F
        V50=F V51=F V52=F V53=F V54=F V55=F V56=F V57=F V58=F V59=F
        V60=F V61=T V62=F V63=F V64=T V65=F V66=F V67=F V68=F V69=F
        V70=F V71=F V72=T V73=T V74=F V75=F V76=T V77=F V78=F V79=F
        V80=T V81=F V82=F V83=T V84=F V85=F V86=F V87=F V88=F V89=F
        V90=F V91=F V92=F V93=F V94=F V95=F V96=F V97=T V98=T V99=F
        V100=F V101=F V102=F V103=F V104=T V105=F V106=F V107=F V108=F V109=T
        V110=F V111=F V112=F V113=F V114=F V115=F V116=F V117=F V118=F V119=T
        V120=F V121=F V122=F V123=F V124=F V125=T V126=T V127=F V128=F V129=F
        V130=F V131=F V132=F V133=F V134=T V135=F V136=F V137=T V138=F V139=T
        V140=F V141=F V142=F V143=T V144=T V145=F V146=T V147=F V148=F V149=F
        V150=F V151=F V152=T V153=F V154=F V155=F V156=F V157=F V158=F V159=F
        V160=F V161=F V162=F V163=T V164=T V165=T V166=T V167=F V168=F V169=F
        V170=F V171=T V172=F V173=F V174=F V175=F V176=F V177=T V178=T V179=F
        V180=F V181=F V182=F V183=T V184=F V185=F V186=F V187=F V188=F V189=F
        V190=F V191=T V192=F V193=F V194=F V195=F V196=F V197=T V198=T V199=F
    - Total Number of Assignments Tried: 172476
    - CPU Execution Time: 0.227s
