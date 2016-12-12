#include <iostream>
#include <string>


class Visitor;
class DocumentPart
{
public:
    DocumentPart(std::string text):m_text(text){}
    virtual void accept(Visitor *v)=0;
    const std::string get_text() const {return m_text;}
    virtual ~DocumentPart(){}
private:
    std::string m_text;
};

class PlainText : public DocumentPart
{
public:
    PlainText(std::string text):DocumentPart(text){}
    virtual void accept(Visitor *v);
    virtual ~PlainText(){}
};

class BoldText : public DocumentPart
{
public:
    BoldText(std::string text):DocumentPart(text){}
    virtual void accept(Visitor *v);
    virtual ~BoldText(){}
};

class Hyperlink : public DocumentPart
{
public:
    Hyperlink(std::string text, std::string url) : DocumentPart(text), m_url(url){}
    virtual void accept(Visitor *v);
    const std::string get_url() const {return m_url;}
    virtual ~Hyperlink(){}
private:
    std::string m_url;
};


class Visitor
{
public:
    virtual void visitBoldText(BoldText *ptr)=0;
    virtual void visitPlainText(PlainText *ptr)=0;
    virtual void visitHyperlink(Hyperlink *ptr)=0;
    virtual ~Visitor(){}
};

class HtmlVisitor : public Visitor
{
public:
    virtual void visitBoldText(BoldText *ptr);
    virtual void visitPlainText(PlainText *ptr);
    virtual void visitHyperlink(Hyperlink *ptr);
    virtual ~HtmlVisitor(){}
};

class LatexVisitor : public Visitor
{
public:
    virtual void visitBoldText(BoldText *ptr);
    virtual void visitPlainText(PlainText *ptr);
    virtual void visitHyperlink(Hyperlink *ptr);
    virtual ~LatexVisitor(){}
};
