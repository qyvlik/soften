#ifndef CHARACTERENCODINGCONVERTER_H
#define CHARACTERENCODINGCONVERTER_H

/*!
 * \title C++字符编码问题探究和中文乱码的产生
 * \url http://my.oschina.net/ybusad/blog/363139
*/

class CharacterEncodingConverter
{
public:
    typedef unsigned int U16;

    static const U16 GB2312ToUnicodeTable[][2];
    static const U16 UnicodeToGB2312Table[][2];

    static U16 UnicodeToGB2312(U16 unicode);
    static U16 GB2312ToUnicode(U16 gb2312);
};

#endif // CHARACTERENCODINGCONVERTER_H
