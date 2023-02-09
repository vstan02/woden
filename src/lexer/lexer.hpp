/* Lexer - Woden lexical analyzer
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

#ifndef WODEN_LEXER_LEXER
#define WODEN_LEXER_LEXER

#include <vector>
#include <string>
#include <fstream>

#include "lexer/token.hpp"
#include "lexer/content.hpp"

namespace woden::lexer {
	class lexer {
		public:
			explicit lexer(char const* code)
				: _tokens(), _code(code) {}

			explicit lexer(std::string code)
				: lexer(code.c_str()) {}

			std::vector<token> scan();

		private:
			std::vector<token> _tokens;
			content _code;

		private:
			token next_token();
			token_type id_token();

			token make_id();
			token make_number();
			token make_string();
			token choose_token(char, token_type, token_type);
			token assert_token(char, token_type);

			bool is_digit(char ch) const {
				return ch >= '0' && ch <= '9';
			}

			bool is_alphanum(char ch) const {
				return is_alpha(ch) || is_digit(ch);
			}

			bool is_alpha(char ch) const {
				return ch == '_' || (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
			}

			token make_token(token_type type) const {
				return token {
					.type = type,
					.target = std::string(_code.word(), _code.size()),
					.line = _code.line()
				};
			}
	};
}

#endif // WODEN_LEXER_LEXER
