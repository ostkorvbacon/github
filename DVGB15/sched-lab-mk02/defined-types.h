// *********************************************************************
//
//  - Name: defined-types.h
//  - Created on: Sep 23, 2020
//  - Author: Marcus Pieskä
// 
// *********************************************************************

#ifndef DEFINED_TYPES 
#define DEFINED_TYPES

typedef long int i64;
typedef double f64;

typedef struct sch_task {
  i64 arrival;
  i64 duration;
  i64 deadline;
  i64 abs_deadline;
  i64 index;
  void* meta_data;
} sch_task;

#endif 

// *********************************************************************
