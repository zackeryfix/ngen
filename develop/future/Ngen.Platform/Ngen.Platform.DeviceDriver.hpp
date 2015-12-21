

#ifndef _NGEN_PLATFORM_DEVICEDRIVER_HPP
#define _NGEN_PLATFORM_DEVICEDRIVER_HPP

namespace Ngen {
	namespace Platform {
		class Kernel;
		
		class DeviceDriver {
		public:
			DeviceDriver(const text& name, const text& vendor, const Version& version) :
				 mName(name), mVendor(vendor), mVersion(version), mIsDisabled(true) {
			}
			
			bool IsDisabled() const {
				return mIsDisabled;
			}
			
			const text& Name() const {
				return mName;
			}
			
			const text& VendorInfo() const {
				return mVendor;
			}
			
			const Version& VersionInfo() const {
				return mVersion;
			}
			
		protected:
			virtual void pDisable() const {
				mIsDisabled = true;
			}
			
			virtual void pEnable() const {
				mIsDisabled = false;
			}
			
			/** @brief Called by the kernel when an application requests a 
			 *	hardware update.  It is the drivers resposibility to detect new
			 * devices and update the states of known devices.
			 */
			virtual bool pPoll(UserInterface* ui, HardwareEventInfo* hdwinfo) {
				return !mIsDisabled;
			}
			
			
			virtual Device* pGetDevice(uwhole hashcode) const pure;
			virtual Array<Device*> pDevices() const pure;
			
			mirror mName;
			text mVendor;
			Version mVersion;
			bool mIsDisabled;
			friend class Kernel;
		};
	}
}
#endif