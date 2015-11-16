/*!
  1. 支持嵌套
  2. 不支持嵌套中并列
    a. 已在 statement 函数中修复
  3. 不支持 ++ += 等操作
*/
#ifndef PARSER_H
#define PARSER_H

#include <fstream>
#include <string>
#include <stack>
#include <vector>


class Parser
{
public:

    typedef std::pair<std::string, std::string> Token;

    explicit Parser();
    virtual ~Parser();

    class InputStream {
    public:
        explicit InputStream()
        { }

        virtual ~InputStream()
        { }
        // virtual bool getToken(Token token) = 0;
        virtual bool getToken(std::string& tokenType, std::string& token) = 0;
        // 由于 tellg 与 seek
        // 还有std::getline
        // 不能很好的配合工作
        // 所以打开 ifstream 是以 ios_base::binary 打开。
        //! [使用 tellg 的一个注意点](http://blog.okbase.net/bruceteen/archive/146.html)
        //! [实战中遇到的C++流文件重置的一个大陷阱： 为什么ifstream的seekg函数无效？]
        //! (http://blog.csdn.net/stpeace/article/details/40693951)
        virtual size_t tell() = 0;
        virtual void seek(size_t pos) = 0;
        virtual bool isEnd() = 0;
    };

    class OutputStream {
    public:
        explicit OutputStream()
        { }

        virtual ~OutputStream()
        { }

        virtual void output(const std::string& operationType,
                            const std::string& arg0,
                            const std::string& arg1,
                            const std::string& result) = 0;
    };


    static InputStream* getInputStream(const std::string& filename);
    static OutputStream* getOutputStream(const std::string& filename);

    int parse(InputStream* inputStream, OutputStream* outputStream);

protected:
    // <程序> ::= <声明序列><语句序列> 这个可以出现一次或多次
    // program ::= <declaration_list><statement_list>

    int program();


    // <声明序列>::=<声明序列><声明语句> | <声明语句>
    // <declaration_list>::= <declaration_list><declaration_stat> | ε
    // <declaration_list> ::= {<declaration_stat>}

    int declaration_list();


    // <声明语句>::= <int>变量;
    // <declaration_stat>::= int | double | long | var ID;

    int declaration_stat();


    // <语句序列> ::= <语句序列><语句> | ε
    // <statement_list> ::= <statement_list><statement> | ε

    int statement_list();


    // <语句> ::= <if 语句> | <while 语句> | <for 语句> | <read 语句> | <write 语句> | <符合语句> | <表达式语句>
    // <statement> ::= <if_stat> | <while_stat> | <for_stat> | <compound_stat> | <expression_stat>

    int statement();


    // <if 语句> ::= if(<表达式>) <语句> [else <语句>]
    // <if_stat> ::= if(<expression>) <statement> [else <statement>]

    int if_stat();


    // <while 语句> ::= while(<表达式>)<语句>
    // <while_stat> ::= while(<expr>) <statement>

    int while_stat();


    // <for 语句> ::= for(<表达式>; <表达式>; <表达式>) <语句>
    // <for_stat> ::= for( <expression>; <expression> ; <expression>  ) <statemenet>

    int for_stat();

    // <复合语句> ::= <语句序列>
    // <compound_stat> := {<statement_list>}

    int compound_stat();


    // <表达式语句> ::= <表达式>; | ;
    // <expression_stat> ::= <expression>; | ;

    int expression_stat();


    // <表达式> ::= <标识符> = <布尔表达式> | <布尔表达式>
    // <expression> ::= ID = <bool_expr> | <bool_expr>

    int expression();


    // <布尔表达式> ::= <算数表达式> | <算术表达式> (> | < | >= | <= | == | !=)
    // <bool_expr> ::= <additive_expr> | <additive_expr> (> | < | >= | <= | == | !=) <additive_expr>

    int bool_expr();


    // <算术表达式> ::= <项>{(+ | -) <项>}
    // <additive_expr> ::= <term>{(+ | -)<term>}

    int additive_expr();


    // <项> ::= <因子> {（* | / | %）<因子>}
    // <term> ::= <factor> {(* | / | %)<factor>}

    int term();


    // <因子> ::= (<表达式> | <标识符> | <无符号整数>)
    // <factor> ::= (<expression>) | ID | NUM

    int factor();

protected:
    class IInputStream : public InputStream
    {
    public:
        explicit IInputStream(const std::string& filename);
        ~IInputStream();

        bool getToken(std::string &tokenType, std::string &token) override;
        size_t tell() override;
        void seek(size_t pos) override;
        bool isEnd() override;

    private:
        std::ifstream fread;
        bool m_end;
    };

    class IOutputStream : public OutputStream
    {
    public:
        explicit IOutputStream(const std::string& filename);
        ~IOutputStream();
        void output(const std::string& operationType,
                    const std::string& arg0,
                    const std::string& arg1,
                    const std::string& result) override;
    private:
        std::ofstream fwriter;
    };

    class QuadrupleCreator {
    public:
        explicit QuadrupleCreator();
        ~QuadrupleCreator();
        void push(const std::string& token);
        void outputQuadruple(Parser::OutputStream* outputStream);
        void setOperation(const std::string &value);
        std::string top();
        void pop();
        std::string getTempVarName();
    private:
        std::string operation;
        std::vector<std::string> stack;
        int tempName;
    };

    class LabelCreator {
    public:
        explicit LabelCreator();
        ~LabelCreator();
        void push();
        void pop();
        std::string getLabel();
    private:
        int labelCount;
        std::vector<int> parts;
    };

private:
    InputStream* m_inputStream;
    OutputStream* m_outputStream;

    std::string m_tokenType;
    std::string m_token;


    LabelCreator* labelCreator;
    QuadrupleCreator* quadrupleCreator;
};




#endif // PARSER_H

/*!
 ** \brief Quadruple Operation
 ** (op, arg0, arg1, result);
 **
 ** \brief Quadruple DECLARA
 **
 ** int name;
 ** DECLARA int name 0
 **
 ** int name = 0;
 ** DECLARA int name 0
 **
 ** int name = name1;
 ** DECLARA int name1 name
 **
 ** \brief Quadruple LABEL and GOTO
 ** LABLE 0 :
 ** GOTO true 1:0
 ** LABEL 1 :
*/

//! [毕业设计（论文）-基于GUI的交互式编译系统之中间代码生成器的设计与实现]
//! (http://max.book118.com/html/2015/0611/18837623.shtm)
