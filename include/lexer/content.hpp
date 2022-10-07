/* Content - Content for the lexical analyzer
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

#ifndef WODEN_LEXER_CONTENT
#define WODEN_LEXER_CONTENT

#include <cstddef>

namespace woden::lexer {
    class content {
        public:
            content(): _line(1) {};

            std::size_t line() const;

            bool is_eof() const;
            bool is_eol() const;

            void skip_whitespaces();

            virtual const char* word() const = 0;
            virtual std::size_t size() const = 0;

            virtual void start_word() = 0;
            virtual char advance() = 0;
            virtual void shift(std::size_t size) = 0;

            virtual char operator[](std::size_t index) const = 0;

        protected:
            std::size_t _line;

        private:
            void skip_comments();
    };
}

#endif // WODEN_LEXER_CONTENT
