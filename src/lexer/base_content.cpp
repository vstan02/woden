/* Base Content - String content for the lexical analyzer
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

#include <cstring>
#include <cstdlib>

#include "lexer/base_content.hpp"

namespace woden::lexer {
    base_content::base_content(const char *target)
        : content(), _start(target), _current(target) {}

    std::size_t base_content::size() const {
        return _current - _start;
    }

    const char* base_content::word() const {
        return _start;
    }

    char base_content::operator[](std::size_t index) const {
        return _current[index];
    }

    char base_content::advance() {
        return (++_current)[-1];
    }

    void base_content::shift(std::size_t size) {
        _start += size;
    }

    void base_content::start_word() {
        _start = _current;
    }
}
