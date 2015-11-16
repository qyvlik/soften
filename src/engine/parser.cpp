#include "parser.h"

#include <iostream>
#include <sstream>

using namespace std;

Parser::Parser():
    m_inputStream(nullptr),
    m_outputStream(nullptr),
    //! 以下是语法制导的部分
    labelCreator(new LabelCreator()),
    quadrupleCreator(new QuadrupleCreator())
{
}


Parser::~Parser()
{
    //! \note don't delete m_inputStream and m_outputStream

    delete labelCreator;
    delete quadrupleCreator;
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

    this->m_inputStream = inputStream;
    this->m_outputStream = outputStream;

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

    this->m_outputStream->output("DECLARA", type, id, "_");

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

    this->m_inputStream->getToken(m_tokenType, m_token);

    es = expression();                              // if 中的判断条件

    if(es > 0) {
        return es;
    }

    if(m_token != ")") {                            // 缺少 ')'
        return (es = 6);
    }

    this->m_inputStream->getToken(m_tokenType, m_token);

    //! label[0]
    labelCreator->push();
    string label0 = labelCreator->getLabel();
    this->m_outputStream->output("GOTO", quadrupleCreator->top(),
                                 label0,          // label[0]
                                 label0 +"#1");   // label[1]
    //  label[1] = label[0] + label[0][label[0].length-1]

    this->m_outputStream->output("LABEL", label0 , ":", "");

    //! 条件为真时的执行语句
    es = statement();

    if(es > 0 ) {
        return es;
    }

    //! label[1]
    labelCreator->push();

    this->m_outputStream->output("LABEL", labelCreator->getLabel(),":","");

    this->m_inputStream->getToken(m_tokenType, m_token);

    if(m_token == "else") {                             // else 部分处理

        this->m_inputStream->getToken(m_tokenType, m_token);

        //! 条件为假时的执行语句
        es = statement();

        if(es > 0) {
            return es;
        }
    }

    labelCreator->pop();
    labelCreator->pop();

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

    labelCreator->push();
    string label0 = labelCreator->getLabel();

    // this->printPos();
    this->m_outputStream->output("LOOP_START_LABEL", label0,":","");

    this->m_inputStream->getToken(m_tokenType, m_token);

    //! while 循环跳出条件判断
    es = expression();

    this->m_outputStream->output("LOOP_GOTO",
                                 quadrupleCreator->top(),
                                 label0+"#1",
                                 label0+"#2");

    if(es > 0) {
        return es;
    }

    if(m_token != ")") {                                 // 缺少 ')'
        return (es = 6);
    }

    //! label[1]
    //! while 循环体
    labelCreator->push();
    this->m_outputStream->output("LOOP_BODY_LABEL", labelCreator->getLabel(), ":", "");

    this->m_inputStream->getToken(m_tokenType, m_token);

    es = statement();

    this->m_outputStream->output("LOOP_JUMP", label0, "", "");

    //! label[2]
    //! 跳出while循环
    labelCreator->push();
    this->m_outputStream->output("LOOP_END_LABEL", labelCreator->getLabel(),":","");


    labelCreator->pop();
    labelCreator->pop();
    labelCreator->pop();

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

    labelCreator->push();
    string label0 = labelCreator->getLabel();
    this->m_outputStream->output("LOOP_START_LABEL", label0,":","");

    this->m_inputStream->getToken(m_tokenType, m_token);

    es = expression();

    this->m_outputStream->output("LOOP_GOTO",
                                 quadrupleCreator->top(),
                                 label0+"#1",
                                 label0+"#2");

    if(es > 0) {
        return es;
    }

    if(m_token != ";") {                                 // 缺少 ';'
        return (es = 4);
    }

    //! step
    //! label[1]
    labelCreator->push();
    this->m_outputStream->output("LOOP_BODY_LABEL", labelCreator->getLabel(),":","");

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

    this->m_outputStream->output("LOOP_JUMP", label0, "", "");

    //! label[2]
    //! 跳出for循环
    labelCreator->push();
    this->m_outputStream->output("LOOP_END_LABEL", labelCreator->getLabel(),":","");

    labelCreator->pop();
    labelCreator->pop();
    labelCreator->pop();

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

        cout << "clear temp" << endl;

        this->m_inputStream->getToken(m_tokenType, m_token);
        return es;
    }

    es = expression();

    if(es > 0) {
        return es;
    }

    if(es == 0 && m_token == ";" ) {

        cout << "clear temp" << endl;

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

        //! 将单因子push到四元式中
        quadrupleCreator->push(m_token);

        fileadd = this->m_inputStream->tell();              // 记住文件当前位置

        this->m_inputStream->getToken(tokenType, token);

        if(tokenType == "=") {

            // 生成四元式时记录下操作符


            this->m_inputStream->getToken(m_tokenType, m_token);

            es = bool_expr();

            if(es > 0) {
                return es;
            }

            // 向输出流输出四元式
            // = z, , 临时值
            quadrupleCreator->setOperation(tokenType);
            quadrupleCreator->outputQuadruple(this->m_outputStream);
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


// <布尔表达式> ::= <算数表达式> | <算术表达式> (> | < | >= | <= | == | !=)
// <bool_expr> ::= <additive_expr> | <additive_expr> (> | < | >= | <= | == | !=) <additive_expr>
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

        string op = m_token;

        this->m_inputStream->getToken(m_tokenType, m_token);

        es = additive_expr();

        // 生成四元式时记录下操作符
        // 向输出流输出四元式
        quadrupleCreator->setOperation(op);
        quadrupleCreator->outputQuadruple(this->m_outputStream);

        if(es > 0) {
            return es;
        }
    }
    return es;
}

// <算术表达式> ::= <项>{(+ | -) <项>}
// <additive_expr> ::= <term>{(+ | -)<term>}
int Parser::additive_expr()
{
    int es = 0;

    es = term();

    if(es > 0) {
        return es;
    }

    while(m_token == "+" || m_token == "-") {
        string op = m_token;
        this->m_inputStream->getToken(m_tokenType, m_token);

        es = term();

        if(es > 0) {
            return es;
        }
        // 生成四元式时记录下操作符
        // 向输出流输出四元式
        quadrupleCreator->setOperation(op);
        quadrupleCreator->outputQuadruple(this->m_outputStream);

    }

    return es;
}

// <项> ::= <因子> {（* | / | %）<因子>}
// <term> ::= <factor> {(* | / | %)<factor>}
int Parser::term()
{
    int es = 0;

    es = factor();

    if(es > 0) {
        return es;
    }

    while(m_token == "*" || m_token == "/" || m_token == "%") {

        string op = m_token;

        this->m_inputStream->getToken(m_tokenType, m_token);

        es = factor();

        if(es > 0) {
            return es;
        }

        // 生成四元式时记录下操作符
        // 向输出流输出四元式
        quadrupleCreator->setOperation(op);
        quadrupleCreator->outputQuadruple(this->m_outputStream);

    }

    return es;
}

// <因子> ::= (<表达式> | <标识符> | <无符号整数>)
// <factor> ::= (<expression>) | ID | NUM
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
            //! 将单因子push到四元式中
            quadrupleCreator->push(m_token);

            this->m_inputStream->getToken(m_tokenType, m_token);

            return es;
        } else {
            return (es = 7);
        }
    }
    return es;
}


//////////////////////////////////////////////////////////////////////////
////////////////////////Parser::IInputStream//////////////////////////////
//////////////////////////////////////////////////////////////////////////

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
    fwriter(
        filename
        , ios_base::binary | ios_base::in
        )
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

//////////////////////////////Parser::QuadrupleCreator////////////////////////////////////

Parser::QuadrupleCreator::QuadrupleCreator():
    tempName(0)
{
}

Parser::QuadrupleCreator::~QuadrupleCreator()
{
}


void Parser::QuadrupleCreator::push(const string &token)
{
    stack.push_back(token);
}


void Parser::QuadrupleCreator::pop()
{
    if(!stack.empty()) {
        stack.pop_back();
    }
}


string Parser::QuadrupleCreator::top()
{
    return stack.back();
}


string Parser::QuadrupleCreator::getTempVarName()
{
    stringstream ss;
    string s;
    ss << tempName;
    ++tempName;
    ss >> s;
    s = "$" + s;
    return s;
}


void Parser::QuadrupleCreator::outputQuadruple(Parser::OutputStream *outputStream)
{
    if(this->operation != "=") {
        string a1 = this->top();
        this->pop();
        string a0 = this->top();
        this->pop();
        this->push(this->getTempVarName());
        outputStream->output(this->operation, a0, a1, this->top());
    } else if(this->operation == "=") {
        string a0 = this->top();
        this->pop();
        outputStream->output(this->operation, a0, "_", this->top());
    }
}


void Parser::QuadrupleCreator::setOperation(const string &value)
{
    this->operation = value;
}


///////////////////////////////Parser::LabelCreator////////////////////////////////////

Parser::LabelCreator::LabelCreator():
    labelCount(0)
{

}


Parser::LabelCreator::~LabelCreator()
{

}


void Parser::LabelCreator::push()
{
    parts.push_back(labelCount++);
}


void Parser::LabelCreator::pop()
{
    parts.pop_back();
}


string Parser::LabelCreator::getLabel()
{
    stringstream ss;

    auto iter = parts.begin();
    auto end = parts.end();
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
