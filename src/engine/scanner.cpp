#include "scanner.h"

using namespace std;

const std::string Scanner::STRING = "STRING";

const std::string Scanner::ID = "ID";

const std::string Scanner::NUMBER = "NUMBER";

const std::string Scanner::KEYWORD = "KEYWORD";

const std::string Scanner::ERROR = "ERROR";

const vector<string> Scanner::KeyWord = {
    "if", "else","true","false",
    "for", "while", "do",
    "switch", "case", "default",
    "return","break", "continue",
    "var", "int", "double", "float", "long",
    "class", "public", "protected", "private", "this",
    "try", "catch", "throw",
    "new", "delete", "null", "function"
};


const std::vector<std::string> Scanner::SingleWord = {
    "+", "-",
    "*", "%",                     // "/"

    "(", ")",
    "[", "]",
    "{", "}",

    ";", ",",

    "."                          //! 点域运算符
};


const std::vector<std::string> Scanner::DoubleWord = {
    ">", "<",
    "=", "!"
};


Scanner::Scanner()
{

}


Scanner::~Scanner()
{

}


Scanner::InputStream *Scanner::getInputStream(const string &filename)
{
    return new IInputStream(filename);
}

Scanner::OutputStream *Scanner::getOutputStream(const string &filename)
{
    return new IOutputStream(filename);
}


void Scanner::scan(Scanner::InputStream *inputStream, OutputStream *outputStream)
{
    string token;
    char letter;

    letter = inputStream->get();

    while(letter != EOF) {

        while(isspace(letter)) {
            letter = inputStream->get();
        }

        //! 组合标识符
        if(isalpha(letter)) {
            token.clear();
            while(isalnum(letter)) {
                token.push_back(letter);
                letter = inputStream->get();
            }
            //! 查保留字
            if(isKeyWord(token)) {
                outputStream->output(Scanner::KEYWORD, token);
            } else {
                outputStream->output(Scanner::ID, token);
            }

            //! 组合数字-无符号整型
        } else if(isdigit(letter)) {
            token.clear();

            // int dot = 0;                        // 检查遇到 '.' 的个数
            while(isdigit(letter)) {
                token.push_back(letter);
                letter = inputStream->get();
            }

            outputStream->output(Scanner::NUMBER, token);

            //! 单分符
        } else if(isSingleWord(letter)) {
            token.clear();
            token.push_back(letter);
            letter = inputStream->get();
            outputStream->output(token, token);

            //! 双分符
        } else if(isDoubleWord(letter)) {
            token.clear();
            token.push_back(letter);
            letter = inputStream->get();

            if(letter == '=') {
                token.push_back(letter);
                letter = inputStream->get();
            }
            outputStream->output(token, token);

            //! 注释处理
        } else if(letter == '/') {
            token.clear();
            if(letter == '*') {
                char letter1 = inputStream->get();
                do {
                    letter = letter1;
                    letter1 = inputStream->get();
                } while((letter != '*' || letter != '/') && letter1 != EOF);
            } else {
                token.push_back('/');
                letter = inputStream->get();
                outputStream->output(token, token);
            }

            //! 字符处理 "
        } else if(letter == '"' || letter == '\'') {
            int flag = 0;
            bool error = false;
            if(letter == '"') {
                flag = '"';
            } else {
                flag = '\'';
            }

            token.clear();


            letter = inputStream->get();
            while(letter != flag && letter != EOF) {
                //! 字符串中不允许直接出现回车，回车必须以 \n 转义
                if(letter == '\n') {
                    error = true;
                    break;
                }

                //! 转义处理
                //! 直接转义到内存中
                if(letter == '\\' ) {
                    letter = inputStream->get();
                    switch (letter)
                    {
                    case 'a':
                        token.push_back('\a'); letter = inputStream->get(); continue;
                    case 'b':
                        token.push_back('\b'); letter = inputStream->get(); continue;
                    case 'f':
                        token.push_back('\f'); letter = inputStream->get(); continue;
                    case 'n':
                        token.push_back('\n'); letter = inputStream->get(); continue;
                    case 'r':
                        token.push_back('\r'); letter = inputStream->get(); continue;
                    case 't':
                        token.push_back('\t'); letter = inputStream->get(); continue;
                    case 'v':
                        token.push_back('\v'); letter = inputStream->get(); continue;
                    case '\\':
                        token.push_back('\\'); letter = inputStream->get(); continue;
                    case '\'':
                        token.push_back('\''); letter = inputStream->get(); continue;
                    case '"':
                        token.push_back('\"'); letter = inputStream->get(); continue;
                    default:
                        break;
                    }
                }
                token.push_back(letter);
                letter = inputStream->get();
            }

            if(letter != EOF && !error) {
                outputStream->output(Scanner::STRING, token);
            } else {
                outputStream->error(Scanner::STRING,token);
                return ;
            }
            letter = inputStream->get();
        } else {
            token.clear();
            token.push_back(letter);
            letter = inputStream->get();
            outputStream->error(Scanner::ERROR,token);
        }
    }
    inputStream->close();
}


bool Scanner::isKeyWord(const string &word)
{
    for(size_t i=0; i<Scanner::KeyWord.size(); i++) {
        if(Scanner::KeyWord[i] == word) {
            return true;
        }
    }
    return false;
}


bool Scanner::isSingleWord(char word)
{
    for(size_t i=0; i<Scanner::SingleWord.size(); i++) {
        if(Scanner::SingleWord[i][0] == word) {
            return true;
        }
    }
    return false;
}


bool Scanner::isDoubleWord(char word)
{
    for(size_t i=0; i<Scanner::DoubleWord.size(); i++) {
        if(Scanner::DoubleWord[i][0] == word) {
            return true;
        }
    }
    return false;
}


/////////////////////// Scanner::IInputStream ////////////////////////////////

Scanner::IInputStream::IInputStream(const string &filename):
    fread(filename)
{
}


Scanner::IInputStream::~IInputStream()
{
    fread.close();
}


bool Scanner::IInputStream::isOpen() const
{
    return fread.is_open();
}


int Scanner::IInputStream::get()
{
    return fread.get();
}


void Scanner::IInputStream::close()
{
    fread.close();
}


Scanner::IOutputStream::IOutputStream(const string &filename):
    fwrite(filename,
           //! 由于 parser 的问题，需要处理文件的位置指针，所以输出为二进制文件最好。。。
           ios_base::out|ios_base::binary
           )
{

}

Scanner::IOutputStream::~IOutputStream()
{
    fwrite.close();
}

void Scanner::IOutputStream::output(const string &token, const string &value)
{
    // cout << token << "\t" << value << endl;
    fwrite << token << "\t" << value << endl;
}


void Scanner::IOutputStream::error(const string &token, const string &errorString)
{
    // cout << Scanner::ERROR << ":" << token << "\t" << errorString << endl;
    fwrite << Scanner::ERROR << ":" << "\t" << errorString << endl;
}
