/* AST View - Woden syntax tree printer
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

#ifndef WODEN_VISITOR_AST_VIEW
#define WODEN_VISITOR_AST_VIEW

#include "parser/parser.hpp"
#include "visitor/visitor.hpp"

namespace woden::visitor {
	class ast_view: public visitor {
		public:
			explicit ast_view(const parser::parser& parser): visitor(parser) {}

			void print();

		private:
			[[nodiscard]] std::string tab(std::size_t deep = 0) const;

			void print_name(const char* category, const char* name);

			void print_expression(parser::exprs::expression* node, std::size_t deep = 0);
			void print_assign_expression(parser::exprs::assign* node, std::size_t deep = 0);
			void print_binary_expression(parser::exprs::binary* node, std::size_t deep = 0);
			void print_unary_expression(parser::exprs::unary* node, std::size_t deep = 0);
			void print_literal_expression(parser::exprs::literal* node, std::size_t deep = 0);
			void print_variable_expression(parser::exprs::variable* node, std::size_t deep = 0);
			void print_grouping_expression(parser::exprs::grouping* node, std::size_t deep = 0);
	};
}

#endif // WODEN_VISITOR_AST_VIEW
