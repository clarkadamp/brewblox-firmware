#include "ActuatorAnalogConstrained.h"
#include "ActuatorDigitalConstrained.h"
#include "FixedPoint.h"
#include "ProcessValue.h"
#include "Setpoint.h"
#include "TempSensor.h"
#include "brewblox.pb.h"
#include "cbox/ObjectBase.h"

namespace cbox {

template <>
const obj_type_t
interfaceIdImpl<ProcessValue<safe_elastic_fixed_point<11, 12, int32_t>>>()
{
    return BrewbloxFieldOptions_LinkType_ProcessValue;
}

template <>
const obj_type_t
interfaceIdImpl<TempSensor>()
{
    return BrewbloxFieldOptions_LinkType_TempSensor;
}

template <>
const obj_type_t
interfaceIdImpl<Setpoint>()
{
    return BrewbloxFieldOptions_LinkType_Setpoint;
}

template <>
const obj_type_t
interfaceIdImpl<ActuatorAnalogConstrained>()
{
    return BrewbloxFieldOptions_LinkType_ActuatorAnalog;
}

template <>
const obj_type_t
interfaceIdImpl<ActuatorDigitalConstrained>()
{
    return BrewbloxFieldOptions_LinkType_ActuatorDigital;
}

} // end namespace cbox
