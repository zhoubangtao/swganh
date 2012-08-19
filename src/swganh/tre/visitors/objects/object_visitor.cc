// This file is part of SWGANH which is released under the MIT license.
// See file LICENSE or go to http://swganh.com/LICENSE

#include "object_visitor.h"

#include "../../iff/iff.h"
#include "../../iff/filenode.h"
#include "../../iff/foldernode.h"

#include <swganh/tre/resource_manager.h>
#include <swganh/tre/visitors/slots/slot_arrangement_visitor.h>
#include <swganh/tre/visitors/slots/slot_descriptor_visitor.h>

using namespace swganh::tre;
using namespace std;
using namespace std::placeholders;

AttributeHandlerIndex ObjectVisitor::attributeHandler_;

ObjectVisitor::ObjectVisitor()
	: VisitorInterface(), has_aggregate_(false), loaded_reference_(false)
{
	if(attributeHandler_.empty())
	{
		attributeHandler_.insert(make_pair(string("animationMapFilename"), bind(&ObjectVisitor::_handleString, _1, _2, _3)));
		attributeHandler_.insert(make_pair(string("appearanceFilename"), bind(&ObjectVisitor::_handleString, _1, _2, _3)));
		attributeHandler_.insert(make_pair(string("arrangementDescriptorFilename"), bind(&ObjectVisitor::_handleString, _1, _2, _3)));
		attributeHandler_.insert(make_pair(string("clearFloraRadius"), bind(&ObjectVisitor::_handleFloat, _1, _2, _3)));
		attributeHandler_.insert(make_pair(string("clientDataFile"), bind(&ObjectVisitor::_handleString, _1, _2, _3)));
		attributeHandler_.insert(make_pair(string("cockpitFilename"), bind(&ObjectVisitor::_handleString, _1, _2, _3)));
		attributeHandler_.insert(make_pair(string("collisionActionBlockFlags"), bind(&ObjectVisitor::_handleInt, _1, _2, _3)));
		attributeHandler_.insert(make_pair(string("collisionActionFlags"), bind(&ObjectVisitor::_handleInt, _1, _2, _3)));
		attributeHandler_.insert(make_pair(string("collisionActionPassFlags"), bind(&ObjectVisitor::_handleInt, _1, _2, _3)));
		attributeHandler_.insert(make_pair(string("collisionHeight"), bind(&ObjectVisitor::_handleFloat, _1, _2, _3)));
		attributeHandler_.insert(make_pair(string("collisionLength"), bind(&ObjectVisitor::_handleFloat, _1, _2, _3)));
		attributeHandler_.insert(make_pair(string("collisionMaterialBlockFlags"), bind(&ObjectVisitor::_handleInt, _1, _2, _3)));
		attributeHandler_.insert(make_pair(string("collisionMaterialFlags"), bind(&ObjectVisitor::_handleInt, _1, _2, _3)));
		attributeHandler_.insert(make_pair(string("collisionMaterialPassFlags"), bind(&ObjectVisitor::_handleInt, _1, _2, _3)));
		attributeHandler_.insert(make_pair(string("collisionRadius"), bind(&ObjectVisitor::_handleFloat, _1, _2, _3)));
		attributeHandler_.insert(make_pair(string("containerType"), bind(&ObjectVisitor::_handleInt, _1, _2, _3)));
		attributeHandler_.insert(make_pair(string("containerVolumeLimit"), bind(&ObjectVisitor::_handleInt, _1, _2, _3)));
		attributeHandler_.insert(make_pair(string("detailedDescription"), bind(&ObjectVisitor::_handleClientString, _1, _2, _3)));
		attributeHandler_.insert(make_pair(string("gameObjectType"), bind(&ObjectVisitor::_handleInt, _1, _2, _3)));
		attributeHandler_.insert(make_pair(string("hasWings"), bind(&ObjectVisitor::_handleBool, _1, _2, _3)));
		attributeHandler_.insert(make_pair(string("interiorLayoutFileName"), bind(&ObjectVisitor::_handleString, _1, _2, _3)));
		attributeHandler_.insert(make_pair(string("locationReservationRadius"), bind(&ObjectVisitor::_handleFloat, _1, _2, _3)));
		attributeHandler_.insert(make_pair(string("lookAtText"), bind(&ObjectVisitor::_handleClientString, _1, _2, _3)));
		attributeHandler_.insert(make_pair(string("movementDatatable"), bind(&ObjectVisitor::_handleString, _1, _2, _3)));
		attributeHandler_.insert(make_pair(string("niche"), bind(&ObjectVisitor::_handleInt, _1, _2, _3)));
		attributeHandler_.insert(make_pair(string("noBuildRadius"), bind(&ObjectVisitor::_handleFloat, _1, _2, _3)));
		attributeHandler_.insert(make_pair(string("numberOfPoles"), bind(&ObjectVisitor::_handleInt, _1, _2, _3)));
		attributeHandler_.insert(make_pair(string("objectName"), bind(&ObjectVisitor::_handleClientString, _1, _2, _3)));
		attributeHandler_.insert(make_pair(string("onlyVisibleInTools"), bind(&ObjectVisitor::_handleBool, _1, _2, _3)));
		attributeHandler_.insert(make_pair(string("playerControlled"), bind(&ObjectVisitor::_handleBool, _1, _2, _3)));
		attributeHandler_.insert(make_pair(string("portalLayoutFilename"), bind(&ObjectVisitor::_handleString, _1, _2, _3)));
		attributeHandler_.insert(make_pair(string("race"), bind(&ObjectVisitor::_handleInt, _1, _2, _3)));
		attributeHandler_.insert(make_pair(string("radius"), bind(&ObjectVisitor::_handleFloat, _1, _2, _3)));
		attributeHandler_.insert(make_pair(string("scale"), bind(&ObjectVisitor::_handleFloat, _1, _2, _3)));
		attributeHandler_.insert(make_pair(string("scaleThresholdBeforeExtentTest"), bind(&ObjectVisitor::_handleFloat, _1, _2, _3)));
		attributeHandler_.insert(make_pair(string("sendToClient"), bind(&ObjectVisitor::_handleBool, _1, _2, _3)));
		attributeHandler_.insert(make_pair(string("slopeModAngle"), bind(&ObjectVisitor::_handleFloat, _1, _2, _3)));
		attributeHandler_.insert(make_pair(string("slopeModPercent"), bind(&ObjectVisitor::_handleFloat, _1, _2, _3)));
		attributeHandler_.insert(make_pair(string("slotDescriptorFilename"), bind(&ObjectVisitor::_handleString, _1, _2, _3)));
		attributeHandler_.insert(make_pair(string("snapToTerrain"), bind(&ObjectVisitor::_handleBool, _1, _2, _3)));
		attributeHandler_.insert(make_pair(string("species"), bind(&ObjectVisitor::_handleInt, _1, _2, _3)));
		attributeHandler_.insert(make_pair(string("stepHeight"), bind(&ObjectVisitor::_handleFloat, _1, _2, _3)));
		attributeHandler_.insert(make_pair(string("structureFootprintFileName"), bind(&ObjectVisitor::_handleString, _1, _2, _3)));
		attributeHandler_.insert(make_pair(string("swimHeight"), bind(&ObjectVisitor::_handleFloat, _1, _2, _3)));
		attributeHandler_.insert(make_pair(string("targetable"), bind(&ObjectVisitor::_handleBool, _1, _2, _3)));
		attributeHandler_.insert(make_pair(string("terrainModificationFileName"), bind(&ObjectVisitor::_handleString, _1, _2, _3)));
		attributeHandler_.insert(make_pair(string("tintPalette"), bind(&ObjectVisitor::_handleBool, _1, _2, _3)));
		attributeHandler_.insert(make_pair(string("useStructureFootprintOutline"), bind(&ObjectVisitor::_handleBool, _1, _2, _3)));
		attributeHandler_.insert(make_pair(string("warpTolerance"), bind(&ObjectVisitor::_handleFloat, _1, _2, _3)));
		attributeHandler_.insert(make_pair(string("waterModPercent"), bind(&ObjectVisitor::_handleFloat, _1, _2, _3)));
		attributeHandler_.insert(make_pair(string("weaponEffect"), bind(&ObjectVisitor::_handleString, _1, _2, _3)));
		attributeHandler_.insert(make_pair(string("weaponEffectIndex"), bind(&ObjectVisitor::_handleInt, _1, _2, _3)));

		attributeHandler_.insert(make_pair(string("attackType"), bind(&ObjectVisitor::_handleUnhandled, _1, _2, _3)));
		attributeHandler_.insert(make_pair(string("defaultValue"), bind(&ObjectVisitor::_handleUnhandled, _1, _2, _3)));
		attributeHandler_.insert(make_pair(string("maxValueExclusive"), bind(&ObjectVisitor::_handleUnhandled, _1, _2, _3)));
		attributeHandler_.insert(make_pair(string("minValueInclusive"), bind(&ObjectVisitor::_handleUnhandled, _1, _2, _3)));
		attributeHandler_.insert(make_pair(string("palettePathName"), bind(&ObjectVisitor::_handleUnhandled, _1, _2, _3)));
		attributeHandler_.insert(make_pair(string("defaultPaletteIndex"), bind(&ObjectVisitor::_handleUnhandled, _1, _2, _3)));
		attributeHandler_.insert(make_pair(string("cameraHeight"), bind(&ObjectVisitor::_handleUnhandled, _1, _2, _3)));
		attributeHandler_.insert(make_pair(string("variableName"), bind(&ObjectVisitor::_handleUnhandled, _1, _2, _3)));
		attributeHandler_.insert(make_pair(string("sourceVariable"), bind(&ObjectVisitor::_handleUnhandled, _1, _2, _3)));
		attributeHandler_.insert(make_pair(string("dependentVariable"), bind(&ObjectVisitor::_handleUnhandled, _1, _2, _3)));
		attributeHandler_.insert(make_pair(string("gender"), bind(&ObjectVisitor::_handleUnhandled, _1, _2, _3)));
		attributeHandler_.insert(make_pair(string("acceleration"), bind(&ObjectVisitor::_handleUnhandled, _1, _2, _3)));
		attributeHandler_.insert(make_pair(string("speed"), bind(&ObjectVisitor::_handleUnhandled, _1, _2, _3)));
		attributeHandler_.insert(make_pair(string("turnRate"), bind(&ObjectVisitor::_handleUnhandled, _1, _2, _3)));
		attributeHandler_.insert(make_pair(string("postureAlignToTerrain"), bind(&ObjectVisitor::_handleUnhandled, _1, _2, _3)));
		attributeHandler_.insert(make_pair(string("collisionOffsetX"), bind(&ObjectVisitor::_handleUnhandled, _1, _2, _3)));
		attributeHandler_.insert(make_pair(string("collisionOffsetZ"), bind(&ObjectVisitor::_handleUnhandled, _1, _2, _3)));
		attributeHandler_.insert(make_pair(string("certificationsRequired"), bind(&ObjectVisitor::_handleUnhandled, _1, _2, _3)));
		attributeHandler_.insert(make_pair(string("customizationVariableMapping"), bind(&ObjectVisitor::_handleUnhandled, _1, _2, _3)));
		attributeHandler_.insert(make_pair(string("paletteColorCustomizationVariables"), bind(&ObjectVisitor::_handleUnhandled, _1, _2, _3)));
		attributeHandler_.insert(make_pair(string("rangedIntCustomizationVariables"), bind(&ObjectVisitor::_handleUnhandled, _1, _2, _3)));
		attributeHandler_.insert(make_pair(string("constStringCustomizationVariables"), bind(&ObjectVisitor::_handleUnhandled, _1, _2, _3)));
		attributeHandler_.insert(make_pair(string("socketDestinations"), bind(&ObjectVisitor::_handleUnhandled, _1, _2, _3)));
		attributeHandler_.insert(make_pair(string("surfaceType"), bind(&ObjectVisitor::_handleUnhandled, _1, _2, _3)));

		//SCHEMATICS STUFF BELOW HERE
		
		//name is used for both "slots" and "attributes"
		attributeHandler_.insert(make_pair(string("name"), bind(&ObjectVisitor::_handleUnhandled, _1, _2, _3)));
		
		//slots marks the beginning of the slots section
		attributeHandler_.insert(make_pair(string("slots"), bind(&ObjectVisitor::_handleUnhandled, _1, _2, _3)));
		attributeHandler_.insert(make_pair(string("hardpoint"), bind(&ObjectVisitor::_handleUnhandled, _1, _2, _3)));
		
		//attributes marks the beginning of the attributes section
		attributeHandler_.insert(make_pair(string("attributes"), bind(&ObjectVisitor::_handleUnhandled, _1, _2, _3)));
		attributeHandler_.insert(make_pair(string("experiment"), bind(&ObjectVisitor::_handleUnhandled, _1, _2, _3)));
		attributeHandler_.insert(make_pair(string("value"), bind(&ObjectVisitor::_handleUnhandled, _1, _2, _3)));

		//marks the end of the draft schematic.
		attributeHandler_.insert(make_pair(string("craftedSharedTemplate"), bind(&ObjectVisitor::_handleUnhandled, _1, _2, _3)));
	}
}

void ObjectVisitor::visit_folder(std::shared_ptr<folder_node> node)
{
}

void ObjectVisitor::visit_data(std::shared_ptr<file_node> node)
{
	const std::string& nameRef = node->name();
	if(nameRef == "XXXX")
	{
		_handleXXXX(node->data());
	}
	else if(nameRef == "DERVXXXX")
	{
		_handleDERVXXXX(node->data());
	}

}

void ObjectVisitor::_handleXXXX(anh::ByteBuffer& buf)
{
	if(buf.size() > 0)
	{
		if(buf.peek<char>() == 1)
		{
			//This is a weird schematic edge case
		}
		else
		{
			std::string attributeName = buf.read<std::string>(false,true);
			AttributeHandlerIndexIterator it = attributeHandler_.find(attributeName);

			if(it != attributeHandler_.cend())
			{
				it->second(this, attributeName, buf);
			}
			else
			{
				printf("WARNING: \"%s\" is truly unhandled!\n", attributeName.c_str());
			}
		}
	}
}

void ObjectVisitor::_handleDERVXXXX(anh::ByteBuffer& buf)
{
	parentFiles.insert(buf.read<std::string>(false,true));
}

void ObjectVisitor::_handleClientString(ObjectVisitor* dst, string& name, anh::ByteBuffer& buf)
{
	if(buf.read<char>())
	{
		shared_ptr<ClientString> cs = make_shared<ClientString>();
		if(buf.read<char>())
		{
			cs->file = buf.read<std::string>(false,true);
			if(buf.read<char>())
			{
				cs->entry = buf.read<std::string>(false,true);
			}
		}
		dst->attributes_.insert(AttributeMap::value_type(move(name), std::make_shared<boost::any>(cs)));
	}
}

void ObjectVisitor::_handleString(ObjectVisitor* dst, string& name, anh::ByteBuffer& buf)
{
	if(buf.read<char>())
	{
		dst->attributes_.insert(AttributeMap::value_type(move(name), std::make_shared<boost::any>(buf.read<std::string>(false,true))));
	}
}

void ObjectVisitor::_handleInt(ObjectVisitor* dst, string& name, anh::ByteBuffer& buf)
{
	if(buf.read<char>())
	{
		buf.read<char>();
		uint32_t buffer = buf.read<uint32_t>();
		dst->attributes_.insert(AttributeMap::value_type(move(name), std::make_shared<boost::any>(buffer)));
	}
}

void ObjectVisitor::_handleFloat(ObjectVisitor* dst, string& name, anh::ByteBuffer& buf)
{
	if(buf.read<char>())
	{
		buf.read<char>();
		float buffer = buf.read<float>();
		dst->attributes_.insert(AttributeMap::value_type(move(name), std::make_shared<boost::any>(buffer)));
	}
}

void ObjectVisitor::_handleBool(ObjectVisitor* dst, string& name, anh::ByteBuffer& buf)
{
	if(buf.read<char>())
	{
		dst->attributes_.insert(AttributeMap::value_type(move(name), std::make_shared<boost::any>((buf.read<char>()) ? true : false)));
	}
}

void ObjectVisitor::_handleUnhandled(ObjectVisitor* dst, std::string& name, anh::ByteBuffer& buf)
{
	//@TODO: PRINT A MESSAGE
}

void ObjectVisitor::debug()
{
	std::set<std::string>::iterator parentIt = parentFiles.begin();
	std::set<std::string>::iterator parentEnd = parentFiles.end();
	while(parentIt != parentEnd)
	{
		printf("Has Parent: %s\n", parentIt->c_str());
		++parentIt;
	}

	AttributeMap::const_iterator it = attributes_.cbegin();

	while(it != attributes_.cend())
	{
		printf("Attribute: \"%s\", value=", it->first.c_str());
		if(it->second->type() == typeid(std::uint32_t))
		{
			printf("%d", boost::any_cast<std::uint32_t>(it->second));
		}
		else if(it->second->type() == typeid(shared_ptr<std::string>))
		{
			printf("%s", boost::any_cast<shared_ptr<std::string>>(it->second)->c_str());
		}
		else if(it->second->type() == typeid(shared_ptr<ClientString>))
		{
			shared_ptr<ClientString> cs = boost::any_cast<shared_ptr<ClientString>>(it->second);
			printf("@%s:%s", cs->file.c_str(), cs->entry.c_str());
		}
		else if(it->second->type() == typeid(float))
		{
			printf("%f", boost::any_cast<float>(it->second));
		}
		else if(it->second->type() == typeid(shared_ptr<bool>))
		{
			printf("%s", (boost::any_cast<bool>(it->second)) ? "true" : "false");
		}
		printf("\n");
		++it;
	}
}


void ObjectVisitor::load_aggregate_data(swganh::tre::ResourceManager* f)
{
	if(!has_aggregate_)
	{
		AttributeMap aggregateAttributeMap;

		std::for_each(parentFiles.begin(), parentFiles.end(), [&] (std::string parentFile)
		{
			auto subI = std::static_pointer_cast<ObjectVisitor>(f->getResourceByName(parentFile, OIFF_VISITOR));
			subI->load_aggregate_data(f);

			//Now we continue to build up our map.
			std::for_each(subI->attributes_.begin(), subI->attributes_.end(), [&] (AttributeMap::value_type pair) {
				AttributeMap::iterator lb = aggregateAttributeMap.lower_bound(pair.first);
				if(lb != aggregateAttributeMap.end() && !(aggregateAttributeMap.key_comp()(pair.first, lb->first)))
				{
					lb->second = pair.second;
				}
				else
				{
					aggregateAttributeMap.insert(lb, AttributeMap::value_type(pair.first, pair.second));
				}
			});
		});

		std::for_each(attributes_.begin(), attributes_.end(), [&] (AttributeMap::value_type pair) {
			AttributeMap::iterator lb = aggregateAttributeMap.lower_bound(pair.first);
			if(lb != aggregateAttributeMap.end() && !(aggregateAttributeMap.key_comp()(pair.first, lb->first)))
			{
				lb->second = pair.second;
			}
			else
			{
				aggregateAttributeMap.insert(lb, AttributeMap::value_type(pair.first, pair.second));    // Use lb as a hint to insert,
																// so it can avoid another lookup
			}
		});

		attributes_ = std::move(aggregateAttributeMap);
		has_aggregate_ = true;		
	}
}

void ObjectVisitor::load_referenced_files(swganh::tre::ResourceManager* f)
{
	if (loaded_reference_)
		return;
	std::map<std::string, std::shared_ptr<boost::any>>::iterator itr;
	std::map<std::string, std::shared_ptr<boost::any>>::iterator end_itr = attributes_.end();

	//animationMapFilename
	//appearanceFilename
	//arrangementDescriptorFilename
	itr = attributes_.find("arrangementDescriptorFilename");
	if(itr != end_itr)
	{
		std::string value = boost::any_cast<std::string>(*(itr->second));
		if(value != "") {
			auto newVal = std::static_pointer_cast<SlotArrangementVisitor>(f->getResourceByName(value, SLOT_ARRANGEMENT_VISITOR));
			itr->second = std::make_shared<boost::any>(newVal);
		}
		else
		{
			shared_ptr<SlotArrangementVisitor> arrangement = nullptr;
			itr->second = make_shared<boost::any>(arrangement);
		}
	}

	//clientDataFile
	//cockpitFileName
	//interiorLayoutFileName
	//movementDatatable
	//portalLayoutFilename
	/*itr = attributes_.find("portalLayoutFilename");
	if(itr != end_itr)
	{
		itr->second = f.load<pob_interpreter>(itr->first);
	}*/

	//slotDescriptorFilename
	itr = attributes_.find("slotDescriptorFilename");
	if(itr != end_itr)
	{
		std::string value = boost::any_cast<std::string>(*(itr->second));
		if(value != "") {
			auto newVal = std::static_pointer_cast<SlotDescriptorVisitor>(f->getResourceByName(value, SLOT_DESCRIPTOR_VISITOR));
			itr->second = std::make_shared<boost::any>(newVal);
		}
		else
		{
			shared_ptr<SlotDescriptorVisitor> descriptor = nullptr;
			itr->second = make_shared<boost::any>(descriptor);
		}
	}

	//structureFootprintFileName
	//terrainModificationFileName

	loaded_reference_ = true;
}
