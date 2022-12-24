/* Viewer - Woden syntax tree visitor
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

#ifndef WODEN_VISITOR_VISITOR
#define WODEN_VISITOR_VISITOR

#include "parser/parser.hpp"

namespace woden::visitor {
	class visitor {
		public:
			explicit visitor(const parser::parser& parser);
			~visitor();

		protected:
			parser::parser _target;
			parser::exprs::expression* _root;

		private:
			void dealloc_expression(parser::exprs::expression* node);
			void dealloc_assign_expression(parser::exprs::assign* node);
			void dealloc_binary_expression(parser::exprs::binary* node);
			void dealloc_unary_expression(parser::exprs::unary* node);
			void dealloc_grouping_expression(parser::exprs::grouping* node);
	};
}

#endif // WODEN_VISITOR_VISITOR
