/* Translator - Woden AST-to-C++ translator
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

#ifndef WODEN_VISITOR_TRANSLATOR
#define WODEN_VISITOR_TRANSLATOR

#include <ostream>

#include "parser/parser.hpp"
#include "visitor/visitor.hpp"

namespace woden::visitor {
	class translator: public visitor {
		public:
			translator(const parser::parser& parser);

			std::ostream& translate(std::ostream& out);

			friend std::ostream& operator<<(std::ostream& out, translator& target);

		private:
			[[nodiscard]] std::string tab(std::size_t deep = 0) const;

			std::ostream& translate_statement(std::ostream& out, parser::stmts::statement* node, std::size_t deep = 0);
			std::ostream& translate_expression_statement(std::ostream& out, parser::stmts::expression* node, std::size_t deep = 0);
			std::ostream& translate_print_statement(std::ostream& out, parser::stmts::print* node, std::size_t deep = 0);
			std::ostream& translate_block_statement(std::ostream& out, parser::stmts::block* node, std::size_t deep = 0);
			std::ostream& translate_program_declaration(std::ostream& out, parser::stmts::program* node, std::size_t deep = 0);

			std::ostream& translate_expression(std::ostream& out, parser::exprs::expression* node, std::size_t deep = 0);
			std::ostream& translate_assign_expression(std::ostream& out, parser::exprs::assign* node, std::size_t deep = 0);
			std::ostream& translate_binary_expression(std::ostream& out, parser::exprs::binary* node, std::size_t deep = 0);
			std::ostream& translate_unary_expression(std::ostream& out, parser::exprs::unary* node, std::size_t deep = 0);
			std::ostream& translate_literal_expression(std::ostream& out, parser::exprs::literal* node, std::size_t deep = 0);
			std::ostream& translate_variable_expression(std::ostream& out, parser::exprs::variable* node, std::size_t deep = 0);
			std::ostream& translate_grouping_expression(std::ostream& out, parser::exprs::grouping* node, std::size_t deep = 0);
	};
}

#endif // WODEN_VISITOR_TRANSLATOR
