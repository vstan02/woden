/* Expression - Woden expression
 * Copyright (C) 2020 Stan Vlad <vstan02@protonmail.com>
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

#ifndef WODEN_EXPRESSION_HPP
#define WODEN_EXPRESSION_HPP

#include "Token.hpp"

namespace expression {
    struct Literal;
    struct Grouping;
    struct Binary;
    struct Unary;
    struct Logical;

    template <typename Type>
    class Visitor {
        public:
            virtual Type visitLiteralExpression(Literal) = default;
            virtual Type visitGroupingExpression(Grouping) = default;
            virtual Type visitBinaryExpression(Binary) = default;
            virtual Type visitUnaryExpression(Unary) = default;
            virtual Type visitLogicalExpression(Logical) = default;
    };

    struct Expression {
        template <typename Type>
        virtual Type accept(Visitor<Type>) = default;
    };

    struct Literal: Expression {
        void* value;

        template <typename Type>
        Type accept(Visitor<Type> visitor) override {
            return visitor.visitLiteralExpression(this);
        }
    };

    struct Grouping: Expression {
        Expression target;

        template <typename Type>
        Type accept(Visitor<Type> visitor) override {
            return visitor.visitGroupingExpression(this);
        }
    };

    struct Binary: Expression {
        Token opr;
        Expression left;
        Expression right;

        template <typename Type>
        Type accept(Visitor<Type> visitor) override {
            return visitor.visitBinaryExpression(this);
        }
    };

    struct Unary: Expression {
        Token opr;
        Expression target;

        template <typename Type>
        Type accept(Visitor<Type> visitor) override {
            return visitor.visitUnaryExpression(this);
        }
    };

    struct Logical: Expression {
        Token opr;
        Expression left;
        Expression right;

        template <typename Type>
        Type accept(Visitor<Type> visitor) override {
            return visitor.visitLogicalExpression(this);
        }
    };
}

#endif // WODEN_EXPRESSION_HPP
