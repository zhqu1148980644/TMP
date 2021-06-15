#ifndef STACK_EX
#define STACK_EX


#ifndef TEST
#define TEST
#define TEST_EX
#endif



#include "stack.cpp"
#include <iostream>
#include <stdlib.h>
#include "vector.cpp"
#include <ctype.h>
#include <stdio.h>
#include <cmath>
#include <time.h>

using std::cout;
using std::endl;
using std::cerr;
using std::abs;
using std::begin;
using std::end;

/*****************************************************convert decimal base****************************************************/
/*
// recursion version
void convert(Stack<char> & stack, long long n, size_t base)
{
    static char digit[] = { '0', '1', '2', '3', '4', '5',
        '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' }
    if ( 0 < n )
    {
        convert(S, n / base, base);
        stack.push(digit[n % base]);   // inversed order
    }
}
*/


// iteration version
void convert(Stack<char> & stack, long long n, size_t base)
{
    static char digit[]
    = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
    while ( 0 < n)
    {
        stack.push(digit[(int) (n % base)]);
        n /= base;
    }
}


// check for integrity of brackets  /////////////////////////////////////////////////////////////////

// devide and conquer                             not tested yet
void trim(char const exp[], size_t & lo, size_t & hi)
{
    while ( (lo <= hi) && (exp[lo] != '(') && (exp[lo] != ')') ) ++lo;
    while ( (lo <= hi) && (exp[hi] != '(') && (exp[lo] != ')') ) --hi;
}

int divide(char const exp[], size_t lo, size_t hi)
{
    size_t mi = lo; size_t crc = 1;
    while ( (0 < crc) && (++mi < hi) )
    {
        if (exp[mi] == ')')
            --crc;
        if (exp[mi] == '(')
            ++crc;
    }
    return mi;
}

// divide and conquer. recursion version
bool paren_recursion(char const exp[], size_t lo, size_t hi)
{
    trim(exp, lo, hi);
    if (lo > hi) return true;    // never be the same
    if (exp[lo] != '(') return false;
    if (exp[hi] != ')') return false;
    size_t mi = divide(exp, lo, hi);
    return paren_recursion(exp, lo + 1, mi -1) && paren_recursion(exp, mi + 1, hi); // mi + 1.there must be one operator in mi
}

// linear iteration
bool paren(char const exp[],size_t lo, size_t hi)
{
    Stack<char> s;
    for (size_t i = 0; exp[i]; ++i)
    {
        switch( exp[i] )
        {
            case 'C': ;
            case '[': ;
            case '{': s.push(exp[i]); break;
            case ')': if ( (s.empty()) || (s.pop() != '(') ) return false; break;
            case ']': if ( (s.empty()) || (s.pop() != '[') ) return false; break;           
            case '}': if ( (s.empty()) || (s.pop() != '{') ) return false; break;
            default : break;
        }
    }
    return s.empty();
}

///////////////////////////////////////////////////////////////////////////////////////////////



// expressions //////////////////////////////////////////////////////////////////////////////

typedef enum {ADD, SUB, MUL, DIV, POW, FAC, L_P, R_P, EOE} Operator;

char pro[9][9] = {
/*         +    -    *    /    ^    !    (    )   \0  */
/* + */   '>', '>', '<', '<', '<', '<', '<', '>', '>',
/* - */   '>', '>', '<', '<', '<', '<', '<', '>', '>',
/* * */   '>', '>', '>', '>', '<', '<', '<', '>', '>',
/* / */   '>', '>', '>', '>', '<', '<', '<', '>', '>',
/* ^ */   '>', '>', '>', '>', '<', '<', '<', '>', '>',
/* ! */   '>', '>', '<', '<', '<', '<', '<', '>', '>',
/* ( */   '<', '<', '<', '<', '<', '<', '<', '=', '(',
/* ) */   ')', ')', ')', ')', ')', ')', ')', ')', ')',
/* 0 */   '<', '<', '<', '<', '<', '<', '<', ')', '=',
};


long long factorial(size_t n)
{
    long long result = 1;
    while (n)
        result *= n--;
    return result;
}

void read_number(char const * & s, Stack<double> & opnd)
{
    opnd.push((double)(*s - '0'));
    while (isdigit(*(++s)))
        opnd.push(opnd.pop() * 10 + (*s - '0'));
    if (*s != '.') return;
    double fraction = 1;
    while (isdigit(*(++s)))
        opnd.push(opnd.pop() + (*s - '0') * (fraction /= 10));
}

double calcu(char const & s, double num)
{
    switch (s)
    {
        case '!': return factorial(floor(num));
        default :
            cerr << "wrong unary operator\n";
            exit(EXIT_FAILURE);
    }
}

double calcu(double num1, char const & s, double num2)
{
    switch (s)
    {
        case '+': return num1 + num2;
        case '-': return num1 - num2;
        case '*': return num1 * num2;
        case '/': return num1 / num2;
        case '^': return pow(num1, num2);
        default :
            cerr << "wrong binary operator |" << s << "|" << endl;
            exit(EXIT_FAILURE);
    }
}

void append(char * & rpn, char & s)
{
    char * find = strchr(rpn, '\0');
    if (find)
    {
        *find = s;
        *++find = ' ';
        *++find = '\0';
    }
}

void append(char * & rpn, double & num)
{
    size_t n = strlen(rpn);
    char buf[64];
    if (num != (double)(int)(num))
        sprintf(buf, "%.2f \0", num);
    else
        sprintf(buf, "%d \0", (int)num);
    strcat(rpn, buf);
}

size_t index_opt(char const & op)
{
    switch (op)
    {
        case '+': return ADD;
        case '-': return SUB;
        case '*': return MUL;
        case '/': return DIV;
        case '^': return POW;
        case '!': return FAC;
        case '(': return L_P;
        case ')': return R_P;
        case '\0': return EOE;
        default : 
            cerr << "wrong operator in index_opt\n";
            exit(EXIT_FAILURE);
    }
}

char const & order_between(char const & op1, char const & op2)
{
    return pro[index_opt(op1)][index_opt(op2)];
}


double evaluate(char const * s, char * rpn)
{
    Stack<char> optr;
    Stack<double> opnd;
    size_t bracket_szie = 0;
    char op;
    optr.push('\0');
    while (!optr.empty())
    {
        while (isspace(*s)) ++s;
        if (isdigit(*s))
        {
            read_number(s, opnd);
            append(rpn, opnd.top());
        }
        else
            switch (order_between(optr.top(), *s))
            {
                case '<':
                    if (((optr.size() -1 - bracket_szie) != (opnd.size() - 1)) && *s != '(' )
                    {
                        cerr << "Invalid expression before: " << s << endl;
                        exit(EXIT_FAILURE);
                    }
                    if (*s == '(') ++bracket_szie;
                    optr.push(*s++);
                    break;
                case '>':
                    op = optr.pop(); append(rpn, op);
                    if ('!' == op)
                    {
                        if (opnd.size() == 0)
                        {
                            cerr << "Defiency of operating number\n";
                            exit(EXIT_FAILURE);
                        }
                        double num = opnd.pop();
                        opnd.push(calcu(op, num));
                    }
                    else
                    {
                        if (opnd.size() < 2)
                        {
                            cerr << "Defiency of operating number\n";
                            exit(EXIT_FAILURE);
                        }
                        double num2 = opnd.pop();
                        double num1 = opnd.pop();
                        opnd.push(calcu(num1, op, num2));
                    }
                    break;
                case '=':
                    optr.pop(); ++s;
                    --bracket_szie;
                    break;
                case ')' :
                    cerr << "unmatched ')' in " << s << " \n";
                    exit(EXIT_FAILURE);
                case '(' :
                    cerr << "unmatched '(' \n";
                    exit(EXIT_FAILURE);
                default :
                    cerr << "Unrecognized error\n";
                    exit(EXIT_FAILURE);
            }// switch            
    }//while
    return opnd.pop();    
}


double evaluate(char  const * rpn)
{
    Stack<double> nums; 
    while (1)
    {
        while (isspace(*rpn)) ++rpn;
        if (!*rpn) break;
        if (isdigit(*rpn))
            read_number(rpn, nums);
        else
        {
            if ('!' == *rpn )
                nums.push(calcu(*rpn, nums.pop()));
            else
            {
                double num2 = nums.pop();
                double num1 = nums.pop();
                nums.push(calcu(num1, *rpn, num2));            
            }
        }
    ++rpn;
    }
    return nums.pop();
}
////////////////////////////////////////////////////////////////////////////////////////////





// Queen //////////////////////////////////////////////////////////////////////////////////

/************************************************backtrack version****************************************/
struct Queen
{
    int x, y;
    Queen(size_t xx = 0, size_t yy = 0) : x(xx), y(yy) {}
    bool operator==(Queen const & q) const
    {
        return ( y == q.y )
                || ( x + y == q.x + q.y )
                || ( x - y == q.x - q.y );
    }
    bool operator!=(Queen const & q) const
    {
        return !(*this == q);
    }
};



struct Result
{
    Result() : ncheck(0) {}
    Stack<Stack<Queen>> solutions;
    size_t ncheck;
};

// using backstrap. return to the nearst last point instead of repeatedly go through the same path.
Result place_queen(size_t N, Result & res)
{
    Queen q(0, 0);
    Stack<Queen> solution;
    while ( (0 < q.x) || (q.y < N) )// end when search to the final point: first row and the end + 1 column (x=0, y=N)
    {
        if  ( N == solution.size() || N == q.y)
        {
            q = solution.pop();
            ++q.y;            
        }
        else
        {        
            while ( (q.y < N) && (0 <= solution.find(q)) )
                ++q.y; ++res.ncheck;
            if (q.y < N)
            {
                solution.push(q);
                if (solution.size() == N)
                    res.solutions.push(solution);
                else
                {
                    ++q.x;
                    q.y = 0;
                }
            }
        }
    }
    cout << "end: " << q.x << "|" << q.y << endl;
    cout << solution.size() << endl;
    cout << time << endl;
    return res;
}

/*******************************************************early stop version******************************************/
// recursion version
// search every chances but terminate the impossible path

void queen(size_t N, Vector<int> path, int row, Vector<Vector<int>> & vv);

void place_queen(size_t N, Vector<Vector<int>>  & vv)
{
    Vector<int> path(N, N, 0);
    queen(N, path, 0, vv);
}

void queen(size_t N, Vector<int> path, int row, Vector<Vector<int>> & vv)
{
    if (row == N)
    {
        vv.push_back(path);
        return;
    }
    for (int col = 0; col < N; ++col)
    {
        path[row] = col;
        bool next = true;
        for (size_t back_row  = 0; back_row < row; ++back_row)
        {
            if ((path[back_row] == col) || (abs(path[back_row] - col) == row - back_row))
                next = false;
        }
        if (next)
            queen(N, path, row + 1, vv);
    }
}


//////////////////////////////////////////////////////////////////////////////////////////



/***************************************************************************************************************************/


#ifdef STACK_EX

int main(int argc, char ** argv)
{
    // test decimal to base
    Stack<char> decimal_stack;
    long long num = 454613748;
    int base = 16;
    convert(decimal_stack, num, base);
    cout << "decimal number: " << num << "'s " << base << " format is : ";
    while (!decimal_stack.empty())
        cout << decimal_stack.pop();
    cout << endl;

    // test calculation
    char rpn[500];
    memset(rpn, '\0', sizeof(rpn));
    char const * expres = "1+478*16 *(1+3/2)/4!+(100-54)/24";
    cout << expres <<"'s result is: " << evaluate(expres, rpn) << endl;
    cout << "rpn expression is: " << rpn << endl;

    // test rpn calculation
    cout << rpn << "'s result is: " << evaluate(rpn) << endl;

    // test search queen
    clock_t start = clock();
    Result res;
    place_queen(6, res);
    cout << res.solutions.size() << endl;
    cout << res.ncheck << endl;
    while (!res.solutions.empty())
    {
        Stack<Queen> tmp = res.solutions.pop();
        while (!tmp.empty())
        {
            Queen q = tmp.pop();
            cout << q.x << "-" << q.y << "  ";
        }
        cout << endl;
    }
    cout << "Total time is: " << (clock() - start) << " seconds!\n";
    // test search queen brute force way
    start = clock();
    Vector<Vector<int>> vv;
    place_queen(6, vv);
    cout << vv.size() << endl;
    for (auto & v : vv)
    {
        for (auto & i : v)
            cout << i << "-";
        cout << endl;
    }
    cout << endl;
    cout << "Total time is: " << (clock() - start) << " seconds!\n";

}
#endif


#endif
