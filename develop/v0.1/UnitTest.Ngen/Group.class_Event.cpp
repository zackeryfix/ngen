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

t_testgroup(class_Event);

/*
t_begin_test(class_Event, Subscribe5Invoke) [] (TestResult& result) {
	auto func = StaticDelegate<>([] () {
		Console::WriteLine("F.T.W.!");
	});

	Event e = Event();
	Delegate* d = (Delegate*)&func;

	e += Event::Subscriber(0, d);
	e += Event::Subscriber(0, d);
	e += Event::Subscriber(0, d);
	e += Event::Subscriber(0, d);
	e += Event::Subscriber(0, d);
	if(e.Length() != 5) {
		result.Error("Failed to correctly subscribe from event!");
	}
	e.Invoke<void_t>();

	e -= Event::Subscriber(0, d);
	e -= Event::Subscriber(0, d);
	if(e.Length() != 3) {
		result.Error("Failed to correctly unsubscribe from event!");
	}
	e.Invoke<void_t>();
}
t_end_test
*/

