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

#ifndef WODEN_PARSER_PARSER
#define WODEN_PARSER_PARSER

#include <cstddef>

#include "lexer/lexer.hpp"

namespace woden::parser {
    class parser {
        public:
            explicit parser(const lexer::lexer& lexer);

            void compare(const lexer::token_type* token_types);

        private:
            lexer::lexer _target;
    };
}

#endif // WODEN_PARSER_PARSER
