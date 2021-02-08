/* Token - Woden tokens
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

#ifndef WODEN_TOKEN_HPP
#define WODEN_TOKEN_HPP

#include "string"

struct Token {
    enum Type {
        // Literals:
        TOKEN_STRING,
        TOKEN_INTEGER,

        // Keywords:
        TOKEN_AND,
        TOKEN_OR,
        TOKEN_FALSE,
        TOKEN_TRUE,
        TOKEN_PRINT,

        // Others:
        TOKEN_LEFT_PAREN,
        TOKEN_RIGHT_PAREN,
        TOKEN_DOT,
        TOKEN_MINUS,
        TOKEN_PLUS,
        TOKEN_SEMICOLON,
        TOKEN_SLASH,
        TOKEN_STAR,
        TOKEN_BANG,
        TOKEN_BANG_EQUAL,
        TOKEN_EQUAL,
        TOKEN_EQUAL_EQUAL,
        TOKEN_GREATER,
        TOKEN_GREATER_EQUAL,
        TOKEN_LESS,
        TOKEN_LESS_EQUAL,
        TOKEN_EOF
    };

    const Type type;
    const std::string lexeme;
    const std::size_t line;
};

#endif // WODEN_TOKEN_HPP
