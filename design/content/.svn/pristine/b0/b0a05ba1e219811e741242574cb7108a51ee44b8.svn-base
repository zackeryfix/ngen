#ifndef TEST_HPP_INCLUDED
#define TEST_HPP_INCLUDED


/** @brief macro documentation. */
#define macro [insert something]

/** @brief Namespace documentation. */
namespace Namespace {
	/** @brief Namespace::Subspace documentation. */
	namespace SubSpace {
		/** @brief TemplateClass documentation. */
		template<typename T> class TemplateClass {
		public:
			/** @brief TemplateClass::TemplateClass() documentation. */
			TemplateClass() {}
			/** @brief TemplateClass::VoidEmpty() documentation. */
			void VoidEmpty() {}
			/** @brief TemplateClass::NonVoid2() documentation.
			 * @param x parameter::x documentation.
			 * @param x parameter::x documentation.
			 */
			int NonVoid2(int x, int y) { return x+y; }
		protected:
			/** @brief TemplateClass::Field documentation. */
			int Field;
			/** @brief TemplateClass::FieldPointer documentation. */
			int* PointerField;
		};

		class Parent {
		public:
			Parent() {}

		protected:
			int Field;
		};

		class Child : public Parent {
		public:
			Child() {}

		protected:
			int* PointerField;
		};

		const int Constant;
		static int StaticConstant;

		template<typename T> void TemplateFunction(int x) {}

		void VoidFunction() {}
	}
}
#endif
