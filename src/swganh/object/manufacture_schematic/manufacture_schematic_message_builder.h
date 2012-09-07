// This file is part of SWGANH which is released under the MIT license.
// See file LICENSE or go to http://swganh.com/LICENSE

#ifndef SWGANH_OBJECT_MANUFACTURE_SCHEMATIC_MANUFACTURE_SCHEMATIC_MESSAGE_BUILDER_H_
#define SWGANH_OBJECT_MANUFACTURE_SCHEMATIC_MANUFACTURE_SCHEMATIC_MESSAGE_BUILDER_H_

#include "swganh/object/intangible/intangible_message_builder.h"

#include "manufacture_schematic.h"

namespace swganh {
namespace object {
namespace manufacture_schematic {
    typedef swganh::ValueEvent<std::shared_ptr<ManufactureSchematic>> ManufactureSchematicEvent;
    class ManufactureSchematicMessageBuilder : public swganh::object::intangible::IntangibleMessageBuilder
    {
    public:
        ManufactureSchematicMessageBuilder(swganh::EventDispatcher* dispatcher) :
            IntangibleMessageBuilder(dispatcher)
        {
            RegisterEventHandlers();
        }
        virtual void SendBaselines(const std::shared_ptr<ManufactureSchematic>& manufacture_schematic, const std::shared_ptr<swganh::observer::ObserverInterface>& observer);
        virtual void RegisterEventHandlers();
		//deltas
		static void BuildSchematicQuantityDelta(const std::shared_ptr<ManufactureSchematic>& manufacture_schematic);
		static void BuildPropertyDelta(const std::shared_ptr<ManufactureSchematic>& manufacture_schematic);
		static void BuildCreatorNameDelta(const std::shared_ptr<ManufactureSchematic>& manufacture_schematic);
		static void BuildSchematicComplexityDelta(const std::shared_ptr<ManufactureSchematic>& manufacture_schematic);
		static void BuildDataSizeDelta(const std::shared_ptr<ManufactureSchematic>& manufacture_schematic);
		static void BuildCustomizationStringDelta(const std::shared_ptr<ManufactureSchematic>& manufacture_schematic);
		static void BuildCustomizationModelDelta(const std::shared_ptr<ManufactureSchematic>& manufacture_schematic);
		static void BuildPrototypeModelDelta(const std::shared_ptr<ManufactureSchematic>& manufacture_schematic);
		static void BuildActiveDelta(const std::shared_ptr<ManufactureSchematic>& manufacture_schematic);
		static void BuildSlotCountDelta(const std::shared_ptr<ManufactureSchematic>& manufacture_schematic);
		static void BuildSlotDelta(const std::shared_ptr<ManufactureSchematic>& manufacture_schematic);
		static void BuildExperimentDelta(const std::shared_ptr<ManufactureSchematic>& manufacture_schematic);
		static void BuildCustomizationDelta(const std::shared_ptr<ManufactureSchematic>& manufacture_schematic);		

        // baselines
        static swganh::messages::BaselinesMessage BuildBaseline3(const std::shared_ptr<ManufactureSchematic>& manufacture_schematic);
        static swganh::messages::BaselinesMessage BuildBaseline6(const std::shared_ptr<ManufactureSchematic>& manufacture_schematic);		
		static swganh::messages::BaselinesMessage BuildBaseline7(const std::shared_ptr<ManufactureSchematic>& manufacture_schematic);		
    };

}}}  // swganh::object::manufacture_schematic

#endif  // SWGANH_OBJECT_MANUFACTURE_SCHEMATIC_MANUFACTURE_SCHEMATIC_MESSAGE_BUILDER_H_
