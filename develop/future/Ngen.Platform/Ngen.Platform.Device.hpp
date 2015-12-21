

#ifndef _NGEN_HARDWARE_DEVICE_HPP
#define _NGEN_HARDWARE_DEVICE_HPP

namespace Ngen {
	namespace Hardware {
	
		class CpuSystem;
		class DeviceState;
		
		enum class EDeviceFeature {
			CHARACTER_INPUT,
			CURSOR_CONTROLING,
			MASS_STORAGE,
			VIDEO_CAPTURE,
			AUDIO_CAPTURE,
		};
		typename
		class Device {
		public:
			Device(uwhole deviceId, const text& description) :
				 mId(deviceId), mDescription(description) {
				
			}
			
			bool IsDisabled() const {
				return mIsDisabled;
			}
			
			const text& Description() const {
				return mDescription;
			}
			
			virtual DevicState* CurrentState() const pure;
			
		protected:
			virtual void Poll() pure;
			
			uwhole mId;
			text mDescription;
			friend class CpuSystem;
		};
	}
}
#endif