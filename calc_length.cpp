#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <map>
#include <stack>
#include <string>
#include <utility>
#include <iostream>
#define MAX 50
#define MAXLEN 1000
using std::map;
using std::string;
using std::pair;
using std::stack;
map<string, double> unit_map;
/* plural to singular form
 */
string unit_transform(char *s)
{
    string str(s);
    if (str == "miles")
        return "mile";
    else if (str == "inches")
        return "inch";
    else if (str == "feet")
        return "foot";
    else if (str == "faths")
        return "fath";
    else if (str == "yards")
        return "yard";
    else
        return str;
}
/* read from file and calc
 */
void calc()
{
    FILE *file = fopen("sc-input.txt", "r");
    char temp_str[MAXLEN];
    int cnt = 0;
    double meter;
    int n;
    while (1)
    {
        fgets(temp_str, sizeof(temp_str), file);
        char *equal = strchr(temp_str, '=');
        if (temp_str[0] != '1')
            break;
        string unit(strtok(temp_str + 2, " ")); 
        double val = atof(strtok(equal + 2, " "));
        pair<string, double> p(unit, val);
        unit_map.insert(p);
        memset(temp_str, '\0', sizeof(temp_str));
    }
    FILE *outfile = fopen("output.txt", "w");
    fprintf(outfile, "%s", "chengbo_ie@163.com\n");
    fprintf(outfile, "\n", NULL);
    while (fgets(temp_str, sizeof(temp_str), file))
    {
        stack<double> opr_num;
        stack<char> opr;
        temp_str[strlen(temp_str) - 1] = '\0';
        char *pos = strtok(temp_str, " ");
        while (pos != NULL)
        {
            if (pos[0] >= '0' && pos[0] <= '9')
                opr_num.push(atof(pos));
            else
                if (pos[0] >= 'a' && pos[0] <= 'z')
                {
                    double v = opr_num.top();
                    opr_num.pop();
                    string s = unit_transform(pos);
                    v *= unit_map[s];
                    opr_num.push(v);
                }
                else
                    opr.push(pos[0]);
            pos = strtok(NULL, " ");
        }
        while (!opr.empty())
        {
            double v2 = opr_num.top();
            opr_num.pop();
            double v1 = opr_num.top();
            opr_num.pop();
            char ch = opr.top();
            opr.pop();
            double rlt;
            if (ch == '+')
                rlt = v1 + v2;
            else
                rlt = v1 - v2; 
            opr_num.push(rlt);
        }
        fprintf(outfile, "%.2lf m\n", opr_num.top());
        memset(temp_str, '\0', sizeof(temp_str));
    }
    fclose(file);
    fclose(outfile);
}

int main(int argc, char **argv)
{
    calc();
    return 0;
}
