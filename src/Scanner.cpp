/* Scanner - Woden lexical analyzer
 * Copyright (C) 2020 Stan Vlad <vstan02@protonmail.com>
 *
 * This file is part of Woden.
 *
 * Woden is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 */

#include "Scanner.hpp"

#include <utility>
#include <stdexcept>

Scanner::Scanner(std::string source)
: source(std::move(source)), start(0), current(0), line(1) {}

std::vector<Token> Scanner::scan() {
    if (tokens.empty()) {
        while (!isAtEnd()) {
            start = current;
            scanToken();
        }
        addToken(Token::END);
    }

    return tokens;
}

void Scanner::scanToken() {
    char c = advance();
    switch (c) {
        case ' ':
        case '\r':
        case '\t': break;
        case '\n': line++; break;
        case '(': addToken(Token::LEFT_PAREN); break;
        case ')': addToken(Token::RIGHT_PAREN); break;
        case '{': addToken(Token::LEFT_BRACE); break;
        case '}': addToken(Token::RIGHT_BRACE); break;
        case '.': addToken(Token::DOT); break;
        case '+': addToken(Token::PLUS); break;
        case '-': addToken(Token::MINUS); break;
        case '*': addToken(Token::STAR); break;
        case ';': addToken(Token::SEMICOLON); break;
        case '=': addToken(match('=') ? Token::EQUAL_EQUAL : Token::EQUAL); break;
        case '!': addToken(match('=') ? Token::BANG_EQUAL : Token::BANG); break;
        case '<': addToken(match('=') ? Token::LESS_EQUAL : Token::LESS); break;
        case '>': addToken(match('=') ? Token::GREATER_EQUAL : Token::GREATER); break;
        case '/': scanSlash(); break;
        case '"': scanString(); break;
        default: scanOther();
    }
}

void Scanner::scanSlash() {
    if (!match('/'))
        return addToken(Token::SLASH);
    while (peek() != '\n') advance();
}

void Scanner::scanString() {
    while (peek() != '"') {
        if (isAtEnd() || peek() == '\n')
            throw std::runtime_error("Scanner::scanString - Unterminated string.");
        advance();
    }

    auto* value = new std::string(source.substr(start + 1, current - start - 1));
    advance();
    addToken(Token::STRING, value);
}

void Scanner::scanInteger() {
    while (isDigit(peek())) advance();
    int value = std::stoi(source.substr(start, (current - start)));
    addToken(Token::INTEGER, new int(value));
}

void Scanner::scanIdentifier() {
    while (isAlphaNum(peek())) advance();
    std::string text = source.substr(start, (current - start));
    auto result = keywords.find(text);
    return result != keywords.end()
        ? addToken(result->second)
        : addToken(Token::IDENTIFIER, new std::string(text));
}

void Scanner::scanOther() {
    char c = peek();
    if (isDigit(c)) {
        scanInteger();
    } else if(isAlpha(c)) {
        scanIdentifier();
    } else {
        throw std::runtime_error("Scanner::scanOther - Unexpected character.");
    }
}

void Scanner::addToken(Token::Type type) {
    addToken(type, nullptr);
}

void Scanner::addToken(Token::Type type, void* literal) {
    std::string lexeme = source.substr(start, (current - start));
    tokens.push_back(Token { type, lexeme, line, literal });
}

char Scanner::advance() {
    return source.at(++current - 1);
}

char Scanner::peek() {
    return isAtEnd() ? '\0' : source.at(current);
}

bool Scanner::match(char expected) {
    if (isAtEnd() || source.at(current) != expected) {
        return false;
    }
    ++current;
    return true;
}

bool Scanner::isAlphaNum(char target) {
    return isAlpha(target) || isDigit(target);
}

bool Scanner::isAlpha(char target) {
    return target == '_'
        || (target >= 'a' && target <= 'z')
        || (target >= 'A' && target <= 'Z');
}

bool Scanner::isDigit(char target) {
    return target >= '0' && target <= '9';
}

bool Scanner::isAtEnd() {
    return current >= source.size();
}
