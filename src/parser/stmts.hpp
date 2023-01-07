/* Stmts - Woden statements
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

#ifndef WODEN_PARSER_STMTS
#define WODEN_PARSER_STMTS

#include <vector>

#include "lexer/token.hpp"
#include "parser/exprs.hpp"

namespace woden::parser::stmts {
	enum statement_type {
    PROGRAM,
		EXPRESSION,
    PRINT,
    BLOCK
	};

	struct statement {
		statement_type type;

		statement(statement_type type): type(type) {}
	};

	struct expression: statement {
		exprs::expression* target;

		expression(exprs::expression* target)
			: statement(statement_type::EXPRESSION), target(target) {}
	};

  struct print: statement {
    std::vector<exprs::expression*> target;

    print(std::vector<exprs::expression*> target)
      : statement(statement_type::PRINT), target(target) {}
  };

  struct block: statement {
    std::vector<stmts::statement*> stmts;

    block(std::vector<stmts::statement*> stmts)
      : statement(statement_type::BLOCK), stmts(stmts) {}
  };

  struct program: statement {
    statement* block;

    program(statement* block)
      : statement(statement_type::PROGRAM), block(block) {}
  };
}

#endif // WODEN_PARSER_STMTS
