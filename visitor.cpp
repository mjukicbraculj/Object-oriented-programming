#include "visitor.h"

void PlainText::accept(Visitor *v)
{
    v->visitPlainText(this);
}

void BoldText::accept(Visitor *v)
{
    v->visitBoldText(this);
}

void Hyperlink::accept(Visitor *v)
{
    v->visitHyperlink(this);
}

void HtmlVisitor::visitBoldText(BoldText *ptr)
{
    std::cout << "<b>"+ptr->get_text() << "</b>";
}

void HtmlVisitor::visitPlainText(PlainText *ptr)
{
    std::cout << ptr->get_text();
}

void HtmlVisitor::visitHyperlink(Hyperlink *ptr)
{
    std::cout << "<a href=\"" +ptr->get_url() << "\">" + ptr->get_text() << "</a>";
}

void LatexVisitor::visitBoldText(BoldText *ptr)
{
    std::cout << "{\\bf "+ptr->get_text()+"}";
}

void LatexVisitor::visitPlainText(PlainText *ptr)
{
    std::cout << ptr->get_text();
}

void LatexVisitor::visitHyperlink(Hyperlink *ptr)
{
    std::cout << "\\href{"+ptr->get_url()+"}{"+ptr->get_text()+"}";
}
