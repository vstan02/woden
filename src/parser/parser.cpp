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
#include "parser/exception.hpp"

namespace woden::parser {
	parser::parser(const lexer::lexer& lexer): _current(), _previous(), _target(lexer) {
		_current = _target.next_token(); // This line should be removed
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
			lexer::token token = _previous;
			result = new exprs::binary(token, result, comparison());
		}
		return result;
	}

	exprs::expression* parser::comparison() {
		using lexer::token_type;
		exprs::expression* result = term();
		while (match({ token_type::GREATER, token_type::GREATER_EQUAL, token_type::LESS, token_type::LESS_EQUAL })) {
			lexer::token token = _previous;
			result = new exprs::binary(token, result, term());
		}
		return result;
	}

	exprs::expression* parser::term() {
		using lexer::token_type;
		exprs::expression* result = factor();
		while (match({ token_type::PLUS, token_type::MINUS })) {
			lexer::token token = _previous;
			result = new exprs::binary(token, result, factor());
		}
		return result;
	}

	exprs::expression* parser::factor() {
		using lexer::token_type;
		exprs::expression* result = unary();
		while (match({ token_type::STAR, token_type::SLASH })) {
			lexer::token token = _previous;
			result = new exprs::binary(token, result, unary());
		}
		return result;
	}

	exprs::expression* parser::unary() {
		using lexer::token_type;
		if (match({ token_type::BANG, token_type::MINUS })) {
			lexer::token token = _previous;
			return new exprs::unary(token, unary());
		}
		return primary();
	}

	exprs::expression* parser::primary() {
		using lexer::token_type;
		if (check(token_type::IDENTIFIER)) {
			advance();
			return new exprs::variable(_previous);
		}

		if (check(token_type::LEFT_PAREN)) {
			advance();
			exprs::expression* result = expression();
			if (!check(token_type::RIGHT_PAREN)) {
				throw exception("Expect ')' after expression.", _current.line);
			}
			advance();
			return new exprs::grouping(result);
		}
		
		advance();
		return new exprs::literal(_previous);
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
