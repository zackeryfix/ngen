


#include "Ngen.hpp"

namespace Ngen {
	namespace Measure {
	   template<typename T>
	   class UnitOfMeasure {
	   public:
         typedef UnitOfMeasure<T> TSelf;
         typedef T TValue;

         T& Value() = 0;
         const T& Value() const = 0;
         const Mirror& Symbol() const = 0;
	   };


	   template<typename T>
	   class Kilometer : public UnitOfMeasure<T> {
      public:

	   };

	   template<typename T>
	   class Distance : public UnitOfMeasure<T> {
	   public:
	      // todo static SymbolConversionDelegate
         template<TLengthUnit>
         Distance(const TDistanceUnit& rhs) : mDistance() {
            switch(rhs.Symbol().Hashcode()) {
            case (const_mirror("km"))
            }
         }
      protected:
         Meter<T> mDistance;
	   };
	}
}

















