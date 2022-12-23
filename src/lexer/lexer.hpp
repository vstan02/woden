/* Lexer - Woden lexical analyzer
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

#ifndef WODEN_LEXER_LEXER
#define WODEN_LEXER_LEXER

#include <cstddef>

#include "lexer/token.hpp"
#include "lexer/content.hpp"

namespace woden::lexer {
	class lexer {
		public:
			explicit lexer(content& code);

			token next_token();

		private:
			content& _code;

		private:
			[[nodiscard]] bool is_alpha(char) const;
			[[nodiscard]] bool is_digit(char) const;
			[[nodiscard]] bool is_alphanum(char) const;

			token_type id_token();

			token make_token(token_type);
			token make_id();
			token make_number();
			token make_string();
			token choose_token(char, token_type, token_type);
			token assert_token(char, token_type);
	};
}

#endif // WODEN_LEXER_LEXER
