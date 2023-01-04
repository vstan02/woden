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

#include "visitor/translator.hpp"

namespace woden::visitor {
	translator::translator(const parser::parser& parser): visitor(parser) {}

	std::ostream& operator<<(std::ostream& out, translator& target) {
		return target.translate(out);
	}

	std::ostream& translator::translate(std::ostream& out) {
		if (_root == nullptr) {
			_root = _target.expression();
		}

		return translate_expression(out, _root) << '\n';
	}

	std::ostream& translator::translate_expression(std::ostream& out, parser::exprs::expression* node) {
		using namespace parser;
		using type = exprs::expression_type;
		switch (node->type) {
			case type::ASSIGN:
				return translate_assign_expression(out, static_cast<exprs::assign*>(node));
			case type::BINARY:
				return translate_binary_expression(out, static_cast<exprs::binary*>(node));
			case type::UNARY:
				return translate_unary_expression(out, static_cast<exprs::unary*>(node));
			case type::GROUPING:
				return translate_grouping_expression(out, static_cast<exprs::grouping*>(node));
			case type::LITERAL:
				return translate_literal_expression(out, static_cast<exprs::literal*>(node));
			case type::VARIABLE:
				return translate_variable_expression(out, static_cast<exprs::variable*>(node));
			default:
				return out;
		}
	}

	std::ostream& translator::translate_assign_expression(std::ostream& out, parser::exprs::assign* node) {
		out << std::string(node->name.start, node->name.size) << " = "; 
		return translate_expression(out, node->value);
	}

	std::ostream& translator::translate_binary_expression(std::ostream& out, parser::exprs::binary* node) {
		translate_expression(out, node->left) << ' ' << std::string(node->operation.start, node->operation.size) << ' ';
		return translate_expression(out, node->right);
	}

	std::ostream& translator::translate_unary_expression(std::ostream& out, parser::exprs::unary* node) {
		out << std::string(node->operation.start, node->operation.size);
		return translate_expression(out, node->target);
	}

	std::ostream& translator::translate_literal_expression(std::ostream& out, parser::exprs::literal* node) {
		using type = lexer::token_type;
		switch (node->value.type) {
			case type::NONE:
				return out << "nullptr";
			case type::TRUE:
				return out << "true";
			case type::FALSE:
				return out << "false";
			case type::NUMBER:
				return out << std::string(node->value.start, node->value.size);
			case type::STRING:
				return out << '"' << std::string(node->value.start, node->value.size) << '"';
			default: 
				return out;
		}
	}

	std::ostream& translator::translate_variable_expression(std::ostream& out, parser::exprs::variable* node) {
		return out << std::string(node->name.start, node->name.size);
	}

	std::ostream& translator::translate_grouping_expression(std::ostream& out, parser::exprs::grouping* node) {
		return translate_expression(out << '(', node->target) << ')';
	}
}
