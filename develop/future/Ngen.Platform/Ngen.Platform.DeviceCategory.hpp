#ifndef _NGEN_PLATFORM_DEVICECATEGORY_HPP
#define _NGEN_PLATFORM_DEVICECATEGORY_HPP

#include "Ngen.Platform.Device.hpp"

namespace Ngen {
	namespace Platform {
		class Kernel;
		
		class DeviceCategory {
		public:
			DeviceCategory(const text& name) :
				 mName(name), mDevices(1) {
			}
			
		protected:
			virtual Device* pGetDevice(uwhole id) const {
				uwhole i = 0;
				
				while(i < mDevices.Length()) {
					if(mDevice[i]->Id() == id) {
						return mDevice[i];
					}
				}
			}
			
			virtual const Array<Device*> pDevices() const {
				return mDevices;
			}
			
			mirror mName;
			Array<Device*> mDevices;
			
			friend class Kernel;
		};
	}
}
#endif