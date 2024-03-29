/* Exception - Woden exceptions
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

#ifndef WODEN_CORE_EXCEPTION
#define WODEN_CORE_EXCEPTION

#include <stdexcept>

namespace woden::core {
	class exception: public std::runtime_error {
		public:
			explicit exception(const char* message, std::size_t line)
				: std::runtime_error(message), _line(line) {}

			std::size_t where() const noexcept { return _line; }

		private:
			std::size_t _line;
	};
}

#endif // WODEN_CORE_EXCEPTION
