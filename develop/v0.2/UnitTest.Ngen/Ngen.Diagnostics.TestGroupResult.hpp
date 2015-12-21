#ifndef __NGEN_DIAGNOSTICS_TESTGROUPRESULT_HPP
#define __NGEN_DIAGNOSTICS_TESTGROUPRESULT_HPP

		class TestGroupResult {
		public:
			TestGroupResult() : mGroup(), mResults() {}
			TestGroupResult() : mGroup(group) : mResults() {}

			TestGroup* Group() const {
				return mGroup;
			}

			List<TestResult>* Results() const {
				return &mResults;
			}

			List<TestResult> FailedResults() const {
				List<TestResult>::Node* i = mResults.Begin();
				List<TestResult> result = List<TestResult>();

				while(!isnull(i)) {
					if(i->Data().HasFailed()) {
						result.Add(i->Data());
					}
				}

				return result;
			}

		protected:
			TestGroup* mGroup;
			List<TestResult> mResults;
		};
	}
}

#endif // __NGEN_DIAGNOSTICS_TESTGROUPRESULT_HPP
