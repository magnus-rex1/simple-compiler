#include "ast.h"
#include "lexer.h"
#include <cassert>
#include <cstring>
#include <gtest/gtest.h>
#include <unistd.h>

std::map<char, int> BinopPrecedence;

void set_input(const char* input)
{
    // redirect to stdin
    freopen(NULL, "r", stdin);
    FILE* fp = fmemopen((void*)input, strlen(input), "r");
    stdin = fp;
}

// ===================================================
//
//                  Get token tests
//
// ===================================================
TEST(GetTokenTests, TestSkipWhiteSpace)
{
    set_input("     a");
    const auto expected = tok_identifier;
    const auto result = gettok();
    ASSERT_EQ(expected, result);
}

TEST(GetTokenTests, TestIdentifier)
{
    set_input("id");
    const auto expected = tok_identifier;
    const auto result = gettok();
    ASSERT_EQ(expected, result);
}

TEST(GetTokenTests, TestFunctionDefinition)
{
    set_input("def");
    const auto expected = tok_def;
    const auto result = gettok();
    ASSERT_EQ(expected, result);
}

TEST(GetTokenTests, TestExtern)
{
    set_input("extern");
    const auto expected = tok_extern;
    const auto result = gettok();
    ASSERT_EQ(expected, result);
}

TEST(GetTokenTests, TestNumber)
{
    set_input("2.3");
    const auto expected = tok_number;
    const auto result = gettok();
    ASSERT_EQ(expected, result);
}

TEST(GetTokenTests, TestLeftParen)
{
    set_input("(");
    const auto expected = '(';
    const auto result = gettok();
    ASSERT_EQ(expected, result);
}

TEST(GetTokenTests, TestRightParen)
{
    set_input(")");
    const auto expected = ')';
    const auto result = gettok();
    ASSERT_EQ(expected, result);
}

// ===================================================
//
//                  Parser tests
//
// ===================================================

TEST(ParserTests, TestParseNumberExpr)
{
    set_input("1.1");
    ASSERT_NE(ParseNumberExpr(), nullptr);
}

TEST(ParserTests, TestParseParenExpr)
{
    set_input("(expression)");
    getNextToken(); // Get the '('
    ASSERT_NE(ParseParenExpr(), nullptr);
}

TEST(ParserTests, TestParseIdentifierExpr)
{
    set_input("identifier");
    ASSERT_NE(ParseIdentifierExpr(), nullptr);
}

TEST(ParserTests, TestParseIdentifierExprParen)
{
    set_input("identifier(expression)");
    ASSERT_NE(ParseIdentifierExpr(), nullptr);
}

TEST(ParserTests, TestParseIdentifierExprParenArgs)
{
    set_input("identifier(left right)");
    ASSERT_NE(ParseIdentifierExpr(), nullptr);
}

TEST(ParserTests, TestParsePrimaryIdentifierExpr)
{
    set_input("identifier");
    getNextToken(); // get the identifier
    ASSERT_NE(ParsePrimary(), nullptr);
}

TEST(ParserTests, TestParsePrimaryNumberExpr)
{
    set_input("1.1");
    getNextToken(); // get the number
    ASSERT_NE(ParsePrimary(), nullptr);
}

TEST(ParserTests, TestParsePrimaryParenExpr)
{
    set_input("(expression)");
    getNextToken(); // get the parenexpr
    ASSERT_NE(ParsePrimary(), nullptr);
}

TEST(ParserTests, TestParseExpression)
{
    set_input("x + y");
    getNextToken(); // get first token
    ASSERT_NE(ParseExpression(), nullptr);
}

TEST(ParserTests, TestParsePrototype)
{
    set_input("foo(x)");
    getNextToken(); // get the parenexpr
    ASSERT_NE(ParsePrototype(), nullptr);
}

TEST(ParserTests, TestParsePrototypeArgs)
{
    set_input("foo(x y)");
    getNextToken(); // get the parenexpr
    ASSERT_NE(ParsePrototype(), nullptr);
}

TEST(ParserTests, TestParseDefinition)
{
    set_input("def foo(x) x");
    getNextToken();
    ASSERT_NE(ParseDefinition(), nullptr);
}

TEST(ParserTests, TestParseDefinitionArgs)
{
    set_input("def foo(x y) x + y");
    getNextToken();
    ASSERT_NE(ParseDefinition(), nullptr);
}

TEST(ParserTests, TestParseExtern)
{
    set_input("extern foo(x)");
    getNextToken();
    ASSERT_NE(ParseExtern(), nullptr);
}

TEST(ParserTests, TestParseTopLevelExpr)
{
    set_input("x + y");
    getNextToken(); // get the parenexpr
    ASSERT_NE(ParseTopLevelExpr(), nullptr);
}

int main(int argc, char** argv)
{
    // operator precedence
    BinopPrecedence['<'] = 10;
    BinopPrecedence['+'] = 20;
    BinopPrecedence['-'] = 20;
    BinopPrecedence['*'] = 40; // highest.

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
