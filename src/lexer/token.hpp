/* Token - Woden lexical tokens
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

#ifndef WODEN_LEXER_TOKEN
#define WODEN_LEXER_TOKEN

#include <cstddef>

namespace woden::lexer {
	enum token_type {
		LEFT_PAREN,
		RIGHT_PAREN,
		LEFT_BRACE,
		RIGHT_BRACE,
		LEFT_BRACKET,
		RIGHT_BRACKET,
		COMMA,
		DOT,
		MINUS,
		PLUS,
		SEMICOLON,
		SLASH,
		STAR,
		PERCENT,
		BANG,
		BANG_EQUAL,
		EQUAL,
		EQUAL_EQUAL,
		GREATER,
		GREATER_EQUAL,
		LESS,
		LESS_EQUAL,
		IDENTIFIER,
		STRING,
		NUMBER,
		AND,
		OR,
		TRUE,
		FALSE,
		NONE,
		IF,
		ELSE,
		VAR,
		FOR,
		WHILE,
		RETURN,
		FUNC,
		CLASS,
		SUPER,
		THIS,
		NEW,
		PRINT,
		PROGRAM,
		END
	};

	struct token {
		token_type type;
		const char* start;
		std::size_t size;
		std::size_t line;
	};
}

#endif // WODEN_LEXER_TOKEN
