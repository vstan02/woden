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

#ifndef WODEN_PARSER_PARSER
#define WODEN_PARSER_PARSER

#include <cstddef>
#include <vector>
#include <memory>

#include "lexer/lexer.hpp"
#include "parser/exprs.hpp"
#include "parser/stmts.hpp"

namespace woden::parser {
	class parser {
		public:
			explicit parser(const lexer::lexer& lexer);

			std::vector<stmts::statement*> parse();

		private:
			lexer::token _current;
			lexer::token _previous;
			lexer::lexer _target;

		private:
			[[nodiscard]] bool at_end() const;
			[[nodiscard]] bool check(lexer::token_type type) const;

			void advance();
			bool match(std::vector<lexer::token_type> types);
			void consume(lexer::token_type type, const char* message);

			stmts::statement* statement();
			stmts::statement* print_statement();
			stmts::statement* block_statement();
			stmts::statement* expression_statement();
			stmts::statement* declaration();
			stmts::statement* program_declaration();

			exprs::expression* expression();
			exprs::expression* primary_expression();
			exprs::expression* unary_expression();
			exprs::expression* factor_expression();
			exprs::expression* term_expression();
			exprs::expression* comparison_expression();
			exprs::expression* equality_expression();
	};
}

#endif // WODEN_PARSER_PARSER
