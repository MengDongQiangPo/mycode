#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

/*关键词*/
char keyWord[11][7] = { "void","int","float","char","if","else",
                        "while","do","for","return","main" };
int keyNum[11] = { 3,4,5,6,7,8,9,10,11,12,13 };
char txtStr[2000];
int strs = 0;

/*判断并返回关键词*/
int isKey(char keyStr[])
{
	int i;
	for (i = 0; i <= 11; i++)
	{
		if (strcmp(keyStr, keyWord[i]) == 0)
		{
			return keyNum[i];
		}
	}

	return 1;
}
/*判断数字*/
int isNum(char c) 
{
	return (c >= '0' && c <= '9');
}
/*判断字母*/
int isWord(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}
/*判断空*/
int isSpace(char c) 
{
	return (c == ' ' || c == '\t' || c == '\n');
}
/*判断标识符*/
int isChar(char c) 
{
	return isWord(c) || isNum(c) || c == '_';
}
/*返回字符*/
char Getchar()
{
    return txtStr[strs++];
}

/*识别*/
int main()
{
    int line = 1, rNum, strNum = 0, numNumber, erLine[20], eri = 0, i;
    char c;
    char str[50];
    char buff = 0;
    int lastLine = 0;

    ifstream fin;

    fin.open("F:/cifa.txt", ios::in);
   /* if (!fin.is_open())
    {
        cout << "无法找到这个文件！" << endl;
        return 0;
    }*/
    i = 0;
    do //((buff = fin.get()) != EOF)
    {
        buff = cin.get();
        txtStr[i++] = buff;
    } while (buff != '#');
    //fin.close();

    while (1)
    {
        c = Getchar();
        if (c == '#')
        {
            break;
        }
        if (isSpace(c))//是空
        {
            if (c == '\n' && lastLine)//如果这行不是空并且这个字符是回车
            {
                line++;//行数加一
                lastLine = 0;//本行暂时为空
                cout << '\n';//输出回车
            }
            continue;//继续读取字符
        }

        lastLine = 1;

        if (isWord(c))//是字母
        {
            str[strNum++] = c;
            c = Getchar();
            while (isChar(c))
            {
                str[strNum++] = c;
                c = Getchar();
            }
            str[strNum] = '\0';
            strs--;//退回字符
            strNum = 0;

            rNum = isKey(str);

            if (rNum != 1)
            {
                cout << "<" << rNum << ",->,";
            }
            else
            {
                cout << "<" << rNum << "," << str << ">,";
            }
        }
        else if (isNum(c))
        {
            numNumber = c - '0';
            c = Getchar();
            while (isNum(c))
            {
                numNumber = numNumber * 10 + (c - '0');
                c = Getchar();
            }
            strs--;

            if (isWord(c) || c == '_')
            {
                cout << "LexicalError,";
                erLine[eri++] = line;
                c = Getchar();
                while (c != ' ')
                {
                    c = Getchar();
                }
                strs--;
                continue;
            }
            cout << "<" << 2 << "," << numNumber << ">,";
        }
        else
        {
            switch (c)
            {
            case '+':
                cout << "<" << 14 << ",->,";
                break;
            case '-':
                cout << "<" << 15 << ",->,";
                break;
            case '*':
                cout << "<" << 16 << ",->,";
                break;
            case '/':
                c = Getchar();
                if (c == '/')
                {
                    c = Getchar();
                    while (c != '\n')
                    {
                        c = Getchar();
                    }
                   
                }
                else if (c == '*') {
                    c = Getchar();
                    while (c != '*' || Getchar() != '/')
                    {        
                        c = Getchar();
                    }
                    c = Getchar();
                    if (c != '\n') {
                        strs--;
                    }
                }
                else {
                    cout << "<" << 17 << ",->,";
                    strs--;
                }
                break;
            case '%':
                cout << "<" << 18 << ",->,";
                break;
            case '(':
                cout << "<" << 28 << ",->,";
                break;
            case ')':
                cout << "<" << 29 << ",->,";
                break;
            case '{':
                cout << "<" << 32 << ",->,";
                break;
            case '}':
                cout << "<" << 33 << ",->,";
                break;
            case '[':
                cout << "<" << 30 << ",->,";
                break;
            case ']':
                cout << "<" << 31 << ",->,";
                break;
            case ';':
                cout << "<" << 34 << ",->,";
                break;
            case ',':
                cout << "<" << 35 << ",->,";
                break;
            case '<':
                c = Getchar();
                if (c == '=') {
                    cout << "<" << 20 << ",->,";
                }
                else {
                    cout << "<" << 19 << ",->,";
                    strs--;
                }
                break;
            case '>':
                c = Getchar();
                if (c == '=') {
                    cout << "<" << 22 << ",->,";
                }
                else {
                    cout << "<" << 21 << ",->,";
                    strs--;
                }
                break;
            case '=':
                c = Getchar();
                if (c == '=') {
                    cout << "<" << 23 << ",->,";
                }
                else {
                    cout << "<" << 27 << ",->,";
                    strs--;
                }
                break;
            case '!':
                c = Getchar();
                if (c == '=') {
                    cout << "<" << 24 << ",->,";
                }
                break;
            case '&':
                c = Getchar();
                if (c == '&') {
                    cout << "<" << 25 << ",->,";
                }
                else {
                    strs--;
                }
                break;
            case '|':
                c = Getchar();
                if (c == '|') {
                    cout << "<" << 26 << ",->,";
                }
                else {
                    strs--;
                }
                break;
            }
        }
    }

    if (eri > 0)
    {
        cout << "LexicalError(s) on line(s) ";
        for (i = 0; i < eri; i++)
        {
            cout << erLine[i] << ",";
        }
    }

    return 0;
}