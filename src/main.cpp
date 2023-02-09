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

#include <fstream>
#include <iostream>
#include <exception>

#include "core/exception.hpp"
#include "lexer/lexer.hpp"
#include "lexer/token.hpp"
#include "parser/parser.hpp"
#include "visitor/translator.hpp"

extern int main(int argc, char** argv) {
  if (argc < 2) {
    std::cerr << "[Error]: invalid arguments.\n";
    std::cerr << "==> usage: app [file path]\n";
    return 0;
  }

  using namespace woden;
  try {
    std::ifstream file(argv[1]);
    std::string code((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

  	lexer::lexer lexer(code.c_str());
    parser::parser parser(lexer);

    visitor::translator visitor(parser);
    std::cout << visitor;
  } catch(const core::exception& error) {
    std::cerr << "[Error]: " << error.what() << '\n';
    std::cerr << "==> at line: " << error.where() << '\n';
  } catch (const std::exception& error) {
    std::cerr << "[Error]: " << error.what() << '\n';
  }
	return 0;
}
