#include <iostream>
#include <string>
#include <cstdio>
#include <cctype>
#include <stack>
#include <cmath>
#include <iomanip>

using namespace std;

const int SIZE = 1000, SGN = 1, VAL = 0;
const string allowed = "+-*/sc()0123456789 ";
const double ERROR = 1.94783;
#define handle_error {res.a[0].type = -1; return res;}


int greater_priority(char c, char pre_c)
{
    return (pre_c == '+' || pre_c == '-') && (c == '*' || c == '/');
}

struct polish_notated
{
    int l;
    struct elem
    {
        int type;
        double val;
        char smb;
    } a[SIZE];
};

double get_val(string s, int &i)
{
    double ans = 0, len = s.size();
    while (i < len && isdigit(s[i]))
        ans = ans * 10 + s[i++] - '0';

    if (i < len && s[i] == '.')
    {
        int ap = i + 1;

        if (ap < len && s[i] == '.' && isdigit(s[ap]))
        {
            while (ap < len && isdigit(s[ap]))
                ans = ans * 10 + s[ap++] - '0';
        }
        else
            return ERROR;

        for (int j = ap; j > i + 1; j--)
            ans /= 10;

        i = ap;
    }

    i--;

    return ans;
}

struct polish_notated to_polish(string s)
{
    int l = s.size();
    stack<char> st;
    stack<char> sncs;

    struct polish_notated res;
    res.l = 0;

    for (int i = 0; i < l; i++)
    {
        if (allowed.find(s[i]) == string::npos)
            handle_error

                if (s[i] == ' ')
                    continue;
        if (isdigit(s[i]))
        {
            res.a[res.l].type = VAL;
            double t = get_val(s, i);
            if (t == ERROR)
                handle_error
            else
                res.a[res.l++].val = t;
        }
        else if (s[i] == '(')
            st.push('(');
        else if (s[i] == ')')
        {
            while (!st.empty() && st.top() != '(')
            {
                res.a[res.l].type = SGN;
                res.a[res.l++].smb = st.top();
                st.pop();
            }

            if (st.empty())
                handle_error
            else
                st.pop();

            if (sncs.size())
            {
                res.a[res.l].type = SGN;
                res.a[res.l++].smb = sncs.top();
                sncs.pop();
            }
        }
        else if (s[i] == 's')
        {
            if (i + 4 >= l || s[i + 1] != 'i' || s[i + 2] != 'n')
                handle_error

                    int j;
            for (j = i + 3; j < l && s[j] == ' '; j++);
            if (j == l || s[j] != '(')
                handle_error

                    sncs.push('s');
            i += 2;
        }
        else if (s[i] == 'c')
        {
            if (i + 4 >= l || s[i + 1] != 'o' || s[i + 2] != 's')
                handle_error

                    int j;
            for (j = i + 3; j < l && s[j] == ' '; j++);
            if (j == l || s[j] != '(')
                handle_error

                    sncs.push('c');
            i += 2;
        }
        else
        {
            if (st.empty() || st.top() == '(' || greater_priority(s[i], st.top()))
                st.push(s[i]);
            else
            {
                while (!st.empty() && st.top() != '(' && !greater_priority(s[i], st.top()))
                {
                    res.a[res.l].type = SGN;
                    res.a[res.l++].smb = st.top();
                    st.pop();
                }
                st.push(s[i]);
            }
        }
    }

    while (!st.empty())
    {
        res.a[res.l].type = SGN;
        res.a[res.l++].smb = st.top();
        st.pop();
    }


    /*for (int i = 0; i < res.l; i++)
      {
      if (res.a[i].type == SGN)
      cout << res.a[i].smb << " ";
      else
      cout << res.a[i].val << " ";
      } */

    return res;
}

double calculate(struct polish_notated s)
{
    stack<double> st;
    int l = s.l;
    for (int i = 0; i < l; i++)
    {
        if (s.a[i].type == VAL)
            st.push(s.a[i].val);
        else
        {
            if (s.a[i].smb == 's' || s.a[i].smb == 'c')
            {
                double a;
                if (!st.empty())
                    a = st.top();
                else
                    return ERROR;
                st.pop();

                if (s.a[i].smb == 's')
                    st.push(sin(a));
                else
                    st.push(cos(a));
            }
            else
            {
                double a, b;
                if (!st.empty())
                    b = st.top();
                else
                    return ERROR;
                st.pop();

                if (!st.empty())
                    a = st.top();
                else
                    return ERROR;
                st.pop();

                switch (s.a[i].smb)
                {
                    case '+': st.push(a + b); break;
                    case '-': st.push(a - b); break;
                    case '*': st.push(a * b); break;
                    case '/': st.push(a / b); break;
                }
            }
        }
    }

    return (st.size() == 1) ? st.top() : ERROR;
}

int main()
{
    char sample[101];

    gets(sample);

    string s(sample);

    struct polish_notated res = to_polish(s);
    if (res.a[0].type == -1)
        cout << "Error" << endl;
    else
    {
        double t = calculate(res);

        if (t == ERROR)
            cout << "Error";
        else
            cout << fixed << setprecision(10) << t;
    }

    cout << endl;
}

