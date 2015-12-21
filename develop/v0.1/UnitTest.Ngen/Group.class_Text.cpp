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

t_testgroup(class_Text);

t_begin_test(class_Text, HashCollision) [] (TestResult& result) {
	List<text> check;
	if(true) {
		check.Add(const_text("ngen"));
		check.Add(const_text("NGEN"));
		check.Add(const_text("negn"));
		check.Add(const_text("NEGN"));
		check.Add(const_text("f00"));
		check.Add(const_text("00f"));
		check.Add(const_text("0f0"));
		check.Add(const_text("?"));
		check.Add(const_text("??"));
		check.Add(const_text("00"));
		check.Add(const_text("ff"));
		check.Add(const_text("NGEO"));
		check.Add(const_text("NGEM"));
		check.Add(const_text("a"));
		check.Add(const_text("A"));
		check.Add(const_text("a"));
		check.Add(const_text("A"));
		check.Add(const_text("anthropologically"));
		check.Add(const_text("Christianizations"));
		check.Add(const_text("compartmentalized"));
		check.Add(const_text("compartmentalizes"));
		check.Add(const_text("comprehensibility"));
		check.Add(const_text("conceptualization"));
		check.Add(const_text("constitutionality"));
		check.Add(const_text("contradistinction"));
		check.Add(const_text("counterproductive"));
		check.Add(const_text("counterrevolution"));
		check.Add(const_text("cryptographically"));
		check.Add(const_text("deterministically"));
		check.Add(const_text("disinterestedness"));
		check.Add(const_text("electrocardiogram"));
		check.Add(const_text("electromechanical"));
		check.Add(const_text("extraordinariness"));
		check.Add(const_text("heterogeneousness"));
		check.Add(const_text("inappropriateness"));
		check.Add(const_text("incompatibilities"));
		check.Add(const_text("inconsequentially"));
		check.Add(const_text("inconsiderateness"));
		check.Add(const_text("indistinguishable"));
		check.Add(const_text("industrialization"));
		check.Add(const_text("institutionalized"));
		check.Add(const_text("institutionalizes"));
		check.Add(const_text("intercommunicated"));
		check.Add(const_text("intercommunicates"));
		check.Add(const_text("interdependencies"));
		check.Add(const_text("interdisciplinary"));
		check.Add(const_text("interrelationship"));
		check.Add(const_text("irreproducibility"));
		check.Add(const_text("lexicographically"));
		check.Add(const_text("Mediterraneanizes"));
		check.Add(const_text("microarchitecture"));
		check.Add(const_text("microinstructions"));
		check.Add(const_text("microprogrammable"));
		check.Add(const_text("miscellaneousness"));
		check.Add(const_text("misrepresentation"));
		check.Add(const_text("misunderstandings"));
		check.Add(const_text("Mohammedanization"));
		check.Add(const_text("Occidentalization"));
		check.Add(const_text("parameterizations"));
		check.Add(const_text("probabilistically"));
		check.Add(const_text("pseudoinstruction"));
		check.Add(const_text("pseudoparallelism"));
		check.Add(const_text("psychotherapeutic"));
		check.Add(const_text("reproducibilities"));
		check.Add(const_text("resynchronization"));
		check.Add(const_text("spectrophotometer"));
		check.Add(const_text("spectrophotometry"));
		check.Add(const_text("straightforwardly"));
		check.Add(const_text("telecommunication"));
		check.Add(const_text("uncontrollability"));
		check.Add(const_text("understandability"));
		check.Add(const_text("unidirectionality"));
		check.Add(const_text("antifundamentalist"));
		check.Add(const_text("autosuggestibility"));
		check.Add(const_text("characteristically"));
		check.Add(const_text("compartmentalizing"));
		check.Add(const_text("conceptualizations"));
		check.Add(const_text("consequentialities"));
		check.Add(const_text("contradistinctions"));
		check.Add(const_text("electrocardiograph"));
		check.Add(const_text("institutionalizing"));
		check.Add(const_text("interchangeability"));
		check.Add(const_text("intercommunicating"));
		check.Add(const_text("intercommunication"));
		check.Add(const_text("interrelationships"));
		check.Add(const_text("microarchitectures"));
	}

	List<text>::Node* i = check.Begin();
	while(!isnull(i)) {
		text x = i->Data();

		List<text>::Node* j = check.Begin();
		while(!isnull(j)) {
			text y = j->Data();

			if(x != y) {
				if (y.ToHashcode() == x.ToHashcode()) {
					result.Error("Hash-code collision was detected!");
				}
			}

			j = j->Next();
		}

		i = i->Next();
	}
}
t_end_test

t_begin_test(class_Text, Add_Text) [] (TestResult& result) {
	text hello = const_text("Hello");
	text world = const_text(" World");
	text helloWorld = hello + world;

	if(helloWorld != const_text("Hello World")) {
		result.Error(const_text("Text was incorrectly formatted!"));
	}
}
t_end_test

t_begin_test(class_Text, Add_Char) [] (TestResult& result) {
	text str = text("A");
	str.Append('a');

	if(str != const_text("Aa")) {
		result.Error(const_text("Text was incorrectly formatted."));
	}

	if(str.Length() != 3) {
		result.Error(const_text("Text length is incorrect."));
	}
}
t_end_test

t_begin_test(class_Text, ReadTo_Char) [] (TestResult& result) {
	text mirrorHash = const_text("0x11:0x02@0x0F=0x00|0xDF,0xFA");
	text mirrorName = const_text("Namespace:Type@void=Method|uword,float32&");

	text namspc = mirrorHash.ReadTo(':');
	text typnam = mirrorName.ReadTo('@');

	if(namspc != const_text("0x11") ||
		typnam != const_text("Namespace:Type")) {
		result.Error(const_text("Text was incorrectly read."));
	}
}
t_end_test


t_begin_test(class_Text, Split_Char) [] (TestResult& result) {
	text mirror = const_text("d:b");
	auto split = mirror.Split(':');

	if(split.Length() != 2) {
		result.Error(const_text("Text was incorrectly split."));
	}

	if(split[0] != const_text("d")) {
		result.Error(const_text("The first token was invalid."));
	}

	if(split[1] != const_text("b")) {
		result.Error(const_text("The second token was invalid."));
	}
}
t_end_test

