/*  _______    ________
    \      \  /  _____/  ____   ___
    /   |   \/   \  ____/ __ \ /   \
   /    |    \    \_\  \  ___/|   | \
   \____|__  /\______  /\___  >___| /
           \/        \/     \/    \/
The MIT License (MIT)

COPYRIGHT (C) 2016 RAZORWARE, LLC

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
using namespace Ngen::Diagnostic;

t_testgroup(class_String);

t_begin_test(class_String, HashCollision) [] (TestResult& result) {
	List<string> check;
	if(true) {
		check.Add(const_string("ngen"));
		check.Add(const_string("NGEN"));
		check.Add(const_string("negn"));
		check.Add(const_string("NEGN"));
		check.Add(const_string("f00"));
		check.Add(const_string("00f"));
		check.Add(const_string("0f0"));
		check.Add(const_string("?"));
		check.Add(const_string("??"));
		check.Add(const_string("00"));
		check.Add(const_string("ff"));
		check.Add(const_string("NGEO"));
		check.Add(const_string("NGEM"));
		check.Add(const_string("a"));
		check.Add(const_string("A"));
		check.Add(const_string("a"));
		check.Add(const_string("A"));
		check.Add(const_string("anthropologically"));
		check.Add(const_string("Christianizations"));
		check.Add(const_string("compartmentalized"));
		check.Add(const_string("compartmentalizes"));
		check.Add(const_string("comprehensibility"));
		check.Add(const_string("conceptualization"));
		check.Add(const_string("constitutionality"));
		check.Add(const_string("contradistinction"));
		check.Add(const_string("counterproductive"));
		check.Add(const_string("counterrevolution"));
		check.Add(const_string("cryptographically"));
		check.Add(const_string("deterministically"));
		check.Add(const_string("disinterestedness"));
		check.Add(const_string("electrocardiogram"));
		check.Add(const_string("electromechanical"));
		check.Add(const_string("extraordinariness"));
		check.Add(const_string("heterogeneousness"));
		check.Add(const_string("inappropriateness"));
		check.Add(const_string("incompatibilities"));
		check.Add(const_string("inconsequentially"));
		check.Add(const_string("inconsiderateness"));
		check.Add(const_string("indistinguishable"));
		check.Add(const_string("industrialization"));
		check.Add(const_string("institutionalized"));
		check.Add(const_string("institutionalizes"));
		check.Add(const_string("intercommunicated"));
		check.Add(const_string("intercommunicates"));
		check.Add(const_string("interdependencies"));
		check.Add(const_string("interdisciplinary"));
		check.Add(const_string("interrelationship"));
		check.Add(const_string("irreproducibility"));
		check.Add(const_string("lexicographically"));
		check.Add(const_string("Mediterraneanizes"));
		check.Add(const_string("microarchitecture"));
		check.Add(const_string("microinstructions"));
		check.Add(const_string("microprogrammable"));
		check.Add(const_string("miscellaneousness"));
		check.Add(const_string("misrepresentation"));
		check.Add(const_string("misunderstandings"));
		check.Add(const_string("Mohammedanization"));
		check.Add(const_string("Occidentalization"));
		check.Add(const_string("parameterizations"));
		check.Add(const_string("probabilistically"));
		check.Add(const_string("pseudoinstruction"));
		check.Add(const_string("pseudoparallelism"));
		check.Add(const_string("psychotherapeutic"));
		check.Add(const_string("reproducibilities"));
		check.Add(const_string("resynchronization"));
		check.Add(const_string("spectrophotometer"));
		check.Add(const_string("spectrophotometry"));
		check.Add(const_string("straightforwardly"));
		check.Add(const_string("telecommunication"));
		check.Add(const_string("uncontrollability"));
		check.Add(const_string("understandability"));
		check.Add(const_string("unidirectionality"));
		check.Add(const_string("antifundamentalist"));
		check.Add(const_string("autosuggestibility"));
		check.Add(const_string("characteristically"));
		check.Add(const_string("compartmentalizing"));
		check.Add(const_string("conceptualizations"));
		check.Add(const_string("consequentialities"));
		check.Add(const_string("contradistinctions"));
		check.Add(const_string("electrocardiograph"));
		check.Add(const_string("institutionalizing"));
		check.Add(const_string("interchangeability"));
		check.Add(const_string("intercommunicating"));
		check.Add(const_string("intercommunication"));
		check.Add(const_string("interrelationships"));
		check.Add(const_string("microarchitectures"));
	}

	List<string>::Node* i = check.Begin();
	while(!isnull(i)) {
		string x = i->Data();

		List<string>::Node* j = check.Begin();
		while(!isnull(j)) {
			string y = j->Data();
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

t_begin_test(class_String, Add_string) [] (TestResult& result) {
	string hello = const_string("Hello");
	string world = const_string(" World");
	string helloWorld = hello + world;

	if(helloWorld != const_string("Hello World")) {
		result.Error(const_string("string was incorrectly formatted!"));
	}
}
t_end_test

t_begin_test(class_String, Add_Char) [] (TestResult& result) {
	string str = string("A");
	str.Append('a');

	if(str != const_string("Aa")) {
		result.Error(const_string("string was incorrectly formatted."));
	}

	if(str.Length() != 3) {
		result.Error(const_string("string length is incorrect."));
	}
}
t_end_test

t_begin_test(class_String, ReadTo_Char) [] (TestResult& result) {
	string mirrorHash = const_string("0x11:0x02@0x0F=0x00|0xDF,0xFA");
	string mirrorName = const_string("Namespace:Type@void=Method|uword,float32&");

	string namspc = mirrorHash.ReadTo(':');
	string typnam = mirrorName.ReadTo('@');

	if(namspc != const_string("0x11") ||
		typnam != const_string("Namespace:Type")) {
		result.Error(const_string("string was incorrectly read."));
	}
}
t_end_test


t_begin_test(class_String, Split_Char) [] (TestResult& result) {
	string mirror = const_string("d:b");
	auto split = mirror.Split(':');

	if(split.Length() != 2) {
		result.Error(const_string("string was incorrectly split."));
		return;
	}

	if(split[0] != const_string("d")) {
		result.Error(const_string("The first token was invalid."));
	}

	if(split[1] != const_string("b")) {
		result.Error(const_string("The second token was invalid."));
	}
}
t_end_test

t_begin_test(class_String, Format_String_BufferFirst) [] (TestResult& result) {
	string format = string::Format(const_string("This is template for an unformatted string."),
                                 { const_string("the complete") });
	if(format == const_string("This is the complete template for an unformatted string.")) {
      result.Error(format);
	}
}
t_end_test

