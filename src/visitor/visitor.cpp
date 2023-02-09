/* Visitor - Woden syntax tree visitor
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

#include "visitor/visitor.hpp"

namespace woden::visitor {
	visitor::visitor(const parser::parser& parser): _target(parser), _stmts() {}

	visitor::~visitor() {
		for (parser::stmts::statement* node: _stmts) {
			dealloc_statement(node);
		}
	}

	void visitor::dealloc_statement(parser::stmts::statement* node) {
		using namespace parser;
		using type = stmts::statement_type;
		if (node == nullptr) return;
		switch (node->type) {
			case type::EXPRESSION:
				return dealloc_expression_statement(static_cast<stmts::expression*>(node));
			case type::PRINT:	
				return dealloc_print_statement(static_cast<stmts::print*>(node));
			case type::BLOCK:	
				return dealloc_block_declaration(static_cast<stmts::block*>(node));
			case type::PROGRAM:	
				return dealloc_program_declaration(static_cast<stmts::program*>(node));
			default:
				delete node;
		}
	}

	void visitor::dealloc_program_declaration(parser::stmts::program* node) {
		dealloc_statement(node->block);
		delete node;
	}

	void visitor::dealloc_block_declaration(parser::stmts::block* block) {
		for (parser::stmts::statement* node: block->stmts) {
			dealloc_statement(node);
		}
		delete block;
	}

	void visitor::dealloc_expression_statement(parser::stmts::expression* node) {
		dealloc_expression(node->target);
		delete node;
	}

	void visitor::dealloc_print_statement(parser::stmts::print* node) {
		for (parser::exprs::expression* expr: node->target) {
			dealloc_expression(expr);
		}
		delete node;
	}

	void visitor::dealloc_expression(parser::exprs::expression* node) {
		if (node == nullptr) return;
		using namespace parser;
		using type = exprs::expression_type;
		switch (node->type) {
			case type::ASSIGN:
				return dealloc_assign_expression(static_cast<exprs::assign*>(node));
			case type::BINARY:
				return dealloc_binary_expression(static_cast<exprs::binary*>(node));
			case type::UNARY:
				return dealloc_unary_expression(static_cast<exprs::unary*>(node));
			case type::GROUPING:
				return dealloc_grouping_expression(static_cast<exprs::grouping*>(node));
			default:
				delete node;
		}
	}

	void visitor::dealloc_assign_expression(parser::exprs::assign* node) {
		dealloc_expression(node->value);
		delete node;
	}

	void visitor::dealloc_binary_expression(parser::exprs::binary* node) {
		dealloc_expression(node->left);
		dealloc_expression(node->right);
		delete node;
	}

	void visitor::dealloc_unary_expression(parser::exprs::unary* node) {
		dealloc_expression(node->target);
		delete node;
	}

	void visitor::dealloc_grouping_expression(parser::exprs::grouping* node) {
		dealloc_expression(node->target);
		delete node;
	}
}
