/* ScannerTest - Tests for Woden lexical analyzer
 * Copyright (C) 2020 Stan Vlad <vstan02@protonmail.com>
 *
 * This file is part of Woden.
 *
 * xCalc is free software: you can redistribute it and/or modify
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

#include <gtest/gtest.h>

#include "Scanner.hpp"

TEST(Scanner, scan) {
    Scanner scanner("program { test 56 and \"message\" }");
    auto result = scanner.scan();
    auto it = result.begin();

    EXPECT_EQ(it->type, Token::PROGRAM);
    EXPECT_EQ((++it)->type, Token::LEFT_BRACE);
    EXPECT_EQ((++it)->type, Token::IDENTIFIER);
    EXPECT_EQ((++it)->type, Token::INTEGER);
    EXPECT_EQ(*((int*)it->literal), 56);
    EXPECT_EQ((++it)->type, Token::AND);
    EXPECT_EQ((++it)->type, Token::STRING);
    EXPECT_EQ(*((std::string*)it->literal), "message");
    EXPECT_EQ((++it)->type, Token::RIGHT_BRACE);
    EXPECT_EQ((++it)->type, Token::END);
}
