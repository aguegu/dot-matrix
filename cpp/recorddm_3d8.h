/*
 * recorddm_3d8.h
 *
 *  Created on: Mar 29, 2013
 *      Author: agu
 */

#ifndef RECORD_DM_3D8_H_
#define RECORD_DM_3D8_H_

#include "record_3d8.h"
#include "dot-matrix-3d8.h"
#include "byte-reverse.h"

class RecordDm3d8: public Record3d8
{
public:
	RecordDm3d8(DotMatrix3d8 & dm);
	virtual ~RecordDm3d8();

	void putDM();
	void putDMrevZ();
	void putReverseDM();
private:
	DotMatrix & _dm;
};

#endif /* RECORD_DM_3D8_H_ */
