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

#include <iostream>

#include "parser/parser.hpp"
#include "parser/exception.hpp"

namespace woden::parser {
	parser::parser(const lexer::lexer& lexer): _current(), _previous(), _target(lexer) {}

	std::vector<stmts::statement*> parser::parse() {
		std::vector<stmts::statement*> result;
		_current = _target.next_token();
		while (!at_end()) {
			result.push_back(declaration());
		}
		return result;
	}

	stmts::statement* parser::declaration() {
		return program_declaration();
	}

	stmts::statement* parser::program_declaration() {
		consume(lexer::token_type::PROGRAM, "Expect 'program'.");
		if (!check(lexer::token_type::LEFT_BRACE)) {
			throw exception("Expect '{' after 'program'.", _current.line);
		}
		return new stmts::program(block_statement());
	}

	stmts::statement* parser::statement() {
		using lexer::token_type;
		switch (_current.type) {
			case token_type::PRINT:
				return print_statement();
			default:
				return expression_statement();
		}
	}

	exprs::expression* parser::expression() {
		return equality_expression();
	}

	stmts::statement* parser::print_statement() {
		advance();
		exprs::expression* target = expression();
		consume(lexer::token_type::SEMICOLON, "Expect ';' after value.");
		return new stmts::print(target);
	}

	stmts::statement* parser::block_statement() {
		advance();
		std::vector<stmts::statement*> stmts;
		while (!check(lexer::token_type::RIGHT_BRACE)) {
			stmts.push_back(statement());
		}
		consume(lexer::token_type::RIGHT_BRACE, "Expect '}' after block.");
		return new stmts::block(stmts);
	}

	stmts::statement* parser::expression_statement() {
		exprs::expression* target = expression();
		consume(lexer::token_type::SEMICOLON, "Expect ';' after value.");
		return new stmts::expression(target);
	}

	exprs::expression* parser::equality_expression() {
		using lexer::token_type;
		exprs::expression* result = comparison_expression();
		while (match({ token_type::EQUAL_EQUAL, token_type::BANG_EQUAL })) {
			lexer::token token = _previous;
			result = new exprs::binary(token, result, comparison_expression());
		}
		return result;
	}

	exprs::expression* parser::comparison_expression() {
		using lexer::token_type;
		exprs::expression* result = term_expression();
		while (match({ token_type::GREATER, token_type::GREATER_EQUAL, token_type::LESS, token_type::LESS_EQUAL })) {
			lexer::token token = _previous;
			result = new exprs::binary(token, result, term_expression());
		}
		return result;
	}

	exprs::expression* parser::term_expression() {
		using lexer::token_type;
		exprs::expression* result = factor_expression();
		while (match({ token_type::PLUS, token_type::MINUS })) {
			lexer::token token = _previous;
			result = new exprs::binary(token, result, factor_expression());
		}
		return result;
	}

	exprs::expression* parser::factor_expression() {
		using lexer::token_type;
		exprs::expression* result = unary_expression();
		while (match({ token_type::STAR, token_type::SLASH })) {
			lexer::token token = _previous;
			result = new exprs::binary(token, result, unary_expression());
		}
		return result;
	}

	exprs::expression* parser::unary_expression() {
		using lexer::token_type;
		if (match({ token_type::BANG, token_type::MINUS })) {
			lexer::token token = _previous;
			return new exprs::unary(token, unary_expression());
		}
		return primary_expression();
	}

	exprs::expression* parser::primary_expression() {
		using lexer::token_type;
		if (check(token_type::IDENTIFIER)) {
			advance();
			return new exprs::variable(_previous);
		}

		if (check(token_type::LEFT_PAREN)) {
			advance();
			exprs::expression* result = expression();
			consume(lexer::token_type::RIGHT_PAREN, "Expect ')' after expression.");
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

	void parser::consume(lexer::token_type type, const char* message) {
		if (check(type)) {
			return advance();
		}
		throw exception(message, _current.line);
	}

	void parser::advance() {
		if (!at_end()) {
			_previous = _current;
			_current = _target.next_token();
		}
	}
}
