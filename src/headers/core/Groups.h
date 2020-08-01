/*
 * Groups.h
 *
 *  Created on: Jul 21, 2020
 *      Author: bcthund
 */

#ifndef HEADERS_CORE_GROUPS_H_
#define HEADERS_CORE_GROUPS_H_

#include "core_functions.h"

namespace Core {

	struct t_Group {
		int index;				// Index of this group
		std::string name;		// Name of this group
		std::string object;		// Name of active object in group (blank for none)
		bool bExclusive;		// Exclusive mode requires one item to always be active (external logic)

		t_Group() {
			index = 0;
			name = "";
			object = "";
			bExclusive = false;
		}
	};

	class _Groups : virtual public t_VectorMap<t_Group> {
		public:
			_Groups();
			virtual ~_Groups();

			t_Group & add(std::string name, bool bExclusive=true);

			void setExclusive(std::string name, bool b=true);
			void setExclusive(int id, bool b=true);

			void setActive(std::string name, std::string object);
			void setActive(int id, std::string object);
	};

} /* namespace Core */

#endif /* HEADERS_CORE_GROUPS_H_ */
