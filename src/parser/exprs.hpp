/* Exprs - Woden expressions
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

#ifndef WODEN_PARSER_EXPRS
#define WODEN_PARSER_EXPRS

#include <memory>

#include "lexer/token.hpp"

namespace woden::parser::exprs {
	enum expression_type {
		ASSIGN,
		BINARY,
		UNARY,
		GROUPING,
		LITERAL,
		VARIABLE
	};

	struct expression {
		expression_type type;

		expression(expression_type type): type(type) {}
	};

	struct assign: expression {
		lexer::token name;
		const expression* value;

		assign(lexer::token name, const expression* value)
			: expression(expression_type::ASSIGN), name(name), value(value) {}
	};

	struct binary: expression {
		lexer::token operation;
		const expression* left;
		const expression* right;

		binary(lexer::token op, const expression* left, const expression* right)
			: expression(expression_type::BINARY), operation(op), left(left), right(right) {}
	};

	struct grouping: expression {
		const expression* target;

		grouping(const expression* target)
			: expression(expression_type::GROUPING), target(target) {}
	};

	struct literal: expression {
		lexer::token value;

		literal(lexer::token value)
			: expression(expression_type::LITERAL), value(value) {}
	};

	struct variable: expression {
		lexer::token name;

		variable(lexer::token name)
			: expression(expression_type::VARIABLE), name(name) {}
	};

	struct unary: expression {
		lexer::token operation;
		const expression* target;

		unary(lexer::token operation, const expression* target)
			: expression(expression_type::UNARY), operation(operation), target(target) {}
	};
}

#endif // WODEN_PARSER_EXPRS
