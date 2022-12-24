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
	visitor::visitor(const parser::parser& parser): _target(parser), _root(nullptr) {}

	visitor::~visitor() {
		if (_root != nullptr) {
			dealloc_expression(_root);
		}
	}

	void visitor::dealloc_expression(parser::exprs::expression* node) {
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
