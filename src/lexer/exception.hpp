/* Exception - Woden lexical analyzer exceptions
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

#ifndef WODEN_LEXER_EXCEPTION
#define WODEN_LEXER_EXCEPTION

#include "core/exception.hpp"

namespace woden::lexer {
	class exception: public core::exception {
		public:
			explicit exception(const char* message, std::size_t line)
				: core::exception(message, line) {}
	};

	class unexpected_character: public exception {
		public:
			explicit unexpected_character(std::size_t line)
				: exception("Unexpected character.", line) {}
	};

	class unterminated_string: public exception {
		public:
			explicit unterminated_string(std::size_t line)
				: exception("Unterminated string.", line) {}
	};
}

#endif // WODEN_LEXER_EXCEPTION
