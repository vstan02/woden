/* Scanner - Woden lexical analyzer
 * Copyright (C) 2020 Stan Vlad <vstan02@protonmail.com>
 *
 * This file is part of Woden.
 *
 * xCalc is free software: you can redistribute it and/or modify
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

#ifndef WODEN_SCANNER_HPP
#define WODEN_SCANNER_HPP

#include <string>
#include <vector>

#include "Token.hpp"

class Scanner {
    private:
        std::string source;
        std::vector<Token> tokens;
        std::size_t start;
        std::size_t current;
        std::size_t line;

    public:
        explicit Scanner(std::string source);

        std::vector<Token> scan();

    private:
        bool isAtEnd();
        bool isDigit(char target);
        bool match(char expected);

        char peek();
        char peekNext();
        char advance();

        void addToken(Token::Type type);
        void addToken(Token::Type type, void* literal);

        void scanToken();
        void scanSlash();
        void scanString();
        void scanInteger();
        void scanOther();
};

#endif // WODEN_SCANNER_HPP
