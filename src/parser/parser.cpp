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

namespace woden::parser {
	parser::parser(const lexer::lexer& lexer): _current(), _previous(), _target(lexer) {
		_previous = _current = _target.next_token(); // This line should be removed
	}

	std::vector<lexer::token> parser::parse() {
		_current = _target.next_token();
		return std::vector<lexer::token>();
	}

	exprs::expression* parser::expression() {
		return equality();
	}

	exprs::expression* parser::equality() {
		using lexer::token_type;
		exprs::expression* result = comparison();
		while (match({ token_type::EQUAL_EQUAL, token_type::BANG_EQUAL })) {
			result = new exprs::binary(_previous, result, comparison());
		}
		return result;
	}

	exprs::expression* parser::comparison() {
		using lexer::token_type;
		exprs::expression* result = term();
		while (match({ token_type::GREATER, token_type::GREATER_EQUAL, token_type::LESS, token_type::LESS_EQUAL })) {
			result = new exprs::binary(_previous, result, term());
		}
		return result;
	}

	exprs::expression* parser::term() {
		using lexer::token_type;
		exprs::expression* result = factor();
		while (match({ token_type::PLUS, token_type::MINUS })) {
			result = new exprs::binary(_previous, result, factor());
		}
		return result;
	}

	exprs::expression* parser::factor() {
		using lexer::token_type;
		exprs::expression* result = unary();
		while (match({ token_type::STAR, token_type::SLASH })) {
			result = new exprs::binary(_previous, result, unary());
		}
		return result;
	}

	exprs::expression* parser::unary() {
		using lexer::token_type;
		if (match({ token_type::BANG, token_type::MINUS })) {
			return new exprs::unary(_previous, unary());
		}
		exprs::expression* result = new exprs::literal(_current);
		advance();
		return result;
	}

	bool parser::at_end() const {
		return _current.type == lexer::token_type::END;
	}

	bool parser::check(lexer::token_type type) const {
		return !at_end() && _current.type == type;
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
			_previous = _current;
			_current = _target.next_token();
		}
	}
}
