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

#include "parser/parser.hpp"
#include "lexer/exception.hpp"

namespace woden::parser {
	parser::parser(const lexer::lexer& lexer): _target(lexer) {
		_current = _target.next_token();
		_next = _target.next_token();
	}

	std::vector<lexer::token> parser::parse() {
		return std::vector<lexer::token>();
	}

	const exprs::expression* parser::expression() {
		return equality();
	}

	const exprs::expression* parser::equality() {
		using lexer::token_type;
		const exprs::expression* result = comparison();
		while (match({ token_type::EQUAL_EQUAL, token_type::BANG_EQUAL })) {
			result = new exprs::binary(_current, result, comparison());
		}
		return result;
	}

	const exprs::expression* parser::comparison() {
		using lexer::token_type;
		const exprs::expression* result = term();
		while (match({ token_type::GREATER, token_type::GREATER_EQUAL, token_type::LESS, token_type::LESS_EQUAL })) {
			result = new exprs::binary(_current, result, term());
		}
		return result;
	}

	const exprs::expression* parser::term() {
		using lexer::token_type;
		const exprs::expression* result = factor();
		while (match({ token_type::PLUS, token_type::MINUS })) {
			result = new exprs::binary(_current, result, factor());
		}
		return result;
	}

	const exprs::expression* parser::factor() {
		using lexer::token_type;
		const exprs::expression* result = unary();
		while (match({ token_type::STAR, token_type::SLASH })) {
			result = new exprs::binary(_current, result, unary());
		}
		return result;
	}

	const exprs::expression* parser::unary() {
		using lexer::token_type;
		if (match({ token_type::BANG, token_type::MINUS })) {
			return new exprs::unary(_current, unary());
		}
		return new exprs::literal(_current);
	}

	bool parser::at_end() const {
		return _next.type == lexer::token_type::END;
	}

	bool parser::check(lexer::token_type type) const {
		return _current.type == type;
	}

	bool parser::match(std::vector<lexer::token_type> types) {
		for (lexer::token_type type: types) {
			if (check(type)) {
				advance();
				return true;
			}
		}
		return false;
	}

	void parser::advance() {
		if (!at_end()) {
			_current = _next;
			_next = _target.next_token();
		}
	}
}
