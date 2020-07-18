/*
 * RunningStat.h
 *
 *  Created on: Aug 22, 2019
 *      Author: bcthund
 */

#include <cmath>

#ifndef HEADERS_CORE_RUNNINGSTAT_H_
#define HEADERS_CORE_RUNNINGSTAT_H_

namespace Core {

	class RunningStat
		{
		public:
			RunningStat() : m_n(0), m_oldM(0), m_newM(0), m_oldS(0), m_newS(0) {}

			void Clear()						{	m_n = 0;	}
			int NumDataValues() const			{	return m_n;	}
			float Mean() const					{	return (m_n > 0) ? m_newM : 0.0;	}
			float Variance() const				{	return ( (m_n > 1) ? m_newS/(m_n - 1) : 0.0 );	}
			float StandardDeviation() const		{	return sqrt( Variance() );	}

			void Push(float x)
			{
				m_n++;

				// See Knuth TAOCP vol 2, 3rd edition, page 232
				if (m_n == 1)
				{
					m_oldM = m_newM = x;
					m_oldS = 0.0;
				}
				else
				{
					m_newM = m_oldM + (x - m_oldM)/m_n;
					m_newS = m_oldS + (x - m_oldM)*(x - m_newM);

					// set up for next iteration
					m_oldM = m_newM;
					m_oldS = m_newS;
				}
			}

		private:
			int m_n;
			float m_oldM, m_newM, m_oldS, m_newS;
		};

} /* namespace Core */

#endif /* HEADERS_CORE_RUNNINGSTAT_H_ */
