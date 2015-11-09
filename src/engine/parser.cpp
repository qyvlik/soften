#include "parser.h"

#include <iostream>
#include <sstream>

using namespace std;

Parser::Parser():
    m_inputStream(nullptr),
    m_outputStream(nullptr),
    m_labelCount(0)
{
}


Parser::~Parser()
{
    //! \note don't delete m_inputStream and m_outputStream
}


Parser::InputStream *Parser::getInputStream(const string &filename)
{
    return new IInputStream(filename);
}


Parser::OutputStream *Parser::getOutputStream(const string &filename)
{
    return new IOutputStream(filename);
}


int Parser::parse(Parser::InputStream *inputStream, Parser::OutputStream *outputStream)
{
    int es = 0;

    m_inputStream = inputStream;
    m_outputStream = outputStream;

    if(es == 0) {
        es = program();
    }

    printf("\n============program result=============\n");

    switch(es)
    {
    case 0: printf("success\n"); break;
    case 1: printf("lost { !\n"); break;
    case 2: printf("lost } !\n"); break;
    case 3: printf("lost Token !\n"); break;
    case 4: printf("lost ; !\n"); break;
    case 5: printf("lost ( !\n"); break;
    case 6: printf("lost ) !\n"); break;
    case 7: printf("lost Number !\n"); break;
    }
    return es;
}


int Parser::program()
{
    int es = 0;


    this->m_inputStream->getToken(m_tokenType, m_token);

    if(m_token != "{") {
        return es=1;
    }

    this->m_inputStream->getToken(m_tokenType, m_token);

    //////////////////////////
    cout << "program :" << endl;

    while(!this->m_inputStream->isEnd()) {

        es = declaration_list();
        if(es > 0) {
            return es;
        }

        es = statement_list();
        if(es >0 ){
            return es;
        }

        if(m_token != "}") {
            return es=2;
        }
        this->m_inputStream->getToken(m_tokenType, m_token);
    }

    cout << "program end :" << endl;


    return es;
}


int Parser::declaration_list()
{
    int es = 0;
    while(m_token == "int" ||
          m_token == "double" ||
          m_token == "float" ||
          m_token == "var" ||
          m_token == "long" )
    {
        es = declaration_stat();
        if(es > 0) {
            return es;
        }
    }
    return es;
}


int Parser::declaration_stat()
{
    int es = 0;

    string type = m_token;

    this->m_inputStream->getToken(m_tokenType, m_token);

    if(m_tokenType != "ID"){                   // 不是标识符
        return (es = 3);
    }

    string id = m_token;


    this->m_inputStream->getToken(m_tokenType, m_token);

    if(m_token != ";"){
        return (es = 4);
    }

    cout << type << " "<< id << endl;

    this->m_inputStream->getToken(m_tokenType, m_token);

    return es;
}


int Parser::statement_list()
{
    int es = 0;
    while( m_token !="}") {
        es = statement();
        if(es > 0)
            return es;
    }
    return es;
}


int Parser::statement()
{
    int es = 0;

    //! 此处的while 循环是为了处理嵌套中，并列的while if for 的解析问题。
    //! 例如：
    //! for(x = 0;
    //!    x < 100;
    //!    x = x+1) {
    //!    while(x == 0) {
    //!
    //!    while(x == 0) {
    //!    }
    //!}

    while(es == 0 && (
              m_token == "if" ||
              m_token == "while" ||
              m_token == "for"
              ))
    {
        if(es == 0 && m_token == "if") {
            es = if_stat();
        }

        // 添加 else

        if(es == 0 &&  m_token == "while") {
            es = while_stat();
        }

        if(es == 0 &&  m_token == "for") {
            es = for_stat();
        }


        this->m_inputStream->getToken(m_tokenType, m_token);
    }

    // 可在此处添加 do 语句

    if(es == 0 &&  m_token == "{") {
        es = compound_stat();
    }

    if(es == 0 && (m_tokenType == "ID"
                   || m_tokenType == "NUMBER"
                   || m_tokenType == "STRING"
                   || m_tokenType == "(" ) )
    {
        es = expression_stat();
    }

    return es;
}


int Parser::if_stat()
{
    //! if 只有两个跳转点
    int es = 0;

    this->m_inputStream->getToken(m_tokenType, m_token);

    if(m_token != "(") {                                 // 缺少 '('
        return (es = 5);
    }

    //! label[0]
    m_pos.push_back(m_labelCount++);
    //this->printPos();
    this->m_outputStream->output("if First LABEL", this->getPosString(),":","");

    this->m_inputStream->getToken(m_tokenType, m_token);

    es = expression();                              // if 中的判断条件

    if(es > 0) {
        return es;
    }

    if(m_token != ")") {                            // 缺少 ')'
        return (es = 6);
    }

    this->m_inputStream->getToken(m_tokenType, m_token);


    //! 条件为真时的执行语句
    es = statement();

    if(es > 0 ) {
        return es;
    }

    //! label[1]
    m_pos.push_back(m_labelCount++);
    //this->printPos();
    this->m_outputStream->output("if second LABEL", this->getPosString(),":","");

    this->m_inputStream->getToken(m_tokenType, m_token);

    if(m_token == "else") {                             // else 部分处理

//        //! label[2]
//        m_pos.push_back(m_labelCount++);
//        // this->printPos();
//        this->m_outputStream->output("LABEL", this->getPosString(),":","");
//        m_pos.pop_back();

        this->m_inputStream->getToken(m_tokenType, m_token);

        //! 条件为假时的执行语句
        es = statement();

        if(es > 0) {
            return es;
        }
    }

    m_pos.pop_back();
    m_pos.pop_back();

    return es;
}


int Parser::while_stat()
{
    int es = 0;

    this->m_inputStream->getToken(m_tokenType, m_token);

    if(m_token != "(") {                                 // 缺少 '('
        return (es = 5);
    }

    //! label[0]
    //! while 循环的真假比较
    m_pos.push_back(m_labelCount++);
    // this->printPos();
    this->m_outputStream->output("while First LABEL", this->getPosString(),":","");

    this->m_inputStream->getToken(m_tokenType, m_token);


    es = expression();

    if(es > 0) {
        return es;
    }

    if(m_token != ")") {                                 // 缺少 ')'
        return (es = 6);
    }

    //! label[1]
    //! while 循环体
    m_pos.push_back(m_labelCount++);
    // this->printPos();
    this->m_outputStream->output("while Second LABEL", this->getPosString(),":","");

    this->m_inputStream->getToken(m_tokenType, m_token);

    es = statement();

    //! label[2]
    //! 跳出while循环
    m_pos.push_back(m_labelCount++);
    // this->printPos();
    this->m_outputStream->output("while thrid LABEL", this->getPosString(),":","");

    m_pos.pop_back();
    m_pos.pop_back();
    m_pos.pop_back();

    return es;
}


int Parser::for_stat()
{
    int es = 0;

    this->m_inputStream->getToken(m_tokenType, m_token);

    if(m_token != "(") {                                 // 缺少 '('
        return (es = 5);
    }

    this->m_inputStream->getToken(m_tokenType, m_token);

    es = expression();

    if(es > 0) {
        return es;
    }

    if(m_token != ";") {                                 // 缺少 ';'
        return (es = 4);
    }

    //! compare
    //! label[0]
    m_pos.push_back(m_labelCount++);
    // this->printPos();
    this->m_outputStream->output("for first LABEL", this->getPosString(),":","");

    this->m_inputStream->getToken(m_tokenType, m_token);

    es = expression();

    if(es > 0) {
        return es;
    }

    if(m_token != ";") {                                 // 缺少 ';'
        return (es = 4);
    }

    //! step
    //! label[1]
    m_pos.push_back(m_labelCount++);
    // this->printPos();
    this->m_outputStream->output("LABEL", this->getPosString(),":","");

    this->m_inputStream->getToken(m_tokenType, m_token);

    es = expression();

    if(es > 0) {
        return es;
    }

    if(m_token != ")") {                                 // 缺少 ')'
        return (es = 6);
    }

    this->m_inputStream->getToken(m_tokenType, m_token);

    es = statement();

    //! label[2]
    //! 跳出for循环
    m_pos.push_back(m_labelCount++);
    // this->printPos();
    this->m_outputStream->output("LABEL", this->getPosString(),":","");

    m_pos.pop_back();
    m_pos.pop_back();
    m_pos.pop_back();

    return es;
}


int Parser::compound_stat()
{
    int es = 0;

    this->m_inputStream->getToken(m_tokenType, m_token);

    es = statement_list();
    return es;
}


int Parser::expression_stat()
{
    int es = 0;

    if(m_token == ";") {
        this->m_inputStream->getToken(m_tokenType, m_token);
        return es;
    }

    es = expression();

    if(es > 0) {
        return es;
    }

    if(es == 0 && m_token == ";" ) {
        this->m_inputStream->getToken(m_tokenType, m_token);
        return es;
    } else {
        return (es = 4);                                // 缺少 ';'
    }
}


int Parser::expression()
{
    int es = 0;
    int fileadd = 0;

    string tokenType, token;

    if(m_tokenType == "ID") {
        fileadd = this->m_inputStream->tell();              // 记住文件当前位置

        this->m_inputStream->getToken(tokenType, token);

        if(tokenType == "=") {
            this->m_inputStream->getToken(m_tokenType, m_token);

            es = bool_expr();

            if(es > 0) {
                return es;
            }
        } else {
            this->m_inputStream->seek(fileadd);              // 若非 '=', 则文件指针回退到 '=' 前的标识符

            es = bool_expr();

            if(es > 0) {
                return es;
            }
        }
    } else {

        es = bool_expr();

    }

    return es;
}


int Parser::bool_expr()
{
    int es = 0;

    es = additive_expr();

    if(es > 0) {
        return es;
    }

    if(m_token == ">"
            || m_token == ">="
            || m_token == "<"
            || m_token == "<="
            || m_token == "=="
            || m_token == "!=" ) {

        this->m_inputStream->getToken(m_tokenType, m_token);

        es = additive_expr();
        if(es > 0) {
            return es;
        }
    }
    return es;
}


int Parser::additive_expr()
{
    int es = 0;
    es = term();

    if(es > 0) {
        return es;
    }

    while(m_token == "+" || m_token == "-") {
        this->m_inputStream->getToken(m_tokenType, m_token);
        es = term();
        if(es > 0) {
            return es;
        }
    }

    return es;
}


int Parser::term()
{
    int es = 0;

    es = factor();

    if(es > 0) {
        return es;
    }

    while(m_token == "*" || m_token == "/" || m_token == "%") {
        this->m_inputStream->getToken(m_tokenType, m_token);

        cout << "PUSH a temp in stack" << endl;

        es = factor();

        if(es > 0) {
            return es;
        }

    }

    return es;
}


int Parser::factor()
{
    int es = 0;

    if(m_token == "(") {
        this->m_inputStream->getToken(m_tokenType, m_token);

        es = expression();

        if(es > 0) {
            return es;
        }

        if(m_token != ")") {                // 缺少 ')'
            return (es = 6);
        }

        this->m_inputStream->getToken(m_tokenType, m_token);
    } else {
        // ID NUMBER STRING
        if(m_tokenType == "ID"
                || m_tokenType == "NUMBER"
                || m_tokenType == "STRING")
        {
            this->m_inputStream->getToken(m_tokenType, m_token);
            return es;
        } else {
            return (es = 7);
        }
    }
    return es;
}


void Parser::printPos()
{
    auto iter = m_pos.begin();
    auto end = m_pos.end();
    while(iter != end) {
        cout << (*iter);
        iter++;
        if(iter != end) {
            cout <<  ".";
        }
    }
    cout << ":" << endl;
}


string Parser::getPosString()
{
    stringstream ss;

    auto iter = m_pos.begin();
    auto end = m_pos.end();
    while(iter != end) {
        ss << (*iter);
        iter++;
        if(iter != end) {
            ss <<  ".";
        }
    }
    string s;
    ss >> s;
    return s;
}


///////////////////////////////////////////////////////////////////////////




////////////////////////Parser::IInputStream//////////////////////////////

Parser::IInputStream::IInputStream(const string &filename):
    fread(filename
          , ios_base::binary | ios_base::in
          ),
    m_end(false)
{
}


Parser::IInputStream::~IInputStream()
{
    fread.close();
}


bool Parser::IInputStream::getToken(string &tokenType, string &token)
{
    string line;
    if(std::getline(fread, line)) {              // tokentype\ttoken

        auto pos = line.find('\t', 0);          // tokentype\ttoken '\t' is on 9

        tokenType.assign(line, 0, pos);
        token.assign(line, pos+1, line.length());

        // cout << tokenType << "\t" << token << endl;

        return true;
    } else {
        m_end = true;
        return false;
    }
}

size_t Parser::IInputStream::tell()
{
    return fread.tellg();
}


void Parser::IInputStream::seek(size_t pos)
{
    fread.seekg(pos, ios_base::beg);
}


bool Parser::IInputStream::isEnd()
{
    return m_end;
}


////////////////////////Parser::IOutputStream//////////////////////////////

Parser::IOutputStream::IOutputStream(const string &filename):
    fwriter(filename)
{

}


Parser::IOutputStream::~IOutputStream()
{
    fwriter.close();
}


void Parser::IOutputStream::output(const string &operationType,
                                   const string &arg0,
                                   const string &arg1,
                                   const string &result)
{
    // cout << operationType << " " << arg0 << " " << arg1 << " " << result << endl;
    fwriter << operationType << " " << arg0 << " " << arg1 << " " << result << endl;
}

