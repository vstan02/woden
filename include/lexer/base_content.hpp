/* Base Content - String content for the lexical analyzer
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

#ifndef WODEN_LEXER_BASE_CONTENT
#define WODEN_LEXER_BASE_CONTENT

#include "content.hpp"

namespace woden::lexer {
    class base_content: public content {
        public:
            base_content(const char* target);

            const char* word() const;
            std::size_t size() const;

            void start_word();
            char advance();
            void shift(std::size_t size);

            char operator[](std::size_t index) const;

        private:
            const char* _start;
            const char* _current;
    };
}

#endif // WODEN_LEXER_BASE_CONTENT
