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
#include <termcolor/termcolor.hpp>

#include "visitor/ast_view.hpp"

namespace woden::visitor {
	void ast_view::print() {
		if (_stmts.size() == 0) {
			_stmts = _target.parse();
		}

		std::size_t index = 0;
		std::cout << "[";
		for (parser::stmts::statement* node: _stmts) {
			if (index++ > 0) {
				std::cout << ',';
			}
			print_statement(node, 1);
		}

		if (index > 0 && index == _stmts.size()) {
			std::cout << '\n';
		}
		std::cout << "]\n";
	}

	void ast_view::print_statement(parser::stmts::statement *node, std::size_t deep) {
		using namespace parser;
		using type = stmts::statement_type;
		if (node == nullptr) return;
		std::cout << '\n';
		switch (node->type) {
			case type::EXPRESSION:
				return print_expression_statement(static_cast<stmts::expression*>(node), deep);
			case type::PRINT:
				return print_print_statement(static_cast<stmts::print*>(node), deep);
			case type::PROGRAM:
				return print_program_declaration(static_cast<stmts::program*>(node), deep);
			case type::BLOCK:
				return print_block_declaration(static_cast<stmts::block*>(node), deep);
		}
	}

	void ast_view::print_block_declaration(parser::stmts::block* block, std::size_t deep) {
		std::cout << termcolor::bright_white << tab(deep);
		print_name("Statement", "Block");
		
		std::size_t index = 0;
		std::cout << termcolor::bright_white << " [";
		for (parser::stmts::statement* node: block->stmts) {
			if (index++ > 0) {
				std::cout << ',';
			}
			print_statement(node, deep + 1);
		}

		if (index > 0 && index == _stmts.size()) {
			std::cout << '\n';
		}
		std::cout << tab(deep) << "]";
	}

	void ast_view::print_program_declaration(parser::stmts::program* node, std::size_t deep) {
		std::cout << termcolor::bright_white << tab(deep);
		print_name("Statement", "Program");
		std::cout << termcolor::bright_white << " {";
		print_statement(node->block, deep + 1);
		std::cout << '\n' << tab(deep) << '}';
	}

	void ast_view::print_expression_statement(parser::stmts::expression* node, std::size_t deep) {
		std::cout << termcolor::bright_white << tab(deep);
		print_name("Statement", "Expression");
		std::cout << termcolor::bright_white << " {\n";
		print_expression(node->target, deep + 1);
		std::cout << '\n' << tab(deep) << '}';
	}

	void ast_view::print_print_statement(parser::stmts::print* node, std::size_t deep) {
		std::cout << termcolor::bright_white << tab(deep);
		print_name("Statement", "Print");
		
		std::size_t index = 0;
		std::cout << termcolor::bright_white << " [";
		for (parser::exprs::expression* expr: node->target) {
			if (index++ > 0) {
				std::cout << ',';
			}
			print_expression(expr, deep + 1);
		}

		if (index > 0 && index == _stmts.size()) {
			std::cout << '\n';
		}
		std::cout << tab(deep) << "]";
	}

	void ast_view::print_expression(parser::exprs::expression *node, std::size_t deep) {
		using namespace parser;
		using type = exprs::expression_type;
		if (node == nullptr) return;
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
		std::cout << termcolor::bright_white << tab(deep);
		print_name("Expression", "Assign");
		std::cout << termcolor::bright_white << " {\n" << tab(deep + 1) << "'" << node->name.target << "',\n";
		print_expression(node->value, deep + 1);
		std::cout << '\n' << tab(deep) << '}';
	}

	void ast_view::print_binary_expression(parser::exprs::binary* node, std::size_t deep) {
		std::cout << termcolor::bright_white << tab(deep);
		print_name("Expression", "Binary");
		std::cout << termcolor::bright_white << " {\n" << tab(deep + 1) << "'" << node->operation.target << "',\n";
		print_expression(node->left, deep + 1);
		std::cout << ",\n";
		print_expression(node->right, deep + 1);
		std::cout << '\n' << tab(deep) << '}';
	}

	void ast_view::print_unary_expression(parser::exprs::unary* node, std::size_t deep) {
		std::cout << termcolor::bright_white << tab(deep);
		print_name("Expression", "Unary");
		std::cout << termcolor::bright_white << " {\n" << tab(deep + 1) << "'" << node->operation.target << "',\n";
		print_expression(node->target, deep + 1);
		std::cout << '\n' << tab(deep) << '}';
	}

	void ast_view::print_literal_expression(parser::exprs::literal* node, std::size_t deep) {
		std::cout << termcolor::bright_white << tab(deep);
		print_name("Expression", "Literal");
		std::cout << termcolor::bright_white << " { '" << node->value.target << "' }";
	}

	void ast_view::print_variable_expression(parser::exprs::variable* node, std::size_t deep) {
		std::cout << termcolor::bright_white << tab(deep);
		print_name("Expression", "Variable");
		std::cout << termcolor::bright_white << " { '" << node->name.target << "' }";
	}

	void ast_view::print_grouping_expression(parser::exprs::grouping* node, std::size_t deep) {
		std::cout << termcolor::bright_white << tab(deep);
		print_name("Expression", "Grouping");
		std::cout << termcolor::bright_white << " {\n";
		print_expression(node->target, deep + 1);
		std::cout << '\n' << tab(deep) << '}';
	}

	void ast_view::print_name(const char* category, const char* name) {
		std::cout << termcolor::bright_blue << category << termcolor::bright_white << "::" << termcolor::bright_yellow << name;
	}
}
