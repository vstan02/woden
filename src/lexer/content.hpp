/* Content - Content for the lexical analyzer
 * Copyright (C) 2023 Stan Vlad <vstan02@protonmail.com>
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
			content(char const* target)
				: _line(1), _start(target), _current(target) {}

			void skip_whitespaces();

			std::size_t line() const { return _line; }

			bool is_eof() const { return (*this)[0] == '\0'; }
			bool is_eol() const { return (*this)[0] == '\n'; }

			char const* word() const { return _start; }
			std::size_t size() const { return _current - _start; }

			char advance() { return (++_current)[-1]; }
			void start_word() { _start = _current; }

			char operator[](std::size_t index) const { return _current[index]; }
			void operator>>(std::size_t size) { _start += size; }

		private:
			std::size_t _line;
			char const* _start;
			char const* _current;

		private:
			void skip_comments();
	};
}

#endif // WODEN_LEXER_CONTENT
