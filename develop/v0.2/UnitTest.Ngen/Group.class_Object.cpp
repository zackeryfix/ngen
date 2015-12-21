/*  _______    ________
    \      \  /  _____/  ____   ___
    /   |   \/   \  ____/ __ \ /   \
   /    |    \    \_\  \  ___/|   | \
   \____|__  /\______  /\___  >___| /
           \/        \/     \/    \/
The MIT License (MIT)

Copyright (c) 2013 Ngeneers Inc.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/
#include "_External.hpp"

using namespace Ngen;
using namespace Ngen::Diagnostics;

t_testgroup(class_Object);

t_begin_test(class_Object, CreateFromCast) [] (TestResult& result) {
	real x = 50;
	real y = 100;

	Object obj_x = const_object(&x);
	Object obj_y = const_object(&y);

	*(obj_x.Cast<real>()) += y;
	*(obj_y.Cast<real>()) += x;

	if(x != 50 + 100) {
		result.Error("Failed to change object 'x'");
	} else if(y != 50 + 100 + 100) {
		result.Error("Failed to change object 'y'");
	}
}t_end_test

t_begin_test(class_Object, CreateFromType) [] (TestResult& result) {
	real x = 50;
	real y = 100;

	Object obj_x = const_object(&x);
	Object obj_y = const_object(&y);

	//Type* type = obj_x.GetType();
}t_end_test

t_begin_test(class_Object, StaticCall) [] (TestResult& result) {
	real x = 50;
	real y = 100;

	auto obj_x = const_object(&x);
	auto obj_y = const_object(&y);

	unknown params[2] {
		obj_x.This(),
		obj_y.This()
	};

	auto args = (unknown*)&params;
	auto staticFunc = StaticDelegate<real&, real&>([] (real& x, real& y) {
		x = 100;
		y = 100;
	});

	((Delegate*)&staticFunc)->Call<void_t, void_t, real&, real&>(0, x, y);
	((Delegate*)&staticFunc)->operator()(null, args);

	if(x != y || x != 100) {
		result.Error("Failed to invoke object delegate.");
	}
}t_end_test
