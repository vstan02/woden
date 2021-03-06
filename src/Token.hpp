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

#ifndef WODEN_HPP
#define WODEN_HPP

#include "string"

struct Token {
    enum Type {
        // Literals:
        STRING,
        INTEGER,

        // Keywords:
        PROGRAM,
        AND,
        OR,
        FALSE,
        TRUE,
        PRINT,

        // Others:
        LEFT_PAREN,
        RIGHT_PAREN,
        LEFT_BRACE,
        RIGHT_BRACE,
        DOT,
        MINUS,
        PLUS,
        SLASH,
        STAR,
        SEMICOLON,
        BANG,
        BANG_EQUAL,
        EQUAL,
        EQUAL_EQUAL,
        GREATER,
        GREATER_EQUAL,
        LESS,
        LESS_EQUAL,
        IDENTIFIER,
        END
    };

    const Type type;
    const std::string lexeme;
    const std::size_t line;
    const void* literal;
};

#endif // WODEN_HPP
