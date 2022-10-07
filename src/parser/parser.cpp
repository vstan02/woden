/* Parser - Woden syntax analyzer
 * Copyright (C) 2021 Stan Vlad <vstan02@protonmail.com>
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

#include <iostream>

#include "parser/parser.hpp"
#include "lexer/exception.hpp"

namespace woden::parser {
    parser::parser(const lexer::lexer& lexer): _target(lexer) {}

    void parser::compare(const lexer::token_type* token_types) {
        try {
            do {
                auto token = _target.next_token();
                std::string temp(token.start, token.size);
                std::cout << ">> " << token.line << ": '" << temp << "' => ";
                std::cout << (*token_types == token.type ? "CORRECT" : "INCORRECT") << std::endl;
            } while (*(++token_types) != lexer::token_type::END);
        } catch (const lexer::exception& error) {
            std::cerr << ">> Lexing error: " << error.what() << std::endl;
            std::cerr << "------> at line: " << error.where() << std::endl;
        }
    }
}
