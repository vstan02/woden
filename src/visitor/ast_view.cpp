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

#include <string>
#include <iostream>

#include "visitor/ast_view.hpp"

namespace woden::visitor {
	void ast_view::print() {
		if (_root == nullptr) {
			_root = _target.expression();
		}

		print_expression(_root);
		std::cout << '\n';
	}

	void ast_view::print_expression(parser::exprs::expression *node, std::size_t deep) {
		using namespace parser;
		using type = exprs::expression_type;
		switch (node->type) {
			case type::ASSIGN:
				return print_assign_expression(static_cast<exprs::assign*>(node), deep);
			case type::BINARY:
				return print_binary_expression(static_cast<exprs::binary*>(node), deep);
			case type::UNARY:
				return print_unary_expression(static_cast<exprs::unary*>(node), deep);
			case type::GROUPING:
				return print_grouping_expression(static_cast<exprs::grouping*>(node), deep);
			case type::LITERAL:
				return print_literal_expression(static_cast<exprs::literal*>(node), deep);
			case type::VARIABLE:
				return print_variable_expression(static_cast<exprs::variable*>(node), deep);
		}
	}

	void ast_view::print_assign_expression(parser::exprs::assign* node, std::size_t deep) {
		std::string name(node->name.start, node->name.size);
		std::cout << tab(deep) << "Expression::Assign {\n" << tab(deep + 1) << "'" << name << "',\n";
		print_expression(node->value, deep + 1);
		std::cout << '\n' << tab(deep) << '}';
	}

	void ast_view::print_binary_expression(parser::exprs::binary* node, std::size_t deep) {
		std::string op(node->operation.start, node->operation.size);
		std::cout << tab(deep) << "Expression::Binary {\n" << tab(deep + 1) << "'" << op << "',\n";
		print_expression(node->left, deep + 1);
		std::cout << ",\n";
		print_expression(node->right, deep + 1);
		std::cout << '\n' << tab(deep) << '}';
	}

	void ast_view::print_unary_expression(parser::exprs::unary* node, std::size_t deep) {
		std::string op(node->operation.start, node->operation.size);
		std::cout << tab(deep) << "Expression::Unary {\n" << tab(deep + 1) << "'" << op << "',\n";
		print_expression(node->target, deep + 1);
		std::cout << '\n' << tab(deep) << '}';
	}

	void ast_view::print_literal_expression(parser::exprs::literal* node, std::size_t deep) {
		std::string value(node->value.start, node->value.size);
		std::cout << tab(deep) << "Expression::Literal { '" << value << "' }";
	}

	void ast_view::print_variable_expression(parser::exprs::variable* node, std::size_t deep) {
		std::string name(node->name.start, node->name.size);
		std::cout << tab(deep) << "Expression::Variable { '" << name << "' }";
	}

	void ast_view::print_grouping_expression(parser::exprs::grouping* node, std::size_t deep) {
		std::cout << tab(deep) << "Expression::Grouping {\n";
		print_expression(node->target, deep + 1);
		std::cout << '\n' << tab(deep) << '}';
	}

	std::string ast_view::tab(std::size_t deep) const {
		return std::string(deep * 2, ' ');
	}
}