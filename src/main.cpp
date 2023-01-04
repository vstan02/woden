/* Woden - A true Object-Oriented programming language
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

#include "lexer/lexer.hpp"
#include "lexer/token.hpp"
#include "lexer/base_content.hpp"
#include "parser/parser.hpp"
#include "visitor/ast_view.hpp"

#define CODE "!(2 * (4 + variable) == (x < 5 - 12))"

extern int main() {
	using namespace woden;
	lexer::base_content code(CODE);
	lexer::lexer lexer(code);
	parser::parser parser(lexer);
	visitor::ast_view view(parser);
	view.print();
	return 0;
}
