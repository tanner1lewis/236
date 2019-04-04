//
// Created by Tanner Lewis on 2019-03-04.
//

#ifndef DATABASE_H
#define DATABASE_H

#include <map>
#include "relation.h"

class Database : public map<string, Relation> {

};

#endif