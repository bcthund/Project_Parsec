/*
 * Groups.cpp
 *
 *  Created on: Jul 21, 2020
 *      Author: bcthund
 */

#include <core/Groups.h>

namespace Core {

	_Groups::_Groups() {
		setSource("Groups");
		add("None", false);		// Default 0 group (No group is still a group)
	}

	_Groups::~_Groups() {
		// TODO Auto-generated destructor stub
	}

	void _Groups::setExclusive(std::string name, bool b) {
		t_VectorMap::get(name).bExclusive = b;
	}

	void _Groups::setExclusive(int id, bool b) {
		t_VectorMap::get(id).bExclusive = b;
	}

	/**
	 * @brief Re-implemented from t_Vector
	 *
	 * @param name
	 * @param bExclusive
	 * @return
	 */
	t_Group & _Groups::add(std::string name, bool bExclusive) {
		t_Group group;
		group.index = size();
		group.name = name;
		group.bExclusive = bExclusive;
		group.object = "";
		return t_VectorMap::add(name, group);
	}

	void _Groups::setActive(std::string name, std::string object) {
		t_VectorMap::get(name).object = object;
	}

	void _Groups::setActive(int id, std::string object) {
		t_VectorMap::get(id).object = object;
	}

} /* namespace Core */
