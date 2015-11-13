#ifndef SCANNER_H
#define SCANNER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

/// \author qyvlik
/// \file scanner.h
/// \brief The Scanner class
/// \date 2015/11/01
/// \version 0.0.1
/// 分词器
class Scanner
{
public:
    explicit Scanner();
    virtual ~Scanner();

    class InputStream {
    public:
        explicit InputStream()
        { }

        virtual ~InputStream()
        { }

        virtual bool isOpen()const = 0;
        virtual int get() = 0;
        virtual int lineNumber() const = 0;
        virtual int columnNumber() const = 0;
        virtual std::string streamName() const = 0;
        virtual void close() = 0;
    };

    class OutputStream {
    public:
        explicit OutputStream()
        { }

        virtual ~OutputStream()
        { }

        virtual void output(const std::string& token, const std::string& value) = 0;
        virtual void error(const std::string& filename,
                           int lineNumber,
                           int columnNumber,
                           const std::string& reason) = 0;
    };

    static InputStream* getInputStream(const std::string& filename);
    static OutputStream* getOutputStream(const std::string& filename);

    void scan(InputStream* inputStream, OutputStream* outputStream);

    static bool isKeyWord(const std::string& word);

    static bool isSingleWord(char word);

    static bool isDoubleWord(char word);

    static const std::string STRING;
    static const std::string ID;
    static const std::string NUMBER;
    static const std::string KEYWORD;
    static const std::string ERROR;

protected:

    class IInputStream : public InputStream
    {
    public:
        explicit IInputStream(const std::string& filename);
        ~IInputStream();
        bool isOpen()const override;
        int get() override;
        int lineNumber() const override;
        int columnNumber() const override;
        std::string streamName() const override;
        void close()override;
    private:
        std::string m_filename;
        int m_lineNumber;
        int m_columnNumber;
        std::ifstream fread;
    };

    class IOutputStream : public OutputStream
    {
    public:
        explicit IOutputStream(const std::string& filename);
        ~IOutputStream();
        void output(const std::string& token, const std::string& value) override;
        void error(const std::string& filename,
                   int lineNumber, int columnNumber,
                   const std::string& reason) override;
    private:
        std::ofstream fwrite;
    };

    /// \brief KeyWord
    /// 关键词
    static const std::vector<std::string> KeyWord;

    /// \brief SingleWord
    /// 单分符
    static const std::vector<std::string> SingleWord;

    /// \brief DoubleWord
    /// 双分符
    static const std::vector<std::string> DoubleWord;
};

#endif // SCANNER_H
